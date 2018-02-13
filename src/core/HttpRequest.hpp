#ifndef HOSS_CORE_HTTP_REQUEST_HPP
#define HOSS_CORE_HTTP_REQUEST_HPP

#include <string>

namespace hoss
{

namespace core
{

class HttpRequest
{
public:
        enum Method
        {
                GET,
                POST
        };

        HttpRequest & path(const std::string &path);

        const std::string & path() const;

        HttpRequest & method(const std::string &method);

        Method method() const;

private:
        std::string _path;
        Method _method;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_REQUEST_HPP */
