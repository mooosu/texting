#include "zstring.h"

using namespace zxlib;

zscws::zscws():m_mode(0){
     m_scws_handler = scws_new();
}
zscws::zscws(const char *charset, const char *dict,  int mode){
     m_scws_handler = scws_new();
     set_charset( charset );
     set_dict( dict, mode);
}
zscws::~zscws(){
     scws_free(m_scws_handler);
}
void zscws::set_charset(const char *charset){
     m_charset = charset;
     scws_set_charset(m_scws_handler, charset);
}
void zscws::set_dict(const char *dict, int mode){
     m_dict = dict;
     m_mode = mode;
     if (scws_set_dict(m_scws_handler, dict, mode) != 0){
          throw "Set dict fail!";
     }
}
void zscws::set_ignore(bool yes){
     if (yes)
          scws_set_ignore(m_scws_handler, 1);
     else
          scws_set_ignore(m_scws_handler, 0);
}
string_array zscws::cws(const char *text){
     string_array ret;
     scws_res_t res,cur;
     scws_send_text(m_scws_handler, text, strlen(text));
     while (res = cur = scws_get_result(m_scws_handler)) {
          while (cur != NULL) {
               ret.push_back( string(text, cur->off, cur->len) );
               cur = cur->next;
          }
          scws_free_result(res);
     }
     return ret;
}
string_array zscws::cws(const string &text){
     return cws(text.c_str());
}
/*
 * vim:ts=5:sw=5:
 */

