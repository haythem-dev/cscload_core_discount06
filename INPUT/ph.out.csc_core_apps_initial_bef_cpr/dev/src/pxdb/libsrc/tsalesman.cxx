/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application

    Database functions

    FUNCTIONS:


REVISION HISTORY

17 Sep 2015 V1.00 REV 00 written by Martin Zoephel

*/


#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include "pxdbfunc.h"
#include <ndefs.h>
#include "tsalesman.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSalesmanStartBrowse                                 */
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
int pxSalesManStartBrowse
(
     struct tSALESMAN * record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tSALESMAN * recordp;
    char sqlStmt[500];
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_StartBrowse;
    recordp = record;

    switch (browseid)
    {
       case cCRSSALESMAN_GETDATAFORKEY:
    	   EXEC SQL DECLARE C_GETDATAFORKEY CURSOR FOR
		   SELECT
				SALESMAN.BRANCHNO,
				SALESMAN.SALESMANNO,
				SALESMAN.SALESMANNAME,
				SALESMAN.SALESMANSTREET,
				SALESMAN.SALESMANCITY,
				SALESMAN.POSTCODE,
				SALESMAN.SACTIVE,
				SALESMAN.SPREWHOLE,
				SALESMAN.EMAILADRESS
			from SALESMAN
			where branchno = :recordp->BRANCHNO
			and salesmanno = :recordp->SALESMANNO
			and SACTIVE = 1 and emailadress!='';
          EXEC SQL OPEN C_GETDATAFORKEY;
          break;
       case cCRSSALESMAN_GETDATAFORPARTNER:
    	  strcpy(sqlStmt,"SELECT distinct( emailadress ) ");
		  strcat(sqlStmt,"from SALESMAN s ");
		  strcat(sqlStmt,"inner join kunde k on k.personalnrvertr = s.salesmanno and s.branchno = k.vertriebszentrumnr ");
		  strcat(sqlStmt,"where k.partnernr = ? and s.branchno = ? ");
		  strcat(sqlStmt,"and SACTIVE = 1 and emailadress!='' ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETDATAFORPARTNER CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_GETDATAFORPARTNER using :recordp->PARTNERNO, :recordp->BRANCHNO;
    	  break;
       default:
          EXEC SQL OPEN C_GETDATAFORKEY;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSalesmanGetNext                                     */
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
int pxSalesManGetNext
(
	struct tSALESMAN * record,
    int browseid
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	    struct tSALESMAN * recordp;
	EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_GetNext;
    recordp = record;

    switch (browseid)
    {
    // into SALESMAN_ZEIGER(recordp);
       case cCRSSALESMAN_GETDATAFORKEY:
           EXEC SQL FETCH C_GETDATAFORKEY
           into :recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS;
          break;
       case cCRSSALESMAN_GETDATAFORPARTNER:
           EXEC SQL FETCH C_GETDATAFORPARTNER
           into :recordp->EMAILADRESS;
    	   break;
       default:
          EXEC SQL FETCH C_GETDATAFORKEY
		  into :recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS;
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSalesmanEndBrowse                                   */
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
int pxSalesManEndBrowse
(
    int browseid
)
{
    functionnr = F_SALESMAN*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRSSALESMAN_GETDATAFORKEY:
          EXEC SQL CLOSE C_GETDATAFORKEY;
          break;
       case cCRSSALESMAN_GETDATAFORPARTNER:
           EXEC SQL CLOSE C_GETDATAFORPARTNER;
    	   break;
       default:
          EXEC SQL CLOSE C_GETDATAFORKEY;
          break;
    }
    return 0;
}

int pxSALESMANRead
(
	struct tSALESMAN * record
#ifdef SKtSALESMAN
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	    struct tSALESMAN * recordp;
	EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_Read;
    recordp = record;

#ifdef SKtSALESMAN
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
	 	 	 	SALESMAN.BRANCHNO,
	 			SALESMAN.SALESMANNO,
	 			SALESMAN.SALESMANNAME,
	 			SALESMAN.SALESMANSTREET,
	 			SALESMAN.SALESMANCITY,
	 			SALESMAN.POSTCODE,
	 			SALESMAN.ACTIVE_FLAG,
	 			SALESMAN.SPREWHOLE,
	 			SALESMAN.EMAILADRESS
     into :recordp->BRANCHNO,
		:recordp->SALESMANNO,
		:recordp->SALESMANNAME,
		:recordp->SALESMANSTREET,
		:recordp->SALESMANCITY,
		:recordp->POSTCODE,
		:recordp->ACTIVE_FLAG,
		:recordp->SPREWHOLE,
		:recordp->EMAILADRESS
     from SALESMAN
     where SKtSALESMAN;
     break;
    default:
#endif

    EXEC SQL SELECT
			SALESMAN.BRANCHNO,
			SALESMAN.SALESMANNO,
			SALESMAN.SALESMANNAME,
			SALESMAN.SALESMANSTREET,
			SALESMAN.SALESMANCITY,
			SALESMAN.POSTCODE,
			SALESMAN.ACTIVE_FLAG,
			SALESMAN.SPREWHOLE,
			SALESMAN.EMAILADRESS
	  into :recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS
     from SALESMAN
     where BRANCHNO   = :recordp->BRANCHNO and SALESMANNO = :recordp->SALESMANNO;

#ifdef SKtSALESMAN
    }
#endif
    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSALESMANReadLock                                      */
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
int pxSALESMANReadLock
(
	struct tSALESMAN * record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	    struct tSALESMAN * recordp;
	EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_ReadLock;
    recordp = record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tSALESMAN_U1 CURSOR WITH HOLD FOR
        SELECT
			SALESMAN.BRANCHNO,
			SALESMAN.SALESMANNO,
			SALESMAN.SALESMANNAME,
			SALESMAN.SALESMANSTREET,
			SALESMAN.SALESMANCITY,
			SALESMAN.POSTCODE,
			SALESMAN.ACTIVE_FLAG,
			SALESMAN.SPREWHOLE,
			SALESMAN.EMAILADRESS
		from SALESMAN
		where BRANCHNO   = :recordp->BRANCHNO and SALESMANNO = :recordp->SALESMANNO
    FOR UPDATE;
    EXEC SQL OPEN tSALESMAN_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tSALESMAN_U1
	  into :recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS
      ;
    }
#else
    EXEC SQL SELECT
		SALESMAN.BRANCHNO,
		SALESMAN.SALESMANNO,
		SALESMAN.SALESMANNAME,
		SALESMAN.SALESMANSTREET,
		SALESMAN.SALESMANCITY,
		SALESMAN.POSTCODE,
		SALESMAN.ACTIVE_FLAG,
		SALESMAN.SPREWHOLE,
		SALESMAN.EMAILADRESS
    into :recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS
    from SALESMAN    HOLDLOCK
    where BRANCHNO   = :recordp->BRANCHNO and SALESMANNO = :recordp->SALESMANNO;
#endif


    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}

int pxSalesManUpdate
(
	struct tSALESMAN * record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	    struct tSALESMAN * recordp;
	EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_Update;
    recordp = record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    	SALESMAN
    SET
		SALESMAN.BRANCHNO=:recordp->BRANCHNO,
		SALESMAN.SALESMANNO=:recordp->SALESMANNO,
		SALESMAN.SALESMANNAME=:recordp->SALESMANNAME,
		SALESMAN.SALESMANSTREET=:recordp->SALESMANSTREET,
		SALESMAN.SALESMANCITY=:recordp->SALESMANCITY,
		SALESMAN.POSTCODE=:recordp->POSTCODE,
		SALESMAN.ACTIVE_FLAG=:recordp->ACTIVE_FLAG,
		SALESMAN.SPREWHOLE=:recordp->SPREWHOLE,
		SALESMAN.EMAILADRESS=:recordp->EMAILADRESS
    where current of tSALESMAN_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tSALESMAN_U1;
    }
#else

    EXEC SQL UPDATE
    	SALESMAN
    SET
		SALESMAN.BRANCHNO=:recordp->BRANCHNO,
		SALESMAN.SALESMANNO=:recordp->SALESMANNO,
		SALESMAN.SALESMANNAME=:recordp->SALESMANNAME,
		SALESMAN.SALESMANSTREET=:recordp->SALESMANSTREET,
		SALESMAN.SALESMANCITY=:recordp->SALESMANCITY,
		SALESMAN.POSTCODE=:recordp->POSTCODE,
		SALESMAN.ACTIVE_FLAG=:recordp->ACTIVE_FLAG,
		SALESMAN.SPREWHOLE=:recordp->SPREWHOLE,
		SALESMAN.EMAILADRESS=:recordp->EMAILADRESS
    where BRANCHNO   = :recordp->BRANCHNO and SALESMANNO = :recordp->SALESMANNO;
#endif

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSALESMANInsert                                       */
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
int pxSalesManInsert
(
	struct tSALESMAN * record
)
{
	EXEC SQL BEGIN DECLARE SECTION;
	    struct tSALESMAN * recordp;
	EXEC SQL END   DECLARE SECTION;

    functionnr = F_SALESMAN*10+F_Insert;
    recordp = record;

    EXEC SQL INSERT INTO
    SALESMAN
    (SALESMAN.BRANCHNO,
		SALESMAN.SALESMANNO,
		SALESMAN.SALESMANNAME,
		SALESMAN.SALESMANSTREET,
		SALESMAN.SALESMANCITY,
		SALESMAN.POSTCODE,
		SALESMAN.ACTIVE_FLAG,
		SALESMAN.SPREWHOLE,
		SALESMAN.EMAILADRESS)
    VALUES (:recordp->BRANCHNO,
			:recordp->SALESMANNO,
			:recordp->SALESMANNAME,
			:recordp->SALESMANSTREET,
			:recordp->SALESMANCITY,
			:recordp->POSTCODE,
			:recordp->ACTIVE_FLAG,
			:recordp->SPREWHOLE,
			:recordp->EMAILADRESS );

    if (SQLCODE == 0)
    {
       return 0;
    }
    if (SQLCODE == -2601)
    {
       return cDBXR_ISDUPLICATE;
    }
    return cDBXR_IOERROR;
}

