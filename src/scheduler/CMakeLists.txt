include_directories(${Boost_INCLUDE_DIRS})

# This is not meant to be installed
add_library(hoss-scheduler STATIC
        Scheduler.cpp
        Session.cpp
        )

add_executable(hoss-schedulerd hoss-schedulerd.cpp)
target_link_libraries(hoss-schedulerd
        hoss-core
        hoss-scheduler
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
