#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "zscws.h"

using namespace std;
using namespace zxlib;

struct zscws_test
{
     scws test_scws;
     zscws_test(){
          const char *charset = "UTF-8";
          const char *dict = "/home/xuyu/zhaoia_work/zhaolibs/dictlab/dict.short.xdb";
          int mode = SCWS_XDICT_XDB;
          test_scws = scws(charset, dict, mode);
     }

     void test_cws(const char *text, size_t size, const char **expected)
     {
          vector<string> res = test_scws.cws(text);
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
/*
BOOST_AUTO_TEST_CASE(Cws)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     const char* strs[]={"有人","的","地方","就有","江湖"};
     test_cws("有人的地方就有江湖", 5, strs);
}
*/

BOOST_AUTO_TEST_SUITE_END();

/*
 * vim:ts=5:sw=5:
 */
