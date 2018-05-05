#ifndef HOSS_SCHEDULER_PARSER_HPP
#define HOSS_SCHEDULER_PARSER_HPP

#include "JobDefinition.hpp"
#include "core/Log.hpp"
#include "core/Yaml.hpp"
#include <fstream>
#include <functional>
#include <string>

namespace hoss
{

namespace scheduler
{

class Parser
{
public:
        Parser();

        void parse(std::ifstream &yaml);

        void parse(const std::string &yaml);

        void jobHandler(std::function<void(JobDefinition)> handler);

private:
        void parse(const hoss::core::Yaml &yaml);

        hoss::scheduler::JobDefinition parseJob(const hoss::core::Yaml &yaml);

        std::function<void(JobDefinition)> _jobHandler;

        hoss::core::Log log;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_PARSER_HPP */
