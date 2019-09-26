.. index:: pair: struct; CodeGenerator::CodeStream::CB
.. _doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b:

struct CodeGenerator::CodeStream::CB
====================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

A close bracket marker. :ref:`More...<details-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <codeStream.h>
	
	struct CB
	{
		// fields
	
		const unsigned int :target:`Level<doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b_1a34c7eaa2f7502df3ddc7a138ee2e4d1b>`;

		// methods
	
		:target:`CB<doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b_1a1bdb3de24897472fac38d36a60783347>`(unsigned int level);
	};
.. _details-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

A close bracket marker.

Write to code stream ``os`` using:

.. ref-code-block:: cpp

	os << :ref:`CB <doxid-d0/d56/struct_code_generator_1_1_code_stream_1_1_c_b_1a1bdb3de24897472fac38d36a60783347>`(16);

