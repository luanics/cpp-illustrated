#pragma once

#include "luanics/utility/Timer.hpp"

namespace luanics::utility {

template <typename ClockT>
Timer<ClockT>::Timer() {
	start();
}

template <typename ClockT>
void Timer<ClockT>::start() {
	_start = ClockT::now();
}

template <typename ClockT>
Duration Timer<ClockT>::elapsed() const {
	return std::chrono::duration_cast<Duration>(ClockT::now() - _start);
}

}  // namespace luanics::utility
