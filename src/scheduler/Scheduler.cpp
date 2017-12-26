#include "Scheduler.hpp"
#include "Session.hpp"
#include "core/Log.hpp"
#include "core/MessageProcessor.hpp"
#include "msg1/Heartbeat.pb.h"
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <unordered_map>

namespace error = boost::asio::error;

using boost::any;
using boost::any_cast;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::core::DocStore;
using hoss::core::Log;
using hoss::core::Message;
using hoss::core::MessageType;
using hoss::core::linesep;
using hoss::msg1::Heartbeat;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Session;
using std::shared_ptr;
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
        Impl(shared_ptr<DocStore> store);

        int run();

        void doAccept();

        void doReadHeader(Session session);

        void doReadBody(Session session, size_t len);

        void handleAccept(error_code error);

        void handleHeartbeat1(const Message &msg, const any &data);

        void handleReadHeader(Session session, error_code error, size_t read);

        void handleReadBody(Session session, error_code error, size_t read);

        void setupProcessing();

private:
        io_service svc;
        tcp::acceptor acceptor;
        tcp::socket sock;
        Log log;
        shared_ptr<DocStore> store;
        unordered_map<Session::Key, Session, KeyHash> sessions;
};

Scheduler::Scheduler(shared_ptr<DocStore> store) :
        impl{new Impl(store)}
{
}

Scheduler::~Scheduler()
{
}

int Scheduler::run()
{
        return impl->run();
}

Scheduler::Impl::Impl(shared_ptr<DocStore> store) :
        acceptor{svc, tcp::endpoint{tcp::v4(), DEFAULT_PORT}},
        sock{svc},
        log{Log::getLogger("Scheduler")},
        store{store}
{
        setupProcessing();
        doAccept();
}

void Scheduler::Impl::setupProcessing()
{
        handle(MessageType::Heartbeat1,
                        std::bind(&Scheduler::Impl::handleHeartbeat1, this,
                                std::placeholders::_1, std::placeholders::_2));
}

int Scheduler::Impl::run()
{
        log.info() << "Starting scheduler on port " << DEFAULT_PORT << linesep;

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

void Scheduler::Impl::doReadBody(Session session, size_t len)
{
        session.buffer().resize(len);

        auto buf = boost::asio::buffer(
                        session.buffer().data() + Message::HEADER_SIZE,
                        len - Message::HEADER_SIZE);

        auto handler = boost::bind(&Scheduler::Impl::handleReadBody,
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
                if (error == error::eof)
                {
                        log.info() << "Client disconnected" << linesep;
                }
                else
                {
                        log.warning() <<
                                "Could not read header - got error " <<
                                error.value() << " with message " <<
                                error.message() << linesep;
                        doReadHeader(session);
                }

                return;
        }

        if (read != Message::HEADER_SIZE)
        {
                log.warning("Did not read the header size");
                doReadHeader(session);
                return;
        }

        Message msg{session.buffer()};
        doReadBody(session, msg.length());
}

void Scheduler::Impl::handleReadBody(Session session, error_code error,
                size_t read)
{
        if (error)
        {
                log.warning("Could not read body!");
                doReadHeader(session);
                return;
        }

        Message msg{session.buffer()};

        if (read != msg.length() - Message::HEADER_SIZE)
        {
                log.warning("Did not read entire message!");
                doReadHeader(session);
                return;
        }

        log.info() << "Received a message of length " <<
                msg.length() << " and type " <<
                static_cast<long>(msg.type()) << linesep;

        any thing = session;
        process(msg, thing);
        doReadHeader(session);
}

void Scheduler::Impl::handleHeartbeat1(const Message &msg, const any &data)
{
        Heartbeat hb = msg.message<Heartbeat>();
        Session::Key k{hb.name(), 0};

        if (sessions.count(k) == 0)
        {
                log.info() << "Got new connection from builder " <<
                        hb.name() << linesep;

                const Session &s = any_cast<Session>(data);
                sessions[k] = s;
        }
}

size_t KeyHash::operator()(const Session::Key &k) const
{
        return k.hash();
}
