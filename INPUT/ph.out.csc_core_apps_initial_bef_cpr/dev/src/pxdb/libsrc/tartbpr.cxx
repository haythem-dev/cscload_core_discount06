/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartbpr.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtikelpreisStartBrowse  declare and open Cursor
        pxArtikelpreisGetNext      get next record
        pxArtikelpreisEndBrowse    close cursor
        pxArtikelpreisRead         get one record
        pxArtikelpreisReadLock     get one record with lock
        pxArtikelpreisInsert       Insert record
        pxArtikelpreisUpdate       Update record
        pxArtikelpreisDelete       Delete record


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tartbpr.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelpreisStartBrowse                                   */
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
int pxArtikelpreisStartBrowse
(
     struct tARTIKELPREIS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
#ifdef MCtartbpr
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_StartBrowse;
    recordp = (struct C_ARTIKELPREIS *) record;

    if (!(sizeof(struct C_ARTIKELPREIS) == sizeof(struct tARTIKELPREIS)))
       return cDBXR_DEFINITION;


#ifdef MCtartbpr
    strcpy(matchcode,recordp->MCtartbpr);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE TARTBPR_C1 CURSOR FOR
        SELECT
        ARTIKELPREIS_LISTE
    from ARTIKELPREIS
    DWtartbpr
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE TARTBPR_C0 CURSOR FOR
        SELECT
        ARTIKELPREIS_LISTE
    from ARTIKELPREIS
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTIKELPREIS_LISTE
    from ARTIKELPREIS
    where ARTIKEL_NR = :recordp->ARTIKEL_NR
	and PREIS_TYP = :recordp->PREIS_TYP
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN TARTBPR_C0;
          break;
       case cCRS_TARTBPRTYPE:
          EXEC SQL OPEN C2;
          break;
       default:
          EXEC SQL OPEN TARTBPR_C1;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelpreisGetNext                                       */
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
int pxArtikelpreisGetNext
(
    struct tARTIKELPREIS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_GetNext;
    recordp = (struct C_ARTIKELPREIS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH TARTBPR_C0
          into ARTIKELPREIS_ZEIGER(recordp);
          break;
       case cCRS_TARTBPRTYPE:
          EXEC SQL FETCH C2
          into ARTIKELPREIS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH TARTBPR_C1
          into ARTIKELPREIS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelpreisEndBrowse                                     */
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
int pxArtikelpreisEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELPREIS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE TARTBPR_C0;
          break;
       case cCRS_TARTBPRTYPE:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE TARTBPR_C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelpreisRead                                          */
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

int pxArtikelpreisRead
(
    struct tARTIKELPREIS* record
#ifdef SKtartbpr
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_Read;
    recordp = (struct C_ARTIKELPREIS *) record;

#ifdef SKtartbpr
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTIKELPREIS_LISTE
     into ARTIKELPREIS_ZEIGER(recordp)
     from ARTIKELPREIS
     where SKtartbpr;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTIKELPREIS_LISTE
     into ARTIKELPREIS_ZEIGER(recordp)
     from ARTIKELPREIS
     where PKtartbpr;

#ifdef SKtartbpr
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
/*  FUNCTION: pxArtikelpreisReadLock                                      */
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
int pxArtikelpreisReadLock
(
    struct tARTIKELPREIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_ReadLock;
    recordp = (struct C_ARTIKELPREIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTBPR_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELPREIS_LISTE
    from ARTIKELPREIS
    where PKtartbpr
    FOR UPDATE;
    EXEC SQL OPEN TARTBPR_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTBPR_U1
      into ARTIKELPREIS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTIKELPREIS_LISTE
    into ARTIKELPREIS_ZEIGER(recordp)
    from ARTIKELPREIS    HOLDLOCK
    where PKtartbpr;
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
/*  FUNCTION: pxArtikelpreisUpdate                                        */
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

int pxArtikelpreisUpdate
(
    struct tARTIKELPREIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_Update;
    recordp = (struct C_ARTIKELPREIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTIKELPREIS
    SET
    ARTIKELPREIS_UPDATE(recordp)
    where current of TARTBPR_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTBPR_U1;
    }
#else

    EXEC SQL UPDATE
    ARTIKELPREIS
    SET
    ARTIKELPREIS_UPDATE(recordp)
    where PKtartbpr;
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
/*  FUNCTION: pxArtikelpreisInsert                                       */
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
int pxArtikelpreisInsert
(
    struct tARTIKELPREIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_Insert;
    recordp = (struct C_ARTIKELPREIS *) record;

    EXEC SQL INSERT INTO
    ARTIKELPREIS
    (ARTIKELPREIS_LISTE)
    VALUES ( ARTIKELPREIS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTIKELPREIS
    VALUES ( ARTIKELPREIS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtikelpreisDelete                                        */
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

int pxArtikelpreisDelete
(
    struct tARTIKELPREIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELPREIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELPREIS*10+F_Delete;
    recordp = (struct C_ARTIKELPREIS *) record;

    EXEC SQL DELETE FROM
    ARTIKELPREIS
    where PKtartbpr;

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
