#include <core/InMemoryDocCollection.hpp>
#include "shim.hpp"

using boost::any_cast;
using hoss::core::Doc;
using hoss::core::InMemoryDocCollection;
using std::string;

class Fixture
{
public:
        InMemoryDocCollection coll;
};

BOOST_AUTO_TEST_CASE(addAndGet)
{
        Fixture f;
        Doc d;

        auto res = f.coll.insert(d);

        BOOST_CHECK(res);
        BOOST_CHECK_EQUAL(1, res.ids().size());
        BOOST_CHECK_EQUAL("0", res.ids().at(0));

        auto doc = f.coll.get("0");

        BOOST_CHECK_EQUAL("0", doc.id());
}

BOOST_AUTO_TEST_CASE(update)
{
        Fixture f;
        Doc d;

        auto res = f.coll.insert(d);

        BOOST_CHECK(res);
        BOOST_CHECK_EQUAL(1, res.ids().size());
        BOOST_CHECK_EQUAL("0", res.ids().at(0));

        d.id(res.ids().at(0));
        d["a"] = string{"b"};
        res = f.coll.update(d);

        BOOST_CHECK(res);

        auto doc = f.coll.get("0");

        BOOST_CHECK_EQUAL("0", doc.id());
        BOOST_CHECK_EQUAL("b", any_cast<string>(doc["a"]));
}

BOOST_AUTO_TEST_CASE(upsert)
{
        Fixture f;
        Doc d;

        auto res = f.coll.upsert(d);

        BOOST_CHECK(res);
        BOOST_CHECK_EQUAL(1, res.ids().size());
        BOOST_CHECK_EQUAL("0", res.ids().at(0));

        d.id(res.ids().at(0));
        d["a"] = string{"b"};
        res = f.coll.upsert(d);

        BOOST_CHECK(res);

        auto doc = f.coll.get("0");

        BOOST_CHECK_EQUAL("0", doc.id());
        BOOST_CHECK_EQUAL("b", any_cast<string>(doc["a"]));
}
