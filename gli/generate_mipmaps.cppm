/// @brief Include to generate mipmaps of textures.
/// @file gli/generate_mipmaps.hpp

module;

export module gli:generate_mipmaps;

export import :core.filter;
export import :sampler1d;
export import :sampler1d_array;
export import :sampler2d;
export import :sampler2d_array;
export import :sampler3d;
export import :sampler_cube;
export import :sampler_cube_array;

export namespace gli
{
	/// Allocate a texture and generate all the mipmaps of the texture using the Minification filter.
	template <typename texture_type>
	texture_type generate_mipmaps(texture_type const& Texture, filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLevel to the MaxLevel included using the Minification filter.
	texture1d generate_mipmaps(
		texture1d const& Texture,
		texture1d::size_type BaseLevel, texture1d::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLayer to the MaxLayer and from the BaseLevel to the MaxLevel included levels using the Minification filter.
	texture1d_array generate_mipmaps(
		texture1d_array const& Texture,
		texture1d_array::size_type BaseLayer, texture1d_array::size_type MaxLayer,
		texture1d_array::size_type BaseLevel, texture1d_array::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLevel to the MaxLevel included using the Minification filter.
	texture2d generate_mipmaps(
		texture2d const& Texture,
		texture2d::size_type BaseLevel, texture2d::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLayer to the MaxLayer and from the BaseLevel to the MaxLevel included levels using the Minification filter.
	texture2d_array generate_mipmaps(
		texture2d_array const& Texture,
		texture2d_array::size_type BaseLayer, texture2d_array::size_type MaxLayer,
		texture2d_array::size_type BaseLevel, texture2d_array::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLevel to the MaxLevel included using the Minification filter.
	texture3d generate_mipmaps(
		texture3d const& Texture,
		texture3d::size_type BaseLevel, texture3d::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLayer to the MaxLayer, from the BaseFace to the MaxFace and from the BaseLevel to the MaxLevel included levels using the Minification filter.
	texture_cube generate_mipmaps(
		texture_cube const& Texture,
		texture_cube::size_type BaseFace, texture_cube::size_type MaxFace,
		texture_cube::size_type BaseLevel, texture_cube::size_type MaxLevel,
		filter Minification);

	/// Allocate a texture and generate the mipmaps of the texture from the BaseLayer to the MaxLayer and from the BaseLevel to the MaxLevel included levels using the Minification filter.
	texture_cube_array generate_mipmaps(
		texture_cube_array const& Texture,
		texture_cube_array::size_type BaseLayer, texture_cube_array::size_type MaxLayer,
		texture_cube_array::size_type BaseFace, texture_cube_array::size_type MaxFace,
		texture_cube_array::size_type BaseLevel, texture_cube_array::size_type MaxLevel,
		filter Minification);
}//namespace gli

export namespace gli
{
	inline texture1d generate_mipmaps(
		texture1d const& Texture,
		texture1d::size_type BaseLevel, texture1d::size_type MaxLevel,
		filter Minification)
	{
		fsampler1D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture1d_array generate_mipmaps(
		texture1d_array const& Texture,
		texture1d_array::size_type BaseLayer, texture1d_array::size_type MaxLayer,
		texture1d_array::size_type BaseLevel, texture1d_array::size_type MaxLevel,
		filter Minification)
	{
		fsampler1DArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture2d generate_mipmaps(
		texture2d const& Texture,
		texture2d::size_type BaseLevel, texture2d::size_type MaxLevel,
		filter Minification)
	{
		fsampler2D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture2d_array generate_mipmaps(
		texture2d_array const& Texture,
		texture2d_array::size_type BaseLayer, texture2d_array::size_type MaxLayer,
		texture2d_array::size_type BaseLevel, texture2d_array::size_type MaxLevel,
		filter Minification)
	{
		fsampler2DArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture3d generate_mipmaps(
		texture3d const& Texture,
		texture3d::size_type BaseLevel, texture3d::size_type MaxLevel,
		filter Minification)
	{
		fsampler3D Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture_cube generate_mipmaps(
		texture_cube const& Texture,
		texture_cube::size_type BaseFace, texture_cube::size_type MaxFace,
		texture_cube::size_type BaseLevel, texture_cube::size_type MaxLevel,
		filter Minification)
	{
		fsamplerCube Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseFace, MaxFace, BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	inline texture_cube_array generate_mipmaps(
		texture_cube_array const& Texture,
		texture_cube_array::size_type BaseLayer, texture_cube_array::size_type MaxLayer,
		texture_cube_array::size_type BaseFace, texture_cube_array::size_type MaxFace,
		texture_cube_array::size_type BaseLevel, texture_cube_array::size_type MaxLevel,
		filter Minification)
	{
		fsamplerCubeArray Sampler(Texture, WRAP_CLAMP_TO_EDGE);
		Sampler.generate_mipmaps(BaseLayer, MaxLayer, BaseFace, MaxFace, BaseLevel, MaxLevel, Minification);
		return Sampler();
	}

	template <>
	inline texture1d generate_mipmaps<texture1d>(texture1d const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture1d_array generate_mipmaps<texture1d_array>(texture1d_array const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture2d generate_mipmaps<texture2d>(texture2d const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture2d_array generate_mipmaps<texture2d_array>(texture2d_array const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture3d generate_mipmaps<texture3d>(texture3d const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture_cube generate_mipmaps<texture_cube>(texture_cube const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_face(), Texture.max_face(), Texture.base_level(), Texture.max_level(), Minification);
	}

	template <>
	inline texture_cube_array generate_mipmaps<texture_cube_array>(texture_cube_array const& Texture, filter Minification)
	{
		return generate_mipmaps(Texture, Texture.base_layer(), Texture.max_layer(), Texture.base_face(), Texture.max_face(), Texture.base_level(), Texture.max_level(), Minification);
	}
}//namespace gli
