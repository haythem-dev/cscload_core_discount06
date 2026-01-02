//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "exportarticlecalculator/exportarticlecalculatorapplctrl.h"


int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
        exportarticlecalculator::ApplCtrl::getInstance().init( argc, argv );
        exportarticlecalculator::ApplCtrl::getInstance().run();
        exportarticlecalculator::ApplCtrl::getInstance().shutdown();
        exportarticlecalculator::ApplCtrl::clear();
    }
    catch( ... )
    {
        result = 99;
    }

    return result;
}
