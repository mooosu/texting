#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE zstring_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "zstring.h"

using namespace std;
using namespace zxlib;

struct zstring_test
{
     string m_text;
     zstring_test()
     {
          m_text="台式机250G硬盘4G内存21.5英寸液晶显示器";
     }
     zstring_test(const char* str):m_text(str){};
     zstring_test(string str):m_text(str){};

     ~zstring_test()
     {
     }

     void test_split_by_re(zstring& str,const char* re,size_t size ,const char** expected_strs)
     {
          vector<term> strs = str.split_by_re(re);
          BOOST_CHECK_EQUAL(strs.size(),size);
          if(strs.size() == size ){
               for( size_t i =0 ; i < size ; i++ ){
                    BOOST_CHECK( string(expected_strs[i]) == strs[i].term_text );
               }
          }

     }
     void test_strip(zstring &str, string &s)
     {
          BOOST_CHECK( str.strip() == s );
     }
     void test_split(zstring &str, size_t size, const char **vec)
     {
          vector<string> strs = str.split();
          BOOST_CHECK_EQUAL(strs.size(),size);
          if(strs.size() == size ){
               for( size_t i =0 ; i < size ; i++ ){
                    BOOST_CHECK( string(vec[i]) == strs[i] );
               }
          }
     }
     void test_join(zstring &str, const vector<string> &vec, const char *res)
     {
          BOOST_CHECK( str.join(vec) == string(res) );
     }
};

BOOST_FIXTURE_TEST_SUITE(mytest, zstring_test);

// test split by re
BOOST_AUTO_TEST_CASE(SplitByRe)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     zstring str(m_text);
     const char* strs[]={"台式机","250G","硬盘","4G","内存","21",".","5","英寸液晶显示器"};
     test_split_by_re(str,"(?i)([a-z0-9]+)",9,strs);
}

// test strip string
BOOST_AUTO_TEST_CASE(Strip)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     zstring str(" \r台式机    250G英寸液晶显示器  \n");
     string striped = "台式机    250G英寸液晶显示器";
     test_strip(str, striped);
}

// test split string
BOOST_AUTO_TEST_CASE(Split)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     zstring str("\n     台式机 250G    硬盘 4G 内存\r\n21 . 5 英寸液晶显示器    \r\n");
     const char* strs[]={"台式机","250G","硬盘","4G","内存","21",".","5","英寸液晶显示器"};
     test_split(str,9,strs);

     zstring str1("\n     台式机 250G    硬盘 4G 内存\r\n21 . 5 英寸液晶显示器    \r\n");
     const char* strs1[]={"台式机","250G","硬盘","4G","内存","21.5","英寸","液晶显示器"};
     test_split(str1,sizeof(strs1)/sizeof(char*),strs);
}

// test join string array
BOOST_AUTO_TEST_CASE(Join)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     zstring str(" ");
     vector<string> vec;
     vec.push_back("台式机");
     vec.push_back("250G");
     vec.push_back("英寸");
     vec.push_back("液晶");
     vec.push_back("显示器"); 
     const char *res = "台式机 250G 英寸 液晶 显示器";
     test_join(str,vec,res);
}

BOOST_AUTO_TEST_SUITE_END();

/*
 * vim:ts=5:sw=5:
 */
