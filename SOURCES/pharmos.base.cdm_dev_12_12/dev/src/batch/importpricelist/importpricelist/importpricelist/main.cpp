//----------------------------------------------------------------------------
/*! \file
 *  \brief  Should have the same, short and consistent structure / layout.
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------
#include "importpricelist/importpricelistapplctrl.h"


int main( int argc, char *argv[] )
{
    int result = 0;
    
	try
    {
		importpricelist::ApplCtrl::getInstance().init( argc, argv );
		importpricelist::ApplCtrl::getInstance().run();
	}
    catch( ... )
    {
        result = -100;
    }

	importpricelist::ApplCtrl::getInstance().shutdown();
	importpricelist::ApplCtrl::clear();

	return result;
}
