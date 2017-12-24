#ifndef HOSS_CORE_DOC_STORE_HPP
#define HOSS_CORE_DOC_STORE_HPP

#include "DocCollection.hpp"
#include <memory>

namespace hoss
{

namespace core
{

/**
 * Wrapper around a document store.
 *
 * Documents symbolizing job state, workflow state, etc. can be stored in here.
 */
class DocStore
{
public:
        /**
         * Get a reference to a collection.
         *
         * @param collection Collection name
         * @param doc A document
         */
        virtual DocCollection & collection(const std::string &name) = 0;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_DOC_STORE_HPP */
