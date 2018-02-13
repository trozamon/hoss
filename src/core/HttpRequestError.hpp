#ifndef HOSS_CORE_HTTP_REQUEST_ERROR_HPP
#define HOSS_CORE_HTTP_REQUEST_ERROR_HPP

#include <exception>

namespace hoss
{

namespace core
{

class HttpRequestError : std::exception
{
public:
        HttpRequestError(const std::string &what) :
                _what{what}
        {
        }

        virtual const char * what() const noexcept
        {
                return _what.c_str();
        }

private:
        std::string _what;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_HTTP_REQUEST_ERROR_HPP */
