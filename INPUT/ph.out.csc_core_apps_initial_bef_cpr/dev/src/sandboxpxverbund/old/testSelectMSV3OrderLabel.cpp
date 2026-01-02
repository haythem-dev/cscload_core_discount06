#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

// ------------------------------------------------------------------------------------------- //
void testSelectMSV3OrderLabel(pxOrderTransmit* xmit)
{	
	short filialnr = 59;
	long idfnr = 4405478;
	nString auftragsart("NO");
	long orderperiodid = 2;
	pxMSV3OrderList* list = new pxMSV3OrderList( xmit->Session() );
	list->SelectMSV3OrderLabel( filialnr, idfnr, auftragsart, orderperiodid );
	if( list->Entries() > 0 )
	{
		pxMSV3OrderListIter iter = pxMSV3OrderListIter(*list);
		pxMSV3Order* order = NULL;
		while ( (order = (pxMSV3Order*) ++iter) != NULL )
		{
			std::cout << "Label: [" << order->OrderLabel() << "]" << std::endl;			
		}
	}
}
