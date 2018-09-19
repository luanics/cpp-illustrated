#pragma once

#include "luanics/string/Matcher.hpp"

#include <string>
#include <vector>

namespace luanics::string {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class EnumeratedMatcher
///
/// @brief Matches any of an enumerated list of strings.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class EnumeratedMatcher : public Matcher {
public:
	EnumeratedMatcher(std::vector<std::string> targets);

	virtual bool operator()(std::string const & candidate) const override final;

private:
	std::vector<std::string> _targets;
}; // class EnumeratedMatcher

} // namespace luanics::string
