.. index:: pair: class; Snippet::ValueBase
.. _doxid-db/dd1/class_snippet_1_1_value_base:

template class Snippet::ValueBase
=================================

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <snippet.h>
	
	template <size_t NumVars>
	class ValueBase
	{
	public:
		// methods
	
		template <typename... T>
		:target:`ValueBase<doxid-db/dd1/class_snippet_1_1_value_base_1aa001b4d15730423c4915ce75e26ca89f>`(T&&... vals);
	
		const std::vector<double>& :ref:`getValues<doxid-db/dd1/class_snippet_1_1_value_base_1ad87c5118a6be03345c415702dd70eedb>`() const;
		double :target:`operator []<doxid-db/dd1/class_snippet_1_1_value_base_1ab7ffe4a19d6b14c9c4a0d41fb14812f0>` (size_t pos) const;
	};
.. _details-db/dd1/class_snippet_1_1_value_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Methods
-------

.. index:: pair: function; getValues
.. _doxid-db/dd1/class_snippet_1_1_value_base_1ad87c5118a6be03345c415702dd70eedb:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const std::vector<double>& getValues() const

Gets values as a vector of doubles.

