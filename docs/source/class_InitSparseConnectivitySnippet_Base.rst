.. index:: pair: class; InitSparseConnectivitySnippet::Base
.. _doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base:

class InitSparseConnectivitySnippet::Base
=========================================

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <initSparseConnectivitySnippet.h>
	
	class Base: public :ref:`Snippet::Base<doxid-d6/df7/class_snippet_1_1_base>`
	{
	public:
		// typedefs
	
		typedef std::function<unsigned int(unsigned int, unsigned int, const std::vector<double>&)> :target:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>`;

		// methods
	
		virtual std::string :target:`getRowBuildCode<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1aa9dd29bd22e2a8f369e1f058e8d37d62>`() const;
		virtual :ref:`ParamValVec<doxid-d6/df7/class_snippet_1_1_base_1a0156727ddf8f9c9cbcbc0d3d913b6b48>` :target:`getRowBuildStateVars<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a2e1599a8871e7ffa6ee63d2da640b4a7>`() const;
		virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` :ref:`getCalcMaxRowLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ab164352b017276ef6957ac033a4e70ec>`() const;
		virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` :ref:`getCalcMaxColLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a43072eecc2ae8b953a6fff561c83c449>`() const;
		virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` :ref:`getExtraGlobalParams<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ac00e552fb74f8f6fd96939abee7f9f92>`() const;
		size_t :ref:`getExtraGlobalParamIndex<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a051b7e5128dc95bc2151c9f1ae0a2d25>`(const std::string& paramName) const;
	};

	// direct descendants

	class :ref:`FixedProbabilityBase<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base>`;
	class :ref:`OneToOne<doxid-dc/d5c/class_init_sparse_connectivity_snippet_1_1_one_to_one>`;
	class :ref:`Uninitialised<doxid-d6/d2a/class_init_sparse_connectivity_snippet_1_1_uninitialised>`;

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

.. _details-d8/d82/class_init_sparse_connectivity_snippet_1_1_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Methods
-------

.. index:: pair: function; getCalcMaxRowLengthFunc
.. _doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ab164352b017276ef6957ac033a4e70ec:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` getCalcMaxRowLengthFunc() const

Get function to calculate the maximum row length of this connector based on the parameters and the size of the pre and postsynaptic population.

.. index:: pair: function; getCalcMaxColLengthFunc
.. _doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a43072eecc2ae8b953a6fff561c83c449:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`CalcMaxLengthFunc<doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a7719c85cf11d180023fa955ec86a4204>` getCalcMaxColLengthFunc() const

Get function to calculate the maximum column length of this connector based on the parameters and the size of the pre and postsynaptic population.

.. index:: pair: function; getExtraGlobalParams
.. _doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1ac00e552fb74f8f6fd96939abee7f9f92:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	virtual :ref:`EGPVec<doxid-d6/df7/class_snippet_1_1_base_1a43ece29884e2c6cabffe9abf985807c6>` getExtraGlobalParams() const

Gets names and types (as strings) of additional per-population parameters for the connection initialisation snippet

.. index:: pair: function; getExtraGlobalParamIndex
.. _doxid-d8/d82/class_init_sparse_connectivity_snippet_1_1_base_1a051b7e5128dc95bc2151c9f1ae0a2d25:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	size_t getExtraGlobalParamIndex(const std::string& paramName) const

Find the index of a named extra global parameter.

