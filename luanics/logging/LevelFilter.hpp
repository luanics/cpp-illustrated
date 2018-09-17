#pragma once

#include "luanics/logging/Filter.hpp"
#include "luanics/logging/Record.hpp"

namespace luanics {
namespace logging {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class LevelFilter
///
/// @brief Filters out all levels above the "maxLevel"
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class LevelFilter : public Filter {
public:
	LevelFilter(Level const maxLevel) : _maxLevel{maxLevel} {}
	virtual bool isAccepting(Record const & record) const override final {
		return record.level() <= _maxLevel;
	}
private:
	Level _maxLevel;
}; // class LevelFilter

}  // namespace logging
}  // namespace luanics
