#include "zstring.h"

using namespace zxlib;

zstring zstring::to_norm(zpcre &filter) const {
     string tmp = znorm(m_text.c_str(), m_text.size());
     zstring ret(tmp);
     return zstring( filter.replace(ret.to_string(), " ") ).strip();
}

zstring zstring::strip() const {
     char* tmp = ztrim(m_text.c_str(), m_text.size());
     return zstring(tmp);
}

string zstring::join(const string_array &vec) const {
     size_t vec_len = vec.size();
     if (vec_len == 0)
          return "";
     else if (vec_len == 1)
          return vec[0];
     else{
          return zxlib::join(vec,m_text.c_str());
     }
}


term_array zstring::split_by_regexp(zpcre &zp, const string &str, TermType type) const{
     term_array terms = zp.split(str, type);
     return terms;
}
term_array zstring::split_by_regexp(zpcre &zp, TermType type) const{
     term_array terms = zp.split(m_text, type);
     return terms;
}
term_array zstring::cws_all(zscws &zs, zpcre &filter, vector<zpcre_type_pair> &zps){
     term_array terms;
     zstring whitespace(" ");
     string tmp_str = to_norm(filter).to_string();
     for (size_t i = 0; i < zps.size(); i++){
          string_array unknown;
          zpcre_type_pair *item = &(zps[i]);
          term_array tmp_terms = split_by_regexp( item->first, tmp_str, item->second );
          for (size_t i = 0; i < tmp_terms.size(); i++){
               term _t = tmp_terms[i];
               if (_t.term_type == Unknown)
                    unknown.push_back(_t.term_text);
               else
                    terms.push_back(_t);
          }
          tmp_str = whitespace.join(unknown);
     }
     string_array cwsed = zs.cws( tmp_str );
     for (size_t i = 0; i < cwsed.size(); i++){
          terms.push_back(term(cwsed[i], Cn));
     }
     return terms;
}
/*
 * vim:ts=5:sw=5:
 */
