#include "zstrip.h"
#include <iostream>
#define ZIS_SPACE_2( s ) \
     (( s[0] == 0xc2 ) && (s[1] == 0xa0 ) )
#define ZIS_SPACE_3( s ) \
     (strncmp((char*)s,"\343\200\200",3) == 0 )

bool zis_space(const char* s , size_t seqlen ){
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
char* zltrim( char* str , size_t len ){
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
          ret= str;
     }
     return ret;
}
char* zrtrim( char* str , size_t len ){
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
          std::cout << "count:" << count << std::endl;
          *(end-count)=0;
          ret = str ;
     } else {
          ret= str;
     }
     return ret;
}
/*
 * vim:ts=5:sw=5:
 */
