#include "zstring.h"
using namespace std;
using namespace zxlib;
zstmt::zstmt( const char* text , vector<zpcre_type_pair> &zps,StmtType stmt_type)
{
     m_terms_calculated = false;
     m_text = zstring(text);
     m_regexp_classifier = zps;
     m_stmt_type = stmt_type ;
}

zstmt::zstmt( string& text , vector<zpcre_type_pair> &zps,StmtType stmt_type)
{
     m_terms_calculated = false;
     m_text = zstring(text);
     m_regexp_classifier = zps;
     m_stmt_type = stmt_type ;
}
zstmt::zstmt( zterm& term, StmtType stmt_type )
{
     m_terms_calculated = true;
     m_terms.push_back(term);
     m_stmt_type = stmt_type ;
}
bool zstmt::parse( zpcre &filter )
{
     bool ret=false;
     if( m_stmt_type == SubStmt ){
          if(  m_regexp_classifier.size() > 0 ){
               m_text.to_norm(filter);
               string_array unknown;
               zpcre_type_pair &classifier= m_regexp_classifier.front();
               term_array tmp_terms = m_text.split_by_regexp( classifier.first, classifier.second );
               for (size_t i = 0; i < tmp_terms.size(); i++){
                    term &t = tmp_terms[i];
                    if (t.term_type == Unknown){
                         m_sub_stmts.push_back(create_sub_stmt(t.term_text));
                         m_sub_stmts.back().parse(filter);
                    } else{
                         m_sub_stmts.push_back(zstmt(t));
                    }
               }
               ret= true;
          } else {
               m_terms_calculated = true;
               m_terms.push_back(zterm(m_text.to_string(),Unknown));
          }
     }
     return ret;
}
zstmt zstmt::create_sub_stmt( string& text )
{
     vector<zpcre_type_pair> zps;
     for( size_t i = 1 ; i< m_regexp_classifier.size() ; i++ ){
          zps.push_back(m_regexp_classifier[i]);
     }
     return zstmt( text , zps );
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
