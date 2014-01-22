/*--------------------------------------------------------------------------
   Author: Thomas Nowotny
  
   Institute: Center for Computational Neuroscience and Robotics
              University of Sussex
	      Falmer, Brighton BN1 9QJ, UK 
  
   email to:  T.Nowotny@sussex.ac.uk
  
   initial version: 2010-02-07
  
--------------------------------------------------------------------------*/

#define DT 1
#include "modelSpec.h"
#include "modelSpec.cc"

float myPOI_p[4]= {
//POISSON neuron parameters
  1,        // 0 - firing rate
  2.5,        // 1 - refratory period
  20.0,       // 2 - Vspike
  -60.0       // 3 - Vrest
};

float myPOI_ini[4]= {
 -60.0,        // 0 - V
  0,           // 1 - seed
  -10.0       // 2 - SpikeTime
};

float exIzh_p[4]{
//Izhikevich model parameters - tonic spiking
	0.02,	// 0 - a
	0.25,	// 1 - b
	-65,	// 2 - c
	6	// 3 - d
};

float exIzh_ini[2]{
//Izhikevich model initial conditions - tonic spiking
	-65,	//0 - V
	-20	//1 - U
};

float myPNKC_p[3]= {
  0.0,           // 0 - Erev: Reversal potential
  -20.0,         // 1 - Epre: Presynaptic threshold potential
  1.0            // 2 - tau_S: decay time constant for S [ms]
};

float postExp[2]={
  1.0,            // 0 - tau_S: decay time constant for S [ms]
  0.0		  // 1 - Erev: Reversal potential
};

float gPNIzh1= 0.01;

#include "../../userproject/include/sizes.h"

void modelDefinition(NNmodel &model) 
{
  model.setName("PoissonIzh");
  model.addNeuronPopulation("PN", _NAL, POISSONNEURON, myPOI_p, myPOI_ini);
  model.addNeuronPopulation("Izh1", _NAL, IZHIKEVICH, exIzh_p, exIzh_ini);

  model.addSynapsePopulation("PNIzh1", NSYNAPSE, ALLTOALL, INDIVIDUALG, NO_DELAY, EXPDECAY, "PN", "Izh1", myPNKC_p, postExp);
  model.setSynapseG("PNIzh1", gPNIzh1);
}
