#ifndef _ZPCRE_H_
#define _ZPCRE_H_
#include "common.h"
#include "zterm.h"
#include "zutils.h"

namespace zxlib {
     class zpcre {
          private:
               string m_expression;
               string m_flags;
               pcrepp::Pcre m_reg;
          public:
               zpcre();
               zpcre(const string &exp);
               zpcre(const string &exp, const string &flags);
               ~zpcre();
               void load_file(const char *filename, const char *flags = "gi");
               term_array split(const string &text, TermType type=Matched);
               string replace(const string &text, const string &with);
               string remove(const string &text);
               bool match(const string &str);
               void study();
               string get_expression(){ return m_expression; }
     };

     typedef pair<zpcre, TermType> zpcre_type_pair;
};

#endif
/*
 * vim:ts=5:sw=5:
 */
