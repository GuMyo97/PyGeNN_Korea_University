.. index:: pair: class; Models::VarInitContainerBase
.. _doxid-d8/d31/class_models_1_1_var_init_container_base:

template class Models::VarInitContainerBase
===========================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Wrapper to ensure at compile time that correct number of value initialisers are used when specifying the values of a model's initial state. :ref:`More...<details-d8/d31/class_models_1_1_var_init_container_base>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <models.h>
	
	template <size_t NumVars>
	class VarInitContainerBase
	{
	public:
		// methods
	
		template <typename... T>
		:target:`VarInitContainerBase<doxid-d8/d31/class_models_1_1_var_init_container_base_1ab32b684a4402a77ad46018f48ef95b3d>`(T&&... initialisers);
	
		const std::vector<:ref:`VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& :ref:`getInitialisers<doxid-d8/d31/class_models_1_1_var_init_container_base_1ad8c91b4dec4d3263425e75ade891aac1>`() const;
		const :ref:`VarInit<doxid-de/d2a/class_models_1_1_var_init>`& :target:`operator []<doxid-d8/d31/class_models_1_1_var_init_container_base_1a27ab7cc7f38e1510db4422259a9658b0>` (size_t pos) const;
	};
.. _details-d8/d31/class_models_1_1_var_init_container_base:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Wrapper to ensure at compile time that correct number of value initialisers are used when specifying the values of a model's initial state.

Methods
-------

.. index:: pair: function; getInitialisers
.. _doxid-d8/d31/class_models_1_1_var_init_container_base_1ad8c91b4dec4d3263425e75ade891aac1:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	const std::vector<:ref:`VarInit<doxid-de/d2a/class_models_1_1_var_init>`>& getInitialisers() const

Gets initialisers as a vector of Values.

