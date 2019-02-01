#pragma once

#include "luanics/profiling/Node.hpp"
#include "luanics/profiling/NodeManager.hpp"
#include "luanics/utility/Ansi.hpp"

#include <iostream>
#include <iomanip>

namespace luanics::profiling {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class Reporter
///
/// @brief Reports the results of a profiling run.
///
/// The output looks something like this...
///
/// Node             Relative(%)     Mean(nsec)    Count
/// <root>                 	100         100            1
///    Child1                 40          20           10
///       Child1A
///       Child1B
///    Child2
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

template <typename NodeManagerT>
class Reporter {
public:
	using NodeType = typename NodeManagerT::NodeType;
	using ClockType = typename NodeManagerT::ClockType;

	Reporter(std::ostream * out) :
		_out{out}, _depth{0} {
	}

	void reportOn(NodeManagerT const & manager) {
		*_out << "** PROFILING  **" << std::endl;
		reportOn("Root", *manager.root());
	}

private:
	static constexpr int nodeColumnWidth = 30;
	static constexpr int relativeColumnWidth = 12;
	static constexpr int meanColumnWidth = 15;
	static constexpr int minColumnWidth = 12;
	static constexpr int maxColumnWidth = 12;
	static constexpr int countColumnWidth = 9;
	using Period = typename ClockType::period;
	static constexpr double nanosecondsPerTick = 1000000000.0 * Period::num / Period::den;

	void reportOn(std::string const & nodeName, NodeType const & node) {
		bool const isRoot = node.parent() == nullptr;
		if (isRoot) {
			printHeader();
		}
		printRow(nodeName, node, isRoot);
		++_depth;
		for (auto const & child: node.children()) {
			reportOn(child.first, child.second);
		}
		--_depth;
	}

	void printHeader() {
		using namespace utility::ansi;
		*_out << WHITE;
		*_out << std::left << std::setw(nodeColumnWidth) << "Node";
		*_out << std::right << std::setw(relativeColumnWidth) << "Relative(%)";
		*_out << std::right << std::setw(meanColumnWidth) << "Mean(nsec)";
		*_out << std::right << std::setw(countColumnWidth) << "Count";
		*_out << std::right << std::setw(minColumnWidth) << "Min(nsec)";
		*_out << std::right << std::setw(maxColumnWidth) << "Max(nsec)";
		*_out << RESET;
		*_out << std::endl;
	}
	void printRow(std::string const & nodeName, NodeType const & node, bool const isRoot) {
		std::string nodeIndent(_depth, ' ');
		*_out << std::left << std::setw(nodeColumnWidth) << (nodeIndent + nodeName);
		double const relative =
			isRoot ? 100 : static_cast<int>(100.0 * static_cast<double>(node.stats().total()) / static_cast<double>(node.parent()->stats().total()));
		*_out << std::right << std::setw(relativeColumnWidth) << relative;
		double const meanInNanos = nanosecondsPerTick * node.stats().mean();
		*_out << std::right << std::setw(meanColumnWidth) << meanInNanos;
		*_out << std::right << std::setw(countColumnWidth) << node.stats().count();
		double const minInNanos = nanosecondsPerTick * node.stats().min();
		*_out << std::right << std::setw(minColumnWidth) << minInNanos;
		double const maxInNanos = nanosecondsPerTick * node.stats().max();
		*_out << std::right << std::setw(maxColumnWidth) << maxInNanos;
		*_out << std::endl;
	}

	std::ostream * _out;
	int _depth;
}; // class Reporter

template <typename NodeManagerT>
void reportOn(NodeManagerT const & manager, std::ostream * out) {
	Reporter<NodeManagerT> reporter{out};
	reporter.reportOn(manager);
}

} // namespace luanics::profiling
