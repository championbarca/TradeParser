cmake_minimum_required(VERSION 3.2)

project(BENCHMARK_TRADEPARSER_BENCHMARK_TEST)

find_package(Threads REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/include
    ${Benchmark_INCLUDE_DIR}
)

link_directories(${Benchmark_LIB_DIR})

add_executable(TPBenchmark parser_benchmark.cpp)

target_link_libraries(TPBenchmark ${Benchmark_LIBRARIES})

INSTALL(TARGETS TPBenchmark DESTINATION bin COMPONENT applications)