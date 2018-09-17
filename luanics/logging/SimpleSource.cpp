#include "luanics/logging/SimpleSink.hpp"
#include "luanics/logging/NoFilter.hpp"
#include "luanics/logging/SimpleSource.hpp"

#include <iostream>

namespace luanics {
namespace logging {

SimpleSource::SimpleSource() :
	_filter{new NoFilter{}},
	_sink{new SimpleSink{&std::cout}} {

}

void SimpleSource::submit(std::unique_ptr<Record> record) {
	if (not _filter->isAccepting(*record)) {
		return;
	}
	_sink->consume(std::move(record));
}

void SimpleSource::setFilter(std::unique_ptr<Filter> filter) {
	_filter = std::move(filter);
}

void SimpleSource::setSink(std::unique_ptr<Sink> sink) {
	_sink = std::move(sink);
}

} // namespace logging
} // namespace luanics
