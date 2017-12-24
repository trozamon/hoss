#ifndef HOSS_CORE_DOC_COLLECTION_HPP
#define HOSS_CORE_DOC_COLLECTION_HPP

#include "Doc.hpp"
#include "DocCollectionResult.hpp"

namespace hoss
{

namespace core
{

class DocCollection
{
public:
        virtual DocCollectionResult insert(const Doc &doc) = 0;

        virtual DocCollectionResult update(const Doc &doc) = 0;

        virtual DocCollectionResult upsert(const Doc &doc) = 0;

        virtual Doc get(const std::string &id) = 0;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_DOC_COLLECTION_HPP */
