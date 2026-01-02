/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragprolink.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderProLinkStartBrowse  declare and open Cursor
        pxOrderProLinkGetNext      get next record
        pxOrderProLinkEndBrowse    close cursor
        pxOrderProLinkRead         get one record
        pxOrderProLinkReadLock     get one record with lock
        pxOrderProLinkInsert       Insert record
        pxOrderProLinkUpdate       Update record
        pxOrderProLinkDelete       Delete record


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
#include <tkdauftragprolink.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderProLinkStartBrowse                                   */
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
int pxOrderProLinkStartBrowse
(
     struct tKDAUFTRAGPROLINK* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
#ifdef MCtkdauftragprolink
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;

    if (!(sizeof(struct C_KDAUFTRAGPROLINK) == sizeof(struct tKDAUFTRAGPROLINK)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragprolink
    strcpy(matchcode,recordp->MCtkdauftragprolink);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPROLINK_LISTE
    from KDAUFTRAGPROLINK
    DWtkdauftragprolink
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPROLINK_LISTE
    from KDAUFTRAGPROLINK
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
/*  FUNCTION: pxOrderProLinkGetNext                                       */
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
int pxOrderProLinkGetNext
(
    struct tKDAUFTRAGPROLINK* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPROLINK_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPROLINK_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderProLinkEndBrowse                                     */
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
int pxOrderProLinkEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPROLINK*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderProLinkRead                                          */
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

int pxOrderProLinkRead
(
    struct tKDAUFTRAGPROLINK* record
#ifdef SKtkdauftragprolink
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_Read;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;

#ifdef SKtkdauftragprolink
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPROLINK_LISTE
     into KDAUFTRAGPROLINK_ZEIGER(recordp)
     from KDAUFTRAGPROLINK
     where SKtkdauftragprolink;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPROLINK_LISTE
     into KDAUFTRAGPROLINK_ZEIGER(recordp)
     from KDAUFTRAGPROLINK
     where PKtkdauftragprolink;

#ifdef SKtkdauftragprolink
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
/*  FUNCTION: pxOrderProLinkReadLock                                      */
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
int pxOrderProLinkReadLock
(
    struct tKDAUFTRAGPROLINK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragprolink_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPROLINK_LISTE
    from KDAUFTRAGPROLINK
    where PKtkdauftragprolink
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragprolink_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragprolink_U1
      into KDAUFTRAGPROLINK_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPROLINK_LISTE
    into KDAUFTRAGPROLINK_ZEIGER(recordp)
    from KDAUFTRAGPROLINK    HOLDLOCK
    where PKtkdauftragprolink;
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
/*  FUNCTION: pxOrderProLinkUpdate                                        */
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

int pxOrderProLinkUpdate
(
    struct tKDAUFTRAGPROLINK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_Update;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPROLINK
    SET
    KDAUFTRAGPROLINK_UPDATE(recordp)
    where current of tkdauftragprolink_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragprolink_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPROLINK
    SET
    KDAUFTRAGPROLINK_UPDATE(recordp)
    where PKtkdauftragprolink;
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
/*  FUNCTION: pxOrderProLinkInsert                                       */
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
int pxOrderProLinkInsert
(
    struct tKDAUFTRAGPROLINK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPROLINK
    (KDAUFTRAGPROLINK_LISTE)
    VALUES ( KDAUFTRAGPROLINK_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPROLINK
    VALUES ( KDAUFTRAGPROLINK_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderProLinkDelete                                        */
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

int pxOrderProLinkDelete
(
    struct tKDAUFTRAGPROLINK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPROLINK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPROLINK*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPROLINK *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPROLINK
    where PKtkdauftragprolink;

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
