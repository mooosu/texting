#include<string>
#include<vector>
namespace zxlib{
     using namespace std;
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
}

