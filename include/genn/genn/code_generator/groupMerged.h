#pragma once

// Standard includes
#include <functional>
#include <vector>

// GeNN includes
#include "gennExport.h"
#include "currentSourceInternal.h"
#include "neuronGroupInternal.h"
#include "synapseGroupInternal.h"

// GeNN code generator includes
#include "code_generator/codeGenUtils.h"
#include "code_generator/codeStream.h"

// Forward declarations
namespace CodeGenerator
{
class ModelSpecMerged;
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
    // Typedefines
    //------------------------------------------------------------------------
    typedef G GroupInternal;

    GroupMerged(size_t index, const std::string &prefix, std::vector<std::reference_wrapper<const GroupInternal>> groups)
        : m_Index(index), m_Prefix(prefix), m_Groups(std::move(groups))
    {}

    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    size_t getIndex() const { return m_Index; }

    const std::string &getPrefix() const { return m_Prefix; }

    //! Get 'archetype' neuron group - it's properties represent those of all other merged neuron groups
    const GroupInternal &getArchetype() const { return m_Groups.front().get(); }

    //! Gets access to underlying vector of neuron groups which have been merged
    const std::vector<std::reference_wrapper<const GroupInternal>> &getGroups() const { return m_Groups; }

    //! Generate structures for this merged group
    void generate(CodeGenerator::CodeStream &definitionsInternal, CodeGenerator::CodeStream &definitionsInternalFunc,
                  CodeGenerator::CodeStream &runnerVarDecl, CodeGenerator::CodeStream &runnerVarAlloc,
                  CodeGenerator::MergedEGPMap &mergedEGPs) const
    {
        // Write struct declation to top of definitions internal
        definitionsInternal << "struct Merged" << getPrefix() << "Group" << getIndex() << std::endl;
        {
            CodeGenerator::CodeStream::Scope b(definitionsInternal);
            for(const auto &f : m_Fields) {
                definitionsInternal << std::get<0>(f) << " " << std::get<1>(f) << ";" << std::endl;

                // If this field is for a pointer EGP, also declare function to push it
                if(std::get<3>(f) == FieldType::PointerEGP) {
                    definitionsInternalFunc << "EXPORT_FUNC void pushMerged" << getPrefix() << getIndex() << std::get<1>(f) << "ToDevice";
                    definitionsInternalFunc << "(unsigned int idx, " << std::get<0>(f) << " value); " << std::endl;
                }
            }
            definitionsInternal << std::endl;
        }

        definitionsInternal << ";" << std::endl;

        // Declare array of these structs containing individual neuron group pointers etc
        runnerVarDecl << "Merged" << getPrefix() << "Group" << getIndex() << " merged" << getPrefix() << "Group" << getIndex();
        runnerVarDecl << "[" << getGroups().size() << "];" << std::endl;

        for(size_t groupIndex = 0; groupIndex < getGroups().size(); groupIndex++) {
            const auto &g = getGroups()[groupIndex];

            // Set all fields in array of structs
            runnerVarAlloc << "merged" << getPrefix() << "Group" << getIndex() << "[" << groupIndex << "] = {";
            for(const auto &f : m_Fields) {
                const std::string fieldInitVal = std::get<2>(f)(g, groupIndex);
                runnerVarAlloc << fieldInitVal << ", ";

                // If field is an EGP, add record to merged EGPS
                if(std::get<3>(f) != FieldType::Standard) {
                    mergedEGPs[fieldInitVal].emplace(
                        std::piecewise_construct,
                        std::forward_as_tuple(getPrefix()),
                        std::forward_as_tuple(getIndex(), groupIndex, std::get<0>(f), std::get<1>(f)));
                }
            }
            runnerVarAlloc << "};" << std::endl;
        }

        // Then generate call to function to copy local array to device
        runnerVarAlloc << "pushMerged" << getPrefix() << "Group" << getIndex() << "ToDevice";
        runnerVarAlloc << "(merged" << getPrefix() << "Group" << getIndex() << "); " << std::endl;

        // Finally add declaration to function to definitions internal
        definitionsInternalFunc << "EXPORT_FUNC void pushMerged" << getPrefix() << "Group" << getIndex() << "ToDevice";
        definitionsInternalFunc << "(const Merged" << getPrefix() << "Group" << getIndex() << " * group); " << std::endl;
    }

protected:
    //------------------------------------------------------------------------
    // Enumerations
    //------------------------------------------------------------------------
    enum class FieldType
    {
        Standard,
        ScalarEGP,
        PointerEGP,
    };

    //------------------------------------------------------------------------
    // Typedefines
    //------------------------------------------------------------------------
    typedef std::function<std::string(const G &, size_t)> GetFieldValueFunc;

    //------------------------------------------------------------------------
    // Protected methods
    //------------------------------------------------------------------------
    //! Helper to test whether parameter values are heterogeneous within merged group
    template<typename P>
    bool isParamValueHeterogeneous(size_t index, P getParamValuesFn) const
    {
        // Get value of parameter in archetype group
        const double archetypeValue = getParamValuesFn(getArchetype()).at(index);

        // Return true if any parameter values differ from the archetype value
        return std::any_of(getGroups().cbegin(), getGroups().cend(),
                           [archetypeValue, index, getParamValuesFn](const GroupInternal &g)
                           {
                               return (getParamValuesFn(g).at(index) != archetypeValue);
                           });
    }

    void addField(const std::string &type, const std::string &name, GetFieldValueFunc getFieldValue, FieldType fieldType = FieldType::Standard)
    {
        m_Fields.emplace_back(type, name, getFieldValue, fieldType);
    }

    void addPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name, [prefix](const G &g, size_t) { return prefix + g.getName(); });
    }

    void addVars(const std::vector<Models::Base::Var> &vars, const std::string &prefix)
    {
        for(const auto &v : vars) {
            addPointerField(v.type, v.name, prefix + v.name);
        }
    }

    void addEGPs(const std::vector<Snippet::Base::EGP> &egps)
    {
        for(const auto &e : egps) {
            addField(e.type, e.name,
                     [e](const G &g, size_t) { return e.name + g.getName(); },
                     Utils::isTypePointer(e.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
        }
    }

    template<typename P, typename H>
    void addHeterogeneousParams(const Snippet::Base::StringVec &paramNames,
                                P getParamValues, H isHeterogeneous)
    {
        // Loop through params
        for(size_t p = 0; p < paramNames.size(); p++) {
            // If parameters is heterogeneous
            if((this->*isHeterogeneous)(p)) {
                // Add field
                addField("scalar", paramNames[p],
                         [p, getParamValues](const G &g, size_t)
                         {
                             const auto &values = (g.*getParamValues)();
                             return Utils::writePreciseString(values.at(p));
                         });
            }
        }
    }

    template<typename P, typename H>
    void addHeterogeneousDerivedParams(const Snippet::Base::DerivedParamVec &derivedParams,
                                       P getDerivedParamValues, H isHeterogeneous)
    {
        // Loop through derived params
        for(size_t p = 0; p < derivedParams.size(); p++) {
            // If parameters isn't homogeneous
            if((this->*isHeterogeneous)(p)) {
                // Add field
                addField("scalar", derivedParams[p].name,
                         [p, getDerivedParamValues](const G &g, size_t)
                         {
                             const auto &values = (g.*getDerivedParamValues)();
                             return Utils::writePreciseString(values.at(p));
                         });
            }
        }
    }

    template<typename V, typename H>
    void addHeterogeneousVarInitParams(const Models::Base::VarVec &vars, V getVarInitialisers, H isHeterogeneous)
    {
        // Loop through weight update model variables
        const std::vector<Models::VarInit> &archetypeVarInitialisers = (getArchetype().*getVarInitialisers)();
        for(size_t v = 0; v < archetypeVarInitialisers.size(); v++) {
            // Loop through parameters
            const Models::VarInit &varInit = archetypeVarInitialisers[v];
            for(size_t p = 0; p < varInit.getParams().size(); p++) {
                if((this->*isHeterogeneous)(v, p)) {
                    addField("scalar", varInit.getSnippet()->getParamNames()[p] + vars[v].name,
                             [p, v, getVarInitialisers](const typename G &ng, size_t)
                             {
                                 const auto &values = (ng.*getVarInitialisers)()[v].getParams();
                                 return Utils::writePreciseString(values.at(p));
                             });
                }
            }
        }
    }

    template<typename V, typename H>
    void addHeterogeneousVarInitDerivedParams(const Models::Base::VarVec &vars, V getVarInitialisers, H isHeterogeneous)
    {
        // Loop through weight update model variables
        const std::vector<Models::VarInit> &archetypeVarInitialisers = (getArchetype().*getVarInitialisers)();
        for(size_t v = 0; v < archetypeVarInitialisers.size(); v++) {
            // Loop through parameters
            const Models::VarInit &varInit = archetypeVarInitialisers[v];
            for(size_t d = 0; d < varInit.getDerivedParams().size(); d++) {
                if((this->*isHeterogeneous)(v, d)) {
                    addField("scalar", varInit.getSnippet()->getDerivedParams()[d].name + vars[v].name,
                             [d, v, getVarInitialisers](const typename G &ng, size_t)
                             {
                                 const auto &values = (ng.*getVarInitialisers)()[v].getDerivedParams();
                                 return Utils::writePreciseString(values.at(d));
                             });
                }
            }
        }
    }

private:
    //------------------------------------------------------------------------
    // Members
    //------------------------------------------------------------------------
    const size_t m_Index;
    const std::string m_Prefix;
    std::vector<std::reference_wrapper<const GroupInternal>> m_Groups;
    std::vector<std::tuple<std::string, std::string, GetFieldValueFunc, FieldType>> m_Fields;
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronGroupMerged : public GroupMerged<NeuronGroupInternal>
{
public:
    //------------------------------------------------------------------------
    // Public API
    //------------------------------------------------------------------------
    //! Get the expression to calculate the queue offset for accessing state of variables this timestep
    std::string getCurrentQueueOffset() const;

    //! Get the expression to calculate the queue offset for accessing state of variables in previous timestep
    std::string getPrevQueueOffset() const;

    //! Is the parameter implemented as a heterogeneous parameter?
    bool isParamHeterogeneous(size_t index) const;

    //! Is the derived parameter implemented as a heterogeneous parameter?
    bool isDerivedParamHeterogeneous(size_t index) const;

    //! Is the current source parameter implemented as a heterogeneous parameter?
    bool isCurrentSourceParamHeterogeneous(size_t childIndex, size_t paramIndex) const;

    //! Is the current source derived parameter implemented as a heterogeneous parameter?
    bool isCurrentSourceDerivedParamHeterogeneous(size_t childIndex, size_t paramIndex) const;

protected:
    NeuronGroupMerged(size_t index, const std::string &prefix, const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups,
                      bool init, const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend);

private:
    //------------------------------------------------------------------------
    // Private methods
    //------------------------------------------------------------------------
    template<typename T, typename G, typename C>
    void orderNeuronGroupChildren(const std::vector<T> &archetypeChildren,
                                  std::vector<std::vector<T>> &sortedGroupChildren,
                                  G getVectorFunc, C isCompatibleFunc) const
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

    template<typename T, typename G, typename C>
    void orderNeuronGroupChildren(std::vector<std::vector<T>> &sortedGroupChildren,
                                  G getVectorFunc, C isCompatibleFunc) const
    {
        const std::vector<T> &archetypeChildren = (getArchetype().*getVectorFunc)();
        orderNeuronGroupChildren(archetypeChildren, sortedGroupChildren, getVectorFunc, isCompatibleFunc);
    }

    template<typename T, typename G>
    bool isChildParamValueHeterogeneous(size_t childIndex, size_t paramIndex, const std::vector<std::vector<T>> &sortedGroupChildren,
                                        G getParamValuesFn) const
    {
        // Get value of archetype derived parameter
        const double firstValue = getParamValuesFn(sortedGroupChildren[0][childIndex]).at(paramIndex);

        // Loop through groups within merged group
        for(size_t i = 0; i < sortedGroupChildren.size(); i++) {
            const auto group = sortedGroupChildren[i][childIndex];
            if(getParamValuesFn(group).at(paramIndex) != firstValue) {
                return true;
            }
        }
        return false;
    }

    void addMergedInSynPointerField(const std::string &type, const std::string &name, size_t archetypeIndex, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name + std::to_string(archetypeIndex),
                 [prefix, archetypeIndex, this](const NeuronGroupInternal &, size_t groupIndex)
                 {
                     return prefix + m_SortedMergedInSyns.at(groupIndex).at(archetypeIndex).first->getPSModelTargetName();
                 });
    }

    void addCurrentSourcePointerField(const std::string &type, const std::string &name, size_t archetypeIndex, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name + std::to_string(archetypeIndex),
                 [prefix, archetypeIndex, this](const NeuronGroupInternal &, size_t groupIndex)
                 {
                     return prefix + m_SortedCurrentSources.at(groupIndex).at(archetypeIndex)->getName();
                 });
    }

    void addSynPointerField(const std::string &type, const std::string &name, size_t archetypeIndex, const std::string &prefix,
                            const std::vector<std::vector<SynapseGroupInternal *>> &sortedSyn)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name + std::to_string(archetypeIndex),
                 [prefix, &sortedSyn, archetypeIndex](const NeuronGroupInternal &, size_t groupIndex)
                 {
                     return prefix + sortedSyn.at(groupIndex).at(archetypeIndex)->getName();
                 });

    }

    //------------------------------------------------------------------------
    // Members
    //------------------------------------------------------------------------
    std::vector<std::vector<std::pair<SynapseGroupInternal *, std::vector<SynapseGroupInternal *>>>> m_SortedMergedInSyns;
    std::vector<std::vector<CurrentSourceInternal *>> m_SortedCurrentSources;
    std::vector<std::vector<SynapseGroupInternal *>> m_SortedInSynWithPostCode;
    std::vector<std::vector<SynapseGroupInternal *>> m_SortedOutSynWithPreCode;
};


//----------------------------------------------------------------------------
// CodeGenerator::NeuronUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronUpdateGroupMerged : public NeuronGroupMerged
{
public:
    NeuronUpdateGroupMerged(size_t index, std::vector<std::reference_wrapper<const NeuronGroupInternal>> groups,
                            const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   NeuronGroupMerged(index, "NeuronUpdate", groups, false, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronInitGroupMerged : public NeuronGroupMerged
{
public:
    NeuronInitGroupMerged(size_t index, std::vector<std::reference_wrapper<const NeuronGroupInternal>> groups,
                          const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   NeuronGroupMerged(index, "NeuronInit", groups, true, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::NeuronSpikeQueueUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT NeuronSpikeQueueUpdateGroupMerged : public GroupMerged<NeuronGroupInternal>
{
public:
    NeuronSpikeQueueUpdateGroupMerged(size_t index, std::vector<std::reference_wrapper<const NeuronGroupInternal>> groups,
                                      const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend);
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
    //! Get the expression to calculate the delay slot for accessing
    //! Presynaptic neuron state variables, taking into account axonal delay
    std::string getPresynapticAxonalDelaySlot() const;

    //! Get the expression to calculate the delay slot for accessing
    //! Postsynaptic neuron state variables, taking into account back propagation delay
    std::string getPostsynapticBackPropDelaySlot() const;

    std::string getDendriticDelayOffset(const std::string &offset = "") const;

    //! Is the weight update model variable initialization parameter implemented as a heterogeneous parameter?
    bool isWUVarInitParamHeterogeneous(size_t varIndex, size_t paramIndex) const;

    //! Is the weight update model variable initialization derived parameter implemented as a heterogeneous parameter?
    bool isWUVarInitDerivedParamHeterogeneous(size_t varIndex, size_t paramIndex) const;

protected:
    //------------------------------------------------------------------------
    // Enumerations
    //------------------------------------------------------------------------
    enum class Role
    {
        PresynapticUpdate,
        PostsynapticUpdate,
        SynapseDynamics,
        DenseInit,
        SparseInit,
    };

    SynapseGroupMerged(size_t index, const std::string &prefix, const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups,
                       Role role, const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend);

private:
    //------------------------------------------------------------------------
    // Private methods
    //------------------------------------------------------------------------
    void addPSPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getPSModelTargetName(); });
    }

    void addSrcPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getSrcNeuronGroup()->getName(); });
    }

    void addTrgPointerField(const std::string &type, const std::string &name, const std::string &prefix)
    {
        assert(!Utils::isTypePointer(type));
        addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getTrgNeuronGroup()->getName(); });
    }

    void addSrcEGPField(const Snippet::Base::EGP &egp)
    {
        addField(egp.type, egp.name + "Pre",
                 [egp](const SynapseGroupInternal &sg, size_t) { return egp.name + sg.getSrcNeuronGroup()->getName(); },
                 Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
    }

    void addTrgEGPField(const Snippet::Base::EGP &egp)
    {
        addField(egp.type, egp.name + "Post",
                 [egp](const SynapseGroupInternal &sg, size_t) { return egp.name + sg.getTrgNeuronGroup()->getName(); },
                 Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::PresynapticUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT PresynapticUpdateGroupMerged : public SynapseGroupMerged
{
public:
    PresynapticUpdateGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                 const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   SynapseGroupMerged(index, "PresynapticUpdate", groups, Role::PresynapticUpdate, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::PostsynapticUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT PostsynapticUpdateGroupMerged : public SynapseGroupMerged
{
public:
    PostsynapticUpdateGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                  const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   SynapseGroupMerged(index, "PostsynapticUpdate", groups, Role::PostsynapticUpdate, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDynamicsGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDynamicsGroupMerged : public SynapseGroupMerged
{
public:
    SynapseDynamicsGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                               const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   SynapseGroupMerged(index, "SynapseDynamics", groups, Role::SynapseDynamics, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDenseInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDenseInitGroupMerged : public SynapseGroupMerged
{
public:
    SynapseDenseInitGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   SynapseGroupMerged(index, "SynapseDenseInit", groups, Role::DenseInit, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseSparseInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseSparseInitGroupMerged : public SynapseGroupMerged
{
public:
    SynapseSparseInitGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                 const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
    :   SynapseGroupMerged(index, "SynapseSparseInit", groups, Role::SparseInit, modelSpec, backend)
    {
    }
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseConnectivityInitGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseConnectivityInitGroupMerged : public GroupMerged<SynapseGroupInternal>
{
public:
    SynapseConnectivityInitGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                       const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend);
};

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDendriticDelayUpdateGroupMerged
//----------------------------------------------------------------------------
class GENN_EXPORT SynapseDendriticDelayUpdateGroupMerged : public GroupMerged<SynapseGroupInternal>
{
public:
    SynapseDendriticDelayUpdateGroupMerged(size_t index, std::vector<std::reference_wrapper<const SynapseGroupInternal>> groups,
                                           const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend);
};
}   // namespace CodeGenerator
