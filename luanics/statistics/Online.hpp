#pragma once

#include <cstdint>
#include <limits>
#include <optional>

namespace luanics {
namespace statistics {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class statistics::Online
///
/// @brief Gather basic descriptive statistics using *online* algorithm.
///
/// Note that most of the descriptive statistics are not defined for count() == 0.
///  Therefore, count() > 0 is precondition for several methods.
///
/// @see https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename ObservationT>
class Online {
public:
	using ObservationType = ObservationT;

	Online();

	void record(ObservationType const observation);

	std::size_t count() const;     ///< @return number of recorded observations
	ObservationType total() const; ///< @return sum of recorded observations
	ObservationType min() const;   ///< @pre count() > 0
	ObservationType max() const;   ///< @pre count() > 0
	double mean() const;           ///< @pre count() > 0
	double stdDev() const;         ///< @pre count() > 0

private:
	std::size_t _count;
	ObservationT _total;
	ObservationT _min;
	ObservationT _max;
	double _mean;
	double _m2;
};
// class Online

} // namespace statistics
} // namespace luanics

#include "luanics/statistics/Online.ipp"
