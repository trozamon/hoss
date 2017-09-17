#ifndef HOSS_CORE_LOG_HPP
#define HOSS_CORE_LOG_HPP

#include "constants.hpp"
#include <string>
#include <sstream>

namespace hoss
{

namespace core
{

class Log
{
public:
        /**
         * Get a named logger.
         *
         * @param name A name (usually the class name)
         * @return a logger that can be logged to
         */
        static Log getLogger(const std::string &name);

        enum class Level
        {
                TRACE,
                DEBUG,
                INFO,
                WARNING,
                ERROR,
                FATAL
        };

        void trace(const std::string &msg);

        void debug(const std::string &msg);
        void info(const std::string &msg);
        void warning(const std::string &msg);
        void error(const std::string &msg);
        void fatal(const std::string &msg);

        void add(const std::string &s);
        void add(char c);
        void add(unsigned char c);
        void add(short s);
        void add(unsigned short s);
        void add(int i);
        void add(unsigned int i);
        void add(long l);
        void add(unsigned long l);
        void add(float f);
        void add(double d);

        std::string buffer();

        Log & trace();
        Log & debug();
        Log & info();
        Log & warning();
        Log & error();
        Log & fatal();

        Level getLevel();

private:
        Log(const std::string &name);

        std::string name;
        Level level;
        std::stringstream buf;
};

} /* namespace core */

} /* namespace hoss */

hoss::core::Log & operator<<(hoss::core::Log &log, const std::string &msg);
hoss::core::Log & operator<<(hoss::core::Log &log, const char *msg);
hoss::core::Log & operator<<(hoss::core::Log &log, char c);
hoss::core::Log & operator<<(hoss::core::Log &log, unsigned char c);
hoss::core::Log & operator<<(hoss::core::Log &log, short s);
hoss::core::Log & operator<<(hoss::core::Log &log, unsigned short s);
hoss::core::Log & operator<<(hoss::core::Log &log, int i);
hoss::core::Log & operator<<(hoss::core::Log &log, unsigned int i);
hoss::core::Log & operator<<(hoss::core::Log &log, long l);
hoss::core::Log & operator<<(hoss::core::Log &log, unsigned long l);
hoss::core::Log & operator<<(hoss::core::Log &log, float f);
hoss::core::Log & operator<<(hoss::core::Log &log, double d);

#endif /* HOSS_CORE_LOG_HPP */
