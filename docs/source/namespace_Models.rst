.. index:: pair: namespace; Models
.. _doxid-d1/d1e/namespace_models:

namespace Models
================

.. toctree::
	:hidden:

	class_Models_Base.rst
	class_Models_VarInit.rst
	class_Models_VarInitContainerBase.rst
	class_Models_VarInitContainerBase-2.rst

Class used to bind together everything required to initialise a variable:

#. A pointer to a variable initialisation snippet

#. The parameters required to control the variable initialisation snippet


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	namespace Models {

	// classes

	class :ref:`Base<doxid-dc/d39/class_models_1_1_base>`;
	class :ref:`VarInit<doxid-de/d2a/class_models_1_1_var_init>`;

	template <>
	class :ref:`VarInitContainerBase<0><doxid-d7/d53/class_models_1_1_var_init_container_base_3_010_01_4>`;

	template <size_t NumVars>
	class :ref:`VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base>`;

	} // namespace Models
