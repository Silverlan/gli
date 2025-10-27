/// @brief Include to use generic textures which can represent any texture target but they don't have target specific built-in caches making accesses slower.
/// @file gli/texture.hpp

module;

#include "definitions.hpp"
#include <array>
#include <memory>
#include <vector>
#include <cstring>

export module gli:texture;

export import :core.storage_linear;
export import :format;
export import :target;

export namespace gli
{
	/// Genetic texture class. It can support any target.
	class texture
	{
	public:
		typedef size_t size_type;
		typedef gli::target target_type;
		typedef gli::format format_type;
		typedef gli::swizzles swizzles_type;
		typedef storage_linear storage_type;
		typedef storage_type::data_type data_type;
		typedef storage_type::extent_type extent_type;

		/// Create an empty texture instance
		texture();

		/// Create a texture object and allocate a texture storage for it
		/// @param Target Type/Shape of the texture storage_linear
		/// @param Format Texel format
		/// @param Extent Size of the texture: width, height and depth.
		/// @param Layers Number of one-dimensional or two-dimensional images of identical size and format
		/// @param Faces 6 for cube map textures otherwise 1.
		/// @param Levels Number of images in the texture mipmap chain.
		/// @param Swizzles A mechanism to swizzle the components of a texture before they are applied according to the texture environment.
		texture(
			target_type Target,
			format_type Format,
			extent_type const& Extent,
			size_type Layers,
			size_type Faces,
			size_type Levels,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture object by sharing an existing texture storage_type from another texture instance.
		/// This texture object is effectively a texture view where the layer, the face and the level allows identifying
		/// a specific subset of the texture storage_linear source. 
		/// This texture object is effectively a texture view where the target and format can be reinterpreted
		/// with a different compatible texture target and texture format.
		texture(
			texture const& Texture,
			target_type Target,
			format_type Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		/// Create a texture object by sharing an existing texture storage_type from another texture instance.
		/// This texture object is effectively a texture view where the target and format can be reinterpreted
		/// with a different compatible texture target and texture format.
		texture(
			texture const& Texture,
			target_type Target,
			format_type Format,
			swizzles_type const& Swizzles = swizzles_type(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA));

		virtual ~texture(){}

		/// Return whether the texture instance is empty, no storage_type or description have been assigned to the instance.
		bool empty() const;

		/// Return the target of a texture instance.
		target_type target() const{return this->Target;}

		/// Return the texture instance format
		format_type format() const;

		swizzles_type swizzles() const;

		/// Return the base layer of the texture instance, effectively a memory offset in the actual texture storage_type to identify where to start reading the layers. 
		size_type base_layer() const;

		/// Return the max layer of the texture instance, effectively a memory offset to the beginning of the last layer in the actual texture storage_type that the texture instance can access. 
		size_type max_layer() const;

		/// Return max_layer() - base_layer() + 1
		size_type layers() const;

		/// Return the base face of the texture instance, effectively a memory offset in the actual texture storage_type to identify where to start reading the faces. 
		size_type base_face() const;

		/// Return the max face of the texture instance, effectively a memory offset to the beginning of the last face in the actual texture storage_type that the texture instance can access. 
		size_type max_face() const;

		/// Return max_face() - base_face() + 1
		size_type faces() const;

		/// Return the base level of the texture instance, effectively a memory offset in the actual texture storage_type to identify where to start reading the levels. 
		size_type base_level() const;

		/// Return the max level of the texture instance, effectively a memory offset to the beginning of the last level in the actual texture storage_type that the texture instance can access. 
		size_type max_level() const;

		/// Return max_level() - base_level() + 1.
		size_type levels() const;

		/// Return the size of a texture instance: width, height and depth.
		extent_type extent(size_type Level = 0) const;

		/// Return the memory size of a texture instance storage_type in bytes.
		size_type size() const;

		/// Return the number of blocks contained in a texture instance storage_type.
		/// genType size must match the block size conresponding to the texture format.
		template <typename genType>
		size_type size() const;

		/// Return the memory size of a specific level identified by Level.
		size_type size(size_type Level) const;

		/// Return the memory size of a specific level identified by Level.
		/// genType size must match the block size conresponding to the texture format.
		template <typename gen_type>
		size_type size(size_type Level) const;

		/// Return a pointer to the beginning of the texture instance data.
		void* data();

		/// Return a pointer of type genType which size must match the texture format block size
		template <typename gen_type>
		gen_type* data();

		/// Return a pointer to the beginning of the texture instance data.
		void const* data() const;

		/// Return a pointer of type genType which size must match the texture format block size
		template <typename gen_type>
		gen_type const* data() const;

		/// Return a pointer to the beginning of the texture instance data.
		void* data(size_type Layer, size_type Face, size_type Level);

		/// Return a pointer to the beginning of the texture instance data.
		void const* const data(size_type Layer, size_type Face, size_type Level) const;

		/// Return a pointer of type genType which size must match the texture format block size
		template <typename gen_type>
		gen_type* data(size_type Layer, size_type Face, size_type Level);

		/// Return a pointer of type genType which size must match the texture format block size
		template <typename gen_type>
		gen_type const* const data(size_type Layer, size_type Face, size_type Level) const;

		/// Clear the entire texture storage_linear with zeros
		void clear();

		/// Clear the entire texture storage_linear with Texel which type must match the texture storage_linear format block size
		/// If the type of gen_type doesn't match the type of the texture format, no conversion is performed and the data will be reinterpreted as if is was of the texture format. 
		template <typename gen_type>
		void clear(gen_type const& Texel);

		/// Clear a specific image of a texture.
		template <typename gen_type>
		void clear(size_type Layer, size_type Face, size_type Level, gen_type const& BlockData);

		/// Clear a subset of a specific image of a texture.
		template <typename gen_type>
		void clear(size_type Layer, size_type Face, size_type Level, extent_type const& TexelOffset, extent_type const& TexelExtent, gen_type const& BlockData);

		/// Copy a specific image of a texture 
		void copy(
			texture const& TextureSrc,
			size_t LayerSrc, size_t FaceSrc, size_t LevelSrc,
			size_t LayerDst, size_t FaceDst, size_t LevelDst);

		/// Copy a subset of a specific image of a texture 
		void copy(
			texture const& TextureSrc,
			size_t LayerSrc, size_t FaceSrc, size_t LevelSrc, extent_type const& OffsetSrc,
			size_t LayerDst, size_t FaceDst, size_t LevelDst, extent_type const& OffsetDst,
			extent_type const& Extent);

		/// Reorder the component in texture memory.
		template <typename gen_type>
		void swizzle(gli::swizzles const& Swizzles);

		/// Fetch a texel from a texture. The texture format must be uncompressed.
		template <typename gen_type>
		gen_type load(extent_type const & TexelCoord, size_type Layer, size_type Face, size_type Level) const;

		/// Write a texel to a texture. The texture format must be uncompressed.
		template <typename gen_type>
		void store(extent_type const& TexelCoord, size_type Layer, size_type Face, size_type Level, gen_type const& Texel);

	protected:
		std::shared_ptr<storage_type> Storage;
		target_type Target;
		format_type Format;
		size_type BaseLayer;
		size_type MaxLayer;
		size_type BaseFace;
		size_type MaxFace;
		size_type BaseLevel;
		size_type MaxLevel;
		swizzles_type Swizzles;

		// Pre compute at texture instance creation some information for faster access to texels
		struct cache
		{
		public:
			enum ctor
			{
				DEFAULT
			};

			explicit cache(ctor)
			{}

			cache
			(
				storage_type& Storage,
				format_type Format,
				size_type BaseLayer, size_type Layers,
				size_type BaseFace, size_type MaxFace,
				size_type BaseLevel, size_type MaxLevel
			)
				: Faces(MaxFace - BaseFace + 1)
				, Levels(MaxLevel - BaseLevel + 1)
			{
				GLI_ASSERT(static_cast<size_t>(gli::levels(Storage.extent(0))) < this->ImageMemorySize.size());

				this->BaseAddresses.resize(Layers * this->Faces * this->Levels);

				for(size_type Layer = 0; Layer < Layers; ++Layer)
				for(size_type Face = 0; Face < this->Faces; ++Face)
				for(size_type Level = 0; Level < this->Levels; ++Level)
				{
					size_type const Index = index_cache(Layer, Face, Level);
					this->BaseAddresses[Index] = Storage.data() + Storage.base_offset(
						BaseLayer + Layer, BaseFace + Face, BaseLevel + Level);
				}

				for(size_type Level = 0; Level < this->Levels; ++Level)
				{
					extent_type const& SrcExtent = Storage.extent(BaseLevel + Level);
					extent_type const& DstExtent = SrcExtent * block_extent(Format) / Storage.block_extent();

					this->ImageExtent[Level] = glm::max(DstExtent, extent_type(1));
					this->ImageMemorySize[Level] = Storage.level_size(BaseLevel + Level);
				}
				
				this->GlobalMemorySize = Storage.layer_size(BaseFace, MaxFace, BaseLevel, MaxLevel) * Layers;
			}

			// Base addresses of each images of a texture.
			data_type* get_base_address(size_type Layer, size_type Face, size_type Level) const
			{
				return this->BaseAddresses[index_cache(Layer, Face, Level)];
			}

			// In texels
			extent_type get_extent(size_type Level) const
			{
				return this->ImageExtent[Level];
			};

			// In bytes
			size_type get_memory_size(size_type Level) const
			{
				return this->ImageMemorySize[Level];
			};

			// In bytes
			size_type get_memory_size() const
			{
				return this->GlobalMemorySize;
			};

		private:
			size_type index_cache(size_type Layer, size_type Face, size_type Level) const
			{
				return ((Layer * this->Faces) + Face) * this->Levels + Level;
			}

			size_type Faces;
			size_type Levels;
			std::vector<data_type*> BaseAddresses;
			std::array<extent_type, 16> ImageExtent;
			std::array<size_type, 16> ImageMemorySize;
			size_type GlobalMemorySize;
		} Cache;
	};
}//namespace gli

export namespace gli
{
	inline texture::texture()
		: Storage(nullptr)
		, Target(static_cast<gli::target>(TARGET_INVALID))
		, Format(gli::FORMAT_UNDEFINED)
		, BaseLayer(0), MaxLayer(0)
		, BaseFace(0), MaxFace(0)
		, BaseLevel(0), MaxLevel(0)
		, Swizzles(SWIZZLE_ZERO)
		, Cache(cache::DEFAULT)
	{}

	inline texture::texture
	(
		target_type Target,
		format_type Format,
		extent_type const& Extent,
		size_type Layers,
		size_type Faces,
		size_type Levels,
		swizzles_type const& Swizzles
	)
		: Storage(std::make_shared<storage_type>(Format, Extent, Layers, Faces, Levels))
		, Target(Target)
		, Format(Format)
		, BaseLayer(0), MaxLayer(Layers - 1)
		, BaseFace(0), MaxFace(Faces - 1)
		, BaseLevel(0), MaxLevel(Levels - 1)
		, Swizzles(Swizzles)
		, Cache(*Storage, Format, this->base_layer(), this->layers(), this->base_face(), this->max_face(), this->base_level(), this->max_level())
	{
		GLI_ASSERT(Target != TARGET_CUBE || (Target == TARGET_CUBE && Extent.x == Extent.y));
		GLI_ASSERT(Target != TARGET_CUBE_ARRAY || (Target == TARGET_CUBE_ARRAY && Extent.x == Extent.y));
	}

	inline texture::texture
	(
		texture const& Texture,
		target_type Target,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: Storage(Texture.Storage)
		, Target(Target)
		, Format(Format)
		, BaseLayer(BaseLayer), MaxLayer(MaxLayer)
		, BaseFace(BaseFace), MaxFace(MaxFace)
		, BaseLevel(BaseLevel), MaxLevel(MaxLevel)
		, Swizzles(Swizzles)
		, Cache(*Storage, Format, this->base_layer(), this->layers(), this->base_face(), this->max_face(), this->base_level(), this->max_level())
	{
		GLI_ASSERT(block_size(Format) == block_size(Texture.format()));
		GLI_ASSERT(Target != TARGET_1D || (Target == TARGET_1D && this->layers() == 1 && this->faces() == 1 && this->extent().y == 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_1D_ARRAY || (Target == TARGET_1D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->extent().y == 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_2D || (Target == TARGET_2D && this->layers() == 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_2D_ARRAY || (Target == TARGET_2D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_3D || (Target == TARGET_3D && this->layers() == 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z >= 1));
		GLI_ASSERT(Target != TARGET_CUBE || (Target == TARGET_CUBE && this->layers() == 1 && this->faces() >= 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_CUBE_ARRAY || (Target == TARGET_CUBE_ARRAY && this->layers() >= 1 && this->faces() >= 1 && this->extent().y >= 1 && this->extent().z == 1));
	}

	inline texture::texture
	(
		texture const& Texture,
		target_type Target,
		format_type Format,
		swizzles_type const& Swizzles
	)
		: Storage(Texture.Storage)
		, Target(Target)
		, Format(Format)
		, BaseLayer(Texture.base_layer()), MaxLayer(Texture.max_layer())
		, BaseFace(Texture.base_face()), MaxFace(Texture.max_face())
		, BaseLevel(Texture.base_level()), MaxLevel(Texture.max_level())
		, Swizzles(Swizzles)
		, Cache(*Storage, Format, this->base_layer(), this->layers(), this->base_face(), this->max_face(), this->base_level(), this->max_level())
	{
		if(this->empty())
			return;

		GLI_ASSERT(Target != TARGET_1D || (Target == TARGET_1D && this->layers() == 1 && this->faces() == 1 && this->extent().y == 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_1D_ARRAY || (Target == TARGET_1D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->extent().y == 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_2D || (Target == TARGET_2D && this->layers() == 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_2D_ARRAY || (Target == TARGET_2D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_3D || (Target == TARGET_3D && this->layers() == 1 && this->faces() == 1 && this->extent().y >= 1 && this->extent().z >= 1));
		GLI_ASSERT(Target != TARGET_CUBE || (Target == TARGET_CUBE && this->layers() == 1 && this->faces() >= 1 && this->extent().y >= 1 && this->extent().z == 1));
		GLI_ASSERT(Target != TARGET_CUBE_ARRAY || (Target == TARGET_CUBE_ARRAY && this->layers() >= 1 && this->faces() >= 1 && this->extent().y >= 1 && this->extent().z == 1));
	}

	inline bool texture::empty() const
	{
		if(this->Storage.get() == nullptr)
			return true;

		return this->Storage->empty();
	}

	inline texture::format_type texture::format() const
	{
		return this->Format;
	}

	inline texture::swizzles_type texture::swizzles() const
	{
		swizzles_type const FormatSwizzle = detail::get_format_info(this->format()).Swizzles;
		swizzles_type const CustomSwizzle = this->Swizzles;

		swizzles_type ResultSwizzle(SWIZZLE_ZERO);
		ResultSwizzle.r = is_channel(CustomSwizzle.r) ? FormatSwizzle[CustomSwizzle.r] : CustomSwizzle.r;
		ResultSwizzle.g = is_channel(CustomSwizzle.g) ? FormatSwizzle[CustomSwizzle.g] : CustomSwizzle.g;
		ResultSwizzle.b = is_channel(CustomSwizzle.b) ? FormatSwizzle[CustomSwizzle.b] : CustomSwizzle.b;
		ResultSwizzle.a = is_channel(CustomSwizzle.a) ? FormatSwizzle[CustomSwizzle.a] : CustomSwizzle.a;
		return ResultSwizzle;
	}

	inline texture::size_type texture::base_layer() const
	{
		return this->BaseLayer;
	}

	inline texture::size_type texture::max_layer() const
	{
		return this->MaxLayer;
	}

	inline texture::size_type texture::layers() const
	{
		if(this->empty())
			return 0;
		return this->max_layer() - this->base_layer() + 1;
	}

	inline texture::size_type texture::base_face() const
	{
		return this->BaseFace;
	}

	inline texture::size_type texture::max_face() const
	{
		return this->MaxFace;
	}

	inline texture::size_type texture::faces() const
	{
		if(this->empty())
			return 0;
		return this->max_face() - this->base_face() + 1;
	}

	inline texture::size_type texture::base_level() const
	{
		return this->BaseLevel;
	}

	inline texture::size_type texture::max_level() const
	{
		return this->MaxLevel;
	}

	inline texture::size_type texture::levels() const
	{
		if(this->empty())
			return 0;
		return this->max_level() - this->base_level() + 1;
	}

	inline texture::size_type texture::size() const
	{
		GLI_ASSERT(!this->empty());

		return this->Cache.get_memory_size();
	}

	template <typename gen_type>
	inline texture::size_type texture::size() const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));

		return this->size() / sizeof(gen_type);
	}

	inline texture::size_type texture::size(size_type Level) const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(Level >= 0 && Level < this->levels());

		return this->Cache.get_memory_size(Level);
	}

	template <typename gen_type>
	inline texture::size_type texture::size(size_type Level) const
	{
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));

		return this->size(Level) / sizeof(gen_type);
	}

	inline void* texture::data()
	{
		GLI_ASSERT(!this->empty());

		return this->Cache.get_base_address(0, 0, 0);
	}

	inline void const* texture::data() const
	{
		GLI_ASSERT(!this->empty());

		return this->Cache.get_base_address(0, 0, 0);
	}

	template <typename gen_type>
	inline gen_type* texture::data()
	{
		GLI_ASSERT(block_size(this->format()) >= sizeof(gen_type));

		return reinterpret_cast<gen_type*>(this->data());
	}

	template <typename gen_type>
	inline gen_type const* texture::data() const
	{
		GLI_ASSERT(block_size(this->format()) >= sizeof(gen_type));

		return reinterpret_cast<gen_type const*>(this->data());
	}

	inline void* texture::data(size_type Layer, size_type Face, size_type Level)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(Layer >= 0 && Layer < this->layers() && Face >= 0 && Face < this->faces() && Level >= 0 && Level < this->levels());

		return this->Cache.get_base_address(Layer, Face, Level);
	}

	inline void const* const texture::data(size_type Layer, size_type Face, size_type Level) const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(Layer >= 0 && Layer < this->layers() && Face >= 0 && Face < this->faces() && Level >= 0 && Level < this->levels());

		return this->Cache.get_base_address(Layer, Face, Level);
	}

	template <typename gen_type>
	inline gen_type* texture::data(size_type Layer, size_type Face, size_type Level)
	{
		GLI_ASSERT(block_size(this->format()) >= sizeof(gen_type));

		return reinterpret_cast<gen_type*>(this->data(Layer, Face, Level));
	}

	template <typename gen_type>
	inline gen_type const* const texture::data(size_type Layer, size_type Face, size_type Level) const
	{
		GLI_ASSERT(block_size(this->format()) >= sizeof(gen_type));

		return reinterpret_cast<gen_type const* const>(this->data(Layer, Face, Level));
	}

	inline texture::extent_type texture::extent(size_type Level) const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(Level >= 0 && Level < this->levels());

		return this->Cache.get_extent(Level);
	}

	inline void texture::clear()
	{
		GLI_ASSERT(!this->empty());

		memset(this->data(), 0, this->size());
	}

	template <typename gen_type>
	inline void texture::clear(gen_type const& Texel)
	{
		GLI_ASSERT(!gli::is_compressed(this->format()));
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));

		gen_type* Data = this->data<gen_type>();
		size_type const BlockCount = this->size<gen_type>();

		for(size_type BlockIndex = 0; BlockIndex < BlockCount; ++BlockIndex)
			*(Data + BlockIndex) = Texel;
	}

	template <typename gen_type>
	inline void texture::clear(size_type Layer, size_type Face, size_type Level, gen_type const& BlockData)
	{
		GLI_ASSERT(!gli::is_compressed(this->format()));
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));
		GLI_ASSERT(Layer >= 0 && Layer < this->layers() && Face >= 0 && Face < this->faces() && Level >= 0 && Level < this->levels());

		size_type const BlockCount = this->Storage->level_size(Level) / sizeof(gen_type);
		gen_type* Data = this->data<gen_type>(Layer, Face, Level);
		for(size_type BlockIndex = 0; BlockIndex < BlockCount; ++BlockIndex)
			*(Data + BlockIndex) = BlockData;
	}

	template <typename gen_type>
	inline void texture::clear
	(
		size_type Layer, size_type Face, size_type Level,
		extent_type const& TexelOffset, extent_type const& TexelExtent,
		gen_type const& BlockData
	)
	{
		storage_type::size_type const BaseOffset = this->Storage->base_offset(Layer, Face, Level);
		storage_type::data_type* const BaseAddress = this->Storage->data() + BaseOffset;

		extent_type BlockOffset(TexelOffset / this->Storage->block_extent());
		extent_type const BlockExtent(TexelExtent / this->Storage->block_extent() + BlockOffset);
		for(; BlockOffset.z < BlockExtent.z; ++BlockOffset.z)
		for(; BlockOffset.y < BlockExtent.y; ++BlockOffset.y)
		for(; BlockOffset.x < BlockExtent.x; ++BlockOffset.x)
		{
			gli::size_t const Offset = this->Storage->image_offset(BlockOffset, this->extent(Level)) * this->Storage->block_size();
			gen_type* const BlockAddress = reinterpret_cast<gen_type* const>(BaseAddress + Offset);
			*BlockAddress = BlockData;
		}
	}

	inline void texture::copy
	(
		texture const& TextureSrc,
		size_t LayerSrc, size_t FaceSrc, size_t LevelSrc,
		size_t LayerDst, size_t FaceDst, size_t LevelDst
	)
	{
		GLI_ASSERT(this->size(LevelDst) == TextureSrc.size(LevelSrc));
		GLI_ASSERT(LayerSrc < TextureSrc.layers());
		GLI_ASSERT(LayerDst < this->layers());
		GLI_ASSERT(FaceSrc < TextureSrc.faces());
		GLI_ASSERT(FaceDst < this->faces());
		GLI_ASSERT(LevelSrc < TextureSrc.levels());
		GLI_ASSERT(LevelDst < this->levels());

		memcpy(
			this->data(LayerDst, FaceDst, LevelDst),
			TextureSrc.data(LayerSrc, FaceSrc, LevelSrc),
			this->size(LevelDst));
	}

	inline void texture::copy
	(
		texture const& TextureSrc,
		size_t LayerSrc, size_t FaceSrc, size_t LevelSrc, texture::extent_type const& OffsetSrc,
		size_t LayerDst, size_t FaceDst, size_t LevelDst, texture::extent_type const& OffsetDst,
		texture::extent_type const& Extent
	)
	{
		storage_type::extent_type const BlockExtent = this->Storage->block_extent();
		this->Storage->copy(
			*TextureSrc.Storage,
			LayerSrc, FaceSrc, LevelSrc, OffsetSrc / BlockExtent,
			LayerDst, FaceDst, LevelDst, OffsetDst / BlockExtent,
			Extent / BlockExtent);
	}

	template <typename gen_type>
	inline void texture::swizzle(gli::swizzles const& Swizzles)
	{
		for(size_type TexelIndex = 0, TexelCount = this->size<gen_type>(); TexelIndex < TexelCount; ++TexelIndex)
		{
			gen_type& TexelDst = *(this->data<gen_type>() + TexelIndex);
			gen_type const TexelSrc = TexelDst;
			for(typename gen_type::length_type Component = 0; Component < TexelDst.length(); ++Component)
			{
				GLI_ASSERT(static_cast<typename gen_type::length_type>(Swizzles[Component]) < TexelDst.length());
				TexelDst[Component] = TexelSrc[Swizzles[Component]];
			}
		}
	}

	template <typename gen_type>
	inline gen_type texture::load(extent_type const& TexelCoord, size_type Layer,  size_type Face, size_type Level) const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));

		size_type const ImageOffset = this->Storage->image_offset(TexelCoord, this->extent(Level));
		GLI_ASSERT(ImageOffset < this->size<gen_type>(Level));

		return *(this->data<gen_type>(Layer, Face, Level) + ImageOffset);
	}

	template <typename gen_type>
	inline void texture::store(extent_type const& TexelCoord, size_type Layer,  size_type Face, size_type Level, gen_type const& Texel)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));
		GLI_ASSERT(glm::all(glm::lessThan(TexelCoord, this->extent(Level))));

		size_type const ImageOffset = this->Storage->image_offset(TexelCoord, this->extent(Level));
		GLI_ASSERT(ImageOffset < this->size<gen_type>(Level));

		*(this->data<gen_type>(Layer, Face, Level) + ImageOffset) = Texel;
	}
}//namespace gli

