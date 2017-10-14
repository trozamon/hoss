#ifndef HOSS_CORE_GIT_SOURCE_HPP
#define HOSS_CORE_GIT_SOURCE_HPP

#include "Source.hpp"
#include <string>

namespace hoss
{

namespace core
{

/**
 * Pull some stuff from git.
 */
class GitSource : public Source
{
public:
        GitSource();

        GitSource & url(const std::string &url);

        GitSource & path(const std::string &path);

        virtual void download();

private:
        class Impl;
        std::unique_ptr<Impl> impl;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_GIT_SOURCE_HPP */
