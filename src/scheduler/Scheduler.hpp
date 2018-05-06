#ifndef HOSS_SCHEDULER_SCHEDULER_HPP
#define HOSS_SCHEDULER_SCHEDULER_HPP

#include "core/DocStore.hpp"
#include "JobDefinition.hpp"
#include <memory>
#include <vector>

namespace hoss
{

namespace scheduler
{

class Scheduler
{
public:
        Scheduler(std::shared_ptr<hoss::core::DocStore> store);

        ~Scheduler();

        void addJobDefinition(const JobDefinition &jd);

        int run();

        constexpr static int DEFAULT_PORT = 4677;

private:
        class Impl;

        std::unique_ptr<Impl> impl;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SCHEDULER_HPP */
