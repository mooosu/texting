#include "zstring.h"

using namespace std;
using namespace zxlib;
void zxlib::load_yaml( const char* filename , zconfig_yaml& config )
{
     ifstream fin(filename);
     YAML::Parser parser(fin);
     YAML::Node doc;
     parser.GetNextDocument(doc);
     if( doc.size() > 0 ){
          config.set_config(doc[0]);
     } else {
          string msg("invalid yaml:");
          msg+=filename;
          throw zexception(msg);
     }
}

string zxlib::join(vector<string>& strs , const char* chars=" ")
{
     size_t i = 0;
     size_t len = strs.size();
     string tmp;
     for( ; i< len-1; i++ ){
          tmp += strs[i]+chars;
     }
     tmp += strs[i];
     return tmp;
}
size_t zxlib::readlines(const char* filename, vector<string>& lines )
{
     FILE *fp;
     char *line = NULL;
     size_t len = 0;
     ssize_t read;

     fp = fopen(filename, "r");
     if (fp){
          while ((read = getline(&line, &len, fp)) != -1) {
               lines.push_back(zrtrim(line,read));
          }
          free(line);
          fclose(fp);
     }
     return lines.size();
}
unsigned char zxlib::dbc_utf8( unsigned char *sbc , size_t len)
{
     unsigned char ch=0 ;
     /*  
      *  "\xef\xbc\x81" => "\357\274\201"
      *  "\xef\xbc\xbf" => "\357\274\277"
      *  "\xef\xbd\x80" => "\357\275\200"
      *  "\xef\xbd\x9d" => "\357\275\235"
      * */
     if ( len == 3 && ZIS_SPACE_3(sbc) ){//"　"
          if( sbc[3] == 0xa5 ) ch = sbc[2] - 0x81;
          else ch = sbc[2] - 0x60;
     }else if ( len == 3 && strncmp((char*)sbc,"\357\274\201",3) >=0 && strncmp((char*) sbc,"\357\274\277",3) <= 0 ){
          if( sbc[3] == 0xa5 ) ch = sbc[2] - 0x81;
          else ch = sbc[2] - 0x60;
     } else if ( len == 3 &&  strncmp((char*)sbc,"\357\275\200",3) >=0 && strncmp( (char*)sbc,"\357\275\235",3) <= 0 ){
          ch = sbc[2] - 0x20;
     } else if ( len == 2 && ZIS_SPACE_2( sbc) ){
          ch = ' ';
     } else if ( strncmp( (char*)sbc,"\357\275\236",3) ==0 ){
          ch = '~';
     }
     return ch;
}
char* zxlib::znorm(const char* str, size_t len )
{
     /*
      * 0x4e00 =>'\xe4\xb8\x80' => "\344\270\200"
      * 0x9fa5 =>'\xe9\xbe\xa5' => "\351\276\245"
      */
     char* ret =NULL;
     unsigned char* tmp = (unsigned char*)malloc(len+1);
     if( tmp != NULL ){
          unsigned char * s =(unsigned char*)str;
          unsigned char * end = (unsigned char*)(len+s);
          int seqlen=0;
          unsigned char dbc=0;
          int k=0;
          while(*s){
               dbc = 0;
               seqlen= zxlib::calculate_sequence_length(s,end);
               if ( seqlen == 3 ){
                    if((dbc= dbc_utf8(s,seqlen))>0){
                         tmp[k++]=dbc;
                    } else if ( strncmp((char*)s,"\344\270\200",3) >=0 && strncmp((char*) s,"\351\276\245",3) <= 0 ){
                         tmp[k++]=s[0];
                         tmp[k++]=s[1];
                         tmp[k++]=s[2];
                    } else {
                         tmp[k++]=' ';
                    }
               } else if ( seqlen == 2 ){
                    tmp[k++]=' ';
               } else if ( seqlen == 1) {
                    tmp[k++]=s[0];
               }
               s+= seqlen;
          }
          tmp[k]=0;
          ret = (char*)tmp;
     }
     return ret;
}

size_t zxlib::find_isolate_chars(string_vector& strs , vector<string_vector>& found)
{

     string_vector tmp;
     for( size_t i =0 ; i< strs.size(); i++ ){
          if(strs[i].size() == 3 && calculate_sequence_length((const unsigned char*)strs[i].c_str(),strs[i].size() ) == 3 ){
               tmp.push_back(strs[i]);
          } else if (strs[i].size() > 3 ){
               if( !tmp.empty()){
                    found.push_back(tmp);
                    tmp.clear();
               }
          }
     }
     if( !tmp.empty()){
          found.push_back(tmp);
     }
     return found.size();
}

size_t zxlib::group_chars(vector<string>& strs, size_t size , string_vector& groups )
{

     size_t count = strs.size() / size ;
     size_t remainder = strs.size() % size;
     string tmp;
     for( size_t i =0 ;i< count ; i++ ){
          for( size_t k = i * size ; k < (i+1)*size ; k++ ){
               tmp+=strs[k];
          }
          groups.push_back(tmp);
          tmp.clear();
     }
     if ( remainder == 1){
          if (groups.empty()){
               groups.push_back(strs.back());
          }else{
               groups.back()=groups.back()+strs.back();
          }
     } else if( remainder > 1 ){
          for( size_t k = strs.size()-remainder ; k < strs.size() ; k++ ){
               tmp+=strs[k];
          }
          groups.push_back(tmp);
     }
     return groups.size();
}
/*
 * vim:ts=5:sw=5:
 */

