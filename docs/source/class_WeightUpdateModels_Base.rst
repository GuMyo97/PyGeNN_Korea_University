.. index:: pair: class; WeightUpdateModels::Base
.. _doxid-d8/d90/class_weight_update_models_1_1_base:

class WeightUpdateModels::Base
==============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Base <doxid-d8/d90/class_weight_update_models_1_1_base>` class for all weight update models. :ref:`More...<details-d8/d90/class_weight_update_models_1_1_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <weightUpdateModels.h>
	
	class Base: public :ref:`Models::Base<doxid-dc/d39/class_models_1_1_base>`
	{
	public:
		// methods
	
		virtual std::string :ref:`getSimCode<doxid-d8/d90/class_weight_update_models_1_1_base_1aff2152fb55b5b0148491ca4eed9291eb>`() const;
		virtual std::string :ref:`getEventCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a090f5529defe517fabf84c543209406f>`() const;
		virtual std::string :ref:`getLearnPostCode<doxid-d8/d90/class_weight_update_models_1_1_base_1abd6d3ec97fb1da0f5750f71c7afc09b1>`() const;
		virtual std::string :ref:`getSynapseDynamicsCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a307cb4e18479682b74972257c5d28dc5>`() const;
		virtual std::string :ref:`getEventThresholdConditionCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a3157e0e66cdc654be4ef4ad67024f84d>`() const;
		virtual std::string :ref:`getSimSupportCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a948b94c553782e9cc05a59bda014fe26>`() const;
		virtual std::string :ref:`getLearnPostSupportCode<doxid-d8/d90/class_weight_update_models_1_1_base_1af98ae8f3d545f8d66d0f80662bf5b322>`() const;
		virtual std::string :ref:`getSynapseDynamicsSuppportCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a7aae3190642d0bbe7f3f6fa01021783f>`() const;
		virtual std::string :ref:`getPreSpikeCode<doxid-d8/d90/class_weight_update_models_1_1_base_1a79e16d6c154e21a8ca7e56599cbe553b>`() const;
		virtual std::string :ref:`getPostSpikeCode<doxid-d8/d90/class_weight_update_models_1_1_base_1abb81b1a933f13ba2af62c088387e186f>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getPreVars<doxid-d8/d90/class_weight_update_models_1_1_base_1a949a9adcbc40d4ae9bbb51b2ec08dff5>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getPostVars<doxid-d8/d90/class_weight_update_models_1_1_base_1a97a0a4fb30a66bb629cd88306e659105>`() const;
		virtual bool :ref:`isPreSpikeTimeRequired<doxid-d8/d90/class_weight_update_models_1_1_base_1a86fb753d87f35b53d789f96c6189a911>`() const;
		virtual bool :ref:`isPostSpikeTimeRequired<doxid-d8/d90/class_weight_update_models_1_1_base_1ad93200ea885e60a88c108db10349edea>`() const;
		size_t :ref:`getPreVarIndex<doxid-d8/d90/class_weight_update_models_1_1_base_1ac8b3e37eeb3f0034ebba50ec01c2840e>`(const std::string& varName) const;
		size_t :ref:`getPostVarIndex<doxid-d8/d90/class_weight_update_models_1_1_base_1a5812718ff39cc394f1c6242e3d3f0987>`(const std::string& varName) const;
	};

	// direct descendants

	class :ref:`PiecewiseSTDP<doxid-db/dae/class_weight_update_models_1_1_piecewise_s_t_d_p>`;
	class :ref:`StaticGraded<doxid-d2/ddd/class_weight_update_models_1_1_static_graded>`;
	class :ref:`StaticPulse<doxid-d7/d9c/class_weight_update_models_1_1_static_pulse>`;
	class :ref:`StaticPulseDendriticDelay<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay>`;

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

.. _details-d8/d90/class_weight_update_models_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Base <doxid-d8/d90/class_weight_update_models_1_1_base>` class for all weight update models.

Methods
-------

.. index:: pair: function; getSimCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1aff2152fb55b5b0148491ca4eed9291eb:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets simulation code run when 'true' spikes are received.

.. index:: pair: function; getEventCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a090f5529defe517fabf84c543209406f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getEventCode() const

Gets code run when events (all the instances where event threshold condition is met) are received.

.. index:: pair: function; getLearnPostCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1abd6d3ec97fb1da0f5750f71c7afc09b1:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getLearnPostCode() const

Gets code to include in the learnSynapsesPost kernel/function.

For examples when modelling STDP, this is where the effect of postsynaptic spikes which occur *after* presynaptic spikes are applied.

.. index:: pair: function; getSynapseDynamicsCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a307cb4e18479682b74972257c5d28dc5:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSynapseDynamicsCode() const

Gets code for synapse dynamics which are independent of spike detection.

.. index:: pair: function; getEventThresholdConditionCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a3157e0e66cdc654be4ef4ad67024f84d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getEventThresholdConditionCode() const

Gets codes to test for events.

.. index:: pair: function; getSimSupportCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a948b94c553782e9cc05a59bda014fe26:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimSupportCode() const

Gets support code to be made available within the synapse kernel/function.

This is intended to contain user defined device functions that are used in the weight update code. Preprocessor defines are also allowed if appropriately safeguarded against multiple definition by using ifndef; functions should be declared as "\__host\__ \__device\__" to be available for both GPU and CPU versions; note that this support code is available to sim, event threshold and event code

.. index:: pair: function; getLearnPostSupportCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1af98ae8f3d545f8d66d0f80662bf5b322:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getLearnPostSupportCode() const

Gets support code to be made available within learnSynapsesPost kernel/function.

Preprocessor defines are also allowed if appropriately safeguarded against multiple definition by using ifndef; functions should be declared as "\__host\__ \__device\__" to be available for both GPU and CPU versions.

.. index:: pair: function; getSynapseDynamicsSuppportCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a7aae3190642d0bbe7f3f6fa01021783f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSynapseDynamicsSuppportCode() const

Gets support code to be made available within the synapse dynamics kernel/function.

Preprocessor defines are also allowed if appropriately safeguarded against multiple definition by using ifndef; functions should be declared as "\__host\__ \__device\__" to be available for both GPU and CPU versions.

.. index:: pair: function; getPreSpikeCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a79e16d6c154e21a8ca7e56599cbe553b:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getPreSpikeCode() const

Gets code to be run once per spiking presynaptic neuron before sim code is run on synapses

This is typically for the code to update presynaptic variables. Postsynaptic and synapse variables are not accesible from within this code

.. index:: pair: function; getPostSpikeCode
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1abb81b1a933f13ba2af62c088387e186f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getPostSpikeCode() const

Gets code to be run once per spiking postsynaptic neuron before learn post code is run on synapses

This is typically for the code to update postsynaptic variables. Presynaptic and synapse variables are not accesible from within this code

.. index:: pair: function; getPreVars
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a949a9adcbc40d4ae9bbb51b2ec08dff5:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getPreVars() const

Gets names and types (as strings) of state variables that are common across all synapses coming from the same presynaptic neuron

.. index:: pair: function; getPostVars
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a97a0a4fb30a66bb629cd88306e659105:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getPostVars() const

Gets names and types (as strings) of state variables that are common across all synapses going to the same postsynaptic neuron

.. index:: pair: function; isPreSpikeTimeRequired
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a86fb753d87f35b53d789f96c6189a911:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool isPreSpikeTimeRequired() const

Whether presynaptic spike times are needed or not.

.. index:: pair: function; isPostSpikeTimeRequired
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1ad93200ea885e60a88c108db10349edea:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool isPostSpikeTimeRequired() const

Whether postsynaptic spike times are needed or not.

.. index:: pair: function; getPreVarIndex
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1ac8b3e37eeb3f0034ebba50ec01c2840e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	size_t getPreVarIndex(const std::string& varName) const

Find the index of a named presynaptic variable.

.. index:: pair: function; getPostVarIndex
.. _doxid-d8/d90/class_weight_update_models_1_1_base_1a5812718ff39cc394f1c6242e3d3f0987:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	size_t getPostVarIndex(const std::string& varName) const

Find the index of a named postsynaptic variable.

