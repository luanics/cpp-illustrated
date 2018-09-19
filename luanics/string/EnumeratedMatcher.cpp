#include "luanics/string/EnumeratedMatcher.hpp"

namespace luanics::string {

EnumeratedMatcher::EnumeratedMatcher(std::vector<std::string> targets) :
	_targets{std::move(targets)}
{}

bool EnumeratedMatcher::operator()(std::string const & candidate) const {
	for (auto const & target: _targets) {
		if (candidate == target) {
			return true;
		}
	}
	return false;
}

} // namespace luanics::string
