
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include "transmissionresponse.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include "pxloggerpool.h"

EXEC SQL include locator;

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTransmissionResponseRead                             */
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

int pxTransmissionResponseRead
(
	struct tTRANSMISSIONRESPONSE* record
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tTRANSMISSIONRESPONSE* recordp;
	char sql[256];
	loc_t xmlresponseLocator;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_ARTIKELKONTO * 10 + F_Read;
	recordp = record;

	strcpy(sql, 
		"SELECT id, request_id, support_id, branchno, customerno, is_offer, responseasxml, create_date "
		"FROM orderresponses "
		"WHERE request_id = ?");

log4cplus_debug(LOGGER_SESSION, sql);

	xmlresponseLocator.loc_loctype = LOCMEMORY;		/* set loctype for in memory */
	xmlresponseLocator.loc_bufsize =-1;				/* let db get buffer */
	xmlresponseLocator.loc_oflags = 0;				/* clear loc_oflags */
	xmlresponseLocator.loc_mflags = 0;				/* set loc_mflags to 0 */

	EXEC SQL PREPARE transmissionresponse_read_query FROM :sql;

log4cplus_debug(LOGGER_SESSION, "after prepare");

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL DECLARE transmissionresponse_read_cursor CURSOR FOR transmissionresponse_read_query;

log4cplus_debug(LOGGER_SESSION, "after declare cursor");

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL OPEN transmissionresponse_read_cursor USING :recordp->Request_Id;

log4cplus_debug(LOGGER_SESSION, "after declare cursor");

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL FETCH transmissionresponse_read_cursor INTO
		:recordp->Id,
		:recordp->Request_Id,
		:recordp->Support_Id,
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->Is_Offer,
		:xmlresponseLocator,
		:recordp->Create_Date;

log4cplus_debug(LOGGER_SESSION, "after fetch cursor");

	if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
		recordp->ResponseAsXml = xmlresponseLocator.loc_buffer;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}

	EXEC SQL CLOSE transmissionresponse_read_cursor;
	EXEC SQL FREE transmissionresponse_read_query;
	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTransmissionResponseReadLock                         */
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
int pxTransmissionResponseReadLock
(
	struct tTRANSMISSIONRESPONSE* record
)
{
	int retval = cDBXR_NORMAL;

	EXEC SQL BEGIN DECLARE SECTION;
	struct tTRANSMISSIONRESPONSE* recordp;
	char sql[256];
	loc_t xmlresponseLocator;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_ARTIKELKONTO * 10 + F_ReadLock;
	recordp = record;

	strcpy(sql, 
		"SELECT id, request_id, support_id, branchno, customerno, is_offer, responseasxml, create_date "
		"FROM orderresponses "
		"WHERE request_id = ? "
		"FOR UPDATE");

	xmlresponseLocator.loc_loctype = LOCMEMORY;		/* set loctype for in memory */
	xmlresponseLocator.loc_bufsize =-1;				/* let db get buffer */
	xmlresponseLocator.loc_oflags = 0;				/* clear loc_oflags */
	xmlresponseLocator.loc_mflags = 0;				/* set loc_mflags to 0 */


	EXEC SQL PREPARE transmissionresponse_readlock_query FROM :sql;

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL DECLARE transmissionresponse_readlock_cursor CURSOR WITH HOLD FOR transmissionresponse_readlock_query;

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL OPEN transmissionresponse_readlock_cursor USING :recordp->Request_Id;

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	EXEC SQL FETCH transmissionresponse_readlock_cursor INTO
		:recordp->Id,
		:recordp->Request_Id,
		:recordp->Support_Id,
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->Is_Offer,
		:xmlresponseLocator,
		:recordp->Create_Date;

	if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
		recordp->ResponseAsXml = xmlresponseLocator.loc_buffer;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}

//	EXEC SQL FREE transmissionresponse_readlock_query;
	return retval;

}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTransmissionResponseUpdate                           */
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

int pxTransmissionResponseUpdate
(
    struct tTRANSMISSIONRESPONSE* record
)
{
	int retval = cDBXR_NORMAL;

    EXEC SQL BEGIN DECLARE SECTION;
    struct tTRANSMISSIONRESPONSE* recordp;
    char sql[256];
    loc_t xmlresponseLocator;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Update;
    recordp = record;

    strcpy( sql,"UPDATE ORDERRESPONSES SET request_id = ?, support_id = ?,branchno = ?,customerno = ?,is_offer = ?,responseasxml = ?,create_date = ? "
			"WHERE CURRENT OF transmissionresponse_readlock_cursor");

    exec sql prepare transmissionresponse_upd_stmt from :sql;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

	xmlresponseLocator.loc_loctype = LOCMEMORY;     /* set loctype for in memory */
	xmlresponseLocator.loc_buffer = recordp->ResponseAsXml;
	xmlresponseLocator.loc_bufsize = strlen(recordp->ResponseAsXml) + 1;
	xmlresponseLocator.loc_size = strlen(recordp->ResponseAsXml);

    exec sql execute transmissionresponse_upd_stmt using
        :recordp->Request_Id,
        :recordp->Support_Id,
        :recordp->BranchNo,
        :recordp->CustomerNo,
        :recordp->Is_Offer,
        :xmlresponseLocator,
        :recordp->Create_Date;

	if (SQLCODE == 100)
	{
		retval = cDBXR_NOTFOUND;
	}
	else if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
	EXEC SQL CLOSE transmissionresponse_readlock_cursor;
	EXEC SQL FREE transmissionresponse_upd_stmt;
	return retval;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTransmissionResponseInsert                           */
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
int pxTransmissionResponseInsert
(
    struct tTRANSMISSIONRESPONSE* record
)
{
	int retval = cDBXR_NORMAL;

    EXEC SQL BEGIN DECLARE SECTION;
    struct tTRANSMISSIONRESPONSE* recordp;
    char sql[1024];
    loc_t xmlresponseLocator;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Insert;
    recordp = record;

    sprintf(sql, "INSERT INTO ORDERRESPONSES (request_id,support_id,branchno,customerno,is_offer,responseasxml,create_date) "
				"VALUES (?, ?, ?, ?, ?, ?, ?)");
	
	EXEC SQL PREPARE transmissionresponse_ins_stmt FROM :sql;

	if (SQLCODE != 0)
		return cDBXR_IOERROR;

	xmlresponseLocator.loc_loctype = LOCMEMORY;     /* set loctype for in memory */
	xmlresponseLocator.loc_buffer = recordp->ResponseAsXml;
	xmlresponseLocator.loc_bufsize = strlen(recordp->ResponseAsXml) + 1;
	xmlresponseLocator.loc_size = strlen(recordp->ResponseAsXml);

	EXEC SQL EXECUTE transmissionresponse_ins_stmt USING
		:recordp->Request_Id,
		:recordp->Support_Id,
		:recordp->BranchNo,
		:recordp->CustomerNo,
		:recordp->Is_Offer,
		:xmlresponseLocator,
		:recordp->Create_Date;

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
		/* if successful then use generated serial value */
		record->Id = sqlca.sqlerrd[1];
	}
	else if (SQLCODE == -2601)
	{
		retval = cDBXR_ISDUPLICATE;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
    EXEC SQL FREE transmissionresponse_ins_stmt;

	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTransmissionResponseDelete                           */
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

int pxTransmissionResponseDelete
(
    struct tTRANSMISSIONRESPONSE* record
)
{
	int retval = cDBXR_NORMAL;

    EXEC SQL BEGIN DECLARE SECTION;
    struct tTRANSMISSIONRESPONSE * recordp;
    char sql[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Delete;
    recordp = record;

    strcpy(sql, "DELETE FROM ORDERRESPONSES WHERE ID = ?");

    EXEC SQL PREPARE transmissionresponse_del_stmt FROM :sql;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    EXEC SQL EXECUTE transmissionresponse_del_stmt USING :recordp->Id;

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

	EXEC SQL FREE transmissionresponse_del_stmt;

	return retval;
}

