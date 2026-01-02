/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-2000 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartmas.c (.sqc)

    Database functions for master article data




    FUNCTIONS:

        pxMArtikelStartBrowse  declare and open Cursor
        pxMArtikelGetNext      get next record
        pxMArtikelEndBrowse    close cursor
        pxMArtikelRead         get one record
        pxMArtikelReadLock     get one record with lock
        pxMArtikelInsert       Insert record
        pxMArtikelUpdate       Update record
        pxMArtikelDelete       Delete record


REVISION HISTORY

25 Apr 2000 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tartikelzentral.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxMArtikelStartBrowse                                   */
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
int pxMArtikelStartBrowse
(
     struct tMARTIKEL* record,
     int browseid
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
#ifdef MCtmartikel
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_StartBrowse;
    recordp = (struct C_ARTIKELZENTRAL *) record;

#ifdef MCtmartikel
    strcpy(matchcode,recordp->MCtmartikel);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
    DWtmartikel
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
    DWtmartikel
    and   DARREICHFORM = :recordp->DARREICHFORM
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
    DWtmartikel
    and   PACKGROESSE  = :recordp->PACKGROESSE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
    DWtmartikel
    and DARREICHFORM = :recordp->DARREICHFORM
    and PACKGROESSE  = :recordp->PACKGROESSE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    switch (browseid)
    {
       case cCRS_DARREICHFORM:
          EXEC SQL OPEN C2;
          break;
       case cCRS_PACKGROESSE:
          EXEC SQL OPEN C3;
          break;
       case cCRS_GROESSE_FORM:
          EXEC SQL OPEN C4;
          break;
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
/*  FUNCTION: pxMArtikelGetNext                                       */
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
int pxMArtikelGetNext
(
    struct tMARTIKEL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_GetNext;
    recordp = (struct C_ARTIKELZENTRAL *) record;

    switch (browseid)
    {
       case cCRS_DARREICHFORM:
          EXEC SQL FETCH C2
          into ARTIKELZENTRAL_ZEIGER(recordp);
          break;
       case cCRS_PACKGROESSE:
          EXEC SQL FETCH C3
          into ARTIKELZENTRAL_ZEIGER(recordp);
          break;
       case cCRS_GROESSE_FORM:
          EXEC SQL FETCH C4
          into ARTIKELZENTRAL_ZEIGER(recordp);
          break;
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTIKELZENTRAL_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTIKELZENTRAL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxMArtikelEndBrowse                                     */
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
int pxMArtikelEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELZENTRAL*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_DARREICHFORM:
          EXEC SQL CLOSE C2;
          break;
       case cCRS_PACKGROESSE:
          EXEC SQL CLOSE C3;
          break;
       case cCRS_GROESSE_FORM:
          EXEC SQL CLOSE C4;
          break;
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
/*  FUNCTION: pxMArtikelRead                                          */
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

int pxMArtikelRead
(
    struct tMARTIKEL* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_Read;
    recordp = (struct C_ARTIKELZENTRAL *) record;



    EXEC SQL SELECT
        ARTIKELZENTRAL_LISTE
     into ARTIKELZENTRAL_ZEIGER(recordp)
     from ARTIKELZENTRAL
     where PKtmartikel;

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
/*  FUNCTION: pxMArtikelReadLock                                      */
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
int pxMArtikelReadLock
(
    struct tMARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_ReadLock;
    recordp = (struct C_ARTIKELZENTRAL *) record;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TMARTIKEL_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELZENTRAL_LISTE
    from ARTIKELZENTRAL
    where PKtmartikel
    FOR UPDATE;
    EXEC SQL OPEN TMARTIKEL_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TMARTIKEL_U1
      into ARTIKELZENTRAL_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTIKELZENTRAL_LISTE
    into ARTIKELZENTRAL_ZEIGER(recordp)
    from ARTIKELZENTRAL    HOLDLOCK
    where PKtmartikel;
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
/*  FUNCTION: pxMArtikelUpdate                                        */
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

int pxMArtikelUpdate
(
    struct tMARTIKEL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_Update;
    recordp = (struct C_ARTIKELZENTRAL *) record;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTIKELZENTRAL
    SET
    ARTIKELZENTRAL_UPDATE(recordp)
    where current of TMARTIKEL_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TMARTIKEL_U1;
    }
#else
    EXEC SQL UPDATE
    ARTIKELZENTRAL
    SET
    ARTIKELZENTRAL_UPDATE(recordp)
    where PKtmartikel;
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
/*  FUNCTION: pxMArtikelInsert                                       */
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
int pxMArtikelInsert
(
    struct tMARTIKEL* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_Insert;
    recordp = (struct C_ARTIKELZENTRAL *) record;

    EXEC SQL INSERT INTO
    ARTIKELZENTRAL
    (ARTIKELZENTRAL_LISTE)
    VALUES ( ARTIKELZENTRAL_ZEIGER(recordp) );


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
/*  FUNCTION: pxMArtikelDelete                                        */
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

int pxMArtikelDelete
(
    struct tMARTIKEL* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELZENTRAL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELZENTRAL*10+F_Delete;
    recordp = (struct C_ARTIKELZENTRAL *) record;

    EXEC SQL DELETE FROM
    ARTIKELZENTRAL
    where PKtmartikel;

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
