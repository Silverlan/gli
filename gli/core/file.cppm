/// @brief File helper functions
/// @file gli/core/file.hpp

module;

#include <cstdio>

export module gli:core.file;

export namespace gli{
namespace detail
{
	FILE* open_file(const char *Filename, const char *mode);
}//namespace detail
}//namespace gli

export namespace gli{
namespace detail
{
	inline FILE* open_file(const char *Filename, const char *Mode)
	{
#		if GLM_COMPILER & GLM_COMPILER_VC
			FILE *File = nullptr;
			fopen_s(&File, Filename, Mode);
			return File;
#		else
			return std::fopen(Filename, Mode);
#		endif
	}
}//namespace detail
}//namespace gli
