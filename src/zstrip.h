#ifndef _ZSTRIP_H_
#define _ZSTRIP_H_

#include<stdio.h>
#include<ctype.h>
#include<cstring>
#include "unicode.h"
#include "zutils.h"

bool zis_space(const char* s , size_t seqlen );
char* zltrim( char* str , size_t len );
char* zrtrim( char* str , size_t len );

#endif
