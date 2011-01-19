#include "unicode.h"
using namespace zxlib;
namespace zxlib{

     size_t  utf8_len(const char* str, size_t size )
     {
          size_t len = 0; 
          const unsigned char *tmp=(const unsigned char*)str; 
          const unsigned char *end =tmp+size; 
          while( tmp < end ){ 
               tmp+= calculate_sequence_length( tmp,end ) ; 
               len++; 
          } 
          return len;
     }

     unsigned calculate_sequence_length( const unsigned char* str,size_t len)
     {
          return calculate_sequence_length(str,str+len);
     }
     unsigned calculate_sequence_length( const unsigned char* str,const unsigned char* end)
     {
          // Handle invalid UTF-8, overlong sequences, and truncated sequences as
          // if the text was actually in ISO-8859-1 since we need to do something
          // with it, and this seems the most likely reason why we'd have invalid
          // UTF-8.

          unsigned char ch = *str;

          unsigned seqlen = 1;
          // Single byte encoding (0x00-0x7f) or overlong sequence (0x80-0xc1).
          //
          // (0xc0 and 0xc1 would start 2 byte sequences for characters which are
          // representable in a single byte, and we should not decode these.)
          if (ch < 0xc2) return seqlen;

          if (ch < 0xe0) {
               if (str + 1 == end || // Not enough bytes
                         (str[1] & 0xc0) != 0x80) // Overlong encoding
                    return seqlen;
               seqlen = 2;
               return seqlen;
          }
          if (ch < 0xf0) {
               if (end - str < 3 || // Not enough bytes
                         bad_cont(str[1]) || bad_cont(str[2]) || // Invalid
                         (str[0] == 0xe0 && str[1] < 0xa0)) // Overlong encoding
                    return seqlen;
               seqlen = 3;
               return seqlen;
          }
          if (ch >= 0xf5 || // Code value above Unicode
                    end - str < 4 || // Not enough bytes
                    bad_cont(str[1]) || bad_cont(str[2]) || bad_cont(str[3]) || // Invalid
                    (str[0] == 0xf0 && str[1] < 0x90) || // Overlong encoding
                    (str[0] == 0xf4 && str[1] >= 0x90)) // Code value above Unicode
               return seqlen;
          seqlen = 4;
          return seqlen;
     }

     Utf8Iterator::Utf8Iterator(const char *p_)
     {
          assign(p_, strlen(p_));
     }

     /** Convert a single non-ASCII Unicode character to UTF-8.
      *
      *  This is intended mainly as a helper method for to_utf8().
      *
      *  The character @a ch (which must be > 128) is written to the buffer @a buf
      *  and the length of the resultant UTF-8 character is returned.
      *
      *  NB buf must have space for (at least) 4 bytes.
      */

     // buf should be at least 4 bytes.
     unsigned nonascii_to_utf8(unsigned ch, char * buf)
     {
          if (ch < 0x800) {
               buf[0] = 0xc0 | (ch >> 6);
               buf[1] = 0x80 | (ch & 0x3f);
               return 2;
          }
          if (ch < 0x10000) {
               buf[0] = 0xe0 | (ch >> 12);
               buf[1] = 0x80 | ((ch >> 6) & 0x3f);
               buf[2] = 0x80 | (ch & 0x3f);
               return 3;
          }
          if (ch < 0x200000) {
               buf[0] = 0xf0 | (ch >> 18);
               buf[1] = 0x80 | ((ch >> 12) & 0x3f);
               buf[2] = 0x80 | ((ch >> 6) & 0x3f);
               buf[3] = 0x80 | (ch & 0x3f);
               return 4;
          }
          // Unicode doesn't specify any characters above 0x10ffff.
          // Should we be presented with such a numeric character
          // entity or similar, we just replace it with nothing.
          return 0;
     }
}
