#include "ztexting.h"
using namespace std;
using namespace zxlib;
zstmt::zstmt( const char* text ,StmtType stmt_type)
{
     init_from_text(text,stmt_type);
}

zstmt::zstmt( string& text ,StmtType stmt_type)
{
     init_from_text(text.c_str(),stmt_type);
}

void zstmt::init_from_text( const char* text , StmtType stmt_type )
{
     m_terms_calculated = false;
     m_text = zstring(text);
     m_stmt_type = stmt_type ;
     m_level = 0;
}
zstmt::zstmt( zterm& term, StmtType stmt_type )
{
     m_terms_calculated = true;
     m_terms.push_back(term);
     m_stmt_type = stmt_type ;
     m_level = 0;
}
bool zstmt::parse( zpcre &filter, vector<zpcre_type_pair> &zps,zscws& cws )
{
     bool ret=false;
     if( m_stmt_type == SubStmt ){
          if(  zps.size() > 0 ){
               if( m_level == 0 ){
                    m_org_text = m_text;
                    m_text = m_text.to_norm(filter);
               }
               string_array unknown;
               zpcre_type_pair &classifier= zps.front();
               term_array tmp_terms = m_text.split_by_regexp( classifier.first, classifier.second );
               for (size_t i = 0; i < tmp_terms.size(); i++){
                    term &t = tmp_terms[i];
                    if (t.term_type == Unknown){
                         zstmt new_stmt( t.term_text);
                         new_stmt.level_up(m_level);
                         m_sub_stmts.push_back(new_stmt);
                         parse_down(m_sub_stmts.back(),filter,zps,cws);
                    } else{
                         m_sub_stmts.push_back(zstmt(t));
                    }
               }
               ret= true;
          } else {
               m_terms_calculated = true;
               string_vector strs = cws.cws(m_text.to_string());
               for(size_t n=0 ; n< strs.size() ; n++){
                    m_terms.push_back(zterm(strs[n],Unknown));
               }
          }
     }
     return ret;
}
bool zstmt::parse_down(zstmt& stmt , zpcre &filter, vector<zpcre_type_pair> &zps,zscws& cws)
{
     vector<zpcre_type_pair> next_zps;
     for( size_t i = 1 ; i< zps.size() ; i++ ){
          next_zps.push_back(zps[i]);
     }
     return stmt.parse(filter,next_zps,cws);
}

term_array& zstmt::get_terms()
{
     if( m_terms_calculated ) return m_terms;
     for( size_t i =0 ; i< m_sub_stmts.size() ; i++){
          term_array& tas  = m_sub_stmts[i].get_terms();
          for( size_t n = 0 ; n < tas.size(); n++){
               m_terms.push_back(tas[n]);
          }
     } 
     m_terms_calculated = true;
     return m_terms;
}
