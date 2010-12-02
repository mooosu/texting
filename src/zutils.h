#ifndef _ZUTILS_H_
#define _ZUTILS_H_

#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include "unicode.h"

#define ZIS_SPACE_2( s ) \
     (( s[0] == 0xc2 ) && (s[1] == 0xa0 ) )
#define ZIS_SPACE_3( s ) \
     (strncmp((char*)s,"\343\200\200",3) == 0 )
namespace zxlib{
     unsigned char dbc_utf8( unsigned char *sbc , size_t len);
     char* znorm(char* str, size_t len );
}

#endif

