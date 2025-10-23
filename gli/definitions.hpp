/// @brief Include for macro definitions
/// @file gli/definitions.hpp

#pragma once

#if GLM_COMPILER & GLM_COMPILER_VC
#	define GLI_FORCE_INLINE __forceinline
#elif GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_APPLE_CLANG | GLM_COMPILER_LLVM)
#	define GLI_FORCE_INLINE inline __attribute__((__always_inline__))
#else
#	define GLI_FORCE_INLINE inline
#endif//GLM_COMPILER

#define GLI_DISABLE_ASSERT 0

#if defined(NDEBUG) || GLI_DISABLE_ASSERT
#	define GLI_ASSERT(test)
#else
#	define GLI_ASSERT(test) assert((test))
#endif

#define GLM_STATIC_ASSERT(x, message) assert(x)
