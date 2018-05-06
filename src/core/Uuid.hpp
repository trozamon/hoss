#ifndef HOSS_CORE_UUID_HPP
#define HOSS_CORE_UUID_HPP

#include <string>

namespace hoss
{

namespace core
{

/**
 * Wrapper around a UUID.
 *
 * UUIDs are 16-byte binary chunks. The "pretty" form is like so:
 *
 *     92866d50-e28b-41d2-ba90-a1cbcdd50453
 */
class Uuid
{
public:
        static const size_t LEN = 16;

        /**
         * Generates a new UUID.
         */
        Uuid();

        /**
         * Wrap an existing UUID (in unparsed form).
         */
        Uuid(const std::string &uuid);

        /**
         * Wrap an existing UUID (in parsed form).
         */
        Uuid(const unsigned char *uuid);

        /**
         * Generate a pretty string.
         */
        std::string pretty() const;

private:
        unsigned char _uuid[LEN];
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_UUID_HPP */
