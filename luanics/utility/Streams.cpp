#include "luanics/utility/Streams.hpp"

namespace luanics::utility {

void reset(std::ostringstream & out, std::string const & value) {
	out.str(value);
	out.clear();
}

void reset(std::istringstream & in, std::string const & value) {
	in.str(value);
	in.clear();
}

} // namespace luanics::utility
