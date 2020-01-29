#include "code_generator/groupMerged.h"

// PLOG includes
#include <plog/Log.h>

// GeNN includes
#include "modelSpecInternal.h"

// GeNN code generator includes
#include "code_generator/modelSpecMerged.h"

//----------------------------------------------------------------------------
// CodeGenerator::NeuronGroupMerged
//----------------------------------------------------------------------------
CodeGenerator::NeuronGroupMerged::NeuronGroupMerged(size_t index, const std::string &prefix, const std::vector<std::reference_wrapper<const NeuronGroupInternal>> &groups,
                                                    Role role, const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
:   CodeGenerator::GroupMerged<NeuronGroupInternal, NeuronGroupMerged>(index, prefix, groups)
{
    if(role == Role::SpikeQueueUpdate) {
        if(getArchetype().isDelayRequired()) {
            addField("unsigned int", "numDelaySlots",
                     [](const NeuronGroupInternal &ng, size_t) { return std::to_string(ng.getNumDelaySlots()); });

            addField("volatile unsigned int*", "spkQuePtr",
                     [&backend](const NeuronGroupInternal &ng, size_t)
                     {
                         return "getSymbolAddress(" + backend.getScalarPrefix() + "spkQuePtr" + ng.getName() + ")";
                     });
        }

        addPointerField("unsigned int", "spkCnt", backend.getArrayPrefix() + "glbSpkCnt");

        if(getArchetype().isSpikeEventRequired()) {
            addPointerField("unsigned int", "spkCntEvnt", backend.getArrayPrefix() + "glbSpkCntEvnt");
        }
    }
    else {
        // Build vector of vectors containing each child group's merged in syns, ordered to match those of the archetype group
        const bool init = (role == Role::Init);
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

        // Build vector of vectors containing each child group's incoming synapse groups
        // with postsynaptic updates, ordered to match those of the archetype group
        const auto inSynWithPostCode = getArchetype().getInSynWithPostCode();
        orderNeuronGroupChildren(inSynWithPostCode, m_SortedInSynWithPostCode, &NeuronGroupInternal::getInSynWithPostCode,
                                 [init](const SynapseGroupInternal *a, const SynapseGroupInternal *b)
                                 {
                                     return init ? a->canWUPostInitBeMerged(*b) : a->canWUPostBeMerged(*b);
                                 });

        // Build vector of vectors containing each child group's incoming synapse groups
        // with postsynaptic updates, ordered to match those of the archetype group
        const auto outSynWithPreCode = getArchetype().getOutSynWithPreCode();
        orderNeuronGroupChildren(outSynWithPreCode, m_SortedOutSynWithPreCode, &NeuronGroupInternal::getOutSynWithPreCode,
                                 [init](const SynapseGroupInternal *a, const SynapseGroupInternal *b)
                                 {
                                     return init ? a->canWUPreInitBeMerged(*b) : a->canWUPreBeMerged(*b);
                                 });

        addField("unsigned int", "numNeurons",
                 [](const NeuronGroupInternal &ng, size_t) { return std::to_string(ng.getNumNeurons()); });

        addPointerField("unsigned int", "spkCnt", backend.getArrayPrefix() + "glbSpkCnt");
        addPointerField("unsigned int", "spk", backend.getArrayPrefix() + "glbSpk");

        if(getArchetype().isSpikeEventRequired()) {
            addPointerField("unsigned int", "spkCntEvnt", backend.getArrayPrefix() + "glbSpkCntEvnt");
            addPointerField("unsigned int", "spkEvnt", backend.getArrayPrefix() + "glbSpkEvnt");
        }

        if(getArchetype().isDelayRequired()) {
            addField("volatile unsigned int*", "spkQuePtr",
                     [&backend](const NeuronGroupInternal &ng, size_t)
                     {
                         return "getSymbolAddress(" + backend.getScalarPrefix() + "spkQuePtr" + ng.getName() + ")";
                     });
        }

        if(getArchetype().isSpikeTimeRequired()) {
            addPointerField(modelSpec.getModel().getTimePrecision(), "sT", backend.getArrayPrefix() + "sT");
        }

        if(backend.isPopulationRNGRequired() && getArchetype().isSimRNGRequired()) {
            addPointerField("curandState", "rng", backend.getArrayPrefix() + "rng");
        }

        // Add pointers to variables
        const NeuronModels::Base *nm = getArchetype().getNeuronModel();
        addVars(nm->getVars(), backend.getArrayPrefix());

        // Extra global parameters are not required for init
        if(!init) {
            addEGPs(nm->getExtraGlobalParams());

            // Add heterogeneous neuron model parameters
            addHeterogeneousParams(getArchetype().getNeuronModel()->getParamNames(),
                                   &NeuronGroupInternal::getParams,
                                   &NeuronGroupMerged::isParamHeterogeneous);


            // Add heterogeneous neuron model derived parameters
            addHeterogeneousDerivedParams(getArchetype().getNeuronModel()->getDerivedParams(),
                                          &NeuronGroupInternal::getDerivedParams,
                                          &NeuronGroupMerged::isDerivedParamHeterogeneous);
        }

        // Build vector of vectors of neuron group's merged in syns
        // Loop through merged synaptic inputs in archetypical neuron group
        for(size_t i = 0; i < getArchetype().getMergedInSyn().size(); i++) {
            const SynapseGroupInternal *sg = getArchetype().getMergedInSyn()[i].first;

            // Add pointer to insyn
            addMergedInSynPointerField(modelSpec.getModel().getPrecision(), "inSynInSyn", i, backend.getArrayPrefix() + "inSyn");

            // Add pointer to dendritic delay buffer if required
            if(sg->isDendriticDelayRequired()) {
                addMergedInSynPointerField(modelSpec.getModel().getPrecision(), "denDelayInSyn", i, backend.getArrayPrefix() + "denDelay");

                addField("volatile unsigned int*", "denDelayPtrInSyn" + std::to_string(i),
                         [&backend, i, this](const NeuronGroupInternal &, size_t groupIndex)
                         {
                             const std::string &targetName = m_SortedMergedInSyns[groupIndex][i].first->getPSModelTargetName();
                             return "getSymbolAddress(" + backend.getScalarPrefix() + "denDelayPtr" + targetName + ")";
                         });
            }

            // Add pointers to state variables
            if(sg->getMatrixType() & SynapseMatrixWeight::INDIVIDUAL_PSM) {
                for(const auto &v : sg->getPSModel()->getVars()) {
                    addMergedInSynPointerField(v.type, v.name + "InSyn", i, backend.getArrayPrefix() + v.name);
                }
            }

            if(!init) {
                /*for(const auto &e : egps) {
                    gen.addField(e.type + " " + e.name + std::to_string(i),
                                 [e](const typename T::GroupInternal &g){ return e.name + g.getName(); });
                }*/
            }
        }

        // Loop through current sources in archetypical neuron group
        for(size_t i = 0; i < getArchetype().getCurrentSources().size(); i++) {
            const auto *cs = getArchetype().getCurrentSources()[i];

            const auto paramNames = cs->getCurrentSourceModel()->getParamNames();
            for(size_t p = 0; p < paramNames.size(); p++) {
                if(isCurrentSourceParamHeterogeneous(i, p)) {
                    addField("scalar", paramNames[p] + "CS" + std::to_string(i),
                             [i, p, this](const NeuronGroupInternal &, size_t groupIndex)
                             {
                                 const double val = m_SortedCurrentSources.at(groupIndex).at(i)->getParams().at(p);
                                 return Utils::writePreciseString(val);
                             });
                }
            }

            const auto derivedParams = cs->getCurrentSourceModel()->getDerivedParams();
            for(size_t p = 0; p < derivedParams.size(); p++) {
                if(isCurrentSourceDerivedParamHeterogeneous(i, p)) {
                    addField("scalar", derivedParams[p].name + "CS" + std::to_string(i),
                             [i, p, this](const NeuronGroupInternal &, size_t groupIndex)
                             {
                                 const double val = m_SortedCurrentSources.at(groupIndex).at(i)->getDerivedParams().at(p);
                                 return Utils::writePreciseString(val);
                             });
                }
            }

            for(const auto &v : cs->getCurrentSourceModel()->getVars()) {
                addCurrentSourcePointerField(v.type, v.name + "CS", i, backend.getArrayPrefix() + v.name);
            }
        }

        // Loop through incoming synapse groups with postsynaptic update code
        for(size_t i = 0; i < inSynWithPostCode.size(); i++) {
            for(const auto &v : inSynWithPostCode[i]->getWUModel()->getPostVars()) {
                addSynPointerField(v.type, v.name + "WUPost", i, backend.getArrayPrefix() + v.name, m_SortedInSynWithPostCode);
            }
        }

        // Loop through outgoing synapse groups with presynaptic update code
        for(size_t i = 0; i < outSynWithPreCode.size(); i++) {
            for(const auto &v : outSynWithPreCode[i]->getWUModel()->getPreVars()) {
                addSynPointerField(v.type, v.name + "WUPre", i, backend.getArrayPrefix() + v.name, m_SortedOutSynWithPreCode);
            }
        }

        std::vector<std::vector<SynapseGroupInternal *>> eventThresholdSGs;
        // Reserve vector of vectors to hold children for all neuron groups, in archetype order
        //sortedEventThresh.reserve(archetypeChildren.size());

        // Loop through neuron groups
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

        size_t i = 0;
        for(const auto &s : getArchetype().getSpikeEventCondition()) {
            if(s.egpInThresholdCode) {
                const auto sgEGPs = s.synapseGroup->getWUModel()->getExtraGlobalParams();
                for(const auto &egp : sgEGPs) {
                    addField(egp.type, egp.name + "EventThresh" + std::to_string(i),
                             [egp, &eventThresholdSGs, i](const NeuronGroupInternal &, size_t groupIndex)
                             {
                                 return egp.name + eventThresholdSGs.at(groupIndex).at(i)->getName();
                             },
                             Utils::isTypePointer(egp.type) ? FieldType::PointerEGP : FieldType::ScalarEGP);
                }
                i++;
            }
        }
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMerged::getCurrentQueueOffset() const
{
    assert(getArchetype().isDelayRequired());
    return "(*group.spkQuePtr * group.numNeurons)";
}
//----------------------------------------------------------------------------
std::string CodeGenerator::NeuronGroupMerged::getPrevQueueOffset() const
{
    assert(getArchetype().isDelayRequired());
    return "(((*group.spkQuePtr + " + std::to_string(getArchetype().getNumDelaySlots() - 1) + ") % " + std::to_string(getArchetype().getNumDelaySlots()) + ") * group.numNeurons)";
}
//----------------------------------------------------------------------------
bool CodeGenerator::NeuronGroupMerged::isParamHeterogeneous(size_t index) const
{
    return isParamValueHeterogeneous(
        index, [](const NeuronGroupInternal &ng) { return ng.getParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::NeuronGroupMerged::isDerivedParamHeterogeneous(size_t index) const
{
    return isParamValueHeterogeneous(
        index, [](const NeuronGroupInternal &ng) { return ng.getDerivedParams(); });
}
//----------------------------------------------------------------------------
bool CodeGenerator::NeuronGroupMerged::isCurrentSourceParamHeterogeneous(size_t childIndex, size_t paramIndex) const
{
    // If parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *csm = getArchetype().getCurrentSources().at(childIndex)->getCurrentSourceModel();
    const std::string paramName = csm->getParamNames().at(paramIndex);
    if(csm->getInjectionCode().find("$(" + paramName + ")") == std::string::npos) {
        return false;
    }
    // Otherwise, return whether values across all groups are heterogeneous
    else {
        return isChildParamValueHeterogeneous(childIndex, paramIndex, m_SortedCurrentSources,
                                              [](const CurrentSourceInternal *cs) { return cs->getParams();  });
    }
}
//----------------------------------------------------------------------------
bool CodeGenerator::NeuronGroupMerged::isCurrentSourceDerivedParamHeterogeneous(size_t childIndex, size_t paramIndex) const
{
    // If derived parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *csm = getArchetype().getCurrentSources().at(childIndex)->getCurrentSourceModel();
    const std::string derivedParamName = csm->getDerivedParams().at(paramIndex).name;
    if(csm->getInjectionCode().find("$(" + derivedParamName + ")") == std::string::npos) {
        return false;
    }
    // Otherwise, return whether values across all groups are heterogeneous
    else {
        return isChildParamValueHeterogeneous(childIndex, paramIndex, m_SortedCurrentSources,
                                              [](const CurrentSourceInternal *cs) { return cs->getDerivedParams();  });
    }
}


//----------------------------------------------------------------------------
// CodeGenerator::SynapseGroupMerged
//----------------------------------------------------------------------------
CodeGenerator::SynapseGroupMerged::SynapseGroupMerged(size_t index, const std::string &prefix, const std::vector<std::reference_wrapper<const SynapseGroupInternal>> &groups,
                                                      Role role, const CodeGenerator::ModelSpecMerged &modelSpec, const CodeGenerator::BackendBase &backend)
:   GroupMerged<SynapseGroupInternal, SynapseGroupMerged>(index, prefix, groups)
{
    if(role == Role::ConnectivityInit) {
        addField("unsigned int", "numSrcNeurons",
                 [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getSrcNeuronGroup()->getNumNeurons()); });
        addField("unsigned int", "numTrgNeurons",
                 [](const SynapseGroupInternal &sg, size_t) { return std::to_string(sg.getTrgNeuronGroup()->getNumNeurons()); });
        addField("unsigned int", "rowStride",
                 [&backend](const SynapseGroupInternal &sg, size_t) { return std::to_string(backend.getSynapticMatrixRowStride(sg)); });

        if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::SPARSE) {
            addPointerField("unsigned int", "rowLength", backend.getArrayPrefix() + "rowLength");
            addPointerField(getArchetype().getSparseIndType(), "ind", backend.getArrayPrefix() + "ind");
        }
        else if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::BITMASK) {
            addPointerField("uint32_t", "gp", backend.getArrayPrefix() + "gp");
        }

        // Add EGPs to struct
        addEGPs(getArchetype().getConnectivityInitialiser().getSnippet()->getExtraGlobalParams());
    }
    else if(role == Role::DendriticDelayUpdate) {
        addField("volatile unsigned int*", "denDelayPtr",
                 [&backend](const SynapseGroupInternal &sg, size_t)
                 {
                     return "getSymbolAddress(" + backend.getScalarPrefix() + "denDelayPtr" + sg.getPSModelTargetName() + ")";
                 });
    }
    else {
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
                addPSPointerField(modelSpec.getModel().getPrecision(), "denDelay", backend.getArrayPrefix() + "denDelay");
                addField("volatile unsigned int*", "denDelayPtr",
                         [&backend](const SynapseGroupInternal &sg, size_t)
                         {
                             return "getSymbolAddress(" + backend.getScalarPrefix() + "denDelayPtr" + sg.getPSModelTargetName() + ")";
                         });
            }
            else {
                addPSPointerField(modelSpec.getModel().getPrecision(), "inSyn", backend.getArrayPrefix() + "inSyn");
            }
        }

        if(role == Role::PresynapticUpdate) {
            if(getArchetype().isTrueSpikeRequired()) {
                addSrcPointerField("unsigned int", "srcSpkCnt", backend.getArrayPrefix() + "glbSpkCnt");
                addSrcPointerField("unsigned int", "srcSpk", backend.getArrayPrefix() + "glbSpk");
            }

            if(getArchetype().isSpikeEventRequired()) {
                addSrcPointerField("unsigned int", "srcSpkCntEvnt", backend.getArrayPrefix() + "glbSpkCntEvnt");
                addSrcPointerField("unsigned int", "srcSpkEvnt", backend.getArrayPrefix() + "glbSpkEvnt");
            }
        }
        else if(role == Role::PostsynapticUpdate) {
            addTrgPointerField("unsigned int", "trgSpkCnt", backend.getArrayPrefix() + "glbSpkCnt");
            addTrgPointerField("unsigned int", "trgSpk", backend.getArrayPrefix() + "glbSpk");
        }

        // If this structure is used for updating rather than initializing
        if(updateRole) {
            // If presynaptic population has delay buffers
            if(getArchetype().getSrcNeuronGroup()->isDelayRequired()) {
                addField("volatile unsigned int*", "srcSpkQuePtr",
                         [&backend](const SynapseGroupInternal &sg, size_t)
                         {
                             return "getSymbolAddress(" + backend.getScalarPrefix() + "spkQuePtr" + sg.getSrcNeuronGroup()->getName() + ")";
                         });
            }

            // If postsynaptic population has delay buffers
            if(getArchetype().getTrgNeuronGroup()->isDelayRequired()) {
                addField("volatile unsigned int*", "trgSpkQuePtr",
                         [&backend](const SynapseGroupInternal &sg, size_t)
                         {
                             return "getSymbolAddress(" + backend.getScalarPrefix() + "spkQuePtr" + sg.getTrgNeuronGroup()->getName() + ")";
                         });
            }

            // Get correct code string
            // **NOTE** we concatenate sim code and event code so both get tested
            const std::string code = ((role == Role::PresynapticUpdate) ? (wum->getSimCode() + wum->getEventCode())
                                      : (role == Role::PostsynapticUpdate) ? wum->getLearnPostCode() : wum->getSynapseDynamicsCode());

            // Loop through variables in presynaptic neuron model
            const auto preVars = getArchetype().getSrcNeuronGroup()->getNeuronModel()->getVars();
            for(const auto &v : preVars) {
                // If variable is referenced in code string, add source pointer
                if(code.find("$(" + v.name + "_pre)") != std::string::npos) {
                    addSrcPointerField(v.type, v.name + "Pre", backend.getArrayPrefix() + v.name);
                }
            }

            // Loop through variables in postsynaptic neuron model
            const auto postVars = getArchetype().getTrgNeuronGroup()->getNeuronModel()->getVars();
            for(const auto &v : postVars) {
                // If variable is referenced in code string, add target pointer
                if(code.find("$(" + v.name + "_post)") != std::string::npos) {
                    addTrgPointerField(v.type, v.name + "Post", backend.getArrayPrefix() + v.name);
                }
            }

            // Loop through extra global parameters in presynaptic neuron model
            const auto preEGPs = getArchetype().getSrcNeuronGroup()->getNeuronModel()->getExtraGlobalParams();
            for(const auto &e : preEGPs) {
                if(code.find("$(" + e.name + "_pre)") != std::string::npos) {
                    addSrcEGPField(e);
                }
            }

            // Loop through extra global parameters in postsynaptic neuron model
            const auto postEGPs = getArchetype().getTrgNeuronGroup()->getNeuronModel()->getExtraGlobalParams();
            for(const auto &e : postEGPs) {
                if(code.find("$(" + e.name + "_post)") != std::string::npos) {
                    addTrgEGPField(e);
                }
            }

            // Add spike times if required
            if(wum->isPreSpikeTimeRequired()) {
                addSrcPointerField(modelSpec.getModel().getTimePrecision(), "sTPre", backend.getArrayPrefix() + "sT");
            }
            if(wum->isPostSpikeTimeRequired()) {
                addTrgPointerField(modelSpec.getModel().getTimePrecision(), "sTPost", backend.getArrayPrefix() + "sT");
            }

            // Add pre and postsynaptic variables to struct
            addVars(wum->getPreVars(), backend.getArrayPrefix());
            addVars(wum->getPostVars(), backend.getArrayPrefix());

            // Add EGPs to struct
            addEGPs(wum->getExtraGlobalParams());
        }

        // Add pointers to connectivity data
        if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::SPARSE) {
            addPointerField("unsigned int", "rowLength", backend.getArrayPrefix() + "rowLength");
            addPointerField(getArchetype().getSparseIndType(), "ind", backend.getArrayPrefix() + "ind");

            // Add additional structure for postsynaptic access
            if(backend.isPostsynapticRemapRequired() && !wum->getLearnPostCode().empty()
               && (role == Role::PostsynapticUpdate || role == Role::SparseInit))
            {
                addPointerField("unsigned int", "colLength", backend.getArrayPrefix() + "colLength");
                addPointerField("unsigned int", "remap", backend.getArrayPrefix() + "remap");
            }

            // Add additional structure for synapse dynamics access
            if(backend.isSynRemapRequired() && !wum->getSynapseDynamicsCode().empty()
               && (role == Role::SynapseDynamics || role == Role::SparseInit))
            {
                addPointerField("unsigned int", "synRemap", backend.getArrayPrefix() + "synRemap");
            }
        }
        else if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::BITMASK) {
            addPointerField("uint32_t", "gp", backend.getArrayPrefix() + "gp");
        }
        else if(getArchetype().getMatrixType() & SynapseMatrixConnectivity::PROCEDURAL) {
            addEGPs(getArchetype().getConnectivityInitialiser().getSnippet()->getExtraGlobalParams());
        }

        // If synaptic matrix weights are individual, add pointers to var pointers to struct
        if(getArchetype().getMatrixType() & SynapseMatrixWeight::INDIVIDUAL) {
            addVars(wum->getVars(), backend.getArrayPrefix());
        }

        // If synaptic matrix weights are procedural or we are initializing
        if(getArchetype().getMatrixType() & SynapseMatrixWeight::PROCEDURAL || !updateRole) {
            addHeterogeneousVarInitParams(wum->getVars(), &SynapseGroupInternal::getWUVarInitialisers,
                                          &SynapseGroupMerged::isWUVarInitParamHeterogeneous);

            addHeterogeneousVarInitDerivedParams(wum->getVars(), &SynapseGroupInternal::getWUVarInitialisers,
                                                 &SynapseGroupMerged::isWUVarInitDerivedParamHeterogeneous);
        }
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMerged::getPresynapticAxonalDelaySlot() const
{
    assert(getArchetype().getSrcNeuronGroup()->isDelayRequired());

    const unsigned int numDelaySteps = getArchetype().getDelaySteps();
    if(numDelaySteps == 0) {
        return "(*group.srcSpkQuePtr)";
    }
    else {
        const unsigned int numSrcDelaySlots = getArchetype().getSrcNeuronGroup()->getNumDelaySlots();
        return "((*group.srcSpkQuePtr + " + std::to_string(numSrcDelaySlots - numDelaySteps) + ") % " + std::to_string(numSrcDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMerged::getPostsynapticBackPropDelaySlot() const
{
    assert(getArchetype().getTrgNeuronGroup()->isDelayRequired());

    const unsigned int numBackPropDelaySteps = getArchetype().getBackPropDelaySteps();
    if(numBackPropDelaySteps == 0) {
        return "(*group.trgSpkQuePtr)";
    }
    else {
        const unsigned int numTrgDelaySlots = getArchetype().getTrgNeuronGroup()->getNumDelaySlots();
        return "((*group.trgSpkQuePtr + " + std::to_string(numTrgDelaySlots - numBackPropDelaySteps) + ") % " + std::to_string(numTrgDelaySlots) + ")";
    }
}
//----------------------------------------------------------------------------
std::string CodeGenerator::SynapseGroupMerged::getDendriticDelayOffset(const std::string &offset) const
{
    assert(getArchetype().isDendriticDelayRequired());

    if(offset.empty()) {
        return "(*group.denDelayPtr * group.numTrgNeurons) + ";
    }
    else {
        return "(((*group.denDelayPtr + " + offset + ") % " + std::to_string(getArchetype().getMaxDendriticDelayTimesteps()) + ") * group.numTrgNeurons) + ";
    }
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMerged::isWUVarInitParamHeterogeneous(size_t varIndex, size_t paramIndex) const
{
    // If parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *varInitSnippet = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet();
    const std::string paramName = varInitSnippet->getParamNames().at(paramIndex);
    if(varInitSnippet->getCode().find("$(" + paramName + ")") == std::string::npos) {
        return false;
    }
    // Otherwise, return whether values across all groups are heterogeneous
    else {
        return isParamValueHeterogeneous(
            paramIndex,
            [varIndex](const SynapseGroupInternal &sg)
            {
                return sg.getWUVarInitialisers().at(varIndex).getParams();
            });
    }
}
//----------------------------------------------------------------------------
bool CodeGenerator::SynapseGroupMerged::isWUVarInitDerivedParamHeterogeneous(size_t varIndex, size_t paramIndex) const
{
    // If derived parameter isn't referenced in code, there's no point implementing it hetereogeneously!
    const auto *varInitSnippet = getArchetype().getWUVarInitialisers().at(varIndex).getSnippet();
    const std::string derivedParamName = varInitSnippet->getDerivedParams().at(paramIndex).name;
    if(varInitSnippet->getCode().find("$(" + derivedParamName + ")") == std::string::npos) {
        return false;
    }
    // Otherwise, return whether values across all groups are heterogeneous
    else {
        return isParamValueHeterogeneous(
            paramIndex,
            [varIndex](const SynapseGroupInternal &sg)
            {
                return sg.getWUVarInitialisers().at(varIndex).getDerivedParams();
            });
    }
}