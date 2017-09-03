#include "system_info.hpp"
#include <stdexcept>
#include <thread>
#include <unistd.h>

namespace si = hoss::core::system_info;

using std::runtime_error;
using std::string;
using std::thread;

string si::hostname()
{
        char buf[1024];

        int err = gethostname(buf, sizeof(buf));
        if (err != 0)
        {
                throw runtime_error{"Could not get hostname"};
        }

        return string{buf};
}

unsigned int si::cpu_threads_total()
{
        return thread::hardware_concurrency();
}

size_t si::memory_mb_total()
{
        return 0;
}
