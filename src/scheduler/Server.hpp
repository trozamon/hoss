#ifndef HOSS_SCHEDULER_SERVER_HPP
#define HOSS_SCHEDULER_SERVER_HPP

#include "Scheduler.hpp"
#include <core/HttpServer.hpp>
#include <memory>

namespace hoss
{

namespace scheduler
{

/**
 * Server that wraps around a scheduler and an HTTP server.
 */
class Server
{
public:
        Server();

        int run();

private:
        std::shared_ptr<hoss::core::DocStore> docStore;
        hoss::scheduler::Scheduler scheduler;
        hoss::core::HttpServer httpServer;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SERVER_HPP */
