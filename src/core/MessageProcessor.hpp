#ifndef HOSS_CORE_MESSAGE_PROCESSOR_HPP
#define HOSS_CORE_MESSAGE_PROCESSOR_HPP

#include "Message.hpp"
#include <boost/any.hpp>
#include <functional>
#include <map>

namespace hoss
{

namespace core
{

/**
 * This class is basically a mix-in for processing messages.
 */
class MessageProcessor
{
public:
        void process(const std::string &raw, const boost::any &data);

        void process(const std::vector<char> &raw, const boost::any &data);

        void process(const Message &msg, const boost::any &data);

        void handle(MessageType type,
                        const std::function<void(const Message &,
                                const boost::any &)> &handler);

private:
        std::map<MessageType, std::function<void(const Message &,
                        const boost::any &)> > cb;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_MESSAGE_PROCESSOR_HPP */
