//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "subsequentdeliveryrelevantcalculator/subsequentdeliveryrelevantcalculatorapplctrl.h"
#include "version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: "  SUBSEQUENTDELIVERYRELEVANTCALCULATOR_VERSION;
}

int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
		subsequentdeliveryrelevantcalculator::ApplCtrl::getInstance().init( argc, argv );
		subsequentdeliveryrelevantcalculator::ApplCtrl::getInstance().run();
	}
    catch( ... )
    {
        result = -100;
    }

	subsequentdeliveryrelevantcalculator::ApplCtrl::getInstance().shutdown();
	subsequentdeliveryrelevantcalculator::ApplCtrl::clear();

	return result;
}
