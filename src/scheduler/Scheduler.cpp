#include "Scheduler.hpp"
#include "Session.hpp"
#include "core.hpp"
#include "msg1.hpp"
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <unordered_map>

#define HANDLER(msg_type) void handle ## msg_type(const Message &msg, \
                any &data);

#define HANDLE(msg_type) do { \
        handle(MessageType::msg_type, \
                        std::bind(&Scheduler::Impl::handle ## msg_type, \
                                this, std::placeholders::_1, \
                                std::placeholders::_2)); \
} while (0)

namespace error = boost::asio::error;
namespace msg1 = hoss::msg1;

using boost::any;
using boost::any_cast;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::system::error_code;
using hoss::core::DocStore;
using hoss::core::Log;
using hoss::core::Message;
using hoss::core::MessageType;
using hoss::core::Uuid;
using hoss::core::linesep;
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

        void addJobDefinition(const JobDefinition &jd);

        void doAccept();

        void doReadHeader(Session session);

        void doReadBody(Session session, size_t len);

        void doSend(any &session, const Message &msg);

        void doSend(Session session, const Message &msg);

        void handleAccept(error_code error);

        void handleReadHeader(Session session, error_code error, size_t read);

        void handleReadBody(Session session, error_code error, size_t read);

        void handleSend(Session session, error_code error, size_t sent);

        void setupProcessing();

        HANDLER(Heartbeat1);
        HANDLER(ScheduleRequest1);

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

void Scheduler::addJobDefinition(const JobDefinition &jd)
{
        impl->addJobDefinition(jd);
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
        HANDLE(Heartbeat1);
        HANDLE(ScheduleRequest1);
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
                        log.info("Client disconnected");
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

void Scheduler::Impl::handleHeartbeat1(const Message &msg, any &data)
{
        msg1::Heartbeat hb = msg.message<msg1::Heartbeat>();
        Session::Key k{hb.name(), 0};

        if (sessions.count(k) == 0)
        {
                log.info() << "Got new connection from builder " <<
                        hb.name() << linesep;

                const Session &s = any_cast<Session>(data);
                sessions[k] = s;
        }
}

void Scheduler::Impl::handleScheduleRequest1(const Message &msg, any &data)
{
        msg1::ScheduleRequest req = msg.message<msg1::ScheduleRequest>();
        msg1::ScheduleResult res;
        Uuid uuid;

        res.set_id(uuid.pretty());
        res.set_status(msg1::ScheduleResult::QUEUED);

        log.info() << "Scheduled " << req.id() <<
                " as " << res.id() << linesep;

        doSend(data, Message(res));
}

size_t KeyHash::operator()(const Session::Key &k) const
{
        return k.hash();
}

void Scheduler::Impl::addJobDefinition(const JobDefinition &jd)
{
}

void Scheduler::Impl::doSend(any &session, const Message &msg)
{
        Session s = any_cast<Session>(session);

        doSend(s, msg);
}

void Scheduler::Impl::doSend(Session session, const Message &msg)
{
        size_t front = session.sbuf().size();

        session.sbuf().resize(front + msg.length());
        memcpy(session.sbuf().data() + front,
                        msg.buffer().c_str(),
                        msg.length());

        if (!session.wip())
        {
                auto cb = boost::bind(&Scheduler::Impl::handleSend,
                                this,
                                session,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred
                                );

                session.wip(true);
                session.socket().async_write_some(
                                boost::asio::buffer(session.sbuf()),
                                cb);
        }
}

void Scheduler::Impl::handleSend(Session session, error_code error,
                size_t sent)
{
        if (error)
        {
                log.warning() << "Could not send - " <<
                        error.value() << " with message " <<
                        error.message() << linesep;
                session.wip(false);
                return;
        }

        session.sbuf().erase(session.sbuf().begin(),
                        session.sbuf().begin() + sent);

        if (session.sbuf().size() == 0)
        {
                session.wip(false);
        }
        else
        {
                auto cb = boost::bind(&Scheduler::Impl::handleSend,
                                this,
                                session,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred
                                );

                session.socket().async_write_some(
                                boost::asio::buffer(session.sbuf()),
                                cb);
        }
}
