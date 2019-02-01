#pragma once

#include "luanics/benchmarking/Benchmarker.hpp"
#include "luanics/benchmarking/Winner.hpp"
#include "luanics/statistics/Online.hpp"

namespace luanics::benchmarking {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Showdown
///
/// @brief Benchmarking showdown between challenger and defender,
///   launched on construction.
///
/// Winner is declared if one of the benchmark median times is
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <
	typename ChallengerT,
	typename DefenderT,
	typename ClockT = std::chrono::high_resolution_clock,
	template <typename> class StatisticsT = statistics::Online
>
class Showdown {
public:
	using TimerType = utility::Timer<ClockT>;
	using DurationType = typename TimerType::DurationType;
	using ObservationType = typename DurationType::rep;
	using StatisticsType = StatisticsT<ObservationType>;

	Showdown(
		ChallengerT challenger,
		DefenderT defender,
		std::size_t const numTrials,
		std::size_t const numIerationsPerTrial,
		bool const isPrintingDiagnostics
	);

	std::size_t numTrials() const;
	std::size_t numIterationsPerTrial() const;
	Winner winner() const;
	StatisticsType const & challengerResults() const;
	StatisticsType const & defenderResults() const;

	void reportTo(std::ostream & out) const;

private:
	void determineWinner();

	Benchmarker<ChallengerT, ClockT, StatisticsT> _challenger;
	Benchmarker<DefenderT, ClockT, StatisticsT> _defender;
	Winner _winner;
}; // class Showdown

} // namespace luanics::benchmarking

#include "luanics/benchmarking/Showdown.ipp"
