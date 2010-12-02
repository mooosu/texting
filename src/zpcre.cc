#include "zpcre.h"

using namespace zxlib;

zpcre::zpcre(){
}
zpcre::zpcre(const string &exp){
    m_expression = exp;
    m_reg = Pcre(exp);
}
zpcre::zpcre(const string &exp, const string &flags){
    m_expression = exp;
    m_flags = flags;
    m_reg = Pcre(exp, flags);
}
zpcre::~zpcre(){
}
vector<term> zpcre::split(const string &text){
     vector<term> splited;
     size_t len = text.length();
     size_t pos = 0, start = 0, end = 0;
     while (pos < len) {
          if(m_reg.search(text, pos)) {
               start = m_reg.get_match_start(0);
               end = m_reg.get_match_end(0);
               if (start > pos) {
                    splited.push_back(term(string(text, pos, start-pos)));
               }
               splited.push_back(term(m_reg.get_match(0), Matched));
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
/*
 * vim:ts=5:sw=5:
 */
