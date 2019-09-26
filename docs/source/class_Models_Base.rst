.. index:: pair: class; Models::Base
.. _doxid-dc/d39/class_models_1_1_base:

class Models::Base
==================

.. toctree::
	:hidden:

	struct_Models_Base_Var.rst

Overview
~~~~~~~~

:ref:`Base <doxid-dc/d39/class_models_1_1_base>` class for all models - in addition to the parameters snippets have, models can have state variables. :ref:`More...<details-dc/d39/class_models_1_1_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <models.h>
	
	class Base: public :ref:`Snippet::Base<doxid-d6/df7/class_snippet_1_1_base>`
	{
	public:
		// typedefs
	
		typedef std::vector<:ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`> :target:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>`;

		// structs
	
		struct :ref:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var>`;

		// methods
	
		virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` :ref:`getVars<doxid-dc/d39/class_models_1_1_base_1a9df8ba9bf6d971a574ed4745f6cf946c>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-dc/d39/class_models_1_1_base_1a7fdddb7d19382736b330ade62c441de1>`() const;
		size_t :ref:`getVarIndex<doxid-dc/d39/class_models_1_1_base_1afa0e39df5002efc76448e180f82825e4>`(const std::string& varName) const;
		size_t :ref:`getExtraGlobalParamIndex<doxid-dc/d39/class_models_1_1_base_1ae046c19ad56dfb2808c5f4d2cc7475fe>`(const std::string& paramName) const;
	};

	// direct descendants

	class :ref:`Base<doxid-d8/d1e/class_current_source_models_1_1_base>`;
	class :ref:`Base<doxid-df/d1b/class_neuron_models_1_1_base>`;
	class :ref:`Base<doxid-d3/d2d/class_postsynaptic_models_1_1_base>`;
	class :ref:`Base<doxid-d8/d90/class_weight_update_models_1_1_base>`;

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

.. _details-dc/d39/class_models_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Base <doxid-dc/d39/class_models_1_1_base>` class for all models - in addition to the parameters snippets have, models can have state variables.

Methods
-------

.. index:: pair: function; getVars
.. _doxid-dc/d39/class_models_1_1_base_1a9df8ba9bf6d971a574ed4745f6cf946c:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`VarVec<doxid-dc/d39/class_models_1_1_base_1a5a6bc95969a38ac1ac68ab4a0ba94c75>` getVars() const

Gets names and types (as strings) of model variables.

.. index:: pair: function; getExtraGlobalParams
.. _doxid-dc/d39/class_models_1_1_base_1a7fdddb7d19382736b330ade62c441de1:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` getExtraGlobalParams() const

Gets names and types (as strings) of additional per-population parameters for the weight update model.

.. index:: pair: function; getVarIndex
.. _doxid-dc/d39/class_models_1_1_base_1afa0e39df5002efc76448e180f82825e4:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	size_t getVarIndex(const std::string& varName) const

Find the index of a named variable.

.. index:: pair: function; getExtraGlobalParamIndex
.. _doxid-dc/d39/class_models_1_1_base_1ae046c19ad56dfb2808c5f4d2cc7475fe:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	size_t getExtraGlobalParamIndex(const std::string& paramName) const

Find the index of a named extra global parameter.

