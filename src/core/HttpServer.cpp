#include "HttpServer.hpp"
#include "Log.hpp"
#include <microhttpd.h>
#include <vector>

using hoss::core::HttpRequest;
using hoss::core::HttpResponse;
using hoss::core::HttpRoute;
using hoss::core::HttpServer;
using hoss::core::HttpStatus;
using hoss::core::Log;
using std::string;
using std::vector;

HttpResponse NOT_FOUND_RESP = HttpResponse()
        .status(HttpStatus::NOT_FOUND)
        .content("<h1>Sorry, this page does not exist :(</h1>");

static int respond(void *cls, struct MHD_Connection *connection,
                const char *url,
                const char *method, const char *version,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls);

static int send_response(struct MHD_Connection *conn, HttpResponse &res);

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
                const char *method, const char * /* version */,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls)
{
        string page{"<h1>Not Found!</h1>"};
        HttpResponse res;
        HttpRequest req;

        req.path(url).method(method);

        for (auto route : routes)
        {
                if (route.matches(url))
                {
                        log.info() << "Handling request on route " <<
                                route.path() << linesep;

                        res = route.handle(req);
                        return send_response(connection, res);
                }
        }

        log.info() << "Could not match route " << url << linesep;

        return send_response(connection, NOT_FOUND_RESP);
}

int respond(void *cls, struct MHD_Connection *connection,
                const char *url,
                const char *method, const char *version,
                const char *upload_data,
                size_t *upload_data_size, void **con_cls)
{
        if (nullptr == cls)
        {
                return MHD_NO;
        }

        HttpServer::Impl *s = reinterpret_cast<HttpServer::Impl*>(cls);
        return s->respond(connection, url, method, version,
                        upload_data, upload_data_size, con_cls);
}

int send_response(struct MHD_Connection *conn, HttpResponse &res)
{
        struct MHD_Response *resp;
        int ret;

        resp = MHD_create_response_from_buffer(res.size(),
                        static_cast<void *>(res.data()),
                        MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(conn, res.istatus(), resp);
        MHD_destroy_response(resp);

        return ret;
}
