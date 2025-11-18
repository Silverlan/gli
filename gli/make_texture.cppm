/// @brief Helper functions to create generic texture
/// @file gli/make_texture.hpp

module;

export module gli:make_texture;

export import :levels;
export import :texture;

export namespace gli
{
	// Helper function to create a 1d texture with a specific number of levels
	gli::texture make_texture1d(format Format, extent1d const& Extent, size_t Levels);

	// Helper function to create a 1d texture with a complete mipmap chain
	gli::texture make_texture1d(format Format, extent1d const& Extent);

	// Helper function to create a 1d array texture with a specific number of levels
	gli::texture make_texture1d_array(format Format, extent1d const& Extent, size_t Layers, size_t Levels);

	// Helper function to create a 1d array texture with a complete mipmap chain
	gli::texture make_texture1d_array(format Format, extent1d const& Extent, size_t Layers);

	// Helper function to create a 2d texture with a specific number of levels
	gli::texture make_texture2d(format Format, extent2d const& Extent, size_t Levels);

	// Helper function to create a 2d texture with a complete mipmap chain
	gli::texture make_texture2d(format Format, extent2d const& Extent);

	// Helper function to create a 2d array texture with a specific number of levels
	gli::texture make_texture2d_array(format Format, extent2d const& Extent, size_t Layer, size_t Levels);

	// Helper function to create a 2d array texture with a complete mipmap chain
	gli::texture make_texture2d_array(format Format, extent2d const& Extent, size_t Layer);

	// Helper function to create a 3d texture with a specific number of levels
	gli::texture make_texture3d(format Format, extent3d const& Extent, size_t Levels);

	// Helper function to create a 3d texture with a complete mipmap chain
	gli::texture make_texture3d(format Format, extent3d const& Extent);

	// Helper function to create a cube texture with a specific number of levels
	gli::texture make_texture_cube(format Format, extent2d const& Extent, size_t Levels);

	// Helper function to create a cube texture with a complete mipmap chain
	gli::texture make_texture_cube(format Format, extent2d const& Extent);

	// Helper function to create a cube array texture with a specific number of levels
	gli::texture make_texture_cube_array(format Format, extent2d const& Extent, size_t Layer, size_t Levels);

	// Helper function to create a cube array texture with a complete mipmap chain
	gli::texture make_texture_cube_array(format Format, extent2d const& Extent, size_t Layer);
}//namespace gli

export namespace gli
{
	inline gli::texture make_texture1d(format Format, extent1d const& Extent, size_t Levels)
	{
		return gli::texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, Levels);
	}

	inline gli::texture make_texture1d(format Format, extent1d const& Extent)
	{
		return gli::texture(TARGET_1D, Format, texture::extent_type(Extent.x, 1, 1), 1, 1, gli::levels(texture::extent_type(Extent.x, 1, 1)));
	}

	inline gli::texture make_texture1d_array(format Format, extent1d const& Extent, size_t Layers, size_t Levels)
	{
		return gli::texture(TARGET_1D_ARRAY, Format, texture::extent_type(Extent.x, 1, 1), Layers, 1, Levels);
	}

	inline gli::texture make_texture1d_array(format Format, extent1d const& Extent, size_t Layers)
	{
		return gli::texture(TARGET_1D_ARRAY, Format, texture::extent_type(Extent.x, 1, 1), Layers, 1, gli::levels(texture::extent_type(Extent.x, 1, 1)));
	}

	inline gli::texture make_texture2d(format Format, extent2d const& Extent, size_t Levels)
	{
		return gli::texture(TARGET_2D, Format, texture::extent_type(Extent, 1), 1, 1, Levels);
	}

	inline gli::texture make_texture2d(format Format, extent2d const& Extent)
	{
		return gli::texture(TARGET_2D, Format, texture::extent_type(Extent, 1), 1, 1, gli::levels(texture::extent_type(Extent, 1)));
	}

	inline gli::texture make_texture2d_array(format Format, extent2d const& Extent, size_t Layer, size_t Levels)
	{
		return gli::texture(TARGET_2D_ARRAY, Format, texture::extent_type(Extent, 1), Layer, 1, Levels);
	}

	inline gli::texture make_texture2d_array(format Format, extent2d const& Extent, size_t Layer)
	{
		return gli::texture(TARGET_2D_ARRAY, Format, texture::extent_type(Extent, 1), Layer, 1, gli::levels(texture::extent_type(Extent, 1)));
	}

	inline gli::texture make_texture3d(format Format, extent3d const& Extent, size_t Levels)
	{
		return gli::texture(TARGET_3D, Format, texture::extent_type(Extent), 1, 1, Levels);
	}

	inline gli::texture make_texture3d(format Format, extent3d const& Extent)
	{
		return gli::texture(TARGET_3D, Format, texture::extent_type(Extent), 1, 1, gli::levels(texture::extent_type(Extent)));
	}

	inline gli::texture make_texture_cube(format Format, extent2d const& Extent, size_t Levels)
	{
		return gli::texture(TARGET_CUBE, Format, texture::extent_type(Extent, 1), 1, 6, Levels);
	}

	inline gli::texture make_texture_cube(format Format, extent2d const& Extent)
	{
		return gli::texture(TARGET_CUBE, Format, texture::extent_type(Extent, 1), 1, 6, gli::levels(texture::extent_type(Extent, 1)));
	}

	inline gli::texture make_texture_cube_array(format Format, extent2d const& Extent, size_t Layer, size_t Levels)
	{
		return gli::texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layer, 6, Levels);
	}

	inline gli::texture make_texture_cube_array(format Format, extent2d const& Extent, size_t Layer)
	{
		return gli::texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layer, 6, gli::levels(texture::extent_type(Extent, 1)));
	}
}//namespace gli
