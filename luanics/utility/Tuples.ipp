#pragma once

#include "luanics/utility/Tuples.hpp"

namespace luanics {
namespace tuples {

namespace detail {

template <typename TupleT, std::size_t IndexV>
struct Writer {
	static void write(TupleT const & values, std::ostream & out, std::string const & delimiter) {
		out << std::get<std::tuple_size<TupleT>::value - IndexV>(values) << delimiter;
		Writer<TupleT, IndexV - 1>::write(values, out, delimiter);
	}
};

template <typename TupleT>
struct Writer<TupleT, 0> {
	static void write(TupleT const & values, std::ostream & out, std::string const & delimiter) {}
};

}

template <typename ... ParamsT>
void write(std::tuple<ParamsT...> const & values, std::ostream & out, std::string const & delimiter) {
	using TupleType = std::tuple<ParamsT...>;
	detail::Writer<TupleType, std::tuple_size<TupleType>::value>::write(values, out, delimiter);
}

}  // namespace tuples
}  // namespace luanics

namespace std {

template <typename ... ParamsT>
ostream & operator<<(ostream & out, tuple<ParamsT...> const & values) {
	luanics::tuples::write(values, out, ",");
	return out;
}

}
