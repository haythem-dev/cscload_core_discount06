#include "csc_deli/csc_deliapplctrl.h"
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif

extern "C" {
	extern const char versioninfo[];
}

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
        csc_deli::ApplCtrl::getInstance().init( argc, argv );
        csc_deli::ApplCtrl::getInstance().run();
        csc_deli::ApplCtrl::getInstance().shutdown();
        csc_deli::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
