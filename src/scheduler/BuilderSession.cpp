#ifndef HOSS_SCHEDULER_BUILDER_WRAPPER_HPP
#define HOSS_SCHEDULER_BUILDER_WRAPPER_HPP

#include "BuilderSession.hpp"

using boost::asio::ip::tcp;
using hoss::scheduler::BuilderSession;
using std::vector;

BuilderSession::BuilderSession(tcp::socket sock) :
        Session(std::move(sock))
{
}

#endif /* HOSS_SCHEDULER_BUILDER_WRAPPER_HPP */
