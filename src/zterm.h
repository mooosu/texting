#ifndef _ZTERM_H_
#define _ZTERM_H_

namespace zxlib {

     typedef struct _term {
          std::string term_text;
          TermType term_type;

          _term() :term_type(Unknown){};
          _term(std::string text) :term_text(text),term_type(Unknown){};
          _term(std::string text, TermType type) :term_text(text), term_type(type){};
     } term,zterm;

     typedef std::vector<term> term_array;

};

#endif
/*
 * vim:ts=5:sw=5:
 */
