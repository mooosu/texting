#ifndef _ZSTRING_H_
#define _ZSTRING_H_
#include <string>
#include <vector>
using namespace std;
namespace zxlib{
     class zstring{
          private:
               string m_text;
               vector<string> m_strings;
          public:
               zstring(){};
               zstring(const char* text):m_text(text){};
               zstring(string text):m_text(text){};
               vector<string>& split_by_re(const char* re);
     };
};


#endif
/*
 * vim:ts=5:sw=5:
 */
