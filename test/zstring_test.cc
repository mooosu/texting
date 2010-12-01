#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE zstring_test
#include <boost/test/unit_test.hpp>
#include "zstring.h"

using namespace std;
using namespace zxlib;

struct zstring_test
{
     string m_text;
     zstring_test()
     {
          // TODO: Common set-up each test case here.
          m_text="台式机250G硬盘4G内存21.5英寸液晶显示器";
     }
     zstring_test(const char* str):m_text(str){};

     ~zstring_test()
     {
          // TODO: Common tear-down for each test case here.
     }

     // TODO: Possibly put some common tests.
     void test_split_by_re(zstring& str,const char* re,size_t size ,const char** expected_strs)
     {
          vector<string> strs = str.split_by_re(re);
          BOOST_CHECK_EQUAL(strs.size(),size);
          if(strs.size() == size ){
               for( size_t i =0 ; i < size ; i++ ){
                    BOOST_CHECK( string(expected_strs[i]) == strs[i] );
               }
          }

     }

     // TODO: Declare some common values accesses in tests here.
};

BOOST_FIXTURE_TEST_SUITE(mytest, zstring_test);

BOOST_AUTO_TEST_CASE(SplitTextByRe)
{
     zstring str(m_text);
     BOOST_REQUIRE(true);   // Stop here if it fails.
     const char* strs[]={"台式机","250G","硬盘4G内存21.5英寸液晶显示器"};
     test_split_by_re(str,"(250G)",3,strs);
     //BOOST_CHECK_THROW(foo.Save(nullptr), exception);
}
BOOST_AUTO_TEST_SUITE_END();

