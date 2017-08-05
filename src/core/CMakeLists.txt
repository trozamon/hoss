add_definitions(-DBOOST_LOG_DYN_LINK)

add_library(hoss-core SHARED
        Configuration.cpp
        Log.cpp
        Message.cpp
        MessageProcessor.cpp
        )

target_link_libraries(hoss-core
        hoss-msg1
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
