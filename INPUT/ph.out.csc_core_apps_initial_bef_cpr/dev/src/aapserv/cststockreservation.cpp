#include "cststockreservation.h"
#include "aeorderstat.h"
#include <logger/loggerconfig.h>
#include <logger/loggerpool.h>
#include <string.h>
#include <pxdbxx.h>

#ifdef __CPLUS__
extern "C" {
#endif

	// forward declarations for SQL 
	retClient Stockreservation_SelOrder(stockreservationorderS* d, tError* tErrorMsg, bool bIsTrans);
	retClient Stockreservation_SelCstStockReservation(stockreservationS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_SelNachlieferPos(stockreservationnachlieferposS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_SelArtikelLokal(stockreservationartikellokalS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_SelArticleReserv(stockreservationarticlereservS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_SelIBTRequet(stockreservationibtrequestS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_DeleteNachlieferPos(stockreservationnachlieferposS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_DeleteCstStockReservedEntry(stockreservationS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_DeleteIbtRequest(stockreservationibtrequestS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_UpdateArtikelLokal(stockreservationartikellokalS* a, tError* stError, bool bIsTrans);
	retClient Stockreservation_UpdateArticleReservation(stockreservationarticlereservS* a, tError* stError, bool bIsTrans);
#ifdef __CPLUS__
}
#endif

CstStockReservation::CstStockReservation(stockreservationS* deleteItem)
	:m_currentDeleteItem(NULL)
	,m_currentOrder(NULL)
	,m_subsequentDeliveryItemToDelete(NULL)
	,m_articleStockToUpdate(NULL)
	,m_reservedStockToUpdate(NULL)
	,m_ibtRequestToDelete(NULL)
{
	const char* fun = "CstStockReservation::CstStockReservation";
	basar::VarString errMsg;

	if (deleteItem == NULL)
		return; // nothing to do

	m_currentDeleteItem = deleteItem;

	basar::VarString trimStr;
	trimStr.format("%s", m_currentDeleteItem->ARTICLE_CODE);
	trimStr.trim();
	strcpy(m_currentDeleteItem->ARTICLE_CODE, trimStr.c_str());

	errMsg.format("%s: Entry to delete: BranchNo %d, CustomerNo %ld, ArticleNo %ld / PCN %s, ReserveType %d, ReservedQty %ld, OrderNo %ld, from %ld",
		fun,
		m_currentDeleteItem->BRANCHNO,
		m_currentDeleteItem->CUSTOMERNO,
		m_currentDeleteItem->ARTICLENO,
		m_currentDeleteItem->ARTICLE_CODE,
		m_currentDeleteItem->RESERVTYPE,
		m_currentDeleteItem->RESERVEDQTY,
		m_currentDeleteItem->KDAUFTRAGNR,
		m_currentDeleteItem->DATEFROM);

	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
}

CstStockReservation::~CstStockReservation()
{
	// currentDeleteItem is from external call and must not be deleted internally
	// the following members are selected data internally and should be removed
	m_currentOrder = NULL; // do not delete, because it's not allocated dynamically via new
	delete m_subsequentDeliveryItemToDelete;
	delete m_articleStockToUpdate;
	delete m_reservedStockToUpdate;
	delete m_ibtRequestToDelete;
}

int CstStockReservation::DeleteEntry(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteEntry";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error

	// load single cststockreservedentry to ensure only one entry will be deleted
	// if more than one entry exists - this select will return with error
	sqlStatus = Stockreservation_SelCstStockReservation(m_currentDeleteItem, sqlErrorMsg, bIsTrans);
	if (sqlStatus != IS_OK)
	{
		errMsg.format("%s: CstStocReserved entry not found: SQL ReturnCode %d, SQL Code %ld: %s",
			fun,
			sqlStatus,
			sqlErrorMsg->lSqlcode,
			sqlErrorMsg->spErrm);
		BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), errMsg);
		status = sqlStatus;
		// nothing to delete
		return status;
	}
	else
	{
		basar::VarString trimStr;
		trimStr.format("%s", m_currentDeleteItem->ARTICLE_CODE);
		trimStr.trim();
		strcpy(m_currentDeleteItem->ARTICLE_CODE,trimStr.c_str());
	}
	
	// check current order state
	if (m_currentDeleteItem->KDAUFTRAGNR > 0)
	{
		// load corresponding order to validate current state of order
		stockreservationorderS selectOrder;
		selectOrder.FILIALNR = m_currentDeleteItem->BRANCHNO;
		selectOrder.KDAUFTRAGNR = m_currentDeleteItem->KDAUFTRAGNR;
		selectOrder.KUNDENNR = m_currentDeleteItem->CUSTOMERNO;
		sqlStatus = Stockreservation_SelOrder(&selectOrder, sqlErrorMsg, bIsTrans);
		if (sqlStatus == IS_OK)
		{
			m_currentOrder = &selectOrder;
			if (selectOrder.DATUM == 0)
			{
				errMsg.format("%s: OrderNo %ld, OrderType %d for CustomerNo: %ld in State %s exists.",
					fun,
					selectOrder.KDAUFTRAGNR,
					selectOrder.KDAUFTRAGART,
					selectOrder.KUNDENNR,
					selectOrder.KDAUFTRAGSTAT);
				BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
			}
			else
			{
				errMsg.format("%s: Archived Order from %ld, OrderNo %ld, OrderType %d for CustomerNo: %ld in State %s exists.",
					fun,
					selectOrder.DATUM,
					selectOrder.KDAUFTRAGNR,
					selectOrder.KDAUFTRAGART,
					selectOrder.KUNDENNR,
					selectOrder.KDAUFTRAGSTAT);

				BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

				if (abs(m_currentOrder->DATUM - m_currentDeleteItem->DATEFROM) > 60)
				{
					errMsg.format("%s: Archived Order not valid - archive date %d to old, does not match to current reserved stock entry from %d!", 
						fun,
						m_currentOrder->DATUM,
						m_currentDeleteItem->DATEFROM);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
					m_currentOrder = NULL;
				}
			}
		}
		else if (sqlStatus == IS_ERROR)
		{
			errMsg.format("%s: select OrderNo %ld returned error %d - SQL Code %ld: %s",
				fun,
				m_currentDeleteItem->KDAUFTRAGNR,
				(int)sqlStatus,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spError);
			status = sqlStatus;
		}
	}
	if (m_currentOrder == NULL ||
		m_currentOrder->KDAUFTRAGSTAT[AEORD_POS_STORNIERT] == '1' ||
		m_currentOrder->KDAUFTRAGSTAT[AEORD_POS_FAKTUR_ENDE] == '1')
	{
		pxBegin();
		switch (m_currentDeleteItem->RESERVTYPE)
		{
		case 7: 
		case 8:
			status = DeleteReservedSubsequentDelivery(sqlErrorMsg, bIsTrans);
			break;
		case 9:
		case 10:
			status = DeleteReservedInterbranchRequest(sqlErrorMsg, bIsTrans);
			break;
		case 11:
		case 12:
			status = DeleteReservedForOpenOrder(sqlErrorMsg, bIsTrans);
			break;
		default:
			errMsg.format("%s: CstStockReserved.ReservedType %d is not supported. Operation returns without deletion.",
				fun,
				m_currentDeleteItem->RESERVTYPE);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
			break;
		}

		if (status == IS_OK) 
		{
			pxCommit();
		} 
		else
		{
			pxRollback();
		}
	}
	else
	{
		// Order not closed, cancled or abandoned
		errMsg.format("%s: OrderNo %ld not in final state closed, cancled or abandoned. CStStockReserved entry will not be deleted.", fun);
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	return status;
}

int CstStockReservation::DeleteReservedSubsequentDelivery(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteSubsequentDeliveryEntries";
	basar::VarString errMsg;

	int status = 0; // no error

	errMsg.format("%s: before delete:", fun);
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	
	//select always for logging the storage location
	status = ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
	if (status != IS_OK)
	{
		errMsg.format("%s: current articles stock can't be evaluated!", fun);
		BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), errMsg);			
	}
	if (m_currentDeleteItem->RESERVTYPE == 8)
	{
		status = ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
		if (status != IS_OK)
		{
			errMsg.format("%s: current reserved stock can't be evaluated!", fun);
			BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
	}

	status = CheckForSubsequentDeliveryEntries(sqlErrorMsg, bIsTrans);
	if (status == IS_OK || status == IS_NOTFOUND)
	{
		if (m_subsequentDeliveryItemToDelete != NULL)
		{
			// current stock may not be incremented by reservedqty because the subsequent delivery articles have not been delivered
			// begin transaction before deletion - in case of error rollback
			status = DeleteSubsequentDeliveryEntries(sqlErrorMsg,bIsTrans);
			if (status == IS_OK)
			{
				status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
				if (status == IS_OK)
				{
					if (m_currentDeleteItem->RESERVTYPE == 7)
					{
						errMsg.format("%s: current stock after deletion of reserved stock entry:", fun);
						BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
						ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
					}
					else if (m_currentDeleteItem->RESERVTYPE == 8)
					{
						errMsg.format("%s: reserved stock after deletion of reserved stock entry:", fun);
						BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
						ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
					}
				}
			}
		}
		else
		{
			errMsg.format("%s: no subsequent delivery entry (nachlieferpos) exists", fun);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

			// delete stock reservation without returning reserved stock to current stock
			// because subsequent delivery entry was not found, so the ordered articles have not
			// not been reduced from stock via this reservation
			status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
			if (status == IS_OK)
			{
				if (m_currentDeleteItem->RESERVTYPE == 7)
				{
					errMsg.format("%s: current stock after deletion of reserved stock entry:", fun);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
					ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
				}
				else if (m_currentDeleteItem->RESERVTYPE == 8)
				{
					errMsg.format("%s: reserved stock after deletion of reserved stock entry:", fun);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
					ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
				}
			}
		}
	}
	return status;
}

int CstStockReservation::UpdateCurrentArticleStock(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::UpdateCurrentArticleStock";
	basar::VarString errMsg;
	int status = 0;
	
	long qtyBefore = m_articleStockToUpdate->BESTAND;
	m_articleStockToUpdate->BESTAND += m_currentDeleteItem->RESERVEDQTY;
	
	status = Stockreservation_UpdateArtikelLokal(m_articleStockToUpdate, sqlErrorMsg, bIsTrans);
	if (status == IS_OK) 
	{
		errMsg.format("%s - current stock for ArticleNo %ld / PCN %s quantity updated from %ld to %ld.",
			fun,
			m_articleStockToUpdate->ARTIKEL_NR,
			m_currentDeleteItem->ARTICLE_CODE,
			qtyBefore,
			m_articleStockToUpdate->BESTAND);
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	else
	{
		errMsg.format("%s - current stock for ArticleNo %ld / PCN %s quantity could not be updated: SQL Error %ld - %s",
			fun,
			m_articleStockToUpdate->ARTIKEL_NR,
			m_currentDeleteItem->ARTICLE_CODE,
			sqlErrorMsg->lSqlcode,
			sqlErrorMsg->spErrm);
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	return status;
}

int CstStockReservation::UpdateReservedArticleStock(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::UpdateReservedArticleStock";
	basar::VarString errMsg;
	int status = 0;
	long qtyBefore = m_reservedStockToUpdate->RESERVEDQTY;

	if (m_reservedStockToUpdate != NULL)
	{
		m_reservedStockToUpdate->RESERVEDQTY += m_currentDeleteItem->RESERVEDQTY;

		status = Stockreservation_UpdateArticleReservation(m_reservedStockToUpdate, sqlErrorMsg, bIsTrans);
		if (status == IS_OK)
		{
			errMsg.format("%s - reserved stock for ArticleNo %ld / PCN %s quantity updated from %ld to %ld.",
				fun,
				m_reservedStockToUpdate->ARTICLENO,
				m_currentDeleteItem->ARTICLE_CODE,
				qtyBefore,
				m_reservedStockToUpdate->RESERVEDQTY);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
	}
	else
	{
		errMsg.format("%s - reserved stock for ArticleNo %ld / PCN %s quantity could not be updated: SQL Error %ld - %s",
			fun,
			m_reservedStockToUpdate->ARTICLENO,
			m_currentDeleteItem->ARTICLE_CODE,
			sqlErrorMsg->lSqlcode,
			sqlErrorMsg->spErrm);
		BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	return status;
}


int CstStockReservation::CheckForInterbranchRequest(tError* errorMsg, bool bIsTrans)
{ 
	const char* fun = "CstStockReservation::CheckForInterbranchRequest";
	basar::VarString errMsg;

	int status = IS_OK; // no error

	delete m_ibtRequestToDelete;
	m_ibtRequestToDelete = new stockreservationibtrequestS();
	m_ibtRequestToDelete->IBTBRANCHNO = m_currentDeleteItem->BRANCHNO;
	m_ibtRequestToDelete->IBTCUSTOMERNO = m_currentDeleteItem->CUSTOMERNO;
	m_ibtRequestToDelete->ARTICLENO = m_currentDeleteItem->ARTICLENO;
	m_ibtRequestToDelete->DATEFROM = m_currentDeleteItem->DATEFROM;
	m_ibtRequestToDelete->TIMEFROM = m_currentDeleteItem->TIMEFROM;

	status = Stockreservation_SelIBTRequet(m_ibtRequestToDelete, errorMsg, bIsTrans);
	if (status == IS_OK)
	{
		errMsg.format("%s: Interbranch Request %ld: for Branch %d, Customer %ld, ArticleNo %ld / PCN %s, Qty: %ld - from Date %ld / Time %ld - Processing State: %d",
			fun,
			m_ibtRequestToDelete->IBTREQUESTID,
			m_ibtRequestToDelete->BRANCHNO,
			m_ibtRequestToDelete->CUSTOMERNO,
			m_ibtRequestToDelete->ARTICLENO,
			m_currentDeleteItem->ARTICLE_CODE,
			m_ibtRequestToDelete->QUANTITY,
			m_currentDeleteItem->DATEFROM,
			m_currentDeleteItem->TIMEFROM,
			m_ibtRequestToDelete->PROCESSINGSTATE);
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	return status;
}

int CstStockReservation::DeleteReservedInterbranchRequest(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteInterbranchRequest";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error

	errMsg.format("%s: before delete:", fun);
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	
	//select always for logging the storage location
	status = ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
	if (status != IS_OK)
	{
		errMsg.format("%s: current articles stock can't be evaluated!", fun);
		BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	else
	{
		status = CheckForInterbranchRequest(sqlErrorMsg, bIsTrans);
		if (status == IS_NOTFOUND)
		{
			errMsg.format("%s: no corresponding Interbranch Request found - processing state unknown. Reserved Stock Quantity will not be returned to stock.", fun);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
			
			status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
		}
		else if (status == IS_OK)
		{
			if (m_ibtRequestToDelete != NULL && m_ibtRequestToDelete->PROCESSINGSTATE < 2)
			{
				if (m_currentDeleteItem->RESERVTYPE == 9)
				{
					errMsg.format("%s: on delete of reserved stock for interbranch request, reserved quantity will be returned to current stock", fun);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
					
					status = UpdateCurrentArticleStock(sqlErrorMsg, bIsTrans);
					if (status == IS_OK)
					{
						status = DeleteInterbranchRequest(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
							if (status == IS_OK)
							{
								errMsg.format("%s: current stock after deletion of reserved stock entry:", fun);
								BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
								ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
							}
						}
					}
				}
				else if (m_currentDeleteItem->RESERVTYPE == 10)
				{
					status = ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
					if (status == IS_OK)
					{
						errMsg.format("%s: on delete of reserved stock for interbranch request, reserved quantity will be returned to reserved stock", fun);
						BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

						status = UpdateReservedArticleStock(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							status = DeleteInterbranchRequest(sqlErrorMsg, bIsTrans);
							if (status == IS_OK)
							{
								status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
								if (status == IS_OK)
								{
									errMsg.format("%s: reserved stock after deletion of reserved stock entry:",fun);
									BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
									ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
								}
							}
						}
					}
				}
			}
			else
			{
				// delete the ibtrequest entry and the reserved stock entry but do not return the reserved quantity to stock
				status = DeleteInterbranchRequest(sqlErrorMsg, bIsTrans);
				if (status == IS_OK)
				{
					status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
					if (status == IS_OK)
					{
						if (m_currentDeleteItem->RESERVTYPE == 9)
						{
							errMsg.format("%s: current stock after deletion of reserved stock entry:", fun);
							BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
							ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
						}
						else if (m_currentDeleteItem->RESERVTYPE == 10)
						{
							errMsg.format("%s: reserved stock after deletion of reserved stock entry:", fun);
							BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
							ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
						}
					}
				}
			}

		}
	}	
	errMsg.format("%s: after delete.", fun);
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

	return status;
}

int CstStockReservation::DeleteReservedForOpenOrder(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteReservedForOpenOrder";
	basar::VarString errMsg;

	int status = IS_OK; // no error
	if (m_currentDeleteItem != NULL)
	{
		// order could result from state 7 or 8 - subsequent delivery
		status = CheckForSubsequentDeliveryEntries(sqlErrorMsg, bIsTrans);
		if (status == IS_OK)
		{
			status = DeleteSubsequentDeliveryEntries(sqlErrorMsg,bIsTrans);
		}
		else
		{
			// order could resul from state 9 or 10
			status = CheckForInterbranchRequest(sqlErrorMsg, bIsTrans);
			if (status == IS_OK)
			{
				status = DeleteInterbranchRequest(sqlErrorMsg, bIsTrans);
			}
		}
		if (status == IS_OK || status == IS_NOTFOUND)
		{
			//select always for logging the storage location
			status = ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
			long stockQtyBeforeDelete = m_articleStockToUpdate->BESTAND;

			// redundant abandoned objects have been deleted
			if (m_currentOrder != NULL)
			{
				if (m_currentOrder->KDAUFTRAGSTAT[AEORD_POS_STORNIERT] == '1')
				{
					if (m_currentDeleteItem->RESERVTYPE == 11) // from current stock
					{
						errMsg.format("%s: on delete of current stock for open order, reserved quantity will be returned to current stock", fun);
						BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

						status = UpdateCurrentArticleStock(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
							if (status == IS_OK)
							{
								errMsg.format("%s: current stock after delete:", fun);
								BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
								ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
							}
						}
					}
					else if (m_currentDeleteItem->RESERVTYPE == 12) // from reserved stock
					{
						errMsg.format("%s: on delete of reserved stock for open order, reserved quantity will be returned to current stock", fun);
						BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

						status = ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							status = UpdateReservedArticleStock(sqlErrorMsg, bIsTrans);
							if (status == IS_OK)
							{
								status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
								if (status == IS_OK)
								{
									errMsg.format("%s: reserved stock after delete:", fun);
									BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
									ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
								}
							}
						}
					}
				}
				else
				{
					errMsg.format("%s: on delete of reserved stock, reserved quantity will not be returned to stock.");
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
					status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
				}
			}
			else if (m_currentDeleteItem->KDAUFTRAGNR == 0)
			{
				if (m_currentDeleteItem->RESERVTYPE == 11) // from current stock
				{
					errMsg.format("%s: on delete of current stock for open order, reserved quantity will be returned to current stock", fun);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

					status = UpdateCurrentArticleStock(sqlErrorMsg, bIsTrans);
					if (status == IS_OK)
					{
						status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							errMsg.format("%s: current stock after delete:", fun);
							BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
							ReportCurrentArticleStock(sqlErrorMsg, bIsTrans);
						}
					}
				}
				else if (m_currentDeleteItem->RESERVTYPE == 12) // from reserved stock
				{
					errMsg.format("%s: on delete of reserved stock for open order, reserved quantity will be returned to current stock", fun);
					BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

					status = ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
					if (status == IS_OK)
					{
						status = UpdateReservedArticleStock(sqlErrorMsg, bIsTrans);
						if (status == IS_OK)
						{
							status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
							if (status == IS_OK)
							{
								errMsg.format("%s: reserved stock after delete:", fun);
								BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
								ReportCurrentReservedStock(sqlErrorMsg, bIsTrans);
							}
						}
					}
				}

			}
			else
			{
				errMsg.format("%s: on delete of reserved stock, reserved quantiy will not be returned to stock.", fun);
				BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
				status = DeleteCstStockReservedEntry(sqlErrorMsg, bIsTrans);
			}
			
		}

	}
	return status;
}

int CstStockReservation::ReportCurrentArticleStock(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::ReportCurrentArticleStock";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error

	if (m_currentDeleteItem != NULL)
	{
		delete m_articleStockToUpdate;
		m_articleStockToUpdate = new stockreservationartikellokalS();
		m_articleStockToUpdate->FILIALNR = m_currentDeleteItem->BRANCHNO;
		m_articleStockToUpdate->ARTIKEL_NR = m_currentDeleteItem->ARTICLENO;

		sqlStatus = Stockreservation_SelArtikelLokal(m_articleStockToUpdate, sqlErrorMsg, bIsTrans);

		if (sqlStatus == IS_OK)
		{
			errMsg.format("%s: current article stock (artikellokal) - BranchNo %d, ArtikelNo %ld, Quantity %ld, Storage Location: %d Station: %s, Shelf %s",
				fun,
				m_articleStockToUpdate->FILIALNR,
				m_articleStockToUpdate->ARTIKEL_NR,
				m_articleStockToUpdate->BESTAND,
				m_articleStockToUpdate->LAGERBEREICHNR,
				m_articleStockToUpdate->STATIONNR,
				m_articleStockToUpdate->LAGERFACHNR);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
		else if (sqlStatus != IS_NOTFOUND)
		{
			errMsg.format("%s: selection for current article stock for Branch %d and ArticleNo %ld returns error SQL Error %ld: %s",
				fun,
				m_currentDeleteItem->BRANCHNO,
				m_currentDeleteItem->ARTICLENO,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spErrm);
			delete m_reservedStockToUpdate;
			m_reservedStockToUpdate = NULL;
			status = (int)sqlStatus;
		}
	}
	return status;
}

int CstStockReservation::ReportCurrentReservedStock(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::ReportCurrentReservedStock";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error

	if (m_currentDeleteItem != NULL)
	{
		delete m_reservedStockToUpdate;
		m_reservedStockToUpdate = new stockreservationarticlereservS();
		m_reservedStockToUpdate->BRANCHNO = m_currentDeleteItem->BRANCHNO;
		m_reservedStockToUpdate->ARTICLENO = m_currentDeleteItem->ARTICLENO;
		m_reservedStockToUpdate->RESERVTYPE = 0; // always 0 !

		sqlStatus = Stockreservation_SelArticleReserv(m_reservedStockToUpdate, sqlErrorMsg, bIsTrans);

		if (sqlStatus == IS_OK)
		{
			errMsg.format("%s: current reserved stock (articlereservation) - BranchNo %d, ArtikelNo %ld, Reserved Quantity %ld, Reserved Type %d",
				fun,
				m_reservedStockToUpdate->BRANCHNO,
				m_reservedStockToUpdate->ARTICLENO,
				m_reservedStockToUpdate->RESERVEDQTY,
				m_reservedStockToUpdate->RESERVTYPE);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
		else if (sqlStatus != IS_NOTFOUND)
		{
			errMsg.format("%s: selection for reserved stock for Branch &d and ArticleNo %ld returns error SQL Error %ld: %s",
				fun,
				m_currentDeleteItem->BRANCHNO,
				m_currentDeleteItem->ARTICLENO,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spErrm);
			delete m_reservedStockToUpdate;
			m_reservedStockToUpdate = NULL;
			status = (int)sqlStatus;
		}
	}
	return status;
}

int CstStockReservation::CheckForSubsequentDeliveryEntries(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::CheckForSubsequentDeliveryEntries";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error
	delete m_subsequentDeliveryItemToDelete;
	m_subsequentDeliveryItemToDelete = NULL;

	stockreservationnachlieferposS subsequentDelivery;
	subsequentDelivery.KDAUFTRAGNR = m_currentDeleteItem->KDAUFTRAGNR;
	subsequentDelivery.IDFNR = m_currentDeleteItem->CUSTOMERNO;
	subsequentDelivery.ARTIKEL_NR = m_currentDeleteItem->ARTICLENO;
	subsequentDelivery.FETCH_REL = SET_OPEN; // open cursor select for more than one possible entry

	sqlStatus = Stockreservation_SelNachlieferPos(&subsequentDelivery, sqlErrorMsg, bIsTrans);
	while (sqlStatus == IS_OK)
	{
		// only the last element will be stored, but due to the parameters
		// on deletion all entries will be delete in one statment later
		delete m_subsequentDeliveryItemToDelete;
		m_subsequentDeliveryItemToDelete = new stockreservationnachlieferposS(subsequentDelivery);

		errMsg.format("%s: open subsequent delivery entry (nachlieferpos) for OrderNo %ld, CustomerNo %ld, ArticleNo %ld, Quantity %ld, PosType %d - will be deleted.",
			fun,
			m_subsequentDeliveryItemToDelete->KDAUFTRAGNR,
			m_subsequentDeliveryItemToDelete->IDFNR,
			m_subsequentDeliveryItemToDelete->ARTIKEL_NR,
			m_subsequentDeliveryItemToDelete->MENGE,
			m_subsequentDeliveryItemToDelete->POSTYP);
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);

		// report next possible entry
		subsequentDelivery.FETCH_REL = SET_FETCH;
		sqlStatus = Stockreservation_SelNachlieferPos(&subsequentDelivery, sqlErrorMsg, bIsTrans);
	}
	if (sqlStatus = IS_NOTFOUND)
	{
		// close cursor
		subsequentDelivery.FETCH_REL = SET_CLOSE;
		sqlStatus = Stockreservation_SelNachlieferPos(&subsequentDelivery, sqlErrorMsg, bIsTrans);
	}
	else
	{
		// error do not delete
		errMsg.format("%s: selection returns error SQL Error %ld: %s",
			fun,
			sqlErrorMsg->lSqlcode,
			sqlErrorMsg->spErrm);
		delete m_subsequentDeliveryItemToDelete;
		m_subsequentDeliveryItemToDelete = NULL;
		status = (int) sqlStatus;
	}

	if (m_subsequentDeliveryItemToDelete != NULL)
	{
		errMsg.format("%s: open subsequent delivery entries exist. Current deletion of cststockreserved entry will not be returned to current stock.");
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
	}
	return status;
}

int CstStockReservation::DeleteSubsequentDeliveryEntries(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteSubsequentDeliveryEntries";
	basar::VarString errMsg;

	int status = 0; // no error
	retClient sqlStatus = IS_OK; // no error

	if (m_subsequentDeliveryItemToDelete != NULL)
	{
		sqlStatus = Stockreservation_DeleteNachlieferPos(m_subsequentDeliveryItemToDelete, sqlErrorMsg, bIsTrans);
		if (sqlStatus == IS_OK)
		{
			errMsg.format("%s: deleted subsequent delivery entries (nachlieferpos)", fun);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
		else
		{
			errMsg.format("%s: deletion of subsequent delivery entries (nachlieferpos) failed: SQL Error %d: %s",
				fun,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spErrm);
			BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), errMsg);
			status = (int)sqlStatus;
		}
	}
	return status;
}

int CstStockReservation::DeleteCstStockReservedEntry(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteCstStockReservedEntry";
	basar::VarString errMsg;

	int status = IS_OK; // no error

	if (m_currentDeleteItem != NULL)
	{
		status = Stockreservation_DeleteCstStockReservedEntry(m_currentDeleteItem, sqlErrorMsg, bIsTrans);
		if (status == IS_OK)
		{
			errMsg.format("%s: deleted cstockreserved entry", fun);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
		else
		{
			errMsg.format("%s: deletion of cstockreservedentry failed: SQL Error %d: %s",
				fun,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spErrm);
			BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
	}
	return status;
}

int CstStockReservation::DeleteInterbranchRequest(tError* sqlErrorMsg, bool bIsTrans)
{
	const char* fun = "CstStockReservation::DeleteInterbranchRequest";
	basar::VarString errMsg;

	int status = IS_OK;

	if (m_ibtRequestToDelete != NULL)
	{
		status = Stockreservation_DeleteIbtRequest(m_ibtRequestToDelete, sqlErrorMsg, bIsTrans);
		if (status == IS_OK)
		{
			errMsg.format("%s: deleted ibtrequest entry", fun);
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
		else
		{
			errMsg.format("%s: deletion of ibtrequest %ld failed: SQL Error %d: %s",
				fun,
				m_ibtRequestToDelete->IBTREQUESTID,
				sqlErrorMsg->lSqlcode,
				sqlErrorMsg->spErrm);
			BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), errMsg);
		}
	}
	return status;
}


