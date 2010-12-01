#ifndef _ZSCWS_H_
#define _ZSCWS_H_

#include <vector>
#include <string>
#include <cstring>
#include <scws.h>

using namespace std;

namespace zxlib{
     class scws{
          private:
               scws_t m_scws_handler;
          public:
               scws();
               scws(const char *charset, const char *dict, int mode);
               ~scws();
               void set_charset(const char *charset);
               void set_dict(const char *dict, int mode);
               vector<string> cws(const char *text);
     };
};
#endif
/*
 * vim:ts=5:sw=5:
 */
