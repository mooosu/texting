#ifndef _ZSCWS_H_
#define _ZSCWS_H_


using namespace std;

namespace zxlib{
     class zscws{
          private:
               scws_t m_scws_handler;
               string m_dict;
               string m_charset;
               int m_mode;
               zscws(zscws& other){}
               zscws& operator=(const zscws &){}

          public:
               zscws();
               zscws(const char *charset, const char *dict, int mode);
               ~zscws();
               void set_charset(const char *charset);
               void set_dict(const char *dict, int mode);
               vector<string> cws(const char *text);
     };
};
#endif
/*
 * vim:ts=5:sw=5:
 */
