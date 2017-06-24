#include "Socket.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::mutable_buffer;
using hoss::core::Socket;
using std::make_shared;
using std::vector;

Socket::Socket(io_service &svc) :
        socket{make_shared<tcp::socket>(svc)}
{
}

Socket::~Socket()
{
}

tcp::socket & Socket::get()
{
        return *socket;
}

vector<char> & Socket::buffer()
{
        return buf;
}
