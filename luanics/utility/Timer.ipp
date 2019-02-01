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
typename Timer<ClockT>::DurationType Timer<ClockT>::elapsed() const {
	return std::chrono::duration_cast<DurationType>(ClockT::now() - _start);
}

}  // namespace luanics::utility
