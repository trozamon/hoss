#ifndef HOSS_CORE_INMEMORY_DOCSTORE_HPP
#define HOSS_CORE_INMEMORY_DOCSTORE_HPP

#include "DocStore.hpp"
#include "InMemoryDocCollection.hpp"

namespace hoss
{

namespace core
{

class InMemoryDocStore : public DocStore
{
public:
        InMemoryDocStore();

        virtual DocCollection & collection(const std::string &name);

private:
        std::shared_ptr<
                std::unordered_map<std::string, InMemoryDocCollection>
                > collections;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_INMEMORY_DOCSTORE_HPP */
