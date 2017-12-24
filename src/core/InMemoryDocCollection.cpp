#include "InMemoryDocCollection.hpp"
#include <sstream>

using hoss::core::Doc;
using hoss::core::DocCollectionResult;
using hoss::core::InMemoryDocCollection;
using std::string;
using std::stringstream;

DocCollectionResult InMemoryDocCollection::insert(const Doc &doc)
{
        string id = doc.id();

        if (id.size() == 0)
        {
                id = generateId();
        }

        docs[id].id(id);

        return DocCollectionResult{}
                .status(DocCollectionResult::Status::OK)
                .ids({id});
}

DocCollectionResult InMemoryDocCollection::update(const Doc &doc)
{
        DocCollectionResult r;

        if (doc.id() == string{})
        {
                return r.status(DocCollectionResult::Status::NOT_FOUND);
        }

        if (docs.count(doc.id()) == 0)
        {
                return r.status(DocCollectionResult::Status::NOT_FOUND);
        }

        docs[doc.id()] = doc;

        r.status(DocCollectionResult::Status::OK)
                .ids({doc.id()});

        return r;
}

DocCollectionResult InMemoryDocCollection::upsert(const Doc &doc)
{
        if (doc.id().size() == 0 ||
                        docs.count(doc.id()) == 0)
        {
                return insert(doc);
        }

        return update(doc);
}

Doc InMemoryDocCollection::get(const std::string &id)
{
        return docs[id];
}

string InMemoryDocCollection::generateId()
{
        stringstream s;
        string id;

        s << docs.size();
        s >> id;

        return id;
}
