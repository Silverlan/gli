/// @brief Include to use cube map textures.
/// @file gli/texture_cube.hpp

module;

#include "definitions.hpp"

export module gli:texture_cube;

export import :texture2d;

export namespace gli
{
	/// Cube map texture
	class texture_cube : public texture
	{
	public:
		typedef extent2d extent_type;

	public:
		/// Create an empty texture cube
		texture_cube();

		/// Create a texture_cube and allocate a new storage_linear
		texture_cube(
			format_type Format,
			extent_type const & Extent,
			size_type Levels,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture_cube and allocate a new storage_linear with a complete mipmap chain
		texture_cube(
			format_type Format,
			extent_type const & Extent,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture_cube view with an existing storage_linear
		explicit texture_cube(
			texture const& Texture);

		/// Create a texture_cube view with an existing storage_linear
		texture_cube(
			texture const& Texture,
			format_type Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture_cube view, reference a subset of an existing texture_cube instance
		texture_cube(
			texture_cube const& Texture,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel);

		/// Create a view of the texture identified by Face in the texture cube
		texture2d operator[](size_type Face) const;

		/// Return the dimensions of a texture instance: width and height where both should be equal.
		extent_type extent(size_type Level = 0) const;

		/// Fetch a texel from a texture. The texture format must be uncompressed.
		template <typename gen_type>
		gen_type load(extent_type const& TexelCoord, size_type Face, size_type Level) const;

		/// Write a texel to a texture. The texture format must be uncompressed.
		template <typename gen_type>
		void store(extent_type const& TexelCoord, size_type Face, size_type Level, gen_type const& Texel);
	};
}//namespace gli

export namespace gli
{
	inline texture_cube::texture_cube()
	{}

	inline texture_cube::texture_cube(format_type Format, extent_type const& Extent, swizzles_type const& Swizzles)
		: texture(TARGET_CUBE, Format, texture::extent_type(Extent, 1), 1, 6, gli::levels(Extent), Swizzles)
	{}

	inline texture_cube::texture_cube(format_type Format, extent_type const& Extent, size_type Levels, swizzles_type const& Swizzles)
		: texture(TARGET_CUBE, Format, texture::extent_type(Extent, 1), 1, 6, Levels, Swizzles)
	{}

	inline texture_cube::texture_cube(texture const& Texture)
		: texture(Texture, TARGET_CUBE, Texture.format())
	{}

	inline texture_cube::texture_cube
	(
		texture const& Texture,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: texture(
			Texture, TARGET_CUBE, Format,
			BaseLayer, MaxLayer,
			BaseFace, MaxFace,
			BaseLevel, MaxLevel,
			Swizzles)
	{}

	inline texture_cube::texture_cube
	(
		texture_cube const& Texture,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel
	)
		: texture(
			Texture, TARGET_CUBE, Texture.format(),
			Texture.base_layer(), Texture.max_layer(),
			Texture.base_face() + BaseFace, Texture.base_face() + MaxFace,
			Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel)
	{}

	inline texture2d texture_cube::operator[](size_type Face) const
	{
		GLI_ASSERT(Face < this->faces());

		return texture2d(
			*this, this->format(),
			this->base_layer(), this->max_layer(),
			this->base_face() + Face, this->base_face() + Face,
			this->base_level(), this->max_level());
	}

	inline texture_cube::extent_type texture_cube::extent(size_type Level) const
	{
		return extent_type(this->texture::extent(Level));
	}

	template <typename gen_type>
	inline gen_type texture_cube::load(extent_type const& TexelCoord, size_type Face, size_type Level) const
	{
		return this->texture::load<gen_type>(texture::extent_type(TexelCoord, 0), 0, Face, Level);
	}

	template <typename gen_type>
	inline void texture_cube::store(extent_type const& TexelCoord, size_type Face, size_type Level, gen_type const& Texel)
	{
		this->texture::store<gen_type>(texture::extent_type(TexelCoord, 0), 0, Face, Level, Texel);
	}
}//namespace gli
