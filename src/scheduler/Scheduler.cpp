#include "BuilderWrapper.hpp"
#include "Scheduler.hpp"
#include "core/Log.hpp"
#include "core/MessageProcessor.hpp"
#include "core/Socket.hpp"
#include "msg1/Heartbeat.pb.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::core::Log;
using hoss::core::Message;
using hoss::core::MessageType;
using hoss::core::Socket;
using hoss::msg1::Heartbeat;
using hoss::scheduler::BuilderWrapper;
using hoss::scheduler::Scheduler;
using std::make_shared;
using std::map;
using std::shared_ptr;
using std::string;

class Scheduler::Impl : public hoss::core::MessageProcessor
{
public:
        Impl();

        int run();

        void handleAccept(Socket &sock);

        void handleRead(Socket &sock, const error_code &error, size_t read);

        void handleReadHeartbeat(const Message &hb);

        void setupParsing();

private:
        io_service svc;
        tcp::acceptor acceptor;
        Log log;
        map<string, BuilderWrapper> builders;
};

Scheduler::Scheduler() :
        impl{new Impl()}
{
}

Scheduler::~Scheduler()
{
}

int Scheduler::run()
{
        return impl->run();
}

Scheduler::Impl::Impl() :
        acceptor{svc, tcp::endpoint{tcp::v4(), DEFAULT_PORT}},
        log{Log::getLogger("Scheduler")}
{
        Socket sock{svc};
        acceptor.async_accept(sock.get(), boost::bind(
                                &Scheduler::Impl::handleAccept, this, sock));
}

int Scheduler::Impl::run()
{
        svc.run();

        return 0;
}

void Scheduler::Impl::handleAccept(Socket &sock)
{
        async_read(sock.get(), boost::asio::buffer(sock.buffer()), boost::bind(
                                &Scheduler::Impl::handleRead,
                                this,
                                sock,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred
                                ));
}

void Scheduler::Impl::handleRead(Socket &sock, const error_code &error,
                size_t read)
{
        log.info("Read some stuff!");
        process(sock.buffer());
}

void Scheduler::Impl::handleReadHeartbeat(const Message &hb)
{
        log.info("Got a heartbeat!");
}

void Scheduler::Impl::setupParsing()
{
        handle(MessageType::Heartbeat1, std::bind(
                                &Scheduler::Impl::handleReadHeartbeat,
                                this,
                                std::placeholders::_1)
              );
}
