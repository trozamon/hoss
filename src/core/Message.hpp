#ifndef HOSS_CORE_MESSAGE_HPP
#define HOSS_CORE_MESSAGE_HPP

#include "msg1.hpp"
#include <sstream>

namespace hoss
{

namespace core
{

/**
 * Possible types of messages.
 */
enum class MessageType : unsigned char
{
        Unknown = 0,
        Heartbeat1 = 1,
        ScheduleRequest1 = 2,
        ScheduleResult1 = 3
};

/**
 * Container for sending protobuf things on the wire.
 *
 * Adds 3 bytes to the front of the message; 2 for the size of the message, and
 * 1 for the message type. These will be in network byte order.
 */
class Message
{
public:
        static constexpr size_t HEADER_SIZE = 3;

        /**
         * Create an empty message.
         */
        Message();

        /**
         * Create a message out of a raw buffer.
         *
         * Decodes the raw buffer.
         *
         * @param raw the raw buffer
         */
        Message(const std::string &raw);

        /**
         * Create a message out of a raw buffer.
         *
         * Decodes the raw buffer.
         *
         * @param raw the raw buffer
         */
        Message(const std::vector<char> &raw);

        /**
         * Create a message out of a heartbeat.
         *
         * @param hb a heartbeat
         */
        Message(const hoss::msg1::Heartbeat &hb);

        /**
         * Create a message out of a schedule request.
         *
         * @param req a request
         */
        Message(const hoss::msg1::ScheduleRequest &req);

        /**
         * Create a message out of a schedule result.
         *
         * @param res a result
         */
        Message(const hoss::msg1::ScheduleResult &res);

        /**
         * Get the raw message ready for shipping across the interwebz.
         *
         * @return raw message in convenient string form
         */
        std::string buffer() const;

        /**
         * Get the type of this message.
         *
         * @return the message type
         */
        MessageType type() const;

        /**
         * Decode and return the actual protobuf message.
         *
         * @return A protobuf object
         */
        template <typename Protobuf>
        Protobuf message() const
        {
                Protobuf msg;
                std::string raw = buf.str().substr(3);

                msg.ParseFromString(raw);

                return msg;
        }

        /**
         * Get the length of the message.
         *
         * @return the total message length, including headers
         */
        size_t length() const;

private:
        void unpack(const std::string &raw);

        void pack(MessageType type, const std::string & data);

        std::stringstream buf;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_MESSAGE_HPP */
