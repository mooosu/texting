#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE zstring_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

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
     void test_cws_all(zscws &zs, const string &text, zpcre &rm, vector<pair<zpcre, TermType> > &zps){
          zstring zstr(text);
          vector<term> ret = zstr.cws_all(zs, rm, zps);
          cout << "test_cws_all" << endl;
          for (vector<term>::iterator i = ret.begin(); i != ret.end(); i++){
               cout << i->term_text << " " << i->term_type << endl;
          }
     }
};

BOOST_FIXTURE_TEST_SUITE(mytest, zstring_test);


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
     const char *charset = "utf8";
     const char *dict = "test/test_data/dict.short.xdb";
     int mode = SCWS_XDICT_XDB;
     zscws zs;
     zs.set_charset(charset);
     zs.set_dict( dict, mode);

     const string text = "　100　毫升…台式机250G硬盘4G内存21.5英寸30米液晶3.06GHz显示器";
     zpcre filter, unit, en;
     filter.load_file("test/test_data/symbol.txt");
     unit.load_file("test/test_data/unit.txt");
     en.load_file("test/test_data/en.txt");
     vector<pair<zpcre, TermType> > zps;
     zps.push_back( pair<zpcre, TermType>(unit, Unit) );
     zps.push_back( pair<zpcre, TermType>(en, En) );
     test_cws_all(zs,text,filter, zps);
}

BOOST_AUTO_TEST_SUITE_END();

/*
 * vim:ts=5:sw=5:
 */
