.. index:: pair: class; SynapseGroupInternal
.. _doxid-d7/d53/class_synapse_group_internal:

class SynapseGroupInternal
==========================

.. toctree::
	:hidden:




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <synapseGroupInternal.h>
	
	class SynapseGroupInternal: public :ref:`SynapseGroup<doxid-d2/d62/class_synapse_group>`
	{
	public:
		// methods
	
		:target:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal_1a0ac57bb652676847ab10edc6ba1f5399>`(
			const std::string name,
			:ref:`SynapseMatrixType<doxid-db/d08/synapse_matrix_type_8h_1a24a045033b9a7e987843a67ff5ddec9c>` matrixType,
			unsigned int delaySteps,
			const :ref:`WeightUpdateModels::Base<doxid-d8/d90/class_weight_update_models_1_1_base>`* wu,
			const std::vector<double>& wuParams,
			const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& wuVarInitialisers,
			const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& wuPreVarInitialisers,
			const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& wuPostVarInitialisers,
			const :ref:`PostsynapticModels::Base<doxid-d3/d2d/class_postsynaptic_models_1_1_base>`* ps,
			const std::vector<double>& psParams,
			const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& psVarInitialisers,
			:ref:`NeuronGroupInternal<doxid-d1/dc9/class_neuron_group_internal>`* srcNeuronGroup,
			:ref:`NeuronGroupInternal<doxid-d1/dc9/class_neuron_group_internal>`* trgNeuronGroup,
			const :ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>`& connectivityInitialiser,
			:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` defaultVarLocation,
			:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` defaultExtraGlobalParamLocation,
			:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` defaultSparseConnectivityLocation
			);
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// enums
	
		enum :ref:`SpanType<doxid-d2/d62/class_synapse_group_1a3da23a0e726b05a12e95c3d58645b1a2>`;

		// methods
	
		:ref:`SynapseGroup<doxid-d2/d62/class_synapse_group_1a7a2a79cb1c07b90fb4070aa77c084411>`(const :ref:`SynapseGroup<doxid-d2/d62/class_synapse_group>`&);
		:ref:`SynapseGroup<doxid-d2/d62/class_synapse_group_1a6d6697d4dd8b60bc78be702d75d87c75>`();
		void :ref:`setWUVarLocation<doxid-d2/d62/class_synapse_group_1a36fd4856ed157898059c1aab176c02b8>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setWUPreVarLocation<doxid-d2/d62/class_synapse_group_1a2b4a14a357b0f00020f632a440a3c048>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setWUPostVarLocation<doxid-d2/d62/class_synapse_group_1abce72af57aaeb5cbeb3b6e1a849b1e1e>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setWUExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a67c9478a20f8181df57a43e91ecb3ea3>`(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setPSVarLocation<doxid-d2/d62/class_synapse_group_1ad394ea032564c35d3228c3e1c1704f54>`(const std::string& varName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setPSExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a90b0bda40690467d37ce993f12236e39>`(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSparseConnectivityExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a3cb510f7c9530a61f4ab7a603ef01ac3>`(const std::string& paramName, :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setInSynVarLocation<doxid-d2/d62/class_synapse_group_1a871ba5677d4b088443eb43d3c3036114>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setSparseConnectivityLocation<doxid-d2/d62/class_synapse_group_1ae30487a9c1dc728cce45130821766fc8>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setDendriticDelayLocation<doxid-d2/d62/class_synapse_group_1a74211da769cfc9a1597f5f1c07e26002>`(:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` loc);
		void :ref:`setMaxConnections<doxid-d2/d62/class_synapse_group_1aab6b2fb0ad30189bc11ee3dd7d48dbb2>`(unsigned int maxConnections);
		void :ref:`setMaxSourceConnections<doxid-d2/d62/class_synapse_group_1a93b12c08d634f1a2300f1b91ef34ea24>`(unsigned int maxPostConnections);
		void :ref:`setMaxDendriticDelayTimesteps<doxid-d2/d62/class_synapse_group_1a220307d4043e8bf1bed07552829f2a17>`(unsigned int maxDendriticDelay);
		void :ref:`setSpanType<doxid-d2/d62/class_synapse_group_1a97cfec638d856e6e07628bc19490690c>`(:ref:`SpanType<doxid-d2/d62/class_synapse_group_1a3da23a0e726b05a12e95c3d58645b1a2>` spanType);
		void :ref:`setNumThreadsPerSpike<doxid-d2/d62/class_synapse_group_1a50da6b80e10ac9175f34e901b252803d>`(unsigned int numThreadsPerSpike);
		void :ref:`setBackPropDelaySteps<doxid-d2/d62/class_synapse_group_1ac080d0115f8d3aa274e9f95898b1a443>`(unsigned int timesteps);
		const std::string& :ref:`getName<doxid-d2/d62/class_synapse_group_1a561bdaf3fc0de5e0e5cfd04df5ef226b>`() const;
		:ref:`SpanType<doxid-d2/d62/class_synapse_group_1a3da23a0e726b05a12e95c3d58645b1a2>` :ref:`getSpanType<doxid-d2/d62/class_synapse_group_1ab23e634dc4ccd31c38d359f0491bc4a8>`() const;
		unsigned int :ref:`getNumThreadsPerSpike<doxid-d2/d62/class_synapse_group_1ac5baeed7d75d9ee25578f7052e34e1f5>`() const;
		unsigned int :ref:`getDelaySteps<doxid-d2/d62/class_synapse_group_1a7201e5a054f27f7b7eaea947134d852d>`() const;
		unsigned int :ref:`getBackPropDelaySteps<doxid-d2/d62/class_synapse_group_1ae3835626fd9c85d83c46f0092cd7f861>`() const;
		unsigned int :ref:`getMaxConnections<doxid-d2/d62/class_synapse_group_1ae75ccb1f35d13752ee677b75b693ccc7>`() const;
		unsigned int :ref:`getMaxSourceConnections<doxid-d2/d62/class_synapse_group_1aee57eec3140c18b7070c67f42773d63d>`() const;
		unsigned int :ref:`getMaxDendriticDelayTimesteps<doxid-d2/d62/class_synapse_group_1aef3b4e22321f4f5f7656373e52750be0>`() const;
		:ref:`SynapseMatrixType<doxid-db/d08/synapse_matrix_type_8h_1a24a045033b9a7e987843a67ff5ddec9c>` :ref:`getMatrixType<doxid-d2/d62/class_synapse_group_1ae6502734aacf09f229ce8c7ea7cac404>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getInSynLocation<doxid-d2/d62/class_synapse_group_1a41b76cf518b46bb396217559e38a32e4>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSparseConnectivityLocation<doxid-d2/d62/class_synapse_group_1a1b36c190b899d65fd9f0ba829f7a4ca6>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getDendriticDelayLocation<doxid-d2/d62/class_synapse_group_1acd4119d64af9b327a2229b5508c06d49>`() const;
		int :ref:`getClusterHostID<doxid-d2/d62/class_synapse_group_1a16b848aedef6d0b42bf7a2606e70b680>`() const;
		bool :ref:`isTrueSpikeRequired<doxid-d2/d62/class_synapse_group_1ad9fc1869b2019d1583563b2c0451ede7>`() const;
		bool :ref:`isSpikeEventRequired<doxid-d2/d62/class_synapse_group_1afddee436ed3459540759061aab08de61>`() const;
		const :ref:`WeightUpdateModels::Base<doxid-d8/d90/class_weight_update_models_1_1_base>`* :ref:`getWUModel<doxid-d2/d62/class_synapse_group_1a5314b27701e1fabd2324446c8ff089f2>`() const;
		const std::vector<double>& :ref:`getWUParams<doxid-d2/d62/class_synapse_group_1ae15a32b099d6f64e8889ea61d594d168>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getWUVarInitialisers<doxid-d2/d62/class_synapse_group_1a372c4b62464bb220d4ee1e58c192c0aa>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getWUPreVarInitialisers<doxid-d2/d62/class_synapse_group_1afdd8b8a0bfdb44a9dfbce76c545016b8>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getWUPostVarInitialisers<doxid-d2/d62/class_synapse_group_1a155c5a8be64fa56067288b17a2b2428b>`() const;
		const std::vector<double> :ref:`getWUConstInitVals<doxid-d2/d62/class_synapse_group_1af0b547cd9f24072506b5e499a822a0de>`() const;
		const :ref:`PostsynapticModels::Base<doxid-d3/d2d/class_postsynaptic_models_1_1_base>`* :ref:`getPSModel<doxid-d2/d62/class_synapse_group_1a8ec4b129d947dd428de59b239b9e9131>`() const;
		const std::vector<double>& :ref:`getPSParams<doxid-d2/d62/class_synapse_group_1a0cf2bf6100bab1160d280c59e278d07e>`() const;
		const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getPSVarInitialisers<doxid-d2/d62/class_synapse_group_1a355db7a7f5168baa3382781dea1eafc7>`() const;
		const std::vector<double> :ref:`getPSConstInitVals<doxid-d2/d62/class_synapse_group_1aa031a395d0e0b3014af664aedae79402>`() const;
		const :ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>`& :ref:`getConnectivityInitialiser<doxid-d2/d62/class_synapse_group_1abfc32979d34d21a95d4088199f870b3a>`() const;
		bool :ref:`isZeroCopyEnabled<doxid-d2/d62/class_synapse_group_1a55eaaa7eb11ddbfcd87f892f455b0931>`() const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUVarLocation<doxid-d2/d62/class_synapse_group_1a417c85e0ec443c8e2721432f9be2bf3f>`(const std::string& var) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUVarLocation<doxid-d2/d62/class_synapse_group_1a16f44ddc07e48968e0b8108d554abf54>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUPreVarLocation<doxid-d2/d62/class_synapse_group_1afd0c0e9c90342bf578456838064e46d4>`(const std::string& var) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUPreVarLocation<doxid-d2/d62/class_synapse_group_1a46b2da75b11fd9bf4a7eca42679f282d>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUPostVarLocation<doxid-d2/d62/class_synapse_group_1a728ddcbdf0150242b6a54607f70e4606>`(const std::string& var) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUPostVarLocation<doxid-d2/d62/class_synapse_group_1aa38a39272cb107f0f2aac723701b7183>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a030ef439b75036f3f572f0e35ae54817>`(const std::string& paramName) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getWUExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1acbb05079b74f536a3a92711577b2eee1>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getPSVarLocation<doxid-d2/d62/class_synapse_group_1a27e33b9a702acaa815e2969becbe1e0d>`(const std::string& var) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getPSVarLocation<doxid-d2/d62/class_synapse_group_1ae697f86aaaa25e5fa2a57073b0228312>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getPSExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a3cb4242aa695a55f138ea799afced8b8>`(const std::string& paramName) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getPSExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1a49a2a3c2c93ebce4891909e5d8be832e>`(size_t index) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSparseConnectivityExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1afb3ee75e0c61ae1ddca70b0fb035868c>`(const std::string& paramName) const;
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` :ref:`getSparseConnectivityExtraGlobalParamLocation<doxid-d2/d62/class_synapse_group_1aa7f0b1e52f84cb0fa8622548a66f43b3>`(size_t index) const;
		bool :ref:`isDendriticDelayRequired<doxid-d2/d62/class_synapse_group_1a869f56ee7776d2cd6687f69a564486a5>`() const;
		bool :ref:`isPSInitRNGRequired<doxid-d2/d62/class_synapse_group_1a1fc9c73d01ce125adbb62e509c3dfc0d>`() const;
		bool :ref:`isWUInitRNGRequired<doxid-d2/d62/class_synapse_group_1a7973bd744f1ae607aed1bff386cb7130>`() const;
		bool :ref:`isWUVarInitRequired<doxid-d2/d62/class_synapse_group_1a36a7de3a71e2724d543e2ee423447cc0>`() const;
		bool :ref:`isSparseConnectivityInitRequired<doxid-d2/d62/class_synapse_group_1ab89435493c98adbb60d837b5fe1ec62f>`() const;

