#ifndef HOSS_SCHEDULER_HTTP_API_1_HPP
#define HOSS_SCHEDULER_HTTP_API_1_HPP

#include <core/HttpServer.hpp>
#include "Scheduler.hpp"

namespace hoss
{

namespace scheduler
{

class HttpApi1
{
public:
        HttpApi1(hoss::core::HttpServer &httpServer,
                        hoss::scheduler::Scheduler &scheduler);

        hoss::core::HttpResponse getJob(const hoss::core::HttpRequest &req);

        hoss::core::HttpResponse getJobs(const hoss::core::HttpRequest &req);

private:
        hoss::core::HttpServer &httpServer;
        hoss::scheduler::Scheduler &scheduler;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_HTTP_API_1_HPP */
