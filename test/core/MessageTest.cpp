#include "core/Message.hpp"
#include "msg1/Heartbeat.pb.h"
#include "shim.hpp"

using hoss::core::Message;
using hoss::core::MessageType;
using hoss::msg1::Heartbeat;
using std::string;

class F
{
public:
        F()
        {
                hb.set_hostname("optimus.example.com");
                hb.mutable_cpu()->set_threads_total(4);
                hb.mutable_cpu()->set_threads_used(1);
                hb.mutable_memory()->set_mb_total(4096);
                hb.mutable_memory()->set_mb_used(2048);
                msg = Message{hb};
        }

        Message msg;
        Heartbeat hb;
};

BOOST_AUTO_TEST_CASE(heartbeatEncodeType)
{
        F f;
        BOOST_CHECK_EQUAL(MessageType::Heartbeat1, f.msg.type());
}

BOOST_AUTO_TEST_CASE(heartbeatEncodeLength)
{
        F f;
        string s;

        f.hb.SerializeToString(&s);

        BOOST_CHECK_EQUAL((s.size() + 3), f.msg.length());
}

BOOST_AUTO_TEST_CASE(heartbeatEncodeData)
{
        F f;
        Heartbeat parsed = f.msg.message<Heartbeat>();

        BOOST_CHECK_EQUAL(f.hb.hostname(), parsed.hostname());
        BOOST_CHECK_EQUAL(f.hb.cpu().threads_total(),
                        parsed.cpu().threads_total());
        BOOST_CHECK_EQUAL(f.hb.cpu().threads_used(),
                        parsed.cpu().threads_used());
        BOOST_CHECK_EQUAL(f.hb.memory().mb_total(),
                        parsed.memory().mb_total());
        BOOST_CHECK_EQUAL(f.hb.memory().mb_used(),
                        parsed.memory().mb_used());
}
