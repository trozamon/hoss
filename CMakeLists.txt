cmake_minimum_required(VERSION 3.7)
project(hoss
        LANGUAGES CXX
        VERSION 0.0.0
        )

set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(Protobuf REQUIRED)


add_subdirectory(src)
