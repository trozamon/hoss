#include "InMemoryDocStore.hpp"

using hoss::core::DocCollection;
using hoss::core::InMemoryDocCollection;
using hoss::core::InMemoryDocStore;
using std::shared_ptr;
using std::string;
using std::unordered_map;

InMemoryDocStore::InMemoryDocStore() :
        collections{new unordered_map<string, InMemoryDocCollection>()}
{
}

DocCollection & InMemoryDocStore::collection(const std::string &name)
{
        if (collections->count(name) == 0)
        {
                collections->insert({name, InMemoryDocCollection()});
        }

        return collections->at(name);
}
