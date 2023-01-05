#include "postsynapticModels.h"

using namespace GeNN;

namespace GeNN::PostsynapticModels
{
// Implement models
IMPLEMENT_SNIPPET(ExpCurr);
IMPLEMENT_SNIPPET(ExpCond);
IMPLEMENT_SNIPPET(DeltaCurr);

//----------------------------------------------------------------------------
// GeNN::PostsynapticModels::Base
//----------------------------------------------------------------------------
boost::uuids::detail::sha1::digest_type Base::getHashDigest() const
{
    // Superclass
    boost::uuids::detail::sha1 hash;
    Models::Base::updateHash(hash);

    Utils::updateHash(getDecayCode(), hash);
    Utils::updateHash(getApplyInputCode(), hash);
    Utils::updateHash(getSupportCode(), hash);
    return hash.get_digest();
}
//----------------------------------------------------------------------------
void Base::validate(const std::unordered_map<std::string, double> &paramValues, 
                    const std::unordered_map<std::string, Models::VarInit> &varValues,
                    const std::string &description) const
{
    // Superclass
    Models::Base::validate(paramValues, varValues, description);

    const auto vars = getVars();
    if(std::any_of(vars.cbegin(), vars.cend(),
                   [](const Models::Base::Var &v){ return (v.access & VarAccessModeAttribute::REDUCE); }))
    {
        throw std::runtime_error("Postsynaptic models cannot include variables with REDUCE access modes - they are only supported by custom update models");
    }
}
}   // namespace GeNN::PostsynapticModels