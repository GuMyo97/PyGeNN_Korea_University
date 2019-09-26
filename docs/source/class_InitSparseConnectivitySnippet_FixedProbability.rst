.. index:: pair: class; InitSparseConnectivitySnippet::FixedProbability
.. _doxid-dd/d83/class_init_sparse_connectivity_snippet_1_1_fixed_probability:

class InitSparseConnectivitySnippet::FixedProbability
=====================================================

.. toctree::
	:hidden:

Initialises connectivity with a fixed probability of a synapse existing between a pair of pre and postsynaptic neurons.

Whether a synapse exists between a pair of pre and a postsynaptic neurons can be modelled using a Bernoulli distribution. While this COULD br sampling directly by repeatedly drawing from the uniform distribution, this is innefficient. Instead we sample from the gemetric distribution which describes "the probability distribution of the number of Bernoulli
trials needed to get one success" essentially the distribution of the 'gaps' between synapses. We do this using the "inversion method" described by Devroye (1986) essentially inverting the CDF of the equivalent continuous distribution (in this case the exponential distribution)


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <initSparseConnectivitySnippet.h>
	
	class FixedProbability: public :ref:`InitSparseConnectivitySnippet::FixedProbabilityBase<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base>`
	{
	public:
		// methods
	
		:target:`DECLARE_SNIPPET<doxid-dd/d83/class_init_sparse_connectivity_snippet_1_1_fixed_probability_1ad89b5fc9427cffbcca1624a0186b520d>`(
			InitSparseConnectivitySnippet::FixedProbability,
			1
			);
	
		:target:`SET_ROW_BUILD_CODE<doxid-dd/d83/class_init_sparse_connectivity_snippet_1_1_fixed_probability_1ac9c0c075e34997dd9f78f28e6c18c86a>`();
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
		virtual std::string :ref:`getRowBuildCode<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1a57f8d74079f8aa82fa90b11f93dce309>`() const = 0;
		:ref:`SET_ROW_BUILD_STATE_VARS<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1a98582cf471523527d7c55c7f0351fec1>`({{"prevJ","int",-1}});
		virtual :ref:`StringVec<doxid-d6/df7/class_snippet_1_1_base_1a06cd0f6da1424a20163e12b6fec62519>` :ref:`getParamNames<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1a74482a683eaf4407369df75b28957905>`() const;
		virtual :ref:`DerivedParamVec<doxid-d6/df7/class_snippet_1_1_base_1ad14217cebf11eddffa751a4d5c4792cb>` :ref:`getDerivedParams<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1a8ad49047e343c93b0c92be50b57ae7f5>`() const;
		:ref:`SET_CALC_MAX_ROW_LENGTH_FUNC<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1a14975e365e173dc24134c26ac8cf5a91>`((unsigned int numPre, unsigned int numPost, const std::vector<double>&pars){const double quantile=pow(0.9999, 1.0/(double) numPre);return :ref:`binomialInverseCDF<doxid-d6/d24/binomial_8cc_1a620a939ae672f5750398dcfa48e288be>`(quantile, numPost, pars[0]);});
		:ref:`SET_CALC_MAX_COL_LENGTH_FUNC<doxid-d1/d15/class_init_sparse_connectivity_snippet_1_1_fixed_probability_base_1abfc1212c5f01c43426939ca7884161e8>`((unsigned int numPre, unsigned int numPost, const std::vector<double>&pars){const double quantile=pow(0.9999, 1.0/(double) numPost);return :ref:`binomialInverseCDF<doxid-d6/d24/binomial_8cc_1a620a939ae672f5750398dcfa48e288be>`(quantile, numPre, pars[0]);});

