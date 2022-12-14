cmake_minimum_required(VERSION 3.5)

project(
  soft_heap
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(GoogleTest)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main)

FetchContent_MakeAvailable(googletest googlebenchmark)

# Perf Testing Executable
add_executable(soft_heap_perf perf_testing.cpp)
target_include_directories(soft_heap_perf PRIVATE "include" "src")
set_property(
  TARGET soft_heap_perf
  PROPERTY CMAKE_BUILD_TYPE Debug
  PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler Properties for Perf
target_compile_features(soft_heap_perf PRIVATE cxx_std_20)
target_compile_options(soft_heap_perf PRIVATE -Wall)

# Unit Testing Executable
add_executable(
  soft_heap_test
  main.cpp
  test/node_tests.cpp
  test/tree_tests.cpp
  test/soft_heap_tests.cpp
  applications/selection_algorithm/tests.cpp
  applications/selection_algorithm/selection_algorithm.hpp
  applications/selection_algorithm/selection_algorithm.cpp
  test/statistics.cpp
  test/flat_tree_tests.cpp
  src/flat_node.hpp)
target_link_libraries(soft_heap_test PRIVATE gtest_main gmock gtest)
target_include_directories(soft_heap_test PRIVATE "include" "src")
set_property(
  TARGET soft_heap_test
  PROPERTY CMAKE_BUILD_TYPE Debug
  PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler Properties for Unit Testing
target_compile_features(soft_heap_test PRIVATE cxx_std_20)
target_compile_options(soft_heap_test PRIVATE -g -Wall -Wextra)

# Benchmark Executable
add_executable(soft_heap_bench benchmark.cpp)
target_link_libraries(soft_heap_bench PRIVATE benchmark::benchmark
                                              benchmark::benchmark_main)
target_include_directories(soft_heap_bench PRIVATE "include" "src")
set_property(
  TARGET soft_heap_bench
  PROPERTY CMAKE_BUILD_TYPE Release
  PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler Properties for Benchmarking
target_compile_features(soft_heap_bench PRIVATE cxx_std_20)
target_compile_options(soft_heap_bench PRIVATE -g -O3 -Wall)

gtest_discover_tests(soft_heap_test)

enable_testing()

# ## Selection Algoithm ### Benchmark Executable
add_executable(
  selection_algorithm_bench
  applications/selection_algorithm/benchmark.cpp
  applications/selection_algorithm/selection_algorithm.hpp
  applications/selection_algorithm/selection_algorithm.cpp)
target_link_libraries(selection_algorithm_bench
                      PRIVATE benchmark::benchmark benchmark::benchmark_main)
target_include_directories(selection_algorithm_bench PRIVATE "include" "src")
target_compile_features(selection_algorithm_bench PRIVATE cxx_std_20)
target_compile_options(selection_algorithm_bench PRIVATE -g -O3 -Wall)

set_property(
  TARGET selection_algorithm_bench
  PROPERTY CMAKE_BUILD_TYPE Release
  PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)
