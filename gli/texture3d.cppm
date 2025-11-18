/// @brief Include to use 3d textures.
/// @file gli/texture3d.hpp

module;

#include "definitions.hpp"

export module gli:texture3d;

export import :image;
import :levels;
export import :texture;

export namespace gli
{
	/// 3d texture
	class texture3d : public texture
	{
	public:
		typedef extent3d extent_type;

	public:
		/// Create an empty texture 3D
		texture3d();

		/// Create a texture3d and allocate a new storage_linear
		texture3d(
			format_type Format,
			extent_type const& Extent,
			size_type Levels,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture3d and allocate a new storage_linear with a complete mipmap chain
		texture3d(
			format_type Format,
			extent_type const& Extent,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture3d view with an existing storage_linear
		explicit texture3d(
			texture const & Texture);

		/// Create a texture3d view with an existing storage_linear
		texture3d(
			texture const& Texture,
			format_type Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture3d view, reference a subset of an existing texture3d instance
		texture3d(
			texture3d const & Texture,
			size_type BaseLevel, size_type MaxLevel);

		/// Create a view of the image identified by Level in the mipmap chain of the texture
		image operator[](size_type Level) const;

		/// Return the dimensions of a texture instance: width, height and depth 
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
	inline texture3d::texture3d()
	{}

	inline texture3d::texture3d(format_type Format, extent_type const& Extent, swizzles_type const& Swizzles)
		: texture(TARGET_3D, Format, Extent, 1, 1, gli::levels(Extent), Swizzles)
	{}

	inline texture3d::texture3d(format_type Format, extent_type const& Extent, size_type Levels, swizzles_type const& Swizzles)
		: texture(TARGET_3D, Format, Extent, 1, 1, Levels, Swizzles)
	{}

	inline texture3d::texture3d(texture const& Texture)
		: texture(Texture, TARGET_3D, Texture.format())
	{}

	inline texture3d::texture3d
	(
		texture const& Texture,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: texture(
			Texture, TARGET_3D, Format,
			BaseLayer, MaxLayer,
			BaseFace, MaxFace,
			BaseLevel, MaxLevel,
			Swizzles)
	{}
 
	inline texture3d::texture3d
	(
		texture3d const& Texture,
		size_type BaseLevel, size_type MaxLevel
	)
		: texture(
			Texture, TARGET_3D, Texture.format(),
			Texture.base_layer(), Texture.max_layer(),
			Texture.base_face(), Texture.max_face(),
			Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel)
	{}

	inline image texture3d::operator[](size_type Level) const
	{
		GLI_ASSERT(Level < this->levels());

		return image(
			this->Storage,
			this->format(),
			this->base_layer(),
			this->base_face(),
			this->base_level() + Level);
	}

	inline texture3d::extent_type texture3d::extent(size_type Level) const
	{
		return extent_type(this->texture::extent(Level));
	}

	template <typename gen_type>
	inline gen_type texture3d::load(extent_type const& TexelCoord, size_type Level) const
	{
		return this->texture::load<gen_type>(texture::extent_type(TexelCoord), 0, 0, Level);
	}

	template <typename gen_type>
	inline void texture3d::store(extent_type const& TexelCoord, size_type Level, gen_type const& Texel)
	{
		this->texture::store<gen_type>(texture::extent_type(TexelCoord), 0, 0, Level, Texel);
	}
}//namespace gli
