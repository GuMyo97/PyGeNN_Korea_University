#include "backend.h"

// Standard C++ includes
#include <algorithm>
#include <iterator>

// GeNN includes
#include "gennUtils.h"
#include "logging.h"

// GeNN code generator includes
#include "code_generator/codeStream.h"
#include "code_generator/codeGenUtils.h"
#include "code_generator/modelSpecMerged.h"
#include "code_generator/substitutions.h"

// CUDA backend includes
#include "utils.h"

using namespace CodeGenerator;

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace
{
const std::vector<Substitutions::FunctionTemplate> cudaSinglePrecisionFunctions = {
    {"gennrand_uniform", 0, "curand_uniform($(rng))"},
    {"gennrand_normal", 0, "curand_normal($(rng))"},
    {"gennrand_exponential", 0, "exponentialDistFloat($(rng))"},
    {"gennrand_log_normal", 2, "curand_log_normal_float($(rng), $(0), $(1))"},
    {"gennrand_gamma", 1, "gammaDistFloat($(rng), $(0))"}
};
//--------------------------------------------------------------------------
const std::vector<Substitutions::FunctionTemplate> cudaDoublePrecisionFunctions = {
    {"gennrand_uniform", 0, "curand_uniform_double($(rng))"},
    {"gennrand_normal", 0, "curand_normal_double($(rng))"},
    {"gennrand_exponential", 0, "exponentialDistDouble($(rng))"},
    {"gennrand_log_normal", 2, "curand_log_normal_double($(rng), $(0), $(1))"},
    {"gennrand_gamma", 1, "gammaDistDouble($(rng), $(0))"}
};
//--------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------
class Timer
{
public:
    Timer(CodeStream &codeStream, const std::string &name, bool timingEnabled, bool synchroniseOnStop = false)
    :   m_CodeStream(codeStream), m_Name(name), m_TimingEnabled(timingEnabled), m_SynchroniseOnStop(synchroniseOnStop)
    {
        // Record start event
        if(m_TimingEnabled) {
            m_CodeStream << "CHECK_CUDA_ERRORS(cudaEventRecord(" << m_Name << "Start));" << std::endl;
        }
    }

    ~Timer()
    {
        // Record stop event
        if(m_TimingEnabled) {
            m_CodeStream << "CHECK_CUDA_ERRORS(cudaEventRecord(" << m_Name << "Stop));" << std::endl;

            // If we should synchronise on stop, insert call
            if(m_SynchroniseOnStop) {
                m_CodeStream << "CHECK_CUDA_ERRORS(cudaEventSynchronize(" << m_Name << "Stop));" << std::endl;

                m_CodeStream << "float tmp;" << std::endl;
                m_CodeStream << "CHECK_CUDA_ERRORS(cudaEventElapsedTime(&tmp, " << m_Name << "Start, " << m_Name << "Stop));" << std::endl;
                m_CodeStream << m_Name << "Time += tmp / 1000.0;" << std::endl;
            }
        }
    }

private:
    //--------------------------------------------------------------------------
    // Members
    //--------------------------------------------------------------------------
    CodeStream &m_CodeStream;
    const std::string m_Name;
    const bool m_TimingEnabled;
    const bool m_SynchroniseOnStop;
};


//-----------------------------------------------------------------------
void genGroupStartIDs(CodeStream &, size_t&, size_t&, size_t)
{
}
//-----------------------------------------------------------------------
template<typename T, typename G, typename ...Args>
void genGroupStartIDs(CodeStream &os, size_t &idStart, size_t &totalConstMem, size_t blockSize,
                      const std::vector<T> &mergedGroups, G getNumThreads,
                      Args... args)
{
    // Loop through merged groups
    for(const auto &m : mergedGroups) {
        // Calculate size of array
        const size_t sizeBytes = m.getGroups().size() * sizeof(unsigned int);

        // If there is enough constant memory left for group, declare it in constant memory space
        if(sizeBytes < totalConstMem) {
            os << "__device__ __constant__ ";
            totalConstMem -= sizeBytes;
        }
        // Otherwise, declare it in global memory space
        else {
            os << "__device__ ";
        }

        // Declare array of starting thread indices for each neuron group
        os << "unsigned int d_merged" << m.getName() << "GroupStartID" << m.getIndex() << "[] = {";
        for(const auto &ng : m.getGroups()) {
            os << idStart << ", ";
            idStart += padSize(getNumThreads(ng.get()), blockSize);
        }
        os << "};" << std::endl;
    }

    // Generate any remaining groups
    genGroupStartIDs(os, idStart, totalConstMem, blockSize, args...);
}
//-----------------------------------------------------------------------
template<typename ...Args>
void genMergedKernelDataStructures(CodeStream &os, size_t blockSize, size_t &totalConstMem,
                                   Args... args)
{
    // Generate group start id arrays
    size_t idStart = 0;
    genGroupStartIDs(os, std::ref(idStart), std::ref(totalConstMem), blockSize, args...);
}

//-----------------------------------------------------------------------
template<typename T, typename G>
size_t getNumMergedGroupThreads(const std::vector<T> &groups, G getNumThreads)
{
    // Accumulate the accumulation of all groups in merged group
    return std::accumulate(
        groups.cbegin(), groups.cend(), size_t{0},
        [getNumThreads](size_t acc, const T &n)
        {
            return std::accumulate(n.getGroups().cbegin(), n.getGroups().cend(), acc,
                                   [getNumThreads](size_t acc, std::reference_wrapper<const typename T::GroupInternal> g)
                                   {
                                       return acc + getNumThreads(g.get());
                                   });
        });
}
//-----------------------------------------------------------------------
template<typename T>
size_t getGroupStartIDSize(const std::vector<T> &mergedGroups)
{
    // Calculate size of groups
    return std::accumulate(mergedGroups.cbegin(), mergedGroups.cend(),
                           size_t{0}, [](size_t acc, const T &ng)
                           {
                               return acc + (sizeof(unsigned int) * ng.getGroups().size());
                           });
}
//-----------------------------------------------------------------------
const std::vector<Substitutions::FunctionTemplate> &getFunctionTemplates(const std::string &precision)
{
    return (precision == "double") ? cudaDoublePrecisionFunctions : cudaSinglePrecisionFunctions;
}
}   // Anonymous namespace

//--------------------------------------------------------------------------
// CodeGenerator::CUDA::Backend
//--------------------------------------------------------------------------
namespace CodeGenerator
{
namespace CUDA
{
//--------------------------------------------------------------------------
Backend::Backend(const KernelBlockSize &kernelBlockSizes, const Preferences &preferences,
                 const std::string &scalarType, int device)
:   BackendSIMT(kernelBlockSizes, preferences, scalarType), m_ChosenDeviceID(device)
{
    // Set device
    CHECK_CUDA_ERRORS(cudaSetDevice(device));

    // Get device properties
    CHECK_CUDA_ERRORS(cudaGetDeviceProperties(&m_ChosenDevice, device));

    // Get CUDA runtime version
    cudaRuntimeGetVersion(&m_RuntimeVersion);

    // Give a warning if automatic copy is used on pre-Pascal devices
    if(getPreferences().automaticCopy && m_ChosenDevice.major < 6) {
        LOGW << "Using automatic copy on pre-Pascal devices is supported but likely to be very slow - we recommend copying manually on these devices";
    }

    // Add CUDA-specific types, additionally marking them as 'device types' innaccesible to host code
    addDeviceType("curandState", 44);
    addDeviceType("curandStatePhilox4_32_10_t", 64);
    addDeviceType("half", 2);
}
//--------------------------------------------------------------------------
bool Backend::areSharedMemAtomicsSlow() const
{
    // If device is older than Maxwell, we shouldn't use shared memory as atomics are emulated
    // and actually slower than global memory (see https://devblogs.nvidia.com/gpu-pro-tip-fast-histograms-using-shared-atomics-maxwell/)
    return (getChosenCUDADevice().major < 5);
}
//--------------------------------------------------------------------------
std::string Backend::getAtomic(const std::string &type, AtomicOperation op, AtomicMemSpace) const
{
    // If operation is an atomic add
    if(op == AtomicOperation::ADD) {
        if(((getChosenCUDADevice().major < 2) && (type == "float"))
           || (((getChosenCUDADevice().major < 6) || (getRuntimeVersion() < 8000)) && (type == "double")))
        {
            return "atomicAddSW";
        }

        return "atomicAdd";
    }
    // Otherwise, it's an atomic or
    else {
        assert(op == AtomicOperation::OR);
        assert(type == "unsigned int" || type == "int");
        return "atomicOr";
    }
}
//--------------------------------------------------------------------------
void Backend::genSharedMemBarrier(CodeStream &os) const
{
    os << "__syncthreads();" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genPopulationRNGInit(CodeStream &os, const std::string &globalRNG, const std::string &seed, const std::string &sequence) const
{
    os << "curand_init(" << seed << ", " << sequence << ", 0, &" << globalRNG << ");" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genPopulationRNGPreamble(CodeStream &, Substitutions &subs, const std::string &globalRNG, const std::string &name) const
{
    subs.addVarSubstitution(name, "&" + globalRNG);
}
//--------------------------------------------------------------------------
void Backend::genPopulationRNGPostamble(CodeStream&, const std::string&) const
{
}
//--------------------------------------------------------------------------
void Backend::genGlobalRNGSkipAhead(CodeStream &os, Substitutions &subs, const std::string &sequence, const std::string &name) const
{
    // Skipahead RNG
    os << "curandStatePhilox4_32_10_t localRNG = d_rng;" << std::endl;
    os << "skipahead_sequence((unsigned long long)" << sequence << ", &localRNG);" << std::endl;

    // Add substitution for RNG
    subs.addVarSubstitution(name, "&localRNG");
}
//--------------------------------------------------------------------------
void Backend::genNeuronUpdate(CodeStream &os, ModelSpecMerged &modelMerged, MemorySpaces &memorySpaces,
                              HostHandler preambleHandler, NeuronGroupSimHandler simHandler, NeuronUpdateGroupMergedHandler wuVarUpdateHandler,
                              HostHandler pushEGPHandler) const
{
    
    const ModelSpecInternal &model = modelMerged.getModel();

    // Create string stream to generate body into so it can be written after structures
    std::ostringstream bodyStream;
    CodeStream body(bodyStream);

    // Generate reset kernel to be run before the neuron kernel
    size_t idPreNeuronReset = 0;
    body << "extern \"C\" __global__ void " << KernelNames[KernelPreNeuronReset] << "()";
    {
        CodeStream::Scope b(body);

        body << "const unsigned int id = " << getKernelBlockSize(KernelPreNeuronReset) << " * blockIdx.x + threadIdx.x;" << std::endl;

        genPreNeuronResetKernel(body, modelMerged, idPreNeuronReset);
    }
    body << std::endl;

    size_t idStart = 0;
    body << "extern \"C\" __global__ void " << KernelNames[KernelNeuronUpdate] << "(" << model.getTimePrecision() << " t";
    if(model.isRecordingInUse()) {
        body << ", unsigned int recordingTimestep";
    }
    body << ")" << std::endl;
    {
        CodeStream::Scope b(body);
        body << "const unsigned int id = " << getKernelBlockSize(KernelNeuronUpdate) << " * blockIdx.x + threadIdx.x; " << std::endl;

        Substitutions kernelSubs(getFunctionTemplates(model.getPrecision()));
        kernelSubs.addVarSubstitution("t", "t");

        genNeuronUpdateKernel(body, kernelSubs, modelMerged, simHandler, wuVarUpdateHandler, idStart);
    }

    body << "void updateNeurons(" << model.getTimePrecision() << " t";
    if(model.isRecordingInUse()) {
        body << ", unsigned int recordingTimestep";
    }
    body << ")";
    {
        CodeStream::Scope b(body);

        // Push any required EGPS
        pushEGPHandler(body);

        if(idPreNeuronReset > 0) {
            CodeStream::Scope b(body);
            genKernelDimensions(body, KernelPreNeuronReset, idPreNeuronReset);
            body << KernelNames[KernelPreNeuronReset] << "<<<grid, threads>>>();" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }
        if(idStart > 0) {
            CodeStream::Scope b(body);

            Timer t(body, "neuronUpdate", model.isTimingEnabled());

            genKernelDimensions(body, KernelNeuronUpdate, idStart);
            body << KernelNames[KernelNeuronUpdate] << "<<<grid, threads>>>(t";
            if(model.isRecordingInUse()) {
                body << ", recordingTimestep";
            }
            body << ");" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }
    }

    // Now that data required in structure is determined, generate struct definitions
    modelMerged.genMergedNeuronUpdateGroupStructs(os, *this);
    modelMerged.genMergedNeuronSpikeQueueUpdateStructs(os, *this);

    // Generate arrays of merged structs and functions to push them
    genMergedStructArrayPush(os, modelMerged.getMergedNeuronSpikeQueueUpdateGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedNeuronUpdateGroups(), memorySpaces);

    // Generate preamble
    preambleHandler(os);

    // Generate data structure for accessing merged groups
    // **NOTE** constant cache is preferentially given to synapse groups as, typically, more synapse kernels are launched
    // so subtract constant memory requirements of synapse group start ids from total constant memory
    const size_t synapseGroupStartIDSize = (getGroupStartIDSize(modelMerged.getMergedPresynapticUpdateGroups()) +
                                            getGroupStartIDSize(modelMerged.getMergedPostsynapticUpdateGroups()) +
                                            getGroupStartIDSize(modelMerged.getMergedSynapseDynamicsGroups()));
    size_t totalConstMem = (getChosenDeviceSafeConstMemBytes() > synapseGroupStartIDSize) ? (getChosenDeviceSafeConstMemBytes() - synapseGroupStartIDSize) : 0;
    genMergedKernelDataStructures(os, getKernelBlockSize(KernelNeuronUpdate), totalConstMem,
                                  modelMerged.getMergedNeuronUpdateGroups(),
                                  [](const NeuronGroupInternal &ng){ return ng.getNumNeurons(); });
    
    // Write body back to stream
    os << std::endl;
    os << bodyStream.str();
}
//--------------------------------------------------------------------------
void Backend::genSynapseUpdate(CodeStream &os, ModelSpecMerged &modelMerged, MemorySpaces &memorySpaces,
                               HostHandler preambleHandler, SynapseGroupMergedHandler wumThreshHandler, SynapseGroupMergedHandler wumSimHandler,
                               SynapseGroupMergedHandler wumEventHandler, SynapseGroupMergedHandler wumProceduralConnectHandler,
                               SynapseGroupMergedHandler postLearnHandler, SynapseGroupMergedHandler synapseDynamicsHandler,
                               HostHandler pushEGPHandler) const
{
     // Create string stream to generate body into so it can be written after structures
    std::ostringstream bodyStream;
    CodeStream body(bodyStream);

    // If any synapse groups require dendritic delay, a reset kernel is required to be run before the synapse kernel
    const ModelSpecInternal &model = modelMerged.getModel();
    size_t idPreSynapseReset = 0;
    if(!modelMerged.getMergedSynapseDendriticDelayUpdateGroups().empty()) {
        body << "extern \"C\" __global__ void " << KernelNames[KernelPreSynapseReset] << "()";
        {
            CodeStream::Scope b(body);

            body << "const unsigned int id = " << getKernelBlockSize(KernelPreSynapseReset) << " * blockIdx.x + threadIdx.x;" << std::endl;

            genPreSynapseResetKernel(body, modelMerged, idPreSynapseReset);
        }
        body << std::endl;
    }

    // If there are any presynaptic update groups
    size_t idPresynapticStart = 0;
    if(!modelMerged.getMergedPresynapticUpdateGroups().empty()) {
        body << "extern \"C\" __global__ void " << KernelNames[KernelPresynapticUpdate] << "(" << model.getTimePrecision() << " t)" << std::endl; // end of synapse kernel header
        {
            CodeStream::Scope b(body);

            Substitutions kernelSubs((model.getPrecision() == "double") ? cudaDoublePrecisionFunctions : cudaSinglePrecisionFunctions);
            kernelSubs.addVarSubstitution("t", "t");

            body << "const unsigned int id = " << getKernelBlockSize(KernelPresynapticUpdate) << " * blockIdx.x + threadIdx.x; " << std::endl;

            genPresynapticUpdateKernel(body, kernelSubs, modelMerged, wumThreshHandler, wumSimHandler, 
                                       wumEventHandler, wumProceduralConnectHandler, idPresynapticStart);
        }
    }

    // If any synapse groups require postsynaptic learning
    size_t idPostsynapticStart = 0;
    if(!modelMerged.getMergedPostsynapticUpdateGroups().empty()) {
        body << "extern \"C\" __global__ void " << KernelNames[KernelPostsynapticUpdate] << "(" << model.getTimePrecision() << " t)" << std::endl;
        {
            CodeStream::Scope b(body);

            Substitutions kernelSubs((model.getPrecision() == "double") ? cudaDoublePrecisionFunctions : cudaSinglePrecisionFunctions);
            kernelSubs.addVarSubstitution("t", "t");

            body << "const unsigned int id = " << getKernelBlockSize(KernelPostsynapticUpdate) << " * blockIdx.x + threadIdx.x; " << std::endl;

            genPostsynapticUpdateKernel(body, kernelSubs, modelMerged, postLearnHandler, idPostsynapticStart);
        }
    }

    size_t idSynapseDynamicsStart = 0;
    if(!modelMerged.getMergedSynapseDynamicsGroups().empty()) {
        body << "extern \"C\" __global__ void " << KernelNames[KernelSynapseDynamicsUpdate] << "(" << model.getTimePrecision() << " t)" << std::endl; // end of synapse kernel header
        {
            CodeStream::Scope b(body);
            body << "const unsigned int id = " << getKernelBlockSize(KernelSynapseDynamicsUpdate) << " * blockIdx.x + threadIdx.x;" << std::endl;

            Substitutions kernelSubs(getFunctionTemplates(model.getPrecision()));
            kernelSubs.addVarSubstitution("t", "t");

            genSynapseDynamicsKernel(body, kernelSubs, modelMerged, synapseDynamicsHandler, idSynapseDynamicsStart);
        }
    }

    body << "void updateSynapses(" << model.getTimePrecision() << " t)";
    {
        CodeStream::Scope b(body);

        // Push any required EGPs
        pushEGPHandler(body);

        // Launch pre-synapse reset kernel if required
        if(idPreSynapseReset > 0) {
            CodeStream::Scope b(body);
            genKernelDimensions(body, KernelPreSynapseReset, idPreSynapseReset);
            body << KernelNames[KernelPreSynapseReset] << "<<<grid, threads>>>();" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }

        // Launch synapse dynamics kernel if required
        if(idSynapseDynamicsStart > 0) {
            CodeStream::Scope b(body);
            Timer t(body, "synapseDynamics", model.isTimingEnabled());

            genKernelDimensions(body, KernelSynapseDynamicsUpdate, idSynapseDynamicsStart);
            body << KernelNames[KernelSynapseDynamicsUpdate] << "<<<grid, threads>>>(t);" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }

        // Launch presynaptic update kernel
        if(idPresynapticStart > 0) {
            CodeStream::Scope b(body);
            Timer t(body, "presynapticUpdate", model.isTimingEnabled());

            genKernelDimensions(body, KernelPresynapticUpdate, idPresynapticStart);
            body << KernelNames[KernelPresynapticUpdate] << "<<<grid, threads>>>(t);" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }

        // Launch postsynaptic update kernel
        if(idPostsynapticStart > 0) {
            CodeStream::Scope b(body);
            Timer t(body, "postsynapticUpdate", model.isTimingEnabled());

            genKernelDimensions(body, KernelPostsynapticUpdate, idPostsynapticStart);
            body << KernelNames[KernelPostsynapticUpdate] << "<<<grid, threads>>>(t);" << std::endl;
            body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
        }
    }

     // Now that data required in structure is determined, generate struct definitions
    modelMerged.genMergedSynapseDendriticDelayUpdateStructs(os, *this);
    modelMerged.genMergedPresynapticUpdateGroupStructs(os, *this);
    modelMerged.genMergedPostsynapticUpdateGroupStructs(os, *this);
    modelMerged.genMergedSynapseDynamicsGroupStructs(os, *this);

    // Generate arrays of merged structs and functions to push them
    genMergedStructArrayPush(os, modelMerged.getMergedSynapseDendriticDelayUpdateGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedPresynapticUpdateGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedPostsynapticUpdateGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedSynapseDynamicsGroups(), memorySpaces);

    // Generate preamble
    preambleHandler(os);

    // Generate data structure for accessing merged groups
    size_t totalConstMem = getChosenDeviceSafeConstMemBytes();
    genMergedKernelDataStructures(os, getKernelBlockSize(KernelPresynapticUpdate), totalConstMem, modelMerged.getMergedPresynapticUpdateGroups(),
                                  [this](const SynapseGroupInternal &sg)
                                  {
                                      return getNumPresynapticUpdateThreads(sg, getPreferences());
                                  });
    genMergedKernelDataStructures(os, getKernelBlockSize(KernelPostsynapticUpdate), totalConstMem, modelMerged.getMergedPostsynapticUpdateGroups(),
                                  [](const SynapseGroupInternal &sg){ return getNumPostsynapticUpdateThreads(sg); });

    genMergedKernelDataStructures(os, getKernelBlockSize(KernelSynapseDynamicsUpdate), totalConstMem, modelMerged.getMergedSynapseDynamicsGroups(),
                                  [](const SynapseGroupInternal &sg){ return getNumSynapseDynamicsThreads(sg); });

    // Write body back to stream
    os << std::endl;
    os << bodyStream.str();
}
//--------------------------------------------------------------------------
void Backend::genInit(CodeStream &os, ModelSpecMerged &modelMerged, MemorySpaces &memorySpaces,
                      HostHandler preambleHandler, NeuronInitGroupMergedHandler localNGHandler, SynapseGroupMergedHandler sgDenseInitHandler,
                      SynapseGroupMergedHandler sgSparseConnectHandler, SynapseGroupMergedHandler sgKernelInitHandler, 
                      SynapseGroupMergedHandler sgSparseInitHandler, HostHandler initPushEGPHandler, HostHandler initSparsePushEGPHandler) const
{
    const ModelSpecInternal &model = modelMerged.getModel();

    os << "#include <iostream>" << std::endl;
    os << "#include <random>" << std::endl;
    os << "#include <cstdint>" << std::endl;
    os << std::endl;

    // Create string stream to generate body into so it can be written after structures
    std::ostringstream bodyStream;
    CodeStream body(bodyStream);

    // If device RNG is required, generate kernel to initialise it
    if(isGlobalDeviceRNGRequired(modelMerged)) {
        body << "extern \"C\" __global__ void initializeRNGKernel(unsigned long long deviceRNGSeed)";
        {
            CodeStream::Scope b(body);
            body << "if(threadIdx.x == 0)";
            {
                CodeStream::Scope b(body);
                body << "curand_init(deviceRNGSeed, 0, 0, &d_rng);" << std::endl;
            }
        }
        body << std::endl;
    }

    // init kernel header
    body << "extern \"C\" __global__ void " << KernelNames[KernelInitialize] << "(unsigned long long deviceRNGSeed)";

    // initialization kernel code
    size_t idInitStart = 0;
    {
        Substitutions kernelSubs(getFunctionTemplates(model.getPrecision()));

        // common variables for all cases
        CodeStream::Scope b(body);

        body << "const unsigned int id = " << getKernelBlockSize(KernelInitialize) << " * blockIdx.x + threadIdx.x;" << std::endl;
        genInitializeKernel(body, kernelSubs, modelMerged, localNGHandler, 
                            sgDenseInitHandler, sgSparseConnectHandler, 
                            sgKernelInitHandler, idInitStart);
    }
    const size_t numStaticInitThreads = idInitStart;

    // Sparse initialization kernel code
    size_t idSparseInitStart = 0;
    if(!modelMerged.getMergedSynapseSparseInitGroups().empty()) {
        body << "extern \"C\" __global__ void " << KernelNames[KernelInitializeSparse] << "()";
        {
            CodeStream::Scope b(body);

            // common variables for all cases
            Substitutions kernelSubs(getFunctionTemplates(model.getPrecision()));

            body << "const unsigned int id = " << getKernelBlockSize(KernelInitializeSparse) << " * blockIdx.x + threadIdx.x;" << std::endl;
            genInitializeSparseKernel(body, kernelSubs, modelMerged, sgSparseInitHandler, numStaticInitThreads, idSparseInitStart);
        }
    }

    body << "void initialize()";
    {
        CodeStream::Scope b(body);

        body << "unsigned long long deviceRNGSeed = 0;" << std::endl;

        // If any sort of on-device global RNG is required
        const bool simRNGRequired = std::any_of(model.getNeuronGroups().cbegin(), model.getNeuronGroups().cend(),
                                                [](const ModelSpec::NeuronGroupValueType &n) { return n.second.isSimRNGRequired(); });
        const bool globalDeviceRNGRequired = isGlobalDeviceRNGRequired(modelMerged);
        if(simRNGRequired || globalDeviceRNGRequired) {
            // If no seed is specified
            if (model.getSeed() == 0) {
                CodeStream::Scope b(body);

                // Use system randomness to generate one unsigned long long worth of seed words
                body << "std::random_device seedSource;" << std::endl;
                body << "uint32_t *deviceRNGSeedWord = reinterpret_cast<uint32_t*>(&deviceRNGSeed);" << std::endl;
                body << "for(int i = 0; i < " << sizeof(unsigned long long) / sizeof(uint32_t) << "; i++)";
                {
                    CodeStream::Scope b(body);
                    body << "deviceRNGSeedWord[i] = seedSource();" << std::endl;
                }
            }
            // Otherwise, use model seed
            else {
                body << "deviceRNGSeed = " << model.getSeed() << ";" << std::endl;
            }

            // If global RNG is required, launch kernel to initalize it
            if (globalDeviceRNGRequired) {
                body << "initializeRNGKernel<<<1, 1>>>(deviceRNGSeed);" << std::endl;
                body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
            }
        }

        for(const auto &s : model.getSynapseGroups()) {
            // If this synapse population has BITMASK connectivity and is intialised on device, insert a call to cudaMemset to zero the whole bitmask
            if(s.second.isSparseConnectivityInitRequired() && s.second.getMatrixType() & SynapseMatrixConnectivity::BITMASK) {
                const size_t gpSize = ceilDivide((size_t)s.second.getSrcNeuronGroup()->getNumNeurons() * getSynapticMatrixRowStride(s.second), 32);
                body << "CHECK_CUDA_ERRORS(cudaMemset(d_gp" << s.first << ", 0, " << gpSize << " * sizeof(uint32_t)));" << std::endl;
            }
            // Otherwise, if this synapse population has RAGGED connectivity and has postsynaptic learning, insert a call to cudaMemset to zero column lengths
            else if((s.second.getMatrixType() & SynapseMatrixConnectivity::SPARSE) && !s.second.getWUModel()->getLearnPostCode().empty()) {
                body << "CHECK_CUDA_ERRORS(cudaMemset(d_colLength" << s.first << ", 0, " << s.second.getTrgNeuronGroup()->getNumNeurons() << " * sizeof(unsigned int)));" << std::endl;
            }
        }

        // Push any required EGPs
        initPushEGPHandler(body);

        // If there are any initialisation threads
        if(idInitStart > 0) {
            CodeStream::Scope b(body);
            {
                Timer t(body, "init", model.isTimingEnabled(), true);

                genKernelDimensions(body, KernelInitialize, idInitStart);
                body << KernelNames[KernelInitialize] << "<<<grid, threads>>>(deviceRNGSeed);" << std::endl;
                body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
            }
        }
    }
    body << std::endl;
    body << "void initializeSparse()";
    {
        CodeStream::Scope b(body);

        // Push any required EGPs
        initSparsePushEGPHandler(body);

        // Copy all uninitialised state variables to device
        if(!getPreferences().automaticCopy) {
            body << "copyStateToDevice(true);" << std::endl;
            body << "copyConnectivityToDevice(true);" << std::endl << std::endl;
        }

        // If there are any sparse initialisation threads
        if(idSparseInitStart > 0) {
            CodeStream::Scope b(body);
            {
                Timer t(body, "initSparse", model.isTimingEnabled(), true);

                genKernelDimensions(body, KernelInitializeSparse, idSparseInitStart);
                body << KernelNames[KernelInitializeSparse] << "<<<grid, threads>>>();" << std::endl;
                body << "CHECK_CUDA_ERRORS(cudaPeekAtLastError());" << std::endl;
            }
        }
    }

    // Now that data required in structure is determined, generate struct definitions
    modelMerged.genMergedNeuronInitGroupStructs(os, *this);
    modelMerged.genMergedSynapseDenseInitGroupStructs(os, *this);
    modelMerged.genMergedSynapseConnectivityInitGroupStructs(os, *this);
    modelMerged.genMergedSynapseSparseInitGroupStructs(os, *this);
    
    // Generate arrays of merged structs and functions to push them
    genMergedStructArrayPush(os, modelMerged.getMergedNeuronInitGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedSynapseDenseInitGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedSynapseConnectivityInitGroups(), memorySpaces);
    genMergedStructArrayPush(os, modelMerged.getMergedSynapseSparseInitGroups(), memorySpaces);

    // Generate preamble
    preambleHandler(os);

    // Generate data structure for accessing merged groups from within initialisation kernel
    // **NOTE** pass in zero constant cache here as it's precious and would be wasted on init kernels which are only launched once
    size_t totalConstMem = 0;
    genMergedKernelDataStructures(os, getKernelBlockSize(KernelInitialize), totalConstMem,
                                  modelMerged.getMergedNeuronInitGroups(), [](const NeuronGroupInternal &ng){ return ng.getNumNeurons(); },
                                  modelMerged.getMergedSynapseDenseInitGroups(), [](const SynapseGroupInternal &sg){ return sg.getTrgNeuronGroup()->getNumNeurons(); },
                                  modelMerged.getMergedSynapseConnectivityInitGroups(), [](const SynapseGroupInternal &sg){ return sg.getSrcNeuronGroup()->getNumNeurons(); });

    // Generate data structure for accessing merged groups from within sparse initialisation kernel
    genMergedKernelDataStructures(os, getKernelBlockSize(KernelInitializeSparse), totalConstMem,
                                  modelMerged.getMergedSynapseSparseInitGroups(), [](const SynapseGroupInternal &sg){ return sg.getMaxConnections(); });
    
    // Write body back to stream
    os << std::endl;
    os << bodyStream.str();
}
//--------------------------------------------------------------------------
void Backend::genDefinitionsPreamble(CodeStream &os, const ModelSpecMerged &) const
{
    os << "// Standard C++ includes" << std::endl;
    os << "#include <random>" << std::endl;
    os << "#include <string>" << std::endl;
    os << "#include <stdexcept>" << std::endl;
    os << std::endl;
    os << "// Standard C includes" << std::endl;
    os << "#include <cassert>" << std::endl;
    os << "#include <cstdint>" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genDefinitionsInternalPreamble(CodeStream &os, const ModelSpecMerged &) const
{
    os << "// CUDA includes" << std::endl;
    os << "#include <curand_kernel.h>" << std::endl;
    if(getRuntimeVersion() >= 9000) {
        os <<"#include <cuda_fp16.h>" << std::endl;
    }
    os << std::endl;
    os << "// ------------------------------------------------------------------------" << std::endl;
    os << "// Helper macro for error-checking CUDA calls" << std::endl;
    os << "#define CHECK_CUDA_ERRORS(call) {\\" << std::endl;
    os << "    cudaError_t error = call;\\" << std::endl;
    os << "    if (error != cudaSuccess) {\\" << std::endl;
    os << "        throw std::runtime_error(__FILE__\": \" + std::to_string(__LINE__) + \": cuda error \" + std::to_string(error) + \": \" + cudaGetErrorString(error));\\" << std::endl;
    os << "    }\\" << std::endl;
    os << "}" << std::endl;
    os << std::endl;
    os << "#define SUPPORT_CODE_FUNC __device__ __host__ inline" << std::endl;
    os << std::endl;

    // If device is older than SM 6 or we're using a version of CUDA older than 8
    if ((getChosenCUDADevice().major < 6) || (getRuntimeVersion() < 8000)){
        os << "// software version of atomic add for double precision" << std::endl;
        os << "__device__ inline double atomicAddSW(double* address, double val)";
        {
            CodeStream::Scope b(os);
            os << "unsigned long long int* address_as_ull = (unsigned long long int*)address;" << std::endl;
            os << "unsigned long long int old = *address_as_ull, assumed;" << std::endl;
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "assumed = old;" << std::endl;
                os << "old = atomicCAS(address_as_ull, assumed, __double_as_longlong(val + __longlong_as_double(assumed)));" << std::endl;
            }
            os << "while (assumed != old);" << std::endl;
            os << "return __longlong_as_double(old);" << std::endl;
        }
        os << std::endl;
    }

    // If we're using a CUDA device with SM < 2
    if (getChosenCUDADevice().major < 2) {
        os << "// software version of atomic add for single precision float" << std::endl;
        os << "__device__ inline float atomicAddSW(float* address, float val)" << std::endl;
        {
            CodeStream::Scope b(os);
            os << "int* address_as_ull = (int*)address;" << std::endl;
            os << "int old = *address_as_ull, assumed;" << std::endl;
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "assumed = old;" << std::endl;
                os << "old = atomicCAS(address_as_ull, assumed, __float_as_int(val + __int_as_float(assumed)));" << std::endl;
            }
            os << "while (assumed != old);" << std::endl;
            os << "return __int_as_float(old);" << std::endl;
        }
        os << std::endl;
    }
    os << std::endl;
    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline float exponentialDistFloat(RNG *rng)";
    {
        CodeStream::Scope b(os);
        os << "while (true)";
        {
            CodeStream::Scope b(os);
            os << "const float u = curand_uniform(rng);" << std::endl;
            os << "if (u != 0.0f)";
            {
                CodeStream::Scope b(os);
                os << "return -logf(u);" << std::endl;
            }
        }
    }
    os << std::endl;
    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline double exponentialDistDouble(RNG *rng)";
    {
        CodeStream::Scope b(os);
        os << "while (true)";
        {
            CodeStream::Scope b(os);
            os << "const double u = curand_uniform_double(rng);" << std::endl;
            os << "if (u != 0.0)";
            {
                CodeStream::Scope b(os);
                os << "return -log(u);" << std::endl;
            }
        }
    }
    os << std::endl;

    // Generate gamma-distributed variates using Marsaglia and Tsang's method
    // G. Marsaglia and W. Tsang. A simple method for generating gamma variables. ACM Transactions on Mathematical Software, 26(3):363-372, 2000.
    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline float gammaDistFloatInternal(RNG *rng, float c, float d)" << std::endl;
    {
        CodeStream::Scope b(os);
        os << "float x, v, u;" << std::endl;
        os << "while (true)";
        {
            CodeStream::Scope b(os);
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "x = curand_normal(rng);" << std::endl;
                os << "v = 1.0f + c*x;" << std::endl;
            }
            os << "while (v <= 0.0f);" << std::endl;
            os << std::endl;
            os << "v = v*v*v;" << std::endl;
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "u = curand_uniform(rng);" << std::endl;
            }
            os << "while (u == 1.0f);" << std::endl;
            os << std::endl;
            os << "if (u < 1.0f - 0.0331f*x*x*x*x) break;" << std::endl;
            os << "if (logf(u) < 0.5f*x*x + d*(1.0f - v + logf(v))) break;" << std::endl;
        }
        os << std::endl;
        os << "return d*v;" << std::endl;
    }
    os << std::endl;
    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline float gammaDistFloat(RNG *rng, float a)" << std::endl;
    {
        CodeStream::Scope b(os);
        os << "if (a > 1)" << std::endl;
        {
            CodeStream::Scope b(os);
            os << "const float u = curand_uniform (rng);" << std::endl;
            os << "const float d = (1.0f + a) - 1.0f / 3.0f;" << std::endl;
            os << "const float c = (1.0f / 3.0f) / sqrtf(d);" << std::endl;
            os << "return gammaDistFloatInternal (rng, c, d) * powf(u, 1.0f / a);" << std::endl;
        }
        os << "else" << std::endl;
        {
            CodeStream::Scope b(os);
            os << "const float d = a - 1.0f / 3.0f;" << std::endl;
            os << "const float c = (1.0f / 3.0f) / sqrtf(d);" << std::endl;
            os << "return gammaDistFloatInternal(rng, c, d);" << std::endl;
        }
    }
    os << std::endl;

    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline float gammaDistDoubleInternal(RNG *rng, double c, double d)" << std::endl;
    {
        CodeStream::Scope b(os);
        os << "double x, v, u;" << std::endl;
        os << "while (true)";
        {
            CodeStream::Scope b(os);
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "x = curand_normal_double(rng);" << std::endl;
                os << "v = 1.0 + c*x;" << std::endl;
            }
            os << "while (v <= 0.0);" << std::endl;
            os << std::endl;
            os << "v = v*v*v;" << std::endl;
            os << "do";
            {
                CodeStream::Scope b(os);
                os << "u = curand_uniform_double(rng);" << std::endl;
            }
            os << "while (u == 1.0);" << std::endl;
            os << std::endl;
            os << "if (u < 1.0 - 0.0331*x*x*x*x) break;" << std::endl;
            os << "if (log(u) < 0.5*x*x + d*(1.0 - v + log(v))) break;" << std::endl;
        }
        os << std::endl;
        os << "return d*v;" << std::endl;
    }
    os << std::endl;

    os << "template<typename RNG>" << std::endl;
    os << "__device__ inline float gammaDistDouble(RNG *rng, double a)" << std::endl;
    {
        CodeStream::Scope b(os);
        os << "if (a > 1.0)" << std::endl;
        {
            CodeStream::Scope b(os);
            os << "const double u = curand_uniform (rng);" << std::endl;
            os << "const double d = (1.0 + a) - 1.0 / 3.0;" << std::endl;
            os << "const double c = (1.0 / 3.0) / sqrt(d);" << std::endl;
            os << "return gammaDistDoubleInternal (rng, c, d) * pow(u, 1.0 / a);" << std::endl;
        }
        os << "else" << std::endl;
        {
            CodeStream::Scope b(os);
            os << "const float d = a - 1.0 / 3.0;" << std::endl;
            os << "const float c = (1.0 / 3.0) / sqrt(d);" << std::endl;
            os << "return gammaDistDoubleInternal(rng, c, d);" << std::endl;
        }
    }
    os << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genRunnerPreamble(CodeStream &os, const ModelSpecMerged &) const
{
#ifdef _WIN32
    // **YUCK** on Windows, disable "function assumed not to throw an exception but does" warning
    // Setting /Ehs SHOULD solve this but CUDA rules don't give this option and it's not clear it gets through to the compiler anyway
    os << "#pragma warning(disable: 4297)" << std::endl;
#else
    // Prevent unused parameter warning
    (void)os;
#endif
}
//--------------------------------------------------------------------------
void Backend::genAllocateMemPreamble(CodeStream &os, const ModelSpecMerged &modelMerged) const
{
    // Get chosen device's PCI bus ID
    char pciBusID[32];
    CHECK_CUDA_ERRORS(cudaDeviceGetPCIBusId(pciBusID, 32, m_ChosenDeviceID));

    // If the model requires zero-copy
    if(modelMerged.getModel().zeroCopyInUse()) {
        // If device doesn't support mapping host memory error
        if(!getChosenCUDADevice().canMapHostMemory) {
            throw std::runtime_error("Device does not support mapping CPU host memory!");
        }

        // set appropriate device flags
        os << "CHECK_CUDA_ERRORS(cudaSetDeviceFlags(cudaDeviceMapHost));" << std::endl;
        os << std::endl;
    }
    
    // If we should select GPU by device ID, do so
    if(getPreferences<Preferences>().selectGPUByDeviceID) {
        os << "CHECK_CUDA_ERRORS(cudaSetDevice(" << m_ChosenDeviceID << "));" << std::endl;
    }
    // Otherwise, write code to get device by PCI bus ID
    // **NOTE** this is required because device IDs are not guaranteed to remain the same and we want the code to be run on the same GPU it was optimise for
    else {
        os << "int deviceID;" << std::endl;
        os << "CHECK_CUDA_ERRORS(cudaDeviceGetByPCIBusId(&deviceID, \"" << pciBusID << "\"));" << std::endl;
        os << "CHECK_CUDA_ERRORS(cudaSetDevice(deviceID));" << std::endl;
    }
    os << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genStepTimeFinalisePreamble(CodeStream &os, const ModelSpecMerged &modelMerged) const
{
    // Synchronise if automatic copying or zero-copy are in use
    // **THINK** Is this only required with automatic copy on older SM, CUDA and on non-Linux?
    if(getPreferences().automaticCopy || modelMerged.getModel().zeroCopyInUse()) {
        os << "CHECK_CUDA_ERRORS(cudaDeviceSynchronize());" << std::endl;
    }

    // If timing is enabled, synchronise last event
    if(modelMerged.getModel().isTimingEnabled()) {
        os << "CHECK_CUDA_ERRORS(cudaEventSynchronize(neuronUpdateStop));" << std::endl;
    }
}
//--------------------------------------------------------------------------
void Backend::genVariableDefinition(CodeStream &definitions, CodeStream &definitionsInternal, const std::string &type, const std::string &name, VarLocation loc) const
{
    const bool deviceType = isDeviceType(type);

    if(getPreferences().automaticCopy && ::Utils::isTypePointer(type)) {
        // Export pointer, either in definitionsInternal if variable has a device type
        // or to definitions if it should be accessable on host
        CodeStream &d = deviceType ? definitionsInternal : definitions;
        d << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
    }
    else {
        if(loc & VarLocation::HOST) {
            if(deviceType) {
                throw std::runtime_error("Variable '" + name + "' is of device-only type '" + type + "' but is located on the host");
            }

            definitions << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
        }
        if(loc & VarLocation::DEVICE) {
            // If the type is a pointer type we need a device pointer
            if(::Utils::isTypePointer(type)) {
                // Write host definition to internal definitions stream if type is device only
                CodeStream &d = deviceType ? definitionsInternal : definitions;
                d << "EXPORT_VAR " << type << " d_" << name << ";" << std::endl;
            }
            // Otherwise we just need a device variable, made volatile for safety
            else {
                definitionsInternal << "EXPORT_VAR __device__ volatile " << type << " d_" << name << ";" << std::endl;
            }
        }
    }


}
//--------------------------------------------------------------------------
void Backend::genVariableImplementation(CodeStream &os, const std::string &type, const std::string &name, VarLocation loc) const
{
    if(getPreferences().automaticCopy && ::Utils::isTypePointer(type)) {
        os << type << " " << name << ";" << std::endl;
    }
    else {
        if(loc & VarLocation::HOST) {
            os << type << " " << name << ";" << std::endl;
        }
        if(loc & VarLocation::DEVICE) {
            // If the type is a pointer type we need a host and a device pointer
            if(::Utils::isTypePointer(type)) {
                os << type << " d_" << name << ";" << std::endl;
            }
            // Otherwise we just need a device variable, made volatile for safety
            else {
                os << "__device__ volatile " << type << " d_" << name << ";" << std::endl;
            }
        }
    }
}
//--------------------------------------------------------------------------
MemAlloc Backend::genVariableAllocation(CodeStream &os, const std::string &type, const std::string &name, VarLocation loc, size_t count) const
{
    auto allocation = MemAlloc::zero();

    if(getPreferences().automaticCopy) {
        os << "CHECK_CUDA_ERRORS(cudaMallocManaged(&" << name << ", " << count << " * sizeof(" << type << ")));" << std::endl;
        allocation += MemAlloc::device(count * getSize(type));
    }
    else {
        if(loc & VarLocation::HOST) {
            const char *flags = (loc & VarLocation::ZERO_COPY) ? "cudaHostAllocMapped" : "cudaHostAllocPortable";
            os << "CHECK_CUDA_ERRORS(cudaHostAlloc(&" << name << ", " << count << " * sizeof(" << type << "), " << flags << "));" << std::endl;
            allocation += MemAlloc::host(count * getSize(type));
        }

        // If variable is present on device at all
        if(loc & VarLocation::DEVICE) {
            // Insert call to correct helper depending on whether variable should be allocated in zero-copy mode or not
            if(loc & VarLocation::ZERO_COPY) {
                os << "CHECK_CUDA_ERRORS(cudaHostGetDevicePointer((void **)&d_" << name << ", (void *)" << name << ", 0));" << std::endl;
                allocation += MemAlloc::zeroCopy(count * getSize(type));
            }
            else {
                os << "CHECK_CUDA_ERRORS(cudaMalloc(&d_" << name << ", " << count << " * sizeof(" << type << ")));" << std::endl;
                allocation += MemAlloc::device(count * getSize(type));
            }
        }
    }

    return allocation;
}
//--------------------------------------------------------------------------
void Backend::genVariableFree(CodeStream &os, const std::string &name, VarLocation loc) const
{
    if(getPreferences().automaticCopy) {
        os << "CHECK_CUDA_ERRORS(cudaFree(" << name << "));" << std::endl;
    }
    else {
        // **NOTE** because we pinned the variable we need to free it with cudaFreeHost rather than use the host code generator
        if(loc & VarLocation::HOST) {
            os << "CHECK_CUDA_ERRORS(cudaFreeHost(" << name << "));" << std::endl;
        }

        // If this variable wasn't allocated in zero-copy mode, free it
        if(loc & VarLocation::DEVICE) {
            os << "CHECK_CUDA_ERRORS(cudaFree(d_" << name << "));" << std::endl;
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamDefinition(CodeStream &definitions, CodeStream &, 
                                            const std::string &type, const std::string &name, VarLocation loc) const
{
    if(getPreferences().automaticCopy) {
        definitions << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
    }
    else {
        if(loc & VarLocation::HOST) {
            definitions << "EXPORT_VAR " << type << " " << name << ";" << std::endl;
        }
        if(loc & VarLocation::DEVICE && ::Utils::isTypePointer(type)) {
            definitions << "EXPORT_VAR " << type << " d_" << name << ";" << std::endl;
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamImplementation(CodeStream &os, const std::string &type, const std::string &name, VarLocation loc) const
{
    if(getPreferences().automaticCopy) {
        os << type << " " << name << ";" << std::endl;
    }
    else {
        if(loc & VarLocation::HOST) {
            os << type << " " << name << ";" << std::endl;
        }
        if(loc & VarLocation::DEVICE && ::Utils::isTypePointer(type)) {
            os << type << " d_" << name << ";" << std::endl;
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamAllocation(CodeStream &os, const std::string &type, const std::string &name, 
                                            VarLocation loc, const std::string &countVarName, const std::string &prefix) const
{
    // Get underlying type
    const std::string underlyingType = ::Utils::getUnderlyingType(type);
    const bool pointerToPointer = ::Utils::isTypePointerToPointer(type);

    const std::string hostPointer = pointerToPointer ? ("*" + prefix + name) : (prefix + name);
    const std::string hostPointerToPointer = pointerToPointer ? (prefix + name) : ("&" + prefix + name);
    const std::string devicePointerToPointer = pointerToPointer ? (prefix + "d_" + name) : ("&" + prefix + "d_" + name);
    if(getPreferences().automaticCopy) {
        os << "CHECK_CUDA_ERRORS(cudaMallocManaged(" << hostPointerToPointer << ", " << countVarName << " * sizeof(" << underlyingType << ")));" << std::endl;
    }
    else {
        if(loc & VarLocation::HOST) {
            const char *flags = (loc & VarLocation::ZERO_COPY) ? "cudaHostAllocMapped" : "cudaHostAllocPortable";
            os << "CHECK_CUDA_ERRORS(cudaHostAlloc(" << hostPointerToPointer << ", " << countVarName << " * sizeof(" << underlyingType << "), " << flags << "));" << std::endl;
        }

        // If variable is present on device at all
        if(loc & VarLocation::DEVICE) {
            if(loc & VarLocation::ZERO_COPY) {
                os << "CHECK_CUDA_ERRORS(cudaHostGetDevicePointer((void**)" << devicePointerToPointer << ", (void*)" << hostPointer << ", 0));" << std::endl;
            }
            else {
                os << "CHECK_CUDA_ERRORS(cudaMalloc(" << devicePointerToPointer << ", " << countVarName << " * sizeof(" << underlyingType << ")));" << std::endl;
            }
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamPush(CodeStream &os, const std::string &type, const std::string &name, 
                                      VarLocation loc, const std::string &countVarName, const std::string &prefix) const
{
    assert(!getPreferences().automaticCopy);

    if(!(loc & VarLocation::ZERO_COPY)) {
        // Get underlying type
        const std::string underlyingType = ::Utils::getUnderlyingType(type);
        const bool pointerToPointer = ::Utils::isTypePointerToPointer(type);

        const std::string hostPointer = pointerToPointer ? ("*" + prefix + name) : (prefix + name);
        const std::string devicePointer = pointerToPointer ? ("*" + prefix + "d_" + name) : (prefix + "d_" + name);

        os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << devicePointer;
        os << ", " << hostPointer;
        os << ", " << countVarName << " * sizeof(" << underlyingType << "), cudaMemcpyHostToDevice));" << std::endl;
    }
}
//--------------------------------------------------------------------------
void Backend::genExtraGlobalParamPull(CodeStream &os, const std::string &type, const std::string &name, 
                                      VarLocation loc, const std::string &countVarName, const std::string &prefix) const
{
    assert(!getPreferences().automaticCopy);

    if(!(loc & VarLocation::ZERO_COPY)) {
        // Get underlying type
        const std::string underlyingType = ::Utils::getUnderlyingType(type);
        const bool pointerToPointer = ::Utils::isTypePointerToPointer(type);

        const std::string hostPointer = pointerToPointer ? ("*" + prefix + name) : (prefix + name);
        const std::string devicePointer = pointerToPointer ? ("*" + prefix + "d_" + name) : (prefix + "d_" + name);

        os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << hostPointer;
        os << ", " << devicePointer;
        os << ", " << countVarName << " * sizeof(" << underlyingType << "), cudaMemcpyDeviceToHost));" << std::endl;
    }
}
//--------------------------------------------------------------------------
void Backend::genMergedExtraGlobalParamPush(CodeStream &os, const std::string &suffix, size_t mergedGroupIdx,
                                            const std::string &groupIdx, const std::string &fieldName,
                                            const std::string &egpName) const
{
    const std::string structName = "Merged" + suffix + "Group" + std::to_string(mergedGroupIdx);
    os << "CHECK_CUDA_ERRORS(cudaMemcpyToSymbolAsync(d_merged" << suffix << "Group" << mergedGroupIdx;
    os << ", &" << egpName << ", sizeof(" << egpName << ")";
    os << ", (sizeof(" << structName << ") * (" << groupIdx << ")) + offsetof(" << structName << ", " << fieldName << ")));" << std::endl;
}
//--------------------------------------------------------------------------
std::string Backend::getMergedGroupFieldHostType(const std::string &type) const
{
    return type;
}
//--------------------------------------------------------------------------
void Backend::genVariablePush(CodeStream &os, const std::string &type, const std::string &name, VarLocation loc, bool autoInitialized, size_t count) const
{
    assert(!getPreferences().automaticCopy);

    if(!(loc & VarLocation::ZERO_COPY)) {
        // Only copy if uninitialisedOnly isn't set
        if(autoInitialized) {
            os << "if(!uninitialisedOnly)" << CodeStream::OB(1101);
        }

        os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << name;
        os << ", " << name;
        os << ", " << count << " * sizeof(" << type << "), cudaMemcpyHostToDevice));" << std::endl;

        if(autoInitialized) {
            os << CodeStream::CB(1101);
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genVariablePull(CodeStream &os, const std::string &type, const std::string &name, VarLocation loc, size_t count) const
{
    assert(!getPreferences().automaticCopy);

    if(!(loc & VarLocation::ZERO_COPY)) {
        os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << name;
        os << ", d_"  << name;
        os << ", " << count << " * sizeof(" << type << "), cudaMemcpyDeviceToHost));" << std::endl;
    }
}
//--------------------------------------------------------------------------
void Backend::genCurrentVariablePush(CodeStream &os, const NeuronGroupInternal &ng, const std::string &type, const std::string &name, VarLocation loc) const
{
    assert(!getPreferences().automaticCopy);

    // If this variable requires queuing and isn't zero-copy
    if(ng.isVarQueueRequired(name) && ng.isDelayRequired() && !(loc & VarLocation::ZERO_COPY)) {
        // Generate memcpy to copy only current timestep's data
        os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << name << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
        os << ", " << name << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
        os << ", " << ng.getNumNeurons() << " * sizeof(" << type << "), cudaMemcpyHostToDevice));" << std::endl;
    }
    // Otherwise, generate standard s
    else {
        genVariablePush(os, type, name + ng.getName(), loc, false, ng.getNumNeurons());
    }
}
//--------------------------------------------------------------------------
void Backend::genCurrentVariablePull(CodeStream &os, const NeuronGroupInternal &ng, const std::string &type, const std::string &name, VarLocation loc) const
{
    assert(!getPreferences().automaticCopy);

    // If this variable requires queuing and isn't zero-copy
    if(ng.isVarQueueRequired(name) && ng.isDelayRequired() && !(loc & VarLocation::ZERO_COPY)) {
        // Generate memcpy to copy only current timestep's data
        os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << name << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
        os << ", d_" << name << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
        os << ", " << ng.getNumNeurons() << " * sizeof(" << type << "), cudaMemcpyDeviceToHost));" << std::endl;
    }
    // Otherwise, generate standard pull
    else {
        genVariablePull(os, type, name + ng.getName(), loc, ng.getNumNeurons());
    }
}
//--------------------------------------------------------------------------
MemAlloc Backend::genGlobalDeviceRNG(CodeStream &, CodeStream &definitionsInternal, CodeStream &runner, CodeStream &, CodeStream &) const
{
    // Define global Phillox RNG
    // **NOTE** this is actually accessed as a global so, unlike other variables, needs device global
    definitionsInternal << "EXPORT_VAR __device__ curandStatePhilox4_32_10_t d_rng;" << std::endl;

    // Implement global Phillox RNG
    runner << "__device__ curandStatePhilox4_32_10_t d_rng;" << std::endl;

    return MemAlloc::device(getSize("curandStatePhilox4_32_10_t"));
}
//--------------------------------------------------------------------------
MemAlloc Backend::genPopulationRNG(CodeStream &definitions, CodeStream &definitionsInternal, CodeStream &runner, CodeStream &allocations, CodeStream &free,
                                   const std::string &name, size_t count) const
{
    // Create an array or XORWOW RNGs
    return genArray(definitions, definitionsInternal, runner, allocations, free, "curandState", name, VarLocation::DEVICE, count);
}
//--------------------------------------------------------------------------
void Backend::genTimer(CodeStream &, CodeStream &definitionsInternal, CodeStream &runner, CodeStream &allocations, CodeStream &free,
                       CodeStream &stepTimeFinalise, const std::string &name, bool updateInStepTime) const
{
    // Define CUDA start and stop events in internal defintions (as they use CUDA-specific types)
    definitionsInternal << "EXPORT_VAR cudaEvent_t " << name << "Start;" << std::endl;
    definitionsInternal << "EXPORT_VAR cudaEvent_t " << name << "Stop;" << std::endl;

    // Implement start and stop event variables
    runner << "cudaEvent_t " << name << "Start;" << std::endl;
    runner << "cudaEvent_t " << name << "Stop;" << std::endl;

    // Create start and stop events in allocations
    allocations << "CHECK_CUDA_ERRORS(cudaEventCreate(&" << name << "Start));" << std::endl;
    allocations << "CHECK_CUDA_ERRORS(cudaEventCreate(&" << name << "Stop));" << std::endl;

    // Destroy start and stop events in allocations
    free << "CHECK_CUDA_ERRORS(cudaEventDestroy(" << name << "Start));" << std::endl;
    free << "CHECK_CUDA_ERRORS(cudaEventDestroy(" << name << "Stop));" << std::endl;

    if(updateInStepTime) {
        CodeGenerator::CodeStream::Scope b(stepTimeFinalise);
        stepTimeFinalise << "float tmp;" << std::endl;
        stepTimeFinalise << "CHECK_CUDA_ERRORS(cudaEventElapsedTime(&tmp, " << name << "Start, " << name << "Stop));" << std::endl;
        stepTimeFinalise << name << "Time += tmp / 1000.0;" << std::endl;
    }
}
//--------------------------------------------------------------------------
void Backend::genReturnFreeDeviceMemoryBytes(CodeStream &os) const
{
    os << "size_t free;" << std::endl;
    os << "size_t total;" << std::endl;
    os << "CHECK_CUDA_ERRORS(cudaMemGetInfo(&free, &total));" << std::endl;
    os << "return free;" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMakefilePreamble(std::ostream &os) const
{
    const std::string architecture = "sm_" + std::to_string(getChosenCUDADevice().major) + std::to_string(getChosenCUDADevice().minor);
    std::string linkFlags = "--shared -arch " + architecture;

    // Write variables to preamble
    os << "CUDA_PATH ?=/usr/local/cuda" << std::endl;
    os << "NVCC := $(CUDA_PATH)/bin/nvcc" << std::endl;
    os << "NVCCFLAGS := " << getNVCCFlags() << std::endl;
    os << "LINKFLAGS := " << linkFlags << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMakefileLinkRule(std::ostream &os) const
{
    os << "\t@$(NVCC) $(LINKFLAGS) -o $@ $(OBJECTS)" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMakefileCompileRule(std::ostream &os) const
{
    // Add one rule to generate dependency files from cc files
    os << "%.d: %.cc" << std::endl;
    os << "\t@$(NVCC) -M $(NVCCFLAGS) $< 1> $@" << std::endl;
    os << std::endl;

    // Add another to build object files from cc files
    os << "%.o: %.cc %.d" << std::endl;
    os << "\t@$(NVCC) -dc $(NVCCFLAGS) $<" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMSBuildConfigProperties(std::ostream &os) const
{
    // Add property to extract CUDA path
    os << "\t\t<!-- **HACK** determine the installed CUDA version by regexing CUDA path -->" << std::endl;
    os << "\t\t<CudaVersion>$([System.Text.RegularExpressions.Regex]::Match($(CUDA_PATH), \"\\\\v([0-9.]+)$\").Groups[1].Value)</CudaVersion>" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMSBuildImportProps(std::ostream &os) const
{
    // Import CUDA props file
    os << "\t<ImportGroup Label=\"ExtensionSettings\">" << std::endl;
    os << "\t\t<Import Project=\"$(VCTargetsPath)\\BuildCustomizations\\CUDA $(CudaVersion).props\" />" << std::endl;
    os << "\t</ImportGroup>" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMSBuildItemDefinitions(std::ostream &os) const
{
    // Add item definition for host compilation
    os << "\t\t<ClCompile>" << std::endl;
    os << "\t\t\t<WarningLevel>Level3</WarningLevel>" << std::endl;
    os << "\t\t\t<Optimization Condition=\"'$(Configuration)'=='Release'\">MaxSpeed</Optimization>" << std::endl;
    os << "\t\t\t<Optimization Condition=\"'$(Configuration)'=='Debug'\">Disabled</Optimization>" << std::endl;
    os << "\t\t\t<FunctionLevelLinking Condition=\"'$(Configuration)'=='Release'\">true</FunctionLevelLinking>" << std::endl;
    os << "\t\t\t<IntrinsicFunctions Condition=\"'$(Configuration)'=='Release'\">true</IntrinsicFunctions>" << std::endl;
    os << "\t\t\t<PreprocessorDefinitions Condition=\"'$(Configuration)'=='Release'\">WIN32;WIN64;NDEBUG;_CONSOLE;BUILDING_GENERATED_CODE;%(PreprocessorDefinitions)</PreprocessorDefinitions>" << std::endl;
    os << "\t\t\t<PreprocessorDefinitions Condition=\"'$(Configuration)'=='Debug'\">WIN32;WIN64;_DEBUG;_CONSOLE;BUILDING_GENERATED_CODE;%(PreprocessorDefinitions)</PreprocessorDefinitions>" << std::endl;
    os << "\t\t</ClCompile>" << std::endl;

    // Add item definition for linking
    os << "\t\t<Link>" << std::endl;
    os << "\t\t\t<GenerateDebugInformation>true</GenerateDebugInformation>" << std::endl;
    os << "\t\t\t<EnableCOMDATFolding Condition=\"'$(Configuration)'=='Release'\">true</EnableCOMDATFolding>" << std::endl;
    os << "\t\t\t<OptimizeReferences Condition=\"'$(Configuration)'=='Release'\">true</OptimizeReferences>" << std::endl;
    os << "\t\t\t<SubSystem>Console</SubSystem>" << std::endl;
    os << "\t\t\t<AdditionalDependencies>cudart_static.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>" << std::endl;
    os << "\t\t</Link>" << std::endl;

    // Add item definition for CUDA compilation
    // **YUCK** the CUDA Visual Studio plugin build system demands that you specify both a virtual an actual architecture 
    // (which NVCC itself doesn't require). While, in general, actual architectures are usable as virtual architectures, 
    // there is no compute_21 so we need to replace that with compute_20
    const std::string architecture = std::to_string(getChosenCUDADevice().major) + std::to_string(getChosenCUDADevice().minor);
    const std::string virtualArchitecture = (architecture == "21") ? "20" : architecture;
    os << "\t\t<CudaCompile>" << std::endl;
    os << "\t\t\t<TargetMachinePlatform>64</TargetMachinePlatform>" << std::endl;
    os << "\t\t\t<GenerateRelocatableDeviceCode>true</GenerateRelocatableDeviceCode>" << std::endl;
    os << "\t\t\t<CodeGeneration>compute_" << virtualArchitecture <<",sm_" << architecture << "</CodeGeneration>" << std::endl;
    os << "\t\t\t<FastMath>" << (getPreferences().optimizeCode ? "true" : "false") << "</FastMath>" << std::endl;
    os << "\t\t\t<GenerateLineInfo>" << (getPreferences<Preferences>().generateLineInfo ? "true" : "false") << "</GenerateLineInfo>" << std::endl;
    os << "\t\t</CudaCompile>" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMSBuildCompileModule(const std::string &moduleName, std::ostream &os) const
{
    os << "\t\t<CudaCompile Include=\"" << moduleName << ".cc\" >" << std::endl;
    // **YUCK** for some reasons you can't call .Contains on %(BaseCommandLineTemplate) directly
    // Solution suggested by https://stackoverflow.com/questions/9512577/using-item-functions-on-metadata-values
    os << "\t\t\t<AdditionalOptions Condition=\" !$([System.String]::new('%(BaseCommandLineTemplate)').Contains('-x cu')) \">-x cu %(AdditionalOptions)</AdditionalOptions>" << std::endl;
    os << "\t\t</CudaCompile>" << std::endl;
}
//--------------------------------------------------------------------------
void Backend::genMSBuildImportTarget(std::ostream &os) const
{
    os << "\t<ImportGroup Label=\"ExtensionTargets\">" << std::endl;
    os << "\t\t<Import Project=\"$(VCTargetsPath)\\BuildCustomizations\\CUDA $(CudaVersion).targets\" />" << std::endl;
    os << "\t</ImportGroup>" << std::endl;
}

//--------------------------------------------------------------------------
Backend::MemorySpaces Backend::getMergedGroupMemorySpaces(const ModelSpecMerged &modelMerged) const
{
    // Get size of update group start ids (constant cache is precious so don't use for init groups
    const size_t groupStartIDSize = (getGroupStartIDSize(modelMerged.getMergedNeuronUpdateGroups()) +
                                     getGroupStartIDSize(modelMerged.getMergedPresynapticUpdateGroups()) +
                                     getGroupStartIDSize(modelMerged.getMergedPostsynapticUpdateGroups()) +
                                     getGroupStartIDSize(modelMerged.getMergedSynapseDynamicsGroups()));

    // Return available constant memory and to
    return {{"__device__ __constant__", (groupStartIDSize > getChosenDeviceSafeConstMemBytes()) ? 0 : (getChosenDeviceSafeConstMemBytes() - groupStartIDSize)},
            {"__device__", m_ChosenDevice.totalGlobalMem}};
}
//--------------------------------------------------------------------------
std::string Backend::getNVCCFlags() const
{
    // **NOTE** now we don't include runner.cc when building standalone modules we get loads of warnings about
    // How you hide device compiler warnings is totally non-documented but https://stackoverflow.com/a/17095910/1476754
    // holds the answer! For future reference --display_error_number option can be used to get warning ids to use in --diag-supress
    // HOWEVER, on CUDA 7.5 and 8.0 this causes a fatal error and, as no warnings are shown when --diag-suppress is removed,
    // presumably this is because this warning simply wasn't implemented until CUDA 9
    const std::string architecture = "sm_" + std::to_string(getChosenCUDADevice().major) + std::to_string(getChosenCUDADevice().minor);
    std::string nvccFlags = "-x cu -arch " + architecture;
#ifndef _WIN32
    nvccFlags += " -std=c++11 --compiler-options \"-fPIC -Wno-return-type-c-linkage\"";
#endif
    if(m_RuntimeVersion >= 9000) {
        nvccFlags += " -Xcudafe \"--diag_suppress=extern_entity_treated_as_static\"";
    }

    nvccFlags += " " + getPreferences<Preferences>().userNvccFlags;
    if(getPreferences().optimizeCode) {
        nvccFlags += " -O3 -use_fast_math";
    }
    if(getPreferences().debugCode) {
        nvccFlags += " -O0 -g -G";
    }
    if(getPreferences<Preferences>().showPtxInfo) {
        nvccFlags += " -Xptxas \"-v\"";
    }
    if(getPreferences<Preferences>().generateLineInfo) {
        nvccFlags += " --generate-line-info";
    }
#ifdef MPI_ENABLE
    // If MPI is enabled, add MPI include path
    nvccFlags +=" -I\"$(MPI_PATH)/include\"";
#endif
    return nvccFlags;
}
//--------------------------------------------------------------------------
void Backend::genCurrentSpikePush(CodeStream &os, const NeuronGroupInternal &ng, bool spikeEvent) const
{
    assert(!getPreferences().automaticCopy);

    if(!(ng.getSpikeLocation() & VarLocation::ZERO_COPY)) {
        // Is delay required
        const bool delayRequired = spikeEvent ?
            ng.isDelayRequired() :
            (ng.isTrueSpikeRequired() && ng.isDelayRequired());

        const char *spikeCntPrefix = spikeEvent ? "glbSpkCntEvnt" : "glbSpkCnt";
        const char *spikePrefix = spikeEvent ? "glbSpkEvnt" : "glbSpk";

        if (delayRequired) {
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << spikeCntPrefix << ng.getName() << " + spkQuePtr" << ng.getName();
            os << ", " << spikeCntPrefix << ng.getName() << " + spkQuePtr" << ng.getName();
            os << ", sizeof(unsigned int), cudaMemcpyHostToDevice));" << std::endl;
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << spikePrefix << ng.getName() << " + (spkQuePtr" << ng.getName() << "*" << ng.getNumNeurons() << ")";
            os << ", " << spikePrefix << ng.getName();
            os << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
            os << ", " << spikeCntPrefix << ng.getName() << "[spkQuePtr" << ng.getName() << "] * sizeof(unsigned int), cudaMemcpyHostToDevice));" << std::endl;
        }
        else {
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << spikeCntPrefix << ng.getName();
            os << ", " << spikeCntPrefix << ng.getName();
            os << ", sizeof(unsigned int), cudaMemcpyHostToDevice));" << std::endl;
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(d_" << spikePrefix << ng.getName();
            os << ", " << spikePrefix << ng.getName();
            os << ", " << spikeCntPrefix << ng.getName() << "[0] * sizeof(unsigned int), cudaMemcpyHostToDevice));" << std::endl;
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genCurrentSpikePull(CodeStream &os, const NeuronGroupInternal &ng, bool spikeEvent) const
{
    if(!(ng.getSpikeLocation() & VarLocation::ZERO_COPY)) {
        // Is delay required
        const bool delayRequired = spikeEvent ?
            ng.isDelayRequired() :
            (ng.isTrueSpikeRequired() && ng.isDelayRequired());

        const char *spikeCntPrefix = spikeEvent ? "glbSpkCntEvnt" : "glbSpkCnt";
        const char *spikePrefix = spikeEvent ? "glbSpkEvnt" : "glbSpk";

        if (delayRequired) {
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << spikeCntPrefix << ng.getName() << " + spkQuePtr" << ng.getName();
            os << ", d_" << spikeCntPrefix << ng.getName() << " + spkQuePtr" << ng.getName();
            os << ", sizeof(unsigned int), cudaMemcpyDeviceToHost));" << std::endl;

            os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << spikePrefix << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
            os << ", d_" << spikePrefix << ng.getName() << " + (spkQuePtr" << ng.getName() << " * " << ng.getNumNeurons() << ")";
            os << ", " << spikeCntPrefix << ng.getName() << "[spkQuePtr" << ng.getName() << "] * sizeof(unsigned int), cudaMemcpyDeviceToHost));" << std::endl;
        }
        else {
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << spikeCntPrefix << ng.getName();
            os << ", d_" << spikeCntPrefix << ng.getName();
            os << ", sizeof(unsigned int), cudaMemcpyDeviceToHost));" << std::endl;
            os << "CHECK_CUDA_ERRORS(cudaMemcpy(" << spikePrefix << ng.getName();
            os << ", d_" << spikePrefix << ng.getName();
            os << ", " << spikeCntPrefix << ng.getName() << "[0] * sizeof(unsigned int), cudaMemcpyDeviceToHost));" << std::endl;
        }
    }
}
//--------------------------------------------------------------------------
void Backend::genKernelDimensions(CodeStream &os, Kernel kernel, size_t numThreads) const
{
    // Calculate grid size
    const size_t gridSize = ceilDivide(numThreads, getKernelBlockSize(kernel));
    os << "const dim3 threads(" << getKernelBlockSize(kernel) << ", 1);" << std::endl;

    if (gridSize < (size_t)getChosenCUDADevice().maxGridSize[0]) {
        os << "const dim3 grid(" << gridSize << ", 1);" << std::endl;
    }
    else {
        // **TODO** this needs to be implemented in genParallelGroup
        assert(false);
        const size_t squareGridSize = (size_t)std::ceil(std::sqrt(gridSize));
        os << "const dim3 grid(" << squareGridSize << ", "<< squareGridSize <<");" << std::endl;
    }
}
}   // namespace CUDA
}   // namespace CodeGenerator
