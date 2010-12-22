#ifndef _ZSTRING_H_
#define _ZSTRING_H_

using namespace std;

namespace zxlib{
     class zstring{
          private:
               string m_text;
          public:
               zstring(){};
               zstring(const char* text):m_text(text){};
               zstring(string text):m_text(text){};

               zstring to_norm(zpcre &filter) const;
               zstring strip() const;
               string join(const string_array &vec) const;
               term_array split_by_regexp(zpcre &zp, const string &str, TermType type = Matched) const;
               term_array split_by_regexp(zpcre &zp, TermType type = Matched) const;
               term_array cws_all(zscws &zs, zpcre &filter, vector<zpcre_type_pair> &zps);
               string to_string(){return m_text;}
     };

};

#endif
/*
 * vim:ts=5:sw=5:
 */
