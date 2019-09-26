.. index:: pair: namespace; CodeGenerator
.. _doxid-d5/d2d/namespace_code_generator:

namespace CodeGenerator
=======================

.. toctree::
	:hidden:

	namespace_CodeGenerator_CUDA.rst
	namespace_CodeGenerator_SingleThreadedCPU.rst
	struct_CodeGenerator_FunctionTemplate.rst
	struct_CodeGenerator_PreferencesBase.rst
	class_CodeGenerator_BackendBase.rst
	class_CodeGenerator_CodeStream.rst
	class_CodeGenerator_MemAlloc.rst
	class_CodeGenerator_Substitutions.rst
	class_CodeGenerator_TeeBuf.rst
	class_CodeGenerator_TeeStream.rst

Overview
~~~~~~~~

Helper class for generating code - automatically inserts brackets, indents etc. :ref:`More...<details-d5/d2d/namespace_code_generator>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	namespace CodeGenerator {

	// namespaces

	namespace :ref:`CodeGenerator::CUDA<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>`;
		namespace :ref:`CodeGenerator::CUDA::Optimiser<doxid-d7/dde/namespace_code_generator_1_1_c_u_d_a_1_1_optimiser>`;
		namespace :ref:`CodeGenerator::CUDA::PresynapticUpdateStrategy<doxid-d0/df3/namespace_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy>`;
		namespace :ref:`CodeGenerator::CUDA::Utils<doxid-d7/dcf/namespace_code_generator_1_1_c_u_d_a_1_1_utils>`;
	namespace :ref:`CodeGenerator::SingleThreadedCPU<doxid-dd/d6e/namespace_code_generator_1_1_single_threaded_c_p_u>`;
		namespace :ref:`CodeGenerator::SingleThreadedCPU::Optimiser<doxid-d0/de5/namespace_code_generator_1_1_single_threaded_c_p_u_1_1_optimiser>`;

	// structs

	struct :ref:`FunctionTemplate<doxid-d6/d3a/struct_code_generator_1_1_function_template>`;
	struct :ref:`PreferencesBase<doxid-d3/d06/struct_code_generator_1_1_preferences_base>`;

	// classes

	class :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`;
	class :ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`;
	class :ref:`MemAlloc<doxid-d2/dd3/class_code_generator_1_1_mem_alloc>`;
	class :ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`;
	class :ref:`TeeBuf<doxid-d9/d31/class_code_generator_1_1_tee_buf>`;
	class :ref:`TeeStream<doxid-df/d6a/class_code_generator_1_1_tee_stream>`;

	// global functions

	void :ref:`substitute<doxid-d5/d2d/namespace_code_generator_1aa4e4834ac812b0cb4663112e4bd49eb2>`(std::string& s, const std::string& trg, const std::string& rep);
	bool :ref:`regexVarSubstitute<doxid-d5/d2d/namespace_code_generator_1a80838daf20cefe142f4af7ec2361bfd5>`(std::string& s, const std::string& trg, const std::string& rep);
	bool :ref:`regexFuncSubstitute<doxid-d5/d2d/namespace_code_generator_1a6f8f82386dbf754701a2c5968614594f>`(std::string& s, const std::string& trg, const std::string& rep);

	void :ref:`functionSubstitute<doxid-d5/d2d/namespace_code_generator_1a7308be23a7721f3913894290bcdd7831>`(
		std::string& code,
		const std::string& funcName,
		unsigned int numParams,
		const std::string& replaceFuncTemplate
		);

	template <
		class T,
		typename std::enable_if< std::is_floating_point< T >::value >::type * = nullptr
		>
	void :ref:`writePreciseString<doxid-d5/d2d/namespace_code_generator_1ab6085ea1d46a8959cf26df18c9675b61>`(
		std::ostream& os,
		T value
		);

	template <
		class T,
		typename std::enable_if< std::is_floating_point< T >::value >::type * = nullptr
		>
	std::string :ref:`writePreciseString<doxid-d5/d2d/namespace_code_generator_1ada66f2dbbdc1120868dcdd7e994d467c>`(T value);

	std::string :ref:`ensureFtype<doxid-d5/d2d/namespace_code_generator_1a22199ae12a7875826210e2f57ee0b1ee>`(const std::string& oldcode, const std::string& type);
	void :ref:`checkUnreplacedVariables<doxid-d5/d2d/namespace_code_generator_1a10af4d74175240a715403e6b5f2103cf>`(const std::string& code, const std::string& codeName);

	void :ref:`preNeuronSubstitutionsInSynapticCode<doxid-d5/d2d/namespace_code_generator_1a6f111f70eb87a0fae09fc1bf755fea9b>`(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& offset,
		const std::string& axonalDelayOffset,
		const std::string& postIdx,
		const std::string& devPrefix,
		const std::string& preVarPrefix = "",
		const std::string& preVarSuffix = ""
		);

	void :ref:`postNeuronSubstitutionsInSynapticCode<doxid-d5/d2d/namespace_code_generator_1acc546df68c6a87e2e08a6935fa0e68f7>`(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& offset,
		const std::string& backPropDelayOffset,
		const std::string& preIdx,
		const std::string& devPrefix,
		const std::string& postVarPrefix = "",
		const std::string& postVarSuffix = ""
		);

	void :ref:`neuronSubstitutionsInSynapticCode<doxid-d5/d2d/namespace_code_generator_1aeffa872d440945d9d6170adff0fc8c11>`(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& preIdx,
		const std::string& postIdx,
		const std::string& devPrefix,
		double dt,
		const std::string& preVarPrefix = "",
		const std::string& preVarSuffix = "",
		const std::string& postVarPrefix = "",
		const std::string& postVarSuffix = ""
		);

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` std::ostream& :target:`operator <<<doxid-d5/d2d/namespace_code_generator_1a950a9d11a55f077e3a144728fc0a7ff0>` (
		std::ostream& s,
		const :ref:`CodeStream::OB<doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b>`& ob
		);

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` std::ostream& :target:`operator <<<doxid-d5/d2d/namespace_code_generator_1aa9430a13006943db52167ab768d63e54>` (
		std::ostream& s,
		const :ref:`CodeStream::CB<doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b>`& cb
		);

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` std::vector<std::string> :target:`generateAll<doxid-d5/d2d/namespace_code_generator_1a702f15415adec44845f9420eb485dd6a>`(
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		const filesystem::path& outputPath,
		bool standaloneModules = false
		);

	void :target:`generateInit<doxid-d5/d2d/namespace_code_generator_1a55adab853949f40aae9d01043872cad0>`(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		bool standaloneModules
		);

	void :ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` :target:`generateMakefile<doxid-d5/d2d/namespace_code_generator_1a48a0efb8eb40969e45c54f39c6a6aa8d>`(
		std::ostream& os,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		const std::vector<std::string>& moduleNames
		);

	void :ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` :ref:`generateMPI<doxid-d5/d2d/namespace_code_generator_1ab064c9ce4812db4d3616b89c9c292ec2>`(:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os, const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model, const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend, bool standaloneModules);

	void :ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` :target:`generateMSBuild<doxid-d5/d2d/namespace_code_generator_1a09921f5dc44e788c7060f559b5469802>`(
		std::ostream& os,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		const std::string& projectGUID,
		const std::vector<std::string>& moduleNames
		);

	void :target:`generateNeuronUpdate<doxid-d5/d2d/namespace_code_generator_1a722e720130ce81d3610c4bffa00b957d>`(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		bool standaloneModules
		);

	:ref:`MemAlloc<doxid-d2/dd3/class_code_generator_1_1_mem_alloc>` :target:`generateRunner<doxid-d5/d2d/namespace_code_generator_1a4b99dd706d4c435e17e522cdf302cc0d>`(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& definitions,
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& definitionsInternal,
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& runner,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		int localHostID
		);

	void :target:`generateSupportCode<doxid-d5/d2d/namespace_code_generator_1a5b65889dde61b596c31bfc428f1bf91c>`(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model
		);

	void :target:`generateSynapseUpdate<doxid-d5/d2d/namespace_code_generator_1a7737e92de770ca0a57a7c3a642c329e0>`(
		:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os,
		const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model,
		const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend,
		bool standaloneModules
		);

	} // namespace CodeGenerator
.. _details-d5/d2d/namespace_code_generator:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Helper class for generating code - automatically inserts brackets, indents etc.

Based heavily on: `https://stackoverflow.com/questions/15053753/writing-a-manipulator-for-a-custom-stream-class <https://stackoverflow.com/questions/15053753/writing-a-manipulator-for-a-custom-stream-class>`__

Global Functions
----------------

.. index:: pair: function; substitute
.. _doxid-d5/d2d/namespace_code_generator_1aa4e4834ac812b0cb4663112e4bd49eb2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void substitute(std::string& s, const std::string& trg, const std::string& rep)

Tool for substituting strings in the neuron code strings or other templates.

.. index:: pair: function; regexVarSubstitute
.. _doxid-d5/d2d/namespace_code_generator_1a80838daf20cefe142f4af7ec2361bfd5:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool regexVarSubstitute(
		std::string& s,
		const std::string& trg,
		const std::string& rep
		)

Tool for substituting variable names in the neuron code strings or other templates using regular expressions.

.. index:: pair: function; regexFuncSubstitute
.. _doxid-d5/d2d/namespace_code_generator_1a6f8f82386dbf754701a2c5968614594f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool regexFuncSubstitute(
		std::string& s,
		const std::string& trg,
		const std::string& rep
		)

Tool for substituting function names in the neuron code strings or other templates using regular expressions.

.. index:: pair: function; functionSubstitute
.. _doxid-d5/d2d/namespace_code_generator_1a7308be23a7721f3913894290bcdd7831:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void functionSubstitute(
		std::string& code,
		const std::string& funcName,
		unsigned int numParams,
		const std::string& replaceFuncTemplate
		)

This function substitutes function calls in the form:

$(functionName, parameter1, param2Function(0.12, "string"))

with replacement templates in the form:

actualFunction(CONSTANT, $(0), $(1))

.. index:: pair: function; writePreciseString
.. _doxid-d5/d2d/namespace_code_generator_1ab6085ea1d46a8959cf26df18c9675b61:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <
		class T,
		typename std::enable_if< std::is_floating_point< T >::value >::type * = nullptr
		>
	void writePreciseString(
		std::ostream& os,
		T value
		)

This function writes a floating point value to a stream -setting the precision so no digits are lost.

.. index:: pair: function; writePreciseString
.. _doxid-d5/d2d/namespace_code_generator_1ada66f2dbbdc1120868dcdd7e994d467c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	template <
		class T,
		typename std::enable_if< std::is_floating_point< T >::value >::type * = nullptr
		>
	std::string writePreciseString(T value)

This function writes a floating point value to a string - setting the precision so no digits are lost.

.. index:: pair: function; ensureFtype
.. _doxid-d5/d2d/namespace_code_generator_1a22199ae12a7875826210e2f57ee0b1ee:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	std::string ensureFtype(const std::string& oldcode, const std::string& type)

This function implements a parser that converts any floating point constant in a code snippet to a floating point constant with an explicit precision (by appending "f" or removing it).

.. index:: pair: function; checkUnreplacedVariables
.. _doxid-d5/d2d/namespace_code_generator_1a10af4d74175240a715403e6b5f2103cf:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void checkUnreplacedVariables(
		const std::string& code,
		const std::string& codeName
		)

This function checks for unknown variable definitions and returns a gennError if any are found.

.. index:: pair: function; preNeuronSubstitutionsInSynapticCode
.. _doxid-d5/d2d/namespace_code_generator_1a6f111f70eb87a0fae09fc1bf755fea9b:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void preNeuronSubstitutionsInSynapticCode(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& offset,
		const std::string& axonalDelayOffset,
		const std::string& postIdx,
		const std::string& devPrefix,
		const std::string& preVarPrefix = "",
		const std::string& preVarSuffix = ""
		)

suffix to be used for presynaptic variable accesses - typically combined with prefix to wrap in function call such as \__ldg(&XXX)

Function for performing the code and value substitutions necessary to insert neuron related variables, parameters, and extraGlobal parameters into synaptic code.

.. index:: pair: function; postNeuronSubstitutionsInSynapticCode
.. _doxid-d5/d2d/namespace_code_generator_1acc546df68c6a87e2e08a6935fa0e68f7:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void postNeuronSubstitutionsInSynapticCode(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& offset,
		const std::string& backPropDelayOffset,
		const std::string& preIdx,
		const std::string& devPrefix,
		const std::string& postVarPrefix = "",
		const std::string& postVarSuffix = ""
		)

suffix to be used for postsynaptic variable accesses - typically combined with prefix to wrap in function call such as \__ldg(&XXX)

.. index:: pair: function; neuronSubstitutionsInSynapticCode
.. _doxid-d5/d2d/namespace_code_generator_1aeffa872d440945d9d6170adff0fc8c11:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void neuronSubstitutionsInSynapticCode(
		:ref:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions>`& substitutions,
		const :ref:`SynapseGroupInternal<doxid-d7/d53/class_synapse_group_internal>`& sg,
		const std::string& preIdx,
		const std::string& postIdx,
		const std::string& devPrefix,
		double dt,
		const std::string& preVarPrefix = "",
		const std::string& preVarSuffix = "",
		const std::string& postVarPrefix = "",
		const std::string& postVarSuffix = ""
		)

Function for performing the code and value substitutions necessary to insert neuron related variables, parameters, and extraGlobal parameters into synaptic code.

suffix to be used for postsynaptic variable accesses - typically combined with prefix to wrap in function call such as \__ldg(&XXX)

.. index:: pair: function; generateMPI
.. _doxid-d5/d2d/namespace_code_generator_1ab064c9ce4812db4d3616b89c9c292ec2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	void :ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` generateMPI(:ref:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream>`& os, const :ref:`ModelSpecInternal<doxid-d7/dd5/class_model_spec_internal>`& model, const :ref:`BackendBase<doxid-d7/d74/class_code_generator_1_1_backend_base>`& backend, bool standaloneModules)

A function that generates predominantly MPI infrastructure code.

In this function MPI infrastructure code are generated, including: MPI send and receive functions.

