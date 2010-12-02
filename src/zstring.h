#ifndef _ZSTRING_H_
#define _ZSTRING_H_

#include "zutils.h"
#include "zstrip.h"
#include "zscws.h"
#include "zpcre.h"

using namespace std;

namespace zxlib{
     class zstring{
          private:
               string m_text;
          public:
               zstring(){};
               zstring(const char* text):m_text(text){};
               zstring(string text):m_text(text){};

               //vector<term> split_by_re(const char* re, TermType type=Unknow) const;
               //vector<term> split_by_re(Pcre &reg, TermType type=Unknow) const;

               string strip() const;
               vector<string> split() const;
               string join(const vector<string> &vec) const;
               vector<term> cws_all(zpcre &unit, zpcre &rm, zscws &zs);
     };
};

#endif
/*
 * vim:ts=5:sw=5:
 */
