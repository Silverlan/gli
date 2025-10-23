/// @brief Include to save KMG textures to files or memory.
/// @file gli/save_kmg.hpp

module;

#include "definitions.hpp"
#include <string>

export module gli:save_kmg;

import :core.filter;
export import :load_kmg;
export import :texture;

export namespace gli
{
	/// Save a texture storage_linear to a KMG (Khronos Image) file.
	///
	/// @param Texture Source texture to save
	/// @param Path Path for where to save the file. It must include the filaname and filename extension.
	/// This function ignores the filename extension in the path and save to KMG anyway but keep the requested filename extension.
	/// @return Returns false if the function fails to save the file.
	bool save_kmg(texture const & Texture, char const * Path);

	/// Save a texture storage_linear to a KMG (Khronos Image) file.
	///
	/// @param Texture Source texture to save
	/// @param Path Path for where to save the file. It must include the filaname and filename extension.
	/// This function ignores the filename extension in the path and save to KMG anyway but keep the requested filename extension.
	/// @return Returns false if the function fails to save the file.
	bool save_kmg(texture const & Texture, std::string const & Path);

	/// Save a texture storage_linear to a KMG (Khronos Image) file.
	///
	/// @param Texture Source texture to save
	/// @param Memory Storage for the KMG container. The function resizes the containers to fit the necessary storage_linear.
	/// @return Returns false if the function fails to save the file.
	bool save_kmg(texture const & Texture, std::vector<char> & Memory);
}//namespace gli

export namespace gli
{
	inline bool save_kmg(texture const & Texture, std::vector<char> & Memory)
	{
		if(Texture.empty())
			return false;

		Memory.resize(sizeof(detail::FOURCC_KMG100) + sizeof(detail::kmgHeader10) + Texture.size());

		std::memcpy(&Memory[0], detail::FOURCC_KMG100, sizeof(detail::FOURCC_KMG100));

		std::size_t Offset = sizeof(detail::FOURCC_KMG100);

		texture::swizzles_type Swizzle = Texture.swizzles();

		detail::kmgHeader10 & Header = *reinterpret_cast<detail::kmgHeader10*>(&Memory[0] + Offset);
		Header.Endianness = 0x04030201;
		Header.Format = Texture.format();
		Header.Target = Texture.target();
		Header.SwizzleRed = Swizzle[0];
		Header.SwizzleGreen = Swizzle[1];
		Header.SwizzleBlue = Swizzle[2];
		Header.SwizzleAlpha = Swizzle[3];
		Header.PixelWidth = static_cast<std::uint32_t>(Texture.extent().x);
		Header.PixelHeight = static_cast<std::uint32_t>(Texture.extent().y);
		Header.PixelDepth = static_cast<std::uint32_t>(Texture.extent().z);
		Header.Layers = static_cast<std::uint32_t>(Texture.layers());
		Header.Levels = static_cast<std::uint32_t>(Texture.levels());
		Header.Faces = static_cast<std::uint32_t>(Texture.faces());
		Header.GenerateMipmaps = FILTER_NONE;
		Header.BaseLevel = static_cast<std::uint32_t>(Texture.base_level());
		Header.MaxLevel = static_cast<std::uint32_t>(Texture.max_level());

		Offset += sizeof(detail::kmgHeader10);

		for(texture::size_type Layer = 0, Layers = Texture.layers(); Layer < Layers; ++Layer)
		for(texture::size_type Level = 0, Levels = Texture.levels(); Level < Levels; ++Level)
		{
			texture::size_type const FaceSize = Texture.size(Level);
			for(texture::size_type Face = 0, Faces = Texture.faces(); Face < Faces; ++Face)
			{
				std::memcpy(&Memory[0] + Offset, Texture.data(Layer, Face, Level), FaceSize);

				Offset += FaceSize;
				GLI_ASSERT(Offset <= Memory.size());
			}
		}

		return true;
	}

	inline bool save_kmg(texture const & Texture, char const * Filename)
	{
		if(Texture.empty())
			return false;

		FILE* File = detail::open_file(Filename, "wb");
		if(!File)
			return false;

		std::vector<char> Memory;
		bool const Result = save_kmg(Texture, Memory);

		std::fwrite(&Memory[0], 1, Memory.size(), File);
		std::fclose(File);

		return Result;
	}

	inline bool save_kmg(texture const & Texture, std::string const & Filename)
	{
		return save_kmg(Texture, Filename.c_str());
	}
}//namespace gli
