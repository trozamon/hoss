#include "core/HttpRoute.hpp"
#include "shim.hpp"

using hoss::core::HttpRequest;
using hoss::core::HttpResponse;
using hoss::core::HttpRoute;

class Handler
{
public:
        Handler() : handled{false} {}

        HttpResponse handle(const HttpRequest &)
        {
                handled = true;
                return HttpResponse();
        }

        bool handled;
};

class F
{
public:
        F() : r{"/accounts/1"}
        {
                r.handler(std::bind(&Handler::handle, &h,
                                        std::placeholders::_1));
        }

        HttpRoute r;
        Handler h;
};

BOOST_AUTO_TEST_CASE(path)
{
        HttpRoute r{"/stuff"};

        BOOST_CHECK_EQUAL("/stuff", r.path());
}

BOOST_AUTO_TEST_CASE(handler)
{
        F f;

        BOOST_CHECK(!f.h.handled);

        f.r.handle(HttpRequest());

        BOOST_CHECK(f.h.handled);
}

BOOST_AUTO_TEST_CASE(copying)
{
        F f;
        HttpRoute r = f.r;

        BOOST_CHECK_EQUAL("/accounts/1", r.path());
        BOOST_CHECK(!f.h.handled);

        r.handle(HttpRequest());

        BOOST_CHECK(f.h.handled);
}
