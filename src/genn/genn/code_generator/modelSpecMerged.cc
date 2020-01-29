#include "code_generator/modelSpecMerged.h"

// GeNN includes
#include "logging.h"
#include "modelSpecInternal.h"

// GeNN code generator includes
#include "code_generator/backendBase.h"

//----------------------------------------------------------------------------
// CodeGenerator::ModelSpecMerged
//----------------------------------------------------------------------------
CodeGenerator::ModelSpecMerged::ModelSpecMerged(const ModelSpecInternal &model, const BackendBase &backend)
:   m_Model(model), m_NeuronUpdateSupportCode("NeuronUpdateSupportCode"), m_PostsynapticDynamicsSupportCode("PostsynapticDynamicsSupportCode"),
    m_PresynapticUpdateSupportCode("PresynapticUpdateSupportCode"), m_PostsynapticUpdateSupportCode("PostsynapticUpdateSupportCode"),
    m_SynapseDynamicsSupportCode("SynapseDynamicsSupportCode")
{
    LOGD_CODE_GEN << "Merging neuron update groups:";
    createMergedGroups(model.getNeuronGroups(), m_MergedNeuronUpdateGroups, 
                       "NeuronUpdate", NeuronGroupMerged::Role::Update, backend,
                       [](const NeuronGroupInternal &){ return true; },
                       [](const NeuronGroupInternal &a, const NeuronGroupInternal &b){ return a.canBeMerged(b); });

    LOGD_CODE_GEN << "Merging presynaptic update groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedPresynapticUpdateGroups, 
                       "PresynapticUpdate", SynapseGroupMerged::Role::PresynapticUpdate, backend,
                       [](const SynapseGroupInternal &sg){ return (sg.isSpikeEventRequired() || sg.isTrueSpikeRequired()); },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canWUBeMerged(b); });

    LOGD_CODE_GEN << "Merging postsynaptic update groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedPostsynapticUpdateGroups, 
                       "PostsynapticUpdate", SynapseGroupMerged::Role::PostsynapticUpdate, backend,
                       [](const SynapseGroupInternal &sg){ return !sg.getWUModel()->getLearnPostCode().empty(); },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canWUBeMerged(b); });

    LOGD_CODE_GEN << "Merging synapse dynamics update groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedSynapseDynamicsGroups, 
                       "SynapseDynamics", SynapseGroupMerged::Role::SynapseDynamics, backend,
                       [](const SynapseGroupInternal &sg){ return !sg.getWUModel()->getSynapseDynamicsCode().empty(); },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canWUBeMerged(b); });

    LOGD_CODE_GEN << "Merging neuron initialization groups:";
    createMergedGroups(model.getNeuronGroups(), m_MergedNeuronInitGroups,
                       "NeuronInit", NeuronGroupMerged::Role::Init, backend,
                       [](const NeuronGroupInternal &){ return true; },
                       [](const NeuronGroupInternal &a, const NeuronGroupInternal &b){ return a.canInitBeMerged(b); });

    LOGD_CODE_GEN << "Merging synapse dense initialization groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedSynapseDenseInitGroups, 
                       "SynapseDenseInit", SynapseGroupMerged::Role::DenseInit, backend,
                       [](const SynapseGroupInternal &sg)
                       {
                           return ((sg.getMatrixType() & SynapseMatrixConnectivity::DENSE) && sg.isWUVarInitRequired());
                       },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canWUInitBeMerged(b); });

    LOGD_CODE_GEN << "Merging synapse connectivity initialisation groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedSynapseConnectivityInitGroups, 
                       "SynapseConnectivityInit", SynapseGroupMerged::Role::ConnectivityInit, backend,
                       [](const SynapseGroupInternal &sg){ return sg.isSparseConnectivityInitRequired(); },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canConnectivityInitBeMerged(b); });

    LOGD_CODE_GEN << "Merging synapse sparse initialization groups:";
    createMergedGroups(model.getSynapseGroups(), m_MergedSynapseSparseInitGroups,
                       "SynapseSparseInit", SynapseGroupMerged::Role::SparseInit, backend,
                       [&backend](const SynapseGroupInternal &sg)
                       {
                           return ((sg.getMatrixType() & SynapseMatrixConnectivity::SPARSE) && 
                                   (sg.isWUVarInitRequired()
                                    || (backend.isSynRemapRequired() && !sg.getWUModel()->getSynapseDynamicsCode().empty())
                                    || (backend.isPostsynapticRemapRequired() && !sg.getWUModel()->getLearnPostCode().empty())));
                       },
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b){ return a.canWUInitBeMerged(b); });

    LOGD_CODE_GEN << "Merging neuron groups which require their spike queues updating:";
    createMergedGroups(model.getNeuronGroups(), m_MergedNeuronSpikeQueueUpdateGroups, 
                       "NeuronSpikeQueueUpdate", NeuronGroupMerged::Role::SpikeQueueUpdate, backend,
                       [](const NeuronGroupInternal &){ return true; },
                       [](const NeuronGroupInternal &a, const NeuronGroupInternal &b)
                       {
                           return ((a.getNumDelaySlots() == b.getNumDelaySlots())
                                   && (a.isSpikeEventRequired() == b.isSpikeEventRequired())
                                   && (a.isTrueSpikeRequired() == b.isTrueSpikeRequired()));
                       });

    // Build vector of merged synapse groups which require dendritic delay
    std::vector<std::reference_wrapper<const SynapseGroupInternal>> synapseGroupsWithDendriticDelay;
    for(const auto &n : model.getNeuronGroups()) {
        for(const auto &m : n.second.getMergedInSyn()) {
            if(m.first->isDendriticDelayRequired()) {
                synapseGroupsWithDendriticDelay.push_back(std::cref(*m.first));
            }
        }
    }
    LOGD_CODE_GEN << "Merging synapse groups which require their dendritic delay updating:";
    createMergedGroups(synapseGroupsWithDendriticDelay, m_MergedSynapseDendriticDelayUpdateGroups, 
                       "SynapseDendriticDelayUpdate", SynapseGroupMerged::Role::DendriticDelayUpdate, backend,
                       [](const SynapseGroupInternal &a, const SynapseGroupInternal &b)
                       {
                           return (a.getMaxDendriticDelayTimesteps() == b.getMaxDendriticDelayTimesteps());
                       });

    // Loop through merged neuron groups
    for(const auto &ng : m_MergedNeuronUpdateGroups) {
        // Add neuron support code
        m_NeuronUpdateSupportCode.addSupportCode(ng.getArchetype().getNeuronModel()->getSupportCode());

        // Loop through merged postsynaptic models and add their support code
        for(const auto &sg : ng.getArchetype().getMergedInSyn()) {
            m_PostsynapticDynamicsSupportCode.addSupportCode(sg.first->getPSModel()->getSupportCode());
        }
    }

    // Loop through merged presynaptic update groups and add support code
    for(const auto &sg : m_MergedPresynapticUpdateGroups) {
        m_PresynapticUpdateSupportCode.addSupportCode(sg.getArchetype().getWUModel()->getSimSupportCode());
    }

    // Loop through merged postsynaptic update groups and add support code
    for(const auto &sg : m_MergedPostsynapticUpdateGroups) {
        m_PostsynapticUpdateSupportCode.addSupportCode(sg.getArchetype().getWUModel()->getLearnPostSupportCode());
    }

    // Loop through merged synapse dynamics groups and add support code
    for(const auto &sg : m_MergedSynapseDynamicsGroups) {
        m_SynapseDynamicsSupportCode.addSupportCode(sg.getArchetype().getWUModel()->getSynapseDynamicsSuppportCode());
    }
}
