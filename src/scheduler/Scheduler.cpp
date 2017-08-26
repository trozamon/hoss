#include "Scheduler.hpp"
#include "Session.hpp"
#include "core/Log.hpp"
#include "core/MessageProcessor.hpp"
#include "msg1/Heartbeat.pb.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <unordered_map>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::core::Log;
using hoss::core::Message;
using hoss::core::MessageType;
using hoss::core::linesep;
using hoss::msg1::Heartbeat;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Session;
using std::string;
using std::unordered_map;

class KeyHash
{
public:
        size_t operator()(const Session::Key &k) const;
};

class Scheduler::Impl : public hoss::core::MessageProcessor
{
public:
        Impl();

        int run();

        void doAccept();

        void doReadHeader(Session session);

        void handleAccept(error_code error);

        void handleHeartbeat1(const Message &msg);

        void handleReadHeader(Session session, error_code error, size_t read);

        void setupProcessing();

private:
        io_service svc;
        tcp::acceptor acceptor;
        tcp::socket sock;
        Log log;
        unordered_map<Session::Key, Session, KeyHash> sessions;
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
        sock{svc},
        log{Log::getLogger("Scheduler")}
{
        setupProcessing();
        doAccept();
}

void Scheduler::Impl::setupProcessing()
{
        handle(MessageType::Heartbeat1,
                        std::bind(&Scheduler::Impl::handleHeartbeat1, this,
                                std::placeholders::_1));
}

int Scheduler::Impl::run()
{
        svc.run();

        return 0;
}

void Scheduler::Impl::doAccept()
{
        acceptor.async_accept(sock, boost::bind(
                                &Scheduler::Impl::handleAccept,
                                this,
                                boost::asio::placeholders::error
                                )
                        );
}

void Scheduler::Impl::handleAccept(error_code error)
{
        if (!error)
        {
                Session s{std::move(sock)};

                sessions[s.key()] = s;
                doReadHeader(s);
        }

        doAccept();
}

void Scheduler::Impl::doReadHeader(Session session)
{
        auto buf = boost::asio::buffer(session.buffer(),
                        Message::HEADER_SIZE);
        auto handler = boost::bind(&Scheduler::Impl::handleReadHeader,
                        this,
                        session,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred
                        );

        async_read(session.socket(), buf, handler);
}

void Scheduler::Impl::handleReadHeader(Session session, error_code error,
                size_t read)
{
        if (error)
        {
                log.warning("Could not read header!");
                doReadHeader(session);
                return;
        }

        if (read != 3)
        {
                log.warning("Did not read the header size");
                doReadHeader(session);
                return;
        }

        Message msg{session.buffer()};

        log.info() << "Received header for a message of length " <<
                msg.length() << " and type " <<
                static_cast<long>(msg.type()) << linesep;

        process(msg);
}

void Scheduler::Impl::handleHeartbeat1(const Message &msg)
{
        Heartbeat hb = msg.message<Heartbeat>();
        Session::Key k{hb.hostname(), 0};

        if (sessions.count(k) == 0)
        {
                log.info() << "Got new connection from " << hb.hostname() <<
                        linesep;
        }
}

size_t KeyHash::operator()(const Session::Key &k) const
{
        return k.hash();
}
