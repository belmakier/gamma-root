#ifndef GAMROOT_UTILS_RTTI_HH
#define GAMROOT_UTILS_RTTI_HH

/* GNU */
#include <cxxabi.h>
#define DEMANGLE_TYPEID_NAME(x) abi::__cxa_demangle(typeid((x)).name(), NULL, NULL, NULL)

#endif
