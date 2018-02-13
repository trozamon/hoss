#ifndef HOSS_CORE_HTTP_RESPONSE_HPP
#define HOSS_CORE_HTTP_RESPONSE_HPP

#include <string>

namespace hoss
{

namespace core
{

enum class HttpStatus : unsigned int
{
        OK = 200,
        NOT_FOUND = 404
};

class HttpResponse
{
public:
        HttpResponse & status(HttpStatus s);

        HttpResponse & content(const std::string &raw);

        HttpStatus status() const;

        unsigned int istatus() const;

        char * data();

        const char * data() const;

        size_t size() const;

private:
        HttpStatus _status;
        std::string _content;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_RESPONSE_HPP */
