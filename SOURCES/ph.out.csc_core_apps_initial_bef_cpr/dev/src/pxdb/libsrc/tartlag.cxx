/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tartlag.c (.sqc)

    Database functions




    FUNCTIONS:

        pxLagerortStartBrowse  declare and open Cursor
        pxLagerortGetNext      get next record
        pxLagerortEndBrowse    close cursor
        pxLagerortRead         get one record
        pxLagerortReadLock     get one record with lock
        pxLagerortInsert       Insert record
        pxLagerortUpdate       Update record
        pxLagerortDelete       Delete record


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
#include "tartlag.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxLagerortStartBrowse                                   */
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
int pxLagerortStartBrowse
(
     struct tARTIKELLAGERORT* record,
     int browseid
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_StartBrowse;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    if (!(sizeof(struct C_ARTIKELLAGERORT) == sizeof(struct tARTIKELLAGERORT)))
       return cDBXR_DEFINITION;

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTIKELLAGERORT_LISTE
    from ARTIKELLAGERORT
    DWtartlag;

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTIKELLAGERORT_LISTE
    from ARTIKELLAGERORT
    DWtartlag
    and   FILIALNR = :recordp->FILIALNR;

	EXEC SQL DECLARE C0 CURSOR FOR
		SELECT
		ARTIKELLAGERORT_LISTE
	from ARTIKELLAGERORT;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       case cCRSART_STO_ArtikelNrFilialNr:
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
/*  FUNCTION: pxLagerortGetNext                                       */
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
int pxLagerortGetNext
(
    struct tARTIKELLAGERORT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_GetNext;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTIKELLAGERORT_ZEIGER(recordp);
          break;
       case cCRSART_STO_ArtikelNrFilialNr:
          EXEC SQL FETCH C2
          into ARTIKELLAGERORT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTIKELLAGERORT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxLagerortEndBrowse                                     */
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
int pxLagerortEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTIKELLAGERORT*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSART_STO_ArtikelNrFilialNr:
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
/*  FUNCTION: pxLagerortRead                                          */
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

int pxLagerortRead
(
    struct tARTIKELLAGERORT* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_Read;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    EXEC SQL SELECT
        ARTIKELLAGERORT_LISTE
     into ARTIKELLAGERORT_ZEIGER(recordp)
     from ARTIKELLAGERORT
     where PKtartlag;

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
/*  FUNCTION: pxLagerortReadLock                                      */
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
int pxLagerortReadLock
(
    struct tARTIKELLAGERORT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_ReadLock;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    EXEC SQL DECLARE TARTLAG_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTIKELLAGERORT_LISTE
    from ARTIKELLAGERORT
    where PKtartlag
    FOR UPDATE;
    EXEC SQL OPEN TARTLAG_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTLAG_U1
      into ARTIKELLAGERORT_ZEIGER(recordp)
      ;
    }


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
/*  FUNCTION: pxLagerortUpdate                                        */
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

int pxLagerortUpdate
(
    struct tARTIKELLAGERORT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_Update;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    EXEC SQL UPDATE
    ARTIKELLAGERORT
    SET
    ARTIKELLAGERORT_UPDATE(recordp)
    where current of TARTLAG_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTLAG_U1;
    }

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
/*  FUNCTION: pxLagerortInsert                                       */
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
int pxLagerortInsert
(
    struct tARTIKELLAGERORT* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_Insert;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    EXEC SQL INSERT INTO
    ARTIKELLAGERORT
    (ARTIKELLAGERORT_LISTE)
    VALUES ( ARTIKELLAGERORT_ZEIGER(recordp) );

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
/*  FUNCTION: pxLagerortDelete                                        */
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

int pxLagerortDelete
(
    struct tARTIKELLAGERORT* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLAGERORT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLAGERORT*10+F_Delete;
    recordp = (struct C_ARTIKELLAGERORT *) record;

    EXEC SQL DELETE FROM
    ARTIKELLAGERORT
    where PKtartlag;

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
