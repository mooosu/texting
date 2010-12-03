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
     size_t readlines(const char* filename, string_vector& lines );
     string join(string_vector& strs , const char* chars);
     size_t group_chars(string_vector& strs, size_t size , string_vector& groups );
     size_t find_isolate_chars(string_vector& chars, vector<string_vector>& found);
     void load_yaml( const char* filename , zconfig_yaml& config );
}

#endif

