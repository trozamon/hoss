include_directories(${Boost_INCLUDE_DIRS})

add_library(hoss-scheduler SHARED
        Scheduler.cpp
        )

add_executable(hoss-schedulerd hoss-schedulerd.cpp)
target_link_libraries(hoss-schedulerd
        hoss-core
        hoss-scheduler
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
