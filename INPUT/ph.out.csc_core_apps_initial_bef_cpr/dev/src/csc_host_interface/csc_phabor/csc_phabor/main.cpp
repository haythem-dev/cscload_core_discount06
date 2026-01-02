//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      application invocation
 *  \author     Bischof Bjoern
 *  \date       23.12.2010
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// includes
//--------------------------------------------------------------------------------------------------//
#include "csc_phaborappl.h"
#include <libbasarappl.h>

#include <libbasarcmnutil_exceptions.h>
#include <libbasardbaspect_accessor.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_manager.h>

#include <cmdlineexception.h>
#include "appinitializerexception.h"
#include "softkillexception.h"
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif
#include <sstream>

#include <iostream>

extern "C" {
	extern const char versioninfo[];
}

using namespace std;

//--------------------------------------------------------------------------------------------------//
// application invocation
//--------------------------------------------------------------------------------------------------//
int main( int argc, char *argv[] )
{ 		
	basar::cmnutil::CmdLineTokenizer args;
	args.setCmdLine(argc, argv);

#ifndef WIN32
	if (args.isParam("-version"))
	{
		std::cout << versioninfo << std::endl;
		std::cout << GitVersionInfo::instance() << std::endl;
		exit( 0 );
	}		
#endif

	try 
	{				
		csc_phabor::CSC_PhaborAppl::getInstance().init( argc, argv );
		csc_phabor::CSC_PhaborAppl::getInstance().run();
		csc_phabor::CSC_PhaborAppl::getInstance().shutdown();
		csc_phabor::CSC_PhaborAppl::clear();		
		return 0;
    }
	catch( ... )
	{
		return 1;
	}
}
