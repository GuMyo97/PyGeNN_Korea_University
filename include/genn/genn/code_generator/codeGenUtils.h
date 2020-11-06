#pragma once

// Standard includes
#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

// GeNN includes
#include "gennExport.h"
#include "gennUtils.h"
#include "neuronGroupInternal.h"
#include "variableMode.h"

// GeNN code generator includes
#include "backendBase.h"
#include "codeStream.h"
#include "substitutions.h"
#include "teeStream.h"

//--------------------------------------------------------------------------
// CodeGenerator
//--------------------------------------------------------------------------
namespace CodeGenerator
{
//--------------------------------------------------------------------------
//! \brief Tool for substituting strings in the neuron code strings or other templates
//--------------------------------------------------------------------------
GENN_EXPORT void substitute(std::string &s, const std::string &trg, const std::string &rep);

//--------------------------------------------------------------------------
/*! \brief Tool for substituting strings in the neuron code strings or other templates 
 * using 'lazy' evaluation - getRep is only called if 'trg' is found
 */
//--------------------------------------------------------------------------
template<typename V>
void substituteLazy(std::string &s, const std::string &trg, V getRepFn)
{
    size_t found= s.find(trg);
    while (found != std::string::npos) {
        s.replace(found,trg.length(), getRepFn());
        found= s.find(trg);
    }
}

//--------------------------------------------------------------------------
//! \brief Tool for substituting variable  names in the neuron code strings or other templates using regular expressions
//--------------------------------------------------------------------------
GENN_EXPORT bool regexVarSubstitute(std::string &s, const std::string &trg, const std::string &rep);

//--------------------------------------------------------------------------
//! \brief Tool for substituting function names in the neuron code strings or other templates using regular expressions
//--------------------------------------------------------------------------
GENN_EXPORT bool regexFuncSubstitute(std::string &s, const std::string &trg, const std::string &rep);

//--------------------------------------------------------------------------
/*! \brief This function substitutes function calls in the form:
 *
 *  $(functionName, parameter1, param2Function(0.12, "string"))
 *
 * with replacement templates in the form:
 *
 *  actualFunction(CONSTANT, $(0), $(1))
 *
 */
//--------------------------------------------------------------------------
GENN_EXPORT void functionSubstitute(std::string &code, const std::string &funcName,
                                    unsigned int numParams, const std::string &replaceFuncTemplate);

//! Divide two integers, rounding up i.e. effectively taking ceil
inline size_t ceilDivide(size_t numerator, size_t denominator)
{
    return ((numerator + denominator - 1) / denominator);
}

//! Pad an integer to a multiple of another
inline size_t padSize(size_t size, size_t blockSize)
{
    return ceilDivide(size, blockSize) * blockSize;
}

GENN_EXPORT void genTypeRange(CodeStream &os, const std::string &precision, const std::string &prefix);

//--------------------------------------------------------------------------
/*! \brief This function implements a parser that converts any floating point constant in a code snippet to a floating point constant with an explicit precision (by appending "f" or removing it).
 */
//--------------------------------------------------------------------------
GENN_EXPORT std::string ensureFtype(const std::string &oldcode, const std::string &type);


//--------------------------------------------------------------------------
/*! \brief This function checks for unknown variable definitions and returns a gennError if any are found
 */
//--------------------------------------------------------------------------
GENN_EXPORT void checkUnreplacedVariables(const std::string &code, const std::string &codeName);

//--------------------------------------------------------------------------
/*! \brief This function substitutes function names in a code with namespace as prefix of the function name for backends that do not support namespaces by checking that the function indeed exists in the support code and returns the substituted code.
 */
 //--------------------------------------------------------------------------
GENN_EXPORT std::string disambiguateNamespaceFunction(const std::string supportCode, const std::string code, std::string namespaceName);

//-------------------------------------------------------------------------
/*!
  \brief Function for performing the code and value substitutions necessary to insert neuron related variables, parameters, and extraGlobal parameters into synaptic code.
*/
//-------------------------------------------------------------------------
template<typename S, typename P, typename D, typename E, typename V>
void neuronSubstitutionsInSynapticCode(CodeGenerator::Substitutions &subs, const NeuronGroupInternal *archetypeNG, 
                                       const std::string &offset, const std::string &delayOffset, 
                                       const std::string &idx, const std::string &sourceSuffix,
                                       S getSpikeTimeFn, P getParamValueFn, D getDerivedParamValueFn, E getEGPFn, V getVarFn)
{
    // Substitute spike times
    subs.addVarSubstitution("sT" + sourceSuffix, 
                            [delayOffset, idx, offset, getSpikeTimeFn](){ return "(" + delayOffset + getSpikeTimeFn() + "[" + offset + idx + "])"; });

    // Substitute neuron variables
    subs.addVarNameSubstitution<Models::Base::Var>(archetypeNG->getNeuronModel()->getVars(), 
                                                    [archetypeNG, getVarFn, idx, offset](const Models::Base::Var &var) 
                                                    { 
                                                        return getVarFn(var) + "[" + (archetypeNG->isVarQueueRequired(var.name) ? offset : "") + idx + "]";
                                                    }, 
                                                    sourceSuffix);

    // Substitute neuron model parameters, derived parameters and extra global parameters
    subs.addParamValueSubstitution(archetypeNG->getNeuronModel()->getParamNames(), 
                                    [getParamValueFn](size_t i) { return getParamValueFn(i); }, 
                                    sourceSuffix);
    subs.addVarValueSubstitution(archetypeNG->getNeuronModel()->getDerivedParams(), 
                                    [getDerivedParamValueFn](size_t i) { return getDerivedParamValueFn(i); }, 
                                    sourceSuffix);

    subs.addVarNameSubstitution<Snippet::Base::EGP>(archetypeNG->getNeuronModel()->getExtraGlobalParams(), 
                                                    [getEGPFn](const Snippet::Base::EGP &egp) { return getEGPFn(egp); },
                                                    sourceSuffix);
}

GENN_EXPORT void genKernelIndex(std::ostream &os, const Substitutions &subs, SynapseGroupMerged &sg);

}   // namespace CodeGenerator
