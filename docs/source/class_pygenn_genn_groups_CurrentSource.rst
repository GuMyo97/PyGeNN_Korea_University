.. index:: pair: class; pygenn::genn_groups::CurrentSource
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source:

class pygenn::genn_groups::CurrentSource
========================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Class representing a current injection into a group of neurons. :ref:`More...<details-d9/def/classpygenn_1_1genn__groups_1_1_current_source>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	class CurrentSource: public :ref:`pygenn::genn_groups::Group<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group>`
	{
	public:
		// fields
	
		 :target:`current_source_model<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1aa2e59cb8e23e22392bc2c15dd571fe47>`;
		 :target:`target_pop<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a9af0c16aa535ae2cfd25ec4444deb537>`;
		 :target:`pop<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a8559a76c85d0c217d97c7797b38e8411>`;

		// methods
	
		def :ref:`__init__<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1ac23778d243253b844e3350b91afb7a77>`();
		def :ref:`size<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a759ae700fd0b5cc1f07b13a9860dc4b5>`();
		def :ref:`set_current_source_model<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1ae9e88149814e0f82a64380820b836fd2>`();
		def :ref:`add_to<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a20917300db04937a93670c3804a6a843>`();
		def :ref:`add_extra_global_param<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a2461e81e8525141c28ae9726138dca66>`();
		def :target:`load<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1aab99115c060d56598422dddbc96041fd>`();
		def :ref:`reinitialise<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a5a21080e25082e0e07ceca063bf7a266>`();
	};

Inherited Members
-----------------

.. ref-code-block:: cpp
	:class: doxyrest-overview-inherited-code-block

	public:
		// fields
	
		 :ref:`name<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a2c166d9ace64b65eca3d4d0d91e0bf0d>`;
		 :ref:`vars<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1ad8e33584773714170465d5166c9c5e3e>`;
		 :ref:`extra_global_params<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a646ab45304e93c1cec854df96e8fb197>`;

		// methods
	
		def :ref:`__init__<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1ac4f6b8f8fb67862785fd508f23d50140>`();
		def :ref:`set_var<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a9a44ddf9d465e2f272d8e5d16aa82c54>`();

.. _details-d9/def/classpygenn_1_1genn__groups_1_1_current_source:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Class representing a current injection into a group of neurons.

Methods
-------

.. index:: pair: function; __init__
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1ac23778d243253b844e3350b91afb7a77:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def __init__()

Init :ref:`CurrentSource <doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>`.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- name

		- string name of the current source

.. index:: pair: function; size
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a759ae700fd0b5cc1f07b13a9860dc4b5:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def size()

Number of neuron in the injected population.

.. index:: pair: function; set_current_source_model
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1ae9e88149814e0f82a64380820b836fd2:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def set_current_source_model()

Set curront source model, its parameters and initial variables.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- model

		- type as string of intance of the model

	*
		- param_space

		- dict with model parameters

	*
		- var_space

		- dict with model variables

.. index:: pair: function; add_to
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a20917300db04937a93670c3804a6a843:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def add_to()

Inject this :ref:`CurrentSource <doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>` into population and add it to the GeNN NNmodel.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- pop

		- instance of :ref:`NeuronGroup <doxid-d6/d59/classpygenn_1_1genn__groups_1_1_neuron_group>` into which this :ref:`CurrentSource <doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>` should be injected

	*
		- nn_model

		- GeNN NNmodel

.. index:: pair: function; add_extra_global_param
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a2461e81e8525141c28ae9726138dca66:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def add_extra_global_param()

Add extra global parameter.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- param_name

		- string with the name of the extra global parameter

	*
		- param_values

		- iterable or a single value

.. index:: pair: function; reinitialise
.. _doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source_1a5a21080e25082e0e07ceca063bf7a266:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def reinitialise()

Reinitialise current source.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- slm

		- SharedLibraryModel instance for acccessing variables

	*
		- scalar

		- String specifying "scalar" type

