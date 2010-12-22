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
               zstring m_org_text;
               term_array m_terms;
               vector<zstmt> m_sub_stmts;
               StmtType m_stmt_type;
               bool m_terms_calculated;
               size_t m_level;
          public:

               zstmt( const char* text ,StmtType stmt_type);
               zstmt( string& text , StmtType stmt_type = SubStmt);
               zstmt( zterm& term, StmtType stmt_type = Term );
               zstmt( ){
                    m_stmt_type= EmptyStmt;
                    m_terms_calculated = false;
               }
               bool parse( zpcre &filter, vector<zpcre_type_pair> &zps,zscws& cws );
               bool parse_down(zstmt& stmt , zpcre &filter, vector<zpcre_type_pair> &zps,zscws& cws);
               void level_up(size_t level){m_level=level+1;}
               term_array& get_terms();
               StmtType stmt_type(){ return m_stmt_type;}
     };
     typedef vector<zstmt> zstmt_vector;
};


#endif
