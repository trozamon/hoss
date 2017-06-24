#include "Scheduler.hpp"
#include "core/Socket.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using hoss::core::Socket;
using hoss::scheduler::Scheduler;
using std::make_shared;
using std::shared_ptr;

class Scheduler::Impl
{
public:
        Impl();

        int run();

        void accept(Socket &sock);

        void read(Socket &sock);

private:
        io_service svc;
        tcp::acceptor acceptor;
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
        acceptor{svc, tcp::endpoint{tcp::v4(), DEFAULT_PORT}}
{
        Socket sock{svc};
        acceptor.async_accept(sock.get(), boost::bind(
                                &Scheduler::Impl::accept, this, sock));
}

int Scheduler::Impl::run()
{
        svc.run();

        return 0;
}

void Scheduler::Impl::accept(Socket &sock)
{
        async_read(sock.get(), boost::asio::buffer(sock.buffer()),
                        boost::bind(&Scheduler::Impl::read, this, sock));
}

void Scheduler::Impl::read(Socket &sock)
{
}
