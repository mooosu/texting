#ifndef _ZUTILS_H_
#define _ZUTILS_H_


#define ZIS_SPACE_2( s ) \
     (( s[0] == 0xc2 ) && (s[1] == 0xa0 ) )
#define ZIS_SPACE_3( s ) \
     (strncmp((char*)s,"\343\200\200",3) == 0 )
namespace zxlib{
     using namespace std;
     unsigned char dbc_utf8( unsigned char *sbc , size_t len);
     char* znorm(const char* str, size_t len );
     size_t readlines(const char* filename, vector<string>& lines );
     string join(vector<string>& strs , const char* chars);
}

#endif

