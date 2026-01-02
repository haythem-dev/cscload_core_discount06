/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttendercustomer.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTenderCustomerStartBrowse  declare and open Cursor
        pxTenderCustomerGetNext      get next record
        pxTenderCustomerEndBrowse    close cursor
        pxTenderCustomerRead         get one record
        pxTenderCustomerReadLock     get one record with lock
        pxTenderCustomerInsert       Insert record
        pxTenderCustomerUpdate       Update record
        pxTenderCustomerDelete       Delete record


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
#include <ttendercustomer.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderCustomerStartBrowse                                   */
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
int pxTenderCustomerStartBrowse
(
     struct tTENDERCUSTOMER* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
#ifdef MCttendercustomer
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_StartBrowse;
    recordp = (struct C_TENDERCUSTOMER *) record;

    if (!(sizeof(struct C_TENDERCUSTOMER) == sizeof(struct tTENDERCUSTOMER)))
       return cDBXR_DEFINITION;


#ifdef MCttendercustomer
    strcpy(matchcode,recordp->MCttendercustomer);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TENDERCUSTOMER_LISTE
    from TENDERCUSTOMER
    DWttendercustomer
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TENDERCUSTOMER_LISTE
    from TENDERCUSTOMER
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
/*  FUNCTION: pxTenderCustomerGetNext                                       */
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
int pxTenderCustomerGetNext
(
    struct tTENDERCUSTOMER* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_GetNext;
    recordp = (struct C_TENDERCUSTOMER *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TENDERCUSTOMER_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TENDERCUSTOMER_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderCustomerEndBrowse                                     */
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
int pxTenderCustomerEndBrowse
(
    int browseid
)
{
    functionnr = F_TENDERCUSTOMER*10+F_EndBrowse;

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
/*  FUNCTION: pxTenderCustomerRead                                          */
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

int pxTenderCustomerRead
(
    struct tTENDERCUSTOMER* record
#ifdef SKttendercustomer
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_Read;
    recordp = (struct C_TENDERCUSTOMER *) record;

#ifdef SKttendercustomer
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TENDERCUSTOMER_LISTE
     into TENDERCUSTOMER_ZEIGER(recordp)
     from TENDERCUSTOMER
     where SKttendercustomer;
     break;
    default:
#endif

    EXEC SQL SELECT
        TENDERCUSTOMER_LISTE
     into TENDERCUSTOMER_ZEIGER(recordp)
     from TENDERCUSTOMER
     where PKttendercustomer;

#ifdef SKttendercustomer
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
/*  FUNCTION: pxTenderCustomerReadLock                                      */
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
int pxTenderCustomerReadLock
(
    struct tTENDERCUSTOMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_ReadLock;
    recordp = (struct C_TENDERCUSTOMER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttendercustomer_U1 CURSOR WITH HOLD FOR
        SELECT
        TENDERCUSTOMER_LISTE
    from TENDERCUSTOMER
    where PKttendercustomer
    FOR UPDATE;
    EXEC SQL OPEN ttendercustomer_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttendercustomer_U1
      into TENDERCUSTOMER_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TENDERCUSTOMER_LISTE
    into TENDERCUSTOMER_ZEIGER(recordp)
    from TENDERCUSTOMER    HOLDLOCK
    where PKttendercustomer;
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
/*  FUNCTION: pxTenderCustomerUpdate                                        */
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

int pxTenderCustomerUpdate
(
    struct tTENDERCUSTOMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_Update;
    recordp = (struct C_TENDERCUSTOMER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TENDERCUSTOMER
    SET
    TENDERCUSTOMER_UPDATE(recordp)
    where current of ttendercustomer_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttendercustomer_U1;
    }
#else

    EXEC SQL UPDATE
    TENDERCUSTOMER
    SET
    TENDERCUSTOMER_UPDATE(recordp)
    where PKttendercustomer;
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
/*  FUNCTION: pxTenderCustomerInsert                                       */
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
int pxTenderCustomerInsert
(
    struct tTENDERCUSTOMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_Insert;
    recordp = (struct C_TENDERCUSTOMER *) record;

    EXEC SQL INSERT INTO
    TENDERCUSTOMER
    (TENDERCUSTOMER_LISTE)
    VALUES ( TENDERCUSTOMER_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TENDERCUSTOMER
    VALUES ( TENDERCUSTOMER_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTenderCustomerDelete                                        */
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

int pxTenderCustomerDelete
(
    struct tTENDERCUSTOMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERCUSTOMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERCUSTOMER*10+F_Delete;
    recordp = (struct C_TENDERCUSTOMER *) record;

    EXEC SQL DELETE FROM
    TENDERCUSTOMER
    where PKttendercustomer;

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
