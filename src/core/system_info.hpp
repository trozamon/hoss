#ifndef HOSS_CORE_SYSTEM_INFO_HPP
#define HOSS_CORE_SYSTEM_INFO_HPP

#include <string>

namespace hoss
{
        
namespace core
{

namespace system_info
{

std::string hostname();

unsigned int cpu_threads_total();

size_t memory_mb_total();

};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_SYSTEM_INFO_HPP */
