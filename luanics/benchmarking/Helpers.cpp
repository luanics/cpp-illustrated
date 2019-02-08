#include "luanics/benchmarking/Helpers.hpp"

#include "luanics/benchmarking/Result.hpp"

namespace luanics::benchmarking {

namespace {

constexpr double secPerNsec = 1e-9;
constexpr double msecPerNsec = 1e-6;

}

double secTotalFor(Result const & result) {
	return result.nsecTotal() * secPerNsec;
}

double msecPerSampleMeanFor(Result const & result) {
	return result.nsecPerSampleMean() * msecPerNsec;
}

double msecPerSampleStdDevFor(Result const & result) {
	return result.nsecPerSampleStdDev() * msecPerNsec;
}

double itemsPerSecFor(Result const & result) {
	return result.numItemsProcessed() / secTotalFor(result);
}

double nsecPerItemMeanFor(Result const & result) {
	return result.nsecPerSampleMean() / result.itemsPerSample();
}

} // namespace luanics::benchmarking
