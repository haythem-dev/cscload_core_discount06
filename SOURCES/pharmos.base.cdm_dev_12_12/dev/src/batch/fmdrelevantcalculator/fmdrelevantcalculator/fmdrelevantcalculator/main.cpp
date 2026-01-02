//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "fmdrelevantcalculator/fmdrelevantcalculatorapplctrl.h"


int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
        fmdrelevantcalculator::ApplCtrl::getInstance().init( argc, argv );
        fmdrelevantcalculator::ApplCtrl::getInstance().run();
        fmdrelevantcalculator::ApplCtrl::getInstance().shutdown();
        fmdrelevantcalculator::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
