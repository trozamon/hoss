#ifndef HOSS_SCHEDULER_BUILDER_SESSION_HPP
#define HOSS_SCHEDULER_BUILDER_SESSION_HPP

#include "Session.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <vector>

namespace hoss
{

namespace scheduler
{

class BuilderSession : public Session
{
public:
        BuilderSession(boost::asio::ip::tcp::socket sock);
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_BUILDER_SESSION_HPP */
