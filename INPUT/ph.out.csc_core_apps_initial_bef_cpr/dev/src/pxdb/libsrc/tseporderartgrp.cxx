/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tseporderartgrp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxSepOrderArtGroupStartBrowse  declare and open Cursor
        pxSepOrderArtGroupGetNext      get next record
        pxSepOrderArtGroupEndBrowse    close cursor
        pxSepOrderArtGroupRead         get one record
        pxSepOrderArtGroupReadLock     get one record with lock
        pxSepOrderArtGroupInsert       Insert record
        pxSepOrderArtGroupUpdate       Update record
        pxSepOrderArtGroupDelete       Delete record


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
#include <tseporderartgrp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSepOrderArtGroupStartBrowse                                   */
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
int pxSepOrderArtGroupStartBrowse
(
     struct tSEPORDERARTGRP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
#ifdef MCtseporderartgrp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_StartBrowse;
    recordp = (struct C_SEPORDERARTGRP *) record;

    if (!(sizeof(struct C_SEPORDERARTGRP) == sizeof(struct tSEPORDERARTGRP)))
       return cDBXR_DEFINITION;


#ifdef MCtseporderartgrp
    strcpy(matchcode,recordp->MCtseporderartgrp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        SEPORDERARTGRP_LISTE
    from SEPORDERARTGRP
    DWtseporderartgrp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        SEPORDERARTGRP_LISTE
    from SEPORDERARTGRP
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
/*  FUNCTION: pxSepOrderArtGroupGetNext                                       */
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
int pxSepOrderArtGroupGetNext
(
    struct tSEPORDERARTGRP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_GetNext;
    recordp = (struct C_SEPORDERARTGRP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into SEPORDERARTGRP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into SEPORDERARTGRP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSepOrderArtGroupEndBrowse                                     */
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
int pxSepOrderArtGroupEndBrowse
(
    int browseid
)
{
    functionnr = F_SEPORDERARTGRP*10+F_EndBrowse;

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
/*  FUNCTION: pxSepOrderArtGroupRead                                          */
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

int pxSepOrderArtGroupRead
(
    struct tSEPORDERARTGRP* record
#ifdef SKtseporderartgrp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_Read;
    recordp = (struct C_SEPORDERARTGRP *) record;

#ifdef SKtseporderartgrp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        SEPORDERARTGRP_LISTE
     into SEPORDERARTGRP_ZEIGER(recordp)
     from SEPORDERARTGRP
     where SKtseporderartgrp;
     break;
    default:
#endif

    EXEC SQL SELECT
        SEPORDERARTGRP_LISTE
     into SEPORDERARTGRP_ZEIGER(recordp)
     from SEPORDERARTGRP
     where PKtseporderartgrp;

#ifdef SKtseporderartgrp
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
/*  FUNCTION: pxSepOrderArtGroupReadLock                                      */
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
int pxSepOrderArtGroupReadLock
(
    struct tSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_ReadLock;
    recordp = (struct C_SEPORDERARTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tseporderartgrp_U1 CURSOR WITH HOLD FOR
        SELECT
        SEPORDERARTGRP_LISTE
    from SEPORDERARTGRP
    where PKtseporderartgrp
    FOR UPDATE;
    EXEC SQL OPEN tseporderartgrp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tseporderartgrp_U1
      into SEPORDERARTGRP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         SEPORDERARTGRP_LISTE
    into SEPORDERARTGRP_ZEIGER(recordp)
    from SEPORDERARTGRP    HOLDLOCK
    where PKtseporderartgrp;
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
/*  FUNCTION: pxSepOrderArtGroupUpdate                                        */
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

int pxSepOrderArtGroupUpdate
(
    struct tSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_Update;
    recordp = (struct C_SEPORDERARTGRP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    SEPORDERARTGRP
    SET
    SEPORDERARTGRP_UPDATE(recordp)
    where current of tseporderartgrp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tseporderartgrp_U1;
    }
#else

    EXEC SQL UPDATE
    SEPORDERARTGRP
    SET
    SEPORDERARTGRP_UPDATE(recordp)
    where PKtseporderartgrp;
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
/*  FUNCTION: pxSepOrderArtGroupInsert                                       */
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
int pxSepOrderArtGroupInsert
(
    struct tSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_Insert;
    recordp = (struct C_SEPORDERARTGRP *) record;

    EXEC SQL INSERT INTO
    SEPORDERARTGRP
    (SEPORDERARTGRP_LISTE)
    VALUES ( SEPORDERARTGRP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    SEPORDERARTGRP
    VALUES ( SEPORDERARTGRP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxSepOrderArtGroupDelete                                        */
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

int pxSepOrderArtGroupDelete
(
    struct tSEPORDERARTGRP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SEPORDERARTGRP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SEPORDERARTGRP*10+F_Delete;
    recordp = (struct C_SEPORDERARTGRP *) record;

    EXEC SQL DELETE FROM
    SEPORDERARTGRP
    where PKtseporderartgrp;

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
