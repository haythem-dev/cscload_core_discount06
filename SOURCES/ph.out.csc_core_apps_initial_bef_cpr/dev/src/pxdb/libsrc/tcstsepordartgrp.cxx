/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstsepordartgrp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCstSepOrdArtGrpStartBrowse  declare and open Cursor
        pxCstSepOrdArtGrpGetNext      get next record
        pxCstSepOrdArtGrpEndBrowse    close cursor
        pxCstSepOrdArtGrpRead         get one record
        pxCstSepOrdArtGrpReadLock     get one record with lock
        pxCstSepOrdArtGrpInsert       Insert record
        pxCstSepOrdArtGrpUpdate       Update record
        pxCstSepOrdArtGrpDelete       Delete record


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
#include <tcstsepordartgrp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstSepOrdArtGrpStartBrowse                                   */
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
int pxCstSepOrdArtGrpStartBrowse
(
     struct tCSTSEPORDERARTGRP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
#ifdef MCtcstsepordartgrp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_StartBrowse;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;

    if (!(sizeof(struct C_CSTSEPORDERARTGRP) == sizeof(struct tCSTSEPORDERARTGRP)))
       return cDBXR_DEFINITION;


#ifdef MCtcstsepordartgrp
    strcpy(matchcode,recordp->MCtcstsepordartgrp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTSEPORDERARTGRP_LISTE
    from CSTSEPORDERARTGRP
    DWtcstsepordartgrp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTSEPORDERARTGRP_LISTE
    from CSTSEPORDERARTGRP
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
/*  FUNCTION: pxCstSepOrdArtGrpGetNext                                       */
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
int pxCstSepOrdArtGrpGetNext
(
    struct tCSTSEPORDERARTGRP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_GetNext;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTSEPORDERARTGRP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTSEPORDERARTGRP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstSepOrdArtGrpEndBrowse                                     */
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
int pxCstSepOrdArtGrpEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTSEPORDERARTGRP*10+F_EndBrowse;

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
/*  FUNCTION: pxCstSepOrdArtGrpRead                                          */
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

int pxCstSepOrdArtGrpRead
(
    struct tCSTSEPORDERARTGRP* record
#ifdef SKtcstsepordartgrp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_Read;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;

#ifdef SKtcstsepordartgrp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTSEPORDERARTGRP_LISTE
     into CSTSEPORDERARTGRP_ZEIGER(recordp)
     from CSTSEPORDERARTGRP
     where SKtcstsepordartgrp;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTSEPORDERARTGRP_LISTE
     into CSTSEPORDERARTGRP_ZEIGER(recordp)
     from CSTSEPORDERARTGRP
     where PKtcstsepordartgrp;

#ifdef SKtcstsepordartgrp
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
/*  FUNCTION: pxCstSepOrdArtGrpReadLock                                      */
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
int pxCstSepOrdArtGrpReadLock
(
    struct tCSTSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_ReadLock;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstsepordartgrp_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTSEPORDERARTGRP_LISTE
    from CSTSEPORDERARTGRP
    where PKtcstsepordartgrp
    FOR UPDATE;
    EXEC SQL OPEN tcstsepordartgrp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstsepordartgrp_U1
      into CSTSEPORDERARTGRP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTSEPORDERARTGRP_LISTE
    into CSTSEPORDERARTGRP_ZEIGER(recordp)
    from CSTSEPORDERARTGRP    HOLDLOCK
    where PKtcstsepordartgrp;
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
/*  FUNCTION: pxCstSepOrdArtGrpUpdate                                        */
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

int pxCstSepOrdArtGrpUpdate
(
    struct tCSTSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_Update;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTSEPORDERARTGRP
    SET
    CSTSEPORDERARTGRP_UPDATE(recordp)
    where current of tcstsepordartgrp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstsepordartgrp_U1;
    }
#else

    EXEC SQL UPDATE
    CSTSEPORDERARTGRP
    SET
    CSTSEPORDERARTGRP_UPDATE(recordp)
    where PKtcstsepordartgrp;
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
/*  FUNCTION: pxCstSepOrdArtGrpInsert                                       */
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
int pxCstSepOrdArtGrpInsert
(
    struct tCSTSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_Insert;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;

    EXEC SQL INSERT INTO
    CSTSEPORDERARTGRP
    (CSTSEPORDERARTGRP_LISTE)
    VALUES ( CSTSEPORDERARTGRP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTSEPORDERARTGRP
    VALUES ( CSTSEPORDERARTGRP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCstSepOrdArtGrpDelete                                        */
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

int pxCstSepOrdArtGrpDelete
(
    struct tCSTSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTSEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTSEPORDERARTGRP*10+F_Delete;
    recordp = (struct C_CSTSEPORDERARTGRP *) record;

    EXEC SQL DELETE FROM
    CSTSEPORDERARTGRP
    where PKtcstsepordartgrp;

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
