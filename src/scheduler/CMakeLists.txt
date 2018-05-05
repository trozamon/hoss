include_directories(${Boost_INCLUDE_DIRS})

# This is not meant to be installed
add_library(hoss-scheduler STATIC
        HttpApi1.cpp
        JobDefinition.cpp
        Parser.cpp
        ScheduleRequest.cpp
        ScheduleResult.cpp
        Scheduler.cpp
        SchedulerConfiguration.cpp
        Server.cpp
        Session.cpp
        )

target_link_libraries(hoss-scheduler
        hoss-core
        )

add_executable(hoss-schedulerd hoss-schedulerd.cpp)
target_link_libraries(hoss-schedulerd
        hoss-scheduler
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
