#ifndef HOSS_CORE_MESSAGE_PROCESSOR_HPP
#define HOSS_CORE_MESSAGE_PROCESSOR_HPP

#include "Message.hpp"
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
        void process(const std::string &raw);

        void process(const std::vector<char> &raw);

        void process(const Message &msg);

        void handle(MessageType type,
                        const std::function<void(const Message &)> &handler);

private:
        std::map<MessageType, std::function<void(const Message &)> > cb;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_MESSAGE_PROCESSOR_HPP */
