#include "Builder.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

using hoss::builder::Builder;
using std::cout;
using std::endl;
using std::string;

static po::variables_map parse_args(int argc, char **argv)
{
        po::options_description desc{"hoss-builderd options"};
        po::variables_map vm;

        desc.add_options()
                ("help", "view this help message")

                ("configuration", po::value<string>(),
                 "Use the given configuration file")
                ;

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        return vm;
}

static void print_help()
{
        cout << "Usage: hoss-builderd [options]" << endl <<
                endl <<
                "\t--configuration <conf_file>\tUse configuration in conf_file" << endl
                ;
}

int main(int argc, char **argv)
{
        po::variables_map args = parse_args(argc, argv);
        Builder b;

        if (args.count("help"))
        {
                print_help();
                return 0;
        }

        return b.run();
}
