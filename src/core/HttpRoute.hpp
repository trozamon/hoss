#ifndef HOSS_CORE_HTTP_ROUTE_HPP
#define HOSS_CORE_HTTP_ROUTE_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <functional>
#include <string>

namespace hoss
{

namespace core
{

/**
 * ... An HTTP route.
 */
class HttpRoute
{
public:
        typedef std::function<HttpResponse (const HttpRequest &)> handler_t;

        HttpRoute(const std::string &path);

        HttpRoute & handler(handler_t func);

        HttpResponse handle(const HttpRequest &req);

        const std::string & path() const;

private:
        handler_t _handler;
        std::string _path;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_ROUTE_HPP */
