.. index:: pair: class; WeightUpdateModels::StaticPulseDendriticDelay
.. _doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay:

class WeightUpdateModels::StaticPulseDendriticDelay
===================================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Pulse-coupled, static synapse with heterogenous dendritic delays. :ref:`More...<details-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <weightUpdateModels.h>
	
	class StaticPulseDendriticDelay: public :ref:`WeightUpdateModels::Base<doxid-d8/d90/class_weight_update_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0> :target:`ParamValues<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1aac18fd6b85313a3e760eb67bd70eab95>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<2> :target:`VarValues<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a03a9e1b66239db7eec37a832cc60e55b>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a4261ca4ccd5ff949fb9118e814d926af>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a05f0bb892477d28b33c974e40af5423a>`;

		// methods
	
		static const StaticPulseDendriticDelay* :target:`getInstance<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a50aec06e96f1216a92550080cc908f6f>`();
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a46604156e563a877ec76e8f85c65908b>`() const;
		virtual std::string :ref:`getSimCode<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1aea75c74a2f04439e32c9dcf5dde47e8b>`() const;
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

.. _details-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Pulse-coupled, static synapse with heterogenous dendritic delays.

No learning rule is applied to the synapse and for each pre-synaptic spikes, the synaptic conductances are simply added to the postsynaptic input variable. The model has 2 variables:

* g - conductance of scalar type

* d - dendritic delay in timesteps and no other parameters.

``sim`` code is:

.. ref-code-block:: cpp

	" $(addToInSynDelay, $(g), $(d));\n\

Methods
-------

.. index:: pair: function; getVars
.. _doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1a46604156e563a877ec76e8f85c65908b:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

.. index:: pair: function; getSimCode
.. _doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay_1aea75c74a2f04439e32c9dcf5dde47e8b:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getSimCode() const

Gets simulation code run when 'true' spikes are received.

