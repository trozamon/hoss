#include "HttpResponse.hpp"

using hoss::core::HttpResponse;
using hoss::core::HttpStatus;

HttpResponse & HttpResponse::status(HttpStatus s)
{
        s = s;
        return *this;
}
