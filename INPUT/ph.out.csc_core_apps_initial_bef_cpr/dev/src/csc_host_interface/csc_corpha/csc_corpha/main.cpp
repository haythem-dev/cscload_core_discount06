//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      application invocation
 *  \author     Steffen Heinlein
 *  \date       22.10.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#include <libbasarappl.h>
#include <libbasarcmnutil_exceptions.h>
#include <libbasardbaspect_accessor.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_manager.h>
#include <cmdlineexception.h>
#include <iostream>
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif
#include <sstream>
#include "csc_corpha_definitions.h"
#include "csc_corphaappl.h"
#include "appinitializerexception.h"
#include "softkillexception.h"

extern "C" {
	extern const char versioninfo[];
}
using namespace std;

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
		csc_corpha::CSC_CorphaAppl::getInstance().init( argc, argv );
		csc_corpha::CSC_CorphaAppl::getInstance().run();
		csc_corpha::CSC_CorphaAppl::getInstance().shutdown();
		csc_corpha::CSC_CorphaAppl::clear();		
		return 0;
    }
	catch( ... )
	{
		return 1;
	}
}


/*!
\todo  
- Suche nach CHECK_WITH_YSI
- Suche nach CHECK_WITH_BB
- Suche nach CHECK
*/
