#include "Message.hpp"
#include <arpa/inet.h>

using hoss::core::Message;
using hoss::core::MessageType;
using hoss::msg1::Heartbeat;
using std::string;

Message::Message()
{
}

Message::Message(const std::string &raw)
{
        buf << raw;
}

Message::Message(const Heartbeat &hb)
{
        pack(MessageType::Heartbeat1, hb.SerializeAsString());
}

void Message::pack(MessageType type, const string & data)
{
        uint16_t s = htons(static_cast<uint16_t>(data.size() + HEADER_SIZE));
        uint8_t t = static_cast<uint8_t>(type);

        char *size = reinterpret_cast<char *>(&s);
        char *typ = reinterpret_cast<char *>(&t);

        buf << size[0] << size[1] << typ[0] << data;
}

string Message::buffer() const
{
        return buf.str();
}

MessageType Message::type()
{
        string raw = buf.str();

        return static_cast<MessageType>(raw[2]);
}

size_t Message::length() const
{
        uint16_t len = 0;

        len |= static_cast<uint16_t>(buf.str().at(0));
        len |= (static_cast<uint16_t>(buf.str().at(1)) << 8);

        return static_cast<size_t>(ntohs(len));
}
