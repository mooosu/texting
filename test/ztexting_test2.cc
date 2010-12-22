#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ztexting_test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ztexting.h"

using namespace std;
using namespace zxlib;

BOOST_AUTO_TEST_CASE( test_singleton )
{
     // should compiler error( ‘zxlib::ztexting::ztexting(zxlib::ztexting_config&)’ is protected )
     //ztexting_config config;
     //ztexting texting(config);;
}
bool call_init_first(zexception ex)
{
     size_t found=string(ex.what()).find("Call ztexting::init first");
     return found!=string::npos;
}
bool reinit_exception(zexception ex)
{
     size_t found=string(ex.what()).find("ztexting was already inited");
     return found!=string::npos;
}
BOOST_AUTO_TEST_CASE(test_ztexting_init)
{
     BOOST_CHECK_EXCEPTION( ztexting::instance(),zexception,call_init_first );
}
BOOST_AUTO_TEST_CASE(test_reinit)
{
     ztexting::init("test/test_ztexting_init.yml");
     ztexting_config &config = ztexting::instance()->config();
     BOOST_CHECK_EXCEPTION(ztexting::init(config.dict_file,config.symbol_file,config.unit_file,config.en_file),
               zexception,reinit_exception);
}
