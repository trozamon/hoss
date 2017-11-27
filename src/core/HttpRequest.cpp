#include "HttpRequest.hpp"

using hoss::core::HttpRequest;
using std::string;

HttpRequest & HttpRequest::path(const string &path)
{
        p = path;
        return *this;
}

const string & HttpRequest::path() const
{
        return p;
}
