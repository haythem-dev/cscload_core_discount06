/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartalt.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtikelAlternStartBrowse  declare and open Cursor
        pxArtikelAlternGetNext      get next record
        pxArtikelAlternEndBrowse    close cursor
        pxArtikelAlternRead         get one record
        pxArtikelAlternReadLock     get one record with lock
        pxArtikelAlternInsert       Insert record
        pxArtikelAlternUpdate       Update record
        pxArtikelAlternDelete       Delete record


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
#include "tartalt.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelAlternStartBrowse                                   */
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
int pxArtikelAlternStartBrowse
(
     struct tARTIKELALTERN* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
#ifdef MCtartalt
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_StartBrowse;
    recordp = (struct C_ARTIKELALTERN *) record;

    if (!(sizeof(struct C_ARTIKELALTERN) == sizeof(struct tARTIKELALTERN)))
       return cDBXR_DEFINITION;


#ifdef MCtartalt
    strcpy(matchcode,recordp->MCtartalt);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTIKELALTERN_LISTE
    from ARTIKELALTERN
    DWtartalt
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTIKELALTERN_LISTE
    from ARTIKELALTERN
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTIKELALTERN_LISTE
    from  ARTIKELALTERN
    inner join ARTIKELZENTRAL on  ARTIKELZENTRAL.ARTIKEL_NR = ARTIKELALTERN.ARTIKEL_NR_ALTERN
    inner join ARTIKELLOKAL on    ARTIKELLOKAL.ARTIKEL_NR = ARTIKELALTERN.ARTIKEL_NR_ALTERN and ARTIKELLOKAL.FILIALNR = ARTIKELALTERN.FILIALNR
    where ARTIKELALTERN.ARTIKEL_NR   = :recordp->ARTIKEL_NR
    and   ARTIKELALTERN.FILIALNR     = :recordp->FILIALNR
    and ARTIKELLOKAL.ARTIKELAKTIV  = 1

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        ARTIKELALTERN_LISTE
    from  ARTIKELALTERN
    inner join ARTIKELZENTRAL on  ARTIKELZENTRAL.ARTIKEL_NR = ARTIKELALTERN.ARTIKEL_NR
    inner join ARTIKELLOKAL on    ARTIKELLOKAL.ARTIKEL_NR = ARTIKELALTERN.ARTIKEL_NR and ARTIKELLOKAL.FILIALNR = ARTIKELALTERN.FILIALNR
    inner join ARTIKELLAGERORT on ARTIKELLAGERORT.ARTIKEL_NR = ARTIKELALTERN.ARTIKEL_NR and ARTIKELLAGERORT.FILIALNR = ARTIKELALTERN.FILIALNR
    where ARTIKELALTERN.ARTIKEL_NR_ALTERN   = :recordp->ARTIKEL_NR_ALTERN
    and   ARTIKELALTERN.FILIALNR            = :recordp->FILIALNR
    and ARTIKELLOKAL.ARTIKELAKTIV  = 1
    and ARTIKELLOKAL.BESTAND > 0
    order by  ARTIKELLOKAL.BESTAND, ARTIKELLAGERORT.DATUMVERFALL desc
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
       case cCRSARTIKELALTERN_FORWARD:
          EXEC SQL OPEN C2;
          break;
       case cCRSARTIKELALTERN_REVERSE:
          EXEC SQL OPEN C3;
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
/*  FUNCTION: pxArtikelAlternGetNext                                       */
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
int pxArtikelAlternGetNext
(
    struct tARTIKELALTERN* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_GetNext;
    recordp = (struct C_ARTIKELALTERN *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTIKELALTERN_ZEIGER(recordp);
          break;
       case cCRSARTIKELALTERN_FORWARD:
          EXEC SQL FETCH C2
          into ARTIKELALTERN_ZEIGER(recordp);
          break;
       case cCRSARTIKELALTERN_REVERSE:
          EXEC SQL FETCH C3
          into ARTIKELALTERN_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTIKELALTERN_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelAlternEndBrowse                                     */
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
int pxArtikelAlternEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELALTERN*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSARTIKELALTERN_FORWARD:
          EXEC SQL CLOSE C2;
          break;
       case cCRSARTIKELALTERN_REVERSE:
          EXEC SQL CLOSE C3;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtikelAlternRead                                          */
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

int pxArtikelAlternRead
(
    struct tARTIKELALTERN* record
#ifdef SKtartalt
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_Read;
    recordp = (struct C_ARTIKELALTERN *) record;

#ifdef SKtartalt
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTIKELALTERN_LISTE
     into ARTIKELALTERN_ZEIGER(recordp)
     from ARTIKELALTERN
     where SKtartalt;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTIKELALTERN_LISTE
     into ARTIKELALTERN_ZEIGER(recordp)
     from ARTIKELALTERN
     where PKtartalt;

#ifdef SKtartalt
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
/*  FUNCTION: pxArtikelAlternReadLock                                      */
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
int pxArtikelAlternReadLock
(
    struct tARTIKELALTERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_ReadLock;
    recordp = (struct C_ARTIKELALTERN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTALT_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELALTERN_LISTE
    from ARTIKELALTERN
    where PKtartalt
    FOR UPDATE;
    EXEC SQL OPEN TARTALT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTALT_U1
      into ARTIKELALTERN_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTIKELALTERN_LISTE
    into ARTIKELALTERN_ZEIGER(recordp)
    from ARTIKELALTERN    HOLDLOCK
    where PKtartalt;
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
/*  FUNCTION: pxArtikelAlternUpdate                                        */
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

int pxArtikelAlternUpdate
(
    struct tARTIKELALTERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_Update;
    recordp = (struct C_ARTIKELALTERN *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTIKELALTERN
    SET
    ARTIKELALTERN_UPDATE(recordp)
    where current of TARTALT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTALT_U1;
    }
#else

    EXEC SQL UPDATE
    ARTIKELALTERN
    SET
    ARTIKELALTERN_UPDATE(recordp)
    where PKtartalt;
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
/*  FUNCTION: pxArtikelAlternInsert                                       */
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
int pxArtikelAlternInsert
(
    struct tARTIKELALTERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_Insert;
    recordp = (struct C_ARTIKELALTERN *) record;

    EXEC SQL INSERT INTO
    ARTIKELALTERN
    (ARTIKELALTERN_LISTE)
    VALUES ( ARTIKELALTERN_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTIKELALTERN
    VALUES ( ARTIKELALTERN_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtikelAlternDelete                                        */
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

int pxArtikelAlternDelete
(
    struct tARTIKELALTERN* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELALTERN * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELALTERN*10+F_Delete;
    recordp = (struct C_ARTIKELALTERN *) record;

    EXEC SQL DELETE FROM
    ARTIKELALTERN
    where PKtartalt;

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
