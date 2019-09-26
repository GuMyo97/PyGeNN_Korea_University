.. index:: pair: struct; CodeGenerator::FunctionTemplate
.. _doxid-d6/d3a/struct_code_generator_1_1_function_template:

struct CodeGenerator::FunctionTemplate
======================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Immutable structure for specifying how to implement a generic function e.g. :ref:`More...<details-d6/d3a/struct_code_generator_1_1_function_template>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <codeGenUtils.h>
	
	struct FunctionTemplate
	{
		// fields
	
		const std::string :ref:`genericName<doxid-d6/d3a/struct_code_generator_1_1_function_template_1a6dadccba6701a1236789870f40ddbf8d>`;
		const unsigned int :ref:`numArguments<doxid-d6/d3a/struct_code_generator_1_1_function_template_1acbaeb772934eb40f024283602624d0f1>`;
		const std::string :ref:`doublePrecisionTemplate<doxid-d6/d3a/struct_code_generator_1_1_function_template_1ab67a3eae53a7343c1e3b2ce33b9140b4>`;
		const std::string :ref:`singlePrecisionTemplate<doxid-d6/d3a/struct_code_generator_1_1_function_template_1a01e8c32ad3139cf75813c0972f61eaa9>`;

		// methods
	
		FunctionTemplate :target:`operator =<doxid-d6/d3a/struct_code_generator_1_1_function_template_1a1c3e3ea299ad5f722805b32af07275a4>` (const FunctionTemplate& o);
	};
.. _details-d6/d3a/struct_code_generator_1_1_function_template:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Immutable structure for specifying how to implement a generic function e.g. gennrand_uniform

**NOTE** for the sake of easy initialisation first two parameters of GenericFunction are repeated (C++17 fixes)

Fields
------

.. index:: pair: variable; genericName
.. _doxid-d6/d3a/struct_code_generator_1_1_function_template_1a6dadccba6701a1236789870f40ddbf8d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const std::string genericName

Generic name used to refer to function in user code.

.. index:: pair: variable; numArguments
.. _doxid-d6/d3a/struct_code_generator_1_1_function_template_1acbaeb772934eb40f024283602624d0f1:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const unsigned int numArguments

Number of function arguments.

.. index:: pair: variable; doublePrecisionTemplate
.. _doxid-d6/d3a/struct_code_generator_1_1_function_template_1ab67a3eae53a7343c1e3b2ce33b9140b4:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const std::string doublePrecisionTemplate

The function template (for use with :ref:`functionSubstitute <doxid-d5/d2d/namespace_code_generator_1a7308be23a7721f3913894290bcdd7831>`) used when model uses double precision.

.. index:: pair: variable; singlePrecisionTemplate
.. _doxid-d6/d3a/struct_code_generator_1_1_function_template_1a01e8c32ad3139cf75813c0972f61eaa9:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const std::string singlePrecisionTemplate

The function template (for use with :ref:`functionSubstitute <doxid-d5/d2d/namespace_code_generator_1a7308be23a7721f3913894290bcdd7831>`) used when model uses single precision.

