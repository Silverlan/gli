/// @brief Include to save DDS, KTX or KMG textures to files or memory.
/// @file gli/save.hpp

module;


export module gli:save;

import :save_dds;
import :save_kmg;
import :save_ktx;
export import :texture;

export namespace gli
{
	/// Save a texture storage_linear to file.
	///
	/// @param Texture Source texture to save
	/// @param Path Path for where to save the file. It must include the filaname and filename extension.
	/// The function use the filename extension included in the path to figure out the file container to use.
	/// @return Returns false if the function fails to save the file.
	bool save(texture const & Texture, char const * Path);

	/// Save a texture storage_linear to file.
	///
	/// @param Texture Source texture to save
	/// @param Path Path for where to save the file. It must include the filaname and filename extension.
	/// The function use the filename extension included in the path to figure out the file container to use.
	/// @return Returns false if the function fails to save the file.
	bool save(texture const & Texture, std::string const & Path);
}//namespace gli

export namespace gli
{
	inline bool save(texture const & Texture, char const * Path)
	{
		return save(Texture, std::string(Path));
	}

	inline bool save(texture const & Texture, std::string const & Path)
	{
		if(Path.rfind(".dds") != std::string::npos)
			return save_dds(Texture, Path);
		if(Path.rfind(".kmg") != std::string::npos)
			return save_kmg(Texture, Path);
		if(Path.rfind(".ktx") != std::string::npos)
			return save_ktx(Texture, Path);
		return false;
	}
}//namespace gli
