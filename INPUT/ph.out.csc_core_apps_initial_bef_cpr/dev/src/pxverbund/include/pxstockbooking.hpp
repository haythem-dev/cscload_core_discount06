/***************************************************************************************************************************/

#ifndef PXSTOCKBOOKING_INC
#define PXSTOCKBOOKING_INC

/***************************************************************************************************************************/

#include "pxerrorloggable.hpp"
#include <types/reservationtypeenum.inc>
#include "ibttype.hpp"
#include <libbasar_definitions.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigptr.h>

/***************************************************************************************************************************/

class pxSession;
class pxArtBase;
class IArticleStockBooking;
class pxCustBase;
class pxOrder;
class pxOrderItem;
class pxFiliale;
class pxCustStockReserved;
class pxCustStockReservedList;
class pxArtReservation;
class pxArtReservationList;
struct ArticleAccountInfo;

/***************************************************************************************************************************/
// All types of pharmos transactions (handled in phatra).
// enum GoodsInBookingType
// {
// 	ACCOUNT_ADD_QUANTITY			= 1,
// 	ACCOUNT_SUB_QUANTITY			= 2,
// 	ACCOUNT_SET_QUANTITY			= 8,
//
// 	CERTIFICATE_NOT_AVAILABLE		= 3,
// 	CERTIFICATE_AVAILABLE			= 4,
// 	CERTIFICATE_UPDATE				= 7,
//
// 	PACKAGE_INSERT_NOT_AVAILABLE	= 5,
//
// 	BATCH_RECALL					= 6,
// 	CANCEL_BATCH_RECALL 			= 9
// };

/***************************************************************************************************************************/

enum GlobalReservationType
{
	GLOBAL_RESTYPE_INFOORDER			= 1,
	GLOBAL_RESTYPE_RESTDELIVERY			= 7,
	GLOBAL_RESTYPE_IBT 					= 9,
	GLOBAL_RESTYPE_OPENORDER			= 11
};

// enum ReservationType
// {
// 	RESTYPE_UNKNOWN					= -1,
//
// 	// reservations in articlereservation
// 	RESTYPE_PHARMACYGROUP			= 0,	// 0 reservation on pharmacygroup level
// 	RESTYPE_NO_SALES_EFFECTIVE		= 2,	// 2 reservation on pharmacygroup level, but not sales effectiv
// 	RESTYPE_NO_CERTIFICATE			= 3,	// 3 no certificate available
// 	RESTYPE_NO_PACKAGE_INSERT		= 4,	// 4 no package insert(beipack)
// 	RESTYPE_BATCH_RECALL			= 5,	// 5 batch recall (SH,2012-05-25)
// 	RESTYPE_TENDER					= 13,	// 13 tender
// 	RESTYPE_BLOCKED_AUTOMAT			= 14,	// 14 Automat (ROWA) blocked
//
// 	// reservations in custstockreserved
// 	RESTYPE_INFOORDER_FREE			= 1,
// 	RESTYPE_INFOORDER_RESERVED		= 6,
// 	RESTYPE_RESTDELIVERY_FREE		= 7,
// 	RESTYPE_RESTDELIVERY_RESERVED	= 8,
// 	RESTYPE_IBT_FREE				= 9,
// 	RESTYPE_IBT_RESERVED			= 10,
// 	RESTYPE_OPENORDER_FREE			= 11,
// 	RESTYPE_OPENORDER_RESERVED		= 12
// };

enum OrderContext
{
	ORDER_CONTEXT_DEFAULT			= 0,
	ORDER_CONTEXT_RESTDELIVERY		= 1,
	ORDER_CONTEXT_IBT				= 2
//	ORDER_CONTEXT_QUARANTINE		= 3,
//	ORDER_CONTEXT_BATCH_RECALL		= 4,
//	ORDER_CONTEXT_TENDER			= 5
};

/***************************************************************************************************************************/

enum TransactionType
{
	TRANSACTIONTYPE_DEBIT					= 'a',	// Abverkauf
	TRANSACTIONTYPE_GOODSIN 				= 'b',  // "WE" bookings (phatra only)
	TRANSACTIONTYPE_CUSTOMERRETURNS 		= 'c',  // "RK" bookings (phatra only)
	TRANSACTIONTYPE_STOCKRECONCILIATION 	= 'd',  // "LR" bookings (phatra only)
	TRANSACTIONTYPE_PERMANENTINVENTORY		= 'e',  // "PI" bookings (phatra only)
	TRANSACTIONTYPE_AUXDELIVERY 			= 'g',  // IBT booking in demanding branch
	TRANSACTIONTYPE_SHORTAGE				= 'k',  // Defekt
	TRANSACTIONTYPE_AUXBOOKED				= 'm',  // IBT booking in delivering branch
	TRANSACTIONTYPE_BATCHINCONSISTENCY		= 'o',  // "WC" booking (phatra only)
	TRANSACTIONTYPE_VSEAMOUNT				= 'q',  // correction stockdifference or article not found in PHARMOS (corpha only)
	TRANSACTIONTYPE_SUPPLY  				= 'r',  // do we need it????
//	TRANSACTIONTYPE_SUPPLY_DEBIT			= 's',  // do we need it????
//	TRANSACTIONTYPE_PREDELIVERY 			= 't',  // do we need it????
//	TRANSACTIONTYPE_RELEASE_RES_STOCK		= 'u',  // do we need it????
	TRANSACTIONTYPE_QUOTA_EXCEEDED			= 'v',  // KontingentDefekt
//	TRANSACTIONTYPE_RESERVE_RESTDEL 		= 'w',  // --> 'x' MoveType 7/8
	TRANSACTIONTYPE_CODEBLOCAGE 			= 'y',  // "CB" bookings (phatra only)
	TRANSACTIONTYPE_RESERVATION 			= 'x',  // new !!!
	TRANSACTIONTYPE_TRANSFERQUARANTINE		= 'z',  // "TR" bookings (phatra only)

	TRANSACTIONTYPE_PICKING_CORRECTION		= 'A'   // correction stockdifference AFTER picking (phatra only)
//	TRANSACTIONTYPE_RESTDELSAMEDAY			= 'S'
};
/***************************************************************************************************************************/

//static const char* const PHARMACYGROUP_NO_CERTIFICATE 	= "299";
//static const char* const PHARMACYGROUP_NO_PACKAGE_INSERT	= "299";
//static const char* const PHARMACYGROUP_BATCH_RECALL 		= "999";

/***************************************************************************************************************************/

class pxStockBooking : public pxErrorLoggable
{

public:
	virtual ~pxStockBooking();

	// Bestandsbuchungen unabhängig von KSC-Aufträgen (z.B. Wareneingang, Lagerrevision, Retouren etc. ? z.B. durch phatra)
	// bezieht sich auf artikellokal.bestand bzw. articlereservation, falls aktiv.
	// Die Aufteilung zwischen artikellokal und articlereservation erfolgt nach festgelegtem Schema (prozentual, Maximum berücksichtigen).
	long 						AddQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info = 0, const bool checkReservation = true);
	long 						SubQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info = 0);
	long 						SetQtyInStock(pxArtBase& article, const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info = 0);

	long						CreateEmptyArticleReservation(pxArtBase& article, const enum ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long maxqty, const short reservepct);
	long						DeleteArticleReservation     (pxArtBase& article, const enum ReservationTypeEnum restype, const basar::VarString& pharmacygroup);

	long						AddArticleReservation        (pxArtBase& article, const enum ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty);
	long						ReleaseArticleReservation    (pxArtBase& article, const enum ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty);
	long						SetAbsoluteArticleReservation(pxArtBase& article, const enum ReservationTypeEnum restype, const basar::VarString& pharmacygroup, const long qty);

	// Bestandsabfragen ohne Reservierung
	long						GetAvailableQtyInStock(pxArtBase& article);
	long						GetAvailableQtyInStock(pxArtBase& article, pxCustBase& customer);

	long						GetReservedQtyInStock(pxArtBase& article);
	long						GetReservedQtyInStock(pxArtBase& article, pxCustBase& customer, const enum OrderContext orderContext);
	long						GetBookableQuantity(pxOrderItem& item, pxArtBase& article);

	long						GetTotalQtyInStock(pxArtBase& article);

	// Bestandsabfrage mit Reservierung
	// Schreibt custstockreserved Satz mit reservetype 1 oder 6 und bucht entsprechend von artikellokal.bestand und / oder articlereservation ab.
	// von articlereservation			-> custstockreserved type 6
	// Rest von artikellokal.bestand	-> custstockreserved type 1
	long						AddReservationForInfoOrder(pxArtBase& article, pxCustBase& customer, const long qty);
	long						CancelReservationForInfoOrder(pxArtBase& article, pxCustBase& customer, const long qty);


	// Reservierung für Nachlieferpositionen (Reservierung für einen Kunden nach WE ? phatra)
	//  	Schreibt custstockreserved Satz mit reservetype 7 oder 8 und bucht entsprechend von artikellokal.bestand und / oder articlereservation ab.
	//	 	von articlereservation				-> custstockreserved type 8
	//		Rest von artikellokal.bestand		-> custstockreserved type 7
	long						AddReservationForRestDelivery(pxArtBase& article, pxCustBase& customer, const long qty);


	// Reservierung für Verbundlieferung
	//  	Schreibt custstockreserved Satz mit reservetype 7 oder 8 und bucht entsprechend von artikellokal.bestand und / oder articlereservation ab.
	//		von articlereservation			-> custstockreserved type 10
	//		Rest von artikellokal.bestand	-> custstockreserved type 9
	long						AddReservationForIBT   (const long articleNo, const long customerNo, const short branchNoIBT, const long qty);
	long						CancelReservationForIBT(const long articleNo, const long customerNo, const short branchNoIBT, const long qty);

	// Eröffnen einer neuen Auftragsposition
	// Schreibt custstockreserved Satz mit reservtype 9 oder 10 und bucht die entsprechende Menge ab:
	long						AddReservationForOpenOrder(pxOrderItem& item, const long qty);

	// Storno (Undo) einer Auftragsposition
	// Löscht custstockreserved Sätze und schreibt Bestand zurück
	// custstockreserved type 11			-> artikellokal.bestand
	// custstockreserved type 12			-> articlereservation
	long						CancelReservationForOpenOrder(pxOrderItem& item, const long qty);


	// Abschluß einer Auftragsposition
	// Verringert die Mengen in den entsprechenden custstockreserved Sätzen und löscht sie, wenn Menge auf 0 geht (type 11 und 12).
	long						ReleaseReservationForOpenOrder(pxOrderItem& item, const long qty);

	long						AddReservationForCCOrder(pxArtBase& article, pxCustBase& customer, const long qty);
	long						CancelReservationForCCOrder(pxArtBase& article, pxCustBase& customer, const long qty);

private:
	pxStockBooking(pxSession* session);
	friend class pxSession;
	long						GetReservedQtyInStockInternal(IArticleStockBooking* article);

	void						InitContext(pxArtBase* article, pxCustBase* customer = NULL, pxOrderItem* orderitem = NULL, const bool readReservations = true);
	void						InitCustomerStockReservation();
	void						InitArticleReservation();
	pxCustStockReserved*		FindCustomerStockReservation(const enum ReservationTypeEnum reserveType);
	pxCustStockReserved*		FindCustomerStockReservation(const enum ReservationTypeEnum reserveType, const long orderno);
	long						AddCustomerStockReservation(const long qty, const enum ReservationTypeEnum reserveType);
	long						AddCustomerStockReservation(const short branchno, const long articleno, const long customerno, const long qty, const enum ReservationTypeEnum reserveType);
	long						ReduceCustomerStockReservation(const long qty, const enum ReservationTypeEnum reserveType);

	PURCHASE_RELEVANCE_MODE		GetPurchaseRelevanceMode();
	void						WriteArticleAccount(const long qty, const TransactionType transactiontype, const struct ArticleAccountInfo* info);

	long						GetReservedQty(const enum GlobalReservationType reservationType);

	pxArtReservation*			findArticleReservation(const enum ReservationTypeEnum type);

	bool						CheckAndLockArticle();
	bool						CheckAndLockArticleReservation();

	pxSession*					m_Session;

	pxCustStockReservedList*	m_CustomerStockReservationList;
	pxArtReservationList*		m_ArticleReservationList;

	IArticleStockBooking*		m_CurrentArticle;
	pxCustBase*					m_CurrentCustomer;
	pxOrderItem*				m_CurrentOrderItem;
	pxArtReservation*			m_CurrentArticleReservation;
	libcsc::stockbooking::IOrderTypeReservationConfigPtr		m_CurrentReservationConfig;
};

/***************************************************************************************************************************/

#endif // PXSTOCKBOOKING_INC

/***************************************************************************************************************************/
