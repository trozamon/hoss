#include "Session.hpp"

using boost::asio::ip::tcp;
using hoss::scheduler::Session;
using std::make_shared;
using std::vector;

class Session::Impl
{
public:
        Impl();

        Impl(tcp::socket sock);

        tcp::socket & socket();

        vector<char> & buffer();

        vector<char> & sbuf();

        size_t bufferLength();

        void wip(bool inProgress);

        bool wip() const;

        Session::Key key() const;

private:
        tcp::socket sock;
        vector<char> buf;
        vector<char> _sbuf;
        bool _wip;
        size_t bufLen;
};

Session::Session()
{
}

Session::Session(tcp::socket sock) :
        impl{make_shared<Impl>(std::move(sock))}
{
}

tcp::socket & Session::socket()
{
        return impl->socket();
}

vector<char> & Session::buffer()
{
        return impl->buffer();
}

Session::Key Session::key() const
{
        return impl->key();
}

vector<char> & Session::sbuf()
{
        return impl->sbuf();
}

bool Session::wip() const
{
        return impl->wip();
}

void Session::wip(bool inProgress)
{
        impl->wip(inProgress);
}

Session::Impl::Impl(tcp::socket sock) :
        sock{std::move(sock)},
        _wip{false}
{
        buf.resize(4096);
}

tcp::socket & Session::Impl::socket()
{
        return sock;
}

vector<char> & Session::Impl::buffer()
{
        return buf;
}

vector<char> & Session::Impl::sbuf()
{
        return _sbuf;
}

void Session::Impl::wip(bool inProgress)
{
        _wip = inProgress;
}

bool Session::Impl::wip() const
{
        return _wip;
}

Session::Key Session::Impl::key() const
{
        return Session::Key{"", 0};
}

Session::Key::Key(const std::string &hostname, uint16_t port) :
        hostname{hostname},
        port{port}
{
}

size_t Session::Key::hash() const
{
        return 0;
}

bool Session::Key::operator==(const Key &other) const
{
        return hostname == other.hostname &&
                port == other.port;
}

bool Session::Key::operator!=(const Key &other) const
{
        return !(*this == other);
}
