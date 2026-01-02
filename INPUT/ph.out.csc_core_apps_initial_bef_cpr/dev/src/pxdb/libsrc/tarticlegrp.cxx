/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticlegrp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleGrpStartBrowse  declare and open Cursor
        pxArticleGrpGetNext      get next record
        pxArticleGrpEndBrowse    close cursor
        pxArticleGrpRead         get one record
        pxArticleGrpReadLock     get one record with lock
        pxArticleGrpInsert       Insert record
        pxArticleGrpUpdate       Update record
        pxArticleGrpDelete       Delete record


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
#include <tarticlegrp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleGrpStartBrowse                                   */
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
int pxArticleGrpStartBrowse
(
     struct tARTICLEGROUP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
#ifdef MCtarticlegrp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_StartBrowse;
    recordp = (struct C_ARTICLEGRP *) record;

    if (!(sizeof(struct C_ARTICLEGRP) == sizeof(struct tARTICLEGROUP)))
       return cDBXR_DEFINITION;


#ifdef MCtarticlegrp
    strcpy(matchcode,recordp->MCtarticlegrp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLEGRP_LISTE
    from ARTICLEGROUP
    DWtarticlegrp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLEGRP_LISTE
    from ARTICLEGROUP
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
/*  FUNCTION: pxArticleGrpGetNext                                       */
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
int pxArticleGrpGetNext
(
    struct tARTICLEGROUP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_GetNext;
    recordp = (struct C_ARTICLEGRP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLEGRP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLEGRP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleGrpEndBrowse                                     */
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
int pxArticleGrpEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLEGROUP*10+F_EndBrowse;

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
/*  FUNCTION: pxArticleGrpRead                                          */
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

int pxArticleGrpRead
(
    struct tARTICLEGROUP* record
#ifdef SKtarticlegrp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_Read;
    recordp = (struct C_ARTICLEGRP *) record;

#ifdef SKtarticlegrp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLEGRP_LISTE
     into ARTICLEGRP_ZEIGER(recordp)
     from ARTICLEGROUP
     where SKtarticlegrp;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLEGRP_LISTE
     into ARTICLEGRP_ZEIGER(recordp)
     from ARTICLEGROUP
     where PKtarticlegrp;

#ifdef SKtarticlegrp
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
/*  FUNCTION: pxArticleGrpReadLock                                      */
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
int pxArticleGrpReadLock
(
    struct tARTICLEGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_ReadLock;
    recordp = (struct C_ARTICLEGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tarticlegrp_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLEGRP_LISTE
    from ARTICLEGROUP
    where PKtarticlegrp
    FOR UPDATE;
    EXEC SQL OPEN tarticlegrp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticlegrp_U1
      into ARTICLEGRP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLEGRP_LISTE
    into ARTICLEGRP_ZEIGER(recordp)
    from ARTICLEGROUP    HOLDLOCK
    where PKtarticlegrp;
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
/*  FUNCTION: pxArticleGrpUpdate                                        */
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

int pxArticleGrpUpdate
(
    struct tARTICLEGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_Update;
    recordp = (struct C_ARTICLEGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLEGROUP
    SET
    ARTICLEGRP_UPDATE(recordp)
    where current of tarticlegrp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticlegrp_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLEGROUP
    SET
    ARTICLEGRP_UPDATE(recordp)
    where PKtarticlegrp;
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
/*  FUNCTION: pxArticleGrpInsert                                       */
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
int pxArticleGrpInsert
(
    struct tARTICLEGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_Insert;
    recordp = (struct C_ARTICLEGRP *) record;

    EXEC SQL INSERT INTO
    ARTICLEGROUP
    (ARTICLEGRP_LISTE)
    VALUES ( ARTICLEGRP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLEGROUP
    VALUES ( ARTICLEGRP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArticleGrpDelete                                        */
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

int pxArticleGrpDelete
(
    struct tARTICLEGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEGROUP*10+F_Delete;
    recordp = (struct C_ARTICLEGRP *) record;

    EXEC SQL DELETE FROM
    ARTICLEGROUP
    where PKtarticlegrp;

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
