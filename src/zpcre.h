#ifndef _ZPCRE_H_
#define _ZPCRE_H_

namespace zxlib {
     class zpcre {
          private:
               std::string m_expression;
               std::string m_flags;
               pcrepp::Pcre m_reg;
          public:
               zpcre();
               zpcre(const std::string &exp);
               zpcre(const std::string &exp, const std::string &flags);
               ~zpcre();
               void load_file(const char *filename, const char *flags = "gi");
               term_array split(const std::string &text, TermType type=Matched);
               std::string replace(const std::string &text, const std::string &with);
               std::string remove(const std::string &text);
               bool match(const std::string &str);
               void study();
               string get_expression(){ return m_expression; }
     };

     typedef pair<zpcre, TermType> zpcre_type_pair;
};

#endif
/*
 * vim:ts=5:sw=5:
 */
