/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdiscountgrp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxRangeStartBrowse  declare and open Cursor
        pxRangeGetNext      get next record
        pxRangeEndBrowse    close cursor
        pxRangeRead         get one record
        pxRangeReadLock     get one record with lock
        pxRangeInsert       Insert record
        pxRangeUpdate       Update record
        pxRangeDelete       Delete record


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
#include <tdiscountgrp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRangeStartBrowse                                   */
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
int pxRangeStartBrowse
(
     struct tDISCOUNTGRP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
#ifdef MCtdiscountgrp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_StartBrowse;
    recordp = (struct C_DISCOUNTGRP *) record;

    if (!(sizeof(struct C_DISCOUNTGRP) == sizeof(struct tDISCOUNTGRP)))
       return cDBXR_DEFINITION;


#ifdef MCtdiscountgrp
    strcpy(matchcode,recordp->MCtdiscountgrp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISCOUNTGRP_LISTE
    from DISCOUNTGRP
    DWtdiscountgrp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISCOUNTGRP_LISTE
    from DISCOUNTGRP
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        DISCOUNTGRP_LISTE
    from DISCOUNTGRP
    where BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNTGRPTYPE = :recordp->DISCOUNTGRPTYPE
    and   CUSTOMERNO      = :recordp->CUSTOMERNO
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
       case cCRSDISCOUNTGRPTYPE       :
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
/*  FUNCTION: pxRangeGetNext                                       */
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
int pxRangeGetNext
(
    struct tDISCOUNTGRP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_GetNext;
    recordp = (struct C_DISCOUNTGRP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISCOUNTGRP_ZEIGER(recordp);
          break;
       case cCRSDISCOUNTGRPTYPE       :
          EXEC SQL FETCH C2
          into DISCOUNTGRP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DISCOUNTGRP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRangeEndBrowse                                     */
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
int pxRangeEndBrowse
(
    int browseid
)
{
    functionnr = F_DISCOUNTGRP*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSDISCOUNTGRPTYPE:
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
/*  FUNCTION: pxRangeRead                                          */
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

int pxRangeRead
(
    struct tDISCOUNTGRP* record
#ifdef SKtdiscountgrp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_Read;
    recordp = (struct C_DISCOUNTGRP *) record;

#ifdef SKtdiscountgrp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISCOUNTGRP_LISTE
     into DISCOUNTGRP_ZEIGER(recordp)
     from DISCOUNTGRP
     where SKtdiscountgrp;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISCOUNTGRP_LISTE
     into DISCOUNTGRP_ZEIGER(recordp)
     from DISCOUNTGRP
     where PKtdiscountgrp;

#ifdef SKtdiscountgrp
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
/*  FUNCTION: pxRangeReadLock                                      */
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
int pxRangeReadLock
(
    struct tDISCOUNTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_ReadLock;
    recordp = (struct C_DISCOUNTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdiscountgrp_U1 CURSOR WITH HOLD FOR
        SELECT
        DISCOUNTGRP_LISTE
    from DISCOUNTGRP
    where PKtdiscountgrp
    FOR UPDATE;
    EXEC SQL OPEN tdiscountgrp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdiscountgrp_U1
      into DISCOUNTGRP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISCOUNTGRP_LISTE
    into DISCOUNTGRP_ZEIGER(recordp)
    from DISCOUNTGRP    HOLDLOCK
    where PKtdiscountgrp;
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
/*  FUNCTION: pxRangeUpdate                                        */
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

int pxRangeUpdate
(
    struct tDISCOUNTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_Update;
    recordp = (struct C_DISCOUNTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISCOUNTGRP
    SET
    DISCOUNTGRP_UPDATE(recordp)
    where current of tdiscountgrp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdiscountgrp_U1;
    }
#else

    EXEC SQL UPDATE
    DISCOUNTGRP
    SET
    DISCOUNTGRP_UPDATE(recordp)
    where PKtdiscountgrp;
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
/*  FUNCTION: pxRangeInsert                                       */
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
int pxRangeInsert
(
    struct tDISCOUNTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_Insert;
    recordp = (struct C_DISCOUNTGRP *) record;

    EXEC SQL INSERT INTO
    DISCOUNTGRP
    (DISCOUNTGRP_LISTE)
    VALUES ( DISCOUNTGRP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISCOUNTGRP
    VALUES ( DISCOUNTGRP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxRangeDelete                                        */
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

int pxRangeDelete
(
    struct tDISCOUNTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRP*10+F_Delete;
    recordp = (struct C_DISCOUNTGRP *) record;

    EXEC SQL DELETE FROM
    DISCOUNTGRP
    where PKtdiscountgrp;

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
