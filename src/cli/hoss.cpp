#include "core.hpp"
#include "io.hpp"
#include "msg1/ScheduleRequest.pb.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

using hoss::core::Message;
using std::cerr;
using std::cout;
using std::endl;
using std::string;

static po::variables_map parse_args(int argc, char **argv)
{
        po::variables_map vm;
        po::options_description desc("Allowed options");
        po::positional_options_description pos;

        pos.add("tool", 1);

        desc.add_options()
                ("help", "Show this help")
                ("tool", po::value<string>(), "Tool to run")
                ;

        po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(pos)
                .run(), vm);
        po::notify(vm);

        return vm;
}

static void help()
{
        cout << "Usage: hoss <tool> [options]" << endl;
        cout << endl;
        cout << "Available tools:" << endl;
        cout << "\ttrigger - Trigger a job to run" << endl;
}

static void trigger(const std::string &jobName)
{
        hoss::msg1::ScheduleRequest req;
        IO io;

        req.set_id(jobName);

        Message msg{req};

        io.connect("127.0.0.1", 4677);
        io.send(msg);

        try
        {
                msg = io.receive();
        }
        catch (boost::system::system_error &e)
        {
                cerr << e.what() << endl;
        }
}

static void run(const po::variables_map &vm)
{
        string tool = vm["tool"].as<string>();

        if (tool == "trigger")
        {
                trigger(string{"libgit2"});
        }
}

int main(int argc, char **argv)
{
        auto args = parse_args(argc, argv);

        if (args.count("help"))
        {
                help();
                return 0;
        }

        if (args.count("tool"))
        {
                run(args);
        }
        else
        {
                help();
                return 1;
        }

        return 0;
}
