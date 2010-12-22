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

BOOST_AUTO_TEST_CASE(test_get_terms)
{

     const char *charset = "utf8";
     const char *dict = "../../zhaolibs/dictlab/dict.short.xdb";
     int mode = SCWS_XDICT_XDB;
     zscws zs;
     zs.set_charset(charset);
     zs.set_dict( dict, mode);

     test_data cases[]={
          {"台式机250G硬盘","台式机:250G:硬盘"}
     };
     zpcre filter, unit, en;
     filter.load_file("./src/symbol.txt");
     unit.load_file("./src/unit.txt");
     en.load_file("./src/en.txt");
     vector<pair<zpcre, TermType> > zps;
     zps.push_back( pair<zpcre, TermType>(unit, Unit) );
     zps.push_back( pair<zpcre, TermType>(en, En) );
     for( size_t i = 0 ;i< sizeof(cases)/sizeof(test_data) ; i++ ){
          zstmt stmt( cases[i].value,zps,SubStmt);
          stmt.parse( filter);
          term_array &tas = stmt.get_terms();
          string_vector tmp;
          for( size_t n =0 ; n < tas.size(); n++){
               tmp.push_back(tas[n].term_text);
          }
          string str = zxlib::join(tmp,":");
          BOOST_CHECK_EQUAL(str,string(cases[i].expected));
     }
}


