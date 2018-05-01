#include "SchedulerConfiguration.hpp"
#include "Server.hpp"
#include <boost/program_options.hpp>
#include <core/Log.hpp>
#include <fstream>
#include <iostream>

namespace po = boost::program_options;

using hoss::core::Log;
using hoss::core::linesep;
using hoss::scheduler::SchedulerConfiguration;
using hoss::scheduler::Server;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

static Log logger = Log::getLogger("hoss-schedulerd");

static po::variables_map parse_args(int argc, char **argv)
{
        po::options_description desc{"hoss-schedulerd options"};
        po::variables_map vm;

        desc.add_options()
                ("help", "view this help message")

                ("configuration",
                 po::value<string>()->default_value("/etc/hoss/scheduler.yml"),
                 "Use the given configuration file")
                ;

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        return vm;
}

static void print_help()
{
        cout << "Usage: hoss-schedulerd [options]" << endl <<
                endl <<
                "\t--configuration <conf_file>\tUse configuration in conf_file" << endl
                ;
}

static SchedulerConfiguration load_configuration(const std::string &fname)
{
        logger.info() << "Loading configuration from " << fname << linesep;
        ifstream in{fname};

        return SchedulerConfiguration::fromYaml(in);
}

int main(int argc, char **argv)
{
        po::variables_map args = parse_args(argc, argv);

        if (args.count("help"))
        {
                print_help();
                return 0;
        }

        SchedulerConfiguration conf = load_configuration(
                        args["configuration"].as<string>());

        for (auto dir : conf.defDirs())
        {
                logger.info() << "Loading defs from " << dir << linesep;
        }

        Server s;

        return s.run();
}
