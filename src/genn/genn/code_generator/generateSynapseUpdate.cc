#include "code_generator/generateSynapseUpdate.h"

// Standard C++ includes
#include <string>

// GeNN code generator includes
#include "code_generator/codeGenUtils.h"
#include "code_generator/codeStream.h"
#include "code_generator/groupMerged.h"
#include "code_generator/modelSpecMerged.h"
#include "code_generator/substitutions.h"
#include "code_generator/teeStream.h"

using namespace CodeGenerator;

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace
{
void applySynapseSubstitutions(CodeStream &os, std::string code, const std::string &errorContext,
                               SynapseGroupMerged &sg, const Substitutions &baseSubs,
                               const ModelSpecMerged &modelMerged, const bool backendSupportsNamespace)
{
    const ModelSpecInternal &model = modelMerged.getModel();
    const auto *wu = sg.getArchetype().getWUModel();

    Substitutions synapseSubs(&baseSubs);

    // Substitute parameter and derived parameter names
    synapseSubs.addParamValueSubstitution(wu->getParamNames(), [&sg](size_t i) { return sg.getWUParam(i); });
    synapseSubs.addVarValueSubstitution(wu->getDerivedParams(), [&sg](size_t i) { return sg.getWUDerivedParam(i); });
    synapseSubs.addVarNameSubstitution<Snippet::Base::EGP>(wu->getExtraGlobalParams(), 
                                                           [&sg](const Snippet::Base::EGP &egp){ return sg.getEGPField(egp); });

    // Substitute names of pre and postsynaptic weight update variables
    const std::string delayedPreIdx = (sg.getArchetype().getDelaySteps() == NO_DELAY) ? synapseSubs["id_pre"] : "preReadDelayOffset + " + baseSubs["id_pre"];
    synapseSubs.addVarNameSubstitution<Models::Base::Var>(wu->getPreVars(), 
                                                          [delayedPreIdx, &sg](const Models::Base::Var &var) { return sg.getVarField(var) + "[" + delayedPreIdx + "]"; });

    const std::string delayedPostIdx = (sg.getArchetype().getBackPropDelaySteps() == NO_DELAY) ? synapseSubs["id_post"] : "postReadDelayOffset + " + baseSubs["id_post"];
    synapseSubs.addVarNameSubstitution<Models::Base::Var>(wu->getPostVars(),
                                                          [delayedPostIdx, &sg](const Models::Base::Var &var) { return sg.getVarField(var) + "[" + delayedPostIdx + "]"; });

    // If weights are individual, substitute variables for values stored in global memory
    if (sg.getArchetype().getMatrixType() & SynapseMatrixWeight::INDIVIDUAL) {
        const std::string idx = "[" + synapseSubs["id_syn"] + "]";
        synapseSubs.addVarNameSubstitution<Models::Base::Var>(wu->getVars(), 
                                                              [idx, &sg](const Models::Base::Var &var) {return sg.getWUVar(var) + idx; });
    }
    // Otherwise, if weights are procedual
    else if (sg.getArchetype().getMatrixType() & SynapseMatrixWeight::PROCEDURAL) {
        if(!sg.getArchetype().getKernelSize().empty()) {
            // Generate kernel index
            os << "const unsigned int kernelInd = ";
            genKernelIndex(os, synapseSubs, sg);
            os << ";" << std::endl;

            // Add substitution
            synapseSubs.addVarSubstitution("id_kernel", "kernelInd");
        }
        const auto vars = wu->getVars();
        for(size_t k = 0; k < vars.size(); k++) {
            const auto &varInit = sg.getArchetype().getWUVarInitialisers().at(k);

            // If this variable has any initialisation code
            if(!varInit.getSnippet()->getCode().empty()) {
                // Configure variable substitutions
                CodeGenerator::Substitutions varSubs(&synapseSubs);
                varSubs.addVarSubstitution("value", "l" + vars[k].name);
                varSubs.addParamValueSubstitution(varInit.getSnippet()->getParamNames(),
                                                  [k, &sg](size_t p) { return sg.getWUVarInitParam(k, p); });
                varSubs.addVarValueSubstitution(varInit.getSnippet()->getDerivedParams(),
                                                [k, &sg](size_t p) { return sg.getWUVarInitDerivedParam(k, p); });
                varSubs.addVarNameSubstitution<Snippet::Base::EGP>(varInit.getSnippet()->getExtraGlobalParams(),
                                                                   [k, &sg](const Snippet::Base::EGP &egp) { return sg.getWUVarInitEGP(k, egp); });

                // Generate variable initialization code
                std::string code = varInit.getSnippet()->getCode();
                varSubs.applyCheckUnreplaced(code, "initVar : merged" + vars[k].name + std::to_string(sg.getIndex()));

                // Declare local variable
                os << vars[k].type << " " << "l" << vars[k].name << ";" << std::endl;

                // Insert code to initialize variable into scope
                {
                    CodeGenerator::CodeStream::Scope b(os);
                    os << code << std::endl;;
                }
            }
        }

        // Substitute variables for newly-declared local variables
        synapseSubs.addVarNameSubstitution(vars, "", "l");
    }
    // Otherwise, substitute variables for constant values
    else {
        synapseSubs.addVarValueSubstitution(wu->getVars(), [&sg](size_t v) { return sg.getWUGlobalVar(v); });
    }

    // Make presynaptic neuron substitutions
    const std::string axonalDelayMs = Utils::writePreciseString(model.getDT() * (double)(sg.getArchetype().getDelaySteps() + 1u)) + " + ";
    const std::string preOffset = sg.getArchetype().getSrcNeuronGroup()->isDelayRequired() ? "preReadDelayOffset + " : "";
    neuronSubstitutionsInSynapticCode(synapseSubs, sg.getArchetype().getSrcNeuronGroup(), preOffset, axonalDelayMs, synapseSubs["id_pre"],  "_pre",
                                      [&sg]() { return sg.getSrcSpikeTimes(); },
                                      [&sg](size_t paramIndex) { return sg.getSrcNeuronParam(paramIndex); },
                                      [&sg](size_t derivedParamIndex) { return sg.getSrcNeuronDerivedParam(derivedParamIndex); },
                                      [&sg](const Snippet::Base::EGP &egp) { return sg.getSrcNeuronEGP(egp); },
                                      [&sg](const Models::Base::Var &var) { return sg.getSrcNeuronVar(var); });

    // Make postsynaptic neuron substitutions
    const std::string backPropDelayMs = Utils::writePreciseString(model.getDT() * (double)(sg.getArchetype().getBackPropDelaySteps() + 1u)) + " + ";
    const std::string postOffset = sg.getArchetype().getTrgNeuronGroup()->isDelayRequired() ? "postReadDelayOffset + " : "";
    neuronSubstitutionsInSynapticCode(synapseSubs, sg.getArchetype().getTrgNeuronGroup(), postOffset, backPropDelayMs, synapseSubs["id_post"],  "_post",
                                      [&sg]() { return sg.getTrgSpikeTimes(); },
                                      [&sg](size_t paramIndex) { return sg.getTrgNeuronParam(paramIndex); },
                                      [&sg](size_t derivedParamIndex) { return sg.getTrgNeuronDerivedParam(derivedParamIndex); },
                                      [&sg](const Snippet::Base::EGP &egp) { return sg.getTrgNeuronEGP(egp); },
                                      [&sg](const Models::Base::Var &var) { return sg.getTrgNeuronVar(var); });

    // If the backend does not support namespaces then we substitute all support code functions with namepsace as prefix
    if (!backendSupportsNamespace) {
        if (!wu->getSimSupportCode().empty()) {
            code = disambiguateNamespaceFunction(wu->getSimSupportCode(), code, modelMerged.getPresynapticUpdateSupportCodeNamespace(wu->getSimSupportCode()));
        }
        if (!wu->getLearnPostSupportCode().empty()) {
            code = disambiguateNamespaceFunction(wu->getLearnPostSupportCode(), code, modelMerged.getPostsynapticUpdateSupportCodeNamespace(wu->getLearnPostSupportCode()));
        }
        if (!wu->getSynapseDynamicsSuppportCode().empty()) {
            code = disambiguateNamespaceFunction(wu->getSynapseDynamicsSuppportCode(), code, modelMerged.getSynapseDynamicsSupportCodeNamespace(wu->getSynapseDynamicsSuppportCode()));
        }
    }

    synapseSubs.apply(code);
    //synapseSubs.applyCheckUnreplaced(code, errorContext + " : " + sg.getName());
    code = ensureFtype(code, model.getPrecision());
    os << code;
}
}   // Anonymous namespace

//--------------------------------------------------------------------------
// CodeGenerator
//--------------------------------------------------------------------------
void CodeGenerator::generateSynapseUpdate(CodeStream &os, BackendBase::MemorySpaces &memorySpaces,
                                          ModelSpecMerged &modelMerged, const BackendBase &backend)
{
    os << "#include \"definitionsInternal.h\"" << std::endl;
    if (backend.supportsNamespace()) {
        os << "#include \"supportCode.h\"" << std::endl;
    }
    os << std::endl;

    // Generate functions to push merged synapse group structures
    const ModelSpecInternal &model = modelMerged.getModel();

    // Synaptic update kernels
    backend.genSynapseUpdate(os, modelMerged, memorySpaces,
        // Preamble handler
        [&modelMerged, &backend](CodeStream &os)
        {
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedSynapseDendriticDelayUpdateGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedPresynapticUpdateGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedPostsynapticUpdateGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedSynapseDynamicsGroups(), backend);
        },
        // Presynaptic weight update threshold
        [&modelMerged, &backend](CodeStream &os, PresynapticUpdateGroupMerged &sg, Substitutions &baseSubs)
        {
            Substitutions synapseSubs(&baseSubs);

            // Make weight update model substitutions
            synapseSubs.addParamValueSubstitution(sg.getArchetype().getWUModel()->getParamNames(), 
                                                  [&sg](size_t i) { return sg.getWUParam(i); });
            synapseSubs.addVarValueSubstitution(sg.getArchetype().getWUModel()->getDerivedParams(), 
                                                [&sg](size_t i) { return sg.getWUDerivedParam(i); });
            synapseSubs.addVarNameSubstitution<Snippet::Base::EGP>(sg.getArchetype().getWUModel()->getExtraGlobalParams(),
                                                                   [&sg](const Snippet::Base::EGP &egp) { return sg.getEGPField(egp); });

            // Get read offset if required and substitute in presynaptic neuron properties
            const std::string offset = sg.getArchetype().getSrcNeuronGroup()->isDelayRequired() ? "preReadDelayOffset + " : "";
            neuronSubstitutionsInSynapticCode(synapseSubs, sg.getArchetype().getSrcNeuronGroup(), offset, "", synapseSubs["id_pre"], "_pre",
                                              [&sg]() { return sg.getSrcSpikeTimes(); },
                                              [&sg](size_t paramIndex) { return sg.getSrcNeuronParam(paramIndex); },
                                              [&sg](size_t derivedParamIndex) { return sg.getSrcNeuronDerivedParam(derivedParamIndex); },
                                              [&sg](const Snippet::Base::EGP &egp) { return sg.getSrcNeuronEGP(egp); },
                                              [&sg](const Models::Base::Var &var) { return sg.getSrcNeuronVar(var); });

            const auto* wum = sg.getArchetype().getWUModel();

            // Get event threshold condition code
            std::string code = wum->getEventThresholdConditionCode();
            synapseSubs.applyCheckUnreplaced(code, "eventThresholdConditionCode");
            code = ensureFtype(code, modelMerged.getModel().getPrecision());

            if (!backend.supportsNamespace() && !wum->getSimSupportCode().empty()) {
                code = disambiguateNamespaceFunction(wum->getSimSupportCode(), code, modelMerged.getPresynapticUpdateSupportCodeNamespace(wum->getSimSupportCode()));
            }

            os << code;
        },
        // Presynaptic spike
        [&modelMerged, &backend](CodeStream &os, PresynapticUpdateGroupMerged &sg, Substitutions &baseSubs)
        {
            applySynapseSubstitutions(os, sg.getArchetype().getWUModel()->getSimCode(), "simCode",
                                      sg, baseSubs, modelMerged, backend.supportsNamespace());
        },
        // Presynaptic spike-like event
        [&modelMerged, &backend](CodeStream &os, PresynapticUpdateGroupMerged &sg, Substitutions &baseSubs)
        {
            applySynapseSubstitutions(os, sg.getArchetype().getWUModel()->getEventCode(), "eventCode",
                                      sg, baseSubs, modelMerged, backend.supportsNamespace());
        },
        // Procedural connectivity
        [&model](CodeStream &os, PresynapticUpdateGroupMerged &sg, Substitutions &baseSubs)
        {
            const auto &connectInit = sg.getArchetype().getConnectivityInitialiser();

            // Add substitutions
            baseSubs.addFuncSubstitution("endRow", 0, "break");
            baseSubs.addParamValueSubstitution(connectInit.getSnippet()->getParamNames(), 
                                               [&sg](size_t i) { return sg.getConnectivityInitParam(i); });
            baseSubs.addVarValueSubstitution(connectInit.getSnippet()->getDerivedParams(), 
                                             [&sg](size_t i) { return sg.getConnectivityInitDerivedParam(i); });
            baseSubs.addVarNameSubstitution<Snippet::Base::EGP>(connectInit.getSnippet()->getExtraGlobalParams(), 
                                                                [&sg](const Snippet::Base::EGP &egp) { return sg.getConnectivityInitEGP(egp); });

            // Initialise row building state variables for procedural connectivity
            for(const auto &a : connectInit.getSnippet()->getRowBuildStateVars()) {
                // Apply substitutions to value
                std::string value = a.value;
                baseSubs.applyCheckUnreplaced(value, "proceduralSparseConnectivity row build state var : merged" + std::to_string(sg.getIndex()));

                os << a.type << " " << a.name << " = " << value << ";" << std::endl;
            }

            // Loop through synapses in row
            os << "while(true)";
            {
                CodeStream::Scope b(os);

                // Apply substitutions to row building code
                std::string pCode = connectInit.getSnippet()->getRowBuildCode();
                baseSubs.addVarNameSubstitution(connectInit.getSnippet()->getRowBuildStateVars());
                baseSubs.applyCheckUnreplaced(pCode, "proceduralSparseConnectivity : merged " + std::to_string(sg.getIndex()));
                pCode = ensureFtype(pCode, model.getPrecision());

                // Write out code
                os << pCode << std::endl;
            }
        },
        // Postsynaptic learning code
        [&modelMerged, &backend](CodeStream &os, PostsynapticUpdateGroupMerged &sg, const Substitutions &baseSubs)
        {
            const auto *wum = sg.getArchetype().getWUModel();
            if (!wum->getLearnPostSupportCode().empty() && backend.supportsNamespace()) {
                os << "using namespace " << modelMerged.getPostsynapticUpdateSupportCodeNamespace(wum->getLearnPostSupportCode()) <<  ";" << std::endl;
            }

            applySynapseSubstitutions(os, wum->getLearnPostCode(), "learnPostCode",
                                      sg, baseSubs, modelMerged, backend.supportsNamespace());
        },
        // Synapse dynamics
        [&modelMerged, &backend](CodeStream &os, SynapseDynamicsGroupMerged &sg, const Substitutions &baseSubs)
        {
            const auto *wum = sg.getArchetype().getWUModel();
            if (!wum->getSynapseDynamicsSuppportCode().empty() && backend.supportsNamespace()) {
                os << "using namespace " << modelMerged.getSynapseDynamicsSupportCodeNamespace(wum->getSynapseDynamicsSuppportCode()) <<  ";" << std::endl;
            }

            applySynapseSubstitutions(os, wum->getSynapseDynamicsCode(), "synapseDynamics",
                                      sg, baseSubs, modelMerged, backend.supportsNamespace());
        },
        // Push EGP handler
        [&backend, &modelMerged](CodeStream &os)
        {
            modelMerged.genScalarEGPPush(os, "PresynapticUpdate", backend);
            modelMerged.genScalarEGPPush(os, "PostsynapticUpdate", backend);
            modelMerged.genScalarEGPPush(os, "SynapseDynamics", backend);
        });
}
