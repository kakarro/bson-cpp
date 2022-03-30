cmake_minimum_required(VERSION 3.10)

project(example)

add_subdirectory(bson)

add_executable(example example.cpp)
target_link_libraries(example ${Boost_LIBRARIES} bsoncxx)