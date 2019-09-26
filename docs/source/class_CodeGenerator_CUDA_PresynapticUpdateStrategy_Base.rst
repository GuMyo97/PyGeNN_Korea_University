.. index:: pair: class; CodeGenerator::CUDA::PresynapticUpdateStrategy::Base
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base:

class CodeGenerator::CUDA::PresynapticUpdateStrategy::Base
==========================================================

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <presynapticUpdateStrategy.h>
	
	class Base
	{
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
	};

	// direct descendants

	class :ref:`PostSpan<doxid-d4/d2e/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_post_span>`;
	class :ref:`PreSpan<doxid-dc/d0b/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_pre_span>`;
.. _details-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Methods
-------

.. index:: pair: function; getNumThreads
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a23dcb4398c882c4af6811b13cb9ebe8d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual size_t getNumThreads(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const = 0

Get the number of threads that presynaptic updates should be parallelised across.

.. index:: pair: function; isCompatible
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a2613968de8aebfbb8e97972b265e6f72:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool isCompatible(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg) const = 0

Is this presynaptic update strategy compatible with a given synapse group?

.. index:: pair: function; shouldAccumulateInRegister
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a9cc23f259f780552598d5424bf4c51e6:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool shouldAccumulateInRegister(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const = 0

Are input currents emitted by this presynaptic update accumulated into a register?

.. index:: pair: function; shouldAccumulateInSharedMemory
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a4903a1c176412710ec2ca83641be6da4:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual bool shouldAccumulateInSharedMemory(const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg, const :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`& backend) const = 0

Are input currents emitted by this presynaptic update accumulated into a shared memory array?

.. index:: pair: function; genCode
.. _doxid-d0/d2c/class_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy_1_1_base_1a3a665d09ec8064093fba498c558bcbc3:

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
		) const = 0

Generate presynaptic update code.

