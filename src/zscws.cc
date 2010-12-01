#include "zscws.h"

using namespace zxlib;

scws::scws(){
     m_scws_handler = scws_new();
}
scws::scws(const char *charset, const char *dict,  int mode){
     m_scws_handler = scws_new();
     scws_set_charset(m_scws_handler, charset);
     scws_set_dict(m_scws_handler, dict, mode);
}
scws::~scws(){
     scws_free(m_scws_handler);
}
void scws::set_charset(const char *charset){
     scws_set_charset(m_scws_handler, charset);
}
void scws::set_dict(const char *dict, int mode){
     scws_set_dict(m_scws_handler, dict, mode);
}
vector<string> scws::cws(const char *text){
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
