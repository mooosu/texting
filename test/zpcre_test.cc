#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "zstring.h"

using namespace std;
using namespace zxlib;
using namespace pcrepp;

BOOST_AUTO_TEST_CASE(match)
{
    zpcre zp("([0-9]+)");
    BOOST_CHECK( zp.match("2009") );
    BOOST_CHECK( !zp.match("a2009") );
}

BOOST_AUTO_TEST_CASE(Remove)
{
    zpcre zp("([\\\\~`!@$%\\(\\)\\{\\}\\[\\]=\"';:,<>?|^]|/(?=[a-z0-9\xE4\xB8\x80-\xE9\xBE\xA5]{2,})|/$|(?<=[^a-z0-9+])\\+)","gi");
    BOOST_CHECK_EQUAL( zp.remove("^%$@@!/"),"" );
}
