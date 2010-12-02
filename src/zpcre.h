#ifndef _ZPCRE_H_
#define _ZPCRE_H_

#include <string>
#include <vector>
#include <pcre++.h>
#include "zterm.h"

using namespace std;
using namespace pcrepp;

namespace zxlib {
     static Pcre reg_left_strip    = Pcre("(^[\\s\\t\\r\\n]+)");
     static Pcre reg_right_strip   = Pcre("([\\s\\t\\r\\n]+$)");
     static Pcre reg_split_default = Pcre("[\\s\\t\\r\\n]+");

     class zpcre {
          private:
               string m_expression;
               string m_flags;
               Pcre m_reg;
          public:
               zpcre();
               zpcre(const string &exp);
               zpcre(const string &exp, const string &flags);
               ~zpcre();
               vector<term> split(const string &text);
               string replace(const string &text, const string &with);
               string remove(const string &text);
     };

};

#endif
/*
 * vim:ts=5:sw=5:
 */
