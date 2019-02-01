#pragma once

#include <chrono>

namespace luanics::utility {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Timer
///
/// @brief Stopwatch-style timer based on std::chrono clocks.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename ClockT = std::chrono::high_resolution_clock>
class Timer {
public:
	using ClockType = ClockT;
	using DurationType = typename ClockT::duration;

	/// start() called on construction
	Timer();

	/// "start" the Timer running from current time
	void start();
	/// @returns time elapsed since start() called
	DurationType elapsed() const;

private:
	using TimeType = typename ClockT::time_point;
	TimeType _start;
}; // class Timer

}  // namespace luanics

#include "luanics/utility/Timer.ipp"
