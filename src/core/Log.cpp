#include "Log.hpp"
#include <boost/log/trivial.hpp>

using hoss::core::Log;
using hoss::core::linesep;
using std::string;

Log::Log(const std::string &name) :
        name{name},
        level{Level::TRACE}
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

Log & Log::trace()
{
        level = Level::TRACE;
        return *this;
}

Log & Log::debug()
{
        level = Level::DEBUG;
        return *this;
}

Log & Log::info()
{
        level = Level::INFO;
        return *this;
}

Log & Log::warning()
{
        level = Level::WARNING;
        return *this;
}

Log & Log::error()
{
        level = Level::ERROR;
        return *this;
}

Log & Log::fatal()
{
        level = Level::FATAL;
        return *this;
}

Log::Level Log::getLevel()
{
        return level;
}

void Log::add(char c)
{
        buf << c;
}

void Log::add(unsigned char c)
{
        buf << c;
}

void Log::add(short s)
{
        buf << s;
}

void Log::add(unsigned short s)
{
        buf << s;
}

void Log::add(int i)
{
        buf << i;
}

void Log::add(unsigned int i)
{
        buf << i;
}

void Log::add(long l)
{
        buf << l;
}

void Log::add(unsigned long l)
{
        buf << l;
}

void Log::add(float f)
{
        buf << f;
}

void Log::add(double d)
{
        buf << d;
}

void Log::add(const string &s)
{
        size_t pos = s.find(linesep);

        if (pos == string::npos)
        {
                buf << s;
                return;
        }

        buf << s.substr(0, pos);

        string msg = buf.str();

        switch (getLevel())
        {
        case Log::Level::TRACE:
                BOOST_LOG_TRIVIAL(trace) << msg;
                break;
        case Log::Level::DEBUG:
                BOOST_LOG_TRIVIAL(debug) << msg;
                break;
        case Log::Level::INFO:
                BOOST_LOG_TRIVIAL(info) << msg;
                break;
        case Log::Level::WARNING:
                BOOST_LOG_TRIVIAL(warning) << msg;
                break;
        case Log::Level::ERROR:
                BOOST_LOG_TRIVIAL(error) << msg;
                break;
        case Log::Level::FATAL:
                BOOST_LOG_TRIVIAL(fatal) << msg;
                break;
        default:
                BOOST_LOG_TRIVIAL(trace) << msg;
                break;
        }

        buf.str("");
}

Log & operator<<(Log &log, const std::string &msg)
{
        log.add(msg);
        return log;
}

Log & operator<<(Log &log, const char *msg)
{
        log.add(msg);
        return log;
}

Log & operator<<(Log &log, long l)
{
        log.add(l);
        return log;
}

Log & operator<<(Log &log, unsigned long l)
{
        log.add(l);
        return log;
}

Log & operator<<(Log &log, double d)
{
        log.add(d);
        return log;
}

Log & operator<<(Log &log, char c)
{
        log.add(c);
        return log;
}

Log & operator<<(Log &log, unsigned char c)
{
        log.add(c);
        return log;
}

Log & operator<<(Log &log, short s)
{
        log.add(s);
        return log;
}

Log & operator<<(Log &log, unsigned short s)
{
        log.add(s);
        return log;
}

Log & operator<<(Log &log, int i)
{
        log.add(i);
        return log;
}

Log & operator<<(Log &log, unsigned int i)
{
        log.add(i);
        return log;
}

Log & operator<<(Log &log, float f)
{
        log.add(f);
        return log;
}
