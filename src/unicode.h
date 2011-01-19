#ifndef _UTF8_H_
#define _UTF8_H_

#include <string>
#include <cstring>
#define LEN_COMPARE( op1,op2,r1,r2) \
     bool operator op1 (unsigned max) { \
          unsigned len = 0; \
          const unsigned char *str=m_str; \
          while( str < m_end ){ \
               str+= calculate_sequence_length( str,m_end ) ; \
               len++; \
               if( len op2 max ){ \
                    return r1 ; \
               } \
          } \
          return r2; \
     }

namespace zxlib{
     inline bool bad_cont(unsigned char ch) { return (ch & 0xc0) != 0x80; }

     size_t   utf8_len(const char* str, size_t len );
     unsigned calculate_sequence_length( const unsigned char* str,const unsigned char* end);
     unsigned calculate_sequence_length( const unsigned char* str,size_t len);
     /** An iterator which returns Unicode character values from a UTF-8 encoded
      *  string.
      */
     class Utf8Iterator {
          const unsigned char *m_str;
          const unsigned char *m_end;
          mutable unsigned m_seqlen;

          unsigned get_char() const;

          Utf8Iterator(const unsigned char *p_, const unsigned char *end_, unsigned seqlen_)
               : m_str(p_), m_end(end_), m_seqlen(seqlen_) { }

          public:
          /** Return the raw const char * pointer for the current position. */
          const char * raw() const {
               return reinterpret_cast<const char *>(m_str ? m_str : m_end);
          }

          /** Return the number of bytes left in the iterator's buffer. */
          size_t left() const { return m_str ? m_end - m_str : 0; }

          /** Assign a new string to the iterator.
           *
           *  The iterator will forget the string it was iterating through, and
           *  return characters from the start of the new string when next called.
           *  The string is not copied into the iterator, so it must remain valid
           *  while the iteration is in progress.
           *
           *  @param p_ A pointer to the start of the string to read.
           *
           *  @param len The length of the string to read.
           */
          void assign(const char *p_, size_t len) {
               if (len) {
                    m_str = reinterpret_cast<const unsigned char*>(p_);
                    m_end = m_str + len;
                    m_seqlen = 0;
               } else {
                    m_str = NULL;
               }
          }

          /** Assign a new string to the iterator.
           *
           *  The iterator will forget the string it was iterating through, and
           *  return characters from the start of the new string when next called.
           *  The string is not copied into the iterator, so it must remain valid
           *  while the iteration is in progress.
           *
           *  @param s The string to read.  Must not be modified while the iteration
           *		 is in progress.
           */
          void assign(const std::string &s) { assign(s.data(), s.size()); }

          /** Create an iterator given a pointer to a null terminated string.
           *
           *  The iterator will return characters from the start of the string when
           *  next called.  The string is not copied into the iterator, so it must
           *  remain valid while the iteration is in progress.
           *
           *  @param p_ A pointer to the start of the null terminated string to read.
           */
          explicit Utf8Iterator(const char *p_);

          /** Create an iterator given a pointer and a length.
           *
           *  The iterator will return characters from the start of the string when
           *  next called.  The string is not copied into the iterator, so it must
           *  remain valid while the iteration is in progress.
           *
           *  @param p_ A pointer to the start of the string to read.
           *
           *  @param len The length of the string to read.
           */
          Utf8Iterator(const char *p_, size_t len) { assign(p_, len); }

          /** Create an iterator given a string.
           *
           *  The iterator will return characters from the start of the string when
           *  next called.  The string is not copied into the iterator, so it must
           *  remain valid while the iteration is in progress.
           *
           *  @param s The string to read.  Must not be modified while the iteration
           *		 is in progress.
           */
          Utf8Iterator(const std::string &s) { assign(s.data(), s.size()); }

          /** Create an iterator which is at the m_end of its iteration.
           *
           *  This can be compared to another iterator to check if the other iterator
           *  has reached its m_end.
           */
          Utf8Iterator() : m_str(NULL), m_end(0), m_seqlen(0) { }


          /** Get the current Unicode character value pointed to by the iterator.
           *
           *  Returns unsigned(-1) if the iterator has reached the m_end of its buffer.
           */
          unsigned operator*() const {
               if (m_str == NULL) return unsigned(-1);
               if (m_seqlen == 0) m_seqlen = calculate_sequence_length(m_str,m_end);
               unsigned char ch = *m_str;
               if (m_seqlen == 1) return ch;
               if (m_seqlen == 2) return ((ch & 0x1f) << 6) | (m_str[1] & 0x3f);
               if (m_seqlen == 3)
                    return ((ch & 0x0f) << 12) | ((m_str[1] & 0x3f) << 6) | (m_str[2] & 0x3f);
               return ((ch & 0x07) << 18) | ((m_str[1] & 0x3f) << 12) |
                    ((m_str[2] & 0x3f) << 6) | (m_str[3] & 0x3f);
          }

          /** Check if lenght of str < given value.
           *
           *  @return true or false.
           */
          LEN_COMPARE(<,>=,false,true);
          /** Check if lenght of str <= given value.
           *
           *  @return true or false.
           */
          LEN_COMPARE(<=,>,false,true);
          /** Check if lenght of str > given value.
           *
           *  @return true or false.
           */
          LEN_COMPARE(>,>,true,false);
          /** Check if lenght of str >= given value.
           *
           *  @return true or false.
           */
          LEN_COMPARE(>=,>=,true,false);
          /** Move forward to the next Unicode character.
           *
           *  @return An iterator pointing to the position before the move.
           */
          Utf8Iterator operator++(int) {
               // If we've not calculated m_seqlen yet, do so.
               if (m_seqlen == 0) m_seqlen = calculate_sequence_length( m_str ,m_end);
               const unsigned char *old_p = m_str;
               unsigned old_seqlen = m_seqlen;
               m_str += m_seqlen;
               if (m_str == m_end) m_str = NULL;
               m_seqlen = 0;
               return Utf8Iterator(old_p, m_end, old_seqlen);
          }

          /** Move forward to the next Unicode character.
           *
           *  @return A reference to this object.
           */
          Utf8Iterator & operator++() {
               if (m_seqlen == 0) m_seqlen = calculate_sequence_length( m_str,m_end );
               m_str += m_seqlen;
               if (m_str == m_end) m_str = NULL;
               m_seqlen = 0;
               return *this;
          }

          /** Test two Utf8Iterators for equality.
           *
           *  @return true iff the iterators point to the same position.
           */
          bool operator==(const Utf8Iterator &other) const { return m_str == other.m_str; }

          /** Test two Utf8Iterators for inequality.
           *
           *  @return true iff the iterators do not point to the same position.
           */
          bool operator!=(const Utf8Iterator &other) const { return m_str != other.m_str; }

          /// We implement the semantics of an STL input_iterator.
          //@{
          typedef std::input_iterator_tag iterator_category;
          typedef unsigned value_type;
          typedef size_t difference_type;
          typedef const unsigned * pointer;
          typedef const unsigned & reference;
          //@}
     };

     /// Functions associated with handling Unicode characters.
     namespace Unicode {

          /** Each Unicode character is in exactly one of these categories. */
          typedef enum {
               UNASSIGNED,
               UPPERCASE_LETTER,
               LOWERCASE_LETTER,
               TITLECASE_LETTER,
               MODIFIER_LETTER,
               OTHER_LETTER,
               NON_SPACING_MARK,
               ENCLOSING_MARK,
               COMBINING_SPACING_MARK,
               DECIMAL_DIGIT_NUMBER,
               LETTER_NUMBER,
               OTHER_NUMBER,
               SPACE_SEPARATOR,
               LINE_SEPARATOR,
               PARAGRAPH_SEPARATOR,
               CONTROL,
               FORMAT,
               PRIVATE_USE,
               SURROGATE,
               CONNECTOR_PUNCTUATION,
               DASH_PUNCTUATION,
               OPEN_PUNCTUATION,
               CLOSE_PUNCTUATION,
               INITIAL_QUOTE_PUNCTUATION,
               FINAL_QUOTE_PUNCTUATION,
               OTHER_PUNCTUATION,
               MATH_SYMBOL,
               CURRENCY_SYMBOL,
               MODIFIER_SYMBOL,
               OTHER_SYMBOL
          } category;

          namespace Internal {
               /** @internal Extract the information about a character from the Unicode
                *  character tables.
                *
                *  ch must be a valid Unicode character value (i.e. < 0x110000)
                */

               int get_character_info(unsigned ch);

               /** @internal Extract how to convert the case of a Unicode character from
                *  its info.
                */
               inline int get_case_type(int info) { return ((info & 0xe0) >> 5); }

               /// @internal Extract the category of a Unicode character from its info.
               inline category get_category(int info) { return static_cast<category>(info & 0x1f); }

               /** @internal Extract the delta to use for case conversion of a character
                *  from its info.
                */
               inline int get_delta(int info) {
                    /* It's implementation defined if sign extension happens on right shift
                     * of a signed int, hence the conditional (hopefully the compiler will
                     * spot this and optimise it to a sign-extending shift on architectures
                     * with a suitable instruction).
                     */
                    return (info >= 0) ? (info >> 15) : (~(~info >> 15));
               }
          }
          unsigned nonascii_to_utf8(unsigned ch, char * buf);

          /** Convert a single Unicode character to UTF-8.
           *
           *  The character @a ch is written to the buffer @a buf and the length of the
           *  resultant UTF-8 character is returned.
           *
           *  NB buf must have space for (at least) 4 bytes.
           */
          inline unsigned to_utf8(unsigned ch, char *buf) {
               if (ch < 128) {
                    *buf = static_cast<unsigned char>(ch);
                    return 1;
               }
               return zxlib::Unicode::nonascii_to_utf8(ch, buf);
          }

          /** Append the UTF-8 representation of a single Unicode character to a
           *  std::string.
           */
          inline void append_utf8(std::string &s, unsigned ch) {
               char buf[4];
               s.append(buf, to_utf8(ch, buf));
          }

          /// Return the category which a given Unicode character falls into.
          inline category get_category(unsigned ch) {
               // Categorise non-Unicode values as UNASSIGNED.
               if (ch >= 0x110000) return zxlib::Unicode::UNASSIGNED;
               return Internal::get_category(Internal::get_character_info(ch));
          }

          /// Test if a given Unicode character is "word character".
          inline bool is_wordchar(unsigned ch) {
               const unsigned int WORDCHAR_MASK =
                    (1 << zxlib::Unicode::UPPERCASE_LETTER) |
                    (1 << zxlib::Unicode::LOWERCASE_LETTER) |
                    (1 << zxlib::Unicode::TITLECASE_LETTER) |
                    (1 << zxlib::Unicode::MODIFIER_LETTER) |
                    (1 << zxlib::Unicode::OTHER_LETTER) |
                    (1 << zxlib::Unicode::NON_SPACING_MARK) |
                    (1 << zxlib::Unicode::ENCLOSING_MARK) |
                    (1 << zxlib::Unicode::COMBINING_SPACING_MARK) |
                    (1 << zxlib::Unicode::DECIMAL_DIGIT_NUMBER) |
                    (1 << zxlib::Unicode::LETTER_NUMBER) |
                    (1 << zxlib::Unicode::OTHER_NUMBER) |
                    (1 << zxlib::Unicode::CONNECTOR_PUNCTUATION);
               return ((WORDCHAR_MASK >> get_category(ch)) & 1);
          }

          /// Test if a given Unicode character is a whitespace character.
          inline bool is_whitespace(unsigned ch) {
               const unsigned int WHITESPACE_MASK =
                    (1 << zxlib::Unicode::CONTROL) | // For TAB, CR, LF, FF.
                    (1 << zxlib::Unicode::SPACE_SEPARATOR) |
                    (1 << zxlib::Unicode::LINE_SEPARATOR) |
                    (1 << zxlib::Unicode::PARAGRAPH_SEPARATOR);
               return ((WHITESPACE_MASK >> get_category(ch)) & 1);
          }

          /// Test if a given Unicode character is a currency symbol.
          inline bool is_currency(unsigned ch) {
               return (get_category(ch) == zxlib::Unicode::CURRENCY_SYMBOL);
          }

          /// Convert a Unicode character to lowercase.
          inline unsigned tolower(unsigned ch) {
               int info;
               // Leave non-Unicode values unchanged.
               if (ch >= 0x110000 || !(Internal::get_case_type((info = zxlib::Unicode::Internal::get_character_info(ch))) & 2))
                    return ch;
               return ch + Internal::get_delta(info);
          }

          /// Convert a Unicode character to uppercase.
          inline unsigned toupper(unsigned ch) {
               int info;
               // Leave non-Unicode values unchanged.
               if (ch >= 0x110000 || !(Internal::get_case_type((info = zxlib::Unicode::Internal::get_character_info(ch))) & 4))
                    return ch;
               return ch - Internal::get_delta(info);
          }

          /// Convert a UTF-8 std::string to lowercase.
          inline std::string tolower(const std::string &term)
          {
               std::string result;
               result.reserve(term.size());
               for (Utf8Iterator i(term); i != Utf8Iterator(); ++i) {
                    append_utf8(result, tolower(*i));
               }
               return result;
          }

          /// Convert a UTF-8 std::string to uppercase.
          inline std::string toupper(const std::string &term)
          {
               std::string result;
               result.reserve(term.size());
               for (Utf8Iterator i(term); i != Utf8Iterator(); ++i) {
                    append_utf8(result, toupper(*i));
               }
               return result;
          }

     }
}

/*
 * vim:ts=5:sw=5:
 */
#endif // _UTF8_H_

