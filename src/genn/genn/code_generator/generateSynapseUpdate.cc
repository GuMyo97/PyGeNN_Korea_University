#include "code_generator/generateSynapseUpdate.h"

// Standard C++ includes
#include <string>

// GeNN includes
#include "modelSpecInternal.h"

// GeNN code generator includes
#include "code_generator/codeStream.h"
#include "code_generator/substitutions.h"
#include "code_generator/backendBase.h"

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace
{
void applySynapseSubstitutions(CodeGenerator::CodeStream &os, std::string code, const std::string &errorContext,
                               const SynapseGroupInternal &sg, const CodeGenerator::Substitutions &baseSubs, const ModelSpecInternal &model,
                               const CodeGenerator::BackendBase &backend, unsigned int vectorWidth)
{
    CodeGenerator::Substitutions synapseSubs(&baseSubs);

    const auto *wum = sg.getWUModel();

    // If synaptic matrix has individual state variables, read them into local variables
    genVariableRead(os, wum->getCombinedVars(), sg.getWUVarImplementation(), backend,
                    sg.getName(), "l", synapseSubs["id_syn"], model.getPrecision(), vectorWidth);

    // Substitute parameter and derived parameter names
    synapseSubs.addParamValueSubstitution(wum->getCombinedDerivedParamNames(), sg.getWUDerivedParams());
    synapseSubs.addVarNameSubstitution(wum->getExtraGlobalParams(), "", "", sg.getName());

    // Substitute names of pre and postsynaptic weight update variables
    const std::string delayedPreIdx = (sg.getDelaySteps() == NO_DELAY) ? synapseSubs["id_pre"] : "preReadDelayOffset + " + baseSubs["id_pre"];
    synapseSubs.addVarSubstitution(wum->getPreVars(), sg.getWUPreVarInitialisers(), sg.getWUPreVarImplementation(),
                                   "", backend.getVarPrefix(), sg.getName() + "[" + delayedPreIdx + "]");

    const std::string delayedPostIdx = (sg.getBackPropDelaySteps() == NO_DELAY) ? synapseSubs["id_post"] : "postReadDelayOffset + " + baseSubs["id_post"];
    synapseSubs.addVarSubstitution(wum->getPostVars(), sg.getWUPostVarInitialisers(), sg.getWUPostVarImplementation(),
                                   "", backend.getVarPrefix(), sg.getName() + "[" + delayedPostIdx + "]");
    synapseSubs.addVarSubstitution(wum->getCombinedVars(), sg.getWUVarInitialisers(), sg.getWUVarImplementation(),
                                   "", "l", "", vectorWidth);


    neuronSubstitutionsInSynapticCode(synapseSubs, sg, synapseSubs["id_pre"],
                                      synapseSubs["id_post"], backend.getVarPrefix(),
                                      model.getDT());
    synapseSubs.applyCheckUnreplaced(code, errorContext + " : " + sg.getName());
    code = CodeGenerator::ensureFtype(code, model.getPrecision());
    os << code;

    // If synaptic matrix has individual state variables, write them back to local variables
    genVariableWriteBack(os, wum->getCombinedVars(), sg.getWUVarImplementation(), backend,
                         sg.getName(), "l", synapseSubs["id_syn"], model.getPrecision(), vectorWidth);
}
}   // Anonymous namespace

//--------------------------------------------------------------------------
// CodeGenerator
//--------------------------------------------------------------------------
void CodeGenerator::generateSynapseUpdate(CodeStream &os, const ModelSpecInternal &model, const BackendBase &backend,
                                          bool standaloneModules)
{
    if(standaloneModules) {
        os << "#include \"runner.cc\"" << std::endl;
    }
    else {
        os << "#include \"definitionsInternal.h\"" << std::endl;
    }
    os << "#include \"supportCode.h\"" << std::endl;
    os << std::endl;

    // Synaptic update kernels
    backend.genSynapseUpdate(os, model,
        // Presynaptic weight update threshold
        [&backend, &model](CodeStream &os, const SynapseGroupInternal &sg, const Substitutions &baseSubs)
        {
            Substitutions synapseSubs(&baseSubs);

            // Make weight update model substitutions
            synapseSubs.addGlobalVarSubstitution(sg.getWUModel()->getCombinedVars(), sg.getWUVarInitialisers(), sg.getWUVarImplementation());
            synapseSubs.addParamValueSubstitution(sg.getWUModel()->getCombinedDerivedParamNames(), sg.getWUDerivedParams());
            synapseSubs.addVarNameSubstitution(sg.getWUModel()->getExtraGlobalParams(), "", "", sg.getName());

            // Get read offset if required
            const std::string offset = sg.getSrcNeuronGroup()->isDelayRequired() ? "preReadDelayOffset + " : "";
            preNeuronSubstitutionsInSynapticCode(synapseSubs, sg, offset, "", baseSubs["id_pre"], backend.getVarPrefix());

            // Get event threshold condition code
            std::string code = sg.getWUModel()->getEventThresholdConditionCode();
            synapseSubs.applyCheckUnreplaced(code, "eventThresholdConditionCode");
            code = ensureFtype(code, model.getPrecision());
            os << code;
        },
        // Presynaptic spike
        [&backend, &model](CodeStream &os, const SynapseGroupInternal &sg, const Substitutions &baseSubs)
        {
            applySynapseSubstitutions(os, sg.getWUModel()->getSimCode(), "simCode",
                                      sg, baseSubs, model, backend, backend.getPresynapticUpdateVectorWidth(sg));
        },
        // Presynaptic spike-like event
        [&backend, &model](CodeStream &os, const SynapseGroupInternal &sg, const Substitutions &baseSubs)
        {
            applySynapseSubstitutions(os, sg.getWUModel()->getEventCode(), "eventCode",
                                      sg, baseSubs, model, backend, backend.getPresynapticUpdateVectorWidth(sg));
        },
        // Postsynaptic learning code
        [&backend, &model](CodeStream &os, const SynapseGroupInternal &sg, const Substitutions &baseSubs)
        {
            if (!sg.getWUModel()->getLearnPostSupportCode().empty()) {
                os << " using namespace " << sg.getName() << "_weightupdate_simLearnPost;" << std::endl;
            }

            applySynapseSubstitutions(os, sg.getWUModel()->getLearnPostCode(), "learnPostCode",
                                      sg, baseSubs, model, backend, 1);
        },
        // Synapse dynamics
        [&backend, &model](CodeStream &os, const SynapseGroupInternal &sg, const Substitutions &baseSubs)
        {
            if (!sg.getWUModel()->getSynapseDynamicsSuppportCode().empty()) {
                os << " using namespace " << sg.getName() << "_weightupdate_synapseDynamics;" << std::endl;
            }

            applySynapseSubstitutions(os, sg.getWUModel()->getSynapseDynamicsCode(), "synapseDynamics",
                                      sg, baseSubs, model, backend, 1);
        }
    );
}
