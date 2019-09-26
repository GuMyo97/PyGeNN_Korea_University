.. index:: pair: class; InitVarSnippet::Gamma
.. _doxid-df/d94/class_init_var_snippet_1_1_gamma:

class InitVarSnippet::Gamma
===========================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Initialises variable by sampling from the exponential distribution. :ref:`More...<details-df/d94/class_init_var_snippet_1_1_gamma>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <initVarSnippet.h>
	
	class Gamma: public :ref:`InitVarSnippet::Base<doxid-da/df2/class_init_var_snippet_1_1_base>`
	{
	public:
		// methods
	
		:target:`DECLARE_SNIPPET<doxid-df/d94/class_init_var_snippet_1_1_gamma_1aa29667a191e433cc5c2629a7a6ce9d1f>`(
			InitVarSnippet::Gamma,
			2
			);
	
		:target:`SET_CODE<doxid-df/d94/class_init_var_snippet_1_1_gamma_1a164787e99c9fec1117e1ec097face206>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-df/d94/class_init_var_snippet_1_1_gamma_1a9b49d48ecc76239c734f2d2c9fa2a749>`() const;
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

.. _details-df/d94/class_init_var_snippet_1_1_gamma:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Initialises variable by sampling from the exponential distribution.

This snippet takes 1 parameter:

* ``lambda`` - mean event rate (events per unit time/distance)

Methods
-------

.. index:: pair: function; getParamNames
.. _doxid-df/d94/class_init_var_snippet_1_1_gamma_1a9b49d48ecc76239c734f2d2c9fa2a749:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

