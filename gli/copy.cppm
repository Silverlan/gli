/// @brief Include to copy textures or a subset of either textures. These operations are performed without memory allocations.
/// @file gli/copy.hpp

module;

#include <cstddef>

export module gli:copy;

export namespace gli
{
	/// Copy a specific image of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy(
		texture_src_type const& TextureSrc, size_t LayerSrc, size_t FaceSrc, size_t LevelSrc,
		texture_dst_type& TextureDst, size_t LayerDst, size_t FaceDst, size_t LevelDst);

	/// Copy a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy(
		texture_src_type const& TextureSrc,
		texture_dst_type& TextureDst);

	// Copy an entire level of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_level(
		texture_src_type const& TextureSrc, size_t BaseLevelSrc,
		texture_dst_type& TextureDst, size_t BaseLevelDst);

	// Copy multiple levels of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_level(
		texture_src_type const& TextureSrc, size_t BaseLevelSrc,
		texture_dst_type& TextureDst, size_t BaseLevelDst,
		size_t LevelCount);

	// Copy an entire face of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_face(
		texture_src_type const& TextureSrc, size_t BaseFaceSrc,
		texture_dst_type& TextureDst, size_t BaseFaceDst);

	// Copy multiple faces of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_face(
		texture_src_type const& TextureSrc, size_t BaseFaceSrc,
		texture_dst_type& TextureDst, size_t BaseFaceDst,
		size_t FaceCount);

	// Copy an entire layer of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_layer(
		texture_src_type const& TextureSrc, size_t BaseLayerSrc,
		texture_dst_type& TextureDst, size_t BaseLayerDst);

	// Copy multiple layers of a texture
	template <typename texture_src_type, typename texture_dst_type>
	void copy_layer(
		texture_src_type const& TextureSrc, size_t BaseLayerSrc,
		texture_dst_type& TextureDst, size_t BaseLayerDst,
		size_t LayerCount);
}//namespace gli

export namespace gli
{
	template <typename texture_src_type, typename texture_dst_type>
	void copy
	(
		texture_src_type const& TextureSrc, size_t LayerSrc, size_t FaceSrc, size_t LevelSrc,
		texture_dst_type& TextureDst, size_t LayerDst, size_t FaceDst, size_t LevelDst
	)
	{
		TextureDst.copy(TextureSrc, LayerSrc, FaceSrc, LevelSrc, LayerDst, FaceDst, LevelDst);
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy
	(
		texture_src_type const& TextureSrc,
		texture_dst_type& TextureDst
	)
	{
		copy_layer(TextureSrc, 0, TextureDst, 0, TextureDst.layers());
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy_level
	(
		texture_src_type const& TextureSrc, size_t BaseLevelSrc,
		texture_dst_type& TextureDst, size_t BaseLevelDst,
		size_t LevelCount
	)
	{
		for(size_t LayerIndex = 0, LayerCount = TextureSrc.layers(); LayerIndex < LayerCount; ++LayerIndex)
		for(size_t FaceIndex = 0, FaceCount = TextureSrc.faces(); FaceIndex < FaceCount; ++FaceIndex)
		for(size_t LevelIndex = 0; LevelIndex < LevelCount; ++LevelIndex)
		{
			TextureDst.copy(
				TextureSrc,
				LayerIndex, FaceIndex, BaseLevelSrc + LevelIndex,
				LayerIndex, FaceIndex, BaseLevelDst + LevelIndex);
		}
	}
	
	template <typename texture_src_type, typename texture_dst_type>
	void copy_level
	(
		texture_src_type const& TextureSrc, size_t BaseLevelSrc,
		texture_dst_type& TextureDst, size_t BaseLevelDst
	)
	{
		copy_level(TextureSrc, BaseLevelSrc, TextureDst, BaseLevelDst, 1);
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy_face
	(
		texture_src_type const& TextureSrc, size_t BaseFaceSrc,
		texture_dst_type& TextureDst, size_t BaseFaceDst,
		size_t FaceCount
	)
	{
		for(size_t LayerIndex = 0, LayerCount = TextureSrc.layers(); LayerIndex < LayerCount; ++LayerIndex)
		for(size_t FaceIndex = 0; FaceIndex < FaceCount; ++FaceIndex)
		for(size_t LevelIndex = 0, LevelCount = TextureSrc.levels(); LevelIndex < LevelCount; ++LevelIndex)
		{
			TextureDst.copy(
				TextureSrc,
				LayerIndex, BaseFaceSrc + FaceIndex, LevelIndex,
				LayerIndex, BaseFaceDst + FaceIndex, LevelIndex);
		}
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy_face
	(
		texture_src_type const& TextureSrc, size_t BaseFaceSrc,
		texture_dst_type& TextureDst, size_t BaseFaceDst
	)
	{
		copy_face(TextureSrc, BaseFaceSrc, TextureDst, BaseFaceDst, 1);
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy_layer
	(
		texture_src_type const& TextureSrc, size_t BaseLayerSrc,
		texture_dst_type& TextureDst, size_t BaseLayerDst,
		size_t LayerCount
	)
	{
		for(size_t LayerIndex = 0; LayerIndex < LayerCount; ++LayerIndex)
		for(size_t FaceIndex = 0, FaceCount = TextureSrc.faces(); FaceIndex < FaceCount; ++FaceIndex)
		for(size_t LevelIndex = 0, LevelCount = TextureSrc.levels(); LevelIndex < LevelCount; ++LevelIndex)
		{
			TextureDst.copy(
				TextureSrc,
				BaseLayerSrc + LayerIndex, FaceIndex, LevelIndex,
				BaseLayerDst + LayerIndex, FaceIndex, LevelIndex);
		}
	}

	template <typename texture_src_type, typename texture_dst_type>
	void copy_layer
	(
		texture_src_type const& TextureSrc, size_t BaseLayerSrc,
		texture_dst_type& TextureDst, size_t BaseLayerDst
	)
	{
		copy_layer(TextureSrc, BaseLayerSrc, TextureDst, BaseLayerDst, 1);
	}
}//namespace gli
