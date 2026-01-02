/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttaxtab.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTaxTabStartBrowse  declare and open Cursor
        pxTaxTabGetNext      get next record
        pxTaxTabEndBrowse    close cursor
        pxTaxTabRead         get one record
        pxTaxTabReadLock     get one record with lock
        pxTaxTabInsert       Insert record
        pxTaxTabUpdate       Update record
        pxTaxTabDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include <ttaxtab.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaxTabStartBrowse                                   */
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
int pxTaxTabStartBrowse
(
     struct tTAXTAB* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_StartBrowse;
    recordp = (struct C_TAXTAB *) record;

    if (!(sizeof(struct C_TAXTAB) == sizeof(struct tTAXTAB)))
       return cDBXR_DEFINITION;



#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TAXTAB_LISTE
    from TAXTAB
    DWttaxtab
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TAXTAB_LISTE
    from TAXTAB
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
/*  FUNCTION: pxTaxTabGetNext                                       */
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
int pxTaxTabGetNext
(
    struct tTAXTAB* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB* recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_GetNext;
    recordp = (struct C_TAXTAB *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TAXTAB_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TAXTAB_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaxTabEndBrowse                                     */
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
int pxTaxTabEndBrowse
(
    int browseid
)
{
    functionnr = F_TAXTAB*10+F_EndBrowse;

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
/*  FUNCTION: pxTaxTabRead                                          */
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

int pxTaxTabRead
(
    struct tTAXTAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_Read;
    recordp = (struct C_TAXTAB *) record;


    EXEC SQL SELECT
        TAXTAB_LISTE
     into TAXTAB_ZEIGER(recordp)
     from TAXTAB
     where PKttaxtab;

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
/*  FUNCTION: pxTaxTabReadLock                                      */
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
int pxTaxTabReadLock
(
    struct tTAXTAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_ReadLock;
    recordp = (struct C_TAXTAB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TTAXTAB_U1 CURSOR WITH HOLD FOR
        SELECT
        TAXTAB_LISTE
    from TAXTAB
    where PKttaxtab
    FOR UPDATE;
    EXEC SQL OPEN TTAXTAB_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TTAXTAB_U1
      into TAXTAB_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TAXTAB_LISTE
    into TAXTAB_ZEIGER(recordp)
    from TAXTAB    HOLDLOCK
    where PKttaxtab;
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
/*  FUNCTION: pxTaxTabUpdate                                        */
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

int pxTaxTabUpdate
(
    struct tTAXTAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_Update;
    recordp = (struct C_TAXTAB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TAXTAB
    SET
    TAXTAB_UPDATE(recordp)
    where current of TTAXTAB_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TTAXTAB_U1;
    }
#else

    EXEC SQL UPDATE
    TAXTAB
    SET
    TAXTAB_UPDATE(recordp)
    where PKttaxtab;
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
/*  FUNCTION: pxTaxTabInsert                                       */
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
int pxTaxTabInsert
(
    struct tTAXTAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_Insert;
    recordp = (struct C_TAXTAB *) record;

    EXEC SQL INSERT INTO
    TAXTAB
    (TAXTAB_LISTE)
    VALUES ( TAXTAB_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TAXTAB
    VALUES ( TAXTAB_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTaxTabDelete                                        */
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

int pxTaxTabDelete
(
    struct tTAXTAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXTAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXTAB*10+F_Delete;
    recordp = (struct C_TAXTAB *) record;

    EXEC SQL DELETE FROM
    TAXTAB
    where PKttaxtab;

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
