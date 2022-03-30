cmake_minimum_required(VERSION 3.10)
project(bsoncxx)

set(BOOST_ROOT /usr/include/boost_1_78_0)
find_package(Boost REQUIRED)

add_library(bsoncxx SHARED 
            base64.cpp
            bson.cpp
            hex.cpp
            json.cpp
            parse_number.cpp
            time_support.cpp
            valid.cpp)
target_link_libraries (bsoncxx ${Boost_LIBRARIES})