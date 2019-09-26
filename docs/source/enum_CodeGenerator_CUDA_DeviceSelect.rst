.. index:: pair: enum; DeviceSelect
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0:

enum CodeGenerator::CUDA::DeviceSelect
======================================

Overview
~~~~~~~~

Methods for selecting :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` device. :ref:`More...<details-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0>`

.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <backend.h>

	enum DeviceSelect
	{
	    :ref:`OPTIMAL<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0af00c8dbdd6e1f11bdae06be94277d293>`,
	    :ref:`MOST_MEMORY<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0a7091742b1aa4b0be2bcb9750a1f4b0b9>`,
	    :ref:`MANUAL<doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0aa60a6a471c0681e5a49c4f5d00f6bc5a>`,
	};

.. _details-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Methods for selecting :ref:`CUDA <doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a>` device.

Enum Values
-----------

.. index:: pair: enumvalue; OPTIMAL
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0af00c8dbdd6e1f11bdae06be94277d293:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	OPTIMAL

Pick optimal device based on how well kernels can be simultaneously simulated and occupancy.

.. index:: pair: enumvalue; MOST_MEMORY
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0a7091742b1aa4b0be2bcb9750a1f4b0b9:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	MOST_MEMORY

Pick device with most global memory.

.. index:: pair: enumvalue; MANUAL
.. _doxid-d2/dab/namespace_code_generator_1_1_c_u_d_a_1a05cdf29b66af2e1899cbb1d9c702f9d0aa60a6a471c0681e5a49c4f5d00f6bc5a:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	MANUAL

Use device specified by user.

