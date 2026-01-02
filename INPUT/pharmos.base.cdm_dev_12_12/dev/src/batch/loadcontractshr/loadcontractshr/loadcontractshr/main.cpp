//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "loadcontractshr/loadcontractshrapplctrl.h"


int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
        loadcontractshr::ApplCtrl::getInstance().init( argc, argv );
        loadcontractshr::ApplCtrl::getInstance().run();
        loadcontractshr::ApplCtrl::getInstance().shutdown();
        loadcontractshr::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
