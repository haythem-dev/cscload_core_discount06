//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "csc_phadex/csc_phadexapplctrl.h"
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif

extern "C" {
    extern const char versioninfo[];
}


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
    //csc_phadex::ApplCtrl::StatusEnum result = csc_phadex::ApplCtrl::ERROR_STATUS

    int result = 0; // Think about a class representing all possible return values and the corresponding texts: csc_phadex::CSC_PHADEXApplCtrl::OK;
    try
    {
        /* alternative call:
            ==> "csc_phadex::CSC_PHADEXApplCtrl::init( argc, argv );" <==
            Here the static method 'getInstance()' is called internally.
            Idea is to offer more readable methods.
        */
        csc_phadex::ApplCtrl::getInstance().init( argc, argv );
        csc_phadex::ApplCtrl::getInstance().run();
        csc_phadex::ApplCtrl::getInstance().shutdown();
        csc_phadex::ApplCtrl::clear();

        //result = csc_phadex::ApplCtrl::OK_STATUS;
    }
    catch( ... )
    {
        //result = csc_phadex::ApplCtrl::UNKNOWN_EXCEPTION_CAUGHT;
        result = 99;
    }

    return result;
}
