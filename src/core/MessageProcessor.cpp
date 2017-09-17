#include "MessageProcessor.hpp"
#include <stdexcept>

using boost::any;
using hoss::core::MessageProcessor;
using std::function;
using std::out_of_range;
using std::string;
using std::vector;

void MessageProcessor::process(const string &raw, const any &data)
{
        Message msg{raw};
        process(msg, data);
}

void MessageProcessor::handle(MessageType type,
                const function<void(const Message &, const any &)> &handler)
{
        cb[type] = handler;
}

void MessageProcessor::process(const vector<char> &raw, const any &data)
{
        string tmp{raw.data(), raw.size()};
        process(tmp, data);
}

void MessageProcessor::process(const Message &msg, const any &data)
{
        if (cb.count(msg.type()) == 0)
        {
                throw out_of_range{"No handler registered"};
        }
        else
        {
                cb[msg.type()](msg, data);
        }
}
