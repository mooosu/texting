#include "ztexting.h"

bool zxlib::zis_space(const char* s , size_t seqlen ){
     bool ret = false;
     if ( seqlen == 3 && ZIS_SPACE_3( s ) ){
          ret = true;
     } else if ( seqlen == 2 && ZIS_SPACE_2( s ) ){
          ret = true;
     } else if ( seqlen == 1 && isspace( s[0] ) ) {
          ret = true;
     }
     return ret;
}
char* zxlib::zltrim(const char* str , size_t len ){
     char* ret = NULL;
     if( len > 0 ) {
          unsigned char * s =(unsigned char*)(char*) str;
          unsigned char * end = (unsigned char*)(len+s);
          size_t seqlen=0;
          do{
               seqlen= zxlib::calculate_sequence_length(s,end);
               if( !zis_space((const char*)s,seqlen) ){
                    break;
               }
               s+= seqlen;
          } while(*s);
          ret =(char*) s ;
     } else {
          ret= (char*)str;
     }
     return ret;
}
char* zxlib::zrtrim(const char* str , size_t len ){
     char* ret = NULL;
     if( len > 0 ) {
          unsigned char * s =(unsigned char*)(char*) str;
          unsigned char * end = (unsigned char*)(len+s);
          size_t seqlen=0;
          int count = 0;
          do{
               seqlen= zxlib::calculate_sequence_length(s,end);
               if( zis_space((const char*)s,seqlen) ){
                    count += seqlen;
               } else{
                    count = 0;
               }
               s+= seqlen;
          } while(s< end);
          *(end-count)=0;
          ret = (char*)str ;
     } else {
          ret= (char*)str;
     }
     return ret;
}
char* zxlib::ztrim(const char* str, size_t len){
     const char* ltrimed = zxlib::zltrim(str, len);
     return zxlib::zrtrim(ltrimed, strlen(ltrimed));
}
/*
 * vim:ts=5:sw=5:
 */

