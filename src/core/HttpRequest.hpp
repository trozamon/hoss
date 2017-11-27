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
        HttpRequest & path(const std::string &path);

        const std::string & path() const;

private:
        std::string p;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_REQUEST_HPP */
