.. index:: pair: class; NeuronModels::Base
.. _doxid-df/d1b/class_neuron_models_1_1_base:

class NeuronModels::Base
========================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Base <doxid-df/d1b/class_neuron_models_1_1_base>` class for all neuron models. :ref:`More...<details-df/d1b/class_neuron_models_1_1_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class Base: public :ref:`Models::Base<doxid-dc/d39/class_models_1_1_base>`
	{
	public:
		// methods
	
		virtual std::string :ref:`getSimCode<doxid-df/d1b/class_neuron_models_1_1_base_1a3de4c7ff580f63c5b0ec12cb461ebd3a>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-df/d1b/class_neuron_models_1_1_base_1a00ffe96ee864dc67936ce75592c6b198>`() const;
		virtual std::string :ref:`getResetCode<doxid-df/d1b/class_neuron_models_1_1_base_1a4bdc01f203f92c2da4d3b1b48109975d>`() const;
		virtual std::string :ref:`getSupportCode<doxid-df/d1b/class_neuron_models_1_1_base_1ada27dc79296ef8368ac2c7ab20ca8c8e>`() const;
		virtual :ref:`Models::Base::ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>` :ref:`getAdditionalInputVars<doxid-df/d1b/class_neuron_models_1_1_base_1afef62c84373334fe4656a754dbb661c7>`() const;
		virtual bool :ref:`isAutoRefractoryRequired<doxid-df/d1b/class_neuron_models_1_1_base_1a32c9b73420bbdf11a373faa4e0cceb09>`() const;
	};

	// direct descendants

	class :ref:`Izhikevich<doxid-d8/dab/class_neuron_models_1_1_izhikevich>`;
	class :ref:`LIF<doxid-d2/d49/class_neuron_models_1_1_l_i_f>`;
	class :ref:`Poisson<doxid-d1/d6c/class_neuron_models_1_1_poisson>`;
	class :ref:`PoissonNew<doxid-d1/d41/class_neuron_models_1_1_poisson_new>`;
	class :ref:`RulkovMap<doxid-d3/da8/class_neuron_models_1_1_rulkov_map>`;
	class :ref:`SpikeSource<doxid-d3/d90/class_neuron_models_1_1_spike_source>`;
	class :ref:`SpikeSourceArray<doxid-dc/d9e/class_neuron_models_1_1_spike_source_array>`;
	class :ref:`TraubMiles<doxid-d6/d4a/class_neuron_models_1_1_traub_miles>`;

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

.. _details-df/d1b/class_neuron_models_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Base <doxid-df/d1b/class_neuron_models_1_1_base>` class for all neuron models.

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-df/d1b/class_neuron_models_1_1_base_1a3de4c7ff580f63c5b0ec12cb461ebd3a:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

.. index:: pair: function; getThresholdConditionCode
.. _doxid-df/d1b/class_neuron_models_1_1_base_1a00ffe96ee864dc67936ce75592c6b198:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getThresholdConditionCode() const

Gets code which defines the condition for a true spike in the described neuron model.

This evaluates to a bool (e.g. "V > 20").

.. index:: pair: function; getResetCode
.. _doxid-df/d1b/class_neuron_models_1_1_base_1a4bdc01f203f92c2da4d3b1b48109975d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getResetCode() const

Gets code that defines the reset action taken after a spike occurred. This can be empty.

.. index:: pair: function; getSupportCode
.. _doxid-df/d1b/class_neuron_models_1_1_base_1ada27dc79296ef8368ac2c7ab20ca8c8e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSupportCode() const

Gets support code to be made available within the neuron kernel/funcion.

This is intended to contain user defined device functions that are used in the neuron codes. Preprocessor defines are also allowed if appropriately safeguarded against multiple definition by using ifndef; functions should be declared as "\__host\__ \__device\__" to be available for both GPU and CPU versions.

.. index:: pair: function; getAdditionalInputVars
.. _doxid-df/d1b/class_neuron_models_1_1_base_1afef62c84373334fe4656a754dbb661c7:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`Models::Base::ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>` getAdditionalInputVars() const

Gets names, types (as strings) and initial values of local variables into which the 'apply input code' of (potentially) multiple postsynaptic input models can apply input

.. index:: pair: function; isAutoRefractoryRequired
.. _doxid-df/d1b/class_neuron_models_1_1_base_1a32c9b73420bbdf11a373faa4e0cceb09:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool isAutoRefractoryRequired() const

Does this model require auto-refractory logic?

