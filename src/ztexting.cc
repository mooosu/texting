#include "ztexting.h"
using namespace zxlib;
auto_ptr<ztexting> ztexting::_instance;

void ztexting::set(string& dict_file,string &symbol_file,string &unit_file , string &en_file)
{
     m_dict_file = dict_file;
     m_symbol_file = symbol_file;
     m_unit_file = unit_file;
     m_en_file = en_file;

     m_zcws.set_charset("utf8");
     m_zcws.set_dict( dict_file.c_str(), SCWS_XDICT_XDB);

     m_symbol_filter.load_file(symbol_file.c_str());
     m_symbol_filter.study();

     zpcre unit, en;
     unit.load_file(unit_file.c_str());
     en.load_file(en_file.c_str());

     unit.study();
     en.study();
     m_regexp_classifier.push_back( zpcre_type_pair(unit, Unit) );
     m_regexp_classifier.push_back( zpcre_type_pair(en, En) );
}
zstmt ztexting::parse_stmt( const char* text )
{
     zstmt stmt( text,SubStmt);
     stmt.parse(m_symbol_filter,m_regexp_classifier,m_zcws);
     return stmt;
}
bool ztexting::init(string& dict_file,string &symbol_file,string &unit_file , string &en_file)
{
     if( 0== _instance.get()) {
          _instance.reset( new ztexting(dict_file,symbol_file,unit_file,en_file));
     } else {
          throw zexception("ztexting was already inited");
     }
     return true;
}
bool ztexting::init( const char* config_file )
{
     ztexting_config config;
     zxlib::load_yaml(config_file,config);
     init(config.dict_file,config.symbol_file,config.unit_file,config.en_file);
}
ztexting *ztexting::instance()
{
     if( 0== _instance.get()) {
          throw zexception("Call ztexting::init first");
     }
     return _instance.get();
}
