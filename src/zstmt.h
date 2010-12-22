#ifndef _ZSTMT_H_
#define _ZSTMT_H_

namespace zxlib{

     using namespace std;
     typedef enum{
          EmptyStmt = 0,
          SubStmt = 1,
          Term = 2,
     }StmtType;
     class zstmt{
          private:
               zstring m_text;
               vector<zpcre_type_pair> m_regexp_classifier;
               term_array m_terms;
               vector<zstmt> m_sub_stmts;
               StmtType m_stmt_type;
               bool m_terms_calculated;
          public:

               zstmt( const char* text , vector<zpcre_type_pair> &zps,StmtType stmt_type);
               zstmt( string& text , vector<zpcre_type_pair> &zps, StmtType stmt_type = SubStmt);
               zstmt( zterm& term, StmtType stmt_type = Term );
               zstmt( ){
                    m_stmt_type= EmptyStmt;
                    m_terms_calculated = false;
               }
               bool parse( zpcre &filter );
               zstmt create_sub_stmt( string& text );
               term_array& get_terms();
               StmtType stmt_type(){ return m_stmt_type;}
     };
     typedef vector<zstmt> zstmt_vector;
};


#endif
