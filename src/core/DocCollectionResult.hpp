#ifndef HOSS_CORE_DOC_COLLECTION_RESULT_HPP
#define HOSS_CORE_DOC_COLLECTION_RESULT_HPP

#include <string>
#include <vector>

namespace hoss
{

namespace core
{

class DocCollectionResult
{
public:
        enum class Status
        {
                OK,
                NOT_FOUND
        };

        Status status() const;

        DocCollectionResult & status(Status status);

        operator bool() const;

        std::vector<std::string> ids();

        DocCollectionResult & ids(const std::vector<std::string> &idents);

private:
        Status s;
        std::vector<std::string> _ids;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_DOC_COLLECTION_RESULT_HPP */
