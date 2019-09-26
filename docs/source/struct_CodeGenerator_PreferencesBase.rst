.. index:: pair: struct; CodeGenerator::PreferencesBase
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base:

struct CodeGenerator::PreferencesBase
=====================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Base class for backend preferences - can be accessed via a global in 'classic' C++ code generator. :ref:`More...<details-d3/d06/struct_code_generator_1_1_preferences_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <backendBase.h>
	
	struct PreferencesBase
	{
		// fields
	
		bool :ref:`optimizeCode<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a78a5449e9e05425cebb11d1ffba5dc21>`;
		bool :ref:`debugCode<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a58b816a5e133a98fa9aa88ec71890a89>`;
		std::string :ref:`userCxxFlagsGNU<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a86fb454bb8ca003d22eedff8c8c7f4e2>`;
		std::string :ref:`userNvccFlagsGNU<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1acad9c31842a33378f83f524093f6011c>`;
		plog::Severity :ref:`logLevel<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a901bd4125e2fff733bee452613175063>`;
	};

	// direct descendants

	struct :ref:`Preferences<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences>`;
	struct :ref:`Preferences<doxid-db/d78/struct_code_generator_1_1_single_threaded_c_p_u_1_1_preferences>`;
.. _details-d3/d06/struct_code_generator_1_1_preferences_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Base class for backend preferences - can be accessed via a global in 'classic' C++ code generator.

Fields
------

.. index:: pair: variable; optimizeCode
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a78a5449e9e05425cebb11d1ffba5dc21:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool optimizeCode

Generate speed-optimized code, potentially at the expense of floating-point accuracy.

.. index:: pair: variable; debugCode
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a58b816a5e133a98fa9aa88ec71890a89:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool debugCode

Generate code with debug symbols.

.. index:: pair: variable; userCxxFlagsGNU
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a86fb454bb8ca003d22eedff8c8c7f4e2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	std::string userCxxFlagsGNU

C++ compiler options to be used for building all host side code (used for unix based platforms)

.. index:: pair: variable; userNvccFlagsGNU
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base_1acad9c31842a33378f83f524093f6011c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	std::string userNvccFlagsGNU

NVCC compiler options they may want to use for all GPU code (used for unix based platforms)

.. index:: pair: variable; logLevel
.. _doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a901bd4125e2fff733bee452613175063:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	plog::Severity logLevel

Logging level to use for code generation.

