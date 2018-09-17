#*******************************************************************
# Library
#*******************************************************************

list(APPEND LuanicsLibSources logging/Level.cpp)
list(APPEND LuanicsLibSources logging/Logger.cpp)
list(APPEND LuanicsLibSources logging/SimpleSink.cpp)
list(APPEND LuanicsLibSources logging/SimpleSource.cpp)

list(APPEND LuanicsLibSources testing/core/AbstractReporter.cpp)
list(APPEND LuanicsLibSources testing/core/Composite.cpp)
list(APPEND LuanicsLibSources testing/core/Leaf.cpp)
list(APPEND LuanicsLibSources testing/core/Outcome.cpp)
list(APPEND LuanicsLibSources testing/core/SimpleReporter.cpp)
list(APPEND LuanicsLibSources testing/tutorial/FirstFailFilter.cpp)
list(APPEND LuanicsLibSources testing/tutorial/Level.cpp)
list(APPEND LuanicsLibSources testing/tutorial/ReporterAdapter.cpp)
list(APPEND LuanicsLibSources testing/tutorial/StandardReporter.cpp)
list(APPEND LuanicsLibSources testing/unit/Filter.cpp)
list(APPEND LuanicsLibSources testing/unit/Instance.cpp)
list(APPEND LuanicsLibSources testing/unit/ReporterAdapter.cpp)
list(APPEND LuanicsLibSources testing/unit/StandardReporter.cpp)

list(APPEND LuanicsLibSources string/Conversion.cpp)
list(APPEND LuanicsLibSources string/ExactMatcher.cpp)

list(APPEND LuanicsLibSources utility/Paths.cpp)

add_library(LuanicsLib SHARED ${LuanicsLibSources})
set_target_properties(LuanicsLib PROPERTIES OUTPUT_NAME luanics${BUILD_POSTFIX})

#*******************************************************************
# Test
#*******************************************************************

list(APPEND LuanicsTestSources logging/test/ContractTest.cpp)
list(APPEND LuanicsTestSources logging/test/SimpleSinkTest.cpp)
list(APPEND LuanicsTestSources logging/test/SimpleSourceTest.cpp)
list(APPEND LuanicsTestSources logging/test/TupleRecordTest.cpp)

list(APPEND LuanicsTestSources testing/core/test/OutcomeTest.cpp)
list(APPEND LuanicsTestSources testing/core/test/CoreTest.cpp)
list(APPEND LuanicsTestSources testing/tutorial/test/ReporterAdapterTest.cpp)

list(APPEND LuanicsTestSources string/test/AllMatcherTest.cpp)
list(APPEND LuanicsTestSources string/test/ExactMatcherTest.cpp)
list(APPEND LuanicsTestSources string/test/ManipulationTest.cpp)

list(APPEND LuanicsTestSources utility/test/ExpressionAnalysisTest.cpp)
list(APPEND LuanicsTestSources utility/test/PathsTest.cpp)
list(APPEND LuanicsTestSources utility/test/TuplesTest.cpp)

add_executable(LuanicsTestApp TestMain.cpp ${LuanicsTestSources})
set_target_properties(LuanicsTestApp PROPERTIES OUTPUT_NAME test${BUILD_POSTFIX})
target_link_libraries(LuanicsTestApp LuanicsLib pthread)
