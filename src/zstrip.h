#ifndef _ZSTRIP_H_
#define _ZSTRIP_H_

namespace zxlib {

     bool zis_space(const char* s , size_t seqlen );
     char* zltrim(const char* str , size_t len );
     char* zrtrim(const char* str , size_t len );
     char* ztrim(const char* str, size_t len);

}

#endif
/*
 * vim:ts=5:sw=5:
 */
