#pragma once

#include "luanics/benchmarking/Reporter.hpp"
#include "luanics/benchmarking/Result.hpp"
#include "luanics/logging/Contract.hpp"

#include <map>

namespace luanics::benchmarking {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class RecordingReporter
///
/// @brief Stores the Results in a map by (unique) label.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class RecordingReporter final : public Reporter {
public:
	/// @pre result.label() must not have been encountered previously
	virtual void report(Result const & result) final {
		auto [iter, isInserted] = resultsByLabel_.try_emplace(result.label(), result);
		EXPECTS(isInserted, "Duplicate label:", result.label());
	}

	std::map<std::string, Result> const & resultsByLabel() const {return resultsByLabel_;}

private:
	std::map<std::string, Result> resultsByLabel_;
};

} // namespace luanics::benchmarking
