#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

using namespace std;
using namespace zxlib;

struct zscws_test
{
     zscws test_scws;
     zscws_test(){
          const char *charset = "utf8";
          const char *dict = "test/test_data/dict.short.xdb";
          int mode = SCWS_XDICT_XDB;
          test_scws.set_charset(charset);
          test_scws.set_dict( dict, mode);
     }

     void test_cws(const char *text, size_t size, const char **expected)
     {
          vector<string> res = test_scws.cws(string(text));
          BOOST_CHECK_EQUAL(res.size(),size);
          if(res.size() == size ){
               for( size_t i =0 ; i < size ; i++ ){
                    BOOST_CHECK( string(expected[i]) == res[i]);
               }
          }

     }
};

BOOST_FIXTURE_TEST_SUITE(mytest, zscws_test);

// test cws
BOOST_AUTO_TEST_CASE(Cws)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     const char* strs[]={"有人","的","地方","就有","江湖"};
     const char* text = "有人的地方就有江湖";
     test_cws(text, sizeof(strs)/sizeof(char*), strs);
}

BOOST_AUTO_TEST_SUITE_END();

/*
 * vim:ts=5:sw=5:
 */
