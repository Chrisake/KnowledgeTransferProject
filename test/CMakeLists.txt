include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable("${PROJECT_NAME}_test" test.cpp ${CMAKE_SOURCE_DIR}/src/utils.cpp ${CMAKE_SOURCE_DIR}/src/logger.cpp)
target_link_libraries("${PROJECT_NAME}_test" gtest_main)
add_test(tests "${PROJECT_NAME}_test")