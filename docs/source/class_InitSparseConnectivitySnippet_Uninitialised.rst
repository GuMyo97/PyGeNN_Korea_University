.. index:: pair: class; InitSparseConnectivitySnippet::Uninitialised
.. _doxid-d6/d2a/class_init_sparse_connectivity_snippet_1_1_uninitialised:

class InitSparseConnectivitySnippet::Uninitialised
==================================================

.. toctree::
	:hidden:

Used to mark connectivity as uninitialised - no initialisation code will be run.


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <initSparseConnectivitySnippet.h>
	
	class Uninitialised: public :ref:`InitSparseConnectivitySnippet::Base<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base>`
	{
	public:
		// methods
	
		:target:`DECLARE_SNIPPET<doxid-d6/d2a/class_init_sparse_connectivity_snippet_1_1_uninitialised_1a93dd79d03a613c46b65452a93d08266e>`(
			InitSparseConnectivitySnippet::Uninitialised,
			0
			);
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
		typedef std::function<unsigned int(unsigned int, unsigned int, const std::vector<double>&)> :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>`;

		// structs
	
		struct :ref:`DerivedParam<doxid-d4/d21/struct_snippet_1_1_base_1_1_derived_param>`;
		struct :ref:`EGP<doxid-d1/d1f/struct_snippet_1_1_base_1_1_e_g_p>`;
		struct :ref:`ParamVal<doxid-d5/dcc/struct_snippet_1_1_base_1_1_param_val>`;

		// methods
	
		virtual :ref:`~Base<doxid-d6/df7/class_snippet_1_1_base_1a17a9ca158277401f2c190afb1e791d1f>`();
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d6/df7/class_snippet_1_1_base_1a0c8374854fbdc457bf0f75e458748580>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d6/df7/class_snippet_1_1_base_1ab01de002618efa59541c927ffdd463f5>`() const;
		virtual std::string :ref:`getRowBuildCode<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1aa9dd29bd22e2a8f369e1f058e8d37d62>`() const;
		virtual :ref:`ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>` :ref:`getRowBuildStateVars<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a2e1599a8871e7ffa6ee63d2da640b4a7>`() const;
		virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` :ref:`getCalcMaxRowLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ab164352b017276ef6957ac033a4e70ec>`() const;
		virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` :ref:`getCalcMaxColLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a43072eecc2ae8b953a6fff561c83c449>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ac00e552fb74f8f6fd96939abee7f9f92>`() const;
		size_t :ref:`getExtraGlobalParamIndex<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a051b7e5128dc95bc2151c9f1ae0a2d25>`(const std::string& paramName) const;

