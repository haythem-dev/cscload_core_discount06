//-----------------------------------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------------------------------//
#include "longtermlackloader/longtermlackloaderapplctrl.h"
#include <infrastructure/loggerpool/longtermlackloader_loggerpool.h>

#if !defined _WIN32
/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "longtermlackloader"
static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;
#endif

//-----------------------------------------------------------------------------------------------------------------------//
// forward declaration section
//-----------------------------------------------------------------------------------------------------------------------//
void log(const basar::VarString& action);

//-----------------------------------------------------------------------------------------------------------------------//
// int main( int argc, char *argv[] )
//-----------------------------------------------------------------------------------------------------------------------//
int main( int argc, char *argv[] )
{
#if !defined _WIN32
	if ( !strcmp( argv[1], "-version" ) )
	{
			printVersion(versioninfo);
			return 0;
	}
#endif

    log("started");
    
    int result = 1; 
    try
    {
        longtermlackloader::ApplCtrl::getInstance().init( argc, argv );
        longtermlackloader::ApplCtrl::getInstance().run();
        longtermlackloader::ApplCtrl::getInstance().shutdown();
        longtermlackloader::ApplCtrl::clear();
        
        result = 0;
    }
    catch( ... )
    {
        result = 99;
        std::stringstream ss; ss << "Main: Undefined Exception caught! Return value of Application: <" << result << ">.";
        longtermlackloader::infrastructure::LoggerPool::getLoggerLongTermLackLoader().forcedLog( log4cplus::INFO_LOG_LEVEL, ss.str() );
    }

    log("finished");
    return result;
}
//-----------------------------------------------------------------------------------------------------------------------//
// void log( const basar::VarString& action )
//-----------------------------------------------------------------------------------------------------------------------//
void log( const basar::VarString& action )
{
    const log4cplus::Logger& logger = longtermlackloader::infrastructure::LoggerPool::getLoggerLongTermLackLoader();
    std::stringstream ss;
    ss << std::endl;
    ss << "========================================================================================" << std::endl;
    ss << "Application::Main " << action.c_str() << "." << std::endl;
    ss << "========================================================================================"; 
    logger.forcedLog( log4cplus::INFO_LOG_LEVEL, ss.str()) ;
}
