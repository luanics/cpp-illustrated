#pragma once

#include <map>
#include <iosfwd>

namespace luanics::crypto {

void histogram(std::map<int, int> const & frequencies, std::ostream & out);

} // namespace luanics::crypto
