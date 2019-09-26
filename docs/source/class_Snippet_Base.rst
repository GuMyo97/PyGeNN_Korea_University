.. index:: pair: class; Snippet::Base
.. _doxid-d6/df7/class_snippet_1_1_base:

class Snippet::Base
===================

.. toctree::
	:hidden:

	struct_Snippet_Base_DerivedParam.rst
	struct_Snippet_Base_EGP.rst
	struct_Snippet_Base_ParamVal.rst

Overview
~~~~~~~~

:ref:`Base <doxid-d6/df7/class_snippet_1_1_base>` class for all code snippets. :ref:`More...<details-d6/df7/class_snippet_1_1_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <snippet.h>
	
	class Base
	{
	public:
		// typedefs
	
		typedef std::vector<std::string> :target:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>`;
		typedef std::vector<:ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`> :target:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>`;
		typedef std::vector<:ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`> :target:`ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>`;
		typedef std::vector<:ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`> :target:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>`;

		// structs
	
		struct :ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`;
		struct :ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`;
		struct :ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`;

		// methods
	
		virtual :target:`~Base<doxid-d6/df7/class_snippet_1_1_base_1a17a9ca158277401f2c190afb1e791d1f>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5>`() const;
	};

	// direct descendants

	class :ref:`Base<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base>`;
	class :ref:`Base<doxid-da/df2/class_init_var_snippet_1_1_base>`;
	class :ref:`Base<doxid-dc/d39/class_models_1_1_base>`;
.. _details-d6/df7/class_snippet_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Base <doxid-d6/df7/class_snippet_1_1_base>` class for all code snippets.

Methods
-------

.. index:: pair: function; getParamNames
.. _doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

.. index:: pair: function; getDerivedParams
.. _doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` getDerivedParams() const

Gets names of derived model parameters and the function objects to call to Calculate their value from a vector of model parameter values

