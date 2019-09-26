.. index:: pair: namespace; CodeGenerator::CUDA
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a:

namespace CodeGenerator::CUDA
=============================

.. toctree::
	:hidden:

	namespace_CodeGenerator_CUDA_Optimiser.rst
	namespace_CodeGenerator_CUDA_PresynapticUpdateStrategy.rst
	namespace_CodeGenerator_CUDA_Utils.rst
	enum_CodeGenerator_CUDA_BlockSizeSelect.rst
	enum_CodeGenerator_CUDA_DeviceSelect.rst
	enum_CodeGenerator_CUDA_Kernel.rst
	struct_CodeGenerator_CUDA_Preferences.rst
	class_CodeGenerator_CUDA_Backend.rst

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	namespace CUDA {

	// namespaces

	namespace :ref:`CodeGenerator::CUDA::Optimiser<doxid-d7/dde/namespace_code_generator_1_1_c_u_d_a_1_1_optimiser>`;
	namespace :ref:`CodeGenerator::CUDA::PresynapticUpdateStrategy<doxid-d0/df3/namespace_code_generator_1_1_c_u_d_a_1_1_presynaptic_update_strategy>`;
	namespace :ref:`CodeGenerator::CUDA::Utils<doxid-d7/dcf/namespace_code_generator_1_1_c_u_d_a_1_1_utils>`;

	// typedefs

	typedef std::array<size_t, :ref:`KernelMax<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05381dc4178da4eb5cd21384a44dace4a50aff7d81597c0195a06734c9fa4ada8>`> :ref:`KernelBlockSize<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a834e8ff4a9b37453a04e5bfa2743423b>`;

	// enums

	enum :ref:`BlockSizeSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a54abdd5e5351c160ba420cd758edb7ab>`;
	enum :ref:`DeviceSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0>`;
	enum :ref:`Kernel<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05381dc4178da4eb5cd21384a44dace4>`;

	// structs

	struct :ref:`Preferences<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences>`;

	// classes

	class :ref:`Backend<doxid-d9/dd6/class_code_generator_1_1_c_u_d_a_1_1_backend>`;

	} // namespace CUDA
.. _details-d2/dab/namespace_code_generator_1_1_c_u_d_a:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Typedefs
--------

.. index:: pair: typedef; KernelBlockSize
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a834e8ff4a9b37453a04e5bfa2743423b:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	typedef std::array<size_t, :ref:`KernelMax<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05381dc4178da4eb5cd21384a44dace4a50aff7d81597c0195a06734c9fa4ada8>`> KernelBlockSize

Array of block sizes for each kernel.

