#ifndef _ZSTRING_H_
#define _ZSTRING_H_

#include <string>
#include <vector>
#include <pcre++.h>
#include <scws.h>

using namespace std;
using namespace pcrepp;

namespace zxlib{

     typedef enum {
          Unknow = 0xff00,
          Unit = 1,
          En   = 2,
          Cn   = 4,
          Brand= 8,
          Category = 16,
          Number = 32
     } TermType;

     typedef struct _term {
          string term_text;
          TermType term_type;

          _term() :term_type(Unknow){};
          _term(string text) :term_text(text),term_type(Unknow){};
          _term(string text, TermType type) :term_text(text), term_type(type){};
     } term;

     static Pcre reg_lstrip = Pcre("(^[\\s\\t\\r\\n]+)");
     static Pcre reg_rstrip = Pcre("([\\s\\t\\r\\n]+$)");

     class zstring{
          private:
               string m_text;
          public:
               zstring(){};
               zstring(const char* text):m_text(text){};
               zstring(string text):m_text(text){};
               string get_text() const;

               vector<term> split_by_re(const char* re) const;
               vector<term> split_by_re(Pcre &reg) const;

               string strip() const;
               vector<string> split() const;
               string join(const vector<string> &vec) const;

               vector<string> cws(scws_t &scws) const;
     };
};

#endif
/*
 * vim:ts=5:sw=5:
 */
