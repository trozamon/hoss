#ifndef HOSS_SCHEDULER_JOB_DEFINITION_HPP
#define HOSS_SCHEDULER_JOB_DEFINITION_HPP

#include <string>

namespace hoss
{

namespace scheduler
{

class JobDefinition
{
public:
        JobDefinition & id(const std::string &id);

        JobDefinition & sourceType(const std::string &type);

        JobDefinition & sourceUri(const std::string &uri);

        JobDefinition & buildType(const std::string &type);

        const std::string & id() const;

private:
        std::string _id;
        std::string _sourceType;
        std::string _sourceUri;
        std::string _buildType;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_JOB_DEFINITION_HPP */
