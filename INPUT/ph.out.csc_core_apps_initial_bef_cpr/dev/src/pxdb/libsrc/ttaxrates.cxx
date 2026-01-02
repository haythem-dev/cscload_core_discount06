/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttaxrates.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTaxRatesStartBrowse  declare and open Cursor
        pxTaxRatesGetNext      get next record
        pxTaxRatesEndBrowse    close cursor
        pxTaxRatesRead         get one record
        pxTaxRatesReadLock     get one record with lock
        pxTaxRatesInsert       Insert record
        pxTaxRatesUpdate       Update record
        pxTaxRatesDelete       Delete record


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
#include <ttaxrates.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaxRatesStartBrowse                                   */
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
int pxTaxRatesStartBrowse
(
     struct tTAXRATES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCttaxrates
    struct C_TAXRATES * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_StartBrowse;
#ifdef MCttaxrates
    recordp = (struct C_TAXRATES *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_TAXRATES) == sizeof(struct tTAXRATES)))
       return cDBXR_DEFINITION;


#ifdef MCttaxrates
    strcpy(matchcode,recordp->MCttaxrates);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TAXRATES_LISTE
    from TAXRATES
    DWttaxrates
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TAXRATES_LISTE
    from TAXRATES
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
/*  FUNCTION: pxTaxRatesGetNext                                       */
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
int pxTaxRatesGetNext
(
    struct tTAXRATES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_GetNext;
    recordp = (struct C_TAXRATES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TAXRATES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into TAXRATES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTaxRatesEndBrowse                                     */
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
int pxTaxRatesEndBrowse
(
    int browseid
)
{
    functionnr = F_TAXRATES*10+F_EndBrowse;

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
/*  FUNCTION: pxTaxRatesRead                                          */
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

int pxTaxRatesRead
(
    struct tTAXRATES* record
#ifdef SKttaxrates
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_Read;
    recordp = (struct C_TAXRATES *) record;

#ifdef SKttaxrates
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TAXRATES_LISTE
     into TAXRATES_ZEIGER(recordp)
     from TAXRATES
     where SKttaxrates;
     break;
    default:
#endif

    EXEC SQL SELECT
        TAXRATES_LISTE
     into TAXRATES_ZEIGER(recordp)
     from TAXRATES
     where PKttaxrates;

#ifdef SKttaxrates
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
/*  FUNCTION: pxTaxRatesReadLock                                      */
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
int pxTaxRatesReadLock
(
    struct tTAXRATES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_ReadLock;
    recordp = (struct C_TAXRATES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttaxrates_U1 CURSOR WITH HOLD FOR
        SELECT
        TAXRATES_LISTE
    from TAXRATES
    where PKttaxrates
    FOR UPDATE;
    EXEC SQL OPEN ttaxrates_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttaxrates_U1
      into TAXRATES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TAXRATES_LISTE
    into TAXRATES_ZEIGER(recordp)
    from TAXRATES    HOLDLOCK
    where PKttaxrates;
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
/*  FUNCTION: pxTaxRatesUpdate                                        */
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

int pxTaxRatesUpdate
(
    struct tTAXRATES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_Update;
    recordp = (struct C_TAXRATES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TAXRATES
    SET
    TAXRATES_UPDATE(recordp)
    where current of ttaxrates_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttaxrates_U1;
    }
#else

    EXEC SQL UPDATE
    TAXRATES
    SET
    TAXRATES_UPDATE(recordp)
    where PKttaxrates;
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
/*  FUNCTION: pxTaxRatesInsert                                       */
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
int pxTaxRatesInsert
(
    struct tTAXRATES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_Insert;
    recordp = (struct C_TAXRATES *) record;

    EXEC SQL INSERT INTO
    TAXRATES
    (TAXRATES_LISTE)
    VALUES ( TAXRATES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TAXRATES
    VALUES ( TAXRATES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTaxRatesDelete                                        */
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

int pxTaxRatesDelete
(
    struct tTAXRATES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TAXRATES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TAXRATES*10+F_Delete;
    recordp = (struct C_TAXRATES *) record;

    EXEC SQL DELETE FROM
    TAXRATES
    where PKttaxrates;

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
