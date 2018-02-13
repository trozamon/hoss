cmake_minimum_required(VERSION 3.5)
project(hoss
        LANGUAGES CXX
        VERSION 0.0.0
        )

set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS
        filesystem
        log
        program_options
        system
        )

find_package(Protobuf REQUIRED)

find_program(SPHINX_BUILD sphinx-build)
find_program(DOXYGEN doxygen)

add_subdirectory(docs)
add_subdirectory(src)

option(ENABLE_TESTS
        "Build and run the tests"
        OFF
        )

if (ENABLE_TESTS)
        enable_testing()
        add_subdirectory(test)
endif()
