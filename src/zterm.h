#ifndef _ZTERM_H_
#define _ZTERM_H_

#include <string>

namespace zxlib {
     typedef enum {
          Unknow = 0xff00,
          Matched = 0xee00,
          Unit = 1,
          En   = 2,
          Cn   = 4,
          Brand= 8,
          Category = 16,
          Number = 32
     } TermType;

     typedef struct _term {
          std::string term_text;
          TermType term_type;

          _term() :term_type(Unknow){};
          _term(std::string text) :term_text(text),term_type(Unknow){};
          _term(std::string text, TermType type) :term_text(text), term_type(type){};
     } term;

};

#endif
/*
 * vim:ts=5:sw=5:
 */
