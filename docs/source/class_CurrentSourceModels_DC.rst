.. index:: pair: class; CurrentSourceModels::DC
.. _doxid-d3/d29/class_current_source_models_1_1_d_c:

class CurrentSourceModels::DC
=============================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`DC <doxid-d3/d29/class_current_source_models_1_1_d_c>` source. :ref:`More...<details-d3/d29/class_current_source_models_1_1_d_c>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <currentSourceModels.h>
	
	class DC: public :ref:`CurrentSourceModels::Base<doxid-d8/d1e/class_current_source_models_1_1_base>`
	{
	public:
		// typedefs
	
		typedef :ref:`Snippet::ValueBase<doxid-db/dd1/class_snippet_1_1_value_base>`<1> :target:`ParamValues<doxid-d3/d29/class_current_source_models_1_1_d_c_1a3999840df60dc6284d6209e8f21f72b3>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`VarValues<doxid-d3/d29/class_current_source_models_1_1_d_c_1a5f87cf43404ed2416185be2e85f6bd74>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PreVarValues<doxid-d3/d29/class_current_source_models_1_1_d_c_1a979def8db5dd3d0bd585afe965f93698>`;
		typedef :ref:`Models::VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`<0> :target:`PostVarValues<doxid-d3/d29/class_current_source_models_1_1_d_c_1a961309e28760d0e81122bb660716aa54>`;

		// methods
	
		static const DC* :target:`getInstance<doxid-d3/d29/class_current_source_models_1_1_d_c_1af70581941c10eb3ebad704b3ea79a405>`();
		:target:`SET_INJECTION_CODE<doxid-d3/d29/class_current_source_models_1_1_d_c_1ab14a6c9700652ac6e741b372c441cfed>`("$(injectCurrent, $(amp));\n");
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d3/d29/class_current_source_models_1_1_d_c_1a6a95c17036de93f523b846e3105ff1be>`() const;
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
		virtual std::string :ref:`getInjectionCode<doxid-d8/d1e/class_current_source_models_1_1_base_1ae03aa4efaacd4a169409f3a08262a0f3>`() const;

.. _details-d3/d29/class_current_source_models_1_1_d_c:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`DC <doxid-d3/d29/class_current_source_models_1_1_d_c>` source.

It has a single parameter:

* ``amp`` - amplitude of the current [nA]

Methods
-------

.. index:: pair: function; getParamNames
.. _doxid-d3/d29/class_current_source_models_1_1_d_c_1a6a95c17036de93f523b846e3105ff1be:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` getParamNames() const

Gets names of of (independent) model parameters.

