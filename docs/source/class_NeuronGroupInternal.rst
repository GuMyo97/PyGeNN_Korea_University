.. index:: pair: class; NeuronGroupInternal
.. _doxid-d1/dc9/class_neuron_group_internal:

class NeuronGroupInternal
=========================

.. toctree::
	:hidden:




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronGroupInternal.h>
	
	class NeuronGroupInternal: public :ref:`NeuronGroup<doxid-df/dbc/class_neuron_group>`
	{
	public:
		// methods
	
		:target:`NeuronGroupInternal<doxid-d1/dc9/class_neuron_group_internal_1a10d1a8498a9bd91151ff1b4b3c480a95>`(
			const std::string& name,
			int numNeurons,
			const :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`* neuronModel,
			const std::vector<double>& params,
			const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& varInitialisers,
			:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` defaultVarLocation,
			:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` defaultExtraGlobalParamLocation,
			int hostID
			);
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// methods
	
		:ref:`NeuronGroup<doxid-df/dbc/class_neuron_group_1aa2b21c7c696a54bb3824c6843a0d5bb1>`(const :ref:`NeuronGroup<doxid-df/dbc/class_neuron_group>`&);
		:ref:`NeuronGroup<doxid-df/dbc/class_neuron_group_1acf9b709abcfb87f8bdc2375796aa8b78>`();
		void :ref:`setSpikeLocation<doxid-df/dbc/class_neuron_group_1a9df1df6d85dde4a46ddef63954828a95>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSpikeEventLocation<doxid-df/dbc/class_neuron_group_1a95f0660e93790ea764119002db68f706>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSpikeTimeLocation<doxid-df/dbc/class_neuron_group_1a63004d6ff9f5b2982ef401e95314d531>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setVarLocation<doxid-df/dbc/class_neuron_group_1a75951040bc142c60c4f0b5a8aa84bd57>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setExtraGlobalParamLocation<doxid-df/dbc/class_neuron_group_1a9f54ec7c3dbf68196a62c2c953eeccd4>`(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		const std::string& :ref:`getName<doxid-df/dbc/class_neuron_group_1a78241745e3b1b183676b02ecf4707bae>`() const;
		unsigned int :ref:`getNumNeurons<doxid-df/dbc/class_neuron_group_1abe4b16b1d80aeedfd008113b391173c3>`() const;
		const :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`* :ref:`getNeuronModel<doxid-df/dbc/class_neuron_group_1a30e77db7fede6ab000ed7d2dafee86b4>`() const;
		const std::vector<double>& :ref:`getParams<doxid-df/dbc/class_neuron_group_1a2415c5beaf394c6b89092398848be743>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getVarInitialisers<doxid-df/dbc/class_neuron_group_1a18b1d7a0c40284c03f70f520144839ec>`() const;
		int :ref:`getClusterHostID<doxid-df/dbc/class_neuron_group_1a404eda44aa75eea5658de671fe7e3d9c>`() const;
		bool :ref:`isSpikeTimeRequired<doxid-df/dbc/class_neuron_group_1a1f6734b170767ad67fe7c3eb139923b1>`() const;
		bool :ref:`isTrueSpikeRequired<doxid-df/dbc/class_neuron_group_1a171555a1b0120e2fcb48eda0e7fc40a5>`() const;
		bool :ref:`isSpikeEventRequired<doxid-df/dbc/class_neuron_group_1a0da89b8b6e296af2542300c99f23e4ec>`() const;
		unsigned int :ref:`getNumDelaySlots<doxid-df/dbc/class_neuron_group_1a92ba9779dc04654005751f6adf557452>`() const;
		bool :ref:`isDelayRequired<doxid-df/dbc/class_neuron_group_1a1c49f6bcf677638de5d6e2ea2efa8ee4>`() const;
		bool :ref:`isZeroCopyEnabled<doxid-df/dbc/class_neuron_group_1ae896defdc5b9713528f4229a8e87c48c>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSpikeLocation<doxid-df/dbc/class_neuron_group_1a8b5f5d20f2ddd8bd19c9453642257351>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSpikeEventLocation<doxid-df/dbc/class_neuron_group_1abbc357ccf6edc7ed1caf132441797c01>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSpikeTimeLocation<doxid-df/dbc/class_neuron_group_1af2c9d16d55b029665641da5118894c9f>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getVarLocation<doxid-df/dbc/class_neuron_group_1a5f0c4db4f858908f3e1fbe05c86ddd4e>`(const std::string& varName) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getVarLocation<doxid-df/dbc/class_neuron_group_1ad77d461170963671f180f114c23f0797>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getExtraGlobalParamLocation<doxid-df/dbc/class_neuron_group_1ad1d610a5cf9049eb242fa6e5238d0dd6>`(const std::string& paramName) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getExtraGlobalParamLocation<doxid-df/dbc/class_neuron_group_1acd2cb36583d88ebbcd0245edebcbc40a>`(size_t index) const;
		bool :ref:`isSimRNGRequired<doxid-df/dbc/class_neuron_group_1a701fc33e307d9a4315d05fbb855c0fc3>`() const;
		bool :ref:`isInitRNGRequired<doxid-df/dbc/class_neuron_group_1a357157dcee02174bcd669edd3b89d646>`() const;
		bool :ref:`hasOutputToHost<doxid-df/dbc/class_neuron_group_1a052e3e16e639d9116f9916b45346a459>`(int targetHostID) const;

