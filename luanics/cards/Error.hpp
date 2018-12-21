#pragma once

#include <stdexcept>

namespace luanics {
namespace cards {

class Error : public std::runtime_error {
public:
	Error(std::string const & message = std::string("")) :
		std::runtime_error{message} {}
}; // class Error

}  // namespace cards
}  // namespace luanics
