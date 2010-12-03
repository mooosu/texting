#ifndef _ZSTRING_H_
#define _ZSTRING_H_

#include<stdio.h>
#include<cstring>
#include<stdlib.h>

#include <pcre++.h>
#include <scws.h>

#include "ztype.h"
#include "zterm.h"
#include "unicode.h"

#include "zstrip.h"
#include "zutils.h"
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
               string to_string(){return m_text;}
               zstring to_norm();
     };
};

#endif
/*
 * vim:ts=5:sw=5:
 */
