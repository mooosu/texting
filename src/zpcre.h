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

               term_array split(const std::string &text, TermType type=Matched);
               std::string replace(const std::string &text, const std::string &with);
               std::string remove(const std::string &text);
               bool match(const std::string &str);
     };

     typedef pair<zpcre, TermType> zpcre_type_pair;

     static zpcre SymbolFilter("([\\\\~`!@$%\\(\\)\\{\\}\\[\\]=\"\';:,<>?|^]|/(?=[a-z0-9\xE4\xB8\x80-\xE9\xBE\xA5]{2,})|/$|(?<=[^a-z0-9+])\\+|(?<=[^a-z0-9])[&*#\\-_/]+|(?<=[\xE4\xB8\x80-\xE9\xBE\xA5])[&*#\\-_+/]+|^[&*#\\-_+/]|(?<=[^0-9])\\.(?=[^0-9])|^\\.|\\.$|(?<=[)])[&*#\\-_/+])", "gi");

     static zpcre UnitExt("(?i)(?<![0-9a-z\\-])((?:\\d+(?:\\.\\d*)?|\\.\\d+)\\s*(K金|毫升|英寸|克拉|百兆|千兆|米|联|座|芯|瓦|孔|条|针|列|颗|节|匹|张|分|款|号|粒|只|件|匹|升|个|码|片|层|速|转|寸|位|万|倍|克|口|重|枚|兆|代|((CM|MM|GHz|(bit)|B)|(T|G|M|K)B?)(?=[^0-9a-z+-])))", "gi");

     static zpcre EnExt("((?:[a-z0-9][a-z0-9&*#\\-_+/\\.]+(?:[a-z0-9#+\\-]{1,}))+|[a-z0-9]+)", "gi");

};

#endif
/*
 * vim:ts=5:sw=5:
 */
