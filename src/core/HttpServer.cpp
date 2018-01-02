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

        void run();

        HttpRoute & route(const std::string &path);

        const vector<HttpRoute> & getRoutes() const;

        int respond(struct MHD_Connection *connection,
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

void HttpServer::run()
{
        impl->run();
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
        log{Log::getLogger("HttpServer")},
        port{8080}
{
}

void HttpServer::Impl::setPort(unsigned short p)
{
        port = p;
}

void HttpServer::Impl::run()
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

int HttpServer::Impl::respond(struct MHD_Connection *connection,
                const char *url,
                const char *method, const char *version,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls)
{
        char * page = "<h1>Hey!</h1>";
        struct MHD_Response *resp;
        int ret;

        log.info() << "Handling request on path " << url << linesep;

        resp = MHD_create_response_from_buffer(13,
                        static_cast<void *>(page),
                        MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
        MHD_destroy_response(resp);

        return ret;
}

#include <iostream>
static int respond(void *cls, struct MHD_Connection *connection,
                const char *url,
                const char *method, const char *version,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls)
{
        if (nullptr == cls)
        {
                std::cout << "oh boy" << std::endl;
                return MHD_NO;
        }

        HttpServer::Impl *s = reinterpret_cast<HttpServer::Impl*>(cls);
        return s->respond(connection, url, method, version,
                        upload_data, upload_data_size, con_cls);
}
