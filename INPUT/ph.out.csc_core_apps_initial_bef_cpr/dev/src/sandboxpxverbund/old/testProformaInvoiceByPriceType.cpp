#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

// ------------------------------------------------------------------------------------------- //
void testProformaInvoiceByPriceType(pxOrderTransmit* xmit)
{
	short pricetype = -1;
	
	long KdAuftragNr = 773957;

	pxOrder				*order			= new pxOrder(xmit->Session(), KdAuftragNr, cDBGET_READONLY);
	pxOrderItemList		*oItemList;
	pxOrderItem			*item;
	int cnt = 0;

	while (pricetype <= 2)
	{
		cnt = 0;

		order->ProformaInvoice(pricetype);
		
		oItemList = order->ItemListProforma();           //Liste von Positionen
		
		item = (pxOrderItem *)oItemList->At(cnt);

		while (item)
		{
			++cnt;
			std::cout	<< "Auftrag: "	<< item->KdAuftragNr()
						<< "PZN: "		<< item->ArtikelNr()
						<< "PosNr: "	<< item->PosNr()
						<< "PreisTyp: "	<< item->PreisTyp()			
						<< std::endl;

			item = (pxOrderItem *)oItemList->At(cnt);
		}

		std::cout << "------------- <" << cnt << "> Positionen für Preistyp <"	<< pricetype << "> in Auftrag <" << KdAuftragNr << "> gefundnen! ----------------" << std::endl;

		++pricetype;
	}
}
