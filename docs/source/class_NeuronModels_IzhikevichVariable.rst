.. index:: pair: class; NeuronModels::IzhikevichVariable
.. _doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable:

class NeuronModels::IzhikevichVariable
======================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Izhikevich <doxid-d8/dab/class_neuron_models_1_1_izhikevich>` neuron with variable parameters :ref:`izhikevich2003simple <doxid-d0/de3/citelist_1CITEREF_izhikevich2003simple>`. :ref:`More...<details-d8/d6a/class_neuron_models_1_1_izhikevich_variable>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class IzhikevichVariable: public :ref:`NeuronModels::Izhikevich<doxid-d8/dab/class_neuron_models_1_1_izhikevich>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0> :target:`ParamValues<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a96e038918c5db3058040d60e6e67c400>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<6> :target:`VarValues<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1adbf8876ce890d29615b5f4e3bd9ac46a>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a7a76ca4abb9214d8da22bd2987906e26>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1aa35945b830120db0dddbc465f1e724fa>`;

		// methods
	
		static const NeuronModels::IzhikevichVariable* :target:`getInstance<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a69d5c6810f1bdedd118b956dfca7c7f6>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a77955c438418e0c215e31a527823c689>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a8c4a88ba3d44ca550325148203bc53ca>`() const;
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
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<4> :ref:`ParamValues<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1ae94c10cb33862aef367793f56cdbddd8>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<2> :ref:`VarValues<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1aed21c7cc4971268506c9114d17e6bf22>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :ref:`PreVarValues<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1a59bb450aa8a6e840d9445d52095c1486>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :ref:`PostVarValues<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1a674301f3dc07282505a2350217791ee0>`;

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
		static const :ref:`NeuronModels::Izhikevich<doxid-d8/dab/class_neuron_models_1_1_izhikevich>`* :ref:`getInstance<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1acf0e3e311aab815bc4d7bdf8a048239f>`();
		virtual std::string :ref:`getSimCode<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1a67669e3ef6477d221b6023c19a357960>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1af85c7d6485949e74cc766fd5860f55bc>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1a3a5d58236a09163fce623add3b1095c0>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d8/dab/class_neuron_models_1_1_izhikevich_1a4da70b0f1e24f4634b60d15e2e1c6343>`() const;

.. _details-d8/d6a/class_neuron_models_1_1_izhikevich_variable:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Izhikevich <doxid-d8/dab/class_neuron_models_1_1_izhikevich>` neuron with variable parameters :ref:`izhikevich2003simple <doxid-d0/de3/citelist_1CITEREF_izhikevich2003simple>`.

This is the same model as :ref:`Izhikevich <doxid-d8/dab/class_neuron_models_1_1_izhikevich>` but parameters are defined as "variables" in order to allow users to provide individual values for each individual neuron instead of fixed values for all neurons across the population.

Accordingly, the model has the Variables:

* ``V`` - Membrane potential

* ``U`` - Membrane recovery variable

* ``a`` - time scale of U

* ``b`` - sensitivity of U

* ``c`` - after-spike reset value of V

* ``d`` - after-spike reset value of U

and no parameters.

Methods
-------

.. index:: pair: function; getParamNames
.. _doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a77955c438418e0c215e31a527823c689:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getVars
.. _doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable_1a8c4a88ba3d44ca550325148203bc53ca:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

