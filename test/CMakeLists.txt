cmake_minimum_required(VERSION 3.2)

project(UNIT_TEST)

find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${GTEST_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(${GTEST_LIB_DIR})

add_executable(tradeparserunittest StatisticsTest.cpp)

target_link_libraries(tradeparserunittest ${GTEST_LIBRARIES})

add_test(tradeparser_complete_test tradeparserunittest)

INSTALL(TARGETS tradeparserunittest DESTINATION bin COMPONENT applications)