#pragma once

#define UNUSED_PARAM(Parameter) (void)(Parameter)

#if defined(CEPP_WINDOWS)
    #if defined(CEPP_IMPORT)
        #define CEPP_DLL __declspec(dllimport)
    #else
        #define CEPP_DLL __declspec(dllexport)
    #endif
#else
    #define CEPP_DLL
#endif
