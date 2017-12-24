#include "Builder.hpp"
#include "core.hpp"
#include "msg1/Heartbeat.pb.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>

namespace si = hoss::core::system_info;

using boost::asio::async_connect;
using boost::asio::deadline_timer;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::builder::Builder;
using hoss::core::Log;
using hoss::core::Message;
using std::vector;

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
        deadline_timer hbTimer;
        vector<char> buf;
        Log log;
        size_t threadsInUse;
        tcp::socket socket;
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
        hbTimer{svc},
        log{Log::getLogger("Builder")},
        threadsInUse{0},
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

        async_connect(socket, endpoints,
                        boost::bind(&Builder::Impl::handleConnect, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::iterator));

        svc.run();

        return 0;
}

void Builder::Impl::handleConnect(const error_code &error,
                tcp::resolver::iterator /*endpoint*/)
{
        if (error)
        {
                return;
        }

        log.info("Connected, starting to send heartbeats");

        async_read(socket,
                        boost::asio::buffer(buf),
                        boost::bind(&Builder::Impl::handleRead, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));

        error_code tmp;
        handleHeartbeat(tmp);
}

void Builder::Impl::handleHeartbeat(const error_code &error)
{
        if (error)
        {
                return;
        }


        hoss::msg1::Heartbeat hb;

        hb.set_hostname(si::hostname());
        hb.mutable_cpu()->set_threads_total(si::cpu_threads_total());
        hb.mutable_cpu()->set_threads_used(threadsInUse);
        hb.mutable_memory()->set_mb_total(si::memory_mb_total());
        hb.mutable_memory()->set_mb_used(0);

        Message msg{hb};
        async_write(socket, boost::asio::buffer(msg.buffer()),
                        boost::bind(&Builder::Impl::handleWrite,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));

        hbTimer.expires_from_now(boost::posix_time::seconds(2));
        hbTimer.async_wait(boost::bind(&Builder::Impl::handleHeartbeat,
                                this, boost::asio::placeholders::error));
}

void Builder::Impl::handleRead(const error_code &/*error*/,
                std::size_t /*bytesRead*/)
{
        log.info("Read something");
}

void Builder::Impl::handleWrite(const error_code & /*error*/,
                std::size_t /*bytesWritten*/)
{
        log.info("Sent a heartbeat");
}
