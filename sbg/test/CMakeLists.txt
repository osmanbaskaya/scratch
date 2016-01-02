cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ../kmer_analyzer_test.cpp ../kmer_analyzer.cpp ../utils.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_definitions(-std=c++11)

