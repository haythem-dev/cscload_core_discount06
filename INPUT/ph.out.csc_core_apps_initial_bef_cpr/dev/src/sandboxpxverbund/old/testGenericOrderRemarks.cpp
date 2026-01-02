#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

// ------------------------------------------------------------------------------------------- //
void testGenericOrderRemarks(pxOrderTransmit* xmit)
{	
	long orderno = 706655;
	nString tenderid = "I am the tender id";

	pxOrder* order = new pxOrder( xmit->Session(), orderno, cDBOPEN_UPDATE);
	delete order;
	/*
	if( order->IsGoodState() )
	{
		if( !order->setTenderContractId(tenderid) )
		{
			cout << "failed to set the tender contract id" << endl;
		}

		pxGenericOrderRemarkList* list = order->getGenericOrderRemarks();
		if( list->Entries() > 0 )
		{
			pxGenericOrderRemarkListIter iter = pxGenericOrderRemarkListIter(*list);
			pxGenericOrderRemark* ordrem = NULL;
			while( ordrem = (pxGenericOrderRemark*) ++iter )
			{
				std::cout << "-> OrderRemark: \t" 
					<< "CSCOrderNo: [" << ordrem->CSCOrderNo() << "] "
					<< "PositionNo: [" << ordrem->PositionNo() << "] "
					<< "RemarkType: [" << ordrem->RemarkType() << "] "
					<< "TextNumber: [" << ordrem->TextNumber() << "] "				
					<< "RemarkText: [" << ordrem->RemarkText() << "] " 				
					<< std::endl;
			}
		}

		delete order;
	}
	*/
	
	/*
	pxGenericOrderRemarkList* list = new pxGenericOrderRemarkList( xmit->Session() );	
	list->SelectOrderRemarksByOrderNo(orderno);	
	if( list->Entries() > 0 )
	{
		pxGenericOrderRemarkListIter iter = pxGenericOrderRemarkListIter(*list);
		pxGenericOrderRemark* ordrem = NULL;
		while( ordrem = (pxGenericOrderRemark*) ++iter )
		{
			std::cout << "-> OrderRemark: \t" 
				<< "CSCOrderNo: [" << ordrem->CSCOrderNo() << "] "
				<< "PositionNo: [" << ordrem->PositionNo() << "] "
				<< "RemarkType: [" << ordrem->RemarkType() << "] "
				<< "TextNumber: [" << ordrem->TextNumber() << "] "				
				<< "RemarkText: [" << ordrem->RemarkText() << "] " 				
				<< std::endl;
		}
	}
	*/
}
