#pragma once

#include <chrono>

namespace luanics {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class ManualClock
///
/// @brief For testing, conforms to Clock concept and allows manual time control.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <typename DurationT = std::chrono::nanoseconds>
struct ManualClock {
	using duration = DurationT;
	using rep = typename duration::rep;
	using period = typename duration::period;
	using time_point = std::chrono::time_point<ManualClock, duration>;

	static_assert(ManualClock::duration::min() < ManualClock::duration::zero(),
	    "a clock's minimum duration cannot be less than its epoch");

	static constexpr bool is_steady = true;
	static time_point now() noexcept {return _current;}
	static void setNowInNanos(size_t const nanos) {_current = timePointFromNanos(nanos);}

private:
	static time_point timePointFromNanos(size_t const nanos) {
		return time_point(std::chrono::nanoseconds(nanos));
	}
	static time_point _current;
};

template <typename DurationT>
typename ManualClock<DurationT>::time_point ManualClock<DurationT>::_current;

}  // namespace luanics
