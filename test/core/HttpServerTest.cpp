#include "core/HttpServer.hpp"
#include "shim.hpp"

using hoss::core::HttpRequest;
using hoss::core::HttpResponse;
using hoss::core::HttpServer;
using hoss::core::HttpStatus;

HttpResponse noop(const HttpRequest &)
{
        return HttpResponse().status(HttpStatus::OK);
}

BOOST_AUTO_TEST_CASE(addRoute)
{
        HttpServer s;

        s.route("/").handler(&noop);

        BOOST_CHECK_EQUAL(1, s.routes().size());
}
