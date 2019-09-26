.. index:: pair: struct; Models::Base::Var
.. _doxid-db/db6/struct_models_1_1_base_1_1_var:

struct Models::Base::Var
========================

.. toctree::
	:hidden:

Overview
~~~~~~~~

A variable has a name, a type and an access type. :ref:`More...<details-db/db6/struct_models_1_1_base_1_1_var>`


.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <models.h>
	
	struct Var
	{
		// fields
	
		std::string :target:`name<doxid-db/db6/struct_models_1_1_base_1_1_var_1a333472c1ad027594ee870b1994f884b1>`;
		std::string :target:`type<doxid-db/db6/struct_models_1_1_base_1_1_var_1a0cd74662a030e8cd95027844b47f09a0>`;
		:ref:`VarAccess<doxid-d4/d13/models_8h_1a5a5f7e906a7fdc27f3e5eb66b7115240>` :target:`access<doxid-db/db6/struct_models_1_1_base_1_1_var_1a43fa55b9b858bb7b6fd9927267aa61ae>`;

		// methods
	
		:target:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var_1a3f416643a3668eac22768b43bbb42e50>`();
	
		:target:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var_1ad2186427408c204f026878e16e1392a5>`(
			const std::string& n,
			const std::string& t,
			:ref:`VarAccess<doxid-d4/d13/models_8h_1a5a5f7e906a7fdc27f3e5eb66b7115240>` a
			);
	
		:target:`Var<doxid-db/db6/struct_models_1_1_base_1_1_var_1a7e8510b76838b833f738be333cbc8f16>`(
			const std::string& n,
			const std::string& t
			);
	};
.. _details-db/db6/struct_models_1_1_base_1_1_var:

Detailed Documentation
~~~~~~~~~~~~~~~~~~~~~~

A variable has a name, a type and an access type.

Explicit constructors required as although, through the wonders of C++ aggregate initialization, access would default to :ref:`VarAccess::READ_WRITE <doxid-d4/d13/models_8h_1a5a5f7e906a7fdc27f3e5eb66b7115240aa7b843fb734e3b3fea8e5f902d3f4144>` if not specified, this results in a -Wmissing-field-initializers warning on GCC and Clang

