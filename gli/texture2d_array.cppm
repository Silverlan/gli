/// @brief Include to use 2d array textures.
/// @file gli/texture2d_array.hpp

module;

#include "definitions.hpp"

export module gli:texture2d_array;

export import :texture2d;

namespace gli
{
	/// 2d array texture
	class texture2d_array : public texture
	{
	public:
		typedef extent2d extent_type;

	public:
		/// Create an empty texture 2D array
		texture2d_array();

		/// Create a texture2d_array and allocate a new storage_linear
		texture2d_array(
			format_type Format,
			extent_type const& Extent,
			size_type Layers,
			size_type Levels,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture2d_array and allocate a new storage_linear with a complete mipmap chain
		texture2d_array(
			format_type Format,
			extent_type const& Extent,
			size_type Layers,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture2d_array view with an existing storage_linear
		explicit texture2d_array(
			texture const& Texture);

		/// Create a texture2d_array view with an existing storage_linear
		texture2d_array(
			texture const& Texture,
			format_type Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture view, reference a subset of an exiting texture2d_array instance
		texture2d_array(
			texture2d_array const& Texture,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseLevel, size_type MaxLevel);

		/// Create a view of the texture identified by Layer in the texture array
		texture2d operator[](size_type Layer) const;

		/// Return the dimensions of a texture instance: width and height 
		extent_type extent(size_type Level = 0) const;

		/// Fetch a texel from a texture. The texture format must be uncompressed.
		template <typename gen_type>
		gen_type load(extent_type const& TexelCoord, size_type Layer, size_type Level) const;

		/// Write a texel to a texture. The texture format must be uncompressed.
		template <typename gen_type>
		void store(extent_type const& TexelCoord, size_type Layer, size_type Level, gen_type const& Texel);
	};
}//namespace gli

export namespace gli
{
	inline texture2d_array::texture2d_array()
	{}

	inline texture2d_array::texture2d_array(format_type Format, extent_type const& Extent, size_type Layers, swizzles_type const& Swizzles)
		: texture(TARGET_2D_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 1, gli::levels(Extent), Swizzles)
	{}

	inline texture2d_array::texture2d_array(format_type Format, extent_type const& Extent, size_type Layers, size_type Levels, swizzles_type const& Swizzles)
		: texture(TARGET_2D_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 1, Levels, Swizzles)
	{}

	inline texture2d_array::texture2d_array(texture const& Texture)
		: texture(Texture, TARGET_2D_ARRAY, Texture.format())
	{}

	inline texture2d_array::texture2d_array
	(
		texture const& Texture,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: texture(
			Texture, TARGET_2D_ARRAY,
			Format,
			BaseLayer, MaxLayer,
			BaseFace, MaxFace,
			BaseLevel, MaxLevel,
			Swizzles)
	{}

	inline texture2d_array::texture2d_array
	(
		texture2d_array const& Texture,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseLevel, size_type MaxLevel
	)
		: texture(
			Texture, TARGET_2D_ARRAY,
			Texture.format(),
			Texture.base_layer() + BaseLayer, Texture.base_layer() + MaxLayer,
			Texture.base_face(), Texture.max_face(),
			Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel)
	{}

	inline texture2d texture2d_array::operator[](size_type Layer) const
	{
		GLI_ASSERT(Layer < this->layers());

		return texture2d(
			*this, this->format(),
			this->base_layer() + Layer, this->base_layer() + Layer,
			this->base_face(), this->max_face(),
			this->base_level(), this->max_level());
	}

	inline texture2d_array::extent_type texture2d_array::extent(size_type Level) const
	{
		return extent_type(this->texture::extent(Level));
	}

	template <typename gen_type>
	inline gen_type texture2d_array::load(extent_type const& TexelCoord, size_type Layer, size_type Level) const
	{
		return this->texture::load<gen_type>(texture::extent_type(TexelCoord, 0), Layer, 0, Level);
	}

	template <typename gen_type>
	inline void texture2d_array::store(extent_type const& TexelCoord, size_type Layer, size_type Level, gen_type const& Texel)
	{
		this->texture::store<gen_type>(texture::extent_type(TexelCoord, 0), Layer, 0, Level, Texel);
	}
}//namespace gli
