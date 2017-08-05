include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_BINARY_DIR}/src")

find_package(Boost REQUIRED COMPONENTS
        unit_test_framework
        )

add_subdirectory(core)
