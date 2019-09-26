.. index:: pair: struct; CodeGenerator::CUDA::Preferences
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences:

struct CodeGenerator::CUDA::Preferences
=======================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

:ref:`Preferences <doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences>` for :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` backend. :ref:`More...<details-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <backend.h>
	
	struct Preferences: public :ref:`CodeGenerator::PreferencesBase<doxid-d3/d06/struct_code_generator_1_1_preferences_base>`
	{
		// fields
	
		bool :ref:`showPtxInfo<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ad8e937d78148dcd94e8174b3fba45e86>`;
		:ref:`DeviceSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0>` :ref:`deviceSelectMethod<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ab3f7e871cfa06d52cdff493f80a9289e>`;
		unsigned int :ref:`manualDeviceID<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1a3b75fa868ca95ea3c644efcaaff3308d>`;
		:ref:`BlockSizeSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a54abdd5e5351c160ba420cd758edb7ab>` :ref:`blockSizeSelectMethod<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ad9ddce1e46c8707bf1c30116f9a799be>`;
		:ref:`KernelBlockSize<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a834e8ff4a9b37453a04e5bfa2743423b>` :ref:`manualBlockSizes<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1a24e6c8b33837783988259baa53fd4dda>`;
		std::string :ref:`userNvccFlags<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1aa370bc1e7c48d0928ace7bf4baaa7e73>`;

		// methods
	
		:target:`Preferences<doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1a81d2f28e0431fcbb375e6c0c547a879d>`();
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// fields
	
		bool :ref:`optimizeCode<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a78a5449e9e05425cebb11d1ffba5dc21>`;
		bool :ref:`debugCode<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a58b816a5e133a98fa9aa88ec71890a89>`;
		std::string :ref:`userCxxFlagsGNU<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a86fb454bb8ca003d22eedff8c8c7f4e2>`;
		std::string :ref:`userNvccFlagsGNU<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1acad9c31842a33378f83f524093f6011c>`;
		plog::Severity :ref:`logLevel<doxid-d3/d06/struct_code_generator_1_1_preferences_base_1a901bd4125e2fff733bee452613175063>`;

.. _details-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

:ref:`Preferences <doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences>` for :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` backend.

Fields
------

.. index:: pair: variable; showPtxInfo
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ad8e937d78148dcd94e8174b3fba45e86:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	bool showPtxInfo

Should PTX assembler information be displayed for each :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` kernel during compilation.

.. index:: pair: variable; deviceSelectMethod
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ab3f7e871cfa06d52cdff493f80a9289e:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`DeviceSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0>` deviceSelectMethod

How to select GPU device.

.. index:: pair: variable; manualDeviceID
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1a3b75fa868ca95ea3c644efcaaff3308d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	unsigned int manualDeviceID

If device select method is set to :ref:`DeviceSelect::MANUAL <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0aa60a6a471c0681e5a49c4f5d00f6bc5a>`, id of device to use.

.. index:: pair: variable; blockSizeSelectMethod
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1ad9ddce1e46c8707bf1c30116f9a799be:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`BlockSizeSelect<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a54abdd5e5351c160ba420cd758edb7ab>` blockSizeSelectMethod

How to select :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` blocksize.

.. index:: pair: variable; manualBlockSizes
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1a24e6c8b33837783988259baa53fd4dda:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`KernelBlockSize<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a834e8ff4a9b37453a04e5bfa2743423b>` manualBlockSizes

If block size select method is set to :ref:`BlockSizeSelect::MANUAL <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0aa60a6a471c0681e5a49c4f5d00f6bc5a>`, block size to use for each kernel.

.. index:: pair: variable; userNvccFlags
.. _doxid-d5/d67/struct_code_generator_1_1_c_u_d_a_1_1_preferences_1aa370bc1e7c48d0928ace7bf4baaa7e73:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	std::string userNvccFlags

NVCC compiler options for all GPU code.

