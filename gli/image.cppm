/// @brief Include to use images, a representation of a single texture level.
/// @file gli/image.hpp

module;

#include "definitions.hpp"

export module gli:image;

export import :core.storage_linear;
export import :format;

export namespace gli
{
	/// Image, representation for a single texture level
	class image
	{
	private:
		friend class texture1d;
		friend class texture2d;
		friend class texture3d;

	public:
		typedef size_t size_type;
		typedef gli::format format_type;
		typedef storage_linear::extent_type extent_type;
		typedef storage_linear::data_type data_type;

		/// Create an empty image instance
		image();

		/// Create an image object and allocate an image storoge for it.
		explicit image(format_type Format, extent_type const& Extent);

		/// Create an image object by sharing an existing image storage_linear from another image instance.
		/// This image object is effectively an image view where format can be reinterpreted
		/// with a different compatible image format.
		/// For formats to be compatible, the block size of source and destination must match.
		explicit image(image const& Image, format_type Format);

		/// Return whether the image instance is empty, no storage_linear or description have been assigned to the instance.
		bool empty() const;

		/// Return the image instance format.
		format_type format() const;

		/// Return the dimensions of an image instance: width, height and depth.
		extent_type extent() const;

		/// Return the memory size of an image instance storage_linear in bytes.
		size_type size() const;

		/// Return the number of blocks contained in an image instance storage_linear.
		/// genType size must match the block size conresponding to the image format. 
		template <typename genType>
		size_type size() const;

		/// Return a pointer to the beginning of the image instance data.
		void* data();

		/// Return a pointer to the beginning of the image instance data.
		void const* data() const;

		/// Return a pointer of type genType which size must match the image format block size.
		template <typename genType>
		genType* data();

		/// Return a pointer of type genType which size must match the image format block size.
		template <typename genType>
		genType const* data() const;

		/// Clear the entire image storage_linear with zeros
		void clear();

		/// Clear the entire image storage_linear with Texel which type must match the image storage_linear format block size
		/// If the type of genType doesn't match the type of the image format, no conversion is performed and the data will be reinterpreted as if is was of the image format. 
		template <typename genType>
		void clear(genType const& Texel);

		/// Load the texel located at TexelCoord coordinates.
		/// It's an error to call this function if the format is compressed.
		/// It's an error if TexelCoord values aren't between [0, dimensions].
		template <typename genType>
		genType load(extent_type const& TexelCoord);

		/// Store the texel located at TexelCoord coordinates.
		/// It's an error to call this function if the format is compressed.
		/// It's an error if TexelCoord values aren't between [0, dimensions].
		template <typename genType>
		void store(extent_type const& TexelCoord, genType const& Data);

	private:
		/// Create an image object by sharing an existing image storage_linear from another image instance.
		/// This image object is effectively an image view where the layer, the face and the level allows identifying
		/// a specific subset of the image storage_linear source. 
		/// This image object is effectively a image view where the format can be reinterpreted
		/// with a different compatible image format.
		explicit image(
			std::shared_ptr<storage_linear> Storage,
			format_type Format,
			size_type BaseLayer,
			size_type BaseFace,
			size_type BaseLevel);

		std::shared_ptr<storage_linear> Storage;
		format_type const Format;
		size_type const BaseLevel;
		data_type* Data;
		size_type const Size;

		data_type* compute_data(size_type BaseLayer, size_type BaseFace, size_type BaseLevel);
		size_type compute_size(size_type Level) const;
	};
}//namespace gli

namespace gli{
namespace detail
{
	inline size_t texel_linear_addressing
	(
		extent1d const& Extent,
		extent1d const& TexelCoord
	)
	{
		GLI_ASSERT(glm::all(glm::lessThan(TexelCoord, Extent)));

		return static_cast<size_t>(TexelCoord.x);
	}

	inline size_t texel_linear_addressing
	(
		extent2d const& Extent,
		extent2d const& TexelCoord
	)
	{
		GLI_ASSERT(TexelCoord.x < Extent.x);
		GLI_ASSERT(TexelCoord.y < Extent.y);

		return static_cast<size_t>(TexelCoord.x + Extent.x * TexelCoord.y);
	}

	inline size_t texel_linear_addressing
	(
		extent3d const& Extent,
		extent3d const& TexelCoord
	)
	{
		GLI_ASSERT(TexelCoord.x < Extent.x);
		GLI_ASSERT(TexelCoord.y < Extent.y);
		GLI_ASSERT(TexelCoord.z < Extent.z);

		return static_cast<size_t>(TexelCoord.x + Extent.x * (TexelCoord.y + Extent.y * TexelCoord.z));
	}

	inline size_t texel_morton_addressing
	(
		extent1d const& Extent,
		extent1d const& TexelCoord
	)
	{
		GLI_ASSERT(TexelCoord.x < Extent.x);

		return TexelCoord.x;
	}

	inline size_t texel_morton_addressing
	(
		extent2d const& Extent,
		extent2d const& TexelCoord
	)
	{
		GLI_ASSERT(TexelCoord.x < Extent.x && TexelCoord.x >= 0 && TexelCoord.x < std::numeric_limits<extent2d::value_type>::max());
		GLI_ASSERT(TexelCoord.y < Extent.y && TexelCoord.y >= 0 && TexelCoord.y < std::numeric_limits<extent2d::value_type>::max());

		glm::u32vec2 const Input(TexelCoord);

		return static_cast<size_t>(glm::gtc::bitfieldInterleave(Input.x, Input.y));
	}

	inline size_t texel_morton_addressing
	(
		extent3d const& Extent,
		extent3d const& TexelCoord
	)
	{
		GLI_ASSERT(TexelCoord.x < Extent.x);
		GLI_ASSERT(TexelCoord.y < Extent.y);
		GLI_ASSERT(TexelCoord.z < Extent.z);

		glm::u32vec3 const Input(TexelCoord);

		return static_cast<size_t>(glm::gtc::bitfieldInterleave(Input.x, Input.y, Input.z));
	}
}//namespace detail
}

export namespace gli{
	inline image::image()
		: Format(gli::FORMAT_UNDEFINED)
		, BaseLevel(0)
		, Data(nullptr)
		, Size(0)
	{}

	inline image::image
	(
		format_type Format,
		extent_type const& Extent
	)
		: Storage(std::make_shared<storage_linear>(Format, Extent, 1, 1, 1))
		, Format(Format)
		, BaseLevel(0)
		, Data(Storage->data())
		, Size(compute_size(0))
	{}

	inline image::image
	(
		std::shared_ptr<storage_linear> Storage,
		format_type Format,
		size_type BaseLayer,
		size_type BaseFace,
		size_type BaseLevel
	)
		: Storage(Storage)
		, Format(Format)
		, BaseLevel(BaseLevel)
		, Data(compute_data(BaseLayer, BaseFace, BaseLevel))
		, Size(compute_size(BaseLevel))
	{}

	inline image::image
	(
		image const & Image,
		format_type Format
	)
		: Storage(Image.Storage)
		, Format(Format)
		, BaseLevel(Image.BaseLevel)
		, Data(Image.Data)
		, Size(Image.Size)
	{
		GLI_ASSERT(block_size(Format) == block_size(Image.format()));
	}

	inline bool image::empty() const
	{
		if(this->Storage.get() == nullptr)
			return true;

		return this->Storage->empty();
	}

	inline image::size_type image::size() const
	{
		GLI_ASSERT(!this->empty());

		return this->Size;
	}

	template <typename genType>
	inline image::size_type image::size() const
	{
		GLI_ASSERT(sizeof(genType) <= this->Storage->block_size());

		return this->size() / sizeof(genType);
	}

	inline image::format_type image::format() const
	{
		return this->Format;
	}

	inline image::extent_type image::extent() const
	{
		GLI_ASSERT(!this->empty());

		storage_linear::extent_type const& SrcExtent = this->Storage->extent(this->BaseLevel);
		storage_linear::extent_type const& DstExtent = SrcExtent * block_extent(this->format()) / this->Storage->block_extent();

		return glm::max(DstExtent, storage_linear::extent_type(1));
	}

	inline void* image::data()
	{
		GLI_ASSERT(!this->empty());

		return this->Data;
	}

	inline void const* image::data() const
	{
		GLI_ASSERT(!this->empty());

		return this->Data;
	}

	template <typename genType>
	inline genType* image::data()
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(this->Storage->block_size() >= sizeof(genType));

		return reinterpret_cast<genType *>(this->data());
	}

	template <typename genType>
	inline genType const* image::data() const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(this->Storage->block_size() >= sizeof(genType));

		return reinterpret_cast<genType const *>(this->data());
	}

	inline void image::clear()
	{
		GLI_ASSERT(!this->empty());

		memset(this->data<gli::byte>(), 0, this->size<gli::byte>());
	}

	template <typename genType>
	inline void image::clear(genType const& Texel)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(this->Storage->block_size() == sizeof(genType));

		for(size_type TexelIndex = 0; TexelIndex < this->size<genType>(); ++TexelIndex)
			*(this->data<genType>() + TexelIndex) = Texel;
	}

	inline image::data_type* image::compute_data(size_type BaseLayer, size_type BaseFace, size_type BaseLevel)
	{
		size_type const BaseOffset = this->Storage->base_offset(BaseLayer, BaseFace, BaseLevel);

		return this->Storage->data() + BaseOffset;
	}

	inline image::size_type image::compute_size(size_type Level) const
	{
		GLI_ASSERT(!this->empty());

		return this->Storage->level_size(Level);
	}

	template <typename genType>
	genType image::load(extent_type const& TexelCoord)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(this->Storage->block_size() == sizeof(genType));
		GLI_ASSERT(glm::all(glm::lessThan(TexelCoord, this->extent())));

		return *(this->data<genType>() + detail::texel_linear_addressing(this->extent(), TexelCoord));
	}

	template <typename genType>
	void image::store(extent_type const& TexelCoord, genType const& Data)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(this->Storage->block_size() == sizeof(genType));
		GLI_ASSERT(glm::all(glm::lessThan(TexelCoord, this->extent())));

		*(this->data<genType>() + detail::texel_linear_addressing(this->extent(), TexelCoord)) = Data;
	}
}//namespace gli
