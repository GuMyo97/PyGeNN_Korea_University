.. index:: pair: class; InitVarSnippet::Constant
.. _doxid-d0/de2/class_init_var_snippet_1_1_constant:

class InitVarSnippet::Constant
==============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Initialises variable to a constant value. :ref:`More...<details-d0/de2/class_init_var_snippet_1_1_constant>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <initVarSnippet.h>
	
	class Constant: public :ref:`InitVarSnippet::Base<doxid-da/df2/class_init_var_snippet_1_1_base>`
	{
	public:
		// methods
	
		:target:`DECLARE_SNIPPET<doxid-d0/de2/class_init_var_snippet_1_1_constant_1a30eeefb6ad492305efa24f68bc9a9baf>`(
			InitVarSnippet::Constant,
			1
			);
	
		:target:`SET_CODE<doxid-d0/de2/class_init_var_snippet_1_1_constant_1af7f62772e0b24c2ce29f4163fdd16211>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d0/de2/class_init_var_snippet_1_1_constant_1a016e6cec1879feaa80173f4c3ba9d429>`() const;
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// typedefs
	
		typedef std::vector<std::string> :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>`;
		typedef std::vector<:ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`> :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>`;
		typedef std::vector<:ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`> :ref:`ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>`;
		typedef std::vector<:ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`> :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>`;

		// structs
	
		struct :ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`;
		struct :ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`;
		struct :ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`;

		// methods
	
		virtual :ref:`~Base<doxid-d6/df7/class_snippet_1_1_base_1a17a9ca158277401f2c190afb1e791d1f>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5>`() const;
		virtual std::string :ref:`getCode<doxid-da/df2/class_init_var_snippet_1_1_base_1af6547fd34390034643ed1651f7cf1797>`() const;

.. _details-d0/de2/class_init_var_snippet_1_1_constant:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Initialises variable to a constant value.

This snippet takes 1 parameter:

* ``value`` - The value to intialise the variable to

This snippet type is seldom used directly - :ref:`Models::VarInit <doxid-de/d2a/class_models_1_1_var_init>` has an implicit constructor that, internally, creates one of these snippets

Methods
-------

.. index:: pair: function; getParamNames
.. _doxid-d0/de2/class_init_var_snippet_1_1_constant_1a016e6cec1879feaa80173f4c3ba9d429:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

