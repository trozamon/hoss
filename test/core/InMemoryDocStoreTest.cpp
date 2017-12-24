#include <core/InMemoryDocStore.hpp>
#include "shim.hpp"

using boost::any_cast;
using hoss::core::Doc;
using hoss::core::DocCollection;
using hoss::core::InMemoryDocStore;
using std::string;

BOOST_AUTO_TEST_CASE(collection)
{
        InMemoryDocStore s;
        DocCollection &coll = s.collection("test");
        Doc d;

        auto res = coll.insert(d);

        BOOST_CHECK(res);

        DocCollection &coll2 = s.collection("test");

        Doc d2 = coll2.get("0");

        BOOST_CHECK_EQUAL("0", d2.id());
}
