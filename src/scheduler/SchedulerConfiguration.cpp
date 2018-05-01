#include "SchedulerConfiguration.hpp"

using hoss::core::Configuration;
using hoss::scheduler::SchedulerConfiguration;
using std::ifstream;
using std::string;
using std::vector;

SchedulerConfiguration::SchedulerConfiguration()
{
}

SchedulerConfiguration SchedulerConfiguration::fromYaml(ifstream &yaml)
{
        return SchedulerConfiguration(Configuration::fromYaml(yaml));
}

SchedulerConfiguration SchedulerConfiguration::fromYaml(
                const string &yaml)
{
        return SchedulerConfiguration(Configuration::fromYaml(yaml));
}

SchedulerConfiguration::SchedulerConfiguration(const Configuration &conf) :
        _conf{conf}
{
}

vector<string> SchedulerConfiguration::defDirs()
{
        return _conf.arr("scheduler.def_dirs");
}
