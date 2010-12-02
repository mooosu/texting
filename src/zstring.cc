#include "zstring.h"

using namespace zxlib;

/*
vector<term> zstring::split_by_re(Pcre &reg, TermType type) const {
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
               splited.push_back(term(reg.get_match(0), type));
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


vector<term> zstring::split_by_re(const char* re, TermType type) const {
     Pcre reg(re);
     return split_by_re( reg, type );
}
*/

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
vector<term> zstring::cws_all(zpcre &unit, zpcre &rm, zscws &zs){
     vector<term> terms;
     const char *text = m_text.c_str();
     char *norm_text = znorm(text, strlen(text));
     char *nl_text = zltrim(norm_text, strlen(norm_text));
     char *nlr_text = zrtrim(nl_text, strlen(nl_text));
     vector<term> ext_unit = unit.split(string(nlr_text));
     vector<string> remain;
     for (vector<term>::iterator i = ext_unit.begin(); i != ext_unit.end(); i++){
          if (i->term_type == Matched)
               terms.push_back(term(i->term_text, Unit));
          else
               remain.push_back(i->term_text);
     }
     free(norm_text);
     string remain_str = zstring(" ").join(remain);
     string send_cws_text = rm.remove(remain_str);
     vector<string> cwsed = zs.cws(send_cws_text.c_str());
     for (vector<string>::iterator i = cwsed.begin(); i != cwsed.end(); i++){
          terms.push_back(term(*i, Cn));
     }
     return terms;
}
zstring zstring::to_norm()
{
     char* tmp = znorm((char*)m_text.c_str(),m_text.size());
     zstring ret(tmp);
     // 
     free(tmp);
     return ret;
}
/*
 * vim:ts=5:sw=5:
 */
