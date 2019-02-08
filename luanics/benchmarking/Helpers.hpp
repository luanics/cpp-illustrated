#pragma once

namespace luanics::benchmarking {

class Result;

double secTotalFor(Result const & result);
double msecPerSampleMeanFor(Result const & result);
double msecPerSampleStdDevFor(Result const & result);
double itemsPerSecFor(Result const & result);
double nsecPerItemMeanFor(Result const & result);

} // namespace luanics::benchmarking
