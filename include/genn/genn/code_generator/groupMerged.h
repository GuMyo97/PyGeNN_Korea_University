#pragma once

// Standard includes
#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>

// GeNN includes
#include "gennExport.h"
#include "currentSourceInternal.h"
#include "neuronGroupInternal.h"
#include "synapseGroupInternal.h"

// GeNN code generator includes
#include "code_generator/backendBase.h"
#include "code_generator/codeGenUtils.h"

// Forward declarations
namespace CodeGenerator
{
class CodeStream;
}

//----------------------------------------------------------------------------
// CodeGenerator::GroupMerged
//----------------------------------------------------------------------------
//! Very thin wrapper around a number of groups which have been merged together
namespace CodeGenerator
{
template<typename G>
class GroupMerged
{
public:
    //------------------------------------------------------------------------
    // Enumerations
    //------------------------------------------------------------------------
    enum class FieldType
    {
        Standard,
        Host,
        ScalarEGP,
        PointerEGP,
    };

    //------------------------------------------------------------------------
    // Typedefines
    //------------------------------------------------------------------------
    typedef G GroupInternal;
    typedef std::function<std::string(const G &, size_t)> GetFieldValueFunc;
    typedef std::tuple<std::string, std::string, GetFieldValueFunc, FieldType> Field;

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    size_t getIndex() const { return m_Index; }

    const std::string &getName() const { return m_Name; }

    //! Get 'archetype' neuron group - it's properties represent those of all other merged neuron groups
    const GroupInternal &getArchetype() const { return m_Groups.front().get(); }

    //! Gets access to underlying vector of neuron groups which have been merged
    const std::vector<std::reference_wrapper<const GroupInternal>> &getGroups() const{ return m_Groups; }

    //! Get group fields
    const std::map<std::string, Field> &getFields() const{ return m_Fields; }

    //! Get group fields, sorted into order they will appear in struct
    std::vector<Field> getSortedFields(const BackendBase &backend) const
    {
        // Make a copy of fields and sort so largest come first. This should mean that due
        // to structure packing rules, significant memory is saved and estimate is more precise
        std::vector<Field> sortedFields;
        sortedFields.reserve(m_Fields.size());
        std::transform(m_Fields.cbegin(), m_Fields.cend(), std::back_inserter(sortedFields),
                       [](const typename std::map<std::string, Field>::value_type &f) { return f.second; });
        std::sort(sortedFields.begin(), sortedFields.end(),
                  [&backend](const Field &a, const Field &b)
                  {
                      return (backend.getSize(std::get<0>(a)) > backend.getSize(std::get<0>(b)));
                  });
        return sortedFields;

    }

    //! Generate declaration of struct to hold this merged group
    void generateStruct(CodeStream &os, const BackendBase &backend, bool host = false) const
    {
        os << "struct Merged" << getName() << "Group" << getIndex() << std::endl;
        {
            // Loop through fields and write to structure
            CodeStream::Scope b(os);
            const auto sortedFields = getSortedFields(backend);
            for(const auto &f : sortedFields) {
                // If field is a pointer and not marked as being a host field 
                // (in which case the backend should leave its type alone!)
                const std::string &type = std::get<0>(f);
                if(::Utils::isTypePointer(type) && std::get<3>(f) != FieldType::Host) {
                    // If we are generating a host structure, allow the backend to override the type
                    if(host) {
                        os << backend.getMergedGroupFieldHostType(type);
                    }
                    // Otherwise, allow the backend to add a prefix 
                    else {
                        os << backend.getPointerPrefix() << type;
                    }
                }
                // Otherwise, leave the type alone
                else {
                    os << type;
                }
                os << " " << std::get<1>(f) << ";" << std::endl;
            }
            os << std::endl;
        }

        os << ";" << std::endl;
    }

    void generateStructFieldArgumentDefinitions(CodeStream &os, const BackendBase &backend) const
    {
        // Get sorted fields
        const auto sortedFields = getSortedFields(backend);
        for(size_t fieldIndex = 0; fieldIndex < sortedFields.size(); fieldIndex++) {
            const auto &f = sortedFields[fieldIndex];
            os << backend.getMergedGroupFieldHostType(std::get<0>(f)) << " " << std::get<1>(f);
            if(fieldIndex != (sortedFields.size() - 1)) {
                os << ", ";
            }
        }
    }

    size_t getStructArraySize(const BackendBase &backend) const
    {
        // Loop through fields again to generate any EGP pushing functions that are required and to calculate struct size
        size_t structSize = 0;
        size_t largestFieldSize = 0;
        const auto sortedFields = getSortedFields(backend);
        for(const auto &f : sortedFields) {
            // Add size of field to total
            const size_t fieldSize = backend.getSize(std::get<0>(f));
            structSize += fieldSize;

            // Update largest field size
            largestFieldSize = std::max(fieldSize, largestFieldSize);
        }

        // Add total size of array of merged structures to merged struct data
        // **NOTE** to match standard struct packing rules we pad to a multiple of the largest field size
        return padSize(structSize, largestFieldSize) * getGroups().size();
    }

    std::string getVarField(const Models::Base::Var &var, const std::string &suffix = "")
    {
        // Add pointer field
        return addPointerField(var.type, var.name + suffix, m_Backend.getDeviceVarPrefix() + var.name);
    }

    std::string getEGPField(const Snippet::Base::EGP &egp)
    {
        const bool isPointer = Utils::isTypePointer(egp.type);
        const std::string prefix = isPointer ? m_Backend.getDeviceVarPrefix() : "";
        return addField(egp.type, egp.name,
                        [egp, prefix](const G &g, size_t) { return prefix + egp.name + g.getName(); },
                        isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
    }

protected:
    GroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                const std::vector<std::reference_wrapper<const GroupInternal>> groups)
    :   m_Index(index), m_Name(name), m_LiteralSuffix((precision == "float") ? "f" : ""), m_Groups(std::move(groups)),
        m_Backend(backend), m_Precision(precision), m_TimePrecision(timePrecision)
    {}

    //------------------------------------------------------------------------
    // Protected methods
    //------------------------------------------------------------------------
    const BackendBase &getBackend() const { return m_Backend; }

    const std::string &getPrecision() const{ return m_Precision; }

    const std::string &getTimePrecision() const{ return m_TimePrecision; }

    std::string getValueField(const std::string &type, const std::string &name, GetFieldValueFunc getFieldValueFn)
    {
        // Get value of field in archetype group
        const std::string archetypeValue = getFieldValueFn(getArchetype(), 0);

        // Loop through remaining groups
        // **TODO** use std::any_of for consistency
        for(size_t groupIndex = 1; groupIndex < getGroups().size(); groupIndex++) {
            const G &group = getGroups()[groupIndex];

            // If this group's field value differs - we need to pass this via struct field
            if(getFieldValueFn(group, groupIndex) != archetypeValue) {
                return addField(type, name, getFieldValueFn);
            }
        }

        // All groups must have same value so use value directly
        return archetypeValue;
    }

    std::string getPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        // Add field
        assert(!Utils::isTypePointer(type));
        return addField(type + "*", name, [prefix](const G &g, size_t) { return prefix + g.getName(); });
    }

    //! Helper to test whether parameter values are heterogeneous within merged group
    template<typename P>
    std::string getParamField(size_t index, const Snippet::Base::StringVec &paramNames, 
                              const std::string &suffix, P getParamValuesFn)
    {
        // Get value of parameter in archetype group
        const double archetypeValue = getParamValuesFn(getArchetype()).at(index);

        // If any parameter values differ from the archetype value
        if(std::any_of(getGroups().cbegin(), getGroups().cend(),
                       [archetypeValue, index, getParamValuesFn](const GroupInternal &g)
                       {
                           return (getParamValuesFn(g).at(index) != archetypeValue);
                       }))
        {
            // Add field
            return addScalarField(paramNames.at(index) + suffix,
                                  [index, getParamValuesFn](const G &g, size_t)
                                  {
                                      const auto &values = getParamValuesFn(g);
                                      return Utils::writePreciseString(values.at(index));
                                  });
        }
        // Otherwise, return precise string with archetype value
        else {
            return "(" + Utils::writePreciseString(archetypeValue) + ")";
        }
    }

    //! Helper to test whether derived parameter values are heterogeneous within merged group
    template<typename P, typename V>
    std::string getDerivedParamField(size_t index, const std::vector<V> &derivedParams, 
                                     const std::string &suffix, P getDerivedParamValuesFn)
    {
        // Get value of parameter in archetype group
        const double archetypeValue = getDerivedParamValuesFn(getArchetype()).at(index);

        // If any parameter values differ from the archetype value
        if(std::any_of(getGroups().cbegin(), getGroups().cend(),
                       [archetypeValue, index, getDerivedParamValuesFn](const GroupInternal &g)
                       {
                           return (getDerivedParamValuesFn(g).at(index) != archetypeValue);
                       }))
        {
            // Add field
            return addScalarField(derivedParams.at(index).name + suffix,
                                  [index, getDerivedParamValuesFn](const G &g, size_t)
                                  {
                                      const auto &values = getDerivedParamValuesFn(g);
                                      return Utils::writePreciseString(values.at(index));
                                  });
        }
        // Otherwise, return precise string with archetype value
        else {
            return "(" + Utils::writePreciseString(archetypeValue) + ")";
        }
    }


    std::string addField(const std::string &type, const std::string &name, GetFieldValueFunc getFieldValue, FieldType fieldType = FieldType::Standard)
    {
        // Add field to data structure
        m_Fields.emplace(std::piecewise_construct,
                         std::forward_as_tuple(name),
                         std::forward_as_tuple(type, name, getFieldValue, fieldType));

        // Return code to access field
        return "group->" + name;
    }

    std::string addScalarField(const std::string &name, GetFieldValueFunc getFieldValue, FieldType fieldType = FieldType::Standard)
    {
        return addField("scalar", name,
                        [getFieldValue, this](const G &g, size_t i)
                        {
                            return getFieldValue(g, i) + m_LiteralSuffix;
                        },
                        fieldType);
    }

    std::string addPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        return addField(type + "*", name, [prefix](const G &g, size_t) { return prefix + g.getName(); });
    }

    void generateRunnerBase(const BackendBase &backend, CodeStream &definitionsInternal,
                            CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                            CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc,
                            bool host = false) const
    {
        // Make a copy of fields and sort so largest come first. This should mean that due
        // to structure packing rules, significant memory is saved and estimate is more precise
        auto sortedFields = getSortedFields(backend);

        // If this isn't a host merged structure, generate definition for function to push group
        if(!host) {
            definitionsInternalFunc << "EXPORT_FUNC void pushMerged" << getName() << "Group" << getIndex() << "ToDevice(unsigned int idx, ";
            generateStructFieldArgumentDefinitions(definitionsInternalFunc, backend);
            definitionsInternalFunc << ");" << std::endl;
        }

        // Loop through fields again to generate any EGP pushing functions that are require
        for(const auto &f : sortedFields) {
            // If this field is for a pointer EGP, also declare function to push it
            if(std::get<3>(f) == FieldType::PointerEGP) {
                definitionsInternalFunc << "EXPORT_FUNC void pushMerged" << getName() << getIndex() << std::get<1>(f) << "ToDevice(unsigned int idx, ";
                definitionsInternalFunc << backend.getMergedGroupFieldHostType(std::get<0>(f)) << " value);" << std::endl;
            }

            // Raise error if this field is a host field but this isn't a host structure
            assert(std::get<3>(f) != FieldType::Host || host);
        }

        // If merged group is used on host
        if(host) {
            // Generate struct directly into internal definitions
            // **NOTE** we ignore any backend prefix as we're generating this struct for use on the host
            generateStruct(definitionsInternal, backend, true);

            // Declare array of these structs containing individual neuron group pointers etc
            runnerVarDecl << "Merged" << getName() << "Group" << getIndex() << " merged" << getName() << "Group" << getIndex() << "[" << getGroups().size() << "];" << std::endl;

            // Export it
            definitionsInternalVar << "EXPORT_VAR Merged" << getName() << "Group" << getIndex() << " merged" << getName() << "Group" << getIndex() << "[" << getGroups().size() << "]; " << std::endl;
        }

        // Loop through groups
        for(size_t groupIndex = 0; groupIndex < getGroups().size(); groupIndex++) {
            // If this is a merged group used on the host, directly set array entry
            if(host) {
                runnerMergedStructAlloc << "merged" << getName() << "Group" << getIndex() << "[" << groupIndex << "] = {";
                generateStructFieldArguments(runnerMergedStructAlloc, groupIndex, sortedFields);
                runnerMergedStructAlloc << "};" << std::endl;
            }
            // Otherwise, call function to push to device
            else {
                runnerMergedStructAlloc << "pushMerged" << getName() << "Group" << getIndex() << "ToDevice(" << groupIndex << ", ";
                generateStructFieldArguments(runnerMergedStructAlloc, groupIndex, sortedFields);
                runnerMergedStructAlloc << ");" << std::endl;
            }
        }
    }

private:
    //------------------------------------------------------------------------
    // Private methods
    //------------------------------------------------------------------------
    void generateStructFieldArguments(CodeStream &os, size_t groupIndex, 
                                      const std::vector<Field> &sortedFields) const
    {
        // Get group by index
        const auto &g = getGroups()[groupIndex];

        // Loop through fields
        for(size_t fieldIndex = 0; fieldIndex < sortedFields.size(); fieldIndex++) {
            const auto &f = sortedFields[fieldIndex];
            const std::string fieldInitVal = std::get<2>(f)(g, groupIndex);
            os << fieldInitVal;
            if(fieldIndex != (sortedFields.size() - 1)) {
                os << ", ";
            }
        }
    }

    //------------------------------------------------------------------------
    // Members
    //------------------------------------------------------------------------
    const size_t m_Index;
    const std::string m_Name;
    const std::string m_LiteralSuffix;
    std::map<std::string, Field> m_Fields;
    std::vector<std::reference_wrapper<const GroupInternal>> m_Groups;
    const BackendBase &m_Backend;
    const std::string m_Precision;
    const std::string m_TimePrecision;
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronSpikeQueueUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronSpikeQueueUpdateGroupMerged : public GroupMerged<NeuronGroupInternal>
{
public:
    NeuronSpikeQueueUpdateGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecison, const BackendBase &backend,
                                      const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups);

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                  CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                  CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }

    void genMergedGroupSpikeCountReset(CodeStream &os) const;
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronGroupMergedBase
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronGroupMergedBase : public GroupMerged<NeuronGroupInternal>
{
public:
    NeuronGroupMergedBase(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                          bool init, const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups);

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    //! Get code string for accessing number of neurons - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getNumNeurons();

    //! Get group structure member access for spike count
    std::string getSpikeCount();

    //! Get group structure member access for spikes
    std::string getSpikes();

    //! Get group structure member access for spike event count
    std::string getSpikeEventCount();

    //! Get group structure member access for spike events
    std::string getSpikeEvents();

    //! Get group structure member access for spike queue pointer
    std::string getSpikeQueuePointer();

    //! Get group structure member access for spike times
    std::string getSpikeTimes();

    //! Get group structure member access for simulation RNG
    std::string getSimRNG();

    //! Get group structure member for current source variable
    std::string getCurrentSourceVar(size_t childIndex, const Models::Base::Var &var);

    //! Get group structure member for postsynaptic model variable
    std::string getPSMVar(size_t childIndex, const Models::Base::Var &var);

    //! Get group structure member for postsynaptic model inSyn
    std::string getPSMInSyn(size_t childIndex);

    //! Get group structure member for postsynaptic model denDelay
    std::string getPSMDenDelay(size_t childIndex);

    //! Get group structure member for postsynaptic model denDelayPtr
    std::string getPSMDenDelayPtr(size_t childIndex);

    //! Get group structure member for incoming synapse weight update model postsynaptic variable
    std::string getInSynVar(size_t childIndex, const Models::Base::Var &var);

    //! Get group structure member for outgoing synapse weight update model presynaptic variable
    std::string getOutSynVar(size_t childIndex, const Models::Base::Var &var);

protected:
    //------------------------------------------------------------------------
    // Protected methods
    //------------------------------------------------------------------------
    template<typename T, typename V, typename C>
    void orderNeuronGroupChildren(const std::vector<T> &archetypeChildren,
                                  std::vector<std::vector<T>> &sortedGroupChildren,
                                  V getVectorFunc, C isCompatibleFunc) const
    {
        // Reserve vector of vectors to hold children for all neuron groups, in archetype order
        sortedGroupChildren.reserve(archetypeChildren.size());

        // Loop through groups
        for(const auto &g : getGroups()) {
            // Make temporary copy of this group's children
            std::vector<T> tempChildren((g.get().*getVectorFunc)());

            assert(tempChildren.size() == archetypeChildren.size());

            // Reserve vector for this group's children
            sortedGroupChildren.emplace_back();
            sortedGroupChildren.back().reserve(tempChildren.size());

            // Loop through archetype group's children
            for(const auto &archetypeG : archetypeChildren) {
                // Find compatible child in temporary list
                const auto otherChild = std::find_if(tempChildren.cbegin(), tempChildren.cend(),
                                                     [archetypeG, isCompatibleFunc](const T &g)
                                                     {
                                                         return isCompatibleFunc(archetypeG, g);
                                                     });
                assert(otherChild != tempChildren.cend());

                // Add pointer to vector of compatible merged in syns
                sortedGroupChildren.back().push_back(*otherChild);

                // Remove from original vector
                tempChildren.erase(otherChild);
            }
        }
    }

    template<typename T, typename V, typename C>
    void orderNeuronGroupChildren(std::vector<std::vector<T>> &sortedGroupChildren,
                                  V getVectorFunc, C isCompatibleFunc) const
    {
        const std::vector<T> &archetypeChildren = (getArchetype().*getVectorFunc)();
        orderNeuronGroupChildren(archetypeChildren, sortedGroupChildren, getVectorFunc, isCompatibleFunc);
    }

    //! Helper to test whether parameter values are heterogeneous within merged group
    template<typename P, typename T>
    std::string getChildParamField(size_t childIndex, size_t paramIndex, const Snippet::Base::StringVec &paramNames, 
                                   const std::string &suffix, const std::vector<std::vector<T>> &sortedGroupChildren,
                                   P getParamValuesFn)
    {
        // Get value of parameter in archetype group
        const double archetypeValue = getParamValuesFn(sortedGroupChildren.at(0).at(childIndex)).at(paramIndex);

         // Loop through groups within merged group
        for(size_t i = 0; i < sortedGroupChildren.size(); i++) {
            const auto group = sortedGroupChildren.at(i).at(childIndex);
            if(getParamValuesFn(group).at(paramIndex) != archetypeValue) {
                // Add field
                return addScalarField(paramNames.at(paramIndex) + suffix,
                                      [childIndex, paramIndex, getParamValuesFn, &sortedGroupChildren](const NeuronGroupInternal&, size_t groupIndex)
                                      {
                                          const auto &values = getParamValuesFn(sortedGroupChildren.at(groupIndex).at(childIndex));
                                          return Utils::writePreciseString(values.at(paramIndex));
                                      });
            }
        }

        return "(" + Utils::writePreciseString(archetypeValue) + ")";
    }

    //! Helper to test whether parameter values are heterogeneous within merged group
    template<typename P, typename T, typename V>
    std::string getChildDerivedParamField(size_t childIndex, size_t paramIndex, const std::vector<V> &derivedParams,
                                          const std::string &suffix, const std::vector<std::vector<T>> &sortedGroupChildren,
                                          P getDerivedParamValuesFn)
    {
        // Get value of derived parameter in archetype group
        const double archetypeValue = getDerivedParamValuesFn(sortedGroupChildren.at(0).at(childIndex)).at(paramIndex);

         // Loop through groups within merged group
        for(size_t i = 0; i < sortedGroupChildren.size(); i++) {
            const auto group = sortedGroupChildren.at(i).at(childIndex);
            if(getDerivedParamValuesFn(group).at(paramIndex) != archetypeValue) {
                // Add field
                return addScalarField(derivedParams.at(paramIndex).name + suffix,
                                      [childIndex, paramIndex, getDerivedParamValuesFn, &sortedGroupChildren](const NeuronGroupInternal&, size_t groupIndex)
                                      {
                                          const auto &values = getDerivedParamValuesFn(sortedGroupChildren.at(groupIndex).at(childIndex));
                                          return Utils::writePreciseString(values.at(paramIndex));
                                      });
            }
        }

        return "(" + Utils::writePreciseString(archetypeValue) + ")";
    }

    const std::vector<std::vector<std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>>>> &getSortedMergedInSyns() const { return m_SortedMergedInSyns; }
    const std::vector<std::vector<CurrentSourceInternal*>> &getSortedCurrentSources() const{ return m_SortedCurrentSources; }
    const std::vector<std::vector<SynapseGroupInternal *>> &getSortedInSynWithPostVars() const { return m_SortedInSynWithPostVars; }
    const std::vector<std::vector<SynapseGroupInternal *>> &getSortedOutSynWithPreVars() const { return m_SortedOutSynWithPreVars; }

private:
    //------------------------------------------------------------------------
    // Members
    //------------------------------------------------------------------------
    std::vector<std::vector<std::pair<SynapseGroupInternal *, std::vector<SynapseGroupInternal *>>>> m_SortedMergedInSyns;
    std::vector<std::vector<CurrentSourceInternal*>> m_SortedCurrentSources;
    std::vector<std::vector<SynapseGroupInternal *>> m_SortedInSynWithPostVars;
    std::vector<std::vector<SynapseGroupInternal *>> m_SortedOutSynWithPreVars;
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronUpdateGroupMerged : public NeuronGroupMergedBase
{
public:
    NeuronUpdateGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                            const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups);

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    //! Get the expression to calculate the queue offset for accessing state of variables this timestep
    std::string getCurrentQueueOffset();

    //! Get the expression to calculate the queue offset for accessing state of variables in previous timestep
    std::string getPrevQueueOffset();

    //! Get group structure member for spike recording
    std::string getRecordSpk();

    //! Get group structure member for spike event recording
    std::string getRecordSpkEvent();

    //! Get code string for accessing neuron parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getNeuronParam(size_t index);

    //! Get code string for accessing neuron derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getNeuronDerivedParam(size_t index);

    //! Get code string for accessing current source parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getCurrentSourceParam(size_t childIndex, size_t paramIndex);

    //! Get code string for accessing current source derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getCurrentSourceDerivedParam(size_t childIndex, size_t paramIndex);

    //! Get group structure member for current source variable
    std::string getCurrentSourceEGP(size_t childIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing postsynaptic model parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getPSMParam(size_t childIndex, size_t paramIndex);

    //! Get code string for accessing postsynaptic model derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getPSMDerivedParam(size_t childIndex, size_t paramIndex);

    //! Get group structure member for postsynaptic model extra global parameter
    std::string getPSMEGP(size_t childIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing postsynaptic model variables made constant with GLOBAL_G - may be a literal or
    //! group structure member access, in which case, required field will be added
    std::string getPSMGlobalVar(size_t childIndex, size_t varIndex);

    //! Get code string for accessing incoming synapse weight update model parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getInSynParam(size_t childIndex, size_t paramIndex);

    //! Get code string for accessing incoming synapse weight update model derived parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getInSynDerivedParam(size_t childIndex, size_t paramIndex);

    //! Get group structure member for incoming synapse weight update model extra global parameter
    std::string getInSynEGP(size_t childIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing outgoing synapse weight update model parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getOutSynParam(size_t childIndex, size_t paramIndex);

    //! Get code string for accessing outgoing synapse weight update model derived parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getOutSynDerivedParam(size_t childIndex, size_t paramIndex);

    //! Get group structure member for outgoing synapse weight update model extra global parameter
    std::string getOutSynEGP(size_t childIndex, const Models::Base::EGP &egp);

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronInitGroupMerged : public NeuronGroupMergedBase
{
public:
    NeuronInitGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                          const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups);

    //! Get code string for accessing neuron var init parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getVarInitParam(size_t varIndex, size_t paramIndex);

    //! Get code string for accessing neuron var init derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getVarInitDerivedParam(size_t varIndex, size_t paramIndex);
    
    //! Get group structure member for var init extra global parameter
    std::string getVarInitEGP(size_t varIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing current source var init parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getCurrentSourceVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing current source var init derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getCurrentSourceVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing current source var init extra global parameter
    std::string getCurrentSourceVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing postsynaptic model var init parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getPSMVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing postsynaptic model var init derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getPSMVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing postsynaptic model var init extra global parameter
    std::string getPSMVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing incoming synapse weight update model post var init parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getInSynPostVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing incoming synapse weight update model post var init derived parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getInSynPostVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing incoming synapse weight update model post var init extra global parameter
    std::string getInSynPostVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp);

    //! Get code string for accessing outgoing synapse weight update model pre var init parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getOutSynPreVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex);

    //! Get code string for accessing outgoing synapse weight update model pre var init derived parameter - 
    //! may be a literal or group structure member access, in which case, required field will be added
    std::string getOutSynPreVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex);
    
    //! Get code string for accessing outgoing synapse weight update model pre var init extra global parameter
    std::string getOutSynPreVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp);

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDendriticDelayUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDendriticDelayUpdateGroupMerged : public GroupMerged<SynapseGroupInternal>
{
public:
    SynapseDendriticDelayUpdateGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                           const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &group);

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

// ----------------------------------------------------------------------------
// SynapseConnectivityHostInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseConnectivityHostInitGroupMerged : public GroupMerged<SynapseGroupInternal>
{
public:
    SynapseConnectivityHostInitGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                           const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups);

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc, true);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseGroupMerged : public GroupMerged<SynapseGroupInternal>
{
public:
    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    std::string getRowStride();

    std::string getColStride();

    std::string getNumSrcNeurons();

    std::string getNumTrgNeurons();

     std::string getInSyn();

    std::string getDenDelay();

    std::string getDenDelayPtr();

    std::string getSrcSpikes();

    std::string getSrcNumSpikes();

    std::string getSrcSpikeEvents();

    std::string getSrcNumSpikeEvents();

    std::string getSrcSpikeQueuePointer();

    std::string getSrcSpikeTimes();

    //! Get code string for accessing source neuron parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getSrcNeuronParam(size_t index);

    std::string getSrcNeuronVar(const Models::Base::Var &var);

    std::string getSrcNeuronEGP(const Snippet::Base::EGP &egp);

    //! Get code string for accessing source neuron derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getSrcNeuronDerivedParam(size_t index);

    std::string getTrgSpikes();

    std::string getTrgNumSpikes();

    std::string getTrgSpikeQueuePointer();

    std::string getTrgSpikeTimes();

    //! Get code string for accessing target neuron parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getTrgNeuronParam(size_t index);

    //! Get code string for accessing target neuron derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getTrgNeuronDerivedParam(size_t index);

    std::string getTrgNeuronVar(const Models::Base::Var &var);

    std::string getTrgNeuronEGP(const Snippet::Base::EGP &egp);

    //! Get the expression to calculate the delay slot for accessing
    //! Presynaptic neuron state variables, taking into account axonal delay
    std::string getPresynapticAxonalDelaySlot();

    //! Get the expression to calculate the delay slot for accessing
    //! Postsynaptic neuron state variables, taking into account back propagation delay
    std::string getPostsynapticBackPropDelaySlot();

    std::string getDendriticDelayOffset(const std::string &offset = "");

    //! Get code string for accessing weight update model parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getWUParam(size_t index);

    //! Get code string for accessing weight update model derived parameter - may be a literal or 
    //! group structure member access, in which case, required field will be added
    std::string getWUDerivedParam(size_t index);

    std::string getWUVar(const Models::Base::Var &var);

    //! Get code string for accessing weight update model variables made constant with GLOBAL_G - may be a literal or
    //! group structure member access, in which case, required field will be added
    std::string getWUGlobalVar(size_t varIndex);

    std::string getWUVarInitParam(size_t varIndex, size_t paramIndex);

    std::string getWUVarInitDerivedParam(size_t varIndex, size_t paramIndex);

    std::string getWUVarInitEGP(size_t varIndex, const Snippet::Base::EGP &egp);

    std::string getConnectivityInitParam(size_t paramIndex);

    std::string getConnectivityInitDerivedParam(size_t paramIndex);

    std::string getConnectivityInitEGP(const Snippet::Base::EGP &egp);

    std::string getRowLength();

    std::string getInd();

    std::string getColLength();

    std::string getRemap();

    std::string getSynRemap();

    std::string getBitmask();

    std::string getKernelSize(size_t dimension);

protected:
    SynapseGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                           const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   GroupMerged<SynapseGroupInternal>(index, name, precision, timePrecision, backend, groups)
    {
    }

private:
    //------------------------------------------------------------------------
    // Private methods
    //------------------------------------------------------------------------
    std::string addPSPointerField(const std::string &type, const std::string &name, const std::string &prefix);
    std::string addSrcPointerField(const std::string &type, const std::string &name, const std::string &prefix);
    std::string addTrgPointerField(const std::string &type, const std::string &name, const std::string &prefix);
    std::string addWeightSharingPointerField(const std::string &type, const std::string &name, const std::string &prefix);
};

//----------------------------------------------------------------------------
// CodeGenerator::PresynapticUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT PresynapticUpdateGroupMerged : public SynapseGroupMerged
{
public:
    PresynapticUpdateGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                 const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::PostsynapticUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT PostsynapticUpdateGroupMerged : public SynapseGroupMerged
{
public:
    PostsynapticUpdateGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                  const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDynamicsGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDynamicsGroupMerged : public SynapseGroupMerged
{
public:
    SynapseDynamicsGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                               const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDenseInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDenseInitGroupMerged : public SynapseGroupMerged
{
public:
    SynapseDenseInitGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseSparseInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseSparseInitGroupMerged : public SynapseGroupMerged
{
public:
    SynapseSparseInitGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                 const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};


// ----------------------------------------------------------------------------
// SynapseConnectivityInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseConnectivityInitGroupMerged : public SynapseGroupMerged
{
public:
    SynapseConnectivityInitGroupMerged(size_t index, const std::string &name, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                       const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    :   SynapseGroupMerged(index, name, precision, timePrecision, backend, groups)
    {}

    void generateRunner(const BackendBase &backend, CodeStream &definitionsInternal,
                        CodeStream &definitionsInternalFunc, CodeStream &definitionsInternalVar,
                        CodeStream &runnerVarDecl, CodeStream &runnerMergedStructAlloc) const
    {
        generateRunnerBase(backend, definitionsInternal, definitionsInternalFunc, definitionsInternalVar,
                           runnerVarDecl, runnerMergedStructAlloc);
    }
};
}   // namespace CodeGenerator
