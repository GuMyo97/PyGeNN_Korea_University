.. index:: pair: class; CodeGenerator::CUDA::PresynapticUpdateStrategy::PostSpan
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span:

class CodeGenerator::CUDA::PresynapticUpdateStrategy::PostSpan
==============================================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Postsynaptic parallelism. :ref:`More...<details-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <presynapticUpdateStrategy.h>
	
	class PostSpan: public :ref:`CodeGenerator::CUDA::PresynapticUpdateStrategy::Base<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base>`
	{
	public:
		// methods
	
		virtual size_t :ref:`getNumThreads<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1aa6547dbd6195b74f0c5e156d40e69981>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const;
		virtual bool :ref:`isCompatible<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a8f48bb3bab41339ac00e4eca4649bd24>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const;
		virtual bool :ref:`shouldAccumulateInRegister<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1ae55cec8c17b68cb38cd5922f37f2df44>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const;
		virtual bool :ref:`shouldAccumulateInSharedMemory<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a1daef37e18265b842431dfaba74be20e>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const;
	
		virtual void :ref:`genCode<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a418208734dd6b518796cf3ed3ae6cee2>`(
			:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
			const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
			const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
			const :ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& popSubs,
			const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend,
			bool trueSpike,
			:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumThreshHandler,
			:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumSimHandler
			) const;
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// methods
	
		virtual size_t :ref:`getNumThreads<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a23dcb4398c882c4af6811b13cb9ebe8d>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const = 0;
		virtual bool :ref:`isCompatible<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a2613968de8aebfbb8e97972b265e6f72>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const = 0;
		virtual bool :ref:`shouldAccumulateInRegister<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a9cc23f259f780552598d5424bf4c51e6>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const = 0;
		virtual bool :ref:`shouldAccumulateInSharedMemory<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a4903a1c176412710ec2ca83641be6da4>`(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const = 0;
	
		virtual void :ref:`genCode<doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a3a665d09ec8064093fba498c558bcbc3>`(
			:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
			const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
			const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
			const :ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& popSubs,
			const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend,
			bool trueSpike,
			:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumThreshHandler,
			:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumSimHandler
			) const = 0;

.. _details-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Postsynaptic parallelism.

Methods
-------

.. index:: pair: function; getNumThreads
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1aa6547dbd6195b74f0c5e156d40e69981:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual size_t getNumThreads(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const

Get the number of threads that presynaptic updates should be parallelised across.

.. index:: pair: function; isCompatible
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a8f48bb3bab41339ac00e4eca4649bd24:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool isCompatible(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const

Is this presynaptic update strategy compatible with a given synapse group?

.. index:: pair: function; shouldAccumulateInRegister
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1ae55cec8c17b68cb38cd5922f37f2df44:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool shouldAccumulateInRegister(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const

Are input currents emitted by this presynaptic update accumulated into a register?

.. index:: pair: function; shouldAccumulateInSharedMemory
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a1daef37e18265b842431dfaba74be20e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool shouldAccumulateInSharedMemory(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const

Are input currents emitted by this presynaptic update accumulated into a shared memory array?

.. index:: pair: function; genCode
.. _doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span_1a418208734dd6b518796cf3ed3ae6cee2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual void genCode(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const :ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& popSubs,
		const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend,
		bool trueSpike,
		:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumThreshHandler,
		:ref:`BackendBase::SynapseGroupHandler<doxid-d7/d74/class_code_generator_1_1_backend_base_1a85aea4cafbf9a7e9ceb6b0d12e9d4997>` wumSimHandler
		) const

Generate presynaptic update code.

