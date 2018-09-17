#include "luanics/logging/Logger.hpp"
#include "luanics/logging/SimpleSource.hpp"

namespace luanics {
namespace logging {

Source & logger() {
	static SimpleSource instance;
	return instance;
}

} // namespace logging
} // namespace luanics
