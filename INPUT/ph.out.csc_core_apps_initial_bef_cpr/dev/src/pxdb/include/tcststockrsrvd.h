#ifndef GUARD_CSTSTOCKRESERVED_H
#define GUARD_CSTSTOCKRESERVED_H

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the cststockreserved table                       */
/*----------------------------------------------------------------------------*/
typedef enum CrsCstStockReserved
{
	cCRSCSTSTOCKRESERVED_Default				= 1,
	cCRSCSTSTOCKRESERVED_CustomerReservations	= 2, /* reservations for customer */
	cCRSCSTSTOCKRESERVED_AllReservations		= 4, /* all reservations for article */
	cCRSCSTSTOCKRESERVED_OldReservations		= 8  /* old reservations to delete */
} tCRSID_CSTSTOCKRESERVED;

/*****************************************************************************/
/*  CstStockReserved Table                                                   */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tCSTSTOCKRESERVED
{
    short         BranchNo;                     /* Filialnummer */
    long          CustomerNo;                   /* Customerno*/
    long          ArticleNo;                    /* Article number*/
    long          ReservedQty;                  /* Maximum Quantity*/
    long          DateFrom;                     /* Date From*/
    long          TimeFrom;                     /* Time from*/
    long          DateTo;                       /* Date To*/
    long          TimeTo;                       /* Time to*/
    long          KdAuftragNr;                  /* Kunde Auftrag Nummer */
    short         ReservType;                   /* Reserve Type*/
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/*----------------------------------------------------------------------------*/
/* forward declarations for pxverbund                                         */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int pxCustStockReservedStartBrowse (struct tCSTSTOCKRESERVED* record, const char* dbName, int browseid);
int pxCustStockReservedGetNext     (struct tCSTSTOCKRESERVED* record);
int pxCustStockReservedEndBrowse   ();
int pxCustStockReservedRead        (struct tCSTSTOCKRESERVED* record, const char* dbName);
int pxCustStockReservedReadLock    (struct tCSTSTOCKRESERVED* record, const char* dbName);
int pxCustStockReservedUpdate      (struct tCSTSTOCKRESERVED* record, const char* dbName);
int pxCustStockReservedInsert      (struct tCSTSTOCKRESERVED* record, const char* dbName);
int pxCustStockReservedDelete      (struct tCSTSTOCKRESERVED* record, const char* dbName);

#ifdef __cplusplus
}
#endif

#endif   // GUARD_CSTSTOCKRESERVED_H
