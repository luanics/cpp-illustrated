#include "luanics/benchmarking/Benchmarker.hpp"
#include "luanics/benchmarking/TableReporter.hpp"
#include "luanics/memory/PoolAllocator.hpp"

#include <iostream>
#include <list>
#include <experimental/memory_resource>
#include <variant>
#include <vector>

using namespace luanics::benchmarking;

using Element = std::array<uint8_t, 64>;
using StandardList = std::list<Element>;
using CustomList = std::list<Element, luanics::memory::PoolAllocator<Element>>;
using Vector = std::vector<Element>;

int main(int argc, char ** argv) {
	TableReporter reporter{&std::cout};

	Benchmarker benchmarker{&reporter, 5, 10, {1000000}, 1};

	benchmarker.run("List", [](Benchmarker & benchmarker){
		StandardList container;
		std::size_t const numItems = benchmarker.currentParam();
		while (benchmarker.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmarker.totalNumIterations() * numItems;
		benchmarker.setNumItemsProcessed(numItemsProcessed);
	});

	benchmarker.run("Custom", [](Benchmarker & benchmarker){
		CustomList container;
		std::size_t const numItems = benchmarker.currentParam();
		while (benchmarker.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmarker.totalNumIterations() * numItems;
		benchmarker.setNumItemsProcessed(numItemsProcessed);
	});

	benchmarker.run("Vector", [](Benchmarker & benchmarker){
		Vector container;
		std::size_t const numItems = benchmarker.currentParam();
		container.reserve(numItems);
		while (benchmarker.isRunning()) {
			for (std::size_t i = 0; i < numItems; ++i) {
				container.push_back(Element{});
			}
			for (std::size_t i = 0; i < numItems; ++i) {
				container.pop_back();
			}
		}
		std::size_t numItemsProcessed = benchmarker.totalNumIterations() * numItems;
		benchmarker.setNumItemsProcessed(numItemsProcessed);
	});

	return 0;
}
