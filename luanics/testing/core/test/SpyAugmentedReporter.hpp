#pragma once

#include "luanics/logging/Contract.hpp"
#include "luanics/testing/core/Error.hpp"
#include "luanics/testing/core/Log.hpp"
#include "luanics/testing/core/Result.hpp"
#include "luanics/testing/core/AugmentedReporter.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace luanics::testing::core {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class SpyAugmentedReporter
///
/// @brief AugmentedReporter test double that keeps track of calls.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class SpyAugmentedReporter final : public AugmentedReporter {
public:
	using StartReportParams = std::tuple<std::string, unsigned>;
	using FinishReportParams = std::tuple<std::string, unsigned, Outcome>;

	std::vector<StartReportParams> const & startReportCalls() const {return _startReportCalls;}
	std::vector<FinishReportParams> const & finishReportCalls() const {return _finishReportCalls;}
	std::vector<core::Error> const & reportErrorCalls() const {return _reportErrorCalls;}
	std::vector<core::Log> const & reportLogCalls() const {return _reportLogCalls;}
	std::vector<core::Result> const & reportResultCalls() const {return _reportResultCalls;}

	virtual bool startReportOn(
		Component const & component,
		unsigned const depth
	) {
		_startReportCalls.emplace_back(component.name(), depth);
		return true;
	}
	virtual void finishReportOn(
		Component const & component,
		unsigned const depth,
		Outcome const outcome
	) {
		_finishReportCalls.emplace_back(component.name(), depth, outcome);
	}
	virtual void report(core::Error const & error) {
		_reportErrorCalls.push_back(error);
	}
	virtual void report(core::Log const & log) {
		_reportLogCalls.push_back(log);
	}
	virtual void report(core::Result const & result) {
		_reportResultCalls.push_back(result);
	}

private:
	std::vector<StartReportParams> _startReportCalls;
	std::vector<FinishReportParams> _finishReportCalls;
	std::vector<core::Error> _reportErrorCalls;
	std::vector<core::Log> _reportLogCalls;
	std::vector<core::Result> _reportResultCalls;

}; // class SpyReporter

} // namespace luanics::testing::unit
