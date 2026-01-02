/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustomerspecials.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustomerSpecialsStartBrowse  declare and open Cursor
        pxCustomerSpecialsGetNext      get next record
        pxCustomerSpecialsEndBrowse    close cursor
        pxCustomerSpecialsRead         get one record
        pxCustomerSpecialsReadLock     get one record with lock
        pxCustomerSpecialsInsert       Insert record
        pxCustomerSpecialsUpdate       Update record
        pxCustomerSpecialsDelete       Delete record


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
#include <tcustomerspecials.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSpecialsStartBrowse                               */
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
int pxCustomerSpecialsStartBrowse
(
     struct tCUSTOMERSPECIALS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
#ifdef MCteventreason
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERSPECIALS *) record;

    if (!(sizeof(struct C_CUSTOMERSPECIALS) == sizeof(struct tCUSTOMERSPECIALS)))
       return cDBXR_DEFINITION;


#ifdef MCtcustomerspecials
    strcpy(matchcode,recordp->MCtcustomerspecials);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERSPECIALS_LISTE
    from CUSTOMERSPECIALS
    DWtcustomerspecials
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT FIRST 1
        CUSTOMERSPECIALS_LISTE
    from CUSTOMERSPECIALS
    where CUSTOMERSPECIALS.BRANCHNO     = :recordp->BRANCHNO
    and   CUSTOMERSPECIALS.CUSTOMERNO   = :recordp->CUSTOMERNO
    and   CUSTOMERSPECIALS.UW_IDF > 0
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        CUSTOMERSPECIALS_LISTE
    from CUSTOMERSPECIALS
    where CUSTOMERSPECIALS.BRANCHNO     = :recordp->BRANCHNO
    and   CUSTOMERSPECIALS.UW_IDF       = :recordp->UW_IDF
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERSPECIALS_LISTE
    from CUSTOMERSPECIALS
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
       case cCRSCUSTOMERSPECIALS_FIRST_UW_IDF         :
          EXEC SQL OPEN C2;
          break;
       case cCRSCUSTOMERSPECIALS_UW_IDF         :
          EXEC SQL OPEN C3;
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
/*  FUNCTION: pxCustomerSpecialsGetNext                              */
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
int pxCustomerSpecialsGetNext
(
    struct tCUSTOMERSPECIALS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_GetNext;
    recordp = (struct C_CUSTOMERSPECIALS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERSPECIALS_ZEIGER(recordp);
          break;
       case  cCRSCUSTOMERSPECIALS_FIRST_UW_IDF :
          EXEC SQL FETCH C2
          into CUSTOMERSPECIALS_ZEIGER(recordp);
          break;
       case  cCRSCUSTOMERSPECIALS_UW_IDF :
          EXEC SQL FETCH C3
          into CUSTOMERSPECIALS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERSPECIALS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSpecialsEndBrowse                            */
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
int pxCustomerSpecialsEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERSPECIALS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case  cCRSCUSTOMERSPECIALS_FIRST_UW_IDF :
          EXEC SQL CLOSE C2;
          break;
       case  cCRSCUSTOMERSPECIALS_UW_IDF :
          EXEC SQL CLOSE C3;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerSpecialsRead                                 */
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

int pxCustomerSpecialsRead
(
    struct tCUSTOMERSPECIALS* record
#ifdef SKtcustomerspecials
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_Read;
    recordp = (struct C_CUSTOMERSPECIALS *) record;

#ifdef SKteventreason
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERSPECIALS_LISTE
     into CUSTOMERSPECIALS_ZEIGER(recordp)
     from CUSTOMERSPECIALS
     where SKtcustomerspecials;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERSPECIALS_LISTE
     into CUSTOMERSPECIALS_ZEIGER(recordp)
     from CUSTOMERSPECIALS
     where PKtcustomerspecials;

#ifdef SKteventreason
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
/*  FUNCTION: pxCustomerSpecialsReadLock                                      */
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
int pxCustomerSpecialsReadLock
(
    struct tCUSTOMERSPECIALS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_ReadLock;
    recordp = (struct C_CUSTOMERSPECIALS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tCUSTOMERSPECIALS_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERSPECIALS_LISTE
    from CUSTOMERSPECIALS
    where PKtcustomerspecials
    FOR UPDATE;
    EXEC SQL OPEN tCUSTOMERSPECIALS_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tCUSTOMERSPECIALS_U1
      into CUSTOMERSPECIALS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERSPECIALS_LISTE
    into CUSTOMERSPECIALS_ZEIGER(recordp)
    from CUSTOMERSPECIALS    HOLDLOCK
    where PKtcustomerspecials;
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
/*  FUNCTION: pxCustomerSpecialsUpdate                                        */
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

int pxCustomerSpecialsUpdate
(
    struct tCUSTOMERSPECIALS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_Update;
    recordp = (struct C_CUSTOMERSPECIALS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERSPECIALS
    SET
    CUSTOMERSPECIALS_UPDATE(recordp)
    where current of tCUSTOMERSPECIALS_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tCUSTOMERSPECIALS_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERSPECIALS
    SET
    CUSTOMERSPECIALS_UPDATE(recordp)
    where PKtcustomerspecials;
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
/*  FUNCTION: pxCustomerSpecialsInsert                                       */
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
int pxCustomerSpecialsInsert
(
    struct tCUSTOMERSPECIALS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_Insert;
    recordp = (struct C_CUSTOMERSPECIALS *) record;

    EXEC SQL INSERT INTO
    CUSTOMERSPECIALS
    (CUSTOMERSPECIALS_LISTE)
    VALUES ( CUSTOMERSPECIALS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERSPECIALS
    VALUES ( CUSTOMERSPECIALS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustomerSpecialsDelete                                        */
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

int pxCustomerSpecialsDelete
(
    struct tCUSTOMERSPECIALS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERSPECIALS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERSPECIALS*10+F_Delete;
    recordp = (struct C_CUSTOMERSPECIALS *) record;

    EXEC SQL DELETE FROM
    CUSTOMERSPECIALS
    where PKtcustomerspecials;

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
