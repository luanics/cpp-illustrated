#include "luanics/benchmarking/Showdown.hpp"

namespace luanics::benchmarking {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//	Showdown
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::Showdown(
	ChallengerT challenger,
	DefenderT defender,
	std::size_t const numTrials,
	std::size_t const numIterationsPerTrial,
	bool const isNarrating
) :
	_challenger{challenger, numTrials, numIterationsPerTrial, isNarrating},
	_defender{defender, numTrials, numIterationsPerTrial, isNarrating}
{
	determineWinner();
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
std::size_t Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::numTrials() const {
	return _challenger.numTrials();
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
std::size_t Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::numIterationsPerTrial() const {
	return _challenger.numIterationsPerTrial();
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
Winner Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::winner() const {
	return _winner;
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
typename Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::StatisticsType const & Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::challengerResults() const {
	return _challenger.results();
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
typename Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::StatisticsType const & Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::defenderResults() const {
	return _defender.results();
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
void Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::reportTo(std::ostream & out) const {
	out << "Showdown Results" << std::endl;
	out << "\tChallenger:" << std::endl;
	out << "\t";
	_challenger.reportTo(out);
	out << std::endl;
	out << "\tDefender:  " << std::endl;
	out << "\t";
	_defender.reportTo(out);
	out << std::endl;
	out << "\tWinner:    " << _winner << std::endl;
}

//*******************************************************************
// Helpers
//*******************************************************************

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
void Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>::determineWinner() {
	// Naive test for winner. For better test, use Welch's t test.
	bool const doesChallengerWin =
		challengerResults().mean() < (defenderResults().mean() - defenderResults().stdDev());
	if (doesChallengerWin) {
		_winner = Winner::CHALLENGER;
		return;
	}
	bool const doesDefenderWin =
		challengerResults().mean() > (defenderResults().mean() + defenderResults().stdDev());
	if (doesDefenderWin) {
		_winner = Winner::DEFENDER;
		return;
	}
	_winner = Winner::TIE;
}

template <typename ChallengerT, typename DefenderT, typename ClockT, template <typename> class StatisticsT>
Showdown<ChallengerT, DefenderT, ClockT, StatisticsT> makeShowdown(
	ChallengerT challenger,
	DefenderT defender,
	std::size_t const numTrials,
	std::size_t const numIterationsPerTrial,
	bool const isNarrating
) {
	return Showdown<ChallengerT, DefenderT, ClockT, StatisticsT>{
		challenger, defender, numTrials, numIterationsPerTrial, isNarrating
	};
}

} // namespace luanics::benchmarking
