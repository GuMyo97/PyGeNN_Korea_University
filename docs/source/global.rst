.. _global:
.. index:: pair: namespace; global

Global Namespace
================

.. toctree::
	:hidden:

	namespace_CodeGenerator.rst
	namespace_CurrentSourceModels.rst
	namespace_InitSparseConnectivitySnippet.rst
	namespace_InitVarSnippet.rst
	namespace_Models.rst
	namespace_NeuronModels.rst
	namespace_PostsynapticModels.rst
	namespace_Snippet.rst
	namespace_Utils.rst
	namespace_WeightUpdateModels.rst
	namespace_filesystem.rst
	namespace_pygenn.rst
	namespace_std.rst
	enum_FloatType.rst
	enum_MathsFunc.rst
	enum_SynapseMatrixConnectivity.rst
	enum_SynapseMatrixType.rst
	enum_SynapseMatrixWeight.rst
	enum_TimePrecision.rst
	enum_VarAccess.rst
	enum_VarLocation.rst
	class_CurrentSource.rst
	class_CurrentSourceInternal.rst
	class_ModelSpec.rst
	class_ModelSpecInternal.rst
	class_NeuronGroup.rst
	class_NeuronGroupInternal.rst
	class_SynapseGroup.rst
	class_SynapseGroupInternal.rst

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	// namespaces

	namespace :ref:`CodeGenerator<doxid-d5/d2d/namespace_code_generator>`;
		namespace :ref:`CodeGenerator::CUDA<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>`;
			namespace :ref:`CodeGenerator::CUDA::Optimiser<doxid-d7/dde/namespace_code_generator_1_1_c_u_d_a_1_1_optimiser>`;
			namespace :ref:`CodeGenerator::CUDA::PresynapticUpdateStrategy<doxid-d0/df3/namespace_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy>`;
			namespace :ref:`CodeGenerator::CUDA::Utils<doxid-d7/dcf/namespace_code_generator_1_1_c_u_d_a_1_1_utils>`;
		namespace :ref:`CodeGenerator::SingleThreadedCPU<doxid-dd/d6e/namespace_code_generator_1_1_single_threaded_c_p_u>`;
			namespace :ref:`CodeGenerator::SingleThreadedCPU::Optimiser<doxid-d0/de5/namespace_code_generator_1_1_single_threaded_c_p_u_1_1_optimiser>`;
	namespace :ref:`CurrentSourceModels<doxid-dd/de4/namespace_current_source_models>`;
	namespace :ref:`InitSparseConnectivitySnippet<doxid-d6/d5b/namespace_init_sparse_connectivity_snippet>`;
	namespace :ref:`InitVarSnippet<doxid-d7/dc6/namespace_init_var_snippet>`;
	namespace :ref:`Models<doxid-d1/d1e/namespace_models>`;
	namespace :ref:`NeuronModels<doxid-d1/d5d/namespace_neuron_models>`;
	namespace :ref:`PostsynapticModels<doxid-db/d7d/namespace_postsynaptic_models>`;
	namespace :ref:`Snippet<doxid-db/db2/namespace_snippet>`;
	namespace :ref:`Utils<doxid-d1/d7c/namespace_utils>`;
	namespace :ref:`WeightUpdateModels<doxid-dd/d76/namespace_weight_update_models>`;
	namespace :ref:`filesystem<doxid-d1/d94/namespacefilesystem>`;
	namespace :ref:`pygenn<doxid-da/d6d/namespacepygenn>`;
		namespace :ref:`pygenn::genn_groups<doxid-d5/da5/namespacepygenn_1_1genn__groups>`;
		namespace :ref:`pygenn::genn_model<doxid-de/d6e/namespacepygenn_1_1genn__model>`;
		namespace :ref:`pygenn::model_preprocessor<doxid-d0/d17/namespacepygenn_1_1model__preprocessor>`;
	namespace :ref:`std<doxid-d8/dcc/namespacestd>`;

	// typedefs

	typedef :ref:`ModelSpec<doxid-d1/de7/class_model_spec>` :target:`NNmodel<doxid-db/dd1/model_spec_8h_1a957acf630622e4f9fd4ddd773e962a92>`;

	// enums

	enum :ref:`FloatType<doxid-db/dd1/model_spec_8h_1aa039815ec6b74d0fe4cb016415781c08>`;
	enum :ref:`MathsFunc<doxid-d7/d15/code_gen_utils_8cc_1a36f6ba9b5dd081f9a244f9a4edb3e460>`;
	enum :ref:`SynapseMatrixConnectivity<doxid-db/d08/synapse_matrix_type_8h_1aedb0946699027562bc78103a5d2a578d>`;
	enum :ref:`SynapseMatrixType<doxid-db/d08/synapse_matrix_type_8h_1a24a045033b9a7e987843a67ff5ddec9c>`;
	enum :ref:`SynapseMatrixWeight<doxid-db/d08/synapse_matrix_type_8h_1a3c0f0120d3cb9e81daea1d2afa7fbe1f>`;
	enum :ref:`TimePrecision<doxid-db/dd1/model_spec_8h_1a71ece086a364ee04c7ffc3f626218b8f>`;
	enum :ref:`VarAccess<doxid-d4/d13/models_8h_1a5a5f7e906a7fdc27f3e5eb66b7115240>`;
	enum :ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>`;

	// classes

	class :ref:`CurrentSource<doxid-d4/d11/class_current_source>`;
	class :ref:`CurrentSourceInternal<doxid-d5/de7/class_current_source_internal>`;
	class :ref:`ModelSpec<doxid-d1/de7/class_model_spec>`;
	class :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`;
	class :ref:`NeuronGroup<doxid-df/dbc/class_neuron_group>`;
	class :ref:`NeuronGroupInternal<doxid-d1/dc9/class_neuron_group_internal>`;
	class :ref:`SynapseGroup<doxid-d2/d62/class_synapse_group>`;
	class :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`;

	// global functions

	unsigned int :target:`binomialInverseCDF<doxid-d6/d24/binomial_8cc_1a620a939ae672f5750398dcfa48e288be>`(
		double cdf,
		unsigned int n,
		double p
		);

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` unsigned int :target:`binomialInverseCDF<doxid-d4/d59/binomial_8h_1aec74d0bcd7821591343a693ffad8158c>`(
		double cdf,
		unsigned int n,
		double p
		);

	:target:`IMPLEMENT_MODEL<doxid-d8/de1/current_source_models_8cc_1ad28bb16799cdcf4400f2d702bcde6389>`(:ref:`CurrentSourceModels::DC<doxid-d3/d29/class_current_source_models_1_1_d_c>`);
	:target:`IMPLEMENT_MODEL<doxid-d8/de1/current_source_models_8cc_1ad9ee9afa263e0f9cbb68625b3d50c356>`(:ref:`CurrentSourceModels::GaussianNoise<doxid-d7/da8/class_current_source_models_1_1_gaussian_noise>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d3/d36/init_sparse_connectivity_snippet_8cc_1a62f80488643e5efe5129c36df0ab3ed5>`(:ref:`InitSparseConnectivitySnippet::Uninitialised<doxid-d6/d2a/class_init_sparse_connectivity_snippet_1_1_uninitialised>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d3/d36/init_sparse_connectivity_snippet_8cc_1a1a187fda342c51fc1b81e11c98c2245b>`(:ref:`InitSparseConnectivitySnippet::OneToOne<doxid-dc/d5c/class_init_sparse_connectivity_snippet_1_1_one_to_one>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d3/d36/init_sparse_connectivity_snippet_8cc_1a3953e30b91d0fa3c8cffb54a2e149eae>`(:ref:`InitSparseConnectivitySnippet::FixedProbability<doxid-dd/d83/class_init_sparse_connectivity_snippet_1_1_fixed_probability>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d3/d36/init_sparse_connectivity_snippet_8cc_1a0d297d44dc5f7246ca74359d3d78abd8>`(:ref:`InitSparseConnectivitySnippet::FixedProbabilityNoAutapse<doxid-d2/d20/class_init_sparse_connectivity_snippet_1_1_fixed_probability_no_autapse>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1a5c93e9ea4a7f09a76b4cf43fa7156705>`(:ref:`InitVarSnippet::Uninitialised<doxid-db/db3/class_init_var_snippet_1_1_uninitialised>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1a44c6f1f5b1cf271ec8bbcde75e55f767>`(:ref:`InitVarSnippet::Constant<doxid-d0/de2/class_init_var_snippet_1_1_constant>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1a288a2d0aa49f2f5cf28872c040961634>`(:ref:`InitVarSnippet::Uniform<doxid-d5/da5/class_init_var_snippet_1_1_uniform>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1aff1bcd82de6731d73c97a4006fc9c6ec>`(:ref:`InitVarSnippet::Normal<doxid-d1/d65/class_init_var_snippet_1_1_normal>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1aa57c95d20fa803d69ebbae1b630c044e>`(:ref:`InitVarSnippet::Exponential<doxid-d2/d57/class_init_var_snippet_1_1_exponential>`);
	:target:`IMPLEMENT_SNIPPET<doxid-d9/d55/init_var_snippet_8cc_1a9957e616103e28b0b547d94507069604>`(:ref:`InitVarSnippet::Gamma<doxid-df/d94/class_init_var_snippet_1_1_gamma>`);

	template <typename S>
	:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>` :ref:`initVar<doxid-db/dd1/model_spec_8h_1a82512da3fc2cd603ff00f8f5b7f2f1ce>`(const typename S::ParamValues& params);

	template <typename S>
	std::enable_if<std::is_same<typename S::ParamValues, :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0>>::value, :ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>::type :ref:`initVar<doxid-db/dd1/model_spec_8h_1ae71c7ad7d12a64c251ea45c5e3ff8af8>`();

	:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>` :ref:`uninitialisedVar<doxid-db/dd1/model_spec_8h_1a6bd7d3c3ead0a4d0ffb15d2a4c67d043>`();

	template <typename S>
	:ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` :ref:`initConnectivity<doxid-db/dd1/model_spec_8h_1aa65f6eb60b9d3e3f3c2d4b14d0ebcae2>`(const typename S::ParamValues& params);

	template <typename S>
	std::enable_if<std::is_same<typename S::ParamValues, :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0>>::value, :ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>`>::type :ref:`initConnectivity<doxid-db/dd1/model_spec_8h_1aaf0972f2313fc4e5f9395458b67306a0>`();

	:ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` :ref:`uninitialisedConnectivity<doxid-db/dd1/model_spec_8h_1a367c112babcc14b58db730731b798073>`();
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a20647d3178dce2bead89883dde2d5ab2>`(:ref:`NeuronModels::RulkovMap<doxid-d3/da8/class_neuron_models_1_1_rulkov_map>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a823115a255f34581c09556fb1c08708b>`(:ref:`NeuronModels::Izhikevich<doxid-d8/dab/class_neuron_models_1_1_izhikevich>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1ad113264e7d6a28ae18c92d2953e2d669>`(:ref:`NeuronModels::IzhikevichVariable<doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1ab8477414f72a8c4da087da8d8572ded0>`(:ref:`NeuronModels::LIF<doxid-d2/d49/class_neuron_models_1_1_l_i_f>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a697478b8a22fab92c55b3fefac4d116b>`(:ref:`NeuronModels::SpikeSource<doxid-d3/d90/class_neuron_models_1_1_spike_source>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a3d22d84613da048c6a8cd0d975e0e950>`(:ref:`NeuronModels::SpikeSourceArray<doxid-dc/d9e/class_neuron_models_1_1_spike_source_array>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1ac9fe1db3a169c8c942fcb3c6a0cbcc16>`(:ref:`NeuronModels::Poisson<doxid-d1/d6c/class_neuron_models_1_1_poisson>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a1e7caf0e70f0aff1e5fa627f661a3005>`(:ref:`NeuronModels::PoissonNew<doxid-d1/d41/class_neuron_models_1_1_poisson_new>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1a943c4c53d69a36e283e6a186900de0e7>`(:ref:`NeuronModels::TraubMiles<doxid-d6/d4a/class_neuron_models_1_1_traub_miles>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1ae940eaf40dc68ce1aa073d87565b2803>`(:ref:`NeuronModels::TraubMilesFast<doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1aed4e9357c669217aab6daf1d8888af16>`(:ref:`NeuronModels::TraubMilesAlt<doxid-da/da2/class_neuron_models_1_1_traub_miles_alt>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d54/neuron_models_8cc_1ae6965ad3be03a91d46689361e494c4f1>`(:ref:`NeuronModels::TraubMilesNStep<doxid-db/dfd/class_neuron_models_1_1_traub_miles_n_step>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d3f/postsynaptic_models_8cc_1ab9d461044dfa49678cbee9035439fe76>`(:ref:`PostsynapticModels::ExpCurr<doxid-d1/d8d/class_postsynaptic_models_1_1_exp_curr>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d3f/postsynaptic_models_8cc_1a32ac219544f81912245195b3c0903f70>`(:ref:`PostsynapticModels::ExpCond<doxid-de/d6d/class_postsynaptic_models_1_1_exp_cond>`);
	:target:`IMPLEMENT_MODEL<doxid-db/d3f/postsynaptic_models_8cc_1a451d8d82aee63e3c83b6e102ab7fb410>`(:ref:`PostsynapticModels::DeltaCurr<doxid-d5/da3/class_postsynaptic_models_1_1_delta_curr>`);

	bool :target:`operator &<doxid-db/d08/synapse_matrix_type_8h_1aa09e78ed987437c288d765a264827267>` (
		:ref:`SynapseMatrixType<doxid-db/d08/synapse_matrix_type_8h_1a24a045033b9a7e987843a67ff5ddec9c>` type,
		:ref:`SynapseMatrixConnectivity<doxid-db/d08/synapse_matrix_type_8h_1aedb0946699027562bc78103a5d2a578d>` connType
		);

	bool :target:`operator &<doxid-db/d08/synapse_matrix_type_8h_1aed7c822a202a76e3931f4a2d0ca4eea1>` (
		:ref:`SynapseMatrixType<doxid-db/d08/synapse_matrix_type_8h_1a24a045033b9a7e987843a67ff5ddec9c>` type,
		:ref:`SynapseMatrixWeight<doxid-db/d08/synapse_matrix_type_8h_1a3c0f0120d3cb9e81daea1d2afa7fbe1f>` weightType
		);

	bool :target:`operator &<doxid-da/d08/variable_mode_8h_1aaf0e3a82d97867803ce7cd2cd7cdce57>` (
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` locA,
		:ref:`VarLocation<doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087>` locB
		);

	:target:`IMPLEMENT_MODEL<doxid-d9/df2/weight_update_models_8cc_1aa4ff35ee64f6d2d0ea710d59f1b95844>`(:ref:`WeightUpdateModels::StaticPulse<doxid-d7/d9c/class_weight_update_models_1_1_static_pulse>`);
	:target:`IMPLEMENT_MODEL<doxid-d9/df2/weight_update_models_8cc_1acfcb39f9706f364995282b012975c089>`(:ref:`WeightUpdateModels::StaticPulseDendriticDelay<doxid-d7/d58/class_weight_update_models_1_1_static_pulse_dendritic_delay>`);
	:target:`IMPLEMENT_MODEL<doxid-d9/df2/weight_update_models_8cc_1a8585d1760d612f8f34340bf9f1844e57>`(:ref:`WeightUpdateModels::StaticGraded<doxid-d2/ddd/class_weight_update_models_1_1_static_graded>`);
	:target:`IMPLEMENT_MODEL<doxid-d9/df2/weight_update_models_8cc_1a3005407d4379e4df2d8a3b97e0902a2b>`(:ref:`WeightUpdateModels::PiecewiseSTDP<doxid-db/dae/class_weight_update_models_1_1_piecewise_s_t_d_p>`);

	// macros

	#define :target:`CHECK_CUDA_ERRORS<doxid-d5/d60/utils_8h_1a3d4f854b9c80237b6f4c23540a823f47>`(call)
	#define :target:`CHECK_CU_ERRORS<doxid-d5/d60/utils_8h_1ac1cf82f980a76bb9ef43b7027cb2348b>`(call)

	#define :target:`DECLARE_MODEL<doxid-d4/d13/models_8h_1ae0c817e85c196f39cf62d608883cda13>`( \
		TYPE, \
		NUM_PARAMS, \
		NUM_VARS \
		)

	#define :target:`DECLARE_SNIPPET<doxid-de/d6c/snippet_8h_1ac5727a6720d28f034afadde948ed6e9a>`( \
		TYPE, \
		NUM_PARAMS \
		)

	#define :target:`DECLARE_WEIGHT_UPDATE_MODEL<doxid-d7/d80/weight_update_models_8h_1a611a9113f742a9d07d3def4298a0ea68>`( \
		TYPE, \
		NUM_PARAMS, \
		NUM_VARS, \
		NUM_PRE_VARS, \
		NUM_POST_VARS \
		)

	#define :target:`IMPLEMENT_MODEL<doxid-d4/d13/models_8h_1a0f3d066ed16dd93ee24912f38826520b>`(TYPE)
	#define :target:`IMPLEMENT_SNIPPET<doxid-de/d6c/snippet_8h_1af3c47debe5fc34060e716d7db25462ab>`(TYPE)
	#define :ref:`NO_DELAY<doxid-db/dd1/model_spec_8h_1a291aa33d0e485ee09a6881cf8056e13c>`
	#define :target:`SET_ADDITIONAL_INPUT_VARS<doxid-de/d5f/neuron_models_8h_1a96a3e23f5c7309a47bc6562e0be81e99>`(...)
	#define :target:`SET_APPLY_INPUT_CODE<doxid-d7/d2e/postsynaptic_models_8h_1a41d7141aeae91e2840c2629106b6a3b1>`(APPLY_INPUT_CODE)
	#define :target:`SET_CALC_MAX_COL_LENGTH_FUNC<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1ad59a50b968b2b9dc03093ea1306eec40>`(FUNC)
	#define :target:`SET_CALC_MAX_ROW_LENGTH_FUNC<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1adc763f727358b11685ddeab7ca8434f2>`(FUNC)
	#define :target:`SET_CODE<doxid-d8/d25/init_var_snippet_8h_1a4b6549c5c6a7a5b8058283d68fa11578>`(CODE)
	#define :target:`SET_CURRENT_CONVERTER_CODE<doxid-d7/d2e/postsynaptic_models_8h_1a3fcf1744f98755e7f5b93a6ff7af85ed>`(CURRENT_CONVERTER_CODE)
	#define :target:`SET_DECAY_CODE<doxid-d7/d2e/postsynaptic_models_8h_1a76caa98a308e162345cee61e025de022>`(DECAY_CODE)
	#define :target:`SET_DERIVED_PARAMS<doxid-de/d6c/snippet_8h_1aa592bfe3ce05ffc19a8f21d8482add6b>`(...)
	#define :target:`SET_EVENT_CODE<doxid-d7/d80/weight_update_models_8h_1a8159c6f595e865d6bf609f045c07361e>`(EVENT_CODE)
	#define :target:`SET_EVENT_THRESHOLD_CONDITION_CODE<doxid-d7/d80/weight_update_models_8h_1a9e0fecc624daee536a388777788cd9de>`(EVENT_THRESHOLD_CONDITION_CODE)
	#define :target:`SET_EXTRA_GLOBAL_PARAMS<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1aa33e3634a531794ddac1ad49bde09071>`(...)
	#define :target:`SET_EXTRA_GLOBAL_PARAMS<doxid-d4/d13/models_8h_1aa33e3634a531794ddac1ad49bde09071>`(...)
	#define :target:`SET_INJECTION_CODE<doxid-db/db9/current_source_models_8h_1adf53ca7b56294cfcca6f22ddfd1daf4f>`(INJECTION_CODE)
	#define :target:`SET_LEARN_POST_CODE<doxid-d7/d80/weight_update_models_8h_1a9f1ad825b90bcbaab3b0d18fc4d00016>`(LEARN_POST_CODE)
	#define :target:`SET_LEARN_POST_SUPPORT_CODE<doxid-d7/d80/weight_update_models_8h_1a5acb21708695409f1ebdd950017b6052>`(LEARN_POST_SUPPORT_CODE)
	#define :target:`SET_MAX_COL_LENGTH<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1a9d72764eb9a910bba6d4a1776717ba02>`(MAX_COL_LENGTH)
	#define :target:`SET_MAX_ROW_LENGTH<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1a338915170111c85ba647e848d28ee2a9>`(MAX_ROW_LENGTH)
	#define :target:`SET_NEEDS_AUTO_REFRACTORY<doxid-de/d5f/neuron_models_8h_1a8e76c0c83549fc188cc73f323895b445>`(AUTO_REFRACTORY_REQUIRED)
	#define :target:`SET_NEEDS_POST_SPIKE_TIME<doxid-d7/d80/weight_update_models_8h_1a4f3e008922887cba8cfafc0fb0e53965>`(POST_SPIKE_TIME_REQUIRED)
	#define :target:`SET_NEEDS_PRE_SPIKE_TIME<doxid-d7/d80/weight_update_models_8h_1ad06378df00a5d9ffe4068ba2c01b09ab>`(PRE_SPIKE_TIME_REQUIRED)
	#define :target:`SET_PARAM_NAMES<doxid-de/d6c/snippet_8h_1a75315265035fd71c5b5f7d7f449edbd7>`(...)
	#define :target:`SET_POST_SPIKE_CODE<doxid-d7/d80/weight_update_models_8h_1aef99e5858038673e6b268f4af07864c2>`(POST_SPIKE_CODE)
	#define :target:`SET_POST_VARS<doxid-d7/d80/weight_update_models_8h_1a906e656a5980ea57c9f1b7c3185e876b>`(...)
	#define :target:`SET_PRE_SPIKE_CODE<doxid-d7/d80/weight_update_models_8h_1aede2f97f853841236f081c8d7b9d156f>`(PRE_SPIKE_CODE)
	#define :target:`SET_PRE_VARS<doxid-d7/d80/weight_update_models_8h_1a9a2bc6f56fa2bfb7008e915710720cfd>`(...)
	#define :target:`SET_RESET_CODE<doxid-de/d5f/neuron_models_8h_1a83b79ae440c7b91c4699b81dac350637>`(RESET_CODE)
	#define :target:`SET_ROW_BUILD_CODE<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1a3758f6bc5bc997383426d5f277b8acc9>`(CODE)
	#define :target:`SET_ROW_BUILD_STATE_VARS<doxid-db/d4c/init_sparse_connectivity_snippet_8h_1abfe3722618884af89eb9c64e1345c03f>`(...)
	#define :target:`SET_SIM_CODE<doxid-de/d5f/neuron_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`(SIM_CODE)
	#define :target:`SET_SIM_CODE<doxid-d7/d80/weight_update_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`(SIM_CODE)
	#define :target:`SET_SIM_SUPPORT_CODE<doxid-d7/d80/weight_update_models_8h_1ab03b345e77fa84781890f70b11457e1f>`(SIM_SUPPORT_CODE)
	#define :target:`SET_SUPPORT_CODE<doxid-de/d5f/neuron_models_8h_1a11d60ec86ac6804c9c8a133f7bec526d>`(SUPPORT_CODE)
	#define :target:`SET_SUPPORT_CODE<doxid-d7/d2e/postsynaptic_models_8h_1a11d60ec86ac6804c9c8a133f7bec526d>`(SUPPORT_CODE)
	#define :target:`SET_SYNAPSE_DYNAMICS_CODE<doxid-d7/d80/weight_update_models_8h_1ae68b0e54b73f5cda5fe9bab3667de3a8>`(SYNAPSE_DYNAMICS_CODE)
	#define :target:`SET_SYNAPSE_DYNAMICS_SUPPORT_CODE<doxid-d7/d80/weight_update_models_8h_1ad6ae07196480eed9c142da2e6ba48fac>`(SYNAPSE_DYNAMICS_SUPPORT_CODE)
	#define :target:`SET_THRESHOLD_CONDITION_CODE<doxid-de/d5f/neuron_models_8h_1a9c94b28e6356469d85e3376f3336f0a2>`(THRESHOLD_CONDITION_CODE)
	#define :target:`SET_VARS<doxid-d4/d13/models_8h_1a3025b9fc844fccdf8cc2b51ef4a6e0aa>`(...)
	#define :target:`TYPE<doxid-d5/dc3/backend_base_8cc_1a250d7d96debe4c60c4d0449c2a96ba78>`(T)

.. _details-global:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Global Functions
----------------

.. index:: pair: function; initVar
.. _doxid-db/dd1/model_spec_8h_1a82512da3fc2cd603ff00f8f5b7f2f1ce:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <typename S>
	:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>` initVar(const typename S::ParamValues& params)

Initialise a variable using an initialisation snippet.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- S

		- type of variable initialisation snippet (derived from :ref:`InitVarSnippet::Base <doxid-da/df2/class_init_var_snippet_1_1_base>`).

	*
		- params

		- parameters for snippet wrapped in S::ParamValues object.



.. rubric:: Returns:

:ref:`Models::VarInit <doxid-de/d2a/class_models_1_1_var_init>` object for use within model's VarValues

.. index:: pair: function; initVar
.. _doxid-db/dd1/model_spec_8h_1ae71c7ad7d12a64c251ea45c5e3ff8af8:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <typename S>
	std::enable_if<std::is_same<typename S::ParamValues, :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0>>::value, :ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>::type initVar()

Initialise a variable using an initialisation snippet with no parameters.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- S

		- type of variable initialisation snippet (derived from :ref:`InitVarSnippet::Base <doxid-da/df2/class_init_var_snippet_1_1_base>`).



.. rubric:: Returns:

:ref:`Models::VarInit <doxid-de/d2a/class_models_1_1_var_init>` object for use within model's VarValues

.. index:: pair: function; uninitialisedVar
.. _doxid-db/dd1/model_spec_8h_1a6bd7d3c3ead0a4d0ffb15d2a4c67d043:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>` uninitialisedVar()

Mark a variable as uninitialised.

This means that the backend will not generate any automatic initialization code, but will instead copy the variable from host to device during ``initializeSparse`` function

.. index:: pair: function; initConnectivity
.. _doxid-db/dd1/model_spec_8h_1aa65f6eb60b9d3e3f3c2d4b14d0ebcae2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <typename S>
	:ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` initConnectivity(const typename S::ParamValues& params)

Initialise connectivity using a sparse connectivity snippet.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- S

		- type of sparse connectivitiy initialisation snippet (derived from :ref:`InitSparseConnectivitySnippet::Base <doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base>`).

	*
		- params

		- parameters for snippet wrapped in S::ParamValues object.



.. rubric:: Returns:

:ref:`InitSparseConnectivitySnippet::Init <doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` object for passing to ``:ref:`ModelSpec::addSynapsePopulation <doxid-d1/de7/class_model_spec_1abd4e9128a5d4f5f993907134218af0c2>```

.. index:: pair: function; initConnectivity
.. _doxid-db/dd1/model_spec_8h_1aaf0972f2313fc4e5f9395458b67306a0:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <typename S>
	std::enable_if<std::is_same<typename S::ParamValues, :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<0>>::value, :ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>`>::type initConnectivity()

Initialise connectivity using a sparse connectivity snippet with no parameters.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- S

		- type of sparse connectivitiy initialisation snippet (derived from :ref:`InitSparseConnectivitySnippet::Base <doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base>`).



.. rubric:: Returns:

:ref:`InitSparseConnectivitySnippet::Init <doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` object for passing to ``:ref:`ModelSpec::addSynapsePopulation <doxid-d1/de7/class_model_spec_1abd4e9128a5d4f5f993907134218af0c2>```

.. index:: pair: function; uninitialisedConnectivity
.. _doxid-db/dd1/model_spec_8h_1a367c112babcc14b58db730731b798073:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`InitSparseConnectivitySnippet::Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>` uninitialisedConnectivity()

Mark a synapse group's sparse connectivity as uninitialised.

This means that the backend will not generate any automatic initialization code, but will instead copy the connectivity from host to device during ``initializeSparse`` function (and, if necessary generate any additional data structures it requires)

Macros
------

.. index:: pair: define; NO_DELAY
.. _doxid-db/dd1/model_spec_8h_1a291aa33d0e485ee09a6881cf8056e13c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	#define NO_DELAY

Macro used to indicate no synapse delay for the group (only one queue slot will be generated)

