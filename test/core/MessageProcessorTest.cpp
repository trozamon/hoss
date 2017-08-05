#include "core/MessageProcessor.hpp"
#include "shim.hpp"

using hoss::core::Message;
using hoss::core::MessageProcessor;
using hoss::core::MessageType;
using hoss::msg1::Heartbeat;
using std::vector;

class MockMessageProcessor : MessageProcessor
{
public:
        MockMessageProcessor()
        {
                handle(MessageType::Heartbeat1, std::bind(
                                        &MockMessageProcessor::handleHeartbeat,
                                        this,
                                        std::placeholders::_1));
        }

        void handleHeartbeat(const Message &msg)
        {
                hbs.push_back(msg.message<Heartbeat>());
        }

        void proc(const std::string &raw)
        {
                process(raw);
        }

        vector<Heartbeat> hbs;
};

class F
{
public:
        F()
        {
                Heartbeat hb;
                hb.set_hostname("hey.example.com");
                hb.mutable_cpu()->set_threads_total(4);
                hb.mutable_cpu()->set_threads_used(3);
                hb.mutable_memory()->set_mb_total(4096);
                hb.mutable_memory()->set_mb_used(2048);
                Message msg{hb};

                processor.proc(msg.buffer());
        }

        MockMessageProcessor processor;
};

BOOST_AUTO_TEST_CASE(processedAHeartbeat)
{
        F f;

        BOOST_TEST(1 == f.processor.hbs.size());
        BOOST_TEST("hey.example.com" == f.processor.hbs[0].hostname());
        BOOST_TEST(4 == f.processor.hbs[0].cpu().threads_total());
        BOOST_TEST(3 == f.processor.hbs[0].cpu().threads_used());
        BOOST_TEST(4096 == f.processor.hbs[0].memory().mb_total());
        BOOST_TEST(2048 == f.processor.hbs[0].memory().mb_used());
}
