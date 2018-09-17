#include "luanics/logging/Record.hpp"
#include "luanics/logging/SimpleSink.hpp"
#include "luanics/utility/Paths.hpp"

#include <iomanip>
#include <mutex>

namespace luanics::logging {

SimpleSink::SimpleSink(std::ostream * out) : _out{out} {}

void SimpleSink::consume(std::unique_ptr<Record> record) {
	writeLevel(*record);
	writeFileAndLine(*record);
	writeData(*record);
	*_out << std::endl;
}

void SimpleSink::writeLevel(Record const & record) {
	*_out << "[" << std::setw(7) << std::left << record.level() << "] ";
}

void SimpleSink::writeFileAndLine(Record const & record) {
	*_out << utility::fileNameFrom(record.file()) << ":" << record.line() << " - ";
}

void SimpleSink::writeData(Record const & record) {
	record.writeMessageTo(*_out);
}

} // namespace luanics::logging
