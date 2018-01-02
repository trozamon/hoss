#ifndef HOSS_CORE_HTTP_SERVER_HPP
#define HOSS_CORE_HTTP_SERVER_HPP

#include "HttpRoute.hpp"
#include <memory>
#include <string>
#include <vector>

namespace hoss
{

namespace core
{

/**
 * Responds to HTTP requests (what else would you expect?).
 *
 * libmicrohttpd is used internally to actually respond to the requests,
 * do SSL-related things, etc.
 */
class HttpServer
{
public:
        HttpServer();

        HttpServer & port(unsigned short port);

        HttpRoute & route(const std::string &path);

        const std::vector<HttpRoute> & routes() const;

        void run();

        class Impl;

private:
        std::shared_ptr<Impl> impl;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_SERVER_HPP */
