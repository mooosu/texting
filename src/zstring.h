#ifndef _ZSTRING_H_
#define _ZSTRING_H_

#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<map>

#include <pcre++.h>
#include <scws.h>

#include "ztype.h"
#include "zterm.h"
#include "unicode.h"
#include "zstrip.h"
#include "zutils.h"

#include "zterm.h"
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

               zstring to_norm() const;
               zstring strip() const;
               string join(const string_array &vec) const;
               term_array split_by_regexp(zpcre &zp, const string &str, TermType type = Matched) const;
               term_array split_by_regexp(zpcre &zp, TermType type = Matched) const;
               term_array cws_all(zscws &zs,vector<zpcre_type_pair> &zps, zpcre &rm);
               string to_string(){return m_text;}
     };

};

#endif
/*
 * vim:ts=5:sw=5:
 */
