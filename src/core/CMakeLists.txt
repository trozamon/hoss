add_definitions(-DBOOST_LOG_DYN_LINK)

add_library(hoss-core SHARED
        Configuration.cpp
        Log.cpp
        Socket.cpp
        )

target_link_libraries(hoss-core
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
