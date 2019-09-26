.. index:: pair: namespace; Snippet
.. _doxid-db/db2/namespace_snippet:

namespace Snippet
=================

.. toctree::
	:hidden:

	class_Snippet_Base.rst
	class_Snippet_Init.rst
	class_Snippet_ValueBase.rst
	class_Snippet_ValueBase-2.rst

Wrapper to ensure at compile time that correct number of values are used when specifying the values of a model's parameters and initial state.


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	namespace Snippet {

	// classes

	class :ref:`Base<doxid-d6/df7/class_snippet_1_1_base>`;

	template <typename SnippetBase>
	class :ref:`Init<doxid-da/d6c/class_snippet_1_1_init>`;

	template <>
	class :ref:`ValueBase<0><doxid-db/dcb/class_snippet_1_1_value_base_3_010_01_4>`;

	template <size_t NumVars>
	class :ref:`ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`;

	} // namespace Snippet
