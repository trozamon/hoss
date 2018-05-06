add_executable(hoss
        hoss.cpp
        io.cpp
        )

target_link_libraries(hoss
        hoss-core
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )
