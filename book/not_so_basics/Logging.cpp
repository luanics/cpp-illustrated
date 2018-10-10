#include "luanics/logging/Logger.hpp"
#include "luanics/logging/LevelFilter.hpp"
#include "luanics/logging/Logging.hpp"
#include "luanics/utility/Herald.hpp"

void calculateStuff() {

}

void runSimulation(std::size_t const numRuns) {
	INFO("Starting simulation.")
	for (std::size_t i = 0; i < numRuns; ++i) {
		DEBUG("Running", i)
		calculateStuff();
	}
	INFO("Finished simulation.");
}

int main() {
	luanics::utility::Herald herald{"Logging"};

	luanics::logging::logger().setFilter(std::make_unique<luanics::logging::LevelFilter>(luanics::logging::Level::DEBUG));
	runSimulation(5);

	luanics::logging::logger().setFilter(std::make_unique<luanics::logging::LevelFilter>(luanics::logging::Level::INFO));
	runSimulation(5);

	return 0;
}
