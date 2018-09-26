# Source code for the luanics tutorial

list(APPEND LuanicsTutorialSources basics/GettingStarted.cpp)
list(APPEND LuanicsTutorialSources basics/Statements.cpp)
list(APPEND LuanicsTutorialSources basics/Variables.cpp)
list(APPEND LuanicsTutorialSources basics/Building.cpp)
list(APPEND LuanicsTutorialSources basics/Directives.cpp)
list(APPEND LuanicsTutorialSources basics/Projects.cpp)

list(APPEND LuanicsTutorialSources more_basics/ArithmeticTypes.cpp)
list(APPEND LuanicsTutorialSources more_basics/ControlFlow.cpp)
list(APPEND LuanicsTutorialSources more_basics/Expressions.cpp)
list(APPEND LuanicsTutorialSources more_basics/Introspection.cpp)
list(APPEND LuanicsTutorialSources more_basics/Names.cpp)
list(APPEND LuanicsTutorialSources more_basics/Operators.cpp)
list(APPEND LuanicsTutorialSources more_basics/Types.cpp)

list(APPEND LuanicsTutorialSources not_so_basics/Tools.cpp)
list(APPEND LuanicsTutorialSources not_so_basics/TypeDeduction.cpp)

#list(APPEND LuanicsTutorialSources ../luanics/container/test/Ring1Test.cpp)

#list(APPEND LuanicsTutorialSources ../luanics/graphics/test/BrushTest.cpp)
#list(APPEND LuanicsTutorialSources ../luanics/graphics/test/DeltaTest.cpp)
#list(APPEND LuanicsTutorialSources ../luanics/graphics/test/LineTest.cpp)
#list(APPEND LuanicsTutorialSources ../luanics/graphics/test/PointTest.cpp)
#list(APPEND LuanicsTutorialSources ../luanics/graphics/test/ScreenBufferTest.cpp)
#
#list(APPEND LuanicsTutorialSources library/Time.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/cards/RankTest.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/containers/RingBufferTest.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/crypto/IntegerTest.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/graphics3d/MatricesTest.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/MatrixTest.cpp)
#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/IoTest.cpp)
#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/OperationsTest.cpp)
#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/SolvingTest.cpp)

#list(APPEND LuanicsTutorialSources ${PROJECT_SOURCE_DIR}/test/options/ValuedOptionBuilderTest.cpp)

list(APPEND LuanicsTutorialSources TutorialMain.cpp)

#add_executable(LuanicsTutorialApp ${LuanicsTutorialSources})
#target_link_libraries(LuanicsTutorialApp LuanicsLib pthread)
#set_target_properties(LuanicsTutorialApp PROPERTIES OUTPUT_NAME tutorial${BUILD_POSTFIX})

add_executable(tutorial ${LuanicsTutorialSources})
target_link_libraries(tutorial LuanicsLib pthread)
set_target_properties(tutorial PROPERTIES OUTPUT_NAME tutorial${BUILD_POSTFIX})
