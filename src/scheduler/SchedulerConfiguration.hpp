#ifndef HOSS_SCHEDULER_SCHEDULER_CONFIGURATION_HPP
#define HOSS_SCHEDULER_SCHEDULER_CONFIGURATION_HPP

#include "core/Yaml.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace hoss
{

namespace scheduler
{

class SchedulerConfiguration
{
public:
        SchedulerConfiguration();

        static SchedulerConfiguration fromYaml(std::ifstream &yaml);

        static SchedulerConfiguration fromYaml(const std::string &yaml);

        std::vector<std::string> defDirs();

private:
        SchedulerConfiguration(const hoss::core::Yaml &conf);

        hoss::core::Yaml _conf;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SCHEDULER_CONFIGURATION_HPP */
