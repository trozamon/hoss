#ifndef HOSS_SCHEDULER_SESSION_HPP
#define HOSS_SCHEDULER_SESSION_HPP

#include <boost/asio.hpp>
#include <memory>
#include <vector>

namespace hoss
{

namespace scheduler
{

class Session
{
public:
        Session(boost::asio::ip::tcp::socket sock);

        boost::asio::ip::tcp::socket & socket();

        std::vector<char> & buffer();

private:
        class Impl;
        std::shared_ptr<Impl> impl;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SESSION_HPP */
