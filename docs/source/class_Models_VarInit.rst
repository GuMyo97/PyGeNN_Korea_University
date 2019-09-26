.. index:: pair: class; Models::VarInit
.. _doxid-de/d2a/class_models_1_1_var_init:

class Models::VarInit
=====================

.. toctree::
	:hidden:




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <models.h>
	
	class VarInit: public :ref:`Snippet::Init<doxid-da/d6c/class_snippet_1_1_init>`
	{
	public:
		// methods
	
		:target:`VarInit<doxid-de/d2a/class_models_1_1_var_init_1acb27fde6ac6eda66f81020561ca46a62>`(
			const :ref:`InitVarSnippet::Base<doxid-da/df2/class_init_var_snippet_1_1_base>`* snippet,
			const std::vector<double>& params
			);
	
		:target:`VarInit<doxid-de/d2a/class_models_1_1_var_init_1a07c4e76df4caa8a95ff5cf9cce6d7109>`(double constant);
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// methods
	
		:ref:`Init<doxid-da/d6c/class_snippet_1_1_init_1ae1b490fba08a926f30d03977b37339c5>`(const SnippetBase* snippet, const std::vector<double>& params);
		const SnippetBase* :ref:`getSnippet<doxid-da/d6c/class_snippet_1_1_init_1a3ceb867b6da08f8cc093b73d7e255718>`() const;
		const std::vector<double>& :ref:`getParams<doxid-da/d6c/class_snippet_1_1_init_1aa9ac5d3132df146c7cc83a92f81c5195>`() const;
		const std::vector<double>& :ref:`getDerivedParams<doxid-da/d6c/class_snippet_1_1_init_1a114423c5f6999733ad63b0630aa2afcc>`() const;
		void :ref:`initDerivedParams<doxid-da/d6c/class_snippet_1_1_init_1a567ca2921ef0b3906c8a418aff1124c0>`(double dt);

