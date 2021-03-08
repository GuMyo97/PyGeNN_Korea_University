#pragma once

// Standard C++ includes
#include <iostream>

// GeNN includes
#include "logging.h"

#if CUDA_VERSION >= 6050
#define CHECK_CU_ERRORS(call)                                                                       \
{                                                                                                   \
    CUresult error = call;                                                                          \
    if (error != CUDA_SUCCESS) {                                                                    \
        const char *errStr = nullptr;                                                                         \
        cuGetErrorName(error, &errStr);                                                             \
        LOGE_BACKEND << __FILE__ << ": " <<  __LINE__ << ": cuda driver error " << error << ": " << errStr; \
        exit(EXIT_FAILURE);                                                                         \
    }                                                                                               \
}
#else
#define CHECK_CU_ERRORS(call) call
#endif
