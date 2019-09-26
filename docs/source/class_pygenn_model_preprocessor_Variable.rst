.. index:: pair: class; pygenn::model_preprocessor::Variable
.. _doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable:

class pygenn::model_preprocessor::Variable
==========================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Class holding information about GeNN variables. :ref:`More...<details-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	class Variable: public object
	{
	public:
		// fields
	
		 :target:`name<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a60a8b44bbabea501cf6bd4a70e8999fb>`;
		 :target:`type<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a49333f3b40b081e4c49fd66931517107>`;
		 :target:`view<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a8644b9a1b79f22f369f8bc946392b648>`;
		 :target:`needs_allocation<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1ae07f5351586f4c3475c6d58a940ad99e>`;
		 :target:`init_required<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1aaa2fab632e26b9ebd69355f71cf269c8>`;
		 :target:`init_val<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1ac68a6acf871cd1651df79260ca020129>`;
		 :target:`values<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a8903b59bf2af200967126ea4daae8592>`;

		// methods
	
		def :ref:`__init__<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1adc91484b845934820ba6c6f5a9920def>`();
		def :ref:`set_values<doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a3b3493a3f7dde4952f94613ecbc0d3e8>`();
	};
.. _details-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Class holding information about GeNN variables.

Methods
-------

.. index:: pair: function; __init__
.. _doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1adc91484b845934820ba6c6f5a9920def:

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

		- iterable, single value or VarInit instance

.. index:: pair: function; set_values
.. _doxid-dd/d5a/classpygenn_1_1model__preprocessor_1_1_variable_1a3b3493a3f7dde4952f94613ecbc0d3e8:

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

