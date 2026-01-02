/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tddelcst.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustDelDeliveryStartBrowse  declare and open Cursor
        pxCustDelDeliveryGetNext      get next record
        pxCustDelDeliveryEndBrowse    close cursor
        pxCustDelDeliveryRead         get one record
        pxCustDelDeliveryReadLock     get one record with lock
        pxCustDelDeliveryInsert       Insert record
        pxCustDelDeliveryUpdate       Update record
        pxCustDelDeliveryDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include <tdelayeddeliverycst.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDelDeliveryStartBrowse                                   */
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
int pxCustDelDeliveryStartBrowse
(
     struct tDELAYEDDELIVERYCST* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
#ifdef MCtddelcst
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_StartBrowse;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;

    if (!(sizeof(struct C_DELAYEDDELIVERYCST) == sizeof(struct tDELAYEDDELIVERYCST)))
       return cDBXR_DEFINITION;


#ifdef MCtddelcst
    strcpy(matchcode,recordp->MCtddelcst);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DELAYEDDELIVERYCST_LISTE
    from DELAYEDDELIVERYCST
    DWtddelcst
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        DELAYEDDELIVERYCST_LISTE
    from DELAYEDDELIVERYCST
	where DELAYEDDELIVERYCST.BRANCHNO  = :recordp->BRANCHNO
	and DELAYEDDELIVERYCST.CUSTOMERNO = :recordp->CUSTOMERNO
	and DELAYEDDELIVERYCST.DATEFROM = 0
	and DELAYEDDELIVERYCST.ACTIV = 1
	and DELAYEDDELIVERYCST.WEEKDAY = :recordp->WEEKDAY
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        DELAYEDDELIVERYCST_LISTE
    from DELAYEDDELIVERYCST
	where DELAYEDDELIVERYCST.BRANCHNO  = :recordp->BRANCHNO
	//and (DELAYEDDELIVERYCST.CUSTOMERNO in (0, :recordp->CUSTOMERNO)
	and (DELAYEDDELIVERYCST.CUSTOMERNO = 0
	and (DELAYEDDELIVERYCST.DATEFROM = 0 )
	     or  (DELAYEDDELIVERYCST.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DELAYEDDELIVERYCST.DATETO >= TO_CHAR(today, '%Y%m%d')) )
	and DELAYEDDELIVERYCST.ACTIV = 1
	and DELAYEDDELIVERYCST.WEEKDAY = :recordp->WEEKDAY
	//ORDER BY DELAYEDDELIVERYCST.CUSTOMERNO asc
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

	EXEC SQL DECLARE C4 CURSOR FOR
		SELECT
		DELAYEDDELIVERYCST_LISTE
		from DELAYEDDELIVERYCST
	where DELAYEDDELIVERYCST.BRANCHNO = :recordp->BRANCHNO
	and (DELAYEDDELIVERYCST.CUSTOMERNO = 0
		and (DELAYEDDELIVERYCST.DATEFROM = 0)
		or (DELAYEDDELIVERYCST.DATEFROM <= :recordp->DATEFROM AND DELAYEDDELIVERYCST.DATETO >= :recordp->DATETO))
		and DELAYEDDELIVERYCST.ACTIV = 1
#ifndef pxDATABASE_INFORMIX
		FOR BROWSE;
#else
		;
#endif


    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DELAYEDDELIVERYCST_LISTE
    from DELAYEDDELIVERYCST
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       case cCRDELDELIVERYCST_NOTUSETOURMANAGER_2:
          EXEC SQL OPEN C2;
          break;
       case cCRDELDELIVERYCST_USETOURMANAGER_2:
          EXEC SQL OPEN C3;
          break;
	   case cCRDELDELIVERYCST_USETOURMANAGER_DATE_2:
		   EXEC SQL OPEN C4;
		   break;
       default:
          EXEC SQL OPEN C1;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDelDeliveryGetNext                                       */
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
int pxCustDelDeliveryGetNext
(
    struct tDELAYEDDELIVERYCST* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_GetNext;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0 into DELAYEDDELIVERYCST_ZEIGER(recordp);
          break;
       case cCRDELDELIVERYCST_NOTUSETOURMANAGER_2:
          EXEC SQL FETCH C2 into DELAYEDDELIVERYCST_ZEIGER(recordp);
          break;
       case cCRDELDELIVERYCST_USETOURMANAGER_2:
          EXEC SQL FETCH C3 into DELAYEDDELIVERYCST_ZEIGER(recordp);
          break;
	   case cCRDELDELIVERYCST_USETOURMANAGER_DATE_2:
		   EXEC SQL FETCH C4 into DELAYEDDELIVERYCST_ZEIGER(recordp);
		   break;
       default:
          EXEC SQL FETCH C1 into DELAYEDDELIVERYCST_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDelDeliveryEndBrowse                                     */
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
int pxCustDelDeliveryEndBrowse
(
    int browseid
)
{
    functionnr = F_DELAYEDDELIVERYCST*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRDELDELIVERYCST_NOTUSETOURMANAGER_2:
          EXEC SQL CLOSE C2;
          break;
       case cCRDELDELIVERYCST_USETOURMANAGER_2:
          EXEC SQL CLOSE C3;
          break;
	   case cCRDELDELIVERYCST_USETOURMANAGER_DATE_2:
		   EXEC SQL CLOSE C4;
		   break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDelDeliveryRead                                          */
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

int pxCustDelDeliveryRead
(
    struct tDELAYEDDELIVERYCST* record
#ifdef SKtddelcst
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_Read;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;

#ifdef SKtddelcst
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DELAYEDDELIVERYCST_LISTE
     into DELAYEDDELIVERYCST_ZEIGER(recordp)
     from DELAYEDDELIVERYCST
     where SKtddelcst;
     break;
    default:
#endif

    EXEC SQL SELECT
        DELAYEDDELIVERYCST_LISTE
     into DELAYEDDELIVERYCST_ZEIGER(recordp)
     from DELAYEDDELIVERYCST
     where PKtddelcst;

#ifdef SKtddelcst
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
/*  FUNCTION: pxCustDelDeliveryReadLock                                      */
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
int pxCustDelDeliveryReadLock
(
    struct tDELAYEDDELIVERYCST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_ReadLock;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TDDELCST_U1 CURSOR WITH HOLD FOR
        SELECT
        DELAYEDDELIVERYCST_LISTE
    from DELAYEDDELIVERYCST
    where PKtddelcst
    FOR UPDATE;
    EXEC SQL OPEN TDDELCST_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TDDELCST_U1
      into DELAYEDDELIVERYCST_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DELAYEDDELIVERYCST_LISTE
    into DELAYEDDELIVERYCST_ZEIGER(recordp)
    from DELAYEDDELIVERYCST    HOLDLOCK
    where PKtddelcst;
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
/*  FUNCTION: pxCustDelDeliveryUpdate                                        */
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

int pxCustDelDeliveryUpdate
(
    struct tDELAYEDDELIVERYCST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_Update;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DELAYEDDELIVERYCST
    SET
    DELAYEDDELIVERYCST_UPDATE(recordp)
    where current of TDDELCST_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TDDELCST_U1;
    }
#else

    EXEC SQL UPDATE
    DELAYEDDELIVERYCST
    SET
    DELAYEDDELIVERYCST_UPDATE(recordp)
    where PKtddelcst;
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
/*  FUNCTION: pxCustDelDeliveryInsert                                       */
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
int pxCustDelDeliveryInsert
(
    struct tDELAYEDDELIVERYCST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_Insert;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;

    EXEC SQL INSERT INTO
    DELAYEDDELIVERYCST
    (DELAYEDDELIVERYCST_LISTE)
    VALUES ( DELAYEDDELIVERYCST_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DELAYEDDELIVERYCST
    VALUES ( DELAYEDDELIVERYCST_ZEIGER(recordp) );   */


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

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDelDeliveryDelete                                        */
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

int pxCustDelDeliveryDelete
(
    struct tDELAYEDDELIVERYCST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DELAYEDDELIVERYCST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DELAYEDDELIVERYCST*10+F_Delete;
    recordp = (struct C_DELAYEDDELIVERYCST *) record;

    EXEC SQL DELETE FROM
    DELAYEDDELIVERYCST
    where PKtddelcst;

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }
}
