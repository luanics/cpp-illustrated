# Source code for the luanics tutorial

list(APPEND TutorialSources basics/GettingStarted.cpp)
list(APPEND TutorialSources basics/Statements.cpp)
list(APPEND TutorialSources basics/Variables.cpp)
list(APPEND TutorialSources basics/Building.cpp)
list(APPEND TutorialSources basics/Directives.cpp)
list(APPEND TutorialSources basics/Projects.cpp)
list(APPEND TutorialSources basics/Objects.cpp)
list(APPEND TutorialSources basics/References.cpp)

list(APPEND TutorialSources more_basics/ArithmeticTypes.cpp)
list(APPEND TutorialSources more_basics/Functions.cpp)
list(APPEND TutorialSources more_basics/ControlFlow.cpp)
list(APPEND TutorialSources more_basics/Expressions.cpp)
list(APPEND TutorialSources more_basics/Introspection.cpp)
list(APPEND TutorialSources more_basics/Names.cpp)
list(APPEND TutorialSources more_basics/Operators.cpp)
list(APPEND TutorialSources more_basics/Types.cpp)

list(APPEND TutorialSources not_so_basics/Tools.cpp)
list(APPEND TutorialSources not_so_basics/TypeDeduction.cpp)

list(APPEND TutorialSources ../luanics/testing/core/test/StringMatcherDecoratorTest.cpp)

#list(APPEND TutorialSources ../luanics/graphics/test/BrushTest.cpp)
#list(APPEND TutorialSources ../luanics/graphics/test/DeltaTest.cpp)
#list(APPEND TutorialSources ../luanics/graphics/test/LineTest.cpp)
#list(APPEND TutorialSources ../luanics/graphics/test/PointTest.cpp)
#list(APPEND TutorialSources ../luanics/graphics/test/ScreenBufferTest.cpp)
#
#list(APPEND TutorialSources library/Time.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/cards/RankTest.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/containers/RingBufferTest.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/crypto/IntegerTest.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/graphics3d/MatricesTest.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/MatrixTest.cpp)
#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/IoTest.cpp)
#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/OperationsTest.cpp)
#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/matrix/SolvingTest.cpp)

#list(APPEND TutorialSources ${PROJECT_SOURCE_DIR}/test/options/ValuedOptionBuilderTest.cpp)

list(APPEND TutorialSources TutorialMain.cpp)

#add_executable(LuanicsTutorialApp ${TutorialSources})
#target_link_libraries(LuanicsTutorialApp LuanicsLib pthread)
#set_target_properties(LuanicsTutorialApp PROPERTIES OUTPUT_NAME tutorial${BUILD_POSTFIX})

add_executable(tutorial ${TutorialSources})
target_link_libraries(tutorial luanics pthread)
set_target_properties(tutorial PROPERTIES OUTPUT_NAME tutorial${BUILD_POSTFIX})
