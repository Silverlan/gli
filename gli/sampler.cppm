/// @brief Include to use wrap modes and the sampler base class.
/// @file gli/sampler.hpp

module;

export module gli:sampler;

export import :core.filter;
export import :type;

export namespace gli
{
	/// Texture coordinate wrapping mode
	enum wrap
	{
		WRAP_CLAMP_TO_EDGE, WRAP_FIRST = WRAP_CLAMP_TO_EDGE,
		WRAP_CLAMP_TO_BORDER,
		WRAP_REPEAT,
		WRAP_MIRROR_REPEAT,
		WRAP_MIRROR_CLAMP_TO_EDGE,
		WRAP_MIRROR_CLAMP_TO_BORDER, WRAP_LAST = WRAP_MIRROR_CLAMP_TO_BORDER
	};

	enum
	{
		WRAP_COUNT = WRAP_LAST - WRAP_FIRST + 1
	};

	/// Evaluate whether the texture coordinate wrapping mode relies on border color
	inline bool is_border(wrap Wrap)
	{
		return Wrap == WRAP_CLAMP_TO_BORDER || Wrap == WRAP_MIRROR_CLAMP_TO_BORDER;
	}

	/// Genetic sampler class.
	class sampler
	{
	public:
		sampler(wrap Wrap, filter Mip, filter Min);
		virtual ~sampler() = default;

	protected:
		typedef float(*wrap_type)(float const & SamplerCoord);

		wrap_type get_func(wrap WrapMode) const;

		wrap_type Wrap;
		filter Mip;
		filter Min;
	};
}//namespace gli

namespace gli{
namespace detail
{
	template <typename T>
	inline T passThrought(T const & SampleCoord)
	{
		return SampleCoord;
	}
}//namespace detail
}

export namespace gli {
	inline sampler::sampler(wrap Wrap, filter Mip, filter Min)
		: Wrap(get_func(Wrap))
		, Mip(Mip)
		, Min(Min)
	{}

	inline sampler::wrap_type sampler::get_func(wrap WrapMode) const
	{
		static wrap_type Table[] =
		{
			glm::clamp,
			detail::passThrought,
			glm::gtc::repeat,
			glm::gtc::mirrorRepeat,
			glm::gtc::mirrorClamp,
			glm::gtc::mirrorClamp
		};
		static_assert(sizeof(Table) / sizeof(Table[0]) == WRAP_COUNT, "Table needs to be updated");

		return Table[WrapMode];
	}
}//namespace gli
