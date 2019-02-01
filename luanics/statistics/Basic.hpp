#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>

namespace luanics::statistics {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class statistics::Basic
///
/// @brief Basic statistics including only count and total.
///
/// @tparam ObservationT The type of the recorded quantities.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <typename ObservationT>
class Basic {
public:
	using ObservationType = ObservationT;

	Basic();

	void record(ObservationType observation);

	std::size_t count() const;
	ObservationType total() const;
	double mean() const;
	ObservationType min() const;
	ObservationType max() const;

private:
	std::size_t _count;
	ObservationType _total;
	ObservationType _min;
	ObservationType _max;
}; // class Basic

} // namespace luanics::statistics

#include "luanics/statistics/Basic.ipp"
