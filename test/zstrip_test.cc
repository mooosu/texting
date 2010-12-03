#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "zstring.h"

using namespace std;
using namespace zxlib;
typedef struct {
     char value[256];
     const char *expected;
}test_data;

BOOST_AUTO_TEST_CASE(is_space)
{
     BOOST_CHECK(zis_space(" ",1));
     BOOST_CHECK(zis_space("　",3));
}
BOOST_AUTO_TEST_CASE(test_zltrim)
{
     test_data cases[]={
          {"1231231","1231231"},
          {" 1231231","1231231"},
          {"  1231231","1231231"},
          {"   1231231","1231231"},
          {"    12   31231","12   31231"},
     };
     
     for( size_t i =0 ; i < sizeof(cases) / sizeof(test_data ) ; i ++ ){
          char* tmp = (char*)cases[i].value;
          BOOST_CHECK_EQUAL(string(zltrim(tmp,strlen(tmp))),string(cases[i].expected));
     }
}
BOOST_AUTO_TEST_CASE(test_zrtrim)
{
     test_data cases[]={
          {"1231231","1231231"},
          {"1231231 ","1231231"},
          {"1231231  ","1231231"},
          {"1231231   ","1231231"},
          {"12   31231   ","12   31231"},
     };
     
     for( size_t i =0 ; i < sizeof(cases) / sizeof(test_data ) ; i ++ ){
          char* tmp = (char*)cases[i].value;
          BOOST_CHECK_EQUAL(string(zrtrim(tmp,strlen(tmp))),string(cases[i].expected));
     }
}

