#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

// ------------------------------------------------------------------------------------------- //
void testOrderPeriod(pxOrderTransmit* xmit)
{
	xmit->Session();
	/*
	short filialnr = 33;
	long idfnr = 3245162;
	long orderperiod = 0;
	pxOrderPeriodList* list = new pxOrderPeriodList( xmit->Session() );
	orderperiod = list->getCurrentOrderPeriodID( filialnr, idfnr );
	std::cout << "Bestellfenster ID: " << orderperiod << std::endl;
	*/
}
