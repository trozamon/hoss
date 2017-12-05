#include "core/Doc.hpp"
#include "shim.hpp"

using boost::any_cast;
using hoss::core::Doc;
using std::string;

BOOST_AUTO_TEST_CASE(id)
{
        Doc d;

        d.id("jfkldsajlkfdsa");

        BOOST_CHECK_EQUAL("jfkldsajlkfdsa", d.id());
}

BOOST_AUTO_TEST_CASE(emptyId)
{
        Doc d;

        BOOST_CHECK_EQUAL("", d.id());
}

BOOST_AUTO_TEST_CASE(ints)
{
        Doc d;

        d.id("blah");
        d["hey"] = 1;

        BOOST_CHECK_EQUAL(1, any_cast<int>(d["hey"]));
}

BOOST_AUTO_TEST_CASE(strings)
{
        Doc d;

        d.id("blah");
        d["hey"] = string{"roar"};

        BOOST_CHECK_EQUAL("roar", any_cast<string>(d["hey"]));
}
