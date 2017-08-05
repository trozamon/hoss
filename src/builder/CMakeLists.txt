# This library is not meant to be installed
add_library(hoss-builder STATIC
        Builder.cpp
        )

target_link_libraries(hoss-builder
        hoss-core
        hoss-msg1
        )

add_executable(hoss-builderd hoss-builderd.cpp)

target_link_libraries(hoss-builderd
        hoss-builder
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )
