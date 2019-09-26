.. index:: pair: class; pygenn::genn_groups::Group
.. _doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group:

class pygenn::genn_groups::Group
================================

.. toctree::
	:hidden:

Overview
~~~~~~~~

Parent class of :ref:`NeuronGroup <doxid-d6/d59/classpygenn_1_1genn__groups_1_1_neuron_group>`, :ref:`SynapseGroup <doxid-df/d4a/classpygenn_1_1genn__groups_1_1_synapse_group>` and :ref:`CurrentSource <doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>`. :ref:`More...<details-dd/df3/classpygenn_1_1genn__groups_1_1_group>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	
	class Group: public object
	{
	public:
		// fields
	
		 :target:`name<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a2c166d9ace64b65eca3d4d0d91e0bf0d>`;
		 :target:`vars<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1ad8e33584773714170465d5166c9c5e3e>`;
		 :target:`extra_global_params<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a646ab45304e93c1cec854df96e8fb197>`;

		// methods
	
		def :ref:`__init__<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1ac4f6b8f8fb67862785fd508f23d50140>`();
		def :ref:`set_var<doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a9a44ddf9d465e2f272d8e5d16aa82c54>`();
	};

	// direct descendants

	class :ref:`CurrentSource<doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>`;
	class :ref:`NeuronGroup<doxid-d6/d59/classpygenn_1_1genn__groups_1_1_neuron_group>`;
	class :ref:`SynapseGroup<doxid-df/d4a/classpygenn_1_1genn__groups_1_1_synapse_group>`;
.. _details-dd/df3/classpygenn_1_1genn__groups_1_1_group:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

Parent class of :ref:`NeuronGroup <doxid-d6/d59/classpygenn_1_1genn__groups_1_1_neuron_group>`, :ref:`SynapseGroup <doxid-df/d4a/classpygenn_1_1genn__groups_1_1_synapse_group>` and :ref:`CurrentSource <doxid-d9/def/classpygenn_1_1genn__groups_1_1_current_source>`.

Methods
-------

.. index:: pair: function; __init__
.. _doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1ac4f6b8f8fb67862785fd508f23d50140:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def __init__()

Init :ref:`Group <doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group>`.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- name

		- string name of the :ref:`Group <doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group>`

.. index:: pair: function; set_var
.. _doxid-dd/df3/classpygenn_1_1genn__groups_1_1_group_1a9a44ddf9d465e2f272d8e5d16aa82c54:

.. ref-code-block:: cpp
	:class: doxyrest-title-code-block

	def set_var()

Set values for a Variable.



.. rubric:: Parameters:

.. list-table::
	:widths: 20 80

	*
		- var_name

		- string with the name of the variable

	*
		- values

		- iterable or a single value

