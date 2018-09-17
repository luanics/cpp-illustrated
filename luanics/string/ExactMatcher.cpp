#include "ExactMatcher.hpp"

namespace luanics {
namespace string {

ExactMatcher::ExactMatcher(std::string target) :
		_target{std::move(target)} {

}

bool ExactMatcher::operator()(std::string const & candidate) const {
	return candidate == _target;
}

} // namespace string
} // namespace luanics
