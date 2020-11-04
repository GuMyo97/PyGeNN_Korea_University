#include "code_generator/groupMerged.h"

// PLOG includes
#include <plog/Log.h>

// GeNN includes
#include "modelSpecInternal.h"

// GeNN code generator includes
#include "code_generator/backendBase.h"
#include "code_generator/codeGenUtils.h"
#include "code_generator/codeStream.h"

//----------------------------------------------------------------------------
// CodeGenerator::NeuronSpikeQueueUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::NeuronSpikeQueueUpdateGroupMerged::name = "NeuronSpikeQueueUpdate";
//----------------------------------------------------------------------------
CodeGenerator::NeuronSpikeQueueUpdateGroupMerged::NeuronSpikeQueueUpdateGroupMerged(size_t index, const std::string &precision, const std::string&, const BackendBase &backend,
                                                                                    const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   GroupMerged<NeuronGroupInternal>(index, precision, backend, groups)
{
    if(getArchetype().isDelayRequired()) {
        addField("unsigned int", "numDelaySlots",
                 [](const NeuronGroupInternal &ng, size_t) { return std::to_string(ng.getNumDelaySlots()); });

        addPointerField("unsigned int", "spkQuePtr", backend.getScalarAddressPrefix() + "spkQuePtr");
    } 

    addPointerField("unsigned int", "spkCnt", backend.getDeviceVarPrefix() + "glbSpkCnt");

    if(getArchetype().isSpikeEventRequired()) {
        addPointerField("unsigned int", "spkCntEvnt", backend.getDeviceVarPrefix() + "glbSpkCntEvnt");
    }
}
//----------------------------------------------------------------------------
void CodeGenerator::NeuronSpikeQueueUpdateGroupMerged::genMergedGroupSpikeCountReset(CodeStream &os) const
{
    if(getArchetype().isDelayRequired()) { // with delay
        if(getArchetype().isSpikeEventRequired()) {
            os << "group->spkCntEvnt[*group->spkQuePtr] = 0;" << std::endl;
        }
        if(getArchetype().isTrueSpikeRequired()) {
            os << "group->spkCnt[*group->spkQuePtr] = 0;" << std::endl;
        }
        else {
            os << "group->spkCnt[0] = 0;" << std::endl;
        }
    }
    else { // no delay
        if(getArchetype().isSpikeEventRequired()) {
            os << "group->spkCntEvnt[0] = 0;" << std::endl;
        }
        os << "group->spkCnt[0] = 0;" << std::endl;
    }
}

//----------------------------------------------------------------------------
// CodeGenerator::NeuronGroupMergedBase
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getNumNeurons()
{
    return getValueField("unsigned int", "numNeurons",
                         [](const NeuronGroupInternal &ng, size_t) { return std::to_string(ng.getNumNeurons()); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikeCount()
{
    return getPointerField("unsigned int", "spkCnt", getBackend().getDeviceVarPrefix() + "glbSpkCnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikes()
{
    return getPointerField("unsigned int", "spk", getBackend().getDeviceVarPrefix() + "glbSpk");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikeEventCount()
{
    return getPointerField("unsigned int", "spkCntEvnt", getBackend().getDeviceVarPrefix() + "glbSpkCntEvnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikeEvents()
{
    return getPointerField("unsigned int", "spkEvnt", getBackend().getDeviceVarPrefix() + "glbSpkEvnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikeQueuePointer()
{
    return getPointerField("unsigned int", "spkQuePtr", getBackend().getScalarAddressPrefix() + "spkQuePtr");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSpikeTimes()
{
    return getPointerField(m_TimePrecision, "sT", getBackend().getDeviceVarPrefix() + "sT");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getSimRNG()
{
    return getPointerField(getBackend().getMergedGroupSimRNGType(), "rng", getBackend().getDeviceVarPrefix() + "rng");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getCurrentSourceVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    addField(var.type + "*", var.name + "CS" + std::to_string(childIndex),
             [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
             {
                 return getBackend().getDeviceVarPrefix() + var.name + m_SortedCurrentSources.at(groupIndex).at(childIndex)->getName();
             });

    return "group->" + var.name + "CS" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getPSMVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    addField(var.type + "*", var.name + "InSyn" + std::to_string(childIndex),
             [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
             {
                 return getBackend().getDeviceVarPrefix() + var.name + m_SortedMergedInSyns.at(groupIndex).at(childIndex).first->getPSModelTargetName();
             });

    return "group->" + var.name + "InSyn" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getInSynVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    addField(var.type + "*", var.name + "WUPost" + std::to_string(childIndex),
             [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
             {
                 return getBackend().getDeviceVarPrefix() + var.name + m_SortedInSynWithPostVars.at(groupIndex).at(childIndex)->getName();
             });

    return "group->" + var.name + "WUPost" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getOutSynVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    addField(var.type + "*", var.name + "WUPre" + std::to_string(childIndex),
             [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
             {
                 return getBackend().getDeviceVarPrefix() + var.name + m_SortedOutSynWithPreVars.at(groupIndex).at(childIndex)->getName();
             });

    return "group->" + var.name + "WUPre" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
bool CodeGenerator::NeuronGroupMergedBase::isPSMGlobalVarHeterogeneous(size_t childIndex, size_t varIndex) const
{
    // If synapse group doesn't have individual PSM variables to start with, return false
    const auto *sg = getArchetype().getMergedInSyn().at(childIndex).first;
    if(sg->getMatrixType() & SynapseMatrixWeight::INDIVIDUAL_PSM) {
        return false;
    }
    else {
        const auto *psm = getArchetype().getMergedInSyn().at(childIndex).first->getPSModel();
        const std::string varName = psm->getVars().at(varIndex).name;
        return isChildParamValueHeterogeneous({psm->getApplyInputCode(), psm->getDecayCode()}, varName, childIndex, varIndex, m_SortedMergedInSyns,
                                              [](const std::pair<SynapseGroupInternal *, std::vector<SynapseGroupInternal *>> &inSyn)
                                              {
                                                  return inSyn.first->getPSConstInitVals();
                                              });
    }
}
//----------------------------------------------------------------------------
CodeGenerator::NeuronGroupMergedBase::NeuronGroupMergedBase(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                                            bool init, const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   CodeGenerator::GroupMerged<NeuronGroupInternal>(index, precision, backend, groups), m_TimePrecision(timePrecision)
{
    // Build vector of vectors containing each child group's merged in syns, ordered to match those of the archetype group
    orderNeuronGroupChildren(m_SortedMergedInSyns, &NeuronGroupInternal::getMergedInSyn,
                             [init](const std::pair<SynapseGroupInternal *, std::vector<SynapseGroupInternal *>> &a,
                                    const std::pair<SynapseGroupInternal *, std::vector<SynapseGroupInternal *>> &b)
                             {
                                 return init ? a.first->canPSInitBeMerged(*b.first) : a.first->canPSBeMerged(*b.first);
                             });

    // Build vector of vectors containing each child group's current sources, ordered to match those of the archetype group
    orderNeuronGroupChildren(m_SortedCurrentSources, &NeuronGroupInternal::getCurrentSources,
                             [init](const CurrentSourceInternal *a, const CurrentSourceInternal *b)
                             {
                                 return init ? a->canInitBeMerged(*b) : a->canBeMerged(*b);
                             });

    // Build vector of vectors containing each child group's incoming 
    // synapse groups, ordered to match those of the archetype group
    orderNeuronGroupChildren(getArchetype().getInSynWithPostVars(), m_SortedInSynWithPostVars, &NeuronGroupInternal::getInSynWithPostVars,
                             [](const SynapseGroupInternal *a, const SynapseGroupInternal *b) { return a->canWUPostInitBeMerged(*b); });

    // Build vector of vectors containing each child group's outgoing 
    // synapse groups, ordered to match those of the archetype group
    orderNeuronGroupChildren(getArchetype().getOutSynWithPreVars(), m_SortedOutSynWithPreVars, &NeuronGroupInternal::getOutSynWithPreVars,
                             [](const SynapseGroupInternal *a, const SynapseGroupInternal *b){ return a->canWUPreInitBeMerged(*b); });


    // Loop through merged synaptic inputs in archetypical neuron group
    for(size_t i = 0; i < getArchetype().getMergedInSyn().size(); i++) {
        const SynapseGroupInternal *sg = getArchetype().getMergedInSyn()[i].first;

        // Add pointer to insyn
        addMergedInSynPointerField(precision, "inSynInSyn", i, backend.getDeviceVarPrefix() + "inSyn");

        // Add pointer to dendritic delay buffer if required
        if(sg->isDendriticDelayRequired()) {
            addMergedInSynPointerField(precision, "denDelayInSyn", i, backend.getDeviceVarPrefix() + "denDelay");
            addMergedInSynPointerField("unsigned int", "denDelayPtrInSyn", i, backend.getScalarAddressPrefix() + "denDelayPtr");
        }

        // Loop through variables
        const auto vars = sg->getPSModel()->getVars();
        for(size_t v = 0; v < vars.size(); v++) {
            // Otherwise, if postsynaptic model variables are global and we're updating 
            // **NOTE** global variable values aren't useful during initialization
            if(!init) {
                // If GLOBALG variable should be implemented heterogeneously, add value
                if(isPSMGlobalVarHeterogeneous(i, v)) {
                    addScalarField(vars[v].name + "InSyn" + std::to_string(i),
                                   [this, i, v](const NeuronGroupInternal &, size_t groupIndex)
                                   {
                                       const double val = m_SortedMergedInSyns.at(groupIndex).at(i).first->getPSConstInitVals().at(v);
                                       return Utils::writePreciseString(val);
                                   });
                }
            }
        }
    }

    // Loop through neuron groups
    std::vector<std::vector<SynapseGroupInternal *>> eventThresholdSGs;
    for(const auto &g : getGroups()) {
        // Reserve vector for this group's children
        eventThresholdSGs.emplace_back();

        // Add synapse groups 
        for(const auto &s : g.get().getSpikeEventCondition()) {
            if(s.egpInThresholdCode) {
                eventThresholdSGs.back().push_back(s.synapseGroup);
            }
        }
    }

    // Loop through all spike event conditions
    size_t i = 0;
    for(const auto &s : getArchetype().getSpikeEventCondition()) {
        // If threshold condition references any EGPs
        if(s.egpInThresholdCode) {
            // Loop through all EGPs in synapse group and add to merged group
            // **TODO** should only be ones referenced
            const auto sgEGPs = s.synapseGroup->getWUModel()->getExtraGlobalParams();
            for(const auto &egp : sgEGPs) {
                const bool isPointer = Utils::isTypePointer(egp.type);
                const std::string prefix = isPointer ? backend.getDeviceVarPrefix() : "";
                addField(egp.type, egp.name + "EventThresh" + std::to_string(i),
                         [eventThresholdSGs, prefix, egp, i](const NeuronGroupInternal &, size_t groupIndex)
                         {
                             return prefix + egp.name + eventThresholdSGs.at(groupIndex).at(i)->getName();
                         },
                         Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
            }
            i++;
        }
    }
}
//----------------------------------------------------------------------------
void CodeGenerator::NeuronGroupMergedBase::addMergedInSynPointerField(const std::string &type, const std::string &name, 
                                                                      size_t archetypeIndex, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    addField(type + "*", name + std::to_string(archetypeIndex),
             [prefix, archetypeIndex, this](const NeuronGroupInternal &, size_t groupIndex)
             {
                 return prefix + m_SortedMergedInSyns.at(groupIndex).at(archetypeIndex).first->getPSModelTargetName();
             });
}

//----------------------------------------------------------------------------
// CodeGenerator::NeuronUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::NeuronUpdateGroupMerged::name = "NeuronUpdate";
//----------------------------------------------------------------------------
CodeGenerator::NeuronUpdateGroupMerged::NeuronUpdateGroupMerged(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                                                const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   NeuronGroupMergedBase(index, precision, timePrecision, backend, false, groups)
{
    if(getArchetype().isSpikeRecordingEnabled()) {
        // Add field for spike recording
        // **YUCK** this mechanism needs to be renamed from PointerEGP to RuntimeAlloc
        addField("uint32_t*", "recordSpk",
                 [&backend](const NeuronGroupInternal &ng, size_t) 
                 { 
                     return backend.getDeviceVarPrefix() + "recordSpk" + ng.getName(); 
                 },
                 FieldType::PointerEGP);
    }

    if(getArchetype().isSpikeEventRecordingEnabled()) {
        // Add field for spike event recording
        // **YUCK** this mechanism needs to be renamed from PointerEGP to RuntimeAlloc
        addField("uint32_t*", "recordSpkEvent",
                 [&backend](const NeuronGroupInternal &ng, size_t)
                 {
                     return backend.getDeviceVarPrefix() + "recordSpkEvent" + ng.getName(); 
                 },
                 FieldType::PointerEGP);
    }

}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getCurrentQueueOffset()
{
    assert(getArchetype().isDelayRequired());
    return "(*" + getSpikeQueuePointer() + " * " + getNumNeurons() + ")";
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getPrevQueueOffset()
{
    assert(getArchetype().isDelayRequired());
    return "(((*" + getSpikeQueuePointer() + " + " + std::to_string(getArchetype().getNumDelaySlots() - 1) + ") % " + std::to_string(getArchetype().getNumDelaySlots()) + ") * " + getNumNeurons() + ")";
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getNeuronParam(size_t index)
{
    return getParamField(index, getArchetype().getNeuronModel()->getParamNames(), "",
                         [](const NeuronGroupInternal &ng) { return ng.getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getNeuronDerivedParam(size_t index)
{
    return getDerivedParamField(index, getArchetype().getNeuronModel()->getDerivedParams(), "",
                                [](const NeuronGroupInternal &ng) { return ng.getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getCurrentSourceParam(size_t childIndex, size_t paramIndex)
{
    const auto *csm = getArchetype().getCurrentSources().at(childIndex)->getCurrentSourceModel();
    return getChildParamField(childIndex, paramIndex, csm->getParamNames(), 
                              "CS" + std::to_string(childIndex), getSortedCurrentSources(),
                              [](const CurrentSourceInternal *cs) { return cs->getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getCurrentSourceDerivedParam(size_t childIndex, size_t paramIndex)
{
    const auto *csm = getArchetype().getCurrentSources().at(childIndex)->getCurrentSourceModel();
    return getChildDerivedParamField(childIndex, paramIndex, csm->getDerivedParams(), 
                                     "CS" + std::to_string(childIndex), getSortedCurrentSources(),
                                     [](const CurrentSourceInternal *cs) { return cs->getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getPSMParam(size_t childIndex, size_t paramIndex)
{
    const auto *psm = getArchetype().getMergedInSyn().at(childIndex).first->getPSModel();
    return getChildParamField(childIndex, paramIndex, psm->getParamNames(), 
                              "InSyn" + std::to_string(childIndex), getSortedMergedInSyns(),
                              [](const std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>> &inSyn) 
                              {
                                  return inSyn.first->getPSParams(); 
                              });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getPSMDerivedParam(size_t childIndex, size_t paramIndex)
{
    const auto *psm = getArchetype().getMergedInSyn().at(childIndex).first->getPSModel();
    return getChildDerivedParamField(childIndex, paramIndex, psm->getDerivedParams(), 
                                     "InSyn" + std::to_string(childIndex), getSortedMergedInSyns(),
                                     [](const std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>> &inSyn) 
                                     { 
                                         return inSyn.first->getPSDerivedParams(); 
                                     });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getInSynParam(size_t childIndex, size_t paramIndex)
{
    const auto *wum = getArchetype().getInSynWithPostVars().at(childIndex)->getWUModel();
    return getChildParamField(childIndex, paramIndex, wum->getParamNames(), 
                              "WUPost" + std::to_string(childIndex), getSortedInSynWithPostVars(),
                              [](const SynapseGroupInternal *s) { return s->getWUParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getInSynDerivedParam(size_t childIndex, size_t paramIndex)
{
    const auto *wum = getArchetype().getInSynWithPostVars().at(childIndex)->getWUModel();
    return getChildDerivedParamField(childIndex, paramIndex, wum->getDerivedParams(), 
                                     "WUPost" + std::to_string(childIndex), getSortedInSynWithPostVars(),
                                     [](const SynapseGroupInternal *s) { return s->getWUDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getOutSynParam(size_t childIndex, size_t paramIndex)
{
    const auto *wum = getArchetype().getOutSynWithPreVars().at(childIndex)->getWUModel();
    return getChildParamField(childIndex, paramIndex, wum->getParamNames(), 
                              "WUPre" + std::to_string(childIndex), getSortedOutSynWithPreVars(),
                              [](const SynapseGroupInternal *s) { return s->getWUParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getOutSynDerivedParam(size_t childIndex, size_t paramIndex)
{
    const auto *wum = getArchetype().getOutSynWithPreVars().at(childIndex)->getWUModel();
    return getChildDerivedParamField(childIndex, paramIndex, wum->getDerivedParams(), 
                                     "WUPre" + std::to_string(childIndex), getSortedOutSynWithPreVars(),
                                     [](const SynapseGroupInternal *s) { return s->getWUDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getCurrentSourceEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    addField(egp.type, egp.name + "CS" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedCurrentSources().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + "CS" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getPSMEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    addField(egp.type, egp.name + "InSyn" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedMergedInSyns().at(groupIndex).at(childIndex).first->getPSModelTargetName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
    
    return "group->" + egp.name + "InSyn" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getInSynEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    addField(egp.type, egp.name + "WUPost" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedInSynWithPostVars().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + "WUPost" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getOutSynEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    addField(egp.type, egp.name + "WUPre" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedOutSynWithPreVars().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + "WUPre" + std::to_string(childIndex);
}

//----------------------------------------------------------------------------
// CodeGenerator::NeuronInitGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::NeuronInitGroupMerged::name = "NeuronInit";
//----------------------------------------------------------------------------
CodeGenerator::NeuronInitGroupMerged::NeuronInitGroupMerged(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                                            const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   NeuronGroupMergedBase(index, precision, timePrecision, backend, true, groups)
{
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getVarInitParam(size_t varIndex, size_t paramIndex)
{
    const auto paramNames = getArchetype().getVarInitialisers().at(varIndex).getSnippet()->getParamNames();
    return getParamField(paramIndex, paramNames, getArchetype().getNeuronModel()->getVars().at(varIndex).name,
                         [varIndex](const NeuronGroupInternal &ng) { return ng.getVarInitialisers().at(varIndex).getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getVarInitDerivedParam(size_t varIndex, size_t paramIndex)
{
    const auto derivedParams = getArchetype().getVarInitialisers().at(varIndex).getSnippet()->getDerivedParams();
    return getDerivedParamField(paramIndex, derivedParams, getArchetype().getNeuronModel()->getVars().at(varIndex).name,
                                [varIndex](const NeuronGroupInternal &ng) { return ng.getVarInitialisers().at(varIndex).getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getVarInitEGP(size_t varIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    const std::string varName = getArchetype().getNeuronModel()->getVars().at(varIndex).name;
    addField(egp.type, egp.name + varName,
             [egp, varPrefix, varName, this](const NeuronGroupInternal &g, size_t)
             {
                 return varPrefix + egp.name + varName + g.getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + varName;
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getCurrentSourceVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getCurrentSources().at(childIndex)->getVarInitialisers().at(varIndex).getSnippet();
    return getChildParamField(childIndex, paramIndex, varInitSnippet->getParamNames(), 
                              "CS" + std::to_string(childIndex), getSortedCurrentSources(),
                              [varIndex](const CurrentSourceInternal *cs){ return cs->getVarInitialisers().at(varIndex).getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getCurrentSourceVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getCurrentSources().at(childIndex)->getVarInitialisers().at(varIndex).getSnippet();
    return getChildDerivedParamField(childIndex, paramIndex, varInitSnippet->getDerivedParams(), 
                                     "CS" + std::to_string(childIndex), getSortedCurrentSources(),
                                     [varIndex](const CurrentSourceInternal *cs) { return cs->getVarInitialisers().at(varIndex).getDerivedParams(); });
}
//---------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getCurrentSourceVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp)
{
    // **TODO** turn into helper
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    const std::string varName = getArchetype().getCurrentSources().at(childIndex)->getCurrentSourceModel()->getVars().at(varIndex).name;
    addField(egp.type, egp.name + varName + "CS" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + varName + getSortedCurrentSources().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + varName + "CS" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getPSMVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getMergedInSyn().at(childIndex).first->getPSVarInitialisers().at(varIndex).getSnippet();
    return getChildParamField(childIndex, paramIndex, varInitSnippet->getParamNames(), "InSyn" + std::to_string(childIndex), getSortedMergedInSyns(),
                              [varIndex](const std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>> &inSyn) 
                              {
                                  return inSyn.first->getPSVarInitialisers().at(varIndex).getParams();
                              });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getPSMVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getMergedInSyn().at(childIndex).first->getPSVarInitialisers().at(varIndex).getSnippet();
    return getChildDerivedParamField(childIndex, paramIndex, varInitSnippet->getDerivedParams(), "InSyn" + std::to_string(childIndex), getSortedMergedInSyns(),
                                     [varIndex](const std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>> &inSyn) 
                                     {
                                         return inSyn.first->getPSVarInitialisers().at(varIndex).getDerivedParams();
                                     });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getPSMVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp)
{
    // **TODO** turn into helper
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    const std::string varName = getArchetype().getMergedInSyn().at(childIndex).first->getPSModel()->getVars().at(varIndex).name;
    addField(egp.type, egp.name + varName + "InSyn" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + varName + getSortedMergedInSyns().at(groupIndex).at(childIndex).first->getPSModelTargetName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + varName + "InSyn" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getInSynPostVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getInSynWithPostVars().at(childIndex)->getWUPostVarInitialisers().at(varIndex).getSnippet();
    return getChildParamField(childIndex, paramIndex, varInitSnippet->getParamNames(), 
                              "WUPost" + std::to_string(childIndex), getSortedInSynWithPostVars(),
                              [varIndex](const SynapseGroupInternal *s){ return s->getWUPostVarInitialisers().at(varIndex).getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getInSynPostVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getInSynWithPostVars().at(childIndex)->getWUPostVarInitialisers().at(varIndex).getSnippet();
    return getChildDerivedParamField(childIndex, paramIndex, varInitSnippet->getDerivedParams(), 
                                     "WUPost" + std::to_string(childIndex), getSortedInSynWithPostVars(),
                                     [varIndex](const SynapseGroupInternal *s) { return s->getWUPostVarInitialisers().at(varIndex).getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getInSynPostVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp)
{
    // **TODO** turn into helper
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    const std::string varName = getArchetype().getInSynWithPostVars().at(childIndex)->getWUModel()->getPostVars().at(varIndex).name;
    addField(egp.type, egp.name + varName + "WUPost" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + varName + getSortedInSynWithPostVars().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + varName + "WUPost" + std::to_string(childIndex);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getOutSynPreVarInitParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getOutSynWithPreVars().at(childIndex)->getWUPreVarInitialisers().at(varIndex).getSnippet();
    return getChildParamField(childIndex, paramIndex, varInitSnippet->getParamNames(), 
                              "WUPre" + std::to_string(childIndex), getSortedOutSynWithPreVars(),
                              [varIndex](const SynapseGroupInternal *s){ return s->getWUPreVarInitialisers().at(varIndex).getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getOutSynPreVarInitDerivedParam(size_t childIndex, size_t varIndex, size_t paramIndex)
{
    const auto *varInitSnippet = getArchetype().getOutSynWithPreVars().at(childIndex)->getWUPreVarInitialisers().at(varIndex).getSnippet();
    return getChildDerivedParamField(childIndex, paramIndex, varInitSnippet->getDerivedParams(), 
                                     "WUPre" + std::to_string(childIndex), getSortedOutSynWithPreVars(),
                                     [varIndex](const SynapseGroupInternal *s) { return s->getWUPreVarInitialisers().at(varIndex).getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronInitGroupMerged::getOutSynPreVarInitEGP(size_t childIndex, size_t varIndex, const Models::Base::EGP &egp)
{
    // **TODO** turn into helper
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    const std::string varName = getArchetype().getOutSynWithPreVars().at(childIndex)->getWUModel()->getPreVars().at(varIndex).name;
    addField(egp.type, egp.name + varName + "WUPre" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + varName + getSortedOutSynWithPreVars().at(groupIndex).at(childIndex)->getName();
             },
             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);

    return "group->" + egp.name + varName + "WUPre" + std::to_string(childIndex);
}

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDendriticDelayUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseDendriticDelayUpdateGroupMerged::name = "SynapseDendriticDelayUpdate";
//----------------------------------------------------------------------------
CodeGenerator::SynapseDendriticDelayUpdateGroupMerged::SynapseDendriticDelayUpdateGroupMerged(size_t index, const std::string &precision, const std::string &, const BackendBase &backend,
                                       const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    : GroupMerged<SynapseGroupInternal>(index, precision, backend, groups)
{
    addField("unsigned int*", "denDelayPtr", 
             [&backend](const SynapseGroupInternal &sg, size_t) 
             {
                 return backend.getScalarAddressPrefix() + "denDelayPtr" + sg.getPSModelTargetName(); 
             });
}

// ----------------------------------------------------------------------------
// CodeGenerator::SynapseConnectivityHostInitGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseConnectivityHostInitGroupMerged::name = "SynapseConnectivityHostInit";
//------------------------------------------------------------------------
CodeGenerator::SynapseConnectivityHostInitGroupMerged::SynapseConnectivityHostInitGroupMerged(size_t index, const std::string &precision, const std::string&, const BackendBase &backend,
                                                                                              const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
:   GroupMerged<SynapseGroupInternal>(index, precision, backend, groups)
{
    // **TODO** these could be generic
    addField("unsigned int", "numSrcNeurons",
             [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getSrcNeuronGroup()->getNumNeurons()); });
    addField("unsigned int", "numTrgNeurons",
             [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getTrgNeuronGroup()->getNumNeurons()); });
    addField("unsigned int", "rowStride",
             [&backend](const SynapseGroupInternal &sg, size_t) { return std::to_string(backend.getSynapticMatrixRowStride(sg)); });

    // Add heterogeneous connectivity initialiser model parameters
    addHeterogeneousParams<SynapseConnectivityHostInitGroupMerged>(
        getArchetype().getConnectivityInitialiser().getSnippet()->getParamNames(), "",
        [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getParams(); },
        &SynapseConnectivityHostInitGroupMerged::isConnectivityInitParamHeterogeneous);

    // Add heterogeneous connectivity initialiser derived parameters
    addHeterogeneousDerivedParams<SynapseConnectivityHostInitGroupMerged>(
        getArchetype().getConnectivityInitialiser().getSnippet()->getDerivedParams(), "",
        [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getDerivedParams(); },
        &SynapseConnectivityHostInitGroupMerged::isConnectivityInitDerivedParamHeterogeneous);

    // Add EGP pointers to struct for both host and device EGPs if they are seperate
    const auto egps = getArchetype().getConnectivityInitialiser().getSnippet()->getExtraGlobalParams();
    for(const auto &e : egps) {
        addField(e.type + "*", e.name,
                 [e](const SynapseGroupInternal &g, size_t) { return "&" + e.name + g.getName(); },
                 FieldType::Host);

        if(!backend.getDeviceVarPrefix().empty()) {
            addField(e.type + "*", backend.getDeviceVarPrefix() + e.name,
                     [e, &backend](const SynapseGroupInternal &g, size_t)
                     {
                         return "&" + backend.getDeviceVarPrefix() + e.name + g.getName();
                     });
        }
        if(!backend.getHostVarPrefix().empty()) {
            addField(e.type + "*", backend.getHostVarPrefix() + e.name,
                     [e, &backend](const SynapseGroupInternal &g, size_t)
                     {
                         return "&" + backend.getHostVarPrefix() + e.name + g.getName();
                     });
        }
    }
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseConnectivityHostInitGroupMerged::isConnectivityInitParamHeterogeneous(size_t paramIndex) const
{
    // If parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *connectInitSnippet = getArchetype().getConnectivityInitialiser().getSnippet();
    const std::string paramName = connectInitSnippet->getParamNames().at(paramIndex);
    return isParamValueHeterogeneous({connectInitSnippet->getHostInitCode()}, paramName, paramIndex,
                                     [](const SynapseGroupInternal &sg)
                                     {
                                         return sg.getConnectivityInitialiser().getParams();
                                     });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseConnectivityHostInitGroupMerged::isConnectivityInitDerivedParamHeterogeneous(size_t paramIndex) const
{
    // If parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *connectInitSnippet = getArchetype().getConnectivityInitialiser().getSnippet();
    const std::string paramName = connectInitSnippet->getDerivedParams().at(paramIndex).name;
    return isParamValueHeterogeneous({connectInitSnippet->getHostInitCode()}, paramName, paramIndex,
                                     [](const SynapseGroupInternal &sg)
                                     {
                                         return sg.getConnectivityInitialiser().getDerivedParams();
                                     });
}


//----------------------------------------------------------------------------
// CodeGenerator::SynapseGroupMergedBase
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getPresynapticAxonalDelaySlot() const
{
    assert(getArchetype().getSrcNeuronGroup()->isDelayRequired());

    const unsigned int numDelaySteps = getArchetype().getDelaySteps();
    if(numDelaySteps == 0) {
        return "(*group->srcSpkQuePtr)";
    }
    else {
        const unsigned int numSrcDelaySlots = getArchetype().getSrcNeuronGroup()->getNumDelaySlots();
        return "((*group->srcSpkQuePtr + " + std::to_string(numSrcDelaySlots - numDelaySteps) + ") % " + std::to_string(numSrcDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getPostsynapticBackPropDelaySlot() const
{
    assert(getArchetype().getTrgNeuronGroup()->isDelayRequired());

    const unsigned int numBackPropDelaySteps = getArchetype().getBackPropDelaySteps();
    if(numBackPropDelaySteps == 0) {
        return "(*group->trgSpkQuePtr)";
    }
    else {
        const unsigned int numTrgDelaySlots = getArchetype().getTrgNeuronGroup()->getNumDelaySlots();
        return "((*group->trgSpkQuePtr + " + std::to_string(numTrgDelaySlots - numBackPropDelaySteps) + ") % " + std::to_string(numTrgDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getDendriticDelayOffset(const std::string &offset) const
{
    assert(getArchetype().isDendriticDelayRequired());

    if(offset.empty()) {
        return "(*group->denDelayPtr * group->numTrgNeurons) + ";
    }
    else {
        return "(((*group->denDelayPtr + " + offset + ") % " + std::to_string(getArchetype().getMaxDendriticDelayTimesteps()) + ") * group->numTrgNeurons) + ";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNeuronParam(size_t index)
{
    return getParamField(index, getArchetype().getSrcNeuronGroup()->getNeuronModel()->getParamNames(), "Src",
                         [](const SynapseGroupInternal &sg) { return sg.getSrcNeuronGroup()->getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNeuronDerivedParam(size_t index)
{
    return getDerivedParamField(index, getArchetype().getSrcNeuronGroup()->getNeuronModel()->getDerivedParams(), "Src", 
                                [](const SynapseGroupInternal &sg) { return sg.getSrcNeuronGroup()->getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgNeuronParam(size_t index)
{
    return getParamField(index, getArchetype().getTrgNeuronGroup()->getNeuronModel()->getParamNames(), "Trg", 
                         [](const SynapseGroupInternal &sg) { return sg.getTrgNeuronGroup()->getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgNeuronDerivedParam(size_t index)
{
    return getDerivedParamField(index, getArchetype().getTrgNeuronGroup()->getNeuronModel()->getDerivedParams(), "Trg", 
                                [](const SynapseGroupInternal &sg) { return sg.getTrgNeuronGroup()->getDerivedParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isWUParamHeterogeneous(size_t paramIndex) const
{
    const auto *wum = getArchetype().getWUModel();
    const std::string paramName = wum->getParamNames().at(paramIndex);
    return isParamValueHeterogeneous({getArchetypeCode()}, paramName, paramIndex,
                                     [](const SynapseGroupInternal &sg) { return sg.getWUParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isWUDerivedParamHeterogeneous(size_t paramIndex) const
{
    const auto *wum = getArchetype().getWUModel();
    const std::string derivedParamName = wum->getDerivedParams().at(paramIndex).name;
    return isParamValueHeterogeneous({getArchetypeCode()}, derivedParamName, paramIndex,
                                     [](const SynapseGroupInternal &sg) { return sg.getWUDerivedParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isWUGlobalVarHeterogeneous(size_t varIndex) const
{
    // If synapse group has global WU variables
    if(getArchetype().getMatrixType() & SynapseMatrixWeight::GLOBAL) {
        const auto *wum = getArchetype().getWUModel();
        const std::string varName = wum->getVars().at(varIndex).name;
        return isParamValueHeterogeneous({getArchetypeCode()}, varName, varIndex,
                                         [](const SynapseGroupInternal &sg) { return sg.getWUConstInitVals(); });
    }
    // Otherwise, return false
    else {
        return false;
    }
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isWUVarInitParamHeterogeneous(size_t varIndex, size_t paramIndex) const
{
    // If parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *varInitSnippet = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet();
    const std::string paramName = varInitSnippet->getParamNames().at(paramIndex);
    return isParamValueHeterogeneous({varInitSnippet->getCode()}, paramName, paramIndex,
                                     [varIndex](const SynapseGroupInternal &sg)
                                     {
                                         return sg.getWUVarInitialisers().at(varIndex).getParams();
                                     });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isWUVarInitDerivedParamHeterogeneous(size_t varIndex, size_t paramIndex) const
{
    // If derived parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *varInitSnippet = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet();
    const std::string derivedParamName = varInitSnippet->getDerivedParams().at(paramIndex).name;
    return isParamValueHeterogeneous({varInitSnippet->getCode()}, derivedParamName, paramIndex,
                                     [varIndex](const SynapseGroupInternal &sg)
                                     {
                                         return sg.getWUVarInitialisers().at(varIndex).getDerivedParams();
                                     });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isConnectivityInitParamHeterogeneous(size_t paramIndex) const
{
    const auto *connectivityInitSnippet = getArchetype().getConnectivityInitialiser().getSnippet();
    const auto rowBuildStateVars = connectivityInitSnippet->getRowBuildStateVars();

    // Build list of code strings containing row build code and any row build state variable values
    std::vector<std::string> codeStrings{connectivityInitSnippet->getRowBuildCode()};
    std::transform(rowBuildStateVars.cbegin(), rowBuildStateVars.cend(), std::back_inserter(codeStrings),
                   [](const Snippet::Base::ParamVal &p) { return p.value; });

    const std::string paramName = connectivityInitSnippet->getParamNames().at(paramIndex);
    return isParamValueHeterogeneous(codeStrings, paramName, paramIndex,
                                     [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isConnectivityInitDerivedParamHeterogeneous(size_t paramIndex) const
{
    const auto *connectivityInitSnippet = getArchetype().getConnectivityInitialiser().getSnippet();
    const auto rowBuildStateVars = connectivityInitSnippet->getRowBuildStateVars();

    // Build list of code strings containing row build code and any row build state variable values
    std::vector<std::string> codeStrings{connectivityInitSnippet->getRowBuildCode()};
    std::transform(rowBuildStateVars.cbegin(), rowBuildStateVars.cend(), std::back_inserter(codeStrings),
                   [](const Snippet::Base::ParamVal &p) { return p.value; });

    const std::string derivedParamName = connectivityInitSnippet->getDerivedParams().at(paramIndex).name;
    return isParamValueHeterogeneous(codeStrings, derivedParamName, paramIndex,
                                     [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getDerivedParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMergedBase::isKernelSizeHeterogeneous(size_t dimensionIndex) const
{
    // Get size of this kernel dimension for archetype
    const unsigned archetypeValue = getArchetype().getKernelSize().at(dimensionIndex);

    // Return true if any of the other groups have a different value
    return std::any_of(getGroups().cbegin(), getGroups().cend(),
                       [archetypeValue, dimensionIndex](const GroupInternal &g)
                       {
                           return (g.getKernelSize().at(dimensionIndex) != archetypeValue);
                       });
}
//----------------------------------------------------------------------------
CodeGenerator::SynapseGroupMergedBase::SynapseGroupMergedBase(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                                              Role role, const std::string &archetypeCode, const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
:   GroupMerged<SynapseGroupInternal>(index, precision, backend, groups), m_ArchetypeCode(archetypeCode)
{
    const bool updateRole = ((role == Role::PresynapticUpdate)
                             || (role == Role::PostsynapticUpdate)
                             || (role == Role::SynapseDynamics));
    const WeightUpdateModels::Base *wum = getArchetype().getWUModel();

    addField("unsigned int", "rowStride",
             [&backend](const SynapseGroupInternal &sg, size_t) { return std::to_string(backend.getSynapticMatrixRowStride(sg)); });
    if(role == Role::PostsynapticUpdate || role == Role::SparseInit) {
        addField("unsigned int", "colStride",
                 [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getMaxSourceConnections()); });
    }

    addField("unsigned int", "numSrcNeurons",
             [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getSrcNeuronGroup()->getNumNeurons()); });
    addField("unsigned int", "numTrgNeurons",
             [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getTrgNeuronGroup()->getNumNeurons()); });

    // If this role is one where postsynaptic input can be provided
    if(role == Role::PresynapticUpdate || role == Role::SynapseDynamics) {
        if(getArchetype().isDendriticDelayRequired()) {
            addPSPointerField(precision, "denDelay", backend.getDeviceVarPrefix() + "denDelay");
            addPSPointerField("unsigned int", "denDelayPtr", backend.getScalarAddressPrefix() + "denDelayPtr");
        }
        else {
            addPSPointerField(precision, "inSyn", backend.getDeviceVarPrefix() + "inSyn");
        }
    }

    if(role == Role::PresynapticUpdate) {
        if(getArchetype().isTrueSpikeRequired()) {
            addSrcPointerField("unsigned int", "srcSpkCnt", backend.getDeviceVarPrefix() + "glbSpkCnt");
            addSrcPointerField("unsigned int", "srcSpk", backend.getDeviceVarPrefix() + "glbSpk");
        }

        if(getArchetype().isSpikeEventRequired()) {
            addSrcPointerField("unsigned int", "srcSpkCntEvnt", backend.getDeviceVarPrefix() + "glbSpkCntEvnt");
            addSrcPointerField("unsigned int", "srcSpkEvnt", backend.getDeviceVarPrefix() + "glbSpkEvnt");
        }
    }
    else if(role == Role::PostsynapticUpdate) {
        addTrgPointerField("unsigned int", "trgSpkCnt", backend.getDeviceVarPrefix() + "glbSpkCnt");
        addTrgPointerField("unsigned int", "trgSpk", backend.getDeviceVarPrefix() + "glbSpk");
    }

    // If this structure is used for updating rather than initializing
    if(updateRole) {
        // If presynaptic population has delay buffers
        if(getArchetype().getSrcNeuronGroup()->isDelayRequired()) {
            addSrcPointerField("unsigned int", "srcSpkQuePtr", backend.getScalarAddressPrefix() + "spkQuePtr");
        }

        // If postsynaptic population has delay buffers
        if(getArchetype().getTrgNeuronGroup()->isDelayRequired()) {
            addTrgPointerField("unsigned int", "trgSpkQuePtr", backend.getScalarAddressPrefix() + "spkQuePtr");
        }

        // Get correct code string
        const std::string code = getArchetypeCode();

        // Loop through variables in presynaptic neuron model
        const auto preVars = getArchetype().getSrcNeuronGroup()->getNeuronModel()->getVars();
        for(const auto &v : preVars) {
            // If variable is referenced in code string, add source pointer
            if(code.find("$(" + v.name + "_pre)") != std::string::npos) {
                addSrcPointerField(v.type, v.name + "Pre", backend.getDeviceVarPrefix() + v.name);
            }
        }

        // Loop through variables in postsynaptic neuron model
        const auto postVars = getArchetype().getTrgNeuronGroup()->getNeuronModel()->getVars();
        for(const auto &v : postVars) {
            // If variable is referenced in code string, add target pointer
            if(code.find("$(" + v.name + "_post)") != std::string::npos) {
                addTrgPointerField(v.type, v.name + "Post", backend.getDeviceVarPrefix() + v.name);
            }
        }

        // Loop through extra global parameters in presynaptic neuron model
        const auto preEGPs = getArchetype().getSrcNeuronGroup()->getNeuronModel()->getExtraGlobalParams();
        for(const auto &e : preEGPs) {
            if(code.find("$(" + e.name + "_pre)") != std::string::npos) {
                const bool isPointer = Utils::isTypePointer(e.type);
                const std::string prefix = isPointer ? backend.getDeviceVarPrefix() : "";
                addField(e.type, e.name + "Pre",
                         [e, prefix](const SynapseGroupInternal &sg, size_t) { return prefix + e.name + sg.getSrcNeuronGroup()->getName(); },
                         Utils::isTypePointer(e.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
            }
        }

        // Loop through extra global parameters in postsynaptic neuron model
        const auto postEGPs = getArchetype().getTrgNeuronGroup()->getNeuronModel()->getExtraGlobalParams();
        for(const auto &e : postEGPs) {
            if(code.find("$(" + e.name + "_post)") != std::string::npos) {
                const bool isPointer = Utils::isTypePointer(e.type);
                const std::string prefix = isPointer ? backend.getDeviceVarPrefix() : "";
                addField(e.type, e.name + "Post",
                         [e, prefix](const SynapseGroupInternal &sg, size_t) { return prefix + e.name + sg.getTrgNeuronGroup()->getName(); },
                         Utils::isTypePointer(e.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
            }
        }

        // Add spike times if required
        if(wum->isPreSpikeTimeRequired()) {
            addSrcPointerField(timePrecision, "sTPre", backend.getDeviceVarPrefix() + "sT");
        }
        if(wum->isPostSpikeTimeRequired()) {
            addTrgPointerField(timePrecision, "sTPost", backend.getDeviceVarPrefix() + "sT");
        }

        // Add heterogeneous weight update model parameters
        addHeterogeneousParams<SynapseGroupMergedBase>(
            wum->getParamNames(), "",
            [](const SynapseGroupInternal &sg) { return sg.getWUParams(); },
            &SynapseGroupMergedBase::isWUParamHeterogeneous);

        // Add heterogeneous weight update model derived parameters
        addHeterogeneousDerivedParams<SynapseGroupMergedBase>(
            wum->getDerivedParams(), "",
            [](const SynapseGroupInternal &sg) { return sg.getWUDerivedParams(); },
            &SynapseGroupMergedBase::isWUDerivedParamHeterogeneous);

        // Add pre and postsynaptic variables to struct
        addVars(wum->getPreVars(), backend.getDeviceVarPrefix());
        addVars(wum->getPostVars(), backend.getDeviceVarPrefix());

        // Add EGPs to struct
        addEGPs(wum->getExtraGlobalParams(), backend.getDeviceVarPrefix());
    }

    // Add pointers to connectivity data
    if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::SPARSE) {
        addWeightSharingPointerField("unsigned int", "rowLength", backend.getDeviceVarPrefix() + "rowLength");
        addWeightSharingPointerField(getArchetype().getSparseIndType(), "ind", backend.getDeviceVarPrefix() + "ind");

        // Add additional structure for postsynaptic access
        if(backend.isPostsynapticRemapRequired() && !wum->getLearnPostCode().empty()
           && (role == Role::PostsynapticUpdate || role == Role::SparseInit))
        {
            addWeightSharingPointerField("unsigned int", "colLength", backend.getDeviceVarPrefix() + "colLength");
            addWeightSharingPointerField("unsigned int", "remap", backend.getDeviceVarPrefix() + "remap");
        }

        // Add additional structure for synapse dynamics access
        if(backend.isSynRemapRequired() && !wum->getSynapseDynamicsCode().empty()
           && (role == Role::SynapseDynamics || role == Role::SparseInit))
        {
            addWeightSharingPointerField("unsigned int", "synRemap", backend.getDeviceVarPrefix() + "synRemap");
        }
    }
    else if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::BITMASK) {
        addWeightSharingPointerField("uint32_t", "gp", backend.getDeviceVarPrefix() + "gp");
    }

    // If we're updating a group with procedural connectivity or initialising connectivity
    if((getArchetype().getMatrixType() & SynapseMatrixConnectivity::PROCEDURAL) || (role == Role::ConnectivityInit)) {
        // Add heterogeneous connectivity initialiser model parameters
        addHeterogeneousParams<SynapseGroupMergedBase>(
            getArchetype().getConnectivityInitialiser().getSnippet()->getParamNames(), "",
            [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getParams(); },
            &SynapseGroupMergedBase::isConnectivityInitParamHeterogeneous);


        // Add heterogeneous connectivity initialiser derived parameters
        addHeterogeneousDerivedParams<SynapseGroupMergedBase>(
            getArchetype().getConnectivityInitialiser().getSnippet()->getDerivedParams(), "",
            [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getDerivedParams(); },
            &SynapseGroupMergedBase::isConnectivityInitDerivedParamHeterogeneous);

        addEGPs(getArchetype().getConnectivityInitialiser().getSnippet()->getExtraGlobalParams(),
                backend.getDeviceVarPrefix());
    }

    // If WU variables are global
    const auto vars = wum->getVars();
    const auto &varInit = getArchetype().getWUVarInitialisers();
    if(getArchetype().getMatrixType() & SynapseMatrixWeight::GLOBAL) {
        // If this is an update role
        // **NOTE **global variable values aren't useful during initialization
        if(updateRole) {
            for(size_t v = 0; v < vars.size(); v++) {
                // If variable should be implemented heterogeneously, add scalar field
                if(isWUGlobalVarHeterogeneous(v)) {
                    addScalarField(vars[v].name,
                                   [v](const SynapseGroupInternal &sg, size_t)
                                   {
                                       return Utils::writePreciseString(sg.getWUConstInitVals().at(v));
                                   });
                }
            }
        }
    }
    // Otherwise (weights are individual or procedural)
    else {
        const bool connectInitRole = (role == Role::ConnectivityInit);
        const bool proceduralWeights = (getArchetype().getMatrixType() & SynapseMatrixWeight::PROCEDURAL);
        const bool individualWeights = (getArchetype().getMatrixType() & SynapseMatrixWeight::INDIVIDUAL);

        // If synapse group has a kernel and we're either updating 
        // with procedural weights or initialising individual weights
        if(!getArchetype().getKernelSize().empty() && ((proceduralWeights && updateRole) || (connectInitRole && individualWeights))) {
            // Loop through kernel size dimensions
            for(size_t d = 0; d < getArchetype().getKernelSize().size(); d++) {
                // If this dimension has a heterogeneous size, add it to struct
                if(isKernelSizeHeterogeneous(d)) {
                    addField("unsigned int", "kernelSize" + std::to_string(d),
                             [d](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getKernelSize().at(d)); });
                }
            }
        }

        // If weights are procedural or we're initializing individual variables
        // **NOTE** some of these won't actually be required - could do this per-variable in loop over vars
        if((proceduralWeights && updateRole) || (!updateRole && individualWeights)) {
            // Add heterogeneous variable initialization parameters and derived parameters
            addHeterogeneousVarInitParams<SynapseGroupMergedBase>(
                wum->getVars(), &SynapseGroupInternal::getWUVarInitialisers,
                &SynapseGroupMergedBase::isWUVarInitParamHeterogeneous);

            addHeterogeneousVarInitDerivedParams<SynapseGroupMergedBase>(
                wum->getVars(), &SynapseGroupInternal::getWUVarInitialisers,
                &SynapseGroupMergedBase::isWUVarInitDerivedParamHeterogeneous);
        }

        // Loop through variables
        for(size_t v = 0; v < vars.size(); v++) {
            // Variable initialisation is required if we're performing connectivity init and var init snippet requires a kernel or
            // We're performing some other sort of initialisation, the snippet DOESN'T require a kernel but has SOME code
            const auto var = vars[v];
            const auto *snippet = varInit.at(v).getSnippet();
            const bool varInitRequired = ((connectInitRole && snippet->requiresKernel()) 
                                          || (!updateRole && !snippet->requiresKernel() && !snippet->getCode().empty()));

            // If we're performing an update with individual weights; or this variable should be initialised
            if((updateRole && individualWeights) || varInitRequired) {
                addWeightSharingPointerField(var.type, var.name, backend.getDeviceVarPrefix() + var.name);
            }

            // If we're performing a procedural update or this variable should be initialised, add any var init EGPs to structure
            if((proceduralWeights && updateRole) || varInitRequired) {
                const auto egps = snippet->getExtraGlobalParams();
                for(const auto &e : egps) {
                    const bool isPointer = Utils::isTypePointer(e.type);
                    const std::string prefix = isPointer ? backend.getDeviceVarPrefix() : "";
                    addField(e.type, e.name + var.name,
                             [e, prefix, var](const SynapseGroupInternal &sg, size_t)
                             {
                                 if(sg.isWeightSharingSlave()) {
                                     return prefix + e.name + var.name + sg.getWeightSharingMaster()->getName();
                                 }
                                 else {
                                     return prefix + e.name + var.name + sg.getName();
                                 }
                             },
                             isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void CodeGenerator::SynapseGroupMergedBase::addPSPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getPSModelTargetName(); });
}
//----------------------------------------------------------------------------
void CodeGenerator::SynapseGroupMergedBase::addSrcPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getSrcNeuronGroup()->getName(); });
}
//----------------------------------------------------------------------------
void CodeGenerator::SynapseGroupMergedBase::addTrgPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getTrgNeuronGroup()->getName(); });
}
//----------------------------------------------------------------------------
void CodeGenerator::SynapseGroupMergedBase::addWeightSharingPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    addField(type + "*", name, 
                   [prefix](const SynapseGroupInternal &sg, size_t)
                   { 
                       if(sg.isWeightSharingSlave()) {
                           return prefix + sg.getWeightSharingMaster()->getName();
                       }
                       else {
                           return prefix + sg.getName();
                       }
                   });
}

//----------------------------------------------------------------------------
// CodeGenerator::PresynapticUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::PresynapticUpdateGroupMerged::name = "PresynapticUpdate";

//----------------------------------------------------------------------------
// CodeGenerator::PostsynapticUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::PostsynapticUpdateGroupMerged::name = "PostsynapticUpdate";

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDynamicsGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseDynamicsGroupMerged::name = "SynapseDynamics";

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDenseInitGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseDenseInitGroupMerged::name = "SynapseDenseInit";

//----------------------------------------------------------------------------
// CodeGenerator::SynapseSparseInitGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseSparseInitGroupMerged::name = "SynapseSparseInit";

// ----------------------------------------------------------------------------
// CodeGenerator::SynapseConnectivityInitGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseConnectivityInitGroupMerged::name = "SynapseConnectivityInit";
