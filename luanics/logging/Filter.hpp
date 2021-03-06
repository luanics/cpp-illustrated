#pragma once

namespace luanics {
namespace logging {

class Record;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Filter
///
/// @brief Component that decides whether a logging::Record is accepted or rejected.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Filter {
public:
	virtual bool isAccepting(Record const & record) const = 0;

	virtual ~Filter() {}
}; // class Filter

}  // namespace logging
}  // namespace luanics
