#ifndef HOSS_CLI_IO_HPP
#define HOSS_CLI_IO_HPP

#include <boost/asio.hpp>
#include "core.hpp"

class IO
{
public:
        IO();

        void connect(const std::string &host, unsigned short port);

        void send(const hoss::core::Message &msg);

        hoss::core::Message receive();

private:
        boost::asio::io_service _svc;
        boost::asio::ip::tcp::socket _sock;
};

#endif /* HOSS_CLI_IO_HPP */
