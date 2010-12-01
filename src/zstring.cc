#include "zstring.h"
#include <iostream>
using namespace zxlib;
vector<string>& zstring::split_by_re(const char* re) {
     Pcre reg(re);
     size_t len = m_text.length();
     size_t pos = 0, start = 0, end = 0;
     if(reg.search(m_text.c_str(), pos)) {
          start = reg.get_match_start(0);
          end = reg.get_match_end(0);
          cout << "start:"<< start << ",end:"<< end << endl;
          if (start > pos)
          {
               string pre = string(m_text, pos, start-pos);
               m_strings.push_back(pre);
          }
          string match = reg.get_match(0);
          m_strings.push_back(match);
          pos = end+1;
          if (pos < len) {
               string tail = string(m_text, pos, len-pos);
               m_strings.push_back(tail);
          }
     }
     return m_strings;
}
/*
 * vim:ts=5:sw=5:
 */
