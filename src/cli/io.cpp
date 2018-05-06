#include "io.hpp"
#include <array>
#include <sstream>

using boost::asio::ip::tcp;
using hoss::core::Message;
using std::array;
using std::string;
using std::stringstream;

IO::IO() :
        _sock{_svc}
{
}

void IO::connect(const string &host, unsigned short port)
{
        stringstream s;
        string p;

        s << port;
        s >> p;

        tcp::resolver resolver{_svc};
        tcp::resolver::query query{host, p};
        tcp::resolver::iterator it = resolver.resolve(query);

        boost::asio::connect(_sock, it);
}

void IO::send(const Message &msg)
{
        _sock.send(boost::asio::buffer(msg.buffer()));
}

Message IO::receive()
{
        array<char, 4096> buf;
        boost::system::error_code ec;
        Message msg;

        size_t len = _sock.read_some(boost::asio::buffer(buf), ec);

        if (!ec || ec == boost::asio::error::eof)
        {
                std::cout << "Got a response " << len << std::endl;
        }
        else
        {
                throw boost::system::system_error(ec);
        }

        return msg;
}
