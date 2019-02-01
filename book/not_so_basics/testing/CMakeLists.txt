add_executable(blackjack_test TestMain.cpp CardTest.cpp RankTest.cpp)
set_target_properties(blackjack_test PROPERTIES OUTPUT_NAME blackjack_test${BUILD_POSTFIX})
target_link_libraries(blackjack_test luanics pthread)

add_executable(BlackjackApp GameMain.cpp Game.cpp Hand.cpp)
set_target_properties(BlackjackApp PROPERTIES OUTPUT_NAME blackjack${BUILD_POSTFIX})
target_link_libraries(BlackjackApp luanics pthread)
