#include "InMemoryDocStore.hpp"

using hoss::core::DocCollection;
using hoss::core::InMemoryDocCollection;
using hoss::core::InMemoryDocStore;
using std::shared_ptr;

InMemoryDocStore::InMemoryDocStore()
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
