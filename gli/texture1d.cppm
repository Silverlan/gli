/// @brief Include to use 1d textures.
/// @file gli/texture1d.hpp

module;

#include "definitions.hpp"

export module gli:texture1d;

export import :image;
import :levels;
export import :texture;

export namespace gli
{
	/// 1d texture
	class texture1d : public texture
	{
	public:
		typedef extent1d extent_type;

		/// Create an empty texture 1D
		texture1d();

		/// Create a texture1d and allocate a new storage_linear
		texture1d(
			format_type Format,
			extent_type const& Extent,
			size_type Levels,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture1d and allocate a new storage_linear with a complete mipmap chain
		texture1d(
			format_type Format,
			extent_type const& Extent,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture1d view with an existing storage_linear
		explicit texture1d(
			texture const& Texture);

		/// Create a texture1d view with an existing storage_linear
		texture1d(
			texture const& Texture,
			format_type Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture1d view, reference a subset of an existing texture1d instance
		texture1d(
			texture1d const& Texture,
			size_type BaseLevel, size_type MaxLevel);

		/// Create a view of the image identified by Level in the mipmap chain of the texture
		image operator[](size_type Level) const;

		/// Return the width of a texture instance 
		extent_type extent(size_type Level = 0) const;

		/// Fetch a texel from a texture. The texture format must be uncompressed.
		template <typename gen_type>
		gen_type load(extent_type const& TexelCoord, size_type Level) const;

		/// Write a texel to a texture. The texture format must be uncompressed.
		template <typename gen_type>
		void store(extent_type const& TexelCoord, size_type Level, gen_type const& Texel);
	};
}//namespace gli

export namespace gli
{
	inline texture1d::texture1d()
	{}

	inline texture1d::texture1d(format_type Format, extent_type const& Extent, swizzles_type const& Swizzles)
		: texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, gli::levels(Extent), Swizzles)
	{}

	inline texture1d::texture1d(format_type Format, extent_type const& Extent, size_type Levels, swizzles_type const& Swizzles)
		: texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, Levels, Swizzles)
	{}

	inline texture1d::texture1d(texture const& Texture)
		: texture(Texture, TARGET_1D, Texture.format())
	{}

	inline texture1d::texture1d
	(
		texture const& Texture,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: texture(
			Texture, TARGET_1D,
			Format,
			BaseLayer, MaxLayer,
			BaseFace, MaxFace,
			BaseLevel, MaxLevel,
		Swizzles)
	{}
 
	inline texture1d::texture1d
	(
		texture1d const& Texture,
		size_type BaseLevel, size_type MaxLevel
	)
		: texture(
			Texture, TARGET_1D,
			Texture.format(),
			Texture.base_layer(), Texture.max_layer(),
			Texture.base_face(), Texture.max_face(),
			Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel)
	{}

	inline image texture1d::operator[](texture1d::size_type Level) const
	{
		GLI_ASSERT(Level < this->levels());

		return image(
			this->Storage,
			this->format(),
			this->base_layer(),
			this->base_face(),
			this->base_level() + Level);
	}

	inline texture1d::extent_type texture1d::extent(size_type Level) const
	{
		return extent_type(this->texture::extent(Level));
	}

	template <typename gen_type>
	inline gen_type texture1d::load(extent_type const& TexelCoord, size_type Level) const
	{
		return this->texture::load<gen_type>(texture::extent_type(TexelCoord.x, 0, 0), 0, 0, Level);
	}

	template <typename gen_type>
	inline void texture1d::store(extent_type const& TexelCoord, size_type Level, gen_type const& Texel)
	{
		this->texture::store<gen_type>(texture::extent_type(TexelCoord.x, 0, 0), 0, 0, Level, Texel);
	}
}//namespace gli
