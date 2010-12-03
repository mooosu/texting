#ifndef _ZSCWS_H_
#define _ZSCWS_H_

namespace zxlib{
     typedef vector<std::string> string_array;
     class zscws{
          private:
               scws_t m_scws_handler;
               std::string m_dict;
               std::string m_charset;
               int m_mode;
               zscws(zscws& other){}
               zscws& operator=(const zscws &){}

          public:
               zscws();
               zscws(const char *charset, const char *dict, int mode);
               ~zscws();
               void set_charset(const char *charset);
               void set_dict(const char *dict, int mode);
               void set_ignore(bool yes);
               string_array cws(const char *text);
               string_array cws(const std::string &text);
     };
};
#endif
/*
 * vim:ts=5:sw=5:
 */
