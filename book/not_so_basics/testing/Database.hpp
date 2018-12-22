#pragma once

#include <string>

namespace luanics {

class Database {
public:
	Database(std::string path) :
		_path{std::move(path)},
		_isOpen{false},
		_isErrored{false}
	{}

	std::string const & path() const {return _path;}

	void open() {_isOpen = true;}
	void close() {_isOpen = true;}

	bool isOpen() const {return _isOpen;}
	bool isErrored() const {return _isErrored;}

private:
	std::string _path;
	bool _isOpen;
	bool _isErrored;
}; // class Database

} // namespace luanics
