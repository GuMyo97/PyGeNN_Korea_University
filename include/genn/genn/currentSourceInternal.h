#pragma once

// GeNN includes
#include "currentSource.h"

//------------------------------------------------------------------------
// GeNN::CurrentSourceInternal
//------------------------------------------------------------------------
namespace GeNN
{
class CurrentSourceInternal : public CurrentSource
{
public:
    CurrentSourceInternal(const std::string &name, const CurrentSourceModels::Base *currentSourceModel,
                          const std::unordered_map<std::string, double> &params, const std::unordered_map<std::string, Models::VarInit> &varInitialisers,
                          const NeuronGroupInternal *targetNeuronGroup, VarLocation defaultVarLocation, 
                          VarLocation defaultExtraGlobalParamLocation)
    :   CurrentSource(name, currentSourceModel, params, varInitialisers, targetNeuronGroup, 
                      defaultVarLocation, defaultExtraGlobalParamLocation)
    {
    }

    using CurrentSource::getTrgNeuronGroup;
    using CurrentSource::initDerivedParams;
    using CurrentSource::getDerivedParams;
    using CurrentSource::isSimRNGRequired;
    using CurrentSource::isInitRNGRequired;
    using CurrentSource::isZeroCopyEnabled;
    using CurrentSource::getHashDigest;
    using CurrentSource::getInitHashDigest;
    using CurrentSource::getVarLocationHashDigest;
};

//----------------------------------------------------------------------------
// CurrentSourceVarAdapter
//----------------------------------------------------------------------------
class CurrentSourceVarAdapter
{
public:
    CurrentSourceVarAdapter(const CurrentSourceInternal &cs) : m_CS(cs)
    {}

    //----------------------------------------------------------------------------
    // Public methods
    //----------------------------------------------------------------------------
    VarLocation getVarLocation(const std::string &varName) const{ return m_CS.getVarLocation(varName); }

    Models::Base::VarVec getVars() const{ return m_CS.getCurrentSourceModel()->getVars(); }

    const std::unordered_map<std::string, Models::VarInit> &getVarInitialisers() const{ return m_CS.getVarInitialisers(); }

private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    const CurrentSourceInternal &m_CS;
};

//----------------------------------------------------------------------------
// CurrentSourceEGPAdapter
//----------------------------------------------------------------------------
class CurrentSourceEGPAdapter
{
public:
    CurrentSourceEGPAdapter(const CurrentSourceInternal &cs) : m_CS(cs)
    {}

    //----------------------------------------------------------------------------
    // Public methods
    //----------------------------------------------------------------------------
    VarLocation getEGPLocation(const std::string &varName) const{ return m_CS.getExtraGlobalParamLocation(varName); }

    Snippet::Base::EGPVec getEGPs() const{ return m_CS.getCurrentSourceModel()->getExtraGlobalParams(); }

private:
    //----------------------------------------------------------------------------
    // Members
    //----------------------------------------------------------------------------
    const CurrentSourceInternal &m_CS;
};
}   // namespace GeNN
