.. index:: pair: class; CodeGenerator::Substitutions
.. _doxid-db/d2c/class_code_generator_1_1_substitutions:

class CodeGenerator::Substitutions
==================================

.. toctree::
	:hidden:




.. ref-code-block:: cpp
	:class: doxyrest-overview-code-block

	#include <substitutions.h>
	
	class Substitutions
	{
	public:
		// methods
	
		:target:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions_1a7fe0822b5faffcadce98ffe3b8e10197>`(const Substitutions* parent = nullptr);
	
		:target:`Substitutions<doxid-db/d2c/class_code_generator_1_1_substitutions_1a6e7c057f59d2af8be75d7bd4f81165b7>`(
			const std::vector<:ref:`FunctionTemplate<doxid-d6/d3a/struct_code_generator_1_1_function_template>`>& functions,
			const std::string& ftype
			);
	
		template <typename T>
		void :target:`addVarNameSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1ace9f2d94bf7832f0f538c53d27063540>`(
			const std::vector<T>& variables,
			const std::string& sourceSuffix = "",
			const std::string& destPrefix = "",
			const std::string& destSuffix = ""
			);
	
		void :target:`addParamNameSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a6923e685a841769d7473736f6f0b4aa8>`(
			const std::vector<std::string>& paramNames,
			const std::string& sourceSuffix = "",
			const std::string& destPrefix = "",
			const std::string& destSuffix = ""
			);
	
		template <typename T>
		void :target:`addVarValueSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a2f2f923e25cbc9d17819cc4453482dc8>`(
			const std::vector<T>& variables,
			const std::vector<double>& values,
			const std::string& sourceSuffix = ""
			);
	
		void :target:`addParamValueSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a6e00e02a190497748561fed0e4c937b0>`(
			const std::vector<std::string>& paramNames,
			const std::vector<double>& values,
			const std::string& sourceSuffix = ""
			);
	
		void :target:`addVarSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1ae3ed06630ef19dce975fd16651768c32>`(
			const std::string& source,
			const std::string& destionation,
			bool allowOverride = false
			);
	
		void :target:`addFuncSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a61c71d0dc4863950a652ecce2fa1b843>`(
			const std::string& source,
			unsigned int numArguments,
			const std::string& funcTemplate,
			bool allowOverride = false
			);
	
		bool :target:`hasVarSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a4fd50f7493be2c4951ce0876d0ad55cc>`(const std::string& source) const;
		const std::string& :target:`getVarSubstitution<doxid-db/d2c/class_code_generator_1_1_substitutions_1a83802d6384bbf6422b5af56f6cc64ab0>`(const std::string& source) const;
		void :target:`apply<doxid-db/d2c/class_code_generator_1_1_substitutions_1a6b81121e62bcf604409a0cbaa57de79e>`(std::string& code) const;
	
		void :target:`applyCheckUnreplaced<doxid-db/d2c/class_code_generator_1_1_substitutions_1aa48a70903adfec87e1198f8455e25c83>`(
			std::string& code,
			const std::string& context
			) const;
	
		const std::string :target:`operator []<doxid-db/d2c/class_code_generator_1_1_substitutions_1a524b56ee41ee756c1fff8bae1ddf90d8>` (const std::string& source) const;
	};
