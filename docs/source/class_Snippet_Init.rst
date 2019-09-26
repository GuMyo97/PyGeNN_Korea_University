.. index:: pair: class; Snippet::Init
.. _doxid-da/d6c/class_snippet_1_1_init:

template class Snippet::Init
============================

.. toctree::
	:hidden:

Class used to bind together everything required to utilize a snippet

#. A pointer to a variable initialisation snippet

#. The parameters required to control the variable initialisation snippet


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <snippet.h>
	
	template <typename SnippetBase>
	class Init
	{
	public:
		// methods
	
		:target:`Init<doxid-da/d6c/class_snippet_1_1_init_1ae1b490fba08a926f30d03977b37339c5>`(
			const SnippetBase* snippet,
			const std::vector<double>& params
			);
	
		const SnippetBase* :target:`getSnippet<doxid-da/d6c/class_snippet_1_1_init_1a3ceb867b6da08f8cc093b73d7e255718>`() const;
		const std::vector<double>& :target:`getParams<doxid-da/d6c/class_snippet_1_1_init_1aa9ac5d3132df146c7cc83a92f81c5195>`() const;
		const std::vector<double>& :target:`getDerivedParams<doxid-da/d6c/class_snippet_1_1_init_1a114423c5f6999733ad63b0630aa2afcc>`() const;
		void :target:`initDerivedParams<doxid-da/d6c/class_snippet_1_1_init_1a567ca2921ef0b3906c8a418aff1124c0>`(double dt);
	};

	// direct descendants

	class :ref:`Init<doxid-dc/d49/class_init_sparse_connectivity_snippet_1_1_init>`;
	class :ref:`VarInit<doxid-de/d2a/class_models_1_1_var_init>`;
