#ifndef HOSS_CORE_INMEMORY_DOC_COLLECTION_HPP
#define HOSS_CORE_INMEMORY_DOC_COLLECTION_HPP

#include "DocCollection.hpp"
#include <string>
#include <unordered_map>

namespace hoss
{

namespace core
{

class InMemoryDocCollection : public DocCollection
{
public:
        virtual DocCollectionResult insert(const Doc &doc);

        virtual DocCollectionResult update(const Doc &doc);

        virtual DocCollectionResult upsert(const Doc &doc);

        virtual Doc get(const std::string &id);

private:
        std::string generateId();

        std::unordered_map<std::string, Doc> docs;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_INMEMORY_DOC_COLLECTION_HPP */
