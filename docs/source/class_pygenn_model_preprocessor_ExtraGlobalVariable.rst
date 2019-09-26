.. index:: pair: class; pygenn::model_preprocessor::ExtraGlobalVariable
.. _doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable:

class pygenn::model_preprocessor::ExtraGlobalVariable
=====================================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Class holding information about GeNN extra global pointer variable. :ref:`More...<details-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	class ExtraGlobalVariable: public object
	{
	public:
		// fields
	
		 :target:`name<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1ae430888ed2c89d03a737951c8ed51486>`;
		 :target:`type<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a032fcb1bb1cca6edc589a3ff22b0c406>`;
		 :target:`view<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a0fc912e4388cacc0188f65ecabb1466c>`;
		 :target:`values<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a7955b71fac4270579250247bbdaef199>`;

		// methods
	
		def :ref:`__init__<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a03a04eda53ad603c3a13dc3b9156be4a>`();
		def :ref:`set_values<doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a9ec82f58973c7df1a46ad937e948441c>`();
	};
.. _details-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Class holding information about GeNN extra global pointer variable.

Methods
-------

.. index:: pair: function; __init__
.. _doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a03a04eda53ad603c3a13dc3b9156be4a:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def __init__()

Init :ref:`Variable <doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable>`.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- variable_name

		- string name of the variable

	*
		- variable_type

		- string type of the variable

	*
		- values

		- iterable

.. index:: pair: function; set_values
.. _doxid-d1/d1e/classpygenn_1_1model__preprocessor_1_1_extra_global_variable_1a9ec82f58973c7df1a46ad937e948441c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def set_values()

Set :ref:`Variable <doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable>` 's values.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- values

		- iterable, single value or VarInit instance

