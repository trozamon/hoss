#ifndef HOSS_CORE_DOC_HPP
#define HOSS_CORE_DOC_HPP

#include <unordered_map>
#include <boost/any.hpp>

namespace hoss
{

namespace core
{

class Doc
{
public:
        boost::any & operator[](const std::string &key);

        Doc & id(const std::string &ident);

        const std::string & id() const;

private:
        std::unordered_map<std::string, boost::any> attributes;
        std::string _id;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_DOC_HPP */
