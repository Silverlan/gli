/// @brief Include to use the format enum and query properties of formats.
/// @file gli/format.hpp

module;

#include "definitions.hpp"
#include <cassert>

export module gli:format;

export import :type;

export namespace gli
{
	/// Texture data format
	enum format
	{
		FORMAT_UNDEFINED = 0,

		FORMAT_RG4_UNORM_PACK8, FORMAT_FIRST = FORMAT_RG4_UNORM_PACK8,
		FORMAT_RGBA4_UNORM_PACK16,
		FORMAT_BGRA4_UNORM_PACK16,
		FORMAT_R5G6B5_UNORM_PACK16,
		FORMAT_B5G6R5_UNORM_PACK16,
		FORMAT_RGB5A1_UNORM_PACK16,
		FORMAT_BGR5A1_UNORM_PACK16,
		FORMAT_A1RGB5_UNORM_PACK16,

		FORMAT_R8_UNORM_PACK8,
		FORMAT_R8_SNORM_PACK8,
		FORMAT_R8_USCALED_PACK8,
		FORMAT_R8_SSCALED_PACK8,
		FORMAT_R8_UINT_PACK8,
		FORMAT_R8_SINT_PACK8,
		FORMAT_R8_SRGB_PACK8,

		FORMAT_RG8_UNORM_PACK8,
		FORMAT_RG8_SNORM_PACK8,
		FORMAT_RG8_USCALED_PACK8,
		FORMAT_RG8_SSCALED_PACK8,
		FORMAT_RG8_UINT_PACK8,
		FORMAT_RG8_SINT_PACK8,
		FORMAT_RG8_SRGB_PACK8,

		FORMAT_RGB8_UNORM_PACK8,
		FORMAT_RGB8_SNORM_PACK8,
		FORMAT_RGB8_USCALED_PACK8,
		FORMAT_RGB8_SSCALED_PACK8,
		FORMAT_RGB8_UINT_PACK8,
		FORMAT_RGB8_SINT_PACK8,
		FORMAT_RGB8_SRGB_PACK8,

		FORMAT_BGR8_UNORM_PACK8,
		FORMAT_BGR8_SNORM_PACK8,
		FORMAT_BGR8_USCALED_PACK8,
		FORMAT_BGR8_SSCALED_PACK8,
		FORMAT_BGR8_UINT_PACK8,
		FORMAT_BGR8_SINT_PACK8,
		FORMAT_BGR8_SRGB_PACK8,

		FORMAT_RGBA8_UNORM_PACK8,
		FORMAT_RGBA8_SNORM_PACK8,
		FORMAT_RGBA8_USCALED_PACK8,
		FORMAT_RGBA8_SSCALED_PACK8,
		FORMAT_RGBA8_UINT_PACK8,
		FORMAT_RGBA8_SINT_PACK8,
		FORMAT_RGBA8_SRGB_PACK8,

		FORMAT_BGRA8_UNORM_PACK8,
		FORMAT_BGRA8_SNORM_PACK8,
		FORMAT_BGRA8_USCALED_PACK8,
		FORMAT_BGRA8_SSCALED_PACK8,
		FORMAT_BGRA8_UINT_PACK8,
		FORMAT_BGRA8_SINT_PACK8,
		FORMAT_BGRA8_SRGB_PACK8,

		FORMAT_RGBA8_UNORM_PACK32,
		FORMAT_RGBA8_SNORM_PACK32,
		FORMAT_RGBA8_USCALED_PACK32,
		FORMAT_RGBA8_SSCALED_PACK32,
		FORMAT_RGBA8_UINT_PACK32,
		FORMAT_RGBA8_SINT_PACK32,
		FORMAT_RGBA8_SRGB_PACK32,

		FORMAT_RGB10A2_UNORM_PACK32,
		FORMAT_RGB10A2_SNORM_PACK32,
		FORMAT_RGB10A2_USCALED_PACK32,
		FORMAT_RGB10A2_SSCALED_PACK32,
		FORMAT_RGB10A2_UINT_PACK32,
		FORMAT_RGB10A2_SINT_PACK32,

		FORMAT_BGR10A2_UNORM_PACK32,
		FORMAT_BGR10A2_SNORM_PACK32,
		FORMAT_BGR10A2_USCALED_PACK32,
		FORMAT_BGR10A2_SSCALED_PACK32,
		FORMAT_BGR10A2_UINT_PACK32,
		FORMAT_BGR10A2_SINT_PACK32,

		FORMAT_R16_UNORM_PACK16,
		FORMAT_R16_SNORM_PACK16,
		FORMAT_R16_USCALED_PACK16,
		FORMAT_R16_SSCALED_PACK16,
		FORMAT_R16_UINT_PACK16,
		FORMAT_R16_SINT_PACK16,
		FORMAT_R16_SFLOAT_PACK16,

		FORMAT_RG16_UNORM_PACK16,
		FORMAT_RG16_SNORM_PACK16,
		FORMAT_RG16_USCALED_PACK16,
		FORMAT_RG16_SSCALED_PACK16,
		FORMAT_RG16_UINT_PACK16,
		FORMAT_RG16_SINT_PACK16,
		FORMAT_RG16_SFLOAT_PACK16,

		FORMAT_RGB16_UNORM_PACK16,
		FORMAT_RGB16_SNORM_PACK16,
		FORMAT_RGB16_USCALED_PACK16,
		FORMAT_RGB16_SSCALED_PACK16,
		FORMAT_RGB16_UINT_PACK16,
		FORMAT_RGB16_SINT_PACK16,
		FORMAT_RGB16_SFLOAT_PACK16,

		FORMAT_RGBA16_UNORM_PACK16,
		FORMAT_RGBA16_SNORM_PACK16,
		FORMAT_RGBA16_USCALED_PACK16,
		FORMAT_RGBA16_SSCALED_PACK16,
		FORMAT_RGBA16_UINT_PACK16,
		FORMAT_RGBA16_SINT_PACK16,
		FORMAT_RGBA16_SFLOAT_PACK16,

		FORMAT_R32_UINT_PACK32,
		FORMAT_R32_SINT_PACK32,
		FORMAT_R32_SFLOAT_PACK32,

		FORMAT_RG32_UINT_PACK32,
		FORMAT_RG32_SINT_PACK32,
		FORMAT_RG32_SFLOAT_PACK32,

		FORMAT_RGB32_UINT_PACK32,
		FORMAT_RGB32_SINT_PACK32,
		FORMAT_RGB32_SFLOAT_PACK32,

		FORMAT_RGBA32_UINT_PACK32,
		FORMAT_RGBA32_SINT_PACK32,
		FORMAT_RGBA32_SFLOAT_PACK32,

		FORMAT_R64_UINT_PACK64,
		FORMAT_R64_SINT_PACK64,
		FORMAT_R64_SFLOAT_PACK64,

		FORMAT_RG64_UINT_PACK64,
		FORMAT_RG64_SINT_PACK64,
		FORMAT_RG64_SFLOAT_PACK64,

		FORMAT_RGB64_UINT_PACK64,
		FORMAT_RGB64_SINT_PACK64,
		FORMAT_RGB64_SFLOAT_PACK64,

		FORMAT_RGBA64_UINT_PACK64,
		FORMAT_RGBA64_SINT_PACK64,
		FORMAT_RGBA64_SFLOAT_PACK64,

		FORMAT_RG11B10_UFLOAT_PACK32,
		FORMAT_RGB9E5_UFLOAT_PACK32,

		FORMAT_D16_UNORM_PACK16,
		FORMAT_D24_UNORM_PACK32,
		FORMAT_D32_SFLOAT_PACK32,
		FORMAT_S8_UINT_PACK8,
		FORMAT_D16_UNORM_S8_UINT_PACK32,
		FORMAT_D24_UNORM_S8_UINT_PACK32,
		FORMAT_D32_SFLOAT_S8_UINT_PACK64,

		FORMAT_RGB_DXT1_UNORM_BLOCK8,
		FORMAT_RGB_DXT1_SRGB_BLOCK8,
		FORMAT_RGBA_DXT1_UNORM_BLOCK8,
		FORMAT_RGBA_DXT1_SRGB_BLOCK8,
		FORMAT_RGBA_DXT3_UNORM_BLOCK16,
		FORMAT_RGBA_DXT3_SRGB_BLOCK16,
		FORMAT_RGBA_DXT5_UNORM_BLOCK16,
		FORMAT_RGBA_DXT5_SRGB_BLOCK16,
		FORMAT_R_ATI1N_UNORM_BLOCK8,
		FORMAT_R_ATI1N_SNORM_BLOCK8,
		FORMAT_RG_ATI2N_UNORM_BLOCK16,
		FORMAT_RG_ATI2N_SNORM_BLOCK16,
		FORMAT_RGB_BP_UFLOAT_BLOCK16,
		FORMAT_RGB_BP_SFLOAT_BLOCK16,
		FORMAT_RGBA_BP_UNORM_BLOCK16,
		FORMAT_RGBA_BP_SRGB_BLOCK16,

		FORMAT_RGB_ETC2_UNORM_BLOCK8,
		FORMAT_RGB_ETC2_SRGB_BLOCK8,
		FORMAT_RGBA_ETC2_UNORM_BLOCK8,
		FORMAT_RGBA_ETC2_SRGB_BLOCK8,
		FORMAT_RGBA_ETC2_UNORM_BLOCK16,
		FORMAT_RGBA_ETC2_SRGB_BLOCK16,
		FORMAT_R_EAC_UNORM_BLOCK8,
		FORMAT_R_EAC_SNORM_BLOCK8,
		FORMAT_RG_EAC_UNORM_BLOCK16,
		FORMAT_RG_EAC_SNORM_BLOCK16,

		FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16,
		FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16,
		FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16,

		FORMAT_RGB_PVRTC1_8X8_UNORM_BLOCK32,
		FORMAT_RGB_PVRTC1_8X8_SRGB_BLOCK32,
		FORMAT_RGB_PVRTC1_16X8_UNORM_BLOCK32,
		FORMAT_RGB_PVRTC1_16X8_SRGB_BLOCK32,
		FORMAT_RGBA_PVRTC1_8X8_UNORM_BLOCK32,
		FORMAT_RGBA_PVRTC1_8X8_SRGB_BLOCK32,
		FORMAT_RGBA_PVRTC1_16X8_UNORM_BLOCK32,
		FORMAT_RGBA_PVRTC1_16X8_SRGB_BLOCK32,
		FORMAT_RGBA_PVRTC2_4X4_UNORM_BLOCK8,
		FORMAT_RGBA_PVRTC2_4X4_SRGB_BLOCK8,
		FORMAT_RGBA_PVRTC2_8X4_UNORM_BLOCK8,
		FORMAT_RGBA_PVRTC2_8X4_SRGB_BLOCK8,

		FORMAT_RGB_ETC_UNORM_BLOCK8,
		FORMAT_RGB_ATC_UNORM_BLOCK8,
		FORMAT_RGBA_ATCA_UNORM_BLOCK16,
		FORMAT_RGBA_ATCI_UNORM_BLOCK16,

		FORMAT_L8_UNORM_PACK8,
		FORMAT_A8_UNORM_PACK8,
		FORMAT_LA8_UNORM_PACK8,
		FORMAT_L16_UNORM_PACK16,
		FORMAT_A16_UNORM_PACK16,
		FORMAT_LA16_UNORM_PACK16,

		FORMAT_BGR8_UNORM_PACK32,
		FORMAT_BGR8_SRGB_PACK32,

		FORMAT_RG3B2_UNORM_PACK8, FORMAT_LAST = FORMAT_RG3B2_UNORM_PACK8
	};

	/// Represent the source of a channel
	enum swizzle
	{
		SWIZZLE_RED, SWIZZLE_FIRST = SWIZZLE_RED, SWIZZLE_CHANNEL_FIRST = SWIZZLE_RED,
		SWIZZLE_GREEN,
		SWIZZLE_BLUE,
		SWIZZLE_ALPHA, SWIZZLE_CHANNEL_LAST = SWIZZLE_ALPHA,
		SWIZZLE_ZERO,
		SWIZZLE_ONE, SWIZZLE_LAST = SWIZZLE_ONE
	};

	/// Determine whether the Swizzle value represent a channel
	inline bool is_channel(swizzle Swizzle)
	{
		return Swizzle >= SWIZZLE_CHANNEL_FIRST && Swizzle <= SWIZZLE_CHANNEL_LAST;
	}

	enum
	{
		FORMAT_COUNT = FORMAT_LAST - FORMAT_FIRST + 1,
		SWIZZLE_COUNT = SWIZZLE_LAST - SWIZZLE_FIRST + 1
	};

	/// Evaluate whether a format value is value or not
	inline bool is_valid(format Format)
	{
		return Format >= FORMAT_FIRST && Format <= FORMAT_LAST;
	}

	typedef glm::vec<4, swizzle> swizzles;

	/// Evaluate whether a format is compressed
	bool is_compressed(format Format);

	/// Evaluate whether a format is compressed with an S3TC algorithm.
	bool is_s3tc_compressed(format Format);

	/// Evaluate whether a format stores sRGB color space values
	bool is_srgb(format Format);

	/// Return the size in bytes of a block for a format.
	size_t block_size(format Format);

	/// Return the dimensions in texels of the block for a format
	ivec3 block_extent(format Format);

	/// Return the number of components of a format
	size_t component_count(format Format);

	/// Evaluate whether a format is unsigned
	bool is_unsigned(format Format);

	/// Evaluate whether a format is signed
	bool is_signed(format Format);

	/// Evaluate whether the format is an integer format
	bool is_integer(format Format);

	/// Evaluate whether the format is a signed integer format
	bool is_signed_integer(format Format);

	/// Evaluate whether the format is an unsigned integer format
	bool is_unsigned_integer(format Format);

	/// Evaluate whether the format is an float format
	bool is_float(format Format);

	/// Evaluate whether the format is normalized
	bool is_normalized(format Format);

	/// Evaluate whether the format is an unsigned normalized format
	bool is_unorm(format Format);

	/// Evaluate whether the format is a signed normalized format
	bool is_snorm(format Format);

	/// Evaluate whether the format is packed
	bool is_packed(format Format);

	/// Evaluate whether the format is a depth format
	bool is_depth(format Format);

	/// Evaluate whether the format has a stencil component
	bool is_stencil(format Format);

	/// Evaluate whether the format has depth and stencil components
	bool is_depth_stencil(format Format);

}//namespace gli

namespace gli{
namespace detail
{
	enum
	{
		CAP_COMPRESSED_BIT = (1 << 0),
		CAP_COLORSPACE_SRGB_BIT = (1 << 1),
		CAP_NORMALIZED_BIT = (1 << 2),
		CAP_SCALED_BIT = (1 << 3),
		CAP_UNSIGNED_BIT = (1 << 4),
		CAP_SIGNED_BIT = (1 << 5),
		CAP_INTEGER_BIT = (1 << 6),
		CAP_FLOAT_BIT = (1 << 7),
		CAP_DEPTH_BIT = (1 << 8),
		CAP_STENCIL_BIT = (1 << 9),
		CAP_SWIZZLE_BIT = (1 << 10),
		CAP_LUMINANCE_ALPHA_BIT = (1 << 11),
		CAP_PACKED8_BIT = (1 << 12),
		CAP_PACKED16_BIT = (1 << 13),
		CAP_PACKED32_BIT = (1 << 14),
		CAP_DDS_GLI_EXT_BIT = (1 << 15),
		CAP_DECODER_BIT = (1 << 16)
	};

	struct formatInfo
	{
		glm::uint8 BlockSize;
		glm::u8vec3 BlockExtent;
		glm::uint8 Component;
		swizzles Swizzles;
		glm::uint32 Flags;
	};

	formatInfo const & get_format_info(format Format);

	inline std::uint32_t bits_per_pixel(format Format)
	{
		detail::formatInfo const & Info = detail::get_format_info(Format);

		return Info.BlockSize * 8 / (Info.BlockExtent.x * Info.BlockExtent.y * Info.BlockExtent.z);
	}
}//namespace detail
}

export namespace gli{
	inline bool has_decoder(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_DECODER_BIT ? true : false;
	}

	inline bool is_compressed(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_COMPRESSED_BIT ? true : false;
	}

	inline bool is_s3tc_compressed(format Format)
	{
		return Format >= FORMAT_RGB_DXT1_UNORM_BLOCK8 && Format <= FORMAT_RGBA_DXT5_SRGB_BLOCK16;
	}

	inline bool is_srgb(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_COLORSPACE_SRGB_BIT ? true : false;
	}

	inline size_t block_size(format Format)
	{
		return detail::get_format_info(Format).BlockSize;
	}

	inline ivec3 block_extent(format Format)
	{
		return gli::ivec3(detail::get_format_info(Format).BlockExtent);
	}

	inline size_t component_count(format Format)
	{
		return detail::get_format_info(Format).Component;
	}

	inline bool is_unsigned(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_UNSIGNED_BIT ? true : false;
	}

	inline bool is_signed(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_SIGNED_BIT ? true : false;
	}

	inline bool is_integer(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_INTEGER_BIT ? true : false;
	}

	inline bool is_signed_integer(format Format)
	{
		return is_integer(Format) && is_signed(Format);
	}

	inline bool is_unsigned_integer(format Format)
	{
		return is_integer(Format) && is_unsigned(Format);
	}

	inline bool is_float(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_FLOAT_BIT ? true : false;
	}

	inline bool is_normalized(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_NORMALIZED_BIT ? true : false;
	}

	inline bool is_unorm(format Format)
	{
		return is_normalized(Format) && is_unsigned(Format);
	}

	inline bool is_snorm(format Format)
	{
		return is_normalized(Format) && is_signed(Format);
	}

	inline bool is_packed(format Format)
	{
		gli::uint16 flags = detail::get_format_info(Format).Flags;

		return (flags & detail::CAP_PACKED8_BIT) != 0 || (flags & detail::CAP_PACKED16_BIT) != 0 || (flags & detail::CAP_PACKED32_BIT) != 0;
	}

	inline bool is_depth(format Format)
	{
		return (detail::get_format_info(Format).Flags & detail::CAP_DEPTH_BIT) ? true : false;
	}

	inline bool is_stencil(format Format)
	{
		return (detail::get_format_info(Format).Flags & detail::CAP_STENCIL_BIT) ? true : false;
	}

	inline bool is_depth_stencil(format Format)
	{
		return is_depth(Format) && is_stencil(Format);
	}

}//namespace gli
