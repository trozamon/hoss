#include "Session.hpp"

using boost::asio::ip::tcp;
using hoss::scheduler::Session;
using std::make_shared;
using std::vector;

class Session::Impl
{
public:
        Impl(tcp::socket sock);

        tcp::socket & socket();

        vector<char> & buffer();

        size_t bufferLength();

private:
        tcp::socket sock;
        vector<char> buf;
        size_t bufLen;
};

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
