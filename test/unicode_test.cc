#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE unicode_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

using namespace std;
using namespace zxlib;

BOOST_AUTO_TEST_CASE(test_utf8_len)
{
     BOOST_CHECK_EQUAL(utf8_len("麦图科技",12),4);
}
BOOST_AUTO_TEST_CASE(test_calculate_sequence_length)
{
     BOOST_CHECK_EQUAL(zxlib::calculate_sequence_length((const unsigned char*)"ab",2),1);
     BOOST_CHECK_EQUAL(zxlib::calculate_sequence_length((const unsigned char*)"麦图科技",12),3);
}
