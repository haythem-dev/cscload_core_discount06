//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "ibtrelevantcalculator/ibtrelevantcalculatorapplctrl.h"


int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
        ibtrelevantcalculator::ApplCtrl::getInstance().init( argc, argv );
        ibtrelevantcalculator::ApplCtrl::getInstance().run();
        ibtrelevantcalculator::ApplCtrl::getInstance().shutdown();
        ibtrelevantcalculator::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
