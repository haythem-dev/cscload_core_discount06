//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "ibtorderimport/ibtorderimportapplctrl.h"

#include <iostream>
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif
#include <sstream>

extern "C" {
	extern const char versioninfo[];
}

using namespace std;

int main( int argc, char *argv[] )
{
    int result = 0;

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
        ibtorderimport::ApplCtrl::getInstance().init( argc, argv );
        ibtorderimport::ApplCtrl::getInstance().run();
        ibtorderimport::ApplCtrl::getInstance().shutdown();
        ibtorderimport::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
