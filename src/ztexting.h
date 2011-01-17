#ifndef _ZTEXTING_H_
#define _ZTEXTING_H_

#include "common.h"

#include "zutils.h"

#include "zterm.h"
#include "zscws.h"
#include "zpcre.h"
#include "zstring.h"
#include "zstmt.h"

namespace zxlib{

     struct _ztexting_config:zxlib::zconfig_yaml{
          string dict_file;
          string symbol_file;
          string unit_file;
          string en_file;
          void set_config(const YAML::Node& node )
          {
               node["dict_file"]>> dict_file;
               node["symbol_file"]>> symbol_file;
               node["unit_file"]>> unit_file;
               node["en_file"]>> en_file;
          }
          void inspect()
          {
               cout << "dict_file:" << dict_file << endl;
               cout << "symbol_file:" << symbol_file << endl;
               cout << "unit_file:" << unit_file << endl;
               cout << "en_file:" << en_file << endl;
          }
     };
     typedef _ztexting_config ztexting_config;
     class ztexting{
          private:
               zscws m_scws;
               string m_dict_file;
               string m_symbol_file; // symbols to remove
               string m_unit_file;
               string m_en_file;
               zscws m_zcws;
               zpcre m_symbol_filter;
               ztexting_config m_config;
               vector<zpcre_type_pair> m_regexp_classifier;
               void set(string& dict_file,string &symbol_file,string &unit_file , string &en_file);
          protected:
               ztexting(ztexting_config& config )
               {
                    m_config = config;
                    set(config.dict_file,config.symbol_file,config.unit_file,config.en_file);
               }

               ztexting(string& dict_file,string &symbol_file,string &unit_file , string &en_file){
                    set(dict_file,symbol_file,unit_file,en_file);
               }

               virtual ~ztexting(void)
               {
               }
               friend class auto_ptr<ztexting>;
               static auto_ptr<ztexting> _instance;
          public:
               zscws& scws(){return m_scws;}
               string& dict_file(){ return m_dict_file;}
               string& symbol_file(){ return m_symbol_file;}
               string& unit_file() { return m_unit_file;}
               string& en_file() { return m_en_file;}
               ztexting_config& config() { return m_config;}
               zstmt parse_stmt( const char* text );
               static bool init(string& dict_file,string &symbol_file,string &unit_file , string &en_file);
               static bool init( const char* config_file);
               static ztexting *instance();
     };
};

#endif

