/*--------------------------------------------------------------------------
   Author: Thomas Nowotny
  
   Institute: Center for Computational Neuroscience and Robotics
              University of Sussex
	      Falmer, Brighton BN1 9QJ, UK 
  
   email to:  T.Nowotny@sussex.ac.uk
  
   initial version: 2010-02-07
  
--------------------------------------------------------------------------*/

#include <string>

//------------------------------------------------------------------------
/*! \file generateKernels.cc

  \brief Contains functions that generate code for CUDA kernels. Part of the code generation section.
*/
//-------------------------------------------------------------------------


//! Macro for a "safe" output of a parameter into generated code by essentially just adding a bracket around the parameter value in the generated code.
#define SAVEP(X) "(" << X << ")" 


//-------------------------------------------------------------------------
/*!
  \brief Function for generating the CUDA kernel that simulates all neurons in the model.

The code generated upon execution of this function is for defining GPU side global variables that will hold model state in the GPU global memory and for the actual kernel function for simulating the neurons for one time step.
*/
//-------------------------------------------------------------------------

unsigned int nt;
short *isGrpVarNeeded;

void genNeuronKernel(NNmodel &model, //!< Model description 
		     string &path,  //!< path for code output
		     ostream &mos //!< output stream for messages
		     )
{
   // write header content
  string name, s, localID;
  ofstream os;
  isGrpVarNeeded = new short[model.neuronGrpN];

  name= path + toString("/") + model.name + toString("_CODE/neuronKrnl.cc");
  os.open(name.c_str());
  
  writeHeader(os);
  // compiler/include control (include once)
  os << "#ifndef _" << model.name << "_neuronKrnl_cc" << endl;
  os << "#define _" << model.name << "_neuronKrnl_cc" << endl;
  
  // write doxygen comment
  os << "//-------------------------------------------------------------------------" << endl;
  os << "/*! \\file neuronKrnl.cc" << endl << endl;
  os << "\\brief File generated from GeNN for the model " << model.name << " containing the neuron kernel function." << endl;
  os << "*/" << endl;
  os << "//-------------------------------------------------------------------------" << endl << endl;

  // global device variables
  os << "// relevant neuron variables" << endl;
  os << "__device__ volatile unsigned int d_done;" << endl;
  for (int i= 0; i < model.neuronGrpN; i++) {
    nt= model.neuronType[i];
    isGrpVarNeeded[i] = 0;
    if (model.neuronDelaySlots[i] == 1) {
      os << "__device__ volatile unsigned int d_glbscnt" << model.neuronName[i] << ";" << endl;
      os << "__device__ volatile unsigned int d_glbSpk" << model.neuronName[i] << "[";
      os << model.neuronN[i] << "];" << endl;
    }
    else {
      os << "__device__ volatile unsigned int d_spkQuePtr" << model.neuronName[i] << ";" << endl;
      os << "__device__ volatile unsigned int d_glbscnt" << model.neuronName[i] << "[";
      os << model.neuronDelaySlots[i] << "];" << endl;
      os << "__device__ volatile unsigned int d_glbSpk" << model.neuronName[i] << "[";
      os << model.neuronN[i] * model.neuronDelaySlots[i] << "];" << endl;
    }
    if (model.neuronType[i] != POISSONNEURON) {
      for (int j= 0; j < model.inSyn[i].size(); j++) {
	os << "__device__ " << model.ftype << " d_inSyn" << model.neuronName[i] << j << "[" << model.neuronN[i] << "];";
	os << "    // summed input for neurons in grp" << model.neuronName[i] << endl;
      }
    }
    if (model.neuronNeedSt[i]) { 
      os << "__device__ volatile " << model.ftype << " d_sT" << model.neuronName[i] << "[" << model.neuronN[i] << "];" << endl;
    }
    os << endl;
  }

  //! Binary spike flag for sparse synapse sources. This is necessary for parallelisation of the synapse kernel for postsynaptic spike queue.  
  for (int i= 0; i < model.synapseGrpN; i++) {
    if ((model.synapseConnType[i] == SPARSE)&& (model.neuronN[model.synapseTarget[i]] > synapseBlkSz) && (isGrpVarNeeded[model.synapseSource[i]] == 0)) {
      os << "__device__ short d_spikeFlag" << model.neuronName[model.synapseSource[i]] << "[" << model.neuronN[model.synapseSource[i]] << "];" << endl;
      isGrpVarNeeded[model.synapseSource[i]] = 1;
    }		
  }
  
  // kernel header
  os << "__global__ void calcNeurons(" << endl;
  for (int i= 0; i < model.neuronGrpN; i++) {
    nt = model.neuronType[i];
    if (nt == POISSONNEURON) {
      // Note: Poisson neurons only used as input neurons; they do not receive any inputs
      os << "  unsigned int *d_rates" << model.neuronName[i];
      os << ", // poisson \"rates\" of grp " << model.neuronName[i] << endl;
      os << "  unsigned int offset" << model.neuronName[i];
      os << ", // poisson \"rates\" offset of grp " << model.neuronName[i] << endl;
    }
    if (model.receivesInputCurrent[i] > 1) {
      os << "  float *d_inputI" << model.neuronName[i];
      os << ", // explicit input current to grp " << model.neuronName[i] << endl;    	
    }
    for (int k= 0, l= nModels[nt].varNames.size(); k < l; k++) {
      os << "  " << nModels[nt].varTypes[k] << " *d_" << nModels[nt].varNames[k];
      os << model.neuronName[i]<< ", " << endl;
    }
  }
  
   
  for (int i=0; i< model.synapseName.size(); i++){
    int pst= model.postSynapseType[i];
    for (int k= 0, l= postSynModels[pst].varNames.size(); k < l; k++) {
      os << "  " << postSynModels[pst].varTypes[k] << " *d_" << postSynModels[pst].varNames[k];
      os << model.synapseName[i]<< ", " << endl;
    }
  }
  
  
  os << model.ftype << " t // absolute time" << endl; 
  os << ")" << endl;

  // kernel code
  os << "{" << endl;
  unsigned int neuronGridSz = model.padSumNeuronN[model.neuronGrpN - 1];
  neuronGridSz = neuronGridSz / neuronBlkSz;
  if (neuronGridSz < deviceProp[theDev].maxGridSize[1]){
    os << "  unsigned int id = " << neuronBlkSz << " * blockIdx.x + threadIdx.x;" << endl;
  }
  else {
    os << "  unsigned int id = " << neuronBlkSz << " * (blockIdx.x * " << ceil(sqrt(neuronGridSz));
    os << " + blockIdx.y) + threadIdx.x;" << endl;  	
  }
  os << "  __shared__ volatile unsigned int scnt;" << endl;
  os << "  __shared__ volatile unsigned int pos;" << endl;
  os << "  __shared__ unsigned int shSpk[" << neuronBlkSz << "];" << endl;
  os << "  unsigned int sidx;" << endl;
  os << endl;
  os << "  if (threadIdx.x == 0) scnt = 0;" << endl;
  os << "  __syncthreads();" << endl;
  
  for (int i= 0; i < model.neuronGrpN; i++) {
    nt= model.neuronType[i];
    if (i == 0) {
      os << "  if (id < " << model.padSumNeuronN[i] << ") {" << endl;
      localID = string("id");
    }
    else {
      os << "  if ((id >= " << model.padSumNeuronN[i-1] << ") && ";
      os << "(id < " << model.padSumNeuronN[i] << ")) {" << endl;
      os << "    unsigned int lid;" << endl;
      os << "    lid = id - " << model.padSumNeuronN[i-1] << ";" << endl;
      localID = string("lid");
    }
    os << "    // only do this for existing neurons" << endl;
    os << "    if (" << localID << " < " << model.neuronN[i] << ") {" << endl;
    os << "      // pull V values in a coalesced access" << endl;
    if (nt == POISSONNEURON) {
      os << "      unsigned int lrate = d_rates" << model.neuronName[i];
      os << "[offset" << model.neuronName[i] << " + " << localID << "];" << endl;
    }
    for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
      os << "      " << nModels[nt].varTypes[k] << " l" << nModels[nt].varNames[k];
      os << " = d_" <<  nModels[nt].varNames[k] << model.neuronName[i] << "[";
      if ((nModels[nt].varNames[k] == "V") && (model.neuronDelaySlots[i] != 1)) {
	os << "(((d_spkQuePtr" << model.neuronName[i] << " + " << (model.neuronDelaySlots[i] - 1) << ") % ";
	os << model.neuronDelaySlots[i] << ") * " << model.neuronN[i] << ") + ";
      }
      os << localID << "];" << endl;
    }
    if (nt != POISSONNEURON) {
      os << "      // pull inSyn values in a coalesced access" << endl;
      for (int j = 0; j < model.inSyn[i].size(); j++) {
      	os << "      " << model.ftype << " linSyn" << j << " = d_inSyn" << model.neuronName[i] << j << "[" << localID << "];" << endl;
      }
      os << "    " << model.ftype << " Isyn = 0;" << endl;
      if (isGrpVarNeeded[i]==1) {
      	os << "    d_spikeFlag" << model.neuronName[model.synapseSource[i]] << "[" << localID << "]=0;" << endl;
      }
      if (model.inSyn[i].size() > 0) {
	for (int j = 0; j < model.inSyn[i].size(); j++) {
	
	
	 for (int k = 0, l = postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames.size(); k < l; k++) {
      os << "      " << postSynModels[model.postSynapseType[model.inSyn[i][j]]].varTypes[k] << " lps" << postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k] << j;
      os << " = d_" <<  postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k] << model.synapseName[model.inSyn[i][j]] << "[";
      os << localID << "];" << endl;
    }
	
	os << "      Isyn += ";
    string psCode = postSynModels[model.postSynapseType[model.inSyn[i][j]]].postSyntoCurrent;

	substitute(psCode, tS("$(inSyn)"), tS("linSyn")+tS(j));

	for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
      substitute(psCode, tS("$(") + nModels[nt].varNames[k] + tS(")"),
		 tS("l") + nModels[nt].varNames[k]);
    }
	
	for (int k = 0, l = nModels[nt].pNames.size(); k < l; k++) {
      substitute(psCode, tS("$(") + nModels[nt].pNames[k] + tS(")"),
		 tS("l") + nModels[nt].pNames[k]);
    }
    
	for (int k = 0, l = postSynModels[model.postSynapseType[model.inSyn[i][j]]].pNames.size(); k < l; k++) {
				substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].pNames[k] + tS(")"), 
				tS(model.postSynapsePara[model.inSyn[i][j]][k]));
		 }  
		   
	for (int k = 0, l = postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames.size(); k < l; k++) {
				substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k] + tS(")"), 
				tS("lps") +tS(postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k])+tS(j));
		 }  
		 
	for (int k = 0; k < postSynModels[model.postSynapseType[model.inSyn[i][j]]].dpNames.size(); ++k)
		substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].dpNames[k] + tS(")"), tS(model.dpsp[model.inSyn[i][j]][k]));
		
	os << psCode;
      
    os << ";" << endl;
		  
	  
	  
	}
      }
    }
    if (model.receivesInputCurrent[i] == 1) { // receives constant  input
      os << "      Isyn += " << model.globalInp[i] << ";" << endl;
    }    	
    if (model.receivesInputCurrent[i] >= 2) { // receives explicit input from file
      os << "    Isyn += (" << model.ftype<< ") d_inputI" << model.neuronName[i] << "[" << localID << "];" << endl;
    } 	
    os << "      // calculate membrane potential" << endl;
    //new way of doing it
    string code = nModels[nt].simCode;
    for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
      substitute(code, tS("$(") + nModels[nt].varNames[k] + tS(")"), tS("l")+ nModels[nt].varNames[k]);
    }
    substitute(code, tS("$(Isyn)"), tS("Isyn"));
    for (int k = 0, l = nModels[nt].pNames.size(); k < l; k++) {
      substitute(code, tS("$(") + nModels[nt].pNames[k] + tS(")"), tS(model.neuronPara[i][k]));
    }
    for (int k = 0, l = nModels[nt].dpNames.size(); k < l; k++) {
      substitute(code, tS("$(") + nModels[nt].dpNames[k] + tS(")"), tS(model.dnp[i][k]));
    }
    os << code;
    if (nModels[nt].thresholdCode != tS("")) {
      code= nModels[nt].thresholdCode;
      for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].varNames[k] + tS(")"), tS("l")+ nModels[nt].varNames[k]);
      }
      substitute(code, tS("$(Isyn)"), tS("Isyn"));
      for (int k = 0, l = nModels[nt].pNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].pNames[k] + tS(")"), tS(model.neuronPara[i][k]));
      }
      for (int k = 0, l = nModels[nt].dpNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].dpNames[k] + tS(")"), tS(model.dnp[i][k]));
      }
      os << code << endl;
      os << "      if (_cond) {" << endl;
    }
    else {
      os << "      if (lV >= " << model.nThresh[i] << ") {" << endl;
    }
    os << "        // register a spike type event" << endl;
    os << "        sidx = atomicAdd((unsigned int *) &scnt, 1);" << endl;
    
    /*if ((model.synapseConnType[i]==SPARSE) && (model.neuronN[model.synapseTarget[i]] > synapseBlkSz)){
      os << "      d_spikeFlag" << model.neuronName[model.synapseSource[i]]<< "[" << localID << "]=1;" << endl;
    }*/
    os << "        shSpk[sidx] = " << localID << ";" << endl;
    if (nModels[nt].resetCode != tS("")) {
      code = nModels[nt].resetCode;
      for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].varNames[k] + tS(")"), tS("l")+ nModels[nt].varNames[k]);
      }
      substitute(code, tS("$(Isyn)"), tS("Isyn"));
      for (int k = 0, l = nModels[nt].pNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].pNames[k] + tS(")"), tS(model.neuronPara[i][k]));
      }
      for (int k = 0, l = nModels[nt].dpNames.size(); k < l; k++) {
	substitute(code, tS("$(") + nModels[nt].dpNames[k] + tS(")"), tS(model.dnp[i][k]));
      }
      os << "        // spike reset code" << endl;
      os << "        " << code << endl;
    }
    os << "      }" << endl;
    for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
      os << "      d_" << nModels[nt].varNames[k] <<  model.neuronName[i] << "[";
      if ((nModels[nt].varNames[k] == "V") && (model.neuronDelaySlots[i] != 1)) {
	os << "(d_spkQuePtr" << model.neuronName[i] << " * " << model.neuronN[i] << ") + ";
      }
      os << localID << "] = l" << nModels[nt].varNames[k] << ";" << endl;
    }
    for (int j = 0; j < model.inSyn[i].size(); j++) {
    
    string psCode = postSynModels[model.postSynapseType[model.inSyn[i][j]]].postSynDecay;

		substitute(psCode, tS("$(inSyn)"), tS("linSyn") + tS(j));
		for (int k = 0, l = postSynModels[model.postSynapseType[model.inSyn[i][j]]].pNames.size(); k < l; k++) {
			substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].pNames[k] + tS(")"), 
			tS(model.postSynapsePara[model.inSyn[i][j]][k]));
		}  
		 
		for (int k = 0, l = postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames.size(); k < l; k++) {
				substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k] + tS(")"), 
				tS("lps") +tS(postSynModels[model.postSynapseType[model.inSyn[i][j]]].varNames[k])+tS(j));
		 }  
		       
		for (int k = 0; k < postSynModels[model.postSynapseType[model.inSyn[i][j]]].dpNames.size(); ++k)
			substitute(psCode, tS("$(") + postSynModels[model.postSynapseType[model.inSyn[i][j]]].dpNames[k] + tS(")"), tS(model.dpsp[model.inSyn[i][j]][k]));
			
		for (int k = 0, l = nModels[nt].varNames.size(); k < l; k++) {
      substitute(psCode, tS("$(") + nModels[nt].varNames[k] + tS(")"),
		 tS("l") + nModels[nt].varNames[k]);
    }
	
	  for (int k = 0, l = nModels[nt].pNames.size(); k < l; k++) {
      substitute(psCode, tS("$(") + nModels[nt].pNames[k] + tS(")"),
		 tS("l") + nModels[nt].pNames[k]);
    }
    
    
     os << psCode;
     os << "      d_inSyn"  << model.neuronName[i] << j << "[" << localID << "] = linSyn"<< j << ";" << endl;
    }
    os << "    }" << endl;
    os << "    __syncthreads();" << endl;
    os << "    if (threadIdx.x == 0) {" << endl;
    os << "      pos = atomicAdd((unsigned int *) &d_glbscnt" << model.neuronName[i];
    if (model.neuronDelaySlots[i] != 1) {
      os << "[d_spkQuePtr" << model.neuronName[i] << "]";
    }
    os << ", scnt);" << endl;
    os << "    }" << endl;
    os << "    __syncthreads();" << endl;
    os << "    if (threadIdx.x < scnt) {" << endl;
    os << "      d_glbSpk" << model.neuronName[i] << "[";
    if (model.neuronDelaySlots[i] != 1) {
      os << "(d_spkQuePtr" << model.neuronName[i] << " * " << model.neuronN[i] << ") + ";
    }
    os << "pos + threadIdx.x] = shSpk[threadIdx.x];" << endl;
    if (model.neuronNeedSt[i]) {
      os << "      d_sT" << model.neuronName[i] << "[shSpk[threadIdx.x]] = t;" << endl;
    }
    os << "    }" << endl;
    os << "  }" << endl;
    os << endl;
  }
  os << "}" << endl;
  os << endl;
  os << "#endif" << endl;
  os.close();
}

//-------------------------------------------------------------------------
/*!
  \brief Function for generating a CUDA kernel for simulating all synapses.

  This functions generates code for global variables on the GPU side that are synapse-related and the actual CUDA kernel for simulating one time step of the synapses.
*/
//-------------------------------------------------------------------------

void genSynapseKernel(NNmodel &model, //!< Model description 
		      string &path, //!< Path for code output
		      ostream &mos //!< output stream for messages
		      )
{
  string name, s, localID, theLG;
  ofstream os;
  unsigned int numOfBlocks,trgN;

  // count how many neuron blocks to use: one thread for each synapse target
  // targets of several input groups are counted multiply
  numOfBlocks = model.padSumSynapseTrgN[model.synapseGrpN - 1] / synapseBlkSz;

  name = path + toString("/") + model.name + toString("_CODE/synapseKrnl.cc");
  os.open(name.c_str());
  writeHeader(os);  // write header content
  // compiler/include control (include once)
  os << "#ifndef _" << model.name << "_synapseKrnl_cc" << endl;
  os << "#define _" << model.name << "_synapseKrnl_cc" << endl;
  os << endl;

  // write doxygen comment
  os << "//-------------------------------------------------------------------------" << endl;
  os << "/*! \\file synapseKrnl.cc" << endl << endl;
  os << "\\brief File generated from GeNN for the model " << model.name;
  os << " containing the synapse kernel and learning kernel functions." << endl;
  os << "*/" << endl;
  os << "//-------------------------------------------------------------------------" << endl << endl;

  //variables for sparse matrices
  for (int i = 0; i < model.synapseGrpN; i++) {
    if (model.synapseConnType[i] == SPARSE) {
      trgN = model.neuronN[model.synapseTarget[i]];
      if (trgN > synapseBlkSz) {
	os << "__device__ volatile " << model.ftype << " d_Lg";
	os << model.synapseName[i] << "[" <<  trgN << "];" << endl;
      }
    }
  }
  os << endl;
  
  // Kernel header
  unsigned int src;
  os << "__global__ void calcSynapses(" << endl;
  for (int i = 0; i < model.synapseGrpN; i++) {
    if (model.synapseGType[i] == (INDIVIDUALG )) {
      os << " " << model.ftype << " * d_gp" << model.synapseName[i] << "," << endl;	
      if (model.synapseConnType[i] == SPARSE){
	os << " unsigned int * d_gp" << model.synapseName[i] << "_ind," << endl;
	os << " unsigned int * d_gp" << model.synapseName[i] << "_indInG," << endl;
      }
    }
    if (model.synapseGType[i] == (INDIVIDUALID )) {
      os << "  unsigned int *d_gp" << model.synapseName[i] << "," << endl;	
    }
    if (model.synapseType[i] == LEARN1SYNAPSE) {
      os << model.ftype << " * d_grawp" << model.synapseName[i] << "," << endl;
    }   	
  }
  for (int i = 0; i < model.neuronGrpN; i++) {
    nt = model.neuronType[i];
    os << "  " << nModels[nt].varTypes[0] << " *d_" << nModels[nt].varNames[0] << model.neuronName[i]; // Vm
    if (i < (model.neuronGrpN - 1) || model.needSt) os << "," << endl;
  }
  if (model.needSt) {
    os << "  " << model.ftype << " t";
  }
  os << endl << ")";
  os << endl;

  // kernel code
  os << "{" << endl;
  os << "  unsigned int id = " << synapseBlkSz << " * blockIdx.x + threadIdx.x;" << endl;
  os << "  __shared__ unsigned int shSpk[" << synapseBlkSz << "];" << endl;
  os << "  __shared__ " << model.ftype << " shSpkV[" << synapseBlkSz << "];" << endl;
  os << "  volatile __shared__ " << model.ftype << " shLg[" << neuronBlkSz << "];" << endl;
  os << "  unsigned int lscnt, numSpikeSubsets, lmax, j, p, r, ipost,npost;" << endl;
  os << "  " << model.ftype << " linSyn, lg;" << endl;
  if (model.needSynapseDelay == 1) {
    os << "  int delaySlot;" << endl;
  }
  os << endl;
  os << "  ipost = 0;" << endl;
  for (int i = 0; i < model.synapseGrpN; i++) {
    if (i == 0) {
      os << "  if (id < " << model.padSumSynapseTrgN[i] << ") { " << endl;
      localID = string("id");
    }
    else {
      os << "  if ((id >= " << model.padSumSynapseTrgN[i - 1] << ") && ";
      os << "(id < " << model.padSumSynapseTrgN[i] << ")) {" << endl;
      os << "    unsigned int lid;" << endl;
      os << "    lid = id - " << model.padSumSynapseTrgN[i - 1] << ";" << endl;
      localID = string("lid");
    }
    unsigned int trg = model.synapseTarget[i];
    unsigned int nN = model.neuronN[trg];
    src = model.synapseSource[i];
    float Epre = model.synapsePara[i][1];
    float Vslope;
    if (model.synapseType[i] == NGRADSYNAPSE) {
      Vslope = model.synapsePara[i][3]; // fails here
    }
    unsigned int inSynNo = model.synapseInSynNo[i];
    if (model.neuronDelaySlots[src] != 1) {
      os << "    delaySlot = (d_spkQuePtr" << model.neuronName[src] << " + ";
      os << (int) (model.neuronDelaySlots[src] - model.synapseDelay[i] + 1);
      os << ") % " << model.neuronDelaySlots[src] << ";" << endl;
    }
    os << "    // only do this for existing neurons" << endl;
    os << "    if (" << localID << " < " << nN <<") {" << endl;
    os << "      linSyn = d_inSyn" << model.neuronName[trg] << inSynNo << "[" << localID << "];" << endl;
    os << "    }" << endl;
    os << "    lscnt = d_glbscnt" << model.neuronName[src];
    if (model.neuronDelaySlots[src] != 1) {
      os << "[delaySlot]";
    }
    os << ";" << endl;
    os << "    numSpikeSubsets = (unsigned int) (ceilf((float) lscnt / " << synapseBlkSz << ".0f));" << endl;
    os << "    for (r = 0; r < numSpikeSubsets; r++) {" << endl;
    os << "      if (r == numSpikeSubsets - 1) lmax = lscnt % " << synapseBlkSz << ";" << endl;
    os << "      else lmax = " << synapseBlkSz << ";" << endl;
    os << "      if (threadIdx.x < lmax) {" << endl;
    os << "        shSpk[threadIdx.x] = d_glbSpk" << model.neuronName[src] << "[";
    if (model.neuronDelaySlots[src] != 1) {
      os << "(delaySlot * " << model.neuronN[src] << ") + ";
    }
    os << "(r * " << synapseBlkSz << ") + threadIdx.x];" << endl;
    if (model.neuronType[src] != POISSONNEURON) {
      os << "        shSpkV[threadIdx.x] = d_V" << model.neuronName[src] << "[";
      if (model.neuronDelaySlots[src] != 1) {
	os << "(delaySlot * " << model.neuronN[src] << ") + ";
      }
      os << "shSpk[threadIdx.x]];" << endl;
    }
    os << "      }" << endl;
    if ((model.synapseConnType[i] == SPARSE) && (model.neuronN[trg] <= synapseBlkSz)) {
      os << "        shLg[threadIdx.x] = 0;" << endl;
    }
    os << "      __syncthreads();" << endl;
    os << "      // only work on existing neurons" << endl;
    os << "      if (" << localID << " < " << model.neuronN[trg] << ") {" << endl;
    if ((model.synapseConnType[i] == SPARSE) && (model.neuronN[trg] > synapseBlkSz)) {
      os << "        d_Lg" << model.synapseName[i] << "[id]=0;" << endl; 
      //os << "          __syncthreads();" << endl; 
      os << "      __threadfence();" << endl;
    }
    os << "        // loop through all incoming spikes" << endl;
    os << "        for (j = 0; j < lmax; j++) {" << endl;
    if (model.synapseGType[i] == INDIVIDUALID) {
      os << "          unsigned int gid = (shSpk[j] * " << model.neuronN[trg];
      os << " + " << localID << ");" << endl;
    }
    if (model.neuronType[src] != POISSONNEURON) {
      os << "          if ";
      if (model.synapseGType[i] == INDIVIDUALID) {
	// Note: we will just access global mem. For compute >= 1.2
	// simultaneous access to same global mem in the (half-)warp
	// will be coalesced - no worries
	os << "((B(d_gp" << model.synapseName[i] << "[gid >> " << logUIntSz << "], gid & ";
	os << UIntSz - 1 << ")) && ";
      } 
      os << "(shSpkV[j] > " << Epre << ")";
      if (model.synapseGType[i] == INDIVIDUALID) {
	os << ")";
      }
      os << " {" << endl;
    }
    else {
      if (model.synapseGType[i] == INDIVIDUALID) {
	os << "          if (B(d_gp" << model.synapseName[i] << "[gid >> " << logUIntSz << "], gid & ";
	os << UIntSz - 1 << ")) {" << endl;
      }
    }
    if (model.synapseGType[i] == INDIVIDUALG) {
      if (model.synapseConnType[i] == SPARSE) {
	os << "          npost = d_gp" << model.synapseName[i] << "_indInG[shSpk[j] + 1] - d_gp";
	os << model.synapseName[i] << "_indInG[shSpk[j]];" << endl;
	os << "          if (id < npost) {" << endl;
	os << "            ipost = d_gp" << model.synapseName[i] << "_ind[d_gp";
	os << model.synapseName[i] << "_indInG[shSpk[j]] + id];" << endl;
	if (isGrpVarNeeded[model.synapseSource[i]] == 0) {
	  theLG = toString("shLg[" + localID + "]");
	  os << "            shLg";
	}
	else {
	  theLG = toString("d_Lg" + model.synapseName[i] + "[" + localID + "]");
	  os << "            d_Lg" << model.synapseName[i];
        }
	os << "[ipost] = d_gp" << model.synapseName[i] << "[d_gp" << model.synapseName[i] << "_indInG[shSpk[j]] + id];";
      }
      else {
        os << "            lg = d_gp" << model.synapseName[i] << "[shSpk[j]*" << model.neuronN[trg] << " + " << localID << "];";
	theLG = toString("lg");
      }
      os << endl;
    }
    if (model.synapseConnType[i] == SPARSE) { // need to close the parenthesis to synchronize threads
      os << "          }" << endl; // end if (id < npost)
      //os << "          __syncthreads();" << endl;
      os << "          __threadfence();" << endl;
    }
    if ((model.synapseGType[i] == GLOBALG) || (model.synapseGType[i] == INDIVIDUALID)) {
      theLG = toString(model.g0[i]);
    }
    if ((model.synapseType[i] == NSYNAPSE) || (model.synapseType[i] == LEARN1SYNAPSE)) {
      os << "          linSyn = linSyn + " << theLG << ";" << endl;
    }
    if (model.synapseType[i] == NGRADSYNAPSE) {
      if (model.neuronType[src] == POISSONNEURON) {
	os << "          linSyn = linSyn + " << theLG << " * tanh((";
	os << SAVEP(model.neuronPara[src][2]) << " - " << SAVEP(Epre);
      }
      else {
	os << "          linSyn = linSyn + " << theLG << " * tanh((shSpkV[j] - " << SAVEP(Epre);
      }
      os << ") / " << Vslope << ");" << endl;
    }
    if (model.synapseConnType[i] == SPARSE) {
      os << "          " << theLG << " = 0;" << endl;        	
    }
    // if needed, do some learning (this is for pre-synaptic spikes)
    if (model.synapseType[i] == LEARN1SYNAPSE) {
      // simply assume INDIVIDUALG for now
      os << "            lg = d_grawp" << model.synapseName[i] << "[shSpk[j] * " << model.neuronN[trg] << " + " << localID << "];" << endl;
      os << "            " << model.ftype << " dt = d_sT" << model.neuronName[trg] << "[" << localID << "] - t - ";
      os << SAVEP(model.synapsePara[i][11]) << ";" << endl;
      os << "            if (dt > " << model.dsp[i][1] << ") {" << endl;
      os << "              dt = - " << SAVEP(model.dsp[i][5]) << ";" << endl;
      os << "            }" << endl;
      os << "            else if (dt > 0.0) {" << endl;
      os << "              dt = " << SAVEP(model.dsp[i][3]) << " * dt + " << SAVEP(model.dsp[i][6]) << ";" << endl;
      os << "            }" << endl;
      os << "            else if (dt > " << model.dsp[i][2] << ") {" << endl;
      os << "              dt = " << SAVEP(model.dsp[i][4]) << " * dt + " << SAVEP(model.dsp[i][6]) << ";" << endl;
      os << "            }" << endl;
      os << "            else {" << endl;
      os << "              dt = - " << SAVEP(model.dsp[i][7]) << ";" << endl;
      os << "            }" << endl;
      os << "            lg = lg + dt;" << endl;
      os << "            d_grawp" << model.synapseName[i] << "[shSpk[j] * " << model.neuronN[trg] << " + " << localID << "] = lg;" << endl;
      os << "            d_gp" << model.synapseName[i] << "[shSpk[j] * " << model.neuronN[trg] << " + " << localID << "] = ";
      os << "gFunc" << model.synapseName[i] << "(lg);" << endl; 
    }
    if (model.synapseConnType[i] != SPARSE) {
      if ((model.neuronType[src] != POISSONNEURON) || (model.synapseGType[i] == INDIVIDUALID)) {
        os << "          }" << endl;
      }
    }
    os << "        }" << endl;
    //os << "      __syncthreads();" << endl;
    os << "      }" << endl;
    os << "    }" << endl;
    os << "    // only do this for existing neurons" << endl;
    /*if (model.synapseConnType[i] == SPARSE) {
      os << "    if (" << localID << " == ipost) {" << endl;
      os << "      d_inSyn" << model.neuronName[trg] << inSynNo << "[ipost] = linSyn;" << endl;
    }
    else{*/
    os << "    if (" << localID << " < " << model.neuronN[trg] <<") {" << endl;
    os << "      d_inSyn" << model.neuronName[trg] << inSynNo << "[" << localID << "] = linSyn;" << endl;
    //}    
    os << "    }" << endl;
    if (model.lrnGroups == 0) {
      os << "    __syncthreads();" << endl;
      os << "    if (threadIdx.x == 0) {" << endl;
      os << "      j = atomicAdd((unsigned int *) &d_done, 1);" << endl;
      os << "      if (j == " << numOfBlocks - 1 << ") {" << endl;
      for (int j = 0; j < model.neuronGrpN; j++) {
	if (model.neuronDelaySlots[j] != 1) {
	  os << "        d_spkQuePtr" << model.neuronName[j] << " = (d_spkQuePtr";
	  os << model.neuronName[j] << " + 1) % " << model.neuronDelaySlots[j] << ";" << endl;
	  os << "        d_glbscnt" << model.neuronName[j] << "[d_spkQuePtr";
	  os << model.neuronName[j] << "] = 0;" << endl;
	}
	else {
	  os << "        d_glbscnt" << model.neuronName[j] << " = 0;" << endl;
	}
      }
      os << "        d_done = 0;" << endl;
      os << "      }" << endl;
      os << "    }" << endl;
    }
    os << "  }" << endl;
    os << endl;
  }
  os << "}" << endl;
  os << endl;


  ///////////////////////////////////////////////////////////////
  // Kernel for learning synapses, post-synaptic spikes

  if (model.lrnGroups > 0) {

    // count how many learn blocks to use: one thread for each synapse source
    // sources of several output groups are counted multiply
    numOfBlocks = model.padSumLearnN[model.lrnGroups - 1] / learnBlkSz;

    // Kernel header
    os << "__global__ void learnSynapsesPost(" << endl;
    for (int i = 0; i < model.synapseGrpN; i++) {
      if (model.synapseGType[i] == (INDIVIDUALG )) {
	os << "  " << model.ftype << " *d_gp" << model.synapseName[i] << "," << endl;	
      }
      if (model.synapseGType[i] == (INDIVIDUALID )) {
	os << "  unsigned int *d_gp" << model.synapseName[i] << "," << endl;	
      }
      if (model.synapseType[i] == LEARN1SYNAPSE) {
	os << "  " << model.ftype << " *d_grawp"  << model.synapseName[i] << "," << endl;
      }
    }
    for (int i = 0; i < model.neuronGrpN; i++) {
      nt = model.neuronType[i];
      os << nModels[nt].varTypes[0] << " *d_" << nModels[nt].varNames[0] << model.neuronName[i] << ","; // Vm
    }
    os << "  " << model.ftype << " t" << endl;
    os << ")" << endl;

    // kernel code
    os << "{" << endl;
    os << "  unsigned int id = " << learnBlkSz << " * blockIdx.x + threadIdx.x;" << endl;
    os << "  __shared__ unsigned int shSpk[" << learnBlkSz << "];" << endl;
    os << "  __shared__ " << model.ftype << " shSpkV[" << learnBlkSz << "];" << endl;
    os << "  unsigned int lscnt, numSpikeSubsets, lmax, j, r;" << endl;
    os << "  " << model.ftype << " lg;" << endl;
    os << endl;

    for (int i = 0; i < model.lrnGroups; i++) {
      if (i == 0) {
	os << "  if (id < " << model.padSumLearnN[i] << ") {" << endl;
	localID = string("id");
      }
      else {
	os << "  if ((id >= " << model.padSumLearnN[i - 1] << ") && ";
	os << "(id < " << model.padSumLearnN[i] << ")) {" << endl;
	os << "    unsigned int lid;" << endl;
	os << "    lid = id - " << model.padSumLearnN[i - 1] << ";" << endl;
	localID = string("lid");
      }
      unsigned int k = model.lrnSynGrp[i];
      unsigned int src = model.synapseSource[k];
      unsigned int nN = model.neuronN[src];
      unsigned int trg = model.synapseTarget[k];
      float Epre = model.synapsePara[k][1];

      os << "    lscnt = d_glbscnt" << model.neuronName[trg];
      if (model.neuronDelaySlots[trg] != 1) os << "[d_spkQuePtr" << model.neuronName[trg] << "]";
      os << ";" << endl;
      os << "    numSpikeSubsets = (unsigned int) (ceilf((float) lscnt / " << learnBlkSz << ".0f));" << endl;
      os << "    for (r = 0; r < numSpikeSubsets; r++) {" << endl;
      os << "      if (r == numSpikeSubsets - 1) lmax = lscnt % " << learnBlkSz << ";" << endl;
      os << "      else lmax = " << learnBlkSz << ";" << endl;
      os << "      if (threadIdx.x < lmax) {" << endl;
      os << "        shSpk[threadIdx.x] = d_glbSpk" << model.neuronName[trg] << "[";
      if (model.neuronDelaySlots[trg] != 1) {
	os << "(d_spkQuePtr" << model.neuronName[trg] << " * " << model.neuronN[trg] << ") + ";
      }
      os << "(r * " << learnBlkSz << ") + threadIdx.x];" << endl;
      os << "        shSpkV[threadIdx.x] = d_V" << model.neuronName[trg] << "[";
      if (model.neuronDelaySlots[trg] != 1) {
	os << "(d_spkQuePtr" << model.neuronName[trg] << " * " << model.neuronN[trg] << ") + ";
      }
      os << "shSpk[threadIdx.x]];" << endl;
      os << "      }" << endl;
      os << "      __syncthreads();" << endl;
      os << "      // only work on existing neurons" << endl;
      os << "      if (" << localID << " < " << model.neuronN[src] << ") {" << endl;
      os << "        // loop through all incoming spikes" << endl;
      os << "        for (j = 0; j < lmax; j++) {" << endl;
      os << "          if (shSpkV[j] > " << Epre << ") {" << endl;
      os << "            lg = d_grawp" << model.synapseName[k] << "[" << localID << " * ";
      os << model.neuronN[trg] << " + shSpk[j]];" << endl;
      os << "            " << model.ftype << " dt = t - d_sT" << model.neuronName[src] << "[" << localID << "]";
      if (model.neuronDelaySlots[src] != 1) {
	os << " + " << (DT * model.synapseDelay[k]);
      }
      os << " - " << SAVEP(model.synapsePara[k][11]) << ";" << endl;
      os << "            if (dt > " << model.dsp[k][1] << ") {" << endl;
      os << "              dt = - " << SAVEP(model.dsp[k][5]) << ";" << endl;
      os << "            }" << endl;
      os << "            else if (dt > 0.0) {" << endl;
      os << "              dt = " << SAVEP(model.dsp[k][3]) << " * dt + " << SAVEP(model.dsp[k][6]) << ";" << endl;
      os << "            }" << endl;
      os << "            else if (dt > " << model.dsp[k][2] << ") {" << endl;
      os << "              dt = " << SAVEP(model.dsp[k][4]) << " * dt + " << SAVEP(model.dsp[k][6]) << ";" << endl;
      os << "            }" << endl;
      os << "            else {" << endl;
      os << "              dt = - " << SAVEP(model.dsp[k][7]) << ";" << endl;
      os << "            }" << endl;
      os << "            lg = lg + dt;" << endl;
      os << "            d_grawp" << model.synapseName[k] << "[" << localID << " * ";
      os << model.neuronN[trg] << " + shSpk[j]] = lg;" << endl;
      os << "            d_gp" << model.synapseName[k] << "[" << localID << " * ";
      os << model.neuronN[trg] << " + shSpk[j]] = gFunc" << model.synapseName[k] << "(lg);" << endl; 
      os << "          }" << endl;
      os << "        }" << endl;
      os << "      }" << endl;
      os << "    }" << endl;
      os << "    __syncthreads();" << endl;
      os << "    if (threadIdx.x == 0) {" << endl;
      os << "      j = atomicAdd((unsigned int *) &d_done, 1);" << endl;
      os << "      if (j == " << numOfBlocks - 1 << ") {" << endl;
      for (int j = 0; j < model.neuronGrpN; j++) {
	if (model.neuronDelaySlots[j] != 1) {
	  os << "        d_spkQuePtr" << model.neuronName[j] << " = (d_spkQuePtr";
	  os << model.neuronName[j] << " + 1) % " << model.neuronDelaySlots[j] << ";" << endl;
	  os << "        d_glbscnt" << model.neuronName[j] << "[d_spkQuePtr";
	  os << model.neuronName[j] << "] = 0;" << endl;
	}
	else {
	  os << "        d_glbscnt" << model.neuronName[j] << " = 0;" << endl;
	}
      }
      os << "        d_done = 0;" << endl;
      os << "      }" << endl;
      os << "    }" << endl;
      os << "  }" << endl;
    }
    os << "}" << endl;
  }
  os << endl;
  os << "#endif" << endl;
  os.close();
}
