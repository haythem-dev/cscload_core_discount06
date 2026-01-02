/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustphg.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustPharmGroupStartBrowse  declare and open Cursor
        pxCustPharmGroupGetNext      get next record
        pxCustPharmGroupEndBrowse    close cursor
        pxCustPharmGroupRead         get one record
        pxCustPharmGroupReadLock     get one record with lock
        pxCustPharmGroupInsert       Insert record
        pxCustPharmGroupUpdate       Update record
        pxCustPharmGroupDelete       Delete record


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
#include <tcustphg.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustPharmGroupStartBrowse                                   */
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
int pxCustPharmGroupStartBrowse
(
     struct tCUSTOMERPHARMACYGR* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
#ifdef MCtcustphg
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;

    if (!(sizeof(struct C_CUSTOMERPHARMACYGR) == sizeof(struct tCUSTOMERPHARMACYGR)))
       return cDBXR_DEFINITION;


#ifdef MCtcustphg
    strcpy(matchcode,recordp->MCtcustphg);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERPHARMACYGR_LISTE
    from CUSTOMERPHARMACYGR
    DWtcustphg
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERPHARMACYGR_LISTE
    from CUSTOMERPHARMACYGR
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
/*  FUNCTION: pxCustPharmGroupGetNext                                       */
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
int pxCustPharmGroupGetNext
(
    struct tCUSTOMERPHARMACYGR* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_GetNext;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERPHARMACYGR_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERPHARMACYGR_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustPharmGroupEndBrowse                                     */
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
int pxCustPharmGroupEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERPHARMACYGR*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustPharmGroupRead                                          */
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

int pxCustPharmGroupRead
(
    struct tCUSTOMERPHARMACYGR* record
#ifdef SKtcustphg
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_Read;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;

#ifdef SKtcustphg
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERPHARMACYGR_LISTE
     into CUSTOMERPHARMACYGR_ZEIGER(recordp)
     from CUSTOMERPHARMACYGR
     where SKtcustphg;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERPHARMACYGR_LISTE
     into CUSTOMERPHARMACYGR_ZEIGER(recordp)
     from CUSTOMERPHARMACYGR
     where PKtcustphg;

#ifdef SKtcustphg
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
/*  FUNCTION: pxCustPharmGroupReadLock                                      */
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
int pxCustPharmGroupReadLock
(
    struct tCUSTOMERPHARMACYGR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_ReadLock;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TCUSTPHG_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERPHARMACYGR_LISTE
    from CUSTOMERPHARMACYGR
    where PKtcustphg
    FOR UPDATE;
    EXEC SQL OPEN TCUSTPHG_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TCUSTPHG_U1
      into CUSTOMERPHARMACYGR_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERPHARMACYGR_LISTE
    into CUSTOMERPHARMACYGR_ZEIGER(recordp)
    from CUSTOMERPHARMACYGR    HOLDLOCK
    where PKtcustphg;
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
/*  FUNCTION: pxCustPharmGroupUpdate                                        */
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

int pxCustPharmGroupUpdate
(
    struct tCUSTOMERPHARMACYGR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_Update;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERPHARMACYGR
    SET
    CUSTOMERPHARMACYGR_UPDATE(recordp)
    where current of TCUSTPHG_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TCUSTPHG_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERPHARMACYGR
    SET
    CUSTOMERPHARMACYGR_UPDATE(recordp)
    where PKtcustphg;
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
/*  FUNCTION: pxCustPharmGroupInsert                                       */
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
int pxCustPharmGroupInsert
(
    struct tCUSTOMERPHARMACYGR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_Insert;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;

    EXEC SQL INSERT INTO
    CUSTOMERPHARMACYGR
    (CUSTOMERPHARMACYGR_LISTE)
    VALUES ( CUSTOMERPHARMACYGR_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERPHARMACYGR
    VALUES ( CUSTOMERPHARMACYGR_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustPharmGroupDelete                                        */
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

int pxCustPharmGroupDelete
(
    struct tCUSTOMERPHARMACYGR* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERPHARMACYGR * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERPHARMACYGR*10+F_Delete;
    recordp = (struct C_CUSTOMERPHARMACYGR *) record;

    EXEC SQL DELETE FROM
    CUSTOMERPHARMACYGR
    where PKtcustphg;

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
