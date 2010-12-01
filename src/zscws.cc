#include "zscws.h"
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
     scws_set_dict(m_scws_handler, dict, mode);
}
vector<string> zscws::cws(const char *text){
     vector<string> ret;
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
/*
 * vim:ts=5:sw=5:
 */

