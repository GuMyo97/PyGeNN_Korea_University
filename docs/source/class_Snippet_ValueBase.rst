.. index:: pair: class; Snippet::ValueBase<0>
.. _doxid-db/dcb/class_snippet_1_1_value_base_3_010_01_4:

template class Snippet::ValueBase<0>
====================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Template specialisation of :ref:`ValueBase <doxid-db/dd1/class_snippet_1_1_value_base>` to avoid compiler warnings in the case when a model requires no parameters or state variables :ref:`More...<details-db/dcb/class_snippet_1_1_value_base_3_010_01_4>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <snippet.h>
	
	template <>
	class ValueBase<0>
	{
	public:
		// methods
	
		template <typename... T>
		:target:`ValueBase<doxid-db/dcb/class_snippet_1_1_value_base_3_010_01_4_1a19f754bd4f0ccac6a75e30c5d5153f0e>`(T&&... vals);
	
		std::vector<double> :ref:`getValues<doxid-db/dcb/class_snippet_1_1_value_base_3_010_01_4_1a3f9a0ac72854478e32629b2ca0db834c>`() const;
	};
.. _details-db/dcb/class_snippet_1_1_value_base_3_010_01_4:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Template specialisation of :ref:`ValueBase <doxid-db/dd1/class_snippet_1_1_value_base>` to avoid compiler warnings in the case when a model requires no parameters or state variables

Methods
-------

.. index:: pair: function; getValues
.. _doxid-db/dcb/class_snippet_1_1_value_base_3_010_01_4_1a3f9a0ac72854478e32629b2ca0db834c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	std::vector<double> getValues() const

Gets values as a vector of doubles.

