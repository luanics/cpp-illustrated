///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file statistics::Concept
///
/// @brief Concepts for statistics implemented using detection idiom.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "luanics/meta/Concepts.hpp"
#include "luanics/meta/Detection.hpp"

#include <type_traits>

namespace luanics::statistics {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class statistics::BasicConcept
///
/// @brief The basics statistics concept (lacking stdDev())
///
/// Requires the following of class T<O> and instance t,
///   where T is the statistics type and O is the observation type.
/// * default constructor - T<O>{}
/// * record method - t.record(O)
/// * count method - t.count()
/// * total method - t.total()
/// * mean method - t.mean()
/// * min method - t.min()
/// * max method - t.max()
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

template <typename T>
using HasRecord_t = decltype(std::declval<T&>().record(std::declval<int>()));

template <typename T>
using HasCount_t = decltype(std::declval<T const &>().count());

template <typename T>
using HasTotal_t = decltype(std::declval<T const &>().total());

template <typename T>
using HasMean_t = decltype(std::declval<T const &>().mean());

template <typename T>
using HasMin_t = decltype(std::declval<T const &>().min());

template <typename T>
using HasMax_t = decltype(std::declval<T const &>().max());

template <template <typename> class StatisticsT, typename ObservationT>
bool constexpr BasicConcept = meta::requires<
	std::is_default_constructible_v<StatisticsT<ObservationT>>,
	IsDetected_v<HasRecord_t, StatisticsT<ObservationT>>,
	IsDetected_v<HasCount_t, StatisticsT<ObservationT>>,
	IsDetected_v<HasMean_t, StatisticsT<ObservationT>>,
	IsDetected_v<HasMin_t, StatisticsT<ObservationT>>,
	IsDetected_v<HasMax_t, StatisticsT<ObservationT>>
>;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class statistics::Concept
///
/// @brief Adds to BasicConcept the requirement of stdDev() method
///
/// Requires the following of class T<O> and instance t:
/// * statistics::BasicConcept<T, O>
/// * standard deviation method - t.stdDev()
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//*********************************************************
// The full Concept adds the requirement of StdDev
//*********************************************************

template <typename T>
using HasStdDev_t = decltype(std::declval<T const &>().stdDev());

template <template <typename> class StatisticsT, typename ObservationT>
bool constexpr Concept = meta::requires<
	BasicConcept<StatisticsT, ObservationT>,
	IsDetected_v<HasStdDev_t, StatisticsT<ObservationT>>
>;

} // namespace luanics::statistics
