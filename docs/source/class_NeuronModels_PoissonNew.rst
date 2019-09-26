.. index:: pair: class; NeuronModels::PoissonNew
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new:

class NeuronModels::PoissonNew
==============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>` neurons. :ref:`More...<details-d1/d41/class_neuron_models_1_1_poisson_new>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class PoissonNew: public :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<1> :target:`ParamValues<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a9ad6559238cc1d3666f74eed991cbdaf>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<1> :target:`VarValues<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a08eff4c0f7dffa1f2b217021939de595>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a403ea9362701828bade7119ca8767204>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1ab36c7c3db9a0b3751ebabb1c5ccbf063>`;

		// methods
	
		static const NeuronModels::PoissonNew* :target:`getInstance<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a79b0a6d08ae5effb4f1f4b3657e41d10>`();
		virtual std::string :ref:`getSimCode<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a0f06f9a277e7ce434a66220ca16fd2fb>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a520cf35fdff7dacca888d18eafcc5d3e>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1adffa087f5ef9119034afe192b208dd94>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a9f0134631c2af3687274f432b19ad646>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1ab880c13caef654859997b9944412fe65>`() const;
		:target:`SET_NEEDS_AUTO_REFRACTORY<doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a82cca47654bf8275dbb9c8748ecfff9f>`(false);
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// typedefs
	
		typedef std::vector<std::string> :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>`;
		typedef std::vector<:ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`> :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>`;
		typedef std::vector<:ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`> :ref:`ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>`;
		typedef std::vector<:ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`> :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>`;
		typedef std::vector<:ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`> :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>`;

		// structs
	
		struct :ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`;
		struct :ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`;
		struct :ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`;
		struct :ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`;

		// methods
	
		virtual :ref:`~Base<doxid-d6/df7/class_snippet_1_1_base_1a17a9ca158277401f2c190afb1e791d1f>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-dc/d39/class_models_1_1_base_1a9df8ba9bf6d971a574ed4745f6cf946c>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-dc/d39/class_models_1_1_base_1a7fdddb7d19382736b330ade62c441de1>`() const;
		size_t :ref:`getVarIndex<doxid-dc/d39/class_models_1_1_base_1afa0e39df5002efc76448e180f82825e4>`(const std::string& varName) const;
		size_t :ref:`getExtraGlobalParamIndex<doxid-dc/d39/class_models_1_1_base_1ae046c19ad56dfb2808c5f4d2cc7475fe>`(const std::string& paramName) const;
		virtual std::string :ref:`getSimCode<doxid-df/d1b/class_neuron_models_1_1_base_1a3de4c7ff580f63c5b0ec12cb461ebd3a>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-df/d1b/class_neuron_models_1_1_base_1a00ffe96ee864dc67936ce75592c6b198>`() const;
		virtual std::string :ref:`getResetCode<doxid-df/d1b/class_neuron_models_1_1_base_1a4bdc01f203f92c2da4d3b1b48109975d>`() const;
		virtual std::string :ref:`getSupportCode<doxid-df/d1b/class_neuron_models_1_1_base_1ada27dc79296ef8368ac2c7ab20ca8c8e>`() const;
		virtual :ref:`Models::Base::ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>` :ref:`getAdditionalInputVars<doxid-df/d1b/class_neuron_models_1_1_base_1afef62c84373334fe4656a754dbb661c7>`() const;
		virtual bool :ref:`isAutoRefractoryRequired<doxid-df/d1b/class_neuron_models_1_1_base_1a32c9b73420bbdf11a373faa4e0cceb09>`() const;

.. _details-d1/d41/class_neuron_models_1_1_poisson_new:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>` neurons.

It has 1 state variable:

* ``timeStepToSpike`` - Number of timesteps to next spike

and 1 parameter:

* ``rate`` - Mean firing rate (Hz)

Internally this samples from the exponential distribution using the C++ 11 <random> library on the CPU and by transforming the uniform distribution, generated using cuRAND, with a natural log on the GPU.

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a0f06f9a277e7ce434a66220ca16fd2fb:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

.. index:: pair: function; getThresholdConditionCode
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a520cf35fdff7dacca888d18eafcc5d3e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getThresholdConditionCode() const

Gets code which defines the condition for a true spike in the described neuron model.

This evaluates to a bool (e.g. "V > 20").

.. index:: pair: function; getParamNames
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new_1adffa087f5ef9119034afe192b208dd94:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getVars
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new_1a9f0134631c2af3687274f432b19ad646:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

.. index:: pair: function; getDerivedParams
.. _doxid-d1/d41/class_neuron_models_1_1_poisson_new_1ab880c13caef654859997b9944412fe65:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` getDerivedParams() const

Gets names of derived model parameters and the function objects to call to Calculate their value from a vector of model parameter values

