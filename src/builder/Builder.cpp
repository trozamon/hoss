#include "Builder.hpp"
#include "core/Log.hpp"
#include "core/Socket.hpp"
#include "msg1/Heartbeat.pb.h"
#include <array>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::async_connect;
using boost::asio::deadline_timer;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::builder::Builder;
using hoss::core::Log;
using hoss::core::Socket;
using std::array;

class Builder::Impl
{
public:
        Impl();

        ~Impl();

        int run();

        void handleConnect(const error_code &error,
                        tcp::resolver::iterator endpoint);

        void handleHeartbeat(const error_code &error);

        void handleRead(const error_code &error,
                        std::size_t bytesRead);

        void handleWrite(const error_code &error,
                        std::size_t bytesWritten);

private:
        io_service svc;
        tcp::resolver resolver;
        array<char, 4096> buf;
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
                        boost::bind(&Builder::Impl::handleConnect, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::iterator));

        svc.run();

        return 0;
}

void Builder::Impl::handleConnect(const error_code &error,
                tcp::resolver::iterator endpoint)
{
        log.info("Connected, starting to send heartbeats");

        async_read(socket.get(),
                        boost::asio::buffer(buf),
                        boost::bind(&Builder::Impl::handleRead, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));

        error_code tmp;
        handleHeartbeat(tmp);
}

void Builder::Impl::handleHeartbeat(const error_code &error)
{
        deadline_timer t(svc);

        hoss::msg1::Heartbeat hb;
        async_write(socket.get(), boost::asio::buffer(hb.SerializeAsString()),
                        boost::bind(&Builder::Impl::handleWrite,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));

        t.expires_from_now(boost::posix_time::milliseconds(2000));
        t.async_wait(boost::bind(&Builder::Impl::handleHeartbeat,
                                this, boost::asio::placeholders::error));
}

void Builder::Impl::handleRead(const error_code &error, std::size_t bytesRead)
{
        log.info("Read something");
}

void Builder::Impl::handleWrite(const error_code &error,
                std::size_t bytesWritten)
{
        log.info("Sent a heartbeat");
}
