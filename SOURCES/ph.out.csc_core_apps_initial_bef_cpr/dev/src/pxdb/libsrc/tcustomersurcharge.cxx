/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustomersurcharge.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustomerSurchargeStartBrowse  declare and open Cursor
        pxCustomerSurchargeGetNext      get next record
        pxCustomerSurchargeEndBrowse    close cursor
        pxCustomerSurchargeRead         get one record
        pxCustomerSurchargeReadLock     get one record with lock
        pxCustomerSurchargeInsert       Insert record
        pxCustomerSurchargeUpdate       Update record
        pxCustomerSurchargeDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <tcustomersurcharge.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSurchargeStartBrowse                                   */
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
int pxCustomerSurchargeStartBrowse
(
     struct tCUSTOMERSURCHARGE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
#ifdef MCtcustomersurcharge
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;

    if (!(sizeof(struct C_CUSTOMERSURCHARGE) == sizeof(struct tCUSTOMERSURCHARGE)))
       return cDBXR_DEFINITION;


#ifdef MCtcustomersurcharge
    strcpy(matchcode,recordp->MCtcustomersurcharge);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERSURCHARGE_LISTE
    from CUSTOMERSURCHARGE
    DWtcustomersurcharge
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERSURCHARGE_LISTE
    from CUSTOMERSURCHARGE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        CUSTOMERSURCHARGE_LISTE
    from CUSTOMERSURCHARGE
    where CUSTOMERSURCHARGE.BRANCHNO        = :recordp->BRANCHNO
    and   CUSTOMERSURCHARGE.CUSTOMERNO    = :recordp->CUSTOMERNO
    and  (CUSTOMERSURCHARGE.MANUFACTURERNO  = :recordp->MANUFACTURERNO)
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
       case cCRSCUSTOMERSURCHARGE_BR_CST_MAN:
          EXEC SQL OPEN C2;
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
/*  FUNCTION: pxCustomerSurchargeGetNext                                       */
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
int pxCustomerSurchargeGetNext
(
    struct tCUSTOMERSURCHARGE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_GetNext;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERSURCHARGE_ZEIGER(recordp);
          break;
       case cCRSCUSTOMERSURCHARGE_BR_CST_MAN:
          EXEC SQL FETCH C2
          into CUSTOMERSURCHARGE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERSURCHARGE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSurchargeEndBrowse                                     */
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
int pxCustomerSurchargeEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERSURCHARGE*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSCUSTOMERSURCHARGE_BR_CST_MAN:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSurchargeRead                                          */
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

int pxCustomerSurchargeRead
(
    struct tCUSTOMERSURCHARGE* record
#ifdef SKtcustomersurcharge
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_Read;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;

#ifdef SKtcustomersurcharge
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERSURCHARGE_LISTE
     into CUSTOMERSURCHARGE_ZEIGER(recordp)
     from CUSTOMERSURCHARGE
     where SKtcustomersurcharge;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERSURCHARGE_LISTE
     into CUSTOMERSURCHARGE_ZEIGER(recordp)
     from CUSTOMERSURCHARGE
     where PKtcustomersurcharge;

#ifdef SKtcustomersurcharge
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
/*  FUNCTION: pxCustomerSurchargeReadLock                                      */
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
int pxCustomerSurchargeReadLock
(
    struct tCUSTOMERSURCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_ReadLock;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcustomersurcharge_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERSURCHARGE_LISTE
    from CUSTOMERSURCHARGE
    where PKtcustomersurcharge
    FOR UPDATE;
    EXEC SQL OPEN tcustomersurcharge_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcustomersurcharge_U1
      into CUSTOMERSURCHARGE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERSURCHARGE_LISTE
    into CUSTOMERSURCHARGE_ZEIGER(recordp)
    from CUSTOMERSURCHARGE    HOLDLOCK
    where PKtcustomersurcharge;
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
/*  FUNCTION: pxCustomerSurchargeUpdate                                        */
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

int pxCustomerSurchargeUpdate
(
    struct tCUSTOMERSURCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_Update;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERSURCHARGE
    SET
    CUSTOMERSURCHARGE_UPDATE(recordp)
    where current of tcustomersurcharge_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcustomersurcharge_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERSURCHARGE
    SET
    CUSTOMERSURCHARGE_UPDATE(recordp)
    where PKtcustomersurcharge;
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
/*  FUNCTION: pxCustomerSurchargeInsert                                       */
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
int pxCustomerSurchargeInsert
(
    struct tCUSTOMERSURCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_Insert;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;

    EXEC SQL INSERT INTO
    CUSTOMERSURCHARGE
    (CUSTOMERSURCHARGE_LISTE)
    VALUES ( CUSTOMERSURCHARGE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERSURCHARGE
    VALUES ( CUSTOMERSURCHARGE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustomerSurchargeDelete                                        */
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

int pxCustomerSurchargeDelete
(
    struct tCUSTOMERSURCHARGE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSURCHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSURCHARGE*10+F_Delete;
    recordp = (struct C_CUSTOMERSURCHARGE *) record;

    EXEC SQL DELETE FROM
    CUSTOMERSURCHARGE
    where PKtcustomersurcharge;

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
