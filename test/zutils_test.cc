#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE zutils_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

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
BOOST_AUTO_TEST_CASE(test_calculate_sequence_length)
{
     BOOST_CHECK_EQUAL(zxlib::calculate_sequence_length((const unsigned char*)"ab",2),1);
}
BOOST_AUTO_TEST_CASE(test_znorm)
{
     
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"　",3),' ');
     BOOST_CHECK_EQUAL(dbc_utf8((unsigned char*)"\xc2\xa0",2),' ');
     const char* strs[]={"~!@#￥%…&*()/、‘’“”}{[]《》?`1234567890-=。　,",
          //           1  2     3 4567    8 9               1011
          "～！＠＃￥％…＆＊（）／、‘’“”｝｛［］《》？｀１２３４５６７８９０－＝。　，",
     };
     for( size_t k =0 ; k< sizeof(strs)/sizeof(char*) ; k++ ){
          size_t len  = strlen(strs[k]);
          string new_str = znorm((char*)strs[k],len);
          const char* expected = "~!@# % &*()/     }{[]  ?`1234567890-=  ,";
          for( size_t i = 0 ;i < strlen(expected) ; i++ ){
               BOOST_CHECK_EQUAL(new_str[i] , expected[i] );
          }
     }
     const char* n1="中文 asdfasdf英 文123汉字";
     BOOST_CHECK_EQUAL(string(n1),string(znorm((char*)n1,strlen(n1))));
}
BOOST_AUTO_TEST_CASE(test_find_isolate_chars)
{
     const char *chars[]={
          "今天","吃","喝","睡","闹","闲","很好","醒","了","就","出去","玩玩","哈"
     };
     string_vector strs;
     for( size_t i=0 ;i< sizeof(chars)/sizeof(char*);i++){
          strs.push_back(chars[i]);
     }
     vector<string_vector> found;
     BOOST_CHECK_EQUAL(zxlib::find_isolate_chars(strs,found),3);
     BOOST_CHECK_EQUAL( zxlib::join(found[0],","),string("吃,喝,睡,闹,闲"));
     BOOST_CHECK_EQUAL( zxlib::join(found[1],","),string("醒,了,就"));
     BOOST_CHECK_EQUAL( zxlib::join(found[2],","),string("哈"));
}
BOOST_AUTO_TEST_CASE(test_group_chars)
{
     const char *chars[]={
          "今天","a","bcd","吃","喝","睡","闹","闲","很好","醒","了","就","出去","玩玩","哈"
     };
     string_vector strs;
     for( size_t i=0 ;i< sizeof(chars)/sizeof(char*);i++){
          strs.push_back(chars[i]);
     }
     vector<string_vector> found;
     BOOST_CHECK_EQUAL(zxlib::find_isolate_chars(strs,found),3);

     BOOST_CHECK_EQUAL( zxlib::join(found[0],","),string("吃,喝,睡,闹,闲"));
     BOOST_CHECK_EQUAL( zxlib::join(found[1],","),string("醒,了,就"));
     BOOST_CHECK_EQUAL( zxlib::join(found[2],","),string("哈"));
     string_vector groups;
     BOOST_CHECK_EQUAL(group_chars( found[0],2,groups),2);
     BOOST_CHECK_EQUAL(groups[0],string("吃喝"));
     BOOST_CHECK_EQUAL(groups[1],string("睡闹闲"));
     groups.clear();
     BOOST_CHECK_EQUAL(group_chars( found[1],2,groups),1);
     BOOST_CHECK_EQUAL(groups[0],string("醒了就"));
     groups.clear();
     BOOST_CHECK_EQUAL(group_chars( found[2],2,groups),1);
     BOOST_CHECK_EQUAL(groups[0],string("哈"));
     groups.clear();


     //3
     BOOST_CHECK_EQUAL(group_chars( found[0],3,groups),2);
     BOOST_CHECK_EQUAL(groups[0],string("吃喝睡"));
     BOOST_CHECK_EQUAL(groups[1],string("闹闲"));
     groups.clear();
     BOOST_CHECK_EQUAL(group_chars( found[1],3,groups),1);
     BOOST_CHECK_EQUAL(groups[0],string("醒了就"));
     groups.clear();
     BOOST_CHECK_EQUAL(group_chars( found[2],3,groups),1);
     BOOST_CHECK_EQUAL(groups[0],string("哈"));
}
BOOST_AUTO_TEST_CASE(test_load_yaml)
{
     struct myconfig:zconfig_yaml{
          string dict_path;
          string host;
          int port;
          string field;
          string collection;
          void set_config(const YAML::Node& node )
          {
               node["dict_path"]>> dict_path;
               node["host"]>> host;
               node["port"]>> port;
               node["field"]>> field;
               node["collection"]>> collection;
          }
          void inspect()
          {
               cout << "dict_path:" << dict_path << endl;
               cout << "host:" << host << endl;
               cout << "port:" << port << endl;
               cout << "field:" << field << endl;
               cout << "collection:" << collection << endl;
          }
     }cfg;
     zxlib::load_yaml("test/test.yml",cfg);
     BOOST_CHECK_EQUAL(cfg.dict_path,"/tmp/mydict.xdb");
     BOOST_CHECK_EQUAL(cfg.host,"192.168.1.86");
     BOOST_CHECK_EQUAL(cfg.port,27017);
     BOOST_CHECK_EQUAL(cfg.field,"atext");
     BOOST_CHECK_EQUAL(cfg.collection,"count_word.download");
}
BOOST_AUTO_TEST_CASE(test_join_isolated_chars)
{
     test_data cases[]={
          {"CLASS 6","CLASS6"},
          {"a b c","abc"},
          {"a bc","abc"},
          {"ab bc","ab bc"},
          {"S PU 索浦","SPU 索浦"},
          {"畅 e 行","畅e行"},
          //{"蓝牙 V2.1","蓝牙 V2.1"},
          {"I Tech","ITech"},
          {"CF 卡","CF 卡"},
          {"电水壶 电水瓶","电水壶电水瓶"},
          {"python cook","python cook"},
          {"A-B-C","A-B-C"},
          {"           ",""},
          {"      1     ","1"},
          {"     1     ","1"},
          {"     1    ","1"},
          {"a o sd 1 3 4 sd t y i kjk","ao sd 134 sd tyi kjk"},
          {"a o smith","ao smith"},
          {"dfs a o smith","dfs ao smith"},
          {"dfs a o","dfs ao"},
          {"AD FD dfs a o 1 3 4   smith","AD FD dfs ao134 smith"},
          {"a o 1 3 4   smith","ao134 smith"},
          {"AD FD dfs a o 1 3 4","AD FD dfs ao134"},
          {"    adsf  34  a o 1 3 4      ","adsf 34 ao134"},
          {" a o 1 3 4","ao134"},
          {"   a o 1 3 4","ao134"},
          {"   a o  lllll 1 3 4","ao lllll 134"},
          {"   a o  找  呀 1 3 4  搜索  sdf3 2 d  g t","ao找呀134搜索 sdf3 2dgt"}
     };
     zpcre filter;
     filter.load_file("./src/symbol.txt");
     char buffer[1024];
     BOOST_CHECK_EQUAL(char_joiner<>::max_size(),32*1024);
     BOOST_CHECK_EQUAL(char_joiner<333>::max_size(),333);
     for( size_t i =0 ; i < sizeof(cases) / sizeof(test_data ) ; i ++ ){
          char* tmp = (char*)cases[i].value;
          string str= tmp;
          const char *res = char_joiner<>(str).join();
          BOOST_CHECK_EQUAL(string(res),string(cases[i].expected));
     }
}
