/*(c)
********************* PHARMX Customer Order Entry Server *********************


Embedded SQL for C application


FILE: tcststockrsrvd.c (.sqc)

Database functions




FUNCTIONS:

pxCustStockReservedStartBrowse  declare and open Cursor
pxCustStockReservedGetNext      get next record
pxCustStockReservedEndBrowse    close cursor
pxCustStockReservedRead         get one record
pxCustStockReservedReadLock     get one record with lock
pxCustStockReservedInsert       Insert record
pxCustStockReservedUpdate       Update record
pxCustStockReservedDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include "pxdbfunc.h"
#include <ndefs.h>
#include <tcststockrsrvd.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedStartBrowse                         */
/*                                                                   */
/*      Declare and Open a Cursor   (general)                        */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustStockReservedStartBrowse
(
	struct tCSTSTOCKRESERVED * record,
	const char* dbName,
	int browseid
 )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED* recordp;
	char sql[1024];
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_StartBrowse;
	recordp = record;

	sprintf(sql,
		"SELECT "
			"BRANCHNO, "
			"CUSTOMERNO, "
			"ARTICLENO, "
			"RESERVEDQTY, "
			"DATEFROM, "
			"TIMEFROM, "
			"DATETO, "
			"TIMETO, "
			"KDAUFTRAGNR, "
			"RESERVTYPE "
		"FROM %s:CSTSTOCKRESERVED ",
		dbName);

	switch (browseid)
	{
 		case cCRSCSTSTOCKRESERVED_OldReservations:
			strcat(sql, "WHERE BRANCHNO = ? AND RESERVTYPE IN (1, 6) AND (DATETO < ? OR (DATETO = ? AND TIMETO <= ? ))");
			break;
 		case cCRSCSTSTOCKRESERVED_AllReservations:
			strcat(sql, "WHERE BRANCHNO = ? AND ARTICLENO = ? ");
			break;
 		case cCRSCSTSTOCKRESERVED_CustomerReservations:
			strcat(sql, "WHERE BRANCHNO = ? AND ARTICLENO = ? AND CUSTOMERNO = ? ");
			break;
		case cCRSCSTSTOCKRESERVED_Default:
		default:
			break;
	}

	EXEC SQL PREPARE browse_stmt from :sql;

	EXEC SQL DECLARE cststockreserved_browse_cur CURSOR WITH HOLD FOR browse_stmt;

	switch (browseid)
	{
 		case cCRSCSTSTOCKRESERVED_OldReservations:
			EXEC SQL OPEN cststockreserved_browse_cur USING
				:recordp->BranchNo,
				:recordp->DateTo,
				:recordp->DateTo,
				:recordp->TimeTo;
			break;
 		case cCRSCSTSTOCKRESERVED_AllReservations:
			EXEC SQL OPEN cststockreserved_browse_cur USING
				:recordp->BranchNo,
				:recordp->ArticleNo;
			break;
 		case cCRSCSTSTOCKRESERVED_CustomerReservations:
			EXEC SQL OPEN cststockreserved_browse_cur USING
				:recordp->BranchNo,
				:recordp->ArticleNo,
				:recordp->CustomerNo;
			break;
		case cCRSCSTSTOCKRESERVED_Default:
		default:
			EXEC SQL OPEN cststockreserved_browse_cur;
			break;
	}

	if (SQLCODE == 0)        return 0;
	if (SQLCODE == 100)      return cDBXR_NOTFOUND;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedGetNext                             */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustStockReservedGetNext
(
	struct tCSTSTOCKRESERVED* record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED* recordp;
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_GetNext;
	recordp = record;

	EXEC SQL FETCH cststockreserved_browse_cur INTO
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->ArticleNo,
		:recordp->ReservedQty,
		:recordp->DateFrom,
		:recordp->TimeFrom,
		:recordp->DateTo,
		:recordp->TimeTo,
		:recordp->KdAuftragNr,
		:recordp->ReservType;

	if (SQLCODE == 0)    return 0;
	if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedEndBrowse                           */
/*                                                                   */
/*      Close a Cursor   (general)                                   */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustStockReservedEndBrowse
(
)
{
	functionnr = F_CSTSTOCKRESERVED*10+F_EndBrowse;

	EXEC SQL CLOSE cststockreserved_browse_cur;
	EXEC SQL FREE browse_stmt;
	return 0;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedRead                                */
/*                                                                   */
/*      Get one record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustStockReservedRead
(
	struct tCSTSTOCKRESERVED* record,
	const char* dbName
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED* recordp;
	char sql[1024];
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_Read;
	recordp = record;

	sprintf(sql,
		"SELECT "
			"BRANCHNO, "
			"CUSTOMERNO, "
			"ARTICLENO, "
			"RESERVEDQTY, "
			"DATEFROM, "
			"TIMEFROM, "
			"DATETO, "
			"TIMETO, "
			"KDAUFTRAGNR, "
			"RESERVTYPE "
		"FROM %s:CSTSTOCKRESERVED "
		"WHERE "
			"BRANCHNO = ? AND "
			"CUSTOMERNO = ? AND "
			"ARTICLENO = ? AND "
			"RESERVTYPE = ? AND "
			"KDAUFTRAGNR = ? AND "
			"DATEFROM = ? ",
		dbName);

	EXEC SQL PREPARE sel_stmt from :sql;

	EXEC SQL DECLARE cststockreserved_sel_cur CURSOR WITH HOLD FOR sel_stmt;

	EXEC SQL OPEN cststockreserved_sel_cur USING
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->ArticleNo,
		:recordp->ReservType,
		:recordp->KdAuftragNr,
		:recordp->DateFrom;

	if (SQLCODE == 0)
	{
		EXEC SQL FETCH cststockreserved_sel_cur INTO
			:recordp->BranchNo,
			:recordp->CustomerNo,
			:recordp->ArticleNo,
			:recordp->ReservedQty,
			:recordp->DateFrom,
			:recordp->TimeFrom,
			:recordp->DateTo,
			:recordp->TimeTo,
			:recordp->KdAuftragNr,
			:recordp->ReservType;
	}

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else if (SQLCODE == 1)                /* found, but more than 1 exists */
	{
		retval = cDBXR_ISDUPLICATE;
	}
	else if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
	EXEC SQL CLOSE cststockreserved_sel_cur;
	EXEC SQL FREE sel_stmt;

	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedReadLock                            */
/*                                                                   */
/*      Get one record with lock                                     */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustStockReservedReadLock
(
	struct tCSTSTOCKRESERVED* record,
	const char* dbName
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED* recordp;
	char sql[1024];
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_ReadLock;
	recordp = record;

	sprintf(sql,
		"SELECT "
			"BRANCHNO, "
			"CUSTOMERNO, "
			"ARTICLENO, "
			"RESERVEDQTY, "
			"DATEFROM, "
			"TIMEFROM, "
			"DATETO, "
			"TIMETO, "
			"KDAUFTRAGNR, "
			"RESERVTYPE "
		"FROM %s:CSTSTOCKRESERVED "
		"WHERE "
			"BRANCHNO = ? AND "
			"CUSTOMERNO = ? AND "
			"ARTICLENO = ? AND "
			"RESERVTYPE = ? AND "
			"KDAUFTRAGNR = ? AND "
			"DATEFROM = ? "
		"FOR UPDATE",
		dbName);

	EXEC SQL PREPARE sel_lock_stmt from :sql;

	EXEC SQL DECLARE cststockreserved_upd_cur CURSOR WITH HOLD FOR sel_lock_stmt;

	EXEC SQL OPEN cststockreserved_upd_cur USING
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->ArticleNo,
		:recordp->ReservType,
		:recordp->KdAuftragNr,
		:recordp->DateFrom;

	if (SQLCODE == 0)
	{
		EXEC SQL FETCH cststockreserved_upd_cur INTO
			:recordp->BranchNo,
			:recordp->CustomerNo,
			:recordp->ArticleNo,
			:recordp->ReservedQty,
			:recordp->DateFrom,
			:recordp->TimeFrom,
			:recordp->DateTo,
			:recordp->TimeTo,
			:recordp->KdAuftragNr,
			:recordp->ReservType;
	}
	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else if (SQLCODE == 1)                /* found, but more than 1 exists */
	{
		retval = cDBXR_ISDUPLICATE;
	}
	else if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedUpdate                              */
/*                                                                   */
/*      Update  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustStockReservedUpdate
(
	struct tCSTSTOCKRESERVED* record,
	const char* dbName
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED* recordp;
	char sql[1024];
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_Update;
	recordp = record;

	sprintf(sql, "UPDATE %s:CSTSTOCKRESERVED SET "
		"BRANCHNO = ?, "
		"CUSTOMERNO = ?, "
		"ARTICLENO = ?, "
		"RESERVEDQTY = ?, "
		"DATEFROM = ?, "
		"TIMEFROM = ?, "
		"DATETO = ?, "
		"TIMETO = ?, "
		"KDAUFTRAGNR = ?, "
		"RESERVTYPE = ? "
		"WHERE CURRENT OF cststockreserved_upd_cur",
		dbName);

	EXEC SQL PREPARE upd_stmt FROM :sql;

	if (SQLCODE == 0)
	{
		EXEC SQL EXECUTE upd_stmt USING
			:recordp->BranchNo,
			:recordp->CustomerNo,
			:recordp->ArticleNo,
			:recordp->ReservedQty,
			:recordp->DateFrom,
			:recordp->TimeFrom,
			:recordp->DateTo,
			:recordp->TimeTo,
			:recordp->KdAuftragNr,
			:recordp->ReservType;
	}

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
	EXEC SQL CLOSE cststockreserved_upd_cur;
    EXEC SQL FREE upd_stmt;

	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedInsert                              */
/*                                                                   */
/*      Insert  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCustStockReservedInsert
(
	struct tCSTSTOCKRESERVED * record,
	const char* dbName
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED * recordp;
	char sql[1024];
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_Insert;
	recordp = record;

	sprintf(sql, "INSERT INTO %s:CSTSTOCKRESERVED ("
		"BRANCHNO, "
		"CUSTOMERNO, "
		"ARTICLENO, "
		"RESERVEDQTY, "
		"DATEFROM, "
		"TIMEFROM, "
		"DATETO, "
		"TIMETO, "
		"KDAUFTRAGNR, "
		"RESERVTYPE) "
		"VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )",
		dbName);
		
	EXEC SQL PREPARE ins_stmt FROM :sql;
	if (SQLCODE == 0)
	{
		EXEC SQL EXECUTE ins_stmt USING
			:recordp->BranchNo,
			:recordp->CustomerNo,
			:recordp->ArticleNo,
			:recordp->ReservedQty,
			:recordp->DateFrom,
			:recordp->TimeFrom,
			:recordp->DateTo,
			:recordp->TimeTo,
			:recordp->KdAuftragNr,
			:recordp->ReservType;
	}

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else if (SQLCODE == -2601)
	{
		retval = cDBXR_ISDUPLICATE;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
    EXEC SQL FREE ins_stmt;

	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustStockReservedDelete                              */
/*                                                                   */
/*      delete  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, else error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxCustStockReservedDelete
(
	struct tCSTSTOCKRESERVED* record,
	const char* dbName
 )
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tCSTSTOCKRESERVED * recordp;
	char sql[1024];
	EXEC SQL END DECLARE SECTION;

	functionnr = F_CSTSTOCKRESERVED*10+F_Delete;
	recordp = record;

	sprintf(sql, "DELETE FROM %s:CSTSTOCKRESERVED "
		"WHERE BRANCHNO = ? "
		"AND CUSTOMERNO = ? "
		"AND ARTICLENO = ? "
		"AND RESERVTYPE = ? "
		"AND KDAUFTRAGNR = ? "
		"AND DATEFROM = ? ",
		dbName);

	EXEC SQL PREPARE del_stmt FROM :sql;
	
	if (SQLCODE == 0)
	{
		EXEC SQL EXECUTE del_stmt USING
			:recordp->BranchNo,
			:recordp->CustomerNo,
			:recordp->ArticleNo,
			:recordp->ReservType,
			:recordp->KdAuftragNr,
			:recordp->DateFrom;
	}

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
	EXEC SQL FREE del_stmt;

	return retval;
}
