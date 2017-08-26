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
        class Key
        {
        public:
                Key(const std::string &hostname, uint16_t port);

                size_t hash() const;

                bool operator==(const Key &other) const;
        };

        Session();

        Session(boost::asio::ip::tcp::socket sock);

        boost::asio::ip::tcp::socket & socket();

        std::vector<char> & buffer();

        Key key() const;

private:
        class Impl;
        std::shared_ptr<Impl> impl;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SESSION_HPP */
