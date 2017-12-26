#include "HttpServer.hpp"
#include "Log.hpp"
#include <microhttpd.h>
#include <vector>

using hoss::core::HttpRoute;
using hoss::core::HttpServer;
using hoss::core::Log;
using std::vector;

static int respond(void *cls, struct MHD_Connection *connection,
                const char *url,
                const char *method, const char *version,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls);

class HttpServer::Impl
{
public:
        Impl();

        void setPort(unsigned short port);

        void start();

        HttpRoute & route(const std::string &path);

        const vector<HttpRoute> & getRoutes() const;

        int respond(void *cls, struct MHD_Connection *connection,
                        const char *url,
                        const char *method, const char *version,
                        const char *upload_data,
                        size_t *upload_data_size, void **con_cls);

private:
        Log log;
        struct MHD_Daemon *mhd;
        unsigned short port;
        vector<HttpRoute> routes;
};

HttpServer::HttpServer() :
        impl{new HttpServer::Impl()}
{
}

HttpServer & HttpServer::port(unsigned short p)
{
        impl->setPort(p);
        return *this;
}

void HttpServer::start()
{
        impl->start();
}

HttpRoute & HttpServer::route(const std::string &path)
{
        return impl->route(path);
}

const vector<HttpRoute> & HttpServer::routes() const
{
        return impl->getRoutes();
}

HttpServer::Impl::Impl() :
        log{Log::getLogger("HttpServer")}
{
}

void HttpServer::Impl::setPort(unsigned short p)
{
        port = p;
}

void HttpServer::Impl::start()
{
        log.info() << "Listening on " << port << linesep;

        mhd = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, nullptr,
                        nullptr, &::respond, this, MHD_OPTION_END);

        if (nullptr == mhd)
        {
                log.error("Failed to launch with MHD");
        }
}

HttpRoute & HttpServer::Impl::route(const std::string &path)
{
        HttpRoute r{path};

        routes.push_back(r);

        return routes.back();
}

const vector<HttpRoute> & HttpServer::Impl::getRoutes() const
{
        return routes;
}

static int respond(void * /*cls*/, struct MHD_Connection * /*connection*/,
                const char * /*url*/,
                const char * /*method*/, const char * /*version*/,
                const char * /*upload_data*/,
                size_t * /*upload_data_size*/, void ** /*con_cls*/)
{
        return 0;
}
