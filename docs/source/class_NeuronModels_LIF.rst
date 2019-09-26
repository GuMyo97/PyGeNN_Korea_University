.. index:: pair: class; NeuronModels::LIF
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f:

class NeuronModels::LIF
=======================

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class LIF: public :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<7> :target:`ParamValues<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a72afa71cfddb72bd8a58a2d3a485fa4d>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<2> :target:`VarValues<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a77d46529f1b92cf61dc2cb2152e24294>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1abcaa32e32259e7a2cc983645b71f8dfb>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1aeffcbbbab2fa431e151fe80a5ac1bf6d>`;

		// methods
	
		static const LIF* :target:`getInstance<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1aa191a622a8c4b4214b6f462a51618673>`();
		virtual std::string :ref:`getSimCode<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a1d3bc9d2acbb6b3f7325be8b56f026d0>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1ae8ac7dffffa874f2102bf0430a2aba70>`() const;
		virtual std::string :ref:`getResetCode<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a02554f75b4fab413a6abf67d8e8d4595>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a15ca4c25319f85d446c6d94e336e06f6>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1ae96e604549047ef24ba8b18090eb779f>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a1cfc76222d898e94227866b319f639ff>`() const;
		:target:`SET_NEEDS_AUTO_REFRACTORY<doxid-d2/d49/class_neuron_models_1_1_l_i_f_1aa4caf6189d82eb0d4fb4891d2416af56>`(false);
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

.. _details-d2/d49/class_neuron_models_1_1_l_i_f:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a1d3bc9d2acbb6b3f7325be8b56f026d0:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

.. index:: pair: function; getThresholdConditionCode
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1ae8ac7dffffa874f2102bf0430a2aba70:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getThresholdConditionCode() const

Gets code which defines the condition for a true spike in the described neuron model.

This evaluates to a bool (e.g. "V > 20").

.. index:: pair: function; getResetCode
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a02554f75b4fab413a6abf67d8e8d4595:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getResetCode() const

Gets code that defines the reset action taken after a spike occurred. This can be empty.

.. index:: pair: function; getParamNames
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a15ca4c25319f85d446c6d94e336e06f6:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getDerivedParams
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1ae96e604549047ef24ba8b18090eb779f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` getDerivedParams() const

Gets names of derived model parameters and the function objects to call to Calculate their value from a vector of model parameter values

.. index:: pair: function; getVars
.. _doxid-d2/d49/class_neuron_models_1_1_l_i_f_1a1cfc76222d898e94227866b319f639ff:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

