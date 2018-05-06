#include "Uuid.hpp"
#include <stdexcept>
#include <string.h>
#include <uuid.h>

using hoss::core::Uuid;
using std::invalid_argument;
using std::string;

Uuid::Uuid()
{
        uuid_generate(_uuid);
}

Uuid::Uuid(const string &uuid)
{
        int err = uuid_parse(uuid.c_str(), _uuid);

        if (err)
        {
                throw invalid_argument{"UUID " + uuid +
                        " is not the correct format"};
        }
}

Uuid::Uuid(const unsigned char *uuid)
{
        memcpy(_uuid, uuid, LEN);
}

string Uuid::pretty() const
{
        char pretty[UUID_STR_LEN];

        uuid_unparse_lower(_uuid, pretty);

        return string{pretty};
}
