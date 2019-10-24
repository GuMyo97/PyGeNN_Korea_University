#include "gennUtils.h"

// Standard C++ includes
#include <algorithm>

// PLOG includes
#include <plog/Log.h>

namespace
{
//--------------------------------------------------------------------------
// GenericFunction
//--------------------------------------------------------------------------
//! Immutable structure for specifying the name and number of
//! arguments of a generic funcion e.g. gennrand_uniform
struct GenericFunction
{
    //! Generic name used to refer to function in user code
    const std::string genericName;

    //! Number of function arguments
    const unsigned int numArguments;
};


GenericFunction randomFuncs[] = {
    {"gennrand_uniform", 0},
    {"gennrand_normal", 0},
    {"gennrand_exponential", 0},
    {"gennrand_log_normal", 2},
    {"gennrand_gamma", 1}
};
}

//--------------------------------------------------------------------------
// Utils
//--------------------------------------------------------------------------
namespace Utils
{
bool isRNGRequired(const std::string &code)
{
    // Loop through random functions
    for(const auto &r : randomFuncs) {
        // If this function takes no arguments, return true if
        // generic function name enclosed in $() markers is found
        if(r.numArguments == 0) {
            if(code.find("$(" + r.genericName + ")") != std::string::npos) {
                return true;
            }
        }
        // Otherwise, return true if generic function name
        // prefixed by $( and suffixed with comma is found
        else if(code.find("$(" + r.genericName + ",") != std::string::npos) {
            return true;
        }
    }
    return false;

}
//--------------------------------------------------------------------------
bool isInitRNGRequired(const std::vector<Models::VarInit> &varInitialisers)
{
    // Return true if any of these variable initialisers require an RNG
    return std::any_of(varInitialisers.cbegin(), varInitialisers.cend(),
                       [](const Models::VarInit &varInit)
                       {
                           return isRNGRequired(varInit.getSnippet()->getCode());
                       });
}
//--------------------------------------------------------------------------
void autoDetermineImplementation(const std::vector<Models::VarInit> &initialisers, const Models::Base::VarVec &vars,
                                 std::vector<VarImplementation> &implementations)
{
    // Reserve implementations vector
    implementations.reserve(initialisers.size()),

    // Implement varaibles that are read only and constant as GLOBAL and others as individual
    std::transform(initialisers.cbegin(), initialisers.cend(), vars.cbegin(), std::back_inserter(implementations),
                   [](const Models::VarInit &varInit, const Models::Base::Var &var)
                   {
                       if(var.access == VarAccess::READ_ONLY && varInit.isConstant()) {
                           LOGD << "Defaulting variable '" << var.name << "' to GLOBAL implementation";
                           return VarImplementation::GLOBAL;
                       }
                       else {
                           LOGD << "Defaulting variable '" << var.name << "' to INDIVIDUAL implementation";
                           return VarImplementation::INDIVIDUAL;
                       }
                   });
}
//--------------------------------------------------------------------------
bool isTypePointer(const std::string &type)
{
    return (type.back() == '*');
}
//--------------------------------------------------------------------------
std::string getUnderlyingType(const std::string &type)
{
    // Check that type is a pointer type
    assert(isTypePointer(type));

    // Return string without last character
    return type.substr(0, type.length() - 1);
}
}   // namespace utils
