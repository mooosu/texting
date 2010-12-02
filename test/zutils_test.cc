#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "zutils.h"

using namespace std;
using namespace zxlib;
typedef struct {
     char value[256];
     const char *expected;
}test_data;

BOOST_AUTO_TEST_CASE(is_dbc_utf8)
{
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"　",3),' ');
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"\xc2\xa0",2),' ');
     unsigned char buffer[256];
     memcpy(buffer,"\xc2\xa0",3);
     BOOST_CHECK_EQUAL(zxlib::calculate_sequence_length((const unsigned char*)buffer,2),2);
}
BOOST_AUTO_TEST_CASE(test_znorm)
{
     
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"　",3),' ');
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"\xc2\xa0",2),' ');
     unsigned char buffer[256];
     //                   1  2     3 4567    8 9               1011
     const char* str="~!@#￥%…&*()/、‘’“”}{[]《》?`1234567890-=。　,";
     size_t len  = strlen(str);
     memcpy(buffer,str,len+1);
     char* new_str = znorm((char*)str,len);
     const char* expected = "~!@# % &*()/     }{[]  ?`1234567890-=  ,";
     for( size_t i = 0 ;i < strlen(expected) ; i++ ){
          BOOST_CHECK_EQUAL(new_str[i] , expected[i] );
     }
}
