#include "Server.hpp"
#include <core/InMemoryDocStore.hpp>
#include <functional>
#include <thread>

using hoss::core::Log;
using hoss::core::HttpServer;
using hoss::core::InMemoryDocStore;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Server;
using std::thread;

Server::Server() :
        docStore{new InMemoryDocStore()},
        scheduler{docStore},
        httpApi1{httpServer, scheduler},
        log{Log::getLogger("Server")}
{
}

int Server::run()
{
        thread sched{std::bind(&Scheduler::run, &scheduler)};
        thread http1{std::bind(&HttpServer::run, &httpServer)};

        sched.join();
        return 0;
}
