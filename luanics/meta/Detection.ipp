#pragma once

#include <type_traits>

namespace luanics::detail {

// Primary template - fallback handles case where OpT<ArgsT...> not valid
template<
	typename DummyT,// placeholder for void_t in specializations
	template <typename ...> typename OpT,
	typename ... ArgsT
>
struct Detector {
	constexpr static bool value = false;
	using type = void;
};

// Specialization for cases where OpT<ArgsT...> valid
template<
	template<typename ...> class OpT,
	typename ... ArgsT
>
struct Detector<std::void_t<OpT<ArgsT...>>, OpT, ArgsT...> {
	constexpr static bool value = true;
	using type = OpT<ArgsT...>;
};

} // namespace luanics::detail
