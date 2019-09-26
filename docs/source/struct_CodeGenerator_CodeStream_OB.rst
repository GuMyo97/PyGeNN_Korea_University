.. index:: pair: struct; CodeGenerator::CodeStream::OB
.. _doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b:

struct CodeGenerator::CodeStream::OB
====================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

An open bracket marker. :ref:`More...<details-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <codeStream.h>
	
	struct OB
	{
		// fields
	
		const unsigned int :target:`Level<doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b_1adc50a112eb3588a5526a80810c83a14b>`;

		// methods
	
		:target:`OB<doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b_1a890a4c3888f1439c4c51166d8518135c>`(unsigned int level);
	};
.. _details-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

An open bracket marker.

Write to code stream ``os`` using:

.. ref-code-block:: cpp

	os << :ref:`OB <doxid-de/d03/struct_code_generator_1_1_code_stream_1_1_o_b_1a890a4c3888f1439c4c51166d8518135c>`(16);

