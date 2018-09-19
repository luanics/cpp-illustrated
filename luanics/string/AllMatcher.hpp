#pragma once

#include "luanics/string/Matcher.hpp"

namespace luanics::string {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class AllMatcher
///
/// @brief Matches everything.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class AllMatcher : public Matcher {
public:
	AllMatcher() = default;
	virtual bool operator()(std::string const & candidate) const override final {
		return true;
	}
}; // class AllMatcher

} // namespace luanics::string