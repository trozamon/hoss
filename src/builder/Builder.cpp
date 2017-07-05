#include "Builder.hpp"
#include "core/Log.hpp"
#include "core/Socket.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::async_connect;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using hoss::builder::Builder;
using hoss::core::Log;
using hoss::core::Socket;

class Builder::Impl
{
public:
        Impl();

        ~Impl();

        int run();

        void connected(const boost::system::error_code &error, 
                        tcp::resolver::iterator endpoint);

private:
        io_service svc;
        tcp::resolver resolver;
        Log log;
        Socket socket;
};

Builder::Builder() :
        impl{new Impl()}
{
}

Builder::~Builder()
{
}

int Builder::run()
{
        return impl->run();
}

Builder::Impl::Impl() :
        resolver{svc},
        log{Log::getLogger("Builder")},
        socket{svc}
{
}

Builder::Impl::~Impl()
{
}

int Builder::Impl::run()
{
        tcp::resolver::query query{"127.0.0.1", "4677"};
        tcp::resolver::iterator endpoints = resolver.resolve(query);

        async_connect(socket.get(), endpoints,
                        boost::bind(&Builder::Impl::connected, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::iterator));

        svc.run();

        return 0;
}

void Builder::Impl::connected(const boost::system::error_code &error, 
                tcp::resolver::iterator endpoint)
{
        log.info("Connected!");
}
