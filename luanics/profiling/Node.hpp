#pragma once

#include "luanics/statistics/Basic.hpp"
#include "luanics/statistics/Concepts.hpp"

#include <map>
#include <string>
#include <unordered_map>

namespace luanics::profiling {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Node
///
/// @brief Node in the profiling system.
///
/// @tparam ClockT must meet the Standard's Clock requirements [time.clock.req]
/// @tparam StatisticsT must meet our Statistics requirements.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <
	typename ClockT,
	template <typename> typename StatisticsT
>
class Node {
public:
	using TimeType = typename ClockT::time_point;
	using TickType = typename ClockT::rep;
	static_assert(statistics::BasicConcept<StatisticsT, TickType>);
	using StatisticsType = StatisticsT<TickType>;
	using NameType = char const *;
	using ChildMapType = std::map<NameType, Node>;

	Node(Node * parent) :
		_parent{parent},
		_start{},
		_stats{},
		_children{}
	{}

//	Node(Node const & other) = default;
//	Node & operator=(Node const & other) = default;
//	Node(Node && other) = default;
//	Node & operator=(Node && other) = default;

	StatisticsType const & stats() const {return _stats;}

	void start() {
		_start = ClockT::now();
	}

	void stop() {
		auto const elapsed = ClockT::now() - _start;
		_stats.record(elapsed.count());
	}

	Node * child(NameType const & name) {
		auto itrBoolPair = _children.emplace(name, this);
		return &(itrBoolPair.first->second);
	}

	ChildMapType const & children() const {
		return _children;
	}

	Node * parent() {return _parent;}
	Node const * parent() const {return _parent;}

private:
	Node * _parent;
	TimeType _start;
	StatisticsType _stats;
	ChildMapType _children;
};

} // namespace luanics::profiling
