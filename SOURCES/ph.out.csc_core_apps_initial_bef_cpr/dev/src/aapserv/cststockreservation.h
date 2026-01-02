#ifndef GUARD_AAPSERV_CST_STOCK_RESERVATION_H
#define GUARD_AAPSERV_CST_STOCK_RESERVATION_H

// new class to handle CPR-240064 - deletion of stock reservation
// DB interactions may not report directly to log so this class
// will use the DB SQL statements in conseccutive order to define
// the deletion process and will protocoll the resulting changes in 
// artikellokal.bestand or articlereservation.reservedqty

#include "artikel.h"
#include "dadedb.h"

class CstStockReservation
{
	public: 
		CstStockReservation(stockreservationS* deleteItem);
		~CstStockReservation();
		int DeleteEntry(tError* errorMsg, bool bIsTrans);

	private:

		CstStockReservation(const CstStockReservation& other); // not implemented
		CstStockReservation& operator=(const CstStockReservation& other); //  not implemented

		int DeleteReservedSubsequentDelivery(tError* errorMsg, bool bIsTrans);
		int DeleteReservedInterbranchRequest(tError* errorMsg, bool bIsTrans);
		int DeleteReservedForOpenOrder(tError* errorMsg, bool bIsTrans);
		int CheckForSubsequentDeliveryEntries(tError* errorMsg, bool bIsTrans);
		int CheckForInterbranchRequest(tError* errorMsg, bool bIsTrans);
		int ReportCurrentArticleStock(tError* errorMsg, bool bIsTrans);
		int ReportCurrentReservedStock(tError* errorMsg, bool bIsTrans);
		int DeleteSubsequentDeliveryEntries(tError* errorMsg, bool bIsTrans);
		int DeleteCstStockReservedEntry(tError* errorMsg, bool bIsTrans);
		int DeleteInterbranchRequest(tError* errorMsg, bool bIsTrans);
		int UpdateCurrentArticleStock(tError* errorMsg, bool bIsTrans);
		int UpdateReservedArticleStock(tError* errorMsg, bool bIsTrans);

		stockreservationS* m_currentDeleteItem;
		stockreservationorderS* m_currentOrder;
		stockreservationnachlieferposS* m_subsequentDeliveryItemToDelete;
		stockreservationartikellokalS* m_articleStockToUpdate;
		stockreservationarticlereservS* m_reservedStockToUpdate;
		stockreservationibtrequestS* m_ibtRequestToDelete;
};

#endif