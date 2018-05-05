add_definitions(-DBOOST_LOG_DYN_LINK)

##############################################
# VCS Support (keep alphabetical by VCS name #
##############################################

# Git
option(VCS_GIT
    "Support the git version control system"
    ON)
if (VCS_GIT)
    add_definitions(-DHOSS_ENABLE_VCS_GIT)
endif()

add_library(hoss-core SHARED
        Doc.cpp
        DocCollectionResult.cpp
        GitSource.cpp
        HttpRequest.cpp
        HttpResponse.cpp
        HttpRoute.cpp
        HttpServer.cpp
        InMemoryDocCollection.cpp
        InMemoryDocStore.cpp
        Log.cpp
        Message.cpp
        MessageProcessor.cpp
        Yaml.cpp
        junk.cpp
        system_info.cpp
        )

target_link_libraries(hoss-core
        hoss-msg1
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        git2
        microhttpd
        yaml
        )
