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
CodeGenerator::NeuronSpikeQueueUpdateGroupMerged::NeuronSpikeQueueUpdateGroupMerged(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                                                                    const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   GroupMerged<NeuronGroupInternal>(index, precision, timePrecision, backend, groups)
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
    return getPointerField(getTimePrecision(), "sT", getBackend().getDeviceVarPrefix() + "sT");
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
    return addField(var.type + "*", var.name + "CS" + std::to_string(childIndex),
                    [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + var.name + m_SortedCurrentSources.at(groupIndex).at(childIndex)->getName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getPSMVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    return addField(var.type + "*", var.name + "InSyn" + std::to_string(childIndex),
                    [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + var.name + m_SortedMergedInSyns.at(groupIndex).at(childIndex).first->getPSModelTargetName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getPSMInSyn(size_t childIndex)
{
    return addField(getPrecision() + "*", "inSynInSyn" + std::to_string(childIndex),
                    [childIndex, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + "inSyn" + m_SortedMergedInSyns.at(groupIndex).at(childIndex).first->getPSModelTargetName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getPSMDenDelay(size_t childIndex)
{
    return addField(getPrecision() + "*", "denDelayInSyn" + std::to_string(childIndex),
                    [childIndex, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + "denDelay" + m_SortedMergedInSyns.at(groupIndex).at(childIndex).first->getPSModelTargetName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getPSMDenDelayPtr(size_t childIndex)
{
    return addField("unsigned int*", "denDelayPtrInSyn" + std::to_string(childIndex),
                    [childIndex, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return getBackend().getScalarAddressPrefix() + "denDelayPtr" + m_SortedMergedInSyns.at(groupIndex).at(childIndex).first->getPSModelTargetName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getInSynVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    return addField(var.type + "*", var.name + "WUPost" + std::to_string(childIndex),
                    [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + var.name + m_SortedInSynWithPostVars.at(groupIndex).at(childIndex)->getName();
                    });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMergedBase::getOutSynVar(size_t childIndex, const Models::Base::Var &var)
{
    assert(!Utils::isTypePointer(var.type));
    return addField(var.type + "*", var.name + "WUPre" + std::to_string(childIndex),
                    [childIndex, var, this](const NeuronGroupInternal &, size_t groupIndex)
                    {
                        return getBackend().getDeviceVarPrefix() + var.name + m_SortedOutSynWithPreVars.at(groupIndex).at(childIndex)->getName();
                    });
}
//----------------------------------------------------------------------------
CodeGenerator::NeuronGroupMergedBase::NeuronGroupMergedBase(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend, 
                                                            bool init, const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups)
:   CodeGenerator::GroupMerged<NeuronGroupInternal>(index, precision, timePrecision, backend, groups)
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
                         isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
            }
            i++;
        }
    }
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
std::string CodeGenerator::NeuronUpdateGroupMerged::getRecordSpk()
{
    // **YUCK** this mechanism needs to be renamed from PointerEGP to RuntimeAlloc
    return addField("uint32_t*", "recordSpk",
                    [this](const NeuronGroupInternal &ng, size_t)
                    {
                        return getBackend().getDeviceVarPrefix() + "recordSpk" + ng.getName();
                    },
                    FieldType::PointerEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getRecordSpkEvent()
{
    // **YUCK** this mechanism needs to be renamed from PointerEGP to RuntimeAlloc
    return addField("uint32_t*", "recordSpkEvent",
                    [this](const NeuronGroupInternal &ng, size_t)
                    {
                        return getBackend().getDeviceVarPrefix() + "recordSpkEvent" + ng.getName();
                    },
                    FieldType::PointerEGP);
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
std::string CodeGenerator::NeuronUpdateGroupMerged::getCurrentSourceEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "CS" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + getSortedCurrentSources().at(groupIndex).at(childIndex)->getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//
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
std::string CodeGenerator::NeuronUpdateGroupMerged::getPSMEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "InSyn" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedMergedInSyns().at(groupIndex).at(childIndex).first->getPSModelTargetName();
             },
             isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronUpdateGroupMerged::getPSMGlobalVar(size_t childIndex, size_t varIndex)
{
    const auto *psm = getArchetype().getMergedInSyn().at(childIndex).first->getPSModel();
    return getChildDerivedParamField(childIndex, varIndex, psm->getVars(),
                                     "InSyn" + std::to_string(childIndex), getSortedMergedInSyns(),
                                     [](const std::pair<SynapseGroupInternal*, std::vector<SynapseGroupInternal*>> &inSyn)
                                     {
                                         return inSyn.first->getPSConstInitVals();
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
std::string CodeGenerator::NeuronUpdateGroupMerged::getInSynEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "WUPost" + std::to_string(childIndex),
             [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
             {
                 return varPrefix + egp.name + getSortedInSynWithPostVars().at(groupIndex).at(childIndex)->getName();
             },
             isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
std::string CodeGenerator::NeuronUpdateGroupMerged::getOutSynEGP(size_t childIndex, const Models::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string varPrefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "WUPre" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + getSortedOutSynWithPreVars().at(groupIndex).at(childIndex)->getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
    return addField(egp.type, egp.name + varName,
                    [egp, varPrefix, varName, this](const NeuronGroupInternal &g, size_t)
                    {
                        return varPrefix + egp.name + varName + g.getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
    return addField(egp.type, egp.name + varName + "CS" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + varName + getSortedCurrentSources().at(groupIndex).at(childIndex)->getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
    return addField(egp.type, egp.name + varName + "InSyn" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + varName + getSortedMergedInSyns().at(groupIndex).at(childIndex).first->getPSModelTargetName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
    return addField(egp.type, egp.name + varName + "WUPost" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + varName + getSortedInSynWithPostVars().at(groupIndex).at(childIndex)->getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
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
    return addField(egp.type, egp.name + varName + "WUPre" + std::to_string(childIndex),
                    [childIndex, egp, varPrefix, varName, this](const NeuronGroupInternal&, size_t groupIndex)
                    {
                        return varPrefix + egp.name + varName + getSortedOutSynWithPreVars().at(groupIndex).at(childIndex)->getName();
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}

//----------------------------------------------------------------------------
// CodeGenerator::SynapseDendriticDelayUpdateGroupMerged
//----------------------------------------------------------------------------
const std::string CodeGenerator::SynapseDendriticDelayUpdateGroupMerged::name = "SynapseDendriticDelayUpdate";
//----------------------------------------------------------------------------
CodeGenerator::SynapseDendriticDelayUpdateGroupMerged::SynapseDendriticDelayUpdateGroupMerged(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                       const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
    : GroupMerged<SynapseGroupInternal>(index, precision, timePrecision, backend, groups)
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
CodeGenerator::SynapseConnectivityHostInitGroupMerged::SynapseConnectivityHostInitGroupMerged(size_t index, const std::string &precision, const std::string &timePrecision, const BackendBase &backend,
                                                                                              const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups)
:   GroupMerged<SynapseGroupInternal>(index, precision, timePrecision, backend, groups)
{
    assert(false);
    // **TODO** these could be generic
    /*addField("unsigned int", "numSrcNeurons",
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
    }*/
}

//----------------------------------------------------------------------------
// CodeGenerator::SynapseGroupMergedBase
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getRowStride()
{
    return getValueField("unsigned int", "rowStride",
                         [this](const SynapseGroupInternal &sg, size_t) { return std::to_string(getBackend().getSynapticMatrixRowStride(sg)); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getColStride()
{
   return getValueField("unsigned int", "colStride",
                        [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getMaxSourceConnections()); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getNumSrcNeurons()
{
    return getValueField("unsigned int", "numSrcNeurons",
                         [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getSrcNeuronGroup()->getNumNeurons()); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getNumTrgNeurons()
{
    return getValueField("unsigned int", "numTrgNeurons",
                         [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getTrgNeuronGroup()->getNumNeurons()); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getInSyn()
{
    return addPSPointerField(getPrecision(), "inSyn", getBackend().getDeviceVarPrefix() + "inSyn");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getDenDelay()
{
     return addPSPointerField(getPrecision(), "denDelay", getBackend().getDeviceVarPrefix() + "denDelay");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getDenDelayPtr()
{
    return addPSPointerField("unsigned int", "denDelayPtr", getBackend().getScalarAddressPrefix() + "denDelayPtr");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcSpikes()
{
    return addSrcPointerField("unsigned int", "srcSpk", getBackend().getDeviceVarPrefix() + "glbSpk");   
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNumSpikes()
{
    return addSrcPointerField("unsigned int", "srcSpkCnt", getBackend().getDeviceVarPrefix() + "glbSpkCnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcSpikeEvents()
{
    return addSrcPointerField("unsigned int", "srcSpkEvnt", getBackend().getDeviceVarPrefix() + "glbSpkEvnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNumSpikeEvents()
{
    return addSrcPointerField("unsigned int", "srcSpkCntEvnt", getBackend().getDeviceVarPrefix() + "glbSpkCntEvnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcSpikeQueuePointer()
{
    return addSrcPointerField("unsigned int", "srcSpkQuePtr", getBackend().getScalarAddressPrefix() + "spkQuePtr");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcSpikeTimes()
{
    return addSrcPointerField(getTimePrecision(), "sTPre", getBackend().getDeviceVarPrefix() + "sT");
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
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNeuronVar(const Models::Base::Var &var)
{
    return addSrcPointerField(var.type, var.name + "Pre", getBackend().getDeviceVarPrefix() + var.name);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSrcNeuronEGP(const Snippet::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string prefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "Pre",
                    [egp, prefix](const SynapseGroupInternal &sg, size_t) { return prefix + egp.name + sg.getSrcNeuronGroup()->getName(); },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgSpikes()
{
    return addTrgPointerField("unsigned int", "trgSpk", getBackend().getDeviceVarPrefix() + "glbSpk");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgNumSpikes()
{
    return addTrgPointerField("unsigned int", "trgSpkCnt", getBackend().getDeviceVarPrefix() + "glbSpkCnt");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgSpikeQueuePointer()
{
    return addTrgPointerField("unsigned int", "trgSpkQuePtr", getBackend().getScalarAddressPrefix() + "spkQuePtr");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgSpikeTimes()
{
    return addTrgPointerField(getTimePrecision(), "sTPost", getBackend().getDeviceVarPrefix() + "sT");
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
std::string CodeGenerator::SynapseGroupMergedBase::getTrgNeuronEGP(const Snippet::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string prefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + "Post",
                    [egp, prefix](const SynapseGroupInternal &sg, size_t) { return prefix + egp.name + sg.getTrgNeuronGroup()->getName(); },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getTrgNeuronVar(const Models::Base::Var &var)
{
    return addTrgPointerField(var.type, var.name + "Post", getBackend().getDeviceVarPrefix() + var.name);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getPresynapticAxonalDelaySlot()
{
    assert(getArchetype().getSrcNeuronGroup()->isDelayRequired());

    const unsigned int numDelaySteps = getArchetype().getDelaySteps();
    if(numDelaySteps == 0) {
        return "(*" + getSrcSpikeQueuePointer() + ")";
    }
    else {
        const unsigned int numSrcDelaySlots = getArchetype().getSrcNeuronGroup()->getNumDelaySlots();
        return "((*" + getSrcSpikeQueuePointer() + " + " + std::to_string(numSrcDelaySlots - numDelaySteps) + ") % " + std::to_string(numSrcDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getPostsynapticBackPropDelaySlot()
{
    assert(getArchetype().getTrgNeuronGroup()->isDelayRequired());

    const unsigned int numBackPropDelaySteps = getArchetype().getBackPropDelaySteps();
    if(numBackPropDelaySteps == 0) {
        return "(*" + getTrgSpikeQueuePointer() + ")";
    }
    else {
        const unsigned int numTrgDelaySlots = getArchetype().getTrgNeuronGroup()->getNumDelaySlots();
        return "((*" + getTrgSpikeQueuePointer() + " + " + std::to_string(numTrgDelaySlots - numBackPropDelaySteps) + ") % " + std::to_string(numTrgDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getDendriticDelayOffset(const std::string &offset)
{
    assert(getArchetype().isDendriticDelayRequired());

    if(offset.empty()) {
        return "(*" + getDenDelayPtr() + " * " + getNumTrgNeurons() + ") + ";
    }
    else {
        return "(((*" + getDenDelayPtr() + " + " + offset + ") % " + std::to_string(getArchetype().getMaxDendriticDelayTimesteps()) + ") * " + getNumTrgNeurons() + ") + ";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUParam(size_t index)
{
    return getParamField(index, getArchetype().getWUModel()->getParamNames(), "",
                         [](const SynapseGroupInternal &sg) { return sg.getWUParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUDerivedParam(size_t index)
{
    return getDerivedParamField(index, getArchetype().getWUModel()->getDerivedParams(), "",
                                [](const SynapseGroupInternal &sg) { return sg.getWUDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUVar(const Models::Base::Var &var)
{
     return addWeightSharingPointerField(var.type, var.name, getBackend().getDeviceVarPrefix() + var.name);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUGlobalVar(size_t varIndex)
{
    return getDerivedParamField(varIndex, getArchetype().getWUModel()->getVars(), "",
                                [](const SynapseGroupInternal &sg) { return sg.getWUConstInitVals(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUVarInitParam(size_t varIndex, size_t paramIndex)
{
    const auto paramNames = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet()->getParamNames();
    return getParamField(paramIndex, paramNames, getArchetype().getWUModel()->getVars().at(varIndex).name,
                         [varIndex](const SynapseGroupInternal &sg) { return sg.getWUVarInitialisers().at(varIndex).getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUVarInitDerivedParam(size_t varIndex, size_t paramIndex)
{
    const auto derivedParams = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet()->getDerivedParams();
    return getDerivedParamField(paramIndex, derivedParams, getArchetype().getWUModel()->getVars().at(varIndex).name,
                                [varIndex](const SynapseGroupInternal &sg) { return sg.getWUVarInitialisers().at(varIndex).getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getWUVarInitEGP(size_t varIndex, const Snippet::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const auto &var = getArchetype().getWUModel()->getVars().at(varIndex);
    const std::string prefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name + var.name,
                [egp, prefix, var](const SynapseGroupInternal &sg, size_t)
                {
                    if(sg.isWeightSharingSlave()) {
                        return prefix + egp.name + var.name + sg.getWeightSharingMaster()->getName();
                    }
                    else {
                        return prefix + egp.name + var.name + sg.getName();
                    }
                },
                isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getConnectivityInitParam(size_t paramIndex)
{
    const auto paramNames = getArchetype().getConnectivityInitialiser().getSnippet()->getParamNames();
    return getParamField(paramIndex, paramNames, "",
                         [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getConnectivityInitDerivedParam(size_t paramIndex)
{
    const auto derivedParams = getArchetype().getConnectivityInitialiser().getSnippet()->getDerivedParams();
    return getDerivedParamField(paramIndex, derivedParams, "",
                                [](const SynapseGroupInternal &sg) { return sg.getConnectivityInitialiser().getDerivedParams(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getConnectivityInitEGP(const Snippet::Base::EGP &egp)
{
    const bool isPointer = Utils::isTypePointer(egp.type);
    const std::string prefix = isPointer ? getBackend().getDeviceVarPrefix() : "";
    return addField(egp.type, egp.name,
                    [egp, prefix](const SynapseGroupInternal &sg, size_t)
                    {
                        if(sg.isWeightSharingSlave()) {
                            return prefix + egp.name + sg.getWeightSharingMaster()->getName();
                        }
                        else {
                            return prefix + egp.name + sg.getName();
                        }
                    },
                    isPointer ? FieldType::PointerEGP : FieldType::ScalarEGP);
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getRowLength()
{
    return addWeightSharingPointerField("unsigned int", "rowLength", getBackend().getDeviceVarPrefix() + "rowLength");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getInd()
{
    return addWeightSharingPointerField(getArchetype().getSparseIndType(), "ind", getBackend().getDeviceVarPrefix() + "ind");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getColLength()
{
     return addWeightSharingPointerField("unsigned int", "colLength", getBackend().getDeviceVarPrefix() + "colLength");
           
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getRemap()
{
     return addWeightSharingPointerField("unsigned int", "remap", getBackend().getDeviceVarPrefix() + "remap");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getSynRemap()
{
    return addWeightSharingPointerField("unsigned int", "synRemap", getBackend().getDeviceVarPrefix() + "synRemap");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getBitmask()
{
    return addWeightSharingPointerField("uint32_t", "gp", getBackend().getDeviceVarPrefix() + "gp");
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::getKernelSize(size_t dimension)
{
    return getValueField("unsigned int", "kernelSize" + std::to_string(dimension),
                         [dimension](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getKernelSize().at(dimension)); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::addPSPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    return addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getPSModelTargetName(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::addSrcPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    return addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getSrcNeuronGroup()->getName(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::addTrgPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    return addField(type + "*", name, [prefix](const SynapseGroupInternal &sg, size_t) { return prefix + sg.getTrgNeuronGroup()->getName(); });
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMergedBase::addWeightSharingPointerField(const std::string &type, const std::string &name, const std::string &prefix)
{
    assert(!Utils::isTypePointer(type));
    return addField(type + "*", name,
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
