#include "Server.hpp"
#include <core/InMemoryDocStore.hpp>
#include <thread>

using hoss::core::InMemoryDocStore;
using hoss::core::HttpServer;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Server;
using std::thread;

Server::Server() :
        docStore{new InMemoryDocStore()},
        httpServer{},
        scheduler{docStore},
        http1{httpServer, scheduler}
{
}

int Server::run()
{
        thread sched{std::bind(&Scheduler::run, &scheduler)};

        sched.join();
        return 0;
}
