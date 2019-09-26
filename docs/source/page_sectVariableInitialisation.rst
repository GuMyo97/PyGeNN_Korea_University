.. index:: pair: page; Variable initialisation
.. _doxid-da/dc0/sect_variable_initialisation:

Variable initialisation
=======================

Neuron, weight update and postsynaptic models all have state variables which GeNN can automatically initialise.

Previously we have shown variables being initialised to constant values such as:

.. ref-code-block:: cpp

	:ref:`NeuronModels::TraubMiles::VarValues <doxid-d8/d31/class_models_1_1_var_init_container_base>` ini(
	    0.0529324,     // 1 - prob. for Na channel activation m
	    ...
	);

state variables can also be left *uninitialised* leaving it up to the user code to initialise them between the calls to ``initialize()`` and ``initializeSparse()`` :

.. ref-code-block:: cpp

	:ref:`NeuronModels::TraubMiles::VarValues <doxid-d8/d31/class_models_1_1_var_init_container_base>` ini(
	    :ref:`uninitialisedVar <doxid-db/dd1/model_spec_8h_1a6bd7d3c3ead0a4d0ffb15d2a4c67d043>`(),     // 1 - prob. for Na channel activation m
	    ...
	);

or initialised using one of a number of predefined *variable initialisation snippets* :

* :ref:`InitVarSnippet::Uniform <doxid-d5/da5/class_init_var_snippet_1_1_uniform>`

* :ref:`InitVarSnippet::Normal <doxid-d1/d65/class_init_var_snippet_1_1_normal>`

* :ref:`InitVarSnippet::Exponential <doxid-d2/d57/class_init_var_snippet_1_1_exponential>`

* :ref:`InitVarSnippet::Gamma <doxid-df/d94/class_init_var_snippet_1_1_gamma>`

For example, to initialise a parameter using values drawn from the normal distribution:

.. ref-code-block:: cpp

	InitVarSnippet::Normal::ParamValues params(
	    0.05,   // 0 - mean
	    0.01);  // 1 - standard deviation
	    
	:ref:`NeuronModels::TraubMiles::VarValues <doxid-d8/d31/class_models_1_1_var_init_container_base>` ini(
	    initVar<InitVarSnippet::Normal>(params),     // 1 - prob. for Na channel activation m
	    ...
	);



.. _doxid-da/dc0/sect_variable_initialisation_1sect_new_var_init:

Defining a new variable initialisation snippet
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Similarly to neuron, weight update and postsynaptic models, new variable initialisation snippets can be created by simply defining a class in the model description. For example, when initialising excitatory (positive) synaptic weights with a normal distribution they should be clipped at 0 so the long tail of the normal distribution doesn't result in negative weights. This could be implemented using the following variable initialisation snippet which redraws until samples are within the desired bounds:

.. ref-code-block:: cpp

	class NormalPositive : public :ref:`InitVarSnippet::Base <doxid-da/df2/class_init_var_snippet_1_1_base>`
	{
	public:
	    :ref:`DECLARE_SNIPPET <doxid-de/d6c/snippet_8h_1ac5727a6720d28f034afadde948ed6e9a>`(NormalPositive, 2);
	
	    :ref:`SET_CODE <doxid-d8/d25/init_var_snippet_8h_1a4b6549c5c6a7a5b8058283d68fa11578>`(
	        "scalar normal;"
	        "do\n"
	        "{\n"
	        "   normal = $(mean) + ($(gennrand_normal) * $(sd));\n"
	        "} while (normal < 0.0);\n"
	        "$(value) = normal;\n");
	
	    :ref:`SET_PARAM_NAMES <doxid-de/d6c/snippet_8h_1a75315265035fd71c5b5f7d7f449edbd7>`({"mean", "sd"});
	};
	:ref:`IMPLEMENT_SNIPPET <doxid-de/d6c/snippet_8h_1af3c47debe5fc34060e716d7db25462ab>`(NormalPositive);

Within the snippet of code specified using the ``:ref:`SET_CODE() <doxid-d8/d25/init_var_snippet_8h_1a4b6549c5c6a7a5b8058283d68fa11578>``` macro, when initialisising neuron and postaynaptic model state variables , the $(id) variable can be used to access the id of the neuron being initialised. Similarly, when initialising weight update model state variables, the $(id_pre) and $(id_post) variables can used to access the ids of the pre and postsynaptic neurons connected by the synapse being initialised.





.. _doxid-da/dc0/sect_variable_initialisation_1sect_var_init_modes:

Variable locations
~~~~~~~~~~~~~~~~~~

Once you have defined **how** your variables are going to be initialised you need to configure **where** they will be allocated. By default memory is allocated for variables on both the GPU and the host. However, the following alternative 'variable locations' are available:

* :ref:`VarLocation::DEVICE <doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087ae10b6ab6a278644ce40631f62f360b6d>` - Variables are only allocated on the GPU, saving memory but meaning that they can't easily be copied to the host - best for internal state variables.

* :ref:`VarLocation::HOST_DEVICE <doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087aa34547c8e93e562b2c7952c77d426710>` - Variables are allocated on both the GPU and the host - the default.

* :ref:`VarLocation::HOST_DEVICE_ZERO_COPY <doxid-da/d08/variable_mode_8h_1a2807180f6261d89020cf7d7d498fb087a42b7a82fbd6d845b0d5c5dbd67846e0d>` - Variables are allocated as 'zero-copy' memory accessible to the host and GPU - useful on devices such as Jetson TX1 where physical memory is shared between the GPU and CPU.

'Zero copy' memory is only supported on newer embedded systems such as the Jetson TX1 where there is no physical seperation between GPU and host memory and thus the same block of memory can be shared between them.

These modes can be set as a model default using ``:ref:`ModelSpec::setDefaultVarLocation <doxid-d1/de7/class_model_spec_1a55c87917355d34463a3c19fc6887e67a>``` or on a per-variable basis using one of the following functions:

* :ref:`NeuronGroup::setSpikeLocation <doxid-df/dbc/class_neuron_group_1a9df1df6d85dde4a46ddef63954828a95>`

* :ref:`NeuronGroup::setSpikeEventLocation <doxid-df/dbc/class_neuron_group_1a95f0660e93790ea764119002db68f706>`

* :ref:`NeuronGroup::setSpikeTimeLocation <doxid-df/dbc/class_neuron_group_1a63004d6ff9f5b2982ef401e95314d531>`

* :ref:`NeuronGroup::setVarLocation <doxid-df/dbc/class_neuron_group_1a75951040bc142c60c4f0b5a8aa84bd57>`

* :ref:`SynapseGroup::setWUVarLocation <doxid-d2/d62/class_synapse_group_1a36fd4856ed157898059c1aab176c02b8>`

* :ref:`SynapseGroup::setWUPreVarLocation <doxid-d2/d62/class_synapse_group_1a2b4a14a357b0f00020f632a440a3c048>`

* :ref:`SynapseGroup::setWUPostVarLocation <doxid-d2/d62/class_synapse_group_1abce72af57aaeb5cbeb3b6e1a849b1e1e>`

* :ref:`SynapseGroup::setPSVarLocation <doxid-d2/d62/class_synapse_group_1ad394ea032564c35d3228c3e1c1704f54>`

* :ref:`SynapseGroup::setInSynVarLocation <doxid-d2/d62/class_synapse_group_1a871ba5677d4b088443eb43d3c3036114>`

:ref:`Previous <doxid-d5/d39/subsect34>` \| :ref:`Top <doxid-d6/de1/_user_manual>` \| :ref:`Next <doxid-dc/df6/sect_sparse_connectivity_initialisation>`

