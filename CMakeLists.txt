cmake_minimum_required (VERSION 2.6)

option(test "Build all tests." ON)

project (AlgoLab)

add_library(partition src/partition.cc)

if (test)

  add_subdirectory(lib/gtest-1.7.0)

  enable_testing()

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(runtests src/partition_test.cc)

  target_link_libraries(runtests gtest gtest_main)

  target_link_libraries(runtests partition)


endif()
