#include "GitSource.hpp"

using hoss::core::GitSource;
using std::string;

class GitSource::Impl
{
public:
        Impl();

        void download();

        void setUrl(const string &url);

        void setPath(const string &path);

private:
        string url;
        string path;
};

GitSource::GitSource()
{
}

GitSource & GitSource::url(const string &url)
{
        impl->setUrl(url);
        return *this;
}

GitSource & GitSource::path(const string &path)
{
        impl->setPath(path);
        return *this;
}

void GitSource::download()
{
        impl->download();
}

void GitSource::Impl::setUrl(const string &u)
{
        url = u;
}

void GitSource::Impl::setPath(const string &p)
{
        path = p;
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
