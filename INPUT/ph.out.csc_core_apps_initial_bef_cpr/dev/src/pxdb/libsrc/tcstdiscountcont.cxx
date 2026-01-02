/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstdiscountcont.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustDiscConditionStartBrowse  declare and open Cursor
        pxCustDiscConditionGetNext      get next record
        pxCustDiscConditionEndBrowse    close cursor
        pxCustDiscConditionRead         get one record
        pxCustDiscConditionReadLock     get one record with lock
        pxCustDiscConditionInsert       Insert record
        pxCustDiscConditionUpdate       Update record
        pxCustDiscConditionDelete       Delete record


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
#include <tcstdiscountcont.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDiscConditionStartBrowse                                   */
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
int pxCustDiscConditionStartBrowse
(
     struct tCSTDISCOUNTCONT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
#ifdef MCtcstdiscountcont
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_StartBrowse;
    recordp = (struct C_CSTDISCOUNTCONT *) record;

    if (!(sizeof(struct C_CSTDISCOUNTCONT) == sizeof(struct tCSTDISCOUNTCONT)))
       return cDBXR_DEFINITION;


#ifdef MCtcstdiscountcont
    strcpy(matchcode,recordp->MCtcstdiscountcont);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTDISCOUNTCONT_LISTE
    from CSTDISCOUNTCONT
    DWtcstdiscountcont
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTDISCOUNTCONT_LISTE
    from CSTDISCOUNTCONT
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
/*  FUNCTION: pxCustDiscConditionGetNext                                       */
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
int pxCustDiscConditionGetNext
(
    struct tCSTDISCOUNTCONT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_GetNext;
    recordp = (struct C_CSTDISCOUNTCONT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTDISCOUNTCONT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTDISCOUNTCONT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustDiscConditionEndBrowse                                     */
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
int pxCustDiscConditionEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTDISCOUNTCONT*10+F_EndBrowse;

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
/*  FUNCTION: pxCustDiscConditionRead                                          */
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

int pxCustDiscConditionRead
(
    struct tCSTDISCOUNTCONT* record
#ifdef SKtcstdiscountcont
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_Read;
    recordp = (struct C_CSTDISCOUNTCONT *) record;

#ifdef SKtcstdiscountcont
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTDISCOUNTCONT_LISTE
     into CSTDISCOUNTCONT_ZEIGER(recordp)
     from CSTDISCOUNTCONT
     where SKtcstdiscountcont;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTDISCOUNTCONT_LISTE
     into CSTDISCOUNTCONT_ZEIGER(recordp)
     from CSTDISCOUNTCONT
     where PKtcstdiscountcont;

#ifdef SKtcstdiscountcont
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
/*  FUNCTION: pxCustDiscConditionReadLock                                      */
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
int pxCustDiscConditionReadLock
(
    struct tCSTDISCOUNTCONT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_ReadLock;
    recordp = (struct C_CSTDISCOUNTCONT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstdiscountcont_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTDISCOUNTCONT_LISTE
    from CSTDISCOUNTCONT
    where PKtcstdiscountcont
    FOR UPDATE;
    EXEC SQL OPEN tcstdiscountcont_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstdiscountcont_U1
      into CSTDISCOUNTCONT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTDISCOUNTCONT_LISTE
    into CSTDISCOUNTCONT_ZEIGER(recordp)
    from CSTDISCOUNTCONT    HOLDLOCK
    where PKtcstdiscountcont;
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
/*  FUNCTION: pxCustDiscConditionUpdate                                        */
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

int pxCustDiscConditionUpdate
(
    struct tCSTDISCOUNTCONT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_Update;
    recordp = (struct C_CSTDISCOUNTCONT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTDISCOUNTCONT
    SET
    CSTDISCOUNTCONT_UPDATE(recordp)
    where current of tcstdiscountcont_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstdiscountcont_U1;
    }
#else

    EXEC SQL UPDATE
    CSTDISCOUNTCONT
    SET
    CSTDISCOUNTCONT_UPDATE(recordp)
    where PKtcstdiscountcont;
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
/*  FUNCTION: pxCustDiscConditionInsert                                       */
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
int pxCustDiscConditionInsert
(
    struct tCSTDISCOUNTCONT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_Insert;
    recordp = (struct C_CSTDISCOUNTCONT *) record;

    EXEC SQL INSERT INTO
    CSTDISCOUNTCONT
    (CSTDISCOUNTCONT_LISTE)
    VALUES ( CSTDISCOUNTCONT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTDISCOUNTCONT
    VALUES ( CSTDISCOUNTCONT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustDiscConditionDelete                                        */
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

int pxCustDiscConditionDelete
(
    struct tCSTDISCOUNTCONT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTDISCOUNTCONT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTDISCOUNTCONT*10+F_Delete;
    recordp = (struct C_CSTDISCOUNTCONT *) record;

    EXEC SQL DELETE FROM
    CSTDISCOUNTCONT
    where PKtcstdiscountcont;

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
