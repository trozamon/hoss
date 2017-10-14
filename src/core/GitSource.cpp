#include "GitSource.hpp"

using hoss::core::GitSource;
using std::string;

class GitSource::Impl
{
public:
        Impl();

        void download();
};

GitSource::GitSource()
{
}

GitSource & GitSource::url(const std::string &url);

GitSource & GitSource::path(const std::string &path);

void GitSource::download()
{
        impl->download();
}

GitSource::Impl::Impl(const string &path) :
{
}

GitSource::Impl::Impl(const string &path, const string &url) :
        path{path},
        url{url}
{
}

#ifdef HOSS_ENABLE_VCS_GIT

#include <git2.h>

void GitSource::Impl::download()
{
        git_repository *repo = nullptr;

        int err = git_clone(&repo, url.c_str(), path.c_str(), NULL);
}

#else /* ifdef HOSS_ENABLE_VCS_GIT */

void GitSource::Impl::download()
{
        throw NotSupported();
}

#endif
