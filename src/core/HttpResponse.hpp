#ifndef HOSS_CORE_HTTP_RESPONSE_HPP
#define HOSS_CORE_HTTP_RESPONSE_HPP

#include <string>

namespace hoss
{

namespace core
{

enum class HttpStatus
{
        OK = 200,
        NOT_FOUND = 404
};

class HttpResponse
{
public:
        HttpResponse & status(HttpStatus s);

private:
        HttpStatus s;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_RESPONSE_HPP */
