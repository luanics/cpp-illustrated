#pragma once

#include <iostream>

namespace luanics {
namespace benchmarking {

enum class Winner {
	CHALLENGER,
	DEFENDER,
	TIE
};

std::ostream & operator<<(std::ostream & out, Winner const winner);

} // namespace benchmarking
} // namespace luanics
