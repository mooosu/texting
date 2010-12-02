#include "zutils.h"
unsigned char zxlib::dbc_utf8( unsigned char *sbc , size_t len)
{
     unsigned char ch=0 ;
     /*  
      *  "\xef\xbc\x81" => "\357\274\201"
      *  "\xef\xbc\xbf" => "\357\274\277"
      *  "\xef\xbd\x80" => "\357\275\200"
      *  "\xef\xbd\x9d" => "\357\275\235"
      * */
     if ( len == 3 && ZIS_SPACE_3(sbc) ){//"　"
          if( sbc[3] == 0xa5 ) ch = sbc[2] - 0x81;
          else ch = sbc[2] - 0x60;
     }else if ( len == 3 && strncmp((char*)sbc,"\357\274\201",3) >=0 && strncmp((char*) sbc,"\357\274\277",3) <= 0 ){
          if( sbc[3] == 0xa5 ) ch = sbc[2] - 0x81;
          else ch = sbc[2] - 0x60;
     } else if ( len == 3 &&  strncmp((char*)sbc,"\357\275\200",3) >=0 && strncmp( (char*)sbc,"\357\275\235",3) <= 0 ){
          ch = sbc[2] - 0x20;
     } else if ( len == 2 && ZIS_SPACE_2( sbc) ){
          ch = ' ';
     } else if ( strncmp( (char*)sbc,"\357\275\236",3) ==0 ){
          ch = '~';
     }
     return ch;
}
char* zxlib::znorm(char* str, size_t len )
{
     /*
      * 0x4e00 =>'\xe4\xb8\x80' => "\344\270\200"
      * 0x9fa5 =>'\xe9\xbe\xa5' => "\351\276\245"
      */
     char* ret =NULL;
     unsigned char* tmp = (unsigned char*)malloc(len+1);
     if( tmp != NULL ){
          unsigned char * s =(unsigned char*)str;
          unsigned char * end = (unsigned char*)(len+s);
          int seqlen=0;
          unsigned char dbc=0;
          int k=0;
          while(*s){
               dbc = 0;
               seqlen= zxlib::calculate_sequence_length(s,end);
               if ( seqlen == 3 ){
                    if((dbc= dbc_utf8(s,seqlen))>0){
                         tmp[k++]=dbc;
                    } else if ( strncmp((char*)s,"\344\270\200",3) >=0 && strncmp((char*) s,"\351\276\245",3) <= 0 ){
                         tmp[k++]=s[0];
                         tmp[k++]=s[1];
                         tmp[k++]=s[2];
                    } else {
                         tmp[k++]=' ';
                    }
               } else if ( seqlen == 2 ){
                    tmp[k++]=' ';
               } else if ( seqlen == 1) {
                    tmp[k++]=s[0];
               }
               s+= seqlen;
          }
          tmp[k]=0;
          ret = (char*)tmp;
     }
     return ret;
}

