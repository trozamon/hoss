#include "core/MessageProcessor.hpp"
#include "shim.hpp"

using boost::any;
using boost::any_cast;
using hoss::core::Message;
using hoss::core::MessageProcessor;
using hoss::core::MessageType;
using hoss::msg1::Heartbeat;
using std::string;
using std::vector;

class MockMessageProcessor : MessageProcessor
{
public:
        MockMessageProcessor()
        {
                handle(MessageType::Heartbeat1, std::bind(
                                        &MockMessageProcessor::handleHeartbeat,
                                        this,
                                        std::placeholders::_1,
                                        std::placeholders::_2));
        }

        void handleHeartbeat(const Message &msg, const any &d)
        {
                hbs.push_back(msg.message<Heartbeat>());
                data.push_back(d);
        }

        void proc(const string &raw, const any &data)
        {
                process(raw, data);
        }

        vector<Heartbeat> hbs;
        vector<any> data;
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
                any thing = static_cast<int>(2);

                processor.proc(msg.buffer(), thing);
        }

        MockMessageProcessor processor;
};

BOOST_AUTO_TEST_CASE(processedAHeartbeat)
{
        F f;

        BOOST_CHECK_EQUAL(1, f.processor.hbs.size());
        BOOST_CHECK_EQUAL("hey.example.com", f.processor.hbs[0].hostname());
        BOOST_CHECK_EQUAL(4, f.processor.hbs[0].cpu().threads_total());
        BOOST_CHECK_EQUAL(3, f.processor.hbs[0].cpu().threads_used());
        BOOST_CHECK_EQUAL(4096, f.processor.hbs[0].memory().mb_total());
        BOOST_CHECK_EQUAL(2048, f.processor.hbs[0].memory().mb_used());
        BOOST_CHECK_EQUAL(2, any_cast<int>(f.processor.data[0]));
}
