#include "MessageProcessor.hpp"
#include <stdexcept>

using hoss::core::MessageProcessor;
using std::function;
using std::string;

void MessageProcessor::process(const std::string &raw)
{
        Message msg{raw};
        process(msg);
}

void MessageProcessor::handle(MessageType type,
                const std::function<void(const Message &)> &handler)
{
        cb[type] = handler;
}

void MessageProcessor::process(const std::vector<char> &raw)
{
        string tmp{raw.data(), raw.size()};
        process(tmp);
}

void MessageProcessor::process(const Message &msg)
{
        if (cb.count(msg.type()) == 0)
        {
                throw std::out_of_range{"No handler registered"};
                return;
        }
        else
        {
                cb[msg.type()](msg);
        }
}
