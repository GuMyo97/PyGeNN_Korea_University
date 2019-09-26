.. index:: pair: page; Neuron models
.. _doxid-da/ddf/sect_neuron_models:

Neuron models
=============

There is a number of predefined models which can be used with the ModelSpec::addNeuronGroup function:

* :ref:`NeuronModels::RulkovMap <doxid-d3/da8/class_neuron_models_1_1_rulkov_map>`

* :ref:`NeuronModels::Izhikevich <doxid-d8/dab/class_neuron_models_1_1_izhikevich>`

* :ref:`NeuronModels::IzhikevichVariable <doxid-d8/d6a/class_neuron_models_1_1_izhikevich_variable>`

* :ref:`NeuronModels::LIF <doxid-d2/d49/class_neuron_models_1_1_l_i_f>`

* :ref:`NeuronModels::SpikeSource <doxid-d3/d90/class_neuron_models_1_1_spike_source>`

* :ref:`NeuronModels::PoissonNew <doxid-d1/d41/class_neuron_models_1_1_poisson_new>`

* :ref:`NeuronModels::TraubMiles <doxid-d6/d4a/class_neuron_models_1_1_traub_miles>`

* :ref:`NeuronModels::TraubMilesFast <doxid-d2/dfb/class_neuron_models_1_1_traub_miles_fast>`

* :ref:`NeuronModels::TraubMilesAlt <doxid-da/da2/class_neuron_models_1_1_traub_miles_alt>`

* :ref:`NeuronModels::TraubMilesNStep <doxid-db/dfd/class_neuron_models_1_1_traub_miles_n_step>`



.. _doxid-da/ddf/sect_neuron_models_1sect_own:

Defining your own neuron type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to define a new neuron type for use in a GeNN application, it is necessary to define a new class derived from :ref:`NeuronModels::Base <doxid-df/d1b/class_neuron_models_1_1_base>`. For convenience the methods this class should implement can be implemented using macros:

* :ref:`DECLARE_MODEL(TYPE, NUM_PARAMS, NUM_VARS) <doxid-d4/d13/models_8h_1ae0c817e85c196f39cf62d608883cda13>` : declared the boilerplate code required for the model e.g. the correct specialisations of NewModels::ValueBase used to wrap the neuron model parameters and values.

* :ref:`SET_SIM_CODE(SIM_CODE) <doxid-d7/d80/weight_update_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>` : where SIM_CODE contains the code for executing the integration of the model for one time stepWithin this code string, variables need to be referred to by $(NAME), where NAME is the name of the variable as defined in the vector varNames. The code may refer to the predefined primitives ``DT`` for the time step size and ```` for the total incoming synaptic current. It can also refer to a unique ID (within the population) using .

* :ref:`SET_THRESHOLD_CONDITION_CODE(THRESHOLD_CONDITION_CODE) <doxid-de/d5f/neuron_models_8h_1a9c94b28e6356469d85e3376f3336f0a2>` defines the condition for true spike detection.

* :ref:`SET_PARAM_NAMES() <doxid-de/d6c/snippet_8h_1a75315265035fd71c5b5f7d7f449edbd7>` defines the names of the model parameters. If defined as ``NAME`` here, they can then be referenced as $(NAME) in the code string. The length of this list should match the NUM_PARAM specified in DECLARE_MODEL. Parameters are assumed to be always of type double.

* :ref:`SET_VARS() <doxid-d4/d13/models_8h_1a3025b9fc844fccdf8cc2b51ef4a6e0aa>` defines the names and type strings (e.g. "float", "double", etc) of the neuron state variables. The type string "scalar" can be used for variables which should be implemented using the precision set globally for the model with :ref:`ModelSpec::setPrecision <doxid-d1/de7/class_model_spec_1a7548f1bf634884c051e4fbac3cf6212c>`. The variables defined here as ``NAME`` can then be used in the syntax $(NAME) in the code string.

* :ref:`SET_NEEDS_AUTO_REFRACTORY() <doxid-de/d5f/neuron_models_8h_1a8e76c0c83549fc188cc73f323895b445>` defines whether the neuron should include an automatic refractory period to prevent it emitting spikes in successive timesteps.

For example, using these macros, we can define a leaky integrator :math:`\tau\frac{dV}{dt}= -V + I_{{\rm syn}}` solved using Euler's method:

.. ref-code-block:: cpp

	class LeakyIntegrator : public :ref:`NeuronModels::Base <doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
	    :ref:`DECLARE_MODEL <doxid-d4/d13/models_8h_1ae0c817e85c196f39cf62d608883cda13>`(LeakyIntegrator, 1, 1);
	    
	    :ref:`SET_SIM_CODE <doxid-de/d5f/neuron_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`("$(V)+= (-$(V)+$(Isyn))*(DT/$(tau));");
	    
	    :ref:`SET_THRESHOLD_CONDITION_CODE <doxid-de/d5f/neuron_models_8h_1a9c94b28e6356469d85e3376f3336f0a2>`("$(V) >= 1.0");
	    
	    :ref:`SET_PARAM_NAMES <doxid-de/d6c/snippet_8h_1a75315265035fd71c5b5f7d7f449edbd7>`({"tau"});
	    
	    :ref:`SET_VARS <doxid-d4/d13/models_8h_1a3025b9fc844fccdf8cc2b51ef4a6e0aa>`({{"V", "scalar"}});
	};

Additionally "dependent parameters" can be defined. Dependent parameters are a mechanism for enhanced efficiency when running neuron models. If parameters with model-side meaning, such as time constants or conductances always appear in a certain combination in the model, then it is more efficient to pre-compute this combination and define it as a dependent parameter.

For example, because the equation defining the previous leaky integrator example has an algebraic solution, it can be more accurately solved as follows - using a derived parameter to calculate :math:`\exp\left(\frac{-t}{\tau}\right)` :

.. ref-code-block:: cpp

	class LeakyIntegrator2 : public :ref:`NeuronModels::Base <doxid-df/d1b/class_neuron_models_1_1_base>`
	{
	public:
	    :ref:`DECLARE_MODEL <doxid-d4/d13/models_8h_1ae0c817e85c196f39cf62d608883cda13>`(LeakyIntegrator2, 1, 1);
	    
	    :ref:`SET_SIM_CODE <doxid-de/d5f/neuron_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`("$(V) = $(Isyn) - $(ExpTC)*($(Isyn) - $(V));");
	    
	    :ref:`SET_THRESHOLD_CONDITION_CODE <doxid-de/d5f/neuron_models_8h_1a9c94b28e6356469d85e3376f3336f0a2>`("$(V) >= 1.0");
	    
	    :ref:`SET_PARAM_NAMES <doxid-de/d6c/snippet_8h_1a75315265035fd71c5b5f7d7f449edbd7>`({"tau"});
	    
	    :ref:`SET_VARS <doxid-d4/d13/models_8h_1a3025b9fc844fccdf8cc2b51ef4a6e0aa>`({{"V", "scalar"}});
	    
	    :ref:`SET_DERIVED_PARAMS <doxid-de/d6c/snippet_8h_1aa592bfe3ce05ffc19a8f21d8482add6b>`({
	        {"ExpTC", [](const vector<double> &pars, double dt){ return std::exp(-dt / pars[0]); }}});
	};

GeNN provides several additional features that might be useful when defining more complex neuron models.



.. _doxid-da/ddf/sect_neuron_models_1neuron_support_code:

Support code
------------

Support code enables a code block to be defined that contains supporting code that will be utilized in multiple pieces of user code. Typically, these are functions that are needed in the sim code or threshold condition code. If possible, these should be defined as ``__host__ __device__`` functions so that both GPU and CPU versions of GeNN code have an appropriate support code function available. The support code is protected with a namespace so that it is exclusively available for the neuron population whose neurons define it. Support code is added to a model using the :ref:`SET_SUPPORT_CODE() <doxid-de/d5f/neuron_models_8h_1a11d60ec86ac6804c9c8a133f7bec526d>` macro, for example:

.. ref-code-block:: cpp

	:ref:`SET_SUPPORT_CODE <doxid-de/d5f/neuron_models_8h_1a11d60ec86ac6804c9c8a133f7bec526d>`("__device__ __host__ scalar mysin(float x){ return sin(x); }");





.. _doxid-da/ddf/sect_neuron_models_1neuron_extra_global_param:

Extra global parameters
-----------------------

Extra global parameters are parameters common to all neurons in the population. However, unlike the standard neuron parameters, they can be varied at runtime meaning they could, for example, be used to provide a global reward signal. These parameters are defined by using the :ref:`SET_EXTRA_GLOBAL_PARAMS() <doxid-db/d4c/init_sparse_connectivity_snippet_8h_1aa33e3634a531794ddac1ad49bde09071>` macro to specify a list of variable names and type strings (like the :ref:`SET_VARS() <doxid-d4/d13/models_8h_1a3025b9fc844fccdf8cc2b51ef4a6e0aa>` macro). For example:

.. ref-code-block:: cpp

	:ref:`SET_EXTRA_GLOBAL_PARAMS <doxid-db/d4c/init_sparse_connectivity_snippet_8h_1aa33e3634a531794ddac1ad49bde09071>`({{"R", "float"}});

These variables are available to all neurons in the population. They can also be used in synaptic code snippets; in this case it need to be addressed with a ``_pre`` or ``_post`` postfix.

For example, if the model with the "R" parameter was used for the pre-synaptic neuron population, the weight update model of a synapse population could have simulation code like:

.. ref-code-block:: cpp

	:ref:`SET_SIM_CODE <doxid-de/d5f/neuron_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`("$(x)= $(x)+$(R_pre);");

where we have assumed that the weight update model has a variable ``x`` and our synapse type will only be used in conjunction with pre-synaptic neuron populations that do have the extra global parameter ``R``. If the pre-synaptic population does not have the required variable/parameter, GeNN will fail when compiling the kernels.





.. _doxid-da/ddf/sect_neuron_models_1neuron_additional_input:

Additional input variables
--------------------------

Normally, neuron models receive the linear sum of the inputs coming from all of their synaptic inputs through the $(inSyn) variable. However neuron models can define additional input variables - allowing input from different synaptic inputs to be combined non-linearly. For example, if we wanted our leaky integrator to operate on the the product of two input currents, it could be defined as follows:

.. ref-code-block:: cpp

	:ref:`SET_ADDITIONAL_INPUT_VARS <doxid-de/d5f/neuron_models_8h_1a96a3e23f5c7309a47bc6562e0be81e99>`({{"Isyn2", "scalar", 1.0}});
	:ref:`SET_SIM_CODE <doxid-de/d5f/neuron_models_8h_1a8d014c818d8ee68f3a16838dcd4f030f>`("const scalar input = $(Isyn) * $(Isyn2);\n"
	             "$(V) = input - $(ExpTC)*(input - $(V));");

Where the :ref:`SET_ADDITIONAL_INPUT_VARS() <doxid-de/d5f/neuron_models_8h_1a96a3e23f5c7309a47bc6562e0be81e99>` macro defines the name, type and its initial value before postsynaptic inputs are applyed (see section :ref:`Postsynaptic integration methods <doxid-dd/de4/sect_postsyn>` for more details).





.. _doxid-da/ddf/sect_neuron_models_1neuron_rng:

Random number generation
------------------------

Many neuron models have probabilistic terms, for example a source of noise or a probabilistic spiking mechanism. In GeNN this can be implemented by using the following functions in blocks of model code:

* ``$(gennrand_uniform)`` returns a number drawn uniformly from the interval :math:`[0.0, 1.0]`

* ``$(gennrand_normal)`` returns a number drawn from a normal distribution with a mean of 0 and a standard deviation of 1.

* ``$(gennrand_exponential)`` returns a number drawn from an exponential distribution with :math:`\lambda=1`.

* ``$(gennrand_log_normal, MEAN, STDDEV)`` returns a number drawn from a log-normal distribution with the specified mean and standard deviation.

* ``$(gennrand_gamma, ALPHA)`` returns a number drawn from a gamma distribution with the specified shape.

Once defined in this way, new neuron models classes, can be used in network descriptions by referring to their type e.g.

.. ref-code-block:: cpp

	networkModel.addNeuronPopulation<LeakyIntegrator>("Neurons", 1, 
	                                                  LeakyIntegrator::ParamValues(20.0), // tau
	                                                  LeakyIntegrator::VarValues(0.0)); // V

:ref:`Previous <doxid-de/d42/sect_defining_network>` \| :ref:`Top <doxid-d6/de1/_user_manual>` \| :ref:`Next <doxid-db/d11/sect_synapse_models>`

