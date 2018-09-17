#pragma once

#include <iostream>
#include <tuple>

namespace luanics {
namespace tuples {

template <typename ... ParamsT>
void write(
	std::tuple<ParamsT...> const & values,
	std::ostream & out,
	std::string const & delimiter = " "
);

}  // namespace tuples
}  // namespace luanics

namespace std {

template <typename ... ParamsT>
std::ostream & operator<<(std::ostream & out, std::tuple<ParamsT...> const & values);

}

#include "luanics/utility/Tuples.ipp"
