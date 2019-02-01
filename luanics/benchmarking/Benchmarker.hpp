#pragma once

#include "luanics/statistics/Concepts.hpp"
#include "luanics/statistics/Online.hpp"
#include "luanics/utility/Timer.hpp"

#include <cstdint>
#include <iosfwd>

namespace luanics::benchmarking {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Benchmarker
///
/// @brief One-shot benchmarker that is launched on construction.
///
/// @tparam FunctionT is the function being benchmarked.
/// @tparam ClockT is the clock used for timing.
/// @tparam StatisticsT is a statistics-concept-conforming class.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <
	typename FunctionT,
	typename ClockT = std::chrono::high_resolution_clock,
	template <typename> class StatisticsT = statistics::Online
>
class Benchmarker {
public:
	using TimerType = utility::Timer<ClockT>;
	using DurationType = typename TimerType::DurationType;
	using ObservationType = typename DurationType::rep;
	static_assert(statistics::Concept<StatisticsT, ObservationType>);
	using StatisticsType = StatisticsT<ObservationType>;

	Benchmarker(
		FunctionT subject,
		std::size_t const numTrials = 10,
		std::size_t const numIterationsPerTrial = 100,
		bool const isPrintingDiagnostics = true
	);

	std::size_t numTrials() const;
	std::size_t numIterationsPerTrial() const;
	StatisticsType const & results() const;

	void reportTo(std::ostream & out) const;

private:
	TimerType _timer;
	StatisticsType _statistics;
	FunctionT _subject;
	std::size_t _numTrials;
	std::size_t _numIterationsPerTrial;
	bool _isPrintingDiagnostics;
}; // class Benchmarker

} // namespace luanics::benchmarking

#include "luanics/benchmarking/Benchmarker.ipp"
