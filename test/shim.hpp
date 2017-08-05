#ifndef HOSS_TEST_SHIM_HPP
#define HOSS_TEST_SHIM_HPP

#include "core/Message.hpp"
#include <boost/test/included/unit_test.hpp>

namespace hoss
{

namespace core
{

std::ostream & operator<<(std::ostream &stream,
                const hoss::core::MessageType &mt)
{
        stream << static_cast<int>(mt);
        return stream;
}

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_TEST_SHIM_HPP */
