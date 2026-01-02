/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttenderpos.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTenderPosStartBrowse  declare and open Cursor
        pxTenderPosGetNext      get next record
        pxTenderPosEndBrowse    close cursor
        pxTenderPosRead         get one record
        pxTenderPosReadLock     get one record with lock
        pxTenderPosInsert       Insert record
        pxTenderPosUpdate       Update record
        pxTenderPosDelete       Delete record


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
#include <ttenderpos.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderPosStartBrowse                                   */
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
int pxTenderPosStartBrowse
(
     struct tTENDERPOS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
#ifdef MCttenderpos
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_StartBrowse;
    recordp = (struct C_TENDERPOS *) record;

    if (!(sizeof(struct C_TENDERPOS) == sizeof(struct tTENDERPOS)))
       return cDBXR_DEFINITION;


#ifdef MCttenderpos
    strcpy(matchcode,recordp->MCttenderpos);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TENDERPOS_LISTE
    from TENDERPOS
    DWttenderpos
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TENDERPOS_LISTE
    from TENDERPOS
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TENDERPOS_LISTE
    from TENDERPOS
    where TENDERNO     = :recordp->TENDERNO
    and   TENDERSTATE  != :recordp->TENDERSTATE
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
       case cCRTPTENDERNOSTATE:
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
/*  FUNCTION: pxTenderPosGetNext                                       */
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
int pxTenderPosGetNext
(
    struct tTENDERPOS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_GetNext;
    recordp = (struct C_TENDERPOS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TENDERPOS_ZEIGER(recordp);
          break;
       case cCRTPTENDERNOSTATE:
          EXEC SQL FETCH C2
          into TENDERPOS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TENDERPOS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderPosEndBrowse                                     */
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
int pxTenderPosEndBrowse
(
    int browseid
)
{
    functionnr = F_TENDERPOS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRTPTENDERNOSTATE:
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
/*  FUNCTION: pxTenderPosRead                                          */
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

int pxTenderPosRead
(
    struct tTENDERPOS* record
#ifdef SKttenderpos
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_Read;
    recordp = (struct C_TENDERPOS *) record;

#ifdef SKttenderpos
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TENDERPOS_LISTE
     into TENDERPOS_ZEIGER(recordp)
     from TENDERPOS
     where SKttenderpos;
     break;
    default:
#endif

    EXEC SQL SELECT
        TENDERPOS_LISTE
     into TENDERPOS_ZEIGER(recordp)
     from TENDERPOS
     where PKttenderpos;

#ifdef SKttenderpos
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
/*  FUNCTION: pxTenderPosReadLock                                      */
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
int pxTenderPosReadLock
(
    struct tTENDERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_ReadLock;
    recordp = (struct C_TENDERPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttenderpos_U1 CURSOR WITH HOLD FOR
        SELECT
        TENDERPOS_LISTE
    from TENDERPOS
    where PKttenderpos
    FOR UPDATE;
    EXEC SQL OPEN ttenderpos_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttenderpos_U1
      into TENDERPOS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TENDERPOS_LISTE
    into TENDERPOS_ZEIGER(recordp)
    from TENDERPOS    HOLDLOCK
    where PKttenderpos;
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
/*  FUNCTION: pxTenderPosUpdate                                        */
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

int pxTenderPosUpdate
(
    struct tTENDERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_Update;
    recordp = (struct C_TENDERPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TENDERPOS
    SET
    TENDERPOS_UPDATE(recordp)
    where current of ttenderpos_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttenderpos_U1;
    }
#else

    EXEC SQL UPDATE
    TENDERPOS
    SET
    TENDERPOS_UPDATE(recordp)
    where PKttenderpos;
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
/*  FUNCTION: pxTenderPosInsert                                       */
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
int pxTenderPosInsert
(
    struct tTENDERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_Insert;
    recordp = (struct C_TENDERPOS *) record;

    EXEC SQL INSERT INTO
    TENDERPOS
    (TENDERPOS_LISTE)
    VALUES ( TENDERPOS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TENDERPOS
    VALUES ( TENDERPOS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTenderPosDelete                                        */
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

int pxTenderPosDelete
(
    struct tTENDERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPOS*10+F_Delete;
    recordp = (struct C_TENDERPOS *) record;

    EXEC SQL DELETE FROM
    TENDERPOS
    where PKttenderpos;

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
