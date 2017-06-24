add_library(hoss-core SHARED
        Configuration.cpp
        Socket.cpp
        )

target_link_libraries(hoss-core
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
