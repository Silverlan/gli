import glm;

namespace gli{
namespace detail
{
	template <typename T>
	inline T passThrought(T const & SampleCoord)
	{
		return SampleCoord;
	}
}//namespace detail

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
