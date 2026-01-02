/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdiscountlist.c (.sqc)

    Database functions




    FUNCTIONS:

        pxSubOrderTypeStartBrowse  declare and open Cursor
        pxSubOrderTypeGetNext      get next record
        pxSubOrderTypeEndBrowse    close cursor
        pxSubOrderTypeRead         get one record
        pxSubOrderTypeReadLock     get one record with lock
        pxSubOrderTypeInsert       Insert record
        pxSubOrderTypeUpdate       Update record
        pxSubOrderTypeDelete       Delete record


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
#include <tdiscountlist.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSubOrderTypeStartBrowse                                   */
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
int pxSubOrderTypeStartBrowse
(
     struct tDISCOUNTLIST* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
#ifdef MCtdiscountlist
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_StartBrowse;
    recordp = (struct C_DISCOUNTLIST *) record;

    if (!(sizeof(struct C_DISCOUNTLIST) == sizeof(struct tDISCOUNTLIST)))
       return cDBXR_DEFINITION;


#ifdef MCtdiscountlist
    strcpy(matchcode,recordp->MCtdiscountlist);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISCOUNTLIST_LISTE
    from DISCOUNTLIST
    DWtdiscountlist
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISCOUNTLIST_LISTE
    from DISCOUNTLIST
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
/*  FUNCTION: pxSubOrderTypeGetNext                                       */
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
int pxSubOrderTypeGetNext
(
    struct tDISCOUNTLIST* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_GetNext;
    recordp = (struct C_DISCOUNTLIST *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISCOUNTLIST_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DISCOUNTLIST_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSubOrderTypeEndBrowse                                     */
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
int pxSubOrderTypeEndBrowse
(
    int browseid
)
{
    functionnr = F_DISCOUNTLIST*10+F_EndBrowse;

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
/*  FUNCTION: pxSubOrderTypeRead                                          */
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

int pxSubOrderTypeRead
(
    struct tDISCOUNTLIST* record
#ifdef SKtdiscountlist
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_Read;
    recordp = (struct C_DISCOUNTLIST *) record;

#ifdef SKtdiscountlist
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISCOUNTLIST_LISTE
     into DISCOUNTLIST_ZEIGER(recordp)
     from DISCOUNTLIST
     where SKtdiscountlist;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISCOUNTLIST_LISTE
     into DISCOUNTLIST_ZEIGER(recordp)
     from DISCOUNTLIST
     where PKtdiscountlist;

#ifdef SKtdiscountlist
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
/*  FUNCTION: pxSubOrderTypeReadLock                                      */
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
int pxSubOrderTypeReadLock
(
    struct tDISCOUNTLIST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_ReadLock;
    recordp = (struct C_DISCOUNTLIST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdiscountlist_U1 CURSOR WITH HOLD FOR
        SELECT
        DISCOUNTLIST_LISTE
    from DISCOUNTLIST
    where PKtdiscountlist
    FOR UPDATE;
    EXEC SQL OPEN tdiscountlist_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdiscountlist_U1
      into DISCOUNTLIST_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISCOUNTLIST_LISTE
    into DISCOUNTLIST_ZEIGER(recordp)
    from DISCOUNTLIST    HOLDLOCK
    where PKtdiscountlist;
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
/*  FUNCTION: pxSubOrderTypeUpdate                                        */
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

int pxSubOrderTypeUpdate
(
    struct tDISCOUNTLIST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_Update;
    recordp = (struct C_DISCOUNTLIST *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISCOUNTLIST
    SET
    DISCOUNTLIST_UPDATE(recordp)
    where current of tdiscountlist_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdiscountlist_U1;
    }
#else

    EXEC SQL UPDATE
    DISCOUNTLIST
    SET
    DISCOUNTLIST_UPDATE(recordp)
    where PKtdiscountlist;
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
/*  FUNCTION: pxSubOrderTypeInsert                                       */
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
int pxSubOrderTypeInsert
(
    struct tDISCOUNTLIST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_Insert;
    recordp = (struct C_DISCOUNTLIST *) record;

    EXEC SQL INSERT INTO
    DISCOUNTLIST
    (DISCOUNTLIST_LISTE)
    VALUES ( DISCOUNTLIST_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISCOUNTLIST
    VALUES ( DISCOUNTLIST_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxSubOrderTypeDelete                                        */
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

int pxSubOrderTypeDelete
(
    struct tDISCOUNTLIST* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTLIST * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTLIST*10+F_Delete;
    recordp = (struct C_DISCOUNTLIST *) record;

    EXEC SQL DELETE FROM
    DISCOUNTLIST
    where PKtdiscountlist;

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
