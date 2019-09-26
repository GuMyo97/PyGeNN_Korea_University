.. index:: pair: class; NeuronGroup
.. _doxid-df/dbc/class_neuron_group:

class NeuronGroup
=================

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <neuronGroup.h>
	
	class NeuronGroup
	{
	public:
		// methods
	
		:target:`NeuronGroup<doxid-df/dbc/class_neuron_group_1aa2b21c7c696a54bb3824c6843a0d5bb1>`(const NeuronGroup&);
		:target:`NeuronGroup<doxid-df/dbc/class_neuron_group_1acf9b709abcfb87f8bdc2375796aa8b78>`();
		void :ref:`setSpikeLocation<doxid-df/dbc/class_neuron_group_1a9df1df6d85dde4a46ddef63954828a95>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSpikeEventLocation<doxid-df/dbc/class_neuron_group_1a95f0660e93790ea764119002db68f706>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSpikeTimeLocation<doxid-df/dbc/class_neuron_group_1a63004d6ff9f5b2982ef401e95314d531>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setVarLocation<doxid-df/dbc/class_neuron_group_1a75951040bc142c60c4f0b5a8aa84bd57>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setExtraGlobalParamLocation<doxid-df/dbc/class_neuron_group_1a9f54ec7c3dbf68196a62c2c953eeccd4>`(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		const std::string& :target:`getName<doxid-df/dbc/class_neuron_group_1a78241745e3b1b183676b02ecf4707bae>`() const;
		unsigned int :ref:`getNumNeurons<doxid-df/dbc/class_neuron_group_1abe4b16b1d80aeedfd008113b391173c3>`() const;
		const :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`* :ref:`getNeuronModel<doxid-df/dbc/class_neuron_group_1a30e77db7fede6ab000ed7d2dafee86b4>`() const;
		const std::vector<double>& :target:`getParams<doxid-df/dbc/class_neuron_group_1a2415c5beaf394c6b89092398848be743>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :target:`getVarInitialisers<doxid-df/dbc/class_neuron_group_1a18b1d7a0c40284c03f70f520144839ec>`() const;
		int :target:`getClusterHostID<doxid-df/dbc/class_neuron_group_1a404eda44aa75eea5658de671fe7e3d9c>`() const;
		bool :target:`isSpikeTimeRequired<doxid-df/dbc/class_neuron_group_1a1f6734b170767ad67fe7c3eb139923b1>`() const;
		bool :target:`isTrueSpikeRequired<doxid-df/dbc/class_neuron_group_1a171555a1b0120e2fcb48eda0e7fc40a5>`() const;
		bool :target:`isSpikeEventRequired<doxid-df/dbc/class_neuron_group_1a0da89b8b6e296af2542300c99f23e4ec>`() const;
		unsigned int :target:`getNumDelaySlots<doxid-df/dbc/class_neuron_group_1a92ba9779dc04654005751f6adf557452>`() const;
		bool :target:`isDelayRequired<doxid-df/dbc/class_neuron_group_1a1c49f6bcf677638de5d6e2ea2efa8ee4>`() const;
		bool :target:`isZeroCopyEnabled<doxid-df/dbc/class_neuron_group_1ae896defdc5b9713528f4229a8e87c48c>`() const;
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
	};

	// direct descendants

	class :ref:`NeuronGroupInternal<doxid-d1/dc9/class_neuron_group_internal>`;
.. _details-df/dbc/class_neuron_group:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Methods
-------

.. index:: pair: function; setSpikeLocation
.. _doxid-df/dbc/class_neuron_group_1a9df1df6d85dde4a46ddef63954828a95:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void setSpikeLocation(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc)

Set location of this neuron group's output spikes.

This is ignored for simulations on hardware with a single memory space

.. index:: pair: function; setSpikeEventLocation
.. _doxid-df/dbc/class_neuron_group_1a95f0660e93790ea764119002db68f706:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void setSpikeEventLocation(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc)

Set location of this neuron group's output spike events.

This is ignored for simulations on hardware with a single memory space

.. index:: pair: function; setSpikeTimeLocation
.. _doxid-df/dbc/class_neuron_group_1a63004d6ff9f5b2982ef401e95314d531:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void setSpikeTimeLocation(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc)

Set location of this neuron group's output spike times.

This is ignored for simulations on hardware with a single memory space

.. index:: pair: function; setVarLocation
.. _doxid-df/dbc/class_neuron_group_1a75951040bc142c60c4f0b5a8aa84bd57:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void setVarLocation(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc)

Set variable location of neuron model state variable.

This is ignored for simulations on hardware with a single memory space

.. index:: pair: function; setExtraGlobalParamLocation
.. _doxid-df/dbc/class_neuron_group_1a9f54ec7c3dbf68196a62c2c953eeccd4:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void setExtraGlobalParamLocation(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc)

Set location of neuron model extra global parameter.

This is ignored for simulations on hardware with a single memory space and only applies to extra global parameters which are pointers.

.. index:: pair: function; getNumNeurons
.. _doxid-df/dbc/class_neuron_group_1abe4b16b1d80aeedfd008113b391173c3:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	unsigned int getNumNeurons() const

Gets number of neurons in group.

.. index:: pair: function; getNeuronModel
.. _doxid-df/dbc/class_neuron_group_1a30e77db7fede6ab000ed7d2dafee86b4:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const :ref:`NeuronModels::Base<doxid-df/d1b/class_neuron_models_1_1_base>`* getNeuronModel() const

Gets the neuron model used by this group.

.. index:: pair: function; getSpikeLocation
.. _doxid-df/dbc/class_neuron_group_1a8b5f5d20f2ddd8bd19c9453642257351:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getSpikeLocation() const

Get location of this neuron group's output spikes.

.. index:: pair: function; getSpikeEventLocation
.. _doxid-df/dbc/class_neuron_group_1abbc357ccf6edc7ed1caf132441797c01:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getSpikeEventLocation() const

Get location of this neuron group's output spike events.

.. index:: pair: function; getSpikeTimeLocation
.. _doxid-df/dbc/class_neuron_group_1af2c9d16d55b029665641da5118894c9f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getSpikeTimeLocation() const

Get location of this neuron group's output spike times.

.. index:: pair: function; getVarLocation
.. _doxid-df/dbc/class_neuron_group_1a5f0c4db4f858908f3e1fbe05c86ddd4e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getVarLocation(const std::string& varName) const

Get location of neuron model state variable by name.

.. index:: pair: function; getVarLocation
.. _doxid-df/dbc/class_neuron_group_1ad77d461170963671f180f114c23f0797:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getVarLocation(size_t index) const

Get location of neuron model state variable by index.

.. index:: pair: function; getExtraGlobalParamLocation
.. _doxid-df/dbc/class_neuron_group_1ad1d610a5cf9049eb242fa6e5238d0dd6:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getExtraGlobalParamLocation(const std::string& paramName) const

Get location of neuron model extra global parameter by name.

This is only used by extra global parameters which are pointers

.. index:: pair: function; getExtraGlobalParamLocation
.. _doxid-df/dbc/class_neuron_group_1acd2cb36583d88ebbcd0245edebcbc40a:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` getExtraGlobalParamLocation(size_t index) const

Get location of neuron model extra global parameter by omdex.

This is only used by extra global parameters which are pointers

.. index:: pair: function; isSimRNGRequired
.. _doxid-df/dbc/class_neuron_group_1a701fc33e307d9a4315d05fbb855c0fc3:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool isSimRNGRequired() const

Does this neuron group require an RNG to simulate?

.. index:: pair: function; isInitRNGRequired
.. _doxid-df/dbc/class_neuron_group_1a357157dcee02174bcd669edd3b89d646:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool isInitRNGRequired() const

Does this neuron group require an RNG for it's init code?

.. index:: pair: function; hasOutputToHost
.. _doxid-df/dbc/class_neuron_group_1a052e3e16e639d9116f9916b45346a459:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool hasOutputToHost(int targetHostID) const

Does this neuron group have outgoing connections specified host id?

