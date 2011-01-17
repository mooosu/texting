#ifndef _ZUTILS_H_
#define _ZUTILS_H_
#include <iostream>
#include <memory>
#include "zstrip.h"


#define ZIS_SPACE_2( s ) \
     (( s[0] == 0xc2 ) && (s[1] == 0xa0 ) )
#define ZIS_SPACE_3( s ) \
     (strncmp((char*)s,"\343\200\200",3) == 0 )
namespace zxlib{
     using namespace std;
     unsigned char dbc_utf8( unsigned char *sbc , size_t len);
     char* znorm(const char* str, size_t len );
     bool file_exists(const char *filename);
     size_t readlines(const char* filename, string_vector& lines );
     string join(string_vector& strs , const char* chars);
     int join_isolated_chars( char * src ,int len, char* dest);
     size_t group_chars(string_vector& strs, size_t size , string_vector& groups );
     size_t find_isolate_chars(string_vector& chars, vector<string_vector>& found);
     void load_yaml( const char* filename , zconfig_yaml& config );


     namespace internal{
          static const size_t c_join_buffer_size = 1024;
          static auto_ptr<char> c_join_buffer(new char[c_join_buffer_size]);
     }

     using internal::c_join_buffer_size;
     using internal::c_join_buffer;
     template<std::size_t MaxSize=32*1024>
     class char_joiner{
          private:
               char* m_string;
               size_t m_size;
               void init( const char* str,size_t size )
               {
                    m_string = str;
                    m_size = size;
                    if( c_join_buffer_size < size  ){
                         c_join_buffer_size = size+1;
                         c_join_buffer.reset( new char[c_join_buffer_size]);
                    }
                    if( c_join_buffer_size >= MaxSize ){
                         throw "Exceed max size" ;
                    }
               }
          public:
               char_joiner(const char* str,size_t size ){
                    init(str,size);
               }
               char_joiner(string& str ){
                    init(str.c_str(),str.size());
               }
               char* join(){
                    join_isolated_chars(m_string,m_size,c_join_buffer.get());
                    return c_join_buffer.get();
               }
     };
};

#endif

