#ifndef HOSS_CORE_LOG_HPP
#define HOSS_CORE_LOG_HPP

#include <string>

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

        void trace(const std::string &msg);
        void debug(const std::string &msg);
        void info(const std::string &msg);
        void warning(const std::string &msg);
        void error(const std::string &msg);
        void fatal(const std::string &msg);

private:
        Log(const std::string &name);

        std::string name;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_LOG_HPP */
