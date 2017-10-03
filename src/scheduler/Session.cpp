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

        size_t bufferLength();

        Session::Key key() const;

private:
        tcp::socket sock;
        vector<char> buf;
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

Session::Impl::Impl(tcp::socket sock) :
        sock{std::move(sock)}
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
