.. index:: pair: class; NeuronModels::Poisson
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson:

class NeuronModels::Poisson
===========================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>` neurons. :ref:`More...<details-d1/d6c/class_neuron_models_1_1_poisson>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class Poisson: public :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<4> :target:`ParamValues<doxid-d1/d6c/class_neuron_models_1_1_poisson_1af5af1f4ac77c218dd5f9503636629ca7>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<2> :target:`VarValues<doxid-d1/d6c/class_neuron_models_1_1_poisson_1ab80672183484b5121175a3d745643d70>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a362d4a49fb69448b34e29229fa244419>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a33fd8bc36ae705af6d8d4fdc528659c6>`;

		// methods
	
		static const NeuronModels::Poisson* :target:`getInstance<doxid-d1/d6c/class_neuron_models_1_1_poisson_1ac0e09d234156a43676664146348bd8c5>`();
		virtual std::string :ref:`getSimCode<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a6358f81e1eb01e319507a16cd40af331>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a81aa0f5a5a1e956dfa8ba5e182461b31>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d1/d6c/class_neuron_models_1_1_poisson_1afc4eae8217dafcb4c513fced5ed91cf9>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a2287ccc9e4e2ed221cb15931d520ba9f>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-d1/d6c/class_neuron_models_1_1_poisson_1a0e1fd99dcc61ea6b34119bef979f7d4a>`() const;
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

.. _details-d1/d6c/class_neuron_models_1_1_poisson:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>` neurons.

:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>` neurons have constant membrane potential (``Vrest``) unless they are activated randomly to the ``Vspike`` value if (t- ``SpikeTime``) > ``trefract``.

It has 2 variables:

* ``V`` - Membrane potential (mV)

* ``SpikeTime`` - Time at which the neuron spiked for the last time (ms)

and 4 parameters:

* ``trefract`` - Refractory period (ms)

* ``tspike`` - duration of spike (ms)

* ``Vspike`` - Membrane potential at spike (mV)

* ``Vrest`` - Membrane potential at rest (mV)

The initial values array for the ``:ref:`Poisson <doxid-d1/d6c/class_neuron_models_1_1_poisson>``` type needs two entries for ``V``, and ``SpikeTime`` and the parameter array needs four entries for ``therate``, ``trefract``, ``Vspike`` and ``Vrest``, *in that order*.

This model uses a linear approximation for the probability of firing a spike in a given time step of size ``DT``, i.e. the probability of firing is :math:`\lambda` times ``DT`` : :math:`p = \lambda \Delta t`. This approximation is usually very good, especially for typical, quite small time steps and moderate firing rates. However, it is worth noting that the approximation becomes poor for very high firing rates and large time steps.

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson_1a6358f81e1eb01e319507a16cd40af331:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

.. index:: pair: function; getThresholdConditionCode
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson_1a81aa0f5a5a1e956dfa8ba5e182461b31:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getThresholdConditionCode() const

Gets code which defines the condition for a true spike in the described neuron model.

This evaluates to a bool (e.g. "V > 20").

.. index:: pair: function; getParamNames
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson_1afc4eae8217dafcb4c513fced5ed91cf9:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getVars
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson_1a2287ccc9e4e2ed221cb15931d520ba9f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

.. index:: pair: function; getExtraGlobalParams
.. _doxid-d1/d6c/class_neuron_models_1_1_poisson_1a0e1fd99dcc61ea6b34119bef979f7d4a:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` getExtraGlobalParams() const

Gets names and types (as strings) of additional per-population parameters for the weight update model.

