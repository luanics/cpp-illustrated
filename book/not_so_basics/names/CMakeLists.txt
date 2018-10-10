#add_executable(BadNamesApp BadMain.cpp BadPlay.cpp BadWork.cpp)
#set_target_properties(BadNamesApp PROPERTIES OUTPUT_NAME bad_names${BUILD_POSTFIX})
#target_link_libraries(BadNamesApp LuanicsLib pthread)

add_executable(GoodNamesApp GoodMain.cpp GoodPlay.cpp GoodWork.cpp)
target_link_libraries(GoodNamesApp luanics pthread)
set_target_properties(GoodNamesApp PROPERTIES OUTPUT_NAME good_names${BUILD_POSTFIX})
