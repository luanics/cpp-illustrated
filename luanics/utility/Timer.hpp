#pragma once

#include "luanics/utility/Duration.hpp"

#include <chrono>

namespace luanics::utility {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Timer
///
/// @brief Stopwatch-style timer based on std::chrono clocks.
///
/// Duration is fixed at nanosecond resolution.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename ClockT = std::chrono::high_resolution_clock>
class Timer {
public:
	/// start() called on construction
	Timer();

	/// "start" the Timer running from current time
	void start();
	/// @returns time elapsed since start() called
	Duration elapsed() const;

private:
	using TimeType = typename ClockT::time_point;
	TimeType _start;
}; // class Timer

}  // namespace luanics

#include "luanics/utility/Timer.ipp"
