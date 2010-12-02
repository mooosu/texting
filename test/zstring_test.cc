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
          m_text="";
     }
     zstring_test(const char* str):m_text(str){};
     zstring_test(string str):m_text(str){};

     ~zstring_test()
     {
     }

     /*
     void test_split_by_re(zstring& str,const char* re,size_t size ,const char** expected_strs)
     {
          vector<term> strs = str.split_by_re(re);
          for( size_t i =0 ; i < strs.size(); i++ ){
               //cout << strs[i].term_text << endl;
          }
          BOOST_CHECK_EQUAL(strs.size(),size);
          if(strs.size() == size ){
               for( size_t i =0 ; i < size ; i++ ){
                    BOOST_CHECK( string(expected_strs[i]) == strs[i].term_text );
               }
          }

     }*/
     void test_re_split(const string &exp, const string &text, size_t size, const char **expected_strs)
     {
          zpcre reg(exp);
          vector<term> ret = reg.split(text);
          for( size_t i =0 ; i < ret.size(); i++ ){
               //cout << ret[i].term_text << endl;
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
     void test_re_replace(const string &exp, const string &piece, const string &with, const string &expected)
     {
          zpcre zp(exp,"g");
          string ret = zp.replace(piece, with);
          BOOST_CHECK( ret == expected );
     }
     void test_cws_all(const string &unit, const string &rm, zscws &zs, const string &text){
          zstring zstr(text);
          zpcre zpunit(unit);
          zpcre zprm(rm);
          vector<term> ret = zstr.cws_all(zpunit, zprm, zs);
          for (vector<term>::iterator i = ret.begin(); i != ret.end(); i++){
               cout << i->term_text << " " << i->term_type << endl;
          }
     }
};

BOOST_FIXTURE_TEST_SUITE(mytest, zstring_test);

/*
// test split by re
BOOST_AUTO_TEST_CASE(SplitByRe)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     zstring str1("100毫升台式机250G硬盘4G内存21.5英寸30米液晶3.06GHz显示器");
     const char* strs1[]={"100毫升","台式机","250G","硬盘","4G","内存","21.5英寸","30米","液晶","3.06GHz","显示器"};
     const char* exp = "(?i)(?<![0-9a-z\\-])((?:\\d+(?:\\.\\d*)?|\\.\\d+)\\s*(K金|毫升|英寸|克拉|百兆|千兆|米|联|座|芯|瓦|孔|条|针|列|颗|节|匹|张|分|款|号|粒|只|件|匹|升|个|码|片|层|速|转|寸|位|万|倍|克|口|重|枚|兆|代|((CM|MM|GHz|(bit)|B)|(T|G|M|K)B?)(?=[^0-9a-z+-])))";
     test_split_by_re(str1,exp,sizeof(strs1)/sizeof(char*),strs1);
}*/

BOOST_AUTO_TEST_CASE(ReSplit)
{
     BOOST_REQUIRE(true);   // Stop here if it fails.
     const string text = "100毫升台式机250G硬盘4G内存21.5英寸30米液晶3.06GHz显示器";
     const char* strs1[]={"100毫升","台式机","250G","硬盘","4G","内存","21.5英寸","30米","液晶","3.06GHz","显示器"};
     const string exp = "(?i)(?<![0-9a-z\\-])((?:\\d+(?:\\.\\d*)?|\\.\\d+)\\s*(K金|毫升|英寸|克拉|百兆|千兆|米|联|座|芯|瓦|孔|条|针|列|颗|节|匹|张|分|款|号|粒|只|件|匹|升|个|码|片|层|速|转|寸|位|万|倍|克|口|重|枚|兆|代|((CM|MM|GHz|(bit)|B)|(T|G|M|K)B?)(?=[^0-9a-z+-])))";
     test_re_split(exp,text,sizeof(strs1)/sizeof(char*),strs1);
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

BOOST_AUTO_TEST_CASE(ReReplace)
{
     const string exp = "([\\\\~`!@$%\\(\\)\\{\\}\\[\\]=\"\';:,<>?|^])";
     const string piece = "hellom2@%.com";
     const string with = "";
     test_re_replace(exp, piece, with, "hellom2.com");
}

BOOST_AUTO_TEST_CASE(ZscwsAll)
{
     const string unit= "(?i)(?<![0-9a-z\\-])((?:\\d+(?:\\.\\d*)?|\\.\\d+)\\s*(K金|毫升|英寸|克拉|百兆|千兆|米|联|座|芯|瓦|孔|条|针|列|颗|节|匹|张|分|款|号|粒|只|件|匹|升|个|码|片|层|速|转|寸|位|万|倍|克|口|重|枚|兆|代|((CM|MM|GHz|(bit)|B)|(T|G|M|K)B?)(?=[^0-9a-z+-])))";
     const string rm = "";
     const char *charset = "utf8";
     const char *dict = "../../zhaolibs/dictlab/dict.short.xdb";
     int mode = SCWS_XDICT_XDB;
     zscws zs;
     zs.set_charset(charset);
     zs.set_dict( dict, mode);
     const string text = "　100　毫…升…台式机250G硬盘4G内存21.5英寸30米液晶3.06GHz显示器";
     test_cws_all(unit, rm, zs, text);
}

BOOST_AUTO_TEST_SUITE_END();

/*
 * vim:ts=5:sw=5:
 */
