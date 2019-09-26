.. index:: pair: class; CodeGenerator::CodeStream
.. _doxid-d3/d26/class_code_generator_1_1_code_stream:

class CodeGenerator::CodeStream
===============================

.. toctree::
	:hidden:

	struct_CodeGenerator_CodeStream_CB.rst
	struct_CodeGenerator_CodeStream_OB.rst
	class_CodeGenerator_CodeStream_IndentBuffer.rst
	class_CodeGenerator_CodeStream_Scope.rst




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <codeStream.h>
	
	class CodeStream: public std::ostream
	{
	public:
		// structs
	
		struct :ref:`CB<doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b>`;
		struct :ref:`OB<doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b>`;

		// classes
	
		class :ref:`IndentBuffer<doxid-d7/d00/class_code_generator_1_1_code_stream_1_1_indent_buffer>`;
		class :ref:`Scope<doxid-da/d96/class_code_generator_1_1_code_stream_1_1_scope>`;

		// methods
	
		:target:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream_1a04a5a264774068dd66b7cd84d2e7a816>`();
		:target:`CodeStream<doxid-d3/d26/class_code_generator_1_1_code_stream_1aa16ba20eb1d2da8dc23045ed8ca74d59>`(std::ostream& stream);
		void :target:`setSink<doxid-d3/d26/class_code_generator_1_1_code_stream_1abe44259e6c0aa0bedd34b99e641e2d87>`(std::ostream& stream);
	};
