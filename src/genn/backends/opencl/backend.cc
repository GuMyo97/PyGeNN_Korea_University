#include "backend.h"

// Standard C++ includes
#include <algorithm>

// PLOG includes
#include <plog/Log.h>

// GeNN includes
#include "gennUtils.h"
#include "modelSpecInternal.h"

// GeNN code generator includes
#include "code_generator/codeStream.h"
#include "code_generator/substitutions.h"
#include "code_generator/codeGenUtils.h"

// CUDA backend includes
#include "utils.h"

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace {

//--------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------
class Timer {
public:
	// TO BE REVIEWED
	Timer(CodeGenerator::CodeStream& codeStream, const std::string& name, bool timingEnabled, bool synchroniseOnStop = false)
	:	m_CodeStream(codeStream), m_Name(name), m_TimingEnabled(timingEnabled), m_SynchroniseOnStop(synchroniseOnStop) {
		
	}
private:
	//--------------------------------------------------------------------------
	// Members
	//--------------------------------------------------------------------------
	CodeGenerator::CodeStream& m_CodeStream;
	const std::string m_Name;
	const bool m_TimingEnabled;
	const bool m_SynchroniseOnStop;
};
}

namespace CodeGenerator
{
namespace OpenCL
{
const char* Backend::KernelNames[KernelMax] = {
	"updateNeuronsKernel",
	"updatePresynapticKernel",
	"updatePostsynapticKernel",
	"updateSynapseDynamicsKernel",
	"initializeKernel",
	"initializeSparseKernel",
	"preNeuronResetKernel",
	"preSynapseResetKernel" };
//--------------------------------------------------------------------------
Backend::Backend(const KernelWorkGroupSize& kernelWorkGroupSizes, const Preferences& preferences,
	int localHostID, const std::string& scalarType, int device)
	: BackendBase(localHostID, scalarType), m_KernelWorkGroupSizes(kernelWorkGroupSizes), m_Preferences(preferences), m_ChosenDeviceID(device)
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::Backend");
	addDeviceType("cl::Buffer", sizeof(cl::Buffer));
}
//--------------------------------------------------------------------------
void Backend::genNeuronUpdate(CodeStream& os, const ModelSpecInternal& model, NeuronGroupSimHandler simHandler, NeuronGroupHandler wuVarUpdateHandler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genNeuronUpdate");
}
//--------------------------------------------------------------------------
void Backend::genSynapseUpdate(CodeStream& os, const ModelSpecInternal& model,
	SynapseGroupHandler wumThreshHandler, SynapseGroupHandler wumSimHandler, SynapseGroupHandler wumEventHandler,
	SynapseGroupHandler postLearnHandler, SynapseGroupHandler synapseDynamicsHandler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genSynapseUpdate");
}
//--------------------------------------------------------------------------
void Backend::genInit(CodeStream &os, const ModelSpecInternal &model,
                      NeuronGroupHandler localNGHandler, NeuronGroupHandler remoteNGHandler,
                      SynapseGroupHandler sgDenseInitHandler, SynapseGroupHandler sgSparseConnectHandler, 
                      SynapseGroupHandler sgSparseInitHandler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genInit");
}
//--------------------------------------------------------------------------
void Backend::genDefinitionsPreamble(CodeStream& os) const
{
	os << "// Standard C++ includes" << std::endl;
	os << "#include <string>" << std::endl;
	os << "#include <stdexcept>" << std::endl;
	os << std::endl;
	os << "// Standard C includes" << std::endl;
	os << "#include <cstdint>" << std::endl;
	os << std::endl;
	os << "// OpenCL includes" << std::endl;
	os << "#define CL_USE_DEPRECATED_OPENCL_1_2_APIS" << std::endl;
	os << "#include <CL/cl.hpp>" << std::endl;
	os << std::endl;
	os << "#define DEVICE_INDEX " << m_ChosenDeviceID << std::endl;
	os << std::endl;
	os << "// ------------------------------------------------------------------------" << std::endl;
	os << "// Helper macro for error-checking OpenCL calls" << std::endl;
	os << "#define CHECK_OPENCL_ERRORS(call) {\\" << std::endl;
	os << "    cl_int error = call;\\" << std::endl;
	os << "    if (error != CL_SUCCESS) {\\" << std::endl;
	os << "        throw std::runtime_error(__FILE__\": \" + std::to_string(__LINE__) + \": cuda error \" + std::to_string(error) + \": \" + clGetErrorString(error));\\" << std::endl;
	os << "    }\\" << std::endl;
	os << "}" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genDefinitionsInternalPreamble(CodeStream& os) const
{
	// **********************************************************************************
	//! TO BE IMPLEMENTED - The starting of definitionsInternal.h
	
	// Declaration of OpenCL functions
	os << "// ------------------------------------------------------------------------" << std::endl;
	os << "// OpenCL functions declaration" << std::endl;
	os << "// ------------------------------------------------------------------------" << std::endl;
	os << "namespace opencl" << std::endl;
	{
		CodeStream::Scope b(os);
		os << "void setUpContext(cl::Context& context, cl::Device& device, const int deviceIndex);" << std::endl;
		os << "void createProgram(const char* kernelSource, cl::Program& program, cl::Context& context);" << std::endl;
	}
	os << std::endl;
	// **********************************************************************************
}
//--------------------------------------------------------------------------
void Backend::genRunnerPreamble(CodeStream& os) const
{
	// Generating static kernels
	os << "// Initialization kernel" << std::endl;
	os << "const char* initKernelSource = R\"(typedef float scalar; " << std::endl;
	os << "// Will have to read the arguments again and update for the program" << std::endl;
	os << "__kernel void initializeKernel(const unsigned int deviceRNGSeed," << std::endl;
	os << "__global unsigned int* glbSpkCntNeurons," << std::endl;
	os << "__global unsigned int* glbSpkNeurons," << std::endl;
	os << "__global scalar* VNeurons," << std::endl;
	os << "__global scalar* UNeurons)";
	{
		CodeStream::Scope b(os);
		os << "int groupId = get_group_id(0);" << std::endl;
		os << "int localId = get_local_id(0);" << std::endl;
		os << "const unsigned int id = 32 * groupId + localId;" << std::endl;
		os << std::endl;
		os << "if(id < 32)";
		{
			CodeStream::Scope b(os);
			os << "// only do this for existing neurons" << std::endl;
			os << "if(id < 7)";
			{
				CodeStream::Scope b(os);
				os << "if(id == 0)";
				{
					CodeStream::Scope b(os);
					os << "glbSpkCntNeurons[0] = 0;" << std::endl;
				}
				os << "glbSpkNeurons[id] = 0;" << std::endl;
				os << "VNeurons[id] = (-6.50000000000000000e+01f);" << std::endl;
				os << "UNeurons[id] = (-2.00000000000000000e+01f);" << std::endl;
				os << "// current source variables" << std::endl;
			}
		}
	}
	os << ")\";" << std::endl;
	os << std::endl;

	// Implementation of OpenCL functions declared in definitionsInternal
	os << "// ------------------------------------------------------------------------" << std::endl;
	os << "// OpenCL functions implementation" << std::endl;
	os << "// ------------------------------------------------------------------------" << std::endl;
	os << std::endl;
	os << "// Initialize context with the given device" << std::endl;
	os << "void opencl::setUpContext(cl::Context& context, cl::Device& device, const int deviceIndex)";
	{
		CodeStream::Scope b(os);
		os << "// Getting all platforms to gather devices from" << std::endl;
		os << "std::vector<cl::Platform> platforms;" << std::endl;
		os << "cl::Platform::get(&platforms); // Gets all the platforms" << std::endl;
		os << std::endl;
		os << "assert(platforms.size() > 0);" << std::endl;
		os << std::endl;
		os << "// Getting all devices and putting them into a single vector" << std::endl;
		os << "std::vector<cl::Device> devices;" << std::endl;
		os << "for (int i = 0; i < platforms.size(); i++)";
		{
			CodeStream::Scope b(os);
			os << "std::vector<cl::Device> platformDevices;" << std::endl;
			os << "platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &platformDevices);" << std::endl;
			os << "devices.insert(devices.end(), platformDevices.begin(), platformDevices.end());" << std::endl;
		}
		os << std::endl;
		os << "assert(devices.size() > 0);" << std::endl;
		os << std::endl;
		os << "// Check if the device exists at the given index" << std::endl;
		os << "if (deviceIndex >= devices.size())";
		{
			CodeStream::Scope b(os);
			os << "assert(deviceIndex >= devices.size());" << std::endl;
			os << "device = devices.front();" << std::endl;
		}
		os << "else";
		{
			CodeStream::Scope b(os);
			os << "device = devices[deviceIndex]; // We will perform our operations using this device" << std::endl;
		}
		os << std::endl;
		os << "context = cl::Context(device);";
		os << std::endl;
	}
	os << std::endl;
	os << "// Create OpenCL program with the specified device" << std::endl;
	os << "void opencl::createProgram(const char* kernelSource, cl::Program& program, cl::Context& context)";
	{
		CodeStream::Scope b(os);
		os << "// Reading the kernel source for execution" << std::endl;
		os << "program = cl::Program(context, kernelSource, true);" << std::endl;
		os << "program.build(\"-cl-std=CL1.2\");" << std::endl;
	}
	os << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genAllocateMemPreamble(CodeStream& os, const ModelSpecInternal& model) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genAllocateMemPreamble");
}
//--------------------------------------------------------------------------
void Backend::genStepTimeFinalisePreamble(CodeStream& os, const ModelSpecInternal& model) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genStepTimeFinalisePreamble");
}
//--------------------------------------------------------------------------
void Backend::genVariableDefinition(CodeStream& definitions, CodeStream& definitionsInternal, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\n\nBackend::genVariableDefinition called\n\n");
	const bool deviceType = isDeviceType(type);

	if (::Utils::isTypePointer(type)) {
		// Export pointer, either in definitionsInternal if variable has a device type
		// or to definitions if it should be accessable on host
		CodeStream& d = deviceType ? definitionsInternal : definitions;
		d << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
	}
	else {
		if (loc & VarLocation::HOST) {
			if (deviceType) {
				throw std::runtime_error("Variable '" + name + "' is of device-only type '" + type + "' but is located on the host");
			}

			definitions << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
		}
		if (loc & VarLocation::DEVICE) {
			// If the type is a pointer type we need a device pointer
			if (::Utils::isTypePointer(type)) {
				// Write host definition to internal definitions stream if type is device only
				CodeStream& d = deviceType ? definitionsInternal : definitions;
				d << "EXPORT_VAR " << type << " d_" << name << ";" << std::endl;
			}
			// Otherwise we just need a device variable, made volatile for safety
			else {
				definitionsInternal << "EXPORT_VAR cl::Buffer " << " db_" << name << ";" << std::endl;
			}
		}
	}
}
//--------------------------------------------------------------------------
void Backend::genVariableImplementation(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariableImplementation");
}
//--------------------------------------------------------------------------
MemAlloc Backend::genVariableAllocation(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc, size_t count) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariableAllocation");
	return MemAlloc::zero();
}
//--------------------------------------------------------------------------
void Backend::genVariableFree(CodeStream& os, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariableFree");
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamDefinition(CodeStream& definitions, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genExtraGlobalParamDefinition");
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamImplementation(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genExtraGlobalParamImplementation");
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamAllocation(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genExtraGlobalParamAllocation");
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamPush(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genExtraGlobalParamPush");
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamPull(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genExtraGlobalParamPull");
}
//--------------------------------------------------------------------------
void Backend::genPopVariableInit(CodeStream& os, VarLocation, const Substitutions& kernelSubs, Handler handler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genPopVariableInit");
}
//--------------------------------------------------------------------------
void Backend::genVariableInit(CodeStream& os, VarLocation, size_t, const std::string& countVarName,
	const Substitutions& kernelSubs, Handler handler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariableInit");
}
//--------------------------------------------------------------------------
void Backend::genSynapseVariableRowInit(CodeStream& os, VarLocation, const SynapseGroupInternal& sg,
	const Substitutions& kernelSubs, Handler handler) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genSynapseVariableRowInit");
}
//--------------------------------------------------------------------------
void Backend::genVariablePush(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc, bool autoInitialized, size_t count) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariablePush");
}
//--------------------------------------------------------------------------
void Backend::genVariablePull(CodeStream& os, const std::string& type, const std::string& name, VarLocation loc, size_t count) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genVariablePull");
}
//--------------------------------------------------------------------------
void Backend::genCurrentVariablePush(CodeStream& os, const NeuronGroupInternal& ng, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genCurrentVariablePush");
}
//--------------------------------------------------------------------------
void Backend::genCurrentVariablePull(CodeStream& os, const NeuronGroupInternal& ng, const std::string& type, const std::string& name, VarLocation loc) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genCurrentVariablePull");
}
//--------------------------------------------------------------------------
MemAlloc Backend::genGlobalRNG(CodeStream& definitions, CodeStream& definitionsInternal, CodeStream& runner, CodeStream& allocations, CodeStream& free, const ModelSpecInternal&) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genGlobalRNG");
	return MemAlloc::zero();
}
//--------------------------------------------------------------------------
MemAlloc Backend::genPopulationRNG(CodeStream& definitions, CodeStream& definitionsInternal, CodeStream& runner, CodeStream& allocations, CodeStream& free,
	const std::string& name, size_t count) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genPopulationRNG");
	return MemAlloc::zero();
}
//--------------------------------------------------------------------------
void Backend::genTimer(CodeStream&, CodeStream& definitionsInternal, CodeStream& runner, CodeStream& allocations, CodeStream& free,
	CodeStream& stepTimeFinalise, const std::string& name, bool updateInStepTime) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genTimer");
}
//--------------------------------------------------------------------------
void Backend::genMakefilePreamble(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMakefilePreamble");
}
//--------------------------------------------------------------------------
void Backend::genMakefileLinkRule(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMakefileLinkRule");
}
//--------------------------------------------------------------------------
void Backend::genMakefileCompileRule(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMakefileCompileRule");
}
//--------------------------------------------------------------------------
void Backend::genMSBuildConfigProperties(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMSBuildConfigProperties");
}
//--------------------------------------------------------------------------
void Backend::genMSBuildImportProps(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMSBuildImportProps");
}
//--------------------------------------------------------------------------
void Backend::genMSBuildItemDefinitions(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMSBuildItemDefinitions");
}
//--------------------------------------------------------------------------
void Backend::genMSBuildCompileModule(const std::string& moduleName, std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMSBuildCompileModule");
}
//--------------------------------------------------------------------------
void Backend::genMSBuildImportTarget(std::ostream& os) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::genMSBuildImportTarget");
}
//--------------------------------------------------------------------------
bool Backend::isGlobalRNGRequired(const ModelSpecInternal& model) const
{
	printf("\nTO BE IMPLEMENTED: ~virtual~ CodeGenerator::OpenCL::Backend::isGlobalRNGRequired");
	return false;
}
//--------------------------------------------------------------------------
void Backend::genCurrentSpikePull(CodeStream& os, const NeuronGroupInternal& ng, bool spikeEvent) const
{
	printf("\nTO BE IMPLEMENTED: CodeGenerator::OpenCL::Backend::genCurrentSpikePull");
}
//--------------------------------------------------------------------------
void Backend::genCurrentSpikePush(CodeStream& os, const NeuronGroupInternal& ng, bool spikeEvent) const
{
	printf("\nTO BE IMPLEMENTED: CodeGenerator::OpenCL::Backend::genCurrentSpikePush");
}
//--------------------------------------------------------------------------
void Backend::addDeviceType(const std::string& type, size_t size)
{
	addType(type, size);
	m_DeviceTypes.emplace(type);
}
//--------------------------------------------------------------------------
bool Backend::isDeviceType(const std::string& type) const
{
	// Get underlying type
	const std::string underlyingType = ::Utils::isTypePointer(type) ? ::Utils::getUnderlyingType(type) : type;

	// Return true if it is in device types set
	return (m_DeviceTypes.find(underlyingType) != m_DeviceTypes.cend());
}
} // namespace OpenCL
} // namespace CodeGenerator