#include "Log.hpp"
#include <boost/log/trivial.hpp>

using hoss::core::Log;

Log::Log(const std::string &name) :
        name{name}
{
}

Log Log::getLogger(const std::string &name)
{
        return Log{name};
}

void Log::trace(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(trace) << msg;
}

void Log::debug(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(debug) << msg;
}

void Log::info(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(info) << msg;
}

void Log::warning(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(warning) << msg;
}

void Log::error(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(error) << msg;
}

void Log::fatal(const std::string &msg)
{
        BOOST_LOG_TRIVIAL(fatal) << msg;
}
