#pragma once

#include "luanics/profiling/Node.hpp"
#include "luanics/statistics/Basic.hpp"

#include <cassert>
#include <chrono>

namespace luanics::profiling {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class NodeManager
///
/// @brief Root of the Node hierarchy.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <
	typename ClockT = std::chrono::high_resolution_clock,
	template <typename> typename StatisticsT = statistics::Basic
>
class NodeManager {
public:
	using ClockType = ClockT;
	using NodeType = Node<ClockT, StatisticsT>;
	using NameType = typename NodeType::NameType;

	NodeManager() :
		_root{nullptr}, _current{&_root}
	{}

	void enter(NameType const & name) {
		assert(_current);
		_current = _current->child(name);
		_current->start();
	}
	void exit() {
		_current->stop();
		_current = _current->parent();
	}

	NodeType * current() {return _current;}
	NodeType * root() {return &_root;}
	NodeType const * root() const {return &_root;}

private:
	NodeType _root;
	NodeType * _current;
}; // class NodeManager

} // namespace luanics::profiling
