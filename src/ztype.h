#ifndef _ZTYPE_H_
#define _ZTYPE_H_
#include<string>
#include<vector>

using std::string;
using std::vector;
using std::exception;
using std::pair;
namespace zxlib{
     typedef vector<string> string_vector;
     typedef vector<string> string_array;
     typedef enum {
          Unit = 0x01,
          Number = 0x02,
          En   = 0x04,
          Cn   = 0x08,
          Brand= 0x10,
          Category = 0x20,
          Matched = 0xee00,
          Unknown = 0xff00,
     } TermType;
     class zexception: public exception {
          public:
               zexception() : m_msg("exception raised from zxlib" ){}
               zexception( const char * msg ) : m_msg(msg){}
               zexception( string& msg ) : m_msg(msg){}
               virtual ~zexception() throw() { }
               virtual const char* what() const throw(){ return m_msg.c_str(); }
          protected:
               string m_msg;
     };
     typedef struct{
          virtual void set_config( const YAML::Node&  node ) = 0;
     }zconfig_yaml;
};
#endif

