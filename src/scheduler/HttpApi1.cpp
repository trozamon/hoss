#include "HttpApi1.hpp"
#include <functional>

using hoss::core::HttpRequest;
using hoss::core::HttpResponse;
using hoss::core::HttpServer;
using hoss::core::HttpStatus;
using hoss::scheduler::HttpApi1;
using hoss::scheduler::Scheduler;

#define HANDLER(x) std::bind(&HttpApi1::x, this, std::placeholders::_1)

HttpApi1::HttpApi1(HttpServer &httpServer, Scheduler &scheduler) :
        httpServer{httpServer},
        scheduler{scheduler}
{
        httpServer.route("/api/v1/jobs")
                .handler(HANDLER(getJobs));

        httpServer.route("/api/v1/job/:id")
                .handler(HANDLER(getJob));
}

HttpResponse HttpApi1::getJob(const HttpRequest & /*req*/)
{
        return HttpResponse()
                .status(HttpStatus::NOT_FOUND);
}

HttpResponse HttpApi1::getJobs(const HttpRequest & /*req*/)
{
        return HttpResponse()
                .status(HttpStatus::NO_CONTENT);
}
