/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdiscountordertyp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxDiscountOrdTypStartBrowse  declare and open Cursor
        pxDiscountOrdTypGetNext      get next record
        pxDiscountOrdTypEndBrowse    close cursor
        pxDiscountOrdTypRead         get one record
        pxDiscountOrdTypReadLock     get one record with lock
        pxDiscountOrdTypInsert       Insert record
        pxDiscountOrdTypUpdate       Update record
        pxDiscountOrdTypDelete       Delete record


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
#include <tdiscountordertyp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountOrdTypStartBrowse                                   */
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
int pxDiscountOrdTypStartBrowse
(
     struct tDISCOUNTORDERTYP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
#ifdef MCtdiscountordertyp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_StartBrowse;
    recordp = (struct C_DISCOUNTORDERTYP *) record;

    if (!(sizeof(struct C_DISCOUNTORDERTYP) == sizeof(struct tDISCOUNTORDERTYP)))
       return cDBXR_DEFINITION;


#ifdef MCtdiscountordertyp
    strcpy(matchcode,recordp->MCtdiscountordertyp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISCOUNTORDERTYP_LISTE
    from DISCOUNTORDERTYP
    DWtdiscountordertyp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISCOUNTORDERTYP_LISTE
    from DISCOUNTORDERTYP
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
/*  FUNCTION: pxDiscountOrdTypGetNext                                       */
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
int pxDiscountOrdTypGetNext
(
    struct tDISCOUNTORDERTYP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_GetNext;
    recordp = (struct C_DISCOUNTORDERTYP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISCOUNTORDERTYP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DISCOUNTORDERTYP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountOrdTypEndBrowse                                     */
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
int pxDiscountOrdTypEndBrowse
(
    int browseid
)
{
    functionnr = F_DISCOUNTORDERTYP*10+F_EndBrowse;

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
/*  FUNCTION: pxDiscountOrdTypRead                                          */
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

int pxDiscountOrdTypRead
(
    struct tDISCOUNTORDERTYP* record
#ifdef SKtdiscountordertyp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_Read;
    recordp = (struct C_DISCOUNTORDERTYP *) record;

#ifdef SKtdiscountordertyp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISCOUNTORDERTYP_LISTE
     into DISCOUNTORDERTYP_ZEIGER(recordp)
     from DISCOUNTORDERTYP
     where SKtdiscountordertyp;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISCOUNTORDERTYP_LISTE
     into DISCOUNTORDERTYP_ZEIGER(recordp)
     from DISCOUNTORDERTYP
     where PKtdiscountordertyp;

#ifdef SKtdiscountordertyp
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
/*  FUNCTION: pxDiscountOrdTypReadLock                                      */
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
int pxDiscountOrdTypReadLock
(
    struct tDISCOUNTORDERTYP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_ReadLock;
    recordp = (struct C_DISCOUNTORDERTYP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdiscountordertyp_U1 CURSOR WITH HOLD FOR
        SELECT
        DISCOUNTORDERTYP_LISTE
    from DISCOUNTORDERTYP
    where PKtdiscountordertyp
    FOR UPDATE;
    EXEC SQL OPEN tdiscountordertyp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdiscountordertyp_U1
      into DISCOUNTORDERTYP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISCOUNTORDERTYP_LISTE
    into DISCOUNTORDERTYP_ZEIGER(recordp)
    from DISCOUNTORDERTYP    HOLDLOCK
    where PKtdiscountordertyp;
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
/*  FUNCTION: pxDiscountOrdTypUpdate                                        */
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

int pxDiscountOrdTypUpdate
(
    struct tDISCOUNTORDERTYP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_Update;
    recordp = (struct C_DISCOUNTORDERTYP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISCOUNTORDERTYP
    SET
    DISCOUNTORDERTYP_UPDATE(recordp)
    where current of tdiscountordertyp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdiscountordertyp_U1;
    }
#else

    EXEC SQL UPDATE
    DISCOUNTORDERTYP
    SET
    DISCOUNTORDERTYP_UPDATE(recordp)
    where PKtdiscountordertyp;
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
/*  FUNCTION: pxDiscountOrdTypInsert                                       */
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
int pxDiscountOrdTypInsert
(
    struct tDISCOUNTORDERTYP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_Insert;
    recordp = (struct C_DISCOUNTORDERTYP *) record;

    EXEC SQL INSERT INTO
    DISCOUNTORDERTYP
    (DISCOUNTORDERTYP_LISTE)
    VALUES ( DISCOUNTORDERTYP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISCOUNTORDERTYP
    VALUES ( DISCOUNTORDERTYP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxDiscountOrdTypDelete                                        */
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

int pxDiscountOrdTypDelete
(
    struct tDISCOUNTORDERTYP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTORDERTYP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTORDERTYP*10+F_Delete;
    recordp = (struct C_DISCOUNTORDERTYP *) record;

    EXEC SQL DELETE FROM
    DISCOUNTORDERTYP
    where PKtdiscountordertyp;

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
