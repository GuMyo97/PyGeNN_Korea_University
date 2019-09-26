.. index:: pair: class; NeuronModels::RulkovMap
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map:

class NeuronModels::RulkovMap
=============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Rulkov Map neuron. :ref:`More...<details-d3/da8/class_neuron_models_1_1_rulkov_map>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronModels.h>
	
	class RulkovMap: public :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<4> :target:`ParamValues<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1ab78959f43ae5b4e46c9a0be793f4bacc>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<2> :target:`VarValues<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1accfe1383d9c7816d0b9163d28a8edd19>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a9f4f6a5071fe21306d101838e04fd220>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a29e31ae2d2fbfe736f7e05f9f4c5bfc1>`;

		// methods
	
		static const NeuronModels::RulkovMap* :target:`getInstance<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1aa738f74b47ff1be4dc9c9d21cbd77906>`();
		virtual std::string :ref:`getSimCode<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a54bf2e930d391bd5989845beb75b0757>`() const;
		virtual std::string :ref:`getThresholdConditionCode<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a35d4a3c3421f16e513c463d74132c2ad>`() const;
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1abb0d6b2673bd56d4f11822e4b56b9342>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a4b38f779fbd61198a040d1aba3b17159>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1aa505830a548e3e112da9bd8cf09aec0e>`() const;
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

.. _details-d3/da8/class_neuron_models_1_1_rulkov_map:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Rulkov Map neuron.

The :ref:`RulkovMap <doxid-d3/da8/class_neuron_models_1_1_rulkov_map>` type is a map based neuron model based on :ref:`Rulkov2002 <doxid-d0/de3/citelist_1CITEREF_Rulkov2002>` but in the 1-dimensional map form used in :ref:`nowotny2005self <doxid-d0/de3/citelist_1CITEREF_nowotny2005self>` :

.. math::

	\begin{eqnarray*} V(t+\Delta t) &=& \left\{ \begin{array}{ll} V_{\rm spike} \Big(\frac{\alpha V_{\rm spike}}{V_{\rm spike}-V(t) \beta I_{\rm syn}} + y \Big) & V(t) \leq 0 \\ V_{\rm spike} \big(\alpha+y\big) & V(t) \leq V_{\rm spike} \big(\alpha + y\big) \; \& \; V(t-\Delta t) \leq 0 \\ -V_{\rm spike} & {\rm otherwise} \end{array} \right. \end{eqnarray*}

The ``:ref:`RulkovMap <doxid-d3/da8/class_neuron_models_1_1_rulkov_map>``` type only works as intended for the single time step size of ``DT`` = 0.5.

The ``:ref:`RulkovMap <doxid-d3/da8/class_neuron_models_1_1_rulkov_map>``` type has 2 variables:

* ``V`` - the membrane potential

* ``preV`` - the membrane potential at the previous time step

and it has 4 parameters:

* ``Vspike`` - determines the amplitude of spikes, typically -60mV

* ``alpha`` - determines the shape of the iteration function, typically :math:`\alpha` = 3

* ``y`` - "shift / excitation" parameter, also determines the iteration function,originally, y= -2.468

* ``beta`` - roughly speaking equivalent to the input resistance, i.e. it regulates the scale of the input into the neuron, typically :math:`\beta` = 2.64 :math:`{\rm M}\Omega`.

The initial values array for the ``:ref:`RulkovMap <doxid-d3/da8/class_neuron_models_1_1_rulkov_map>``` type needs two entries for ``V`` and ``Vpre`` and the parameter array needs four entries for ``Vspike``, ``alpha``, ``y`` and ``beta``, *in that order*.

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a54bf2e930d391bd5989845beb75b0757:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets the code that defines the execution of one timestep of integration of the neuron model.

The code will refer to  for the value of the variable with name "NN". It needs to refer to the predefined variable "ISYN", i.e. contain , if it is to receive input.

.. index:: pair: function; getThresholdConditionCode
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a35d4a3c3421f16e513c463d74132c2ad:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getThresholdConditionCode() const

Gets code which defines the condition for a true spike in the described neuron model.

This evaluates to a bool (e.g. "V > 20").

.. index:: pair: function; getParamNames
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1abb0d6b2673bd56d4f11822e4b56b9342:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getVars
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1a4b38f779fbd61198a040d1aba3b17159:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

.. index:: pair: function; getDerivedParams
.. _doxid-d3/da8/class_neuron_models_1_1_rulkov_map_1aa505830a548e3e112da9bd8cf09aec0e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` getDerivedParams() const

Gets names of derived model parameters and the function objects to call to Calculate their value from a vector of model parameter values

