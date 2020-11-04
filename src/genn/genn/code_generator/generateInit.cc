#include "code_generator/generateInit.h"

// Standard C++ includes
#include <string>

// GeNN includes
#include "models.h"

// GeNN code generator includes
#include "code_generator/codeStream.h"
#include "code_generator/modelSpecMerged.h"
#include "code_generator/substitutions.h"

using namespace CodeGenerator;

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace
{
void genInitSpikeCount(CodeStream &os, const BackendBase &backend,
                       const Substitutions &popSubs, NeuronInitGroupMerged &ng, bool spikeEvent)
{
    // Is initialisation required at all
    const bool initRequired = spikeEvent ? ng.getArchetype().isSpikeEventRequired() : true;
    if(initRequired) {
        // Generate variable initialisation code
        backend.genPopVariableInit(os, popSubs,
            [&backend, &ng, spikeEvent] (CodeStream &os, Substitutions &)
            {
                // Get correct spike count
                const std::string spikeCount = spikeEvent ? ng.getSpikeEventCount() : ng.getSpikeCount() ;

                // Is delay required
                const bool delayRequired = spikeEvent ?
                    ng.getArchetype().isDelayRequired() :
                    (ng.getArchetype().isTrueSpikeRequired() && ng.getArchetype().isDelayRequired());

                if(delayRequired) {
                    os << "for (unsigned int d = 0; d < " << ng.getArchetype().getNumDelaySlots() << "; d++)";
                    {
                        CodeStream::Scope b(os);
                        os << spikeCount << "[d] = 0;" << std::endl;
                    }
                }
                else {
                    os << spikeCount << "[0] = 0;" << std::endl;
                }
            });
    }

}
//--------------------------------------------------------------------------
void genInitSpikes(CodeStream &os, const BackendBase &backend,
                   const Substitutions &popSubs, NeuronInitGroupMerged &ng, bool spikeEvent)
{
    // Is initialisation required at all
    const bool initRequired = spikeEvent ? ng.getArchetype().isSpikeEventRequired() : true;
    if(initRequired) {
        // Generate variable initialisation code
        backend.genVariableInit(os, ng.getNumNeurons(), "id", popSubs,
            [&ng, &backend, spikeEvent] (CodeStream &os, Substitutions &varSubs)
            {
                // Get variable name
                const std::string spike = spikeEvent ? ng.getSpikeEvents() : ng.getSpikes() ;

                // Is delay required
                const bool delayRequired = spikeEvent ?
                    ng.getArchetype().isDelayRequired() :
                    (ng.getArchetype().isTrueSpikeRequired() && ng.getArchetype().isDelayRequired());

                if(delayRequired) {
                    os << "for (unsigned int d = 0; d < " << ng.getArchetype().getNumDelaySlots() << "; d++)";
                    {
                        CodeStream::Scope b(os);
                        os << spike << "[(d * " << ng.getNumNeurons() << ") + " + varSubs["id"] + "] = 0;" << std::endl;
                    }
                }
                else {
                    os << spike << "[" << varSubs["id"] << "] = 0;" << std::endl;
                }
            });
    }
}
//------------------------------------------------------------------------
// **TODO** make typed like generateWUVarUpdate 
template<typename I, typename Q, typename V, typename P, typename D, typename E>
void genInitNeuronVarCode(CodeStream &os, const BackendBase &backend, const Substitutions &popSubs,
                          const Models::Base::VarVec &vars, const std::string &count, 
                          size_t numDelaySlots, const size_t groupIndex, const std::string &ftype,
                          I getVarInitialiser, Q isVarQueueRequired, V getVarFn,
                          P getVarInitParamFn, D getVarInitDerivedParamFn, E getVarInitEGPFn)
{
    for (size_t k = 0; k < vars.size(); k++) {
        const auto &varInit = getVarInitialiser(k);

        // If this variable has any initialisation code
        if(!varInit.getSnippet()->getCode().empty()) {
            CodeStream::Scope b(os);

            // Generate target-specific code to initialise variable
            backend.genVariableInit(os, count, "id", popSubs,
                [&vars, &varInit, &ftype, groupIndex, k, count, isVarQueueRequired, getVarFn,
                 getVarInitParamFn, getVarInitDerivedParamFn, getVarInitEGPFn, numDelaySlots]
                (CodeStream &os, Substitutions &varSubs)
                {
                    // Substitute in parameters and derived parameters for initialising variables
                    varSubs.addParamValueSubstitution(varInit.getSnippet()->getParamNames(), 
                                                      [k, getVarInitParamFn](size_t i) { return getVarInitParamFn(k, i); });
                    varSubs.addVarValueSubstitution(varInit.getSnippet()->getDerivedParams(),
                                                    [k, getVarInitDerivedParamFn](size_t i) { return getVarInitDerivedParamFn(k, i); });
                    varSubs.addVarNameSubstitution<Snippet::Base::EGP>(varInit.getSnippet()->getExtraGlobalParams(),
                                                                       [k, getVarInitEGPFn](const Snippet::Base::EGP &egp){ return getVarInitEGPFn(k, egp); });

                    // If variable requires a queue
                    if (isVarQueueRequired(k)) {
                        // Generate initial value into temporary variable
                        os << vars[k].type << " initVal;" << std::endl;
                        varSubs.addVarSubstitution("value", "initVal");


                        std::string code = varInit.getSnippet()->getCode();
                        varSubs.applyCheckUnreplaced(code, "initVar : " + vars[k].name + "merged" + std::to_string(groupIndex));
                        code = ensureFtype(code, ftype);
                        os << code << std::endl;

                        // Copy this into all delay slots
                        os << "for (unsigned int d = 0; d < " << numDelaySlots << "; d++)";
                        {
                            CodeStream::Scope b(os);
                            os << getVarFn(vars[k]) << "[(d * " << count << ") + " + varSubs["id"] + "] = initVal;" << std::endl;
                        }
                    }
                    else {
                        varSubs.addVarSubstitution("value", getVarFn(vars[k]) + "[" + varSubs["id"] + "]");

                        std::string code = varInit.getSnippet()->getCode();
                        varSubs.applyCheckUnreplaced(code, "initVar : " + vars[k].name + "merged" + std::to_string(groupIndex));
                        code = ensureFtype(code, ftype);
                        os << code << std::endl;
                    }
                });
        }
    }
}
//------------------------------------------------------------------------
template<typename I, typename P, typename D, typename V, typename E>
void genInitNeuronVarCode(CodeStream &os, const BackendBase &backend, const Substitutions &popSubs,
                          const Models::Base::VarVec &vars, const std::string &count, 
                          const size_t groupIndex, const std::string &ftype, 
                          I getVarInitialiser, V getVarFn,
                          P getVarInitParamFn, D getVarInitDerivedParamFn, E getVarInitEGPFn)
{
    genInitNeuronVarCode(os, backend, popSubs, vars, count, 0, groupIndex, ftype,
                         getVarInitialiser,
                         [](size_t){ return false; }, getVarFn,
                         getVarInitParamFn, getVarInitDerivedParamFn, getVarInitEGPFn);
}
//------------------------------------------------------------------------
// Initialise one row of weight update model variables
void genInitWUVarCode(CodeStream &os, const BackendBase &backend,
                      const Substitutions &popSubs, const SynapseGroupMergedBase &sg, const std::string &ftype)
{
    const auto vars = sg.getArchetype().getWUModel()->getVars();
    for (size_t k = 0; k < vars.size(); k++) {
        const auto &varInit = sg.getArchetype().getWUVarInitialisers().at(k);

        // If this variable has any initialisation code and doesn't require a kernel
        if(!varInit.getSnippet()->getCode().empty() && !varInit.getSnippet()->requiresKernel()) {
            CodeStream::Scope b(os);

            // Generate target-specific code to initialise variable
            backend.genSynapseVariableRowInit(os, sg, popSubs,
                [&vars, &varInit, &sg, &ftype, k](CodeStream &os, Substitutions &varSubs)
                {
                    varSubs.addVarSubstitution("value", "group->" + vars[k].name + "[" + varSubs["id_syn"] +  "]");
                    varSubs.addParamValueSubstitution(varInit.getSnippet()->getParamNames(), varInit.getParams(),
                                                      [k, &sg](size_t p) { return sg.isWUVarInitParamHeterogeneous(k, p); },
                                                      "", "group->", vars[k].name);
                    varSubs.addVarValueSubstitution(varInit.getSnippet()->getDerivedParams(), varInit.getDerivedParams(),
                                                      [k, &sg](size_t p) { return sg.isWUVarInitDerivedParamHeterogeneous(k, p); },
                                                      "", "group->", vars[k].name);
                    varSubs.addVarNameSubstitution(varInit.getSnippet()->getExtraGlobalParams(),
                                                   "", "group->", vars[k].name);

                    std::string code = varInit.getSnippet()->getCode();
                    varSubs.applyCheckUnreplaced(code, "initVar : merged" + vars[k].name + std::to_string(sg.getIndex()));
                    code = ensureFtype(code, ftype);
                    os << code << std::endl;
                });
        }
    }
}
}   // Anonymous namespace

//--------------------------------------------------------------------------
// CodeGenerator
//--------------------------------------------------------------------------
void CodeGenerator::generateInit(CodeStream &os, BackendBase::MemorySpaces &memorySpaces,
                                 ModelSpecMerged &modelMerged, const BackendBase &backend)
{
    os << "#include \"definitionsInternal.h\"" << std::endl;

    // Generate functions to push merged synapse group structures
    const ModelSpecInternal &model = modelMerged.getModel();

    backend.genInit(os, modelMerged, memorySpaces,
        // Preamble handler
        [&modelMerged, &backend](CodeStream &os)
        {
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedNeuronInitGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedSynapseDenseInitGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedSynapseConnectivityInitGroups(), backend);
            modelMerged.genMergedGroupPush(os, modelMerged.getMergedSynapseSparseInitGroups(), backend);
        },
        // Local neuron group initialisation
        [&backend, &model](CodeStream &os, NeuronInitGroupMerged &ng, Substitutions &popSubs)
        {
            // Initialise spike counts
            genInitSpikeCount(os, backend, popSubs, ng, false);
            genInitSpikeCount(os, backend, popSubs, ng, true);

            // Initialise spikes
            genInitSpikes(os, backend, popSubs, ng, false);
            genInitSpikes(os, backend, popSubs, ng, true);

            // If spike times are required
            if(ng.getArchetype().isSpikeTimeRequired()) {
                // Generate variable initialisation code
                backend.genVariableInit(os, ng.getNumNeurons(), "id", popSubs,
                    [&backend, &ng] (CodeStream &os, Substitutions &varSubs)
                    {
                        // Is delay required
                        if(ng.getArchetype().isDelayRequired()) {
                            os << "for (unsigned int d = 0; d < " << ng.getArchetype().getNumDelaySlots() << "; d++)";
                            {
                                CodeStream::Scope b(os);
                                os << ng.getSpikeTimes() << "[(d * " << ng.getNumNeurons() << ") + " + varSubs["id"] + "] = -TIME_MAX;" << std::endl;
                            }
                        }
                        else {
                            os << ng.getSpikeTimes() << "[" << varSubs["id"] << "] = -TIME_MAX;" << std::endl;
                        }
                    });
            }

            // If neuron group requires delays, zero spike queue pointer
            if(ng.getArchetype().isDelayRequired()) {
                backend.genPopVariableInit(os, popSubs,
                    [&backend, &ng](CodeStream &os, Substitutions &)
                    {
                        os << "*" << ng.getSpikeQueuePointer() << " = 0;" << std::endl;
                    });
            }

            // Initialise neuron variables
            genInitNeuronVarCode(os, backend, popSubs, ng.getArchetype().getNeuronModel()->getVars(), ng.getNumNeurons(),
                                 ng.getArchetype().getNumDelaySlots(), ng.getIndex(), model.getPrecision(),
                                 [&ng](size_t i){ return ng.getArchetype().getVarInitialisers().at(i); },
                                 [&ng](size_t i){ return ng.getArchetype().isVarQueueRequired(i); },
                                 [&ng](const Models::Base::Var &var) { return ng.getVarField(var); },
                                 [&ng](size_t v, size_t p) { return ng.getVarInitParam(v, p); },
                                 [&ng](size_t v, size_t p) { return ng.getVarInitDerivedParam(v, p); },
                                 [&ng](size_t v, const Snippet::Base::EGP &egp) { return ng.getVarInitEGP(v, egp); });

            // Loop through incoming synaptic populations
            for(size_t i = 0; i < ng.getArchetype().getMergedInSyn().size(); i++) {
                CodeStream::Scope b(os);

                const auto *sg = ng.getArchetype().getMergedInSyn()[i].first;

                // If this synapse group's input variable should be initialised on device
                // Generate target-specific code to initialise variable
                backend.genVariableInit(os, ng.getNumNeurons(), "id", popSubs,
                    [&model, &ng, i] (CodeStream &os, Substitutions &varSubs)
                    {
                        os << ng.getPSMInSyn(i) << "[" << varSubs["id"] << "] = " << model.scalarExpr(0.0) << ";" << std::endl;
                    });

                // If dendritic delays are required
                if(sg->isDendriticDelayRequired()) {
                    backend.genVariableInit(os, ng.getNumNeurons(), "id", popSubs,
                        [&model, &sg, &ng, i](CodeStream &os, Substitutions &varSubs)
                        {
                            os << "for (unsigned int d = 0; d < " << sg->getMaxDendriticDelayTimesteps() << "; d++)";
                            {
                                CodeStream::Scope b(os);
                                const std::string denDelayIndex = "(d * " + ng.getNumNeurons() + ") + " + varSubs["id"];
                                os << ng.getPSMDenDelay(i) << "[" << denDelayIndex << "] = " << model.scalarExpr(0.0) << ";" << std::endl;
                            }
                        });

                    // Zero dendritic delay pointer
                    backend.genPopVariableInit(os, popSubs,
                        [&ng, i](CodeStream &os, Substitutions &)
                        {
                            os << "*" << ng.getPSMDenDelayPtr(i) << " = 0;" << std::endl;
                        });
                }

                // If postsynaptic model variables should be individual
                if(sg->getMatrixType() & SynapseMatrixWeight::INDIVIDUAL_PSM) {
                    genInitNeuronVarCode(os, backend, popSubs, sg->getPSModel()->getVars(),
                                         ng.getNumNeurons(), i, model.getPrecision(),
                                         [sg](size_t i){ return sg->getPSVarInitialisers().at(i); },
                                         [&ng, i](const Models::Base::Var &var){ return ng.getPSMVar(i, var); },
                                         [&ng, i](size_t v, size_t p){ return ng.getPSMVarInitParam(i, v, p); },
                                         [&ng, i](size_t v, size_t p){ return ng.getPSMVarInitDerivedParam(i, v, p); },
                                         [&ng, i](size_t v, const Snippet::Base::EGP &egp){ return ng.getPSMVarInitEGP(i, v, egp); });
                }
            }

            // Loop through incoming synaptic populations with postsynaptic update code
            // **NOTE** number of delay slots is based on the target neuron (for simplicity) but whether delay is required is based on the synapse group
            const auto inSynWithPostVars = ng.getArchetype().getInSynWithPostVars();
            for(size_t i = 0; i < inSynWithPostVars.size(); i++) {
                const auto *sg = inSynWithPostVars.at(i);
                genInitNeuronVarCode(os, backend, popSubs, sg->getWUModel()->getPostVars(),
                                     ng.getNumNeurons(), sg->getTrgNeuronGroup()->getNumDelaySlots(),
                                     i, model.getPrecision(),
                                     [&sg](size_t i){ return sg->getWUPostVarInitialisers().at(i); },
                                     [&sg](size_t){ return (sg->getBackPropDelaySteps() != NO_DELAY); },
                                     [&ng, i](const Models::Base::Var &var) { return ng.getInSynVar(i, var); },
                                     [&ng, i](size_t v, size_t p) { return ng.getInSynPostVarInitParam(i, v, p); },
                                     [&ng, i](size_t v, size_t p) { return ng.getInSynPostVarInitDerivedParam(i, v, p); },
                                     [&ng, i](size_t v, const Snippet::Base::EGP &egp){ return ng.getInSynPostVarInitEGP(i, v, egp); });
            }

            // Loop through outgoing synaptic populations with presynaptic update code
            // **NOTE** number of delay slots is based on the source neuron (for simplicity) but whether delay is required is based on the synapse group
            const auto outSynWithPostVars = ng.getArchetype().getOutSynWithPreVars();
            for(size_t i = 0; i < outSynWithPostVars.size(); i++) {
                const auto *sg = outSynWithPostVars.at(i);
                genInitNeuronVarCode(os, backend, popSubs, sg->getWUModel()->getPreVars(),
                                     ng.getNumNeurons(), sg->getSrcNeuronGroup()->getNumDelaySlots(),
                                     i, model.getPrecision(),
                                     [&sg](size_t i){ return sg->getWUPreVarInitialisers().at(i); },
                                     [&sg](size_t){ return (sg->getDelaySteps() != NO_DELAY); },
                                     [&ng, i](const Models::Base::Var &var) { return ng.getOutSynVar(i, var); },
                                     [&ng, i](size_t v, size_t p) { return ng.getOutSynPreVarInitParam(i, v, p); },
                                     [&ng, i](size_t v, size_t p) { return ng.getOutSynPreVarInitDerivedParam(i, v, p); },
                                     [&ng, i](size_t v, const Snippet::Base::EGP &egp){ return ng.getOutSynPreVarInitEGP(i, v, egp); });
            }

            // Loop through current sources
            os << "// current source variables" << std::endl;
            for(size_t i = 0; i < ng.getArchetype().getCurrentSources().size(); i++) {
                const auto *cs = ng.getArchetype().getCurrentSources()[i];

                genInitNeuronVarCode(os, backend, popSubs, cs->getCurrentSourceModel()->getVars(), 
                                     ng.getNumNeurons(),
                                     i, model.getPrecision(),
                                     [cs](size_t i){ return cs->getVarInitialisers().at(i); },
                                     [&ng, i](const Models::Base::Var &var) { return ng.getCurrentSourceVar(i, var); },
                                     [&ng, i](size_t v, size_t p) { return ng.getCurrentSourceVarInitParam(i, v, p); },
                                     [&ng, i](size_t v, size_t p) { return ng.getCurrentSourceVarInitDerivedParam(i, v, p); },
                                     [&ng, i](size_t v, const Snippet::Base::EGP &egp){ return ng.getCurrentSourceVarInitEGP(i, v, egp); });
            }
        },
        // Dense syanptic matrix variable initialisation
        [&backend, &model](CodeStream &os, const SynapseDenseInitGroupMerged &sg, Substitutions &popSubs)
        {
            // Loop through rows
            os << "for(unsigned int i = 0; i < group->numSrcNeurons; i++)";
            {
                CodeStream::Scope b(os);
                popSubs.addVarSubstitution("id_pre", "i");
                genInitWUVarCode(os, backend, popSubs, sg, model.getPrecision());

            }
        },
        // Sparse synaptic matrix connectivity initialisation
        [&model](CodeStream &os, const SynapseConnectivityInitGroupMerged &sg, Substitutions &popSubs)
        {
            const auto &connectInit = sg.getArchetype().getConnectivityInitialiser();

            // Add substitutions
            popSubs.addFuncSubstitution("endRow", 0, "break");
            popSubs.addParamValueSubstitution(connectInit.getSnippet()->getParamNames(), connectInit.getParams(),
                                              [&sg](size_t i) { return sg.isConnectivityInitParamHeterogeneous(i);  },
                                              "", "group->");
            popSubs.addVarValueSubstitution(connectInit.getSnippet()->getDerivedParams(), connectInit.getDerivedParams(),
                                            [&sg](size_t i) { return sg.isConnectivityInitDerivedParamHeterogeneous(i);  },
                                            "", "group->");
            popSubs.addVarNameSubstitution(connectInit.getSnippet()->getExtraGlobalParams(), "", "group->");

            // Initialise row building state variables and loop on generated code to initialise sparse connectivity
            os << "// Build sparse connectivity" << std::endl;
            for(const auto &a : connectInit.getSnippet()->getRowBuildStateVars()) {
                // Apply substitutions to value
                std::string value = a.value;
                popSubs.applyCheckUnreplaced(value, "initSparseConnectivity row build state var : merged" + std::to_string(sg.getIndex()));

                os << a.type << " " << a.name << " = " << value << ";" << std::endl;
            }
            os << "while(true)";
            {
                CodeStream::Scope b(os);

                // Apply substitutions to row build code
                std::string code = connectInit.getSnippet()->getRowBuildCode();
                popSubs.addVarNameSubstitution(connectInit.getSnippet()->getRowBuildStateVars());
                popSubs.applyCheckUnreplaced(code, "initSparseConnectivity : merged" + std::to_string(sg.getIndex()));
                code = ensureFtype(code, model.getPrecision());

                // Write out code
                os << code << std::endl;
            }
        },
        // Kernel matrix var initialisation
        [&backend, &model](CodeStream &os, const SynapseConnectivityInitGroupMerged &sg, Substitutions &popSubs)
        {
            // Generate kernel index and add to substitutions
            os << "const unsigned int kernelInd = ";
            genKernelIndex(os, popSubs, sg);
            os << ";" << std::endl;
            popSubs.addVarSubstitution("id_kernel", "kernelInd");

            const auto vars = sg.getArchetype().getWUModel()->getVars();
            for(size_t k = 0; k < vars.size(); k++) {
                const auto &varInit = sg.getArchetype().getWUVarInitialisers().at(k);

                // If this variable require a kernel
                if(varInit.getSnippet()->requiresKernel()) {
                    CodeStream::Scope b(os);

                    popSubs.addVarSubstitution("value", "group->" + vars[k].name + "[" + popSubs["id_syn"] + "]");
                    popSubs.addParamValueSubstitution(varInit.getSnippet()->getParamNames(), varInit.getParams(),
                                                      [k, &sg](size_t p) { return sg.isWUVarInitParamHeterogeneous(k, p); },
                                                      "", "group->", vars[k].name);
                    popSubs.addVarValueSubstitution(varInit.getSnippet()->getDerivedParams(), varInit.getDerivedParams(),
                                                    [k, &sg](size_t p) { return sg.isWUVarInitDerivedParamHeterogeneous(k, p); },
                                                    "", "group->", vars[k].name);
                    popSubs.addVarNameSubstitution(varInit.getSnippet()->getExtraGlobalParams(),
                                                    "", "group->", vars[k].name);

                    std::string code = varInit.getSnippet()->getCode();
                    //popSubs.applyCheckUnreplaced(code, "initVar : merged" + vars[k].name + std::to_string(sg.getIndex()));
                    popSubs.apply(code);
                    code = ensureFtype(code, model.getPrecision());
                    os << code << std::endl;
                }
            }
        },
        // Sparse synaptic matrix var initialisation
        [&backend, &model](CodeStream &os, const SynapseSparseInitGroupMerged &sg, Substitutions &popSubs)
        {
            genInitWUVarCode(os, backend, popSubs, sg, model.getPrecision());
        },
        // Initialise push EGP handler
        [&backend, &modelMerged](CodeStream &os)
        {
            modelMerged.genScalarEGPPush(os, "NeuronInit", backend);
            modelMerged.genScalarEGPPush(os, "SynapseDenseInit", backend);
            modelMerged.genScalarEGPPush(os, "SynapseConnectivityInit", backend);
        },
        // Initialise sparse push EGP handler
        [&backend, &modelMerged](CodeStream &os)
        {
            modelMerged.genScalarEGPPush(os, "SynapseSparseInit", backend);
        });
}
