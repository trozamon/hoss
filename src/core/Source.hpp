#ifndef HOSS_CORE_SOURCE_HPP
#define HOSS_CORE_SOURCE_HPP

#include <memory>
#include <string>

namespace hoss
{

namespace core
{

/**
 * A source that code can come from.
 *
 * This is an interface.
 */
class Source
{
public:
        enum class Type
        {
                GIT
        };

        virtual void download() = 0;
};

namespace vcs
{

/**
 * Convenience function for getting a source from a URL.
 */
std::unique_ptr<Source> get(Source::Type type, const std::string &url);

} /* namespace vcs */

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_SOURCE_HPP */
