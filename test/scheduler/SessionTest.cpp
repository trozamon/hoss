#include "scheduler/Session.hpp"
#include "shim.hpp"

using hoss::scheduler::Session;

BOOST_AUTO_TEST_CASE(keyEquality)
{
        Session::Key a{"hoss.example.com", 9001};
        Session::Key b{"hoss.example.com", 4556};

        BOOST_CHECK(a != b);

        b = Session::Key{"hoss.example.com", 9001};

        BOOST_CHECK(a == b);
}
