/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstpaymentterms.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCstPaymentTermsStartBrowse  declare and open Cursor
        pxCstPaymentTermsGetNext      get next record
        pxCstPaymentTermsEndBrowse    close cursor
        pxCstPaymentTermsRead         get one record
        pxCstPaymentTermsReadLock     get one record with lock
        pxCstPaymentTermsInsert       Insert record
        pxCstPaymentTermsUpdate       Update record
        pxCstPaymentTermsDelete       Delete record


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
#include <tcstpaymentterms.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstPaymentTermsStartBrowse                                   */
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
int pxCstPaymentTermsStartBrowse
(
     struct tCSTPAYMENTTERMS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
#ifdef MCtcstpaymentterms
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_StartBrowse;
    recordp = (struct C_CSTPAYMENTTERMS *) record;

    if (!(sizeof(struct C_CSTPAYMENTTERMS) == sizeof(struct tCSTPAYMENTTERMS)))
       return cDBXR_DEFINITION;


#ifdef MCtcstpaymentterms
    strcpy(matchcode,recordp->MCtcstpaymentterms);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTPAYMENTTERMS_LISTE
    from CSTPAYMENTTERMS
    DWtcstpaymentterms
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTPAYMENTTERMS_LISTE
    from CSTPAYMENTTERMS
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
/*  FUNCTION: pxCstPaymentTermsGetNext                                       */
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
int pxCstPaymentTermsGetNext
(
    struct tCSTPAYMENTTERMS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_GetNext;
    recordp = (struct C_CSTPAYMENTTERMS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTPAYMENTTERMS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTPAYMENTTERMS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstPaymentTermsEndBrowse                                     */
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
int pxCstPaymentTermsEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTPAYMENTTERMS*10+F_EndBrowse;

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
/*  FUNCTION: pxCstPaymentTermsRead                                          */
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

int pxCstPaymentTermsRead
(
    struct tCSTPAYMENTTERMS* record
#ifdef SKtcstpaymentterms
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_Read;
    recordp = (struct C_CSTPAYMENTTERMS *) record;

#ifdef SKtcstpaymentterms
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTPAYMENTTERMS_LISTE
     into CSTPAYMENTTERMS_ZEIGER(recordp)
     from CSTPAYMENTTERMS
     where SKtcstpaymentterms;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTPAYMENTTERMS_LISTE
     into CSTPAYMENTTERMS_ZEIGER(recordp)
     from CSTPAYMENTTERMS
     where PKtcstpaymentterms;

#ifdef SKtcstpaymentterms
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
/*  FUNCTION: pxCstPaymentTermsReadLock                                      */
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
int pxCstPaymentTermsReadLock
(
    struct tCSTPAYMENTTERMS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_ReadLock;
    recordp = (struct C_CSTPAYMENTTERMS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstpaymentterms_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTPAYMENTTERMS_LISTE
    from CSTPAYMENTTERMS
    where PKtcstpaymentterms
    FOR UPDATE;
    EXEC SQL OPEN tcstpaymentterms_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstpaymentterms_U1
      into CSTPAYMENTTERMS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTPAYMENTTERMS_LISTE
    into CSTPAYMENTTERMS_ZEIGER(recordp)
    from CSTPAYMENTTERMS    HOLDLOCK
    where PKtcstpaymentterms;
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
/*  FUNCTION: pxCstPaymentTermsUpdate                                        */
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

int pxCstPaymentTermsUpdate
(
    struct tCSTPAYMENTTERMS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_Update;
    recordp = (struct C_CSTPAYMENTTERMS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTPAYMENTTERMS
    SET
    CSTPAYMENTTERMS_UPDATE(recordp)
    where current of tcstpaymentterms_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstpaymentterms_U1;
    }
#else

    EXEC SQL UPDATE
    CSTPAYMENTTERMS
    SET
    CSTPAYMENTTERMS_UPDATE(recordp)
    where PKtcstpaymentterms;
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
/*  FUNCTION: pxCstPaymentTermsInsert                                       */
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
int pxCstPaymentTermsInsert
(
    struct tCSTPAYMENTTERMS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_Insert;
    recordp = (struct C_CSTPAYMENTTERMS *) record;

    EXEC SQL INSERT INTO
    CSTPAYMENTTERMS
    (CSTPAYMENTTERMS_LISTE)
    VALUES ( CSTPAYMENTTERMS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTPAYMENTTERMS
    VALUES ( CSTPAYMENTTERMS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCstPaymentTermsDelete                                        */
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

int pxCstPaymentTermsDelete
(
    struct tCSTPAYMENTTERMS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTPAYMENTTERMS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTPAYMENTTERMS*10+F_Delete;
    recordp = (struct C_CSTPAYMENTTERMS *) record;

    EXEC SQL DELETE FROM
    CSTPAYMENTTERMS
    where PKtcstpaymentterms;

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
