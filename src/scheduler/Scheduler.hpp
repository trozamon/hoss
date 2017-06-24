#ifndef HOSS_SCHEDULER_SCHEDULER_HPP
#define HOSS_SCHEDULER_SCHEDULER_HPP

#include <memory>

namespace hoss
{

namespace scheduler
{

class Scheduler
{
public:
        Scheduler();

        ~Scheduler();

        int run();

        constexpr static int DEFAULT_PORT = 4677;

private:
        class Impl;

        std::unique_ptr<Impl> impl;
};

} /* namespace scheduler */

} /* namespace hoss */

#endif /* HOSS_SCHEDULER_SCHEDULER_HPP */
