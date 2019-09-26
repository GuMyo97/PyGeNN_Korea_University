.. index:: pair: class; CurrentSourceModels::Base
.. _doxid-d8/d1e/class_current_source_models_1_1_base:

class CurrentSourceModels::Base
===============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Base <doxid-d8/d1e/class_current_source_models_1_1_base>` class for all current source models. :ref:`More...<details-d8/d1e/class_current_source_models_1_1_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <currentSourceModels.h>
	
	class Base: public :ref:`Models::Base<doxid-dc/d39/class_models_1_1_base>`
	{
	public:
		// methods
	
		virtual std::string :ref:`getInjectionCode<doxid-d8/d1e/class_current_source_models_1_1_base_1ae03aa4efaacd4a169409f3a08262a0f3>`() const;
	};

	// direct descendants

	class :ref:`DC<doxid-d3/d29/class_current_source_models_1_1_d_c>`;
	class :ref:`GaussianNoise<doxid-d7/da8/class_current_source_models_1_1_gaussian_noise>`;

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
		typedef std::vector<:ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`> :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>`;

		// structs
	
		struct :ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`;
		struct :ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`;
		struct :ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`;
		struct :ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`;

		// methods
	
		virtual :ref:`~Base<doxid-d6/df7/class_snippet_1_1_base_1a17a9ca158277401f2c190afb1e791d1f>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5>`() const;
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-dc/d39/class_models_1_1_base_1a9df8ba9bf6d971a574ed4745f6cf946c>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-dc/d39/class_models_1_1_base_1a7fdddb7d19382736b330ade62c441de1>`() const;
		size_t :ref:`getVarIndex<doxid-dc/d39/class_models_1_1_base_1afa0e39df5002efc76448e180f82825e4>`(const std::string& varName) const;
		size_t :ref:`getExtraGlobalParamIndex<doxid-dc/d39/class_models_1_1_base_1ae046c19ad56dfb2808c5f4d2cc7475fe>`(const std::string& paramName) const;

.. _details-d8/d1e/class_current_source_models_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Base <doxid-d8/d1e/class_current_source_models_1_1_base>` class for all current source models.

Methods
-------

.. index:: pair: function; getInjectionCode
.. _doxid-d8/d1e/class_current_source_models_1_1_base_1ae03aa4efaacd4a169409f3a08262a0f3:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual std::string getInjectionCode() const

Gets the code that defines current injected each timestep.

