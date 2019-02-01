#include "luanics/benchmarking/Benchmarker.hpp"

#include <iostream>

namespace luanics::benchmarking {

template <typename FunctionT, typename ClockT, template <typename> class StatisticsT>
Benchmarker<FunctionT, ClockT, StatisticsT>::Benchmarker(
	FunctionT subject,
	std::size_t const numTrials,
	std::size_t const numIterationsPerTrial,
	bool const isPrintingDiagnostics
) :
	_timer{},
	_statistics{},
	_subject{subject},
	_numTrials{numTrials},
	_numIterationsPerTrial{numIterationsPerTrial},
	_isPrintingDiagnostics{isPrintingDiagnostics}
{
	if (_isPrintingDiagnostics) std::cout << "Benchmarking: Trial ";
	for (std::size_t trial = 0; trial < _numTrials; ++trial) {
		if (_isPrintingDiagnostics) std::cout << trial << " ";
		_timer.start();
		for (std::size_t iteration = 0; iteration < _numIterationsPerTrial; ++iteration) {
			_subject();
		}
		_statistics.record(_timer.elapsed().count());
	}
	if (_isPrintingDiagnostics) std::cout << "Finished" << std::endl;
}

template <typename FunctionT, typename ClockT, template <typename> class StatisticsT>
std::size_t Benchmarker<FunctionT, ClockT, StatisticsT>::numTrials() const {
	return _numTrials;
}

template <typename FunctionT, typename ClockT, template <typename> class StatisticsT>
std::size_t Benchmarker<FunctionT, ClockT, StatisticsT>::numIterationsPerTrial() const {
	return _numIterationsPerTrial;
}

template <typename FunctionT, typename ClockT, template <typename> class StatisticsT>
typename Benchmarker<FunctionT, ClockT, StatisticsT>::StatisticsType const & Benchmarker<FunctionT, ClockT, StatisticsT>::results() const {
	return _statistics;
}

template <typename FunctionT, typename ClockT, template <typename> class StatisticsT>
void Benchmarker<FunctionT, ClockT, StatisticsT>::reportTo(std::ostream & out) const {

}

} // namespace luanics::benchmarking
