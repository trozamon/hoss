#include "HttpRoute.hpp"

using hoss::core::HttpRequest;
using hoss::core::HttpResponse;
using hoss::core::HttpRoute;
using std::string;

HttpRoute::HttpRoute(const string &path) :
        _path{path}
{
}

HttpRoute & HttpRoute::handler(handler_t func)
{
        _handler = func;
        return *this;
}

const string & HttpRoute::path() const
{
        return _path;
}

HttpResponse HttpRoute::handle(const HttpRequest &req)
{
        return _handler(req);
}

bool HttpRoute::matches(const std::string &url) const
{
        return _path == url;
}

bool HttpRoute::matches(const char *url) const
{
        return matches(string{url});
}
