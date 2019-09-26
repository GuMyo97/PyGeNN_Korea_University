.. index:: pair: class; NeuronModels::TraubMilesFast
.. _doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast:

class NeuronModels::TraubMilesFast
==================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Hodgkin-Huxley neurons with Traub & Miles algorithm: Original fast implementation, using 25 inner iterations. :ref:`More...<details-d2/dfb/class_neuron_models_1_1_traub_miles_fast>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class TraubMilesFast: public :ref:`NeuronModels::TraubMiles<doxid-d6/d4a/class_neuron_models_1_1_traub_miles>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<7> :target:`ParamValues<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1abed1cf119d8eff6694849c002bf81edf>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<4> :target:`VarValues<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1a02541b2343ee4007ece237fbe0d1b065>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1a15dc3fa6a491ea4c1220bef255d01d4b>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1a956f2e392e55f5d880e8dea744acf191>`;

		// methods
	
		static const NeuronModels::TraubMilesFast* :target:`getInstance<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1aed98055a1191523a1680f998f39460f5>`();
		virtual std::string :ref:`getSimCode<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1a730858391f8529759644bb3c74950922>`() const;
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
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<7> :ref:`ParamValues<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a968f4e8ff125d312cf760d36f0dee95e>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<4> :ref:`VarValues<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a8ec817cdd9f7bbf5432ffca45dcb5fd2>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :ref:`PreVarValues<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a8d8b78952c1df2ada32ce9ba9e89dba2>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :ref:`PostVarValues<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a4a2c785c6a7b36aa64026e032c0eeaea>`;

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
		static const :ref:`NeuronModels::TraubMiles<doxid-d6/d4a/class_neuron_models_1_1_traub_miles>`* :ref:`getInstance<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1ae47f72166dbcb1e55d2e07755b1526da>`();
		virtual std::string :ref:`getSimCode<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a868f03fe6e30b947586cdb6a8d29146a>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1afdc035bc1c4f29c57c589b05678d232f>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a248a2c830b67bb80cb6dbbbda57f405d>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d6/d4a/class_neuron_models_1_1_traub_miles_1a9c141ce37428493b4fdfb0f55e63d303>`() const;

.. _details-d2/dfb/class_neuron_models_1_1_traub_miles_fast:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Hodgkin-Huxley neurons with Traub & Miles algorithm: Original fast implementation, using 25 inner iterations.

There are singularities in this model, which can be easily hit in float precision

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast_1a730858391f8529759644bb3c74950922:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

