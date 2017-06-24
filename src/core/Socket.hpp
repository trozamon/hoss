#ifndef HOSS_CORE_SOCKET_HPP
#define HOSS_CORE_SOCKET_HPP

#include <boost/asio.hpp>
#include <memory>
#include <vector>

namespace hoss
{

namespace core
{

class Socket
{
public:
        Socket(boost::asio::io_service &svc);

        ~Socket();

        boost::asio::ip::tcp::socket & get();

        std::vector<char> & buffer();

private:
        std::shared_ptr<boost::asio::ip::tcp::socket> socket;
        std::vector<char> buf;
};

} /* namespace hoss */

} /* namespace core */

#endif /* HOSS_CORE_SOCKET_HPP */
