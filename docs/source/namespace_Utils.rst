.. index:: pair: namespace; Utils
.. _doxid-d1/d7c/namespace_utils:

namespace Utils
===============

.. toctree::
	:hidden:

Overview
~~~~~~~~




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	namespace Utils {

	// global functions

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool :ref:`isRNGRequired<doxid-d1/d7c/namespace_utils_1aed26fcdb3b695c252189c2059b17b14d>`(const std::string& code);
	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool :ref:`isInitRNGRequired<doxid-d1/d7c/namespace_utils_1a3cba4962c69919bac88a4f7d4a88ee3d>`(const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& varInitialisers);
	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool :ref:`isTypePointer<doxid-d1/d7c/namespace_utils_1a6288decaa7fb3927a7320329be1908a9>`(const std::string& type);
	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` std::string :ref:`getUnderlyingType<doxid-d1/d7c/namespace_utils_1a81b8175ca219ca3b6cee762c38d6013f>`(const std::string& type);

	} // namespace Utils
.. _details-d1/d7c/namespace_utils:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~



Global Functions
----------------

.. index:: pair: function; isRNGRequired
.. _doxid-d1/d7c/namespace_utils_1aed26fcdb3b695c252189c2059b17b14d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool isRNGRequired(const std::string& code)

Does the code string contain any functions requiring random number generator.

.. index:: pair: function; isInitRNGRequired
.. _doxid-d1/d7c/namespace_utils_1a3cba4962c69919bac88a4f7d4a88ee3d:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool isInitRNGRequired(const std::vector<:ref:`Models::VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& varInitialisers)

Does the model with the vectors of variable initialisers and modes require an RNG for the specified init location i.e. host or device.

.. index:: pair: function; isTypePointer
.. _doxid-d1/d7c/namespace_utils_1a6288decaa7fb3927a7320329be1908a9:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` bool isTypePointer(const std::string& type)

Function to determine whether a string containing a type is a pointer.

.. index:: pair: function; getUnderlyingType
.. _doxid-d1/d7c/namespace_utils_1a81b8175ca219ca3b6cee762c38d6013f:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	:ref:`GENN_EXPORT<doxid-d1/d4a/genn_export_8h_1a8224d44517aa3e4a332fbd342364f2e7>` std::string getUnderlyingType(const std::string& type)

Assuming type is a string containing a pointer type, function to return the underlying type.

