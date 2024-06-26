import glm;

namespace gli
{
	template <length_t L, typename T, qualifier Q>
	inline T levels(vec<L, T, Q> const& Extent)
	{
		return glm::log2(glm::gtx::compMax(Extent)) + static_cast<T>(1);
	}

	template <typename T>
	inline T levels(T Extent)
	{
		return static_cast<T>(glm::gtx::log2(Extent) + static_cast<size_t>(1));
	}
/*
	inline int levels(int Extent)
	{
		return glm::log2(Extent) + static_cast<int>(1);
	}
*/
}//namespace gli
