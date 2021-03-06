#*******************************************************************
# Library
#*******************************************************************

list(APPEND LuanicsLibSources benchmarking/Helpers.cpp)
list(APPEND LuanicsLibSources benchmarking/TableReporter.cpp)

list(APPEND LuanicsLibSources cards/Card.cpp)
list(APPEND LuanicsLibSources cards/Deck.cpp)
list(APPEND LuanicsLibSources cards/Rank.cpp)
list(APPEND LuanicsLibSources cards/Suit.cpp)

list(APPEND LuanicsLibSources crypto/CaesarCipher.cpp)
list(APPEND LuanicsLibSources crypto/Helpers.cpp)
list(APPEND LuanicsLibSources crypto/Histogram.cpp)
list(APPEND LuanicsLibSources crypto/RobustCaesarCipher.cpp)
list(APPEND LuanicsLibSources crypto/VigenereCipher.cpp)

list(APPEND LuanicsLibSources grid/DynamicGrid.cpp)
list(APPEND LuanicsLibSources grid/FlippedGrid.cpp)
list(APPEND LuanicsLibSources grid/Grid.cpp)
list(APPEND LuanicsLibSources grid/SubGrid.cpp)

list(APPEND LuanicsLibSources logging/Level.cpp)
list(APPEND LuanicsLibSources logging/Logger.cpp)
list(APPEND LuanicsLibSources logging/SimpleSink.cpp)
list(APPEND LuanicsLibSources logging/SimpleSource.cpp)

list(APPEND LuanicsLibSources memory/Checker.cpp)
list(APPEND LuanicsLibSources memory/Checking.cpp)

list(APPEND LuanicsLibSources profiling/GlobalNodeManager.cpp)

list(APPEND LuanicsLibSources testing/core/AugmentedReporterDecorator.cpp)
list(APPEND LuanicsLibSources testing/core/Composite.cpp)
list(APPEND LuanicsLibSources testing/core/FirstFailDecorator.cpp)
list(APPEND LuanicsLibSources testing/core/IndentingReporter.cpp)
list(APPEND LuanicsLibSources testing/core/Leaf.cpp)
list(APPEND LuanicsLibSources testing/core/Outcome.cpp)
list(APPEND LuanicsLibSources testing/core/ReporterAugmenter.cpp)
list(APPEND LuanicsLibSources testing/core/SimpleReporter.cpp)
list(APPEND LuanicsLibSources testing/core/StringExcluderDecorator.cpp)
list(APPEND LuanicsLibSources testing/core/StringMatcherDecorator.cpp)
list(APPEND LuanicsLibSources testing/unit/Instance.cpp)
list(APPEND LuanicsLibSources testing/unit/StandardReporter.cpp)

list(APPEND LuanicsLibSources string/Conversion.cpp)
list(APPEND LuanicsLibSources string/EnumeratedMatcher.cpp)
list(APPEND LuanicsLibSources string/ExactMatcher.cpp)

list(APPEND LuanicsLibSources utility/Paths.cpp)
list(APPEND LuanicsLibSources utility/Streams.cpp)

add_library(luanics SHARED ${LuanicsLibSources})
set_target_properties(luanics PROPERTIES OUTPUT_NAME luanics${BUILD_POSTFIX})

#*******************************************************************
# Test
#*******************************************************************

list(APPEND LuanicsTestSources benchmarking/test/BenchmarkerTest.cpp)

list(APPEND LuanicsTestSources cards/test/CardTest.cpp)
list(APPEND LuanicsTestSources cards/test/RankTest.cpp)
list(APPEND LuanicsTestSources cards/test/SuitTest.cpp)

list(APPEND LuanicsTestSources crypto/test/CaesarCipherTest.cpp)
list(APPEND LuanicsTestSources crypto/test/HelpersTest.cpp)
list(APPEND LuanicsTestSources crypto/test/VigenereCipherTest.cpp)

list(APPEND LuanicsTestSources grid/test/DynamicGridTest.cpp)
list(APPEND LuanicsTestSources grid/test/FlippedGridTest.cpp)
list(APPEND LuanicsTestSources grid/test/SubGridTest.cpp)

list(APPEND LuanicsTestSources logging/test/ContractTest.cpp)
list(APPEND LuanicsTestSources logging/test/SimpleSinkTest.cpp)
list(APPEND LuanicsTestSources logging/test/SimpleSourceTest.cpp)
list(APPEND LuanicsTestSources logging/test/TupleRecordTest.cpp)

list(APPEND LuanicsTestSources math/test/OperationsTest.cpp)

list(APPEND LuanicsTestSources memory/test/PoolAllocatorTest.cpp)

list(APPEND LuanicsTestSources meta/test/DetectionTest.cpp)
list(APPEND LuanicsTestSources meta/test/TypeTraitsTest.cpp)

list(APPEND LuanicsTestSources profiling/test/NodeManagerTest.cpp)
list(APPEND LuanicsTestSources profiling/test/NodeTest.cpp)

list(APPEND LuanicsTestSources testing/core/test/OutcomeTest.cpp)
list(APPEND LuanicsTestSources testing/core/test/CoreTest.cpp)
list(APPEND LuanicsTestSources testing/core/test/StringExcluderDecoratorTest.cpp)
list(APPEND LuanicsTestSources testing/core/test/StringMatcherDecoratorTest.cpp)
list(APPEND LuanicsTestSources testing/tutorial/test/ReporterAdapterTest.cpp)

list(APPEND LuanicsTestSources statistics/test/BasicTest.cpp)
list(APPEND LuanicsTestSources statistics/test/ConceptsTest.cpp)
list(APPEND LuanicsTestSources statistics/test/OnlineTest.cpp)

list(APPEND LuanicsTestSources string/test/AllMatcherTest.cpp)
list(APPEND LuanicsTestSources string/test/EnumeratedMatcherTest.cpp)
list(APPEND LuanicsTestSources string/test/ExactMatcherTest.cpp)
list(APPEND LuanicsTestSources string/test/ManipulationTest.cpp)

list(APPEND LuanicsTestSources utility/test/ExpressionAnalysisTest.cpp)
list(APPEND LuanicsTestSources utility/test/HeraldTest.cpp)
list(APPEND LuanicsTestSources utility/test/ManualClockTest.cpp)
list(APPEND LuanicsTestSources utility/test/PathsTest.cpp)
list(APPEND LuanicsTestSources utility/test/TimerTest.cpp)
list(APPEND LuanicsTestSources utility/test/TuplesTest.cpp)

add_executable(luanics_test TestMain.cpp ${LuanicsTestSources})
set_target_properties(luanics_test PROPERTIES OUTPUT_NAME luanics_test${BUILD_POSTFIX})
target_link_libraries(luanics_test luanics pthread)
