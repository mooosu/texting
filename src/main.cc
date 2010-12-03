#include "zstring.h"
#include <iostream>
#include <assert.h>

using namespace std;
using namespace zxlib;

void print_ret( vector<term> &ret ){
     for (vector<term>::iterator i = ret.begin(); i != ret.end(); i++){
          cout << " " << i->term_text << "[" << i->term_type << "]";
     }
     cout << endl;
}

int main(){
     /*
        assert(zpcre("([\xE4\xB8\x80-\xE9\xBE\xA5]+)","ig").replace("中国China","#") == "#China");
        assert(zpcre("([0-9]+)","g").replace("20支装","#") == "#支装");
        assert(zpcre("([0-9]+\\.[0-9]+)","g").replace("3.06GHz","#") == "#GHz");
        assert(zpcre("([0-9]+x[0-9]+)","g").replace("4x2包","#") == "#包");
        assert(zpcre("(v领)","gi").replace("V领夹克","#") == "#夹克");
        assert(zpcre("([a-z0-9\\+]+)","gi").replace("PA+++","#") == "#");
        assert(zpcre("([a-z0-9]+/(?![0-9a-z]{2})[a-z0-9])","gi").replace("MP3/4","#") == "#");
        assert(zpcre("((?<![a-z0-9])[a-z0-9]{1}\\-[a-z0-9]*)","gi").replace("a-cdf","#") == "#");
        assert(zpcre("([a-z0-9]+\\-[a-z0-9](?![a-z0-9]))","gi").replace("abc-d","#") == "#");
        assert(zpcre("((?<=[a-z])\\.(?=[a-z]))","gi").replace("A.B.C","") == "ABC");
        */
     zscws zs("UTF-8", "/home/xuyu/zhaoia_work/zhaolibs/dictlab/dict.short.xdb", SCWS_XDICT_XDB);
     zs.set_ignore(true);
     vector<pair<zpcre, TermType> > zps;
     zps.push_back( pair<zpcre, TermType>(UnitExt, Unit) );
     zps.push_back( pair<zpcre, TermType>(EnExt, En) );
     char input_string[1024];
     vector<term> ret;
     while (true){
          cin.getline(input_string, 1024);
          ret = zstring(input_string).cws_all(zs, zps, SymbolFilter);
          print_ret( ret );
     }
     return 0;
}
/*
 * vim:ts=5:sw=5:
 */
