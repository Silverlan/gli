/// @brief Include to load DDS, KTX or KMG textures from files or memory.
/// @file gli/load.hpp

module;

#include <cstdio>

export module gli:load;

import :load_dds;
import :load_kmg;
import :load_ktx;
export import :texture;

export namespace gli
{
	/// Loads a texture storage_linear from file. Returns an empty storage_linear in case of failure.
	///
	/// @param Path Path of the file to open including filaname and filename extension
	texture load(char const* Path);

	/// Loads a texture storage_linear from file. Returns an empty storage_linear in case of failure.
	///
	/// @param Path Path of the file to open including filaname and filename extension
	texture load(std::string const& Path);

	/// Loads a texture storage_linear from memory. Returns an empty storage_linear in case of failure.
	///
	/// @param Data Data of a texture
	/// @param Size Size of the data
	texture load(char const* Data, std::size_t Size);
}//namespace gli

export namespace gli
{
	/// Load a texture (DDS, KTX or KMG) from memory
	inline texture load(char const * Data, std::size_t Size)
	{
		{
			texture Texture = load_dds(Data, Size);
			if(!Texture.empty())
				return Texture;
		}
		{
			texture Texture = load_kmg(Data, Size);
			if(!Texture.empty())
				return Texture;
		}
		{
			texture Texture = load_ktx(Data, Size);
			if(!Texture.empty())
				return Texture;
		}

		return texture();
	}

	/// Load a texture (DDS, KTX or KMG) from file
	inline texture load(char const * Filename)
	{
		FILE* File = detail::open_file(Filename, "rb");
		if(!File)
			return texture();

		long Beg = std::ftell(File);
		std::fseek(File, 0, SEEK_END);
		long End = std::ftell(File);
		std::fseek(File, 0, SEEK_SET);

		std::vector<char> Data(static_cast<std::size_t>(End - Beg));

		std::fread(&Data[0], 1, Data.size(), File);
		std::fclose(File);

		return load(&Data[0], Data.size());
	}

	/// Load a texture (DDS, KTX or KMG) from file
	inline texture load(std::string const & Filename)
	{
		return load(Filename.c_str());
	}
}//namespace gli
