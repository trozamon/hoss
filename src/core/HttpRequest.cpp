#include "HttpRequest.hpp"
#include "HttpRequestError.hpp"

using hoss::core::HttpRequest;
using std::string;

HttpRequest & HttpRequest::path(const string &path)
{
        _path = path;
        return *this;
}

const string & HttpRequest::path() const
{
        return _path;
}

HttpRequest & HttpRequest::method(const string &method)
{
        if (method == "GET")
        {
                _method = Method::GET;
        }
        else if (method == "POST")
        {
                _method = Method::POST;
        }
        else
        {
                throw HttpRequestError("Unsupported method " + method);
        }

        return *this;
}
