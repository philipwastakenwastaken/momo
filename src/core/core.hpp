#pragma once
#include <cstdlib>

// Controls parameters related to building in different modes

#ifdef MOMO_DEBUG
    #define MOMO_ENABLE_ASSERT
    #define MOMO_ENABLE_LOGGING
#elif MOMO_RELEASE
    #define MOMO_ENABLE_ASSERT
    #define MOMO_ENABLE_LOGGING
#endif

#define MOMO_STATIC_ASSERT(x, ...) {static_assert(x, __VA_ARGS__);}

#ifdef MOMO_ENABLE_ASSERT
    #define MOMO_ASSERT(x, ...) {if (!(x)) {MOMO_ERROR("Assertion failed: {0}", __VA_ARGS__); std::abort();}}
#else
    #define MOMO_ASSERT(x, ...)
#endif