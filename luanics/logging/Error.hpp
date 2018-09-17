#pragma once

#include <stdexcept>

namespace luanics {

class Error : public std::runtime_error {
public:
	Error(std::string const & message) : std::runtime_error{message} {}
};

class PreconditionViolation : public Error {
public:
	PreconditionViolation(std::string const & message) : Error{message} {}
};

class PostconditionViolation : public Error {
public:
	PostconditionViolation(std::string const & message) : Error{message} {}
};

}  // namespace luanics
