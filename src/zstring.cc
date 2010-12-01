#include "zstring.h"

using namespace zxlib;

vector<term> zstring::split_by_re(Pcre &reg) const {
     vector<term> splited;
     size_t len = m_text.length();
     size_t pos = 0, start = 0, end = 0;
     while (pos < len) {
          if(reg.search(m_text, pos)) {
               start = reg.get_match_start(0);
               end = reg.get_match_end(0);
               if (start > pos) {
                    splited.push_back(term(string(m_text, pos, start-pos)));
               }
               splited.push_back(term(reg.get_match(0)));
               pos = end+1;
          } else {
               if (pos < len) {
                    splited.push_back(term(string(m_text, pos, len-pos)));
               }
               break;
          }
     }
     return splited;
}


vector<term> zstring::split_by_re(const char* re) const {
     Pcre reg(re);
     return split_by_re( reg );
}


string zstring::strip() const {
     return reg_right_strip.replace(reg_left_strip.replace(m_text, ""), "");
}


vector<string> zstring::split() const {
     return reg_split_default.split(strip());
}


string zstring::join(const vector<string> & vec) const {
     size_t vec_len = vec.size();
     if (vec_len == 0)
          return "";
     else if (vec_len == 1)
          return vec[0];
     else{
          size_t size = m_text.length() * (vec_len-1);
          for(size_t i = 0; i < vec_len; i++)
               size += vec[i].size();
          string tmp;
          tmp.reserve(size);
          tmp = vec[0];
          for(size_t i = 1; i < vec_len; i++) 
               tmp += m_text + vec[i];
          return tmp;
     }
}
/*
 * vim:ts=5:sw=5:
 */
