#ifndef HOSS_SCHEDULER_SERVER_HPP
#define HOSS_SCHEDULER_SERVER_HPP

#include "HttpApi1.hpp"
#include "Scheduler.hpp"
#include "SchedulerConfiguration.hpp"
#include <core/Log.hpp>
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
        //static Server fromConfiguration(const std::string &configFile);

        Server();

        Server(const SchedulerConfiguration &conf);

        int run();

private:
        void configure();

        void loadJobDefs(const std::string &dir);

        hoss::scheduler::SchedulerConfiguration _conf;
        std::shared_ptr<hoss::core::DocStore> docStore;
        hoss::scheduler::Scheduler scheduler;
        hoss::core::HttpServer httpServer;
        hoss::scheduler::HttpApi1 httpApi1;
        hoss::core::Log log;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SERVER_HPP */
