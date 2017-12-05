#include "Doc.hpp"

using hoss::core::Doc;

boost::any & Doc::operator[](const std::string &key)
{
        return attributes[key];
}

Doc & Doc::id(const std::string &ident)
{
        _id = ident;
        return *this;
}

const std::string & Doc::id() const
{
        return _id;
}
