#include "DocCollectionResult.hpp"

using hoss::core::DocCollectionResult;
using std::string;
using std::vector;

vector<string> DocCollectionResult::ids()
{
        return _ids;
}

DocCollectionResult & DocCollectionResult::ids(const vector<string> &idents)
{
        _ids = idents;
        return *this;
}

DocCollectionResult::Status DocCollectionResult::status() const
{
        return s;
}

DocCollectionResult & DocCollectionResult::status(Status status)
{
        s = status;
        return *this;
}

DocCollectionResult::operator bool() const
{
        return s == Status::OK;
}
