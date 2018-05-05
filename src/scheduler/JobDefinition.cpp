#include "JobDefinition.hpp"

using hoss::scheduler::JobDefinition;
using std::string;

JobDefinition & JobDefinition::id(const string &id)
{
        _id = id;
        return *this;
}

JobDefinition & JobDefinition::sourceType(const string &type)
{
        _sourceType = type;
        return *this;
}

JobDefinition & JobDefinition::sourceUri(const string &uri)
{
        _sourceUri = uri;
        return *this;
}

JobDefinition & JobDefinition::buildType(const string &type)
{
        _buildType = type;
        return *this;
}

const string & JobDefinition::id() const
{
        return _id;
}
