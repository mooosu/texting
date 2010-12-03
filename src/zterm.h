#ifndef _ZTERM_H_
#define _ZTERM_H_

namespace zxlib {
     typedef enum {
          Unit = 0x01,
          Number = 0x02,
          En   = 0x04,
          Cn   = 0x08,
          Brand= 0x10,
          Category = 0x20,
          Matched = 0xee00,
          Unknown = 0xff00,
     } TermType;

     typedef struct _term {
          std::string term_text;
          TermType term_type;

          _term() :term_type(Unknown){};
          _term(std::string text) :term_text(text),term_type(Unknown){};
          _term(std::string text, TermType type) :term_text(text), term_type(type){};
     } term;

     typedef std::vector<term> term_array;

};

#endif
/*
 * vim:ts=5:sw=5:
 */
