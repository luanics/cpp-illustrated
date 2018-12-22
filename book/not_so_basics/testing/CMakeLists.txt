add_executable(ExampleTestApp TestMain.cpp Hand.cpp HandTest.cpp)
set_target_properties(ExampleTestApp PROPERTIES OUTPUT_NAME example_test${BUILD_POSTFIX})
target_link_libraries(ExampleTestApp LuanicsLib pthread)

add_executable(BlackjackApp GameMain.cpp Game.cpp Hand.cpp)
set_target_properties(BlackjackApp PROPERTIES OUTPUT_NAME blackjack${BUILD_POSTFIX})
target_link_libraries(BlackjackApp LuanicsLib pthread)
