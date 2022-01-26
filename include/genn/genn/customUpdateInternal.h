#pragma once

// GeNN includes
#include "customUpdate.h"

//------------------------------------------------------------------------
// CustomUpdateInternal
//------------------------------------------------------------------------
class CustomUpdateInternal : public CustomUpdate
{
public:
    CustomUpdateInternal(const std::string &name, const std::string &updateGroupName,
                         const CustomUpdateModels::Base *customUpdateModel, const std::unordered_map<std::string, double> &params, 
                         const std::unordered_map<std::string, Models::VarInit> &varInitialisers, const std::unordered_map<std::string, Models::VarReference> &varReferences, 
                         VarLocation defaultVarLocation, VarLocation defaultExtraGlobalParamLocation)
    :   CustomUpdate(name, updateGroupName, customUpdateModel, params, varInitialisers, varReferences, 
                     defaultVarLocation, defaultExtraGlobalParamLocation)
    {
    }

    using CustomUpdateBase::initDerivedParams;
    using CustomUpdateBase::getDerivedParams;
    using CustomUpdateBase::isInitRNGRequired;
    using CustomUpdateBase::isZeroCopyEnabled;
    using CustomUpdateBase::isBatched;
    using CustomUpdateBase::isReduction;
    using CustomUpdateBase::getRunnerHashDigest;
    using CustomUpdateBase::getVarLocationHashDigest;

    using CustomUpdate::finalize;
    using CustomUpdate::getHashDigest;
    using CustomUpdate::getInitHashDigest;
    using CustomUpdate::getDelayNeuronGroup;
};

//------------------------------------------------------------------------
// CustomUpdateInternal
//------------------------------------------------------------------------
class CustomUpdateWUInternal : public CustomUpdateWU
{
public:
    CustomUpdateWUInternal(const std::string &name, const std::string &updateGroupName,
                           const CustomUpdateModels::Base *customUpdateModel, const std::unordered_map<std::string, double> &params, 
                           const std::unordered_map<std::string, Models::VarInit> &varInitialisers, const std::unordered_map<std::string, Models::WUVarReference> &varReferences, 
                           VarLocation defaultVarLocation, VarLocation defaultExtraGlobalParamLocation)
    :   CustomUpdateWU(name, updateGroupName, customUpdateModel, params, varInitialisers, varReferences, 
                       defaultVarLocation, defaultExtraGlobalParamLocation)
    {
    }

    using CustomUpdateBase::initDerivedParams;
    using CustomUpdateBase::getDerivedParams;
    using CustomUpdateBase::isInitRNGRequired;
    using CustomUpdateBase::isZeroCopyEnabled;
    using CustomUpdateBase::isBatched;
    using CustomUpdateBase::isReduction;
    using CustomUpdateBase::getRunnerHashDigest;
    using CustomUpdateBase::getVarLocationHashDigest;
    
    using CustomUpdateWU::getHashDigest;
    using CustomUpdateWU::getInitHashDigest;    
    using CustomUpdateWU::getSynapseGroup;
    using CustomUpdateWU::isTransposeOperation;
};
