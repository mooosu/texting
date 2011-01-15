#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ztexting_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

using namespace std;
using namespace zxlib;

typedef struct {
     char value[256];
     const char *expected;
}test_data;

BOOST_AUTO_TEST_CASE( test_singleton )
{
     // should compiler error( ‘zxlib::ztexting::ztexting(zxlib::ztexing_config&)’ is protected )
     //ztexing_config config;
     //ztexting texting(config);;
}
BOOST_AUTO_TEST_CASE(test_ztexting_init)
{
     ztexting::init("test/test_ztexting_init.yml");
     ztexting* inst = ztexting::instance();
     BOOST_CHECK_EQUAL(inst->dict_file(),"test/test_data/dict.short.xdb");
     BOOST_CHECK_EQUAL(inst->symbol_file(),"test/test_data/symbol.txt");
     BOOST_CHECK_EQUAL(inst->unit_file(),"test/test_data/unit.txt");
     BOOST_CHECK_EQUAL(inst->en_file(),"test/test_data/en.txt");
}
BOOST_AUTO_TEST_CASE(test_ztexting_parse_stmt)
{
     test_data cases[]={
          //{"Crest 佳洁士 全优7效牙刷","ddd"},
          {"包邮！销量7300台！首信 S718 老人手机 正品行货 黑色 白色","包邮:销量:7300台:首信:S718:老人:手机:正品:行货:黑色:白色"},
          {"台式机250G硬盘","台式机:250G:硬盘"}
     };

     for( size_t i = 0 ;i< sizeof(cases)/sizeof(test_data) ; i++ ){
          zstmt stmt = ztexting::instance()->parse_stmt(cases[i].value);
          term_array &tas = stmt.get_terms();
          string_vector tmp;
          for( size_t n =0 ; n < tas.size(); n++){
               tmp.push_back(tas[n].term_text);
          }
          string str = zxlib::join(tmp,":");
          BOOST_CHECK_EQUAL(str,string(cases[i].expected));
     }
}
