#include "HttpResponse.hpp"

using hoss::core::HttpResponse;
using hoss::core::HttpStatus;

HttpResponse::HttpResponse() :
        _status{HttpStatus::NO_CONTENT}
{
}

HttpResponse & HttpResponse::status(HttpStatus s)
{
        _status = s;
        return *this;
}

HttpResponse & HttpResponse::content(const std::string &raw)
{
        _content = raw;
        return *this;
}

HttpStatus HttpResponse::status() const
{
        return _status;
}

unsigned int HttpResponse::istatus() const
{
        return static_cast<unsigned int>(_status);
}

char * HttpResponse::data()
{
        return _content.data();
}

const char * HttpResponse::data() const
{
        return _content.data();
}

size_t HttpResponse::size() const
{
        return _content.size();
}
