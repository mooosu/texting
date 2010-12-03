#include "zstring.h"

using namespace zxlib;

zpcre::zpcre(){
}
zpcre::zpcre(const string &exp){
    m_expression = exp;
    m_reg = pcrepp::Pcre(exp);
}
zpcre::zpcre(const string &exp, const string &flags){
    m_expression = exp;
    m_flags = flags;
    m_reg = pcrepp::Pcre(exp, flags);
}
zpcre::~zpcre(){
}
term_array zpcre::split(const string &text, TermType type){
     term_array splited;
     size_t len = text.length();
     size_t pos = 0, start = 0, end = 0;
     while (pos < len) {
          if(m_reg.search(text, pos)) {
               start = m_reg.get_match_start(0);
               end = m_reg.get_match_end(0);
               if (start > pos) {
                    splited.push_back(term(string(text, pos, start-pos)));
               }
               splited.push_back(term(m_reg.get_match(0), type));
               pos = end+1;
          } else {
               if (pos < len) {
                    splited.push_back(term(string(text, pos, len-pos)));
               }
               break;
          }
     }
     return splited;
}
string zpcre::replace(const string &text, const string &with){
    return m_reg.replace(text, with);
}
string zpcre::remove(const string &text){
    return m_reg.replace(text, "");
}
bool zpcre::match(const string &str){
     if (!m_reg.search(str))
          return false;
     return (m_reg.matches() == 1 && m_reg.get_match_length(0) == str.length());
}
void zpcre::study(){
     m_reg.study();
}
void zpcre::load_file(const char *filename, const char *flags){
     string_array strs;
     readlines(filename, strs);
     m_expression = "(" + join(strs, "") + ")";
     m_flags = flags;
     m_reg = pcrepp::Pcre(m_expression, flags);
}

/*
 * vim:ts=5:sw=5:
 */
