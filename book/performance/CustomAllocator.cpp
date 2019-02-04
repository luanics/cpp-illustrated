#include "luanics/benchmark/Benchmark.hpp"
#include "luanics/benchmark/TableReporter.hpp"
#include "luanics/memory/PoolAllocator.hpp"

#include <iostream>
#include <list>
#include <experimental/memory_resource>
#include <variant>
#include <vector>

using namespace luanics::benchmark;

using Element = std::array<uint8_t, 64>;
using StandardList = std::list<Element>;
using CustomList = std::list<Element, luanics::memory::PoolAllocator<Element>>;
using Vector = std::vector<Element>;

int main(int argc, char ** argv) {
	TableReporter reporter{&std::cout};

	Benchmark standard{&reporter, "Standard", 5, 10, {1000000}, 1};
	standard.run([](Benchmark & benchmark){
		StandardList container;
		std::size_t const numItems = benchmark.param();
		while (benchmark.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmark.totalNumIterations() * numItems;
		benchmark.setNumItemsProcessed(numItemsProcessed);
	});

	Benchmark custom{&reporter, "Custom", 5, 10, {1000000}, 1};
	custom.run([](Benchmark & benchmark){
		CustomList container;
		std::size_t const numItems = benchmark.param();
		while (benchmark.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmark.totalNumIterations() * numItems;
		benchmark.setNumItemsProcessed(numItemsProcessed);
	});

	Benchmark vector{&reporter, "Vector", 5, 10, {1000000}, 1};
	vector.run([](Benchmark & benchmark){
		Vector container;
		std::size_t const numItems = benchmark.param();
		container.reserve(numItems);
		while (benchmark.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmark.totalNumIterations() * numItems;
		benchmark.setNumItemsProcessed(numItemsProcessed);
	});

	return 0;
}
