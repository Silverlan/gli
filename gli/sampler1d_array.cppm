/// @brief Include to sample 1d array textures.
/// @file gli/sampler1d_array.hpp

module;

#include "definitions.hpp"

export module gli:sampler1d_array;

import :core.clear;
import :core.filter_compute;
import :core.mipmaps_compute;
export import :convert;
export import :sampler;
export import :texture1d_array;

export namespace gli
{
	/// 1d array texture sampler
	/// @tparam T Sampler can fetch, write and interpret any texture format but will expose and process the data through type T conversions.
	/// @tparam P Precision in term of ULPs
	template <typename T, qualifier P = defaultp>
	class sampler1d_array : public sampler
	{
	private:
		typedef typename detail::interpolate<T>::type interpolate_type;

	public:
		typedef texture1d_array texture_type;
		typedef typename texture_type::size_type size_type;
		typedef typename texture_type::extent_type extent_type;
		typedef interpolate_type level_type;
		typedef vec<1, interpolate_type, P> normalized_type;
		typedef vec<4, T, P> texel_type;

		sampler1d_array(texture_type const& Texture, wrap Wrap, filter Mip = FILTER_NEAREST, filter Min = FILTER_NEAREST, texel_type const& BorderColor = texel_type(0, 0, 0, 1));

		/// Access the sampler texture object
		texture_type const& operator()() const;

		/// Fetch a texel from the sampler texture
		texel_type texel_fetch(extent_type const& TexelCoord, size_type layer, size_type Level) const;

		/// Write a texel in the sampler texture
		void texel_write(extent_type const& TexelCoord, size_type layer, size_type Level, texel_type const & Texel);

		/// Clear the sampler texture with a uniform texel
		void clear(texel_type const& Texel);

		/// Sample the sampler texture at a specific level
		texel_type texture_lod(normalized_type const& SampleCoord, size_type layer, level_type Level) const;

		/// Generate all the mipmaps of the sampler texture from the texture base level
		void generate_mipmaps(filter Minification);

		/// Generate the mipmaps of the sampler texture from the texture base level to the texture max level included
		void generate_mipmaps(size_type BaseLayer, size_type MaxLayer, size_type BaseLevel, size_type MaxLevel, filter Minification);

	private:
		typedef typename detail::convert<texture_type, T, P>::func convert_type;
		typedef typename detail::convert<texture_type, T, P>::fetchFunc fetch_type;
		typedef typename detail::convert<texture_type, T, P>::writeFunc write_type;
		typedef typename detail::filterBase<detail::DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type>::filterFunc filter_type;

		texture_type Texture;
		convert_type Convert;
		texel_type BorderColor;
		filter_type Filter;
	};

	typedef sampler1d_array<float> fsampler1DArray;
	typedef sampler1d_array<double> dsampler1DArray;
	typedef sampler1d_array<unsigned int> usampler1DArray;
	typedef sampler1d_array<int> isampler1DArray;

}//namespace gli

export namespace gli
{
	template <typename T, qualifier P>
	inline sampler1d_array<T, P>::sampler1d_array(texture_type const & Texture, gli::wrap Wrap, filter Mip, filter Min, texel_type const & BorderColor)
		: sampler(Wrap, Texture.levels() > 1 ? Mip : FILTER_NEAREST, Min)
		, Texture(Texture)
		, Convert(detail::convert<texture_type, T, P>::call(this->Texture.format()))
		, BorderColor(BorderColor)
		, Filter(detail::get_filter<filter_type, detail::DIMENSION_1D, texture_type, interpolate_type, normalized_type, fetch_type, texel_type, T>(Mip, Min, is_border(Wrap)))
	{
		GLI_ASSERT(!Texture.empty());
		GLI_ASSERT(!is_compressed(Texture.format()));
		GLI_ASSERT((!std::numeric_limits<T>::is_iec559 && Mip == FILTER_NEAREST && Min == FILTER_NEAREST) || std::numeric_limits<T>::is_iec559);
	}

	template <typename T, qualifier P>
	inline typename sampler1d_array<T, P>::texture_type const & sampler1d_array<T, P>::operator()() const
	{
		return this->Texture;
	}

	template <typename T, qualifier P>
	inline typename sampler1d_array<T, P>::texel_type sampler1d_array<T, P>::texel_fetch(extent_type const & TexelCoord, size_type layer, size_type Level) const
	{
		GLI_ASSERT(!this->Texture.empty());
		GLI_ASSERT(this->Convert.Fetch);

		return this->Convert.Fetch(this->Texture, TexelCoord, layer, 0, Level);
	}

	template <typename T, qualifier P>
	inline void sampler1d_array<T, P>::texel_write(extent_type const & TexelCoord, size_type layer, size_type Level, texel_type const & Texel)
	{
		GLI_ASSERT(!this->Texture.empty());
		GLI_ASSERT(this->Convert.Write);

		this->Convert.Write(this->Texture, TexelCoord, layer, 0, Level, Texel);
	}

	template <typename T, qualifier P>
	inline void sampler1d_array<T, P>::clear(texel_type const & Color)
	{
		GLI_ASSERT(!this->Texture.empty());
		GLI_ASSERT(this->Convert.Write);

		detail::clear<texture_type, T, P>::call(this->Texture, this->Convert.Write, Color);
	}

	template <typename T, qualifier P>
	inline typename sampler1d_array<T, P>::texel_type sampler1d_array<T, P>::texture_lod(normalized_type const & SampleCoord, size_type Layer, level_type Level) const
	{
		GLI_ASSERT(!this->Texture.empty());
		GLI_ASSERT(std::numeric_limits<T>::is_iec559);
		GLI_ASSERT(this->Filter && this->Convert.Fetch);

		normalized_type const SampleCoordWrap(this->Wrap(SampleCoord.x));
		return this->Filter(this->Texture, this->Convert.Fetch, SampleCoordWrap, Layer, size_type(0), Level, this->BorderColor);
	}

	template <typename T, qualifier P>
	inline void sampler1d_array<T, P>::generate_mipmaps(filter Minification)
	{
		this->generate_mipmaps(this->Texture.base_layer(), this->Texture.max_layer(), this->Texture.base_level(), this->Texture.max_level(), Minification);
	}

	template <typename T, qualifier P>
	inline void sampler1d_array<T, P>::generate_mipmaps(size_type BaseLayer, size_type MaxLayer, size_type BaseLevel, size_type MaxLevel, filter Minification)
	{
		GLI_ASSERT(!this->Texture.empty());
		GLI_ASSERT(!is_compressed(this->Texture.format()));
		GLI_ASSERT(this->Texture.base_layer() <= BaseLayer && BaseLayer <= MaxLayer && MaxLayer <= this->Texture.max_layer());
		GLI_ASSERT(this->Texture.base_level() <= BaseLevel && BaseLevel <= MaxLevel && MaxLevel <= this->Texture.max_level());
		GLI_ASSERT(this->Convert.Fetch && this->Convert.Write);
		GLI_ASSERT(Minification >= FILTER_FIRST && Minification <= FILTER_LAST);

		detail::generate_mipmaps_1d<texture_type, T, fetch_type, write_type, normalized_type, texel_type>(
			this->Texture, this->Convert.Fetch, this->Convert.Write, BaseLayer, MaxLayer, 0, 0, BaseLevel, MaxLevel, Minification);
	}
}//namespace gli
