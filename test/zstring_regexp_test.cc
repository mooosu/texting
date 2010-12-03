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

BOOST_AUTO_TEST_CASE(test_to_norm)
{

     test_data cases[]={
          {"ICEDX-B-C","ICEDX-B-C"},
          {"t5740W(VS504PC)","t5740W VS504PC"},
          {"MP3/Mp4" ,"MP3 Mp4"},
          {"MP3\\Mp4","MP3 Mp4"},
          {"MP3\\Mp4","MP3 Mp4"},
          {"MP3/4","MP3/4"},
          {"电水壶／电水瓶", "电水壶电水瓶"},
          {"/电水瓶/","电水瓶"},
          {"siemens 索尼（Sony）Nokia n97 诺基亚 n97" ,"siemens 索尼 Sony Nokia n97 诺基亚 n97"},
          {"siemens 索尼《Sony》Nokia n97 诺基亚 n97" ,"siemens 索尼 Sony Nokia n97 诺基亚 n97"},
          {"EM・ONE" ,"EM ONE"},
          {"TP－LINK","TP-LINK"},
          {"乔治·阿玛尼" ,"乔治阿玛尼"},
          {"00PT.SEG0C", "00PT SEG0C"},
          {"1.2","1.2"},
          {"Z－TEK", "Z-TEK"},
          {"ThinkPad （IBM）","ThinkPad IBM"},
     };
     char buffer[1024];
     for( size_t i =0 ; i < sizeof(cases) / sizeof(test_data ) ; i ++ ){
          char* tmp = (char*)cases[i].value;
          zstring(tmp).to_norm().to_string();
          printf("cases[i].expected %s\n",cases[i].expected);
          BOOST_CHECK_EQUAL(zstring(tmp).to_norm().to_string(),string(cases[i].expected));
     }
}

