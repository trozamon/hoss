#include "Server.hpp"
#include <core/InMemoryDocStore.hpp>
#include <functional>
#include <thread>

using hoss::core::InMemoryDocStore;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Server;
using std::thread;

Server::Server() :
        docStore{new InMemoryDocStore()},
        scheduler{docStore}
{
}

int Server::run()
{
        thread sched{std::bind(&Scheduler::run, &scheduler)};

        sched.join();
        return 0;
}
