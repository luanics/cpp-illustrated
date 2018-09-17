#pragma once

#include "luanics/logging/Sink.hpp"

namespace luanics::logging {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class SimpleSink
///
/// @brief Logging sink suitable for single-threaded applications.
///
/// All records consumed are printed to std::ostream in same thread.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SimpleSink : public Sink {
public:
	SimpleSink(std::ostream * out);
	virtual void consume(std::unique_ptr<Record> record) override final;

private:
	void writeLevel(Record const & record);
	void writeFileAndLine(Record const & record);
	void writeData(Record const & record);

	std::ostream * _out;
};

} // namespace luanics::logging
