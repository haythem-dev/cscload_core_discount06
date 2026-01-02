/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkundeausku.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustBaseInformationStartBrowse  declare and open Cursor
        pxCustBaseInformationGetNext      get next record
        pxCustBaseInformationEndBrowse    close cursor
        pxCustBaseInformationRead         get one record
        pxCustBaseInformationReadLock     get one record with lock
        pxCustBaseInformationInsert       Insert record
        pxCustBaseInformationUpdate       Update record
        pxCustBaseInformationDelete       Delete record


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
#include <tkundeausku.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustBaseInformationStartBrowse                                   */
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
int pxCustBaseInformationStartBrowse
(
     struct tKNDAUSKU* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
#ifdef MCtkundeausku
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_StartBrowse;
    recordp = (struct C_KNDAUSKU *) record;

    if (!(sizeof(struct C_KNDAUSKU) == sizeof(struct tKNDAUSKU)))
       return cDBXR_DEFINITION;


#ifdef MCtkundeausku
    strcpy(matchcode,recordp->MCtkundeausku);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KNDAUSKU_LISTE
    from KNDAUSKU
    DWtkundeausku
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KNDAUSKU_LISTE
    from KNDAUSKU
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
/*  FUNCTION: pxCustBaseInformationGetNext                                       */
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
int pxCustBaseInformationGetNext
(
    struct tKNDAUSKU* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_GetNext;
    recordp = (struct C_KNDAUSKU *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KNDAUSKU_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KNDAUSKU_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustBaseInformationEndBrowse                                     */
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
int pxCustBaseInformationEndBrowse
(
    int browseid
)
{
    functionnr = F_KNDAUSKU*10+F_EndBrowse;

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
/*  FUNCTION: pxCustBaseInformationRead                                          */
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

int pxCustBaseInformationRead
(
    struct tKNDAUSKU* record
#ifdef SKtkundeausku
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_Read;
    recordp = (struct C_KNDAUSKU *) record;

#ifdef SKtkundeausku
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KNDAUSKU_LISTE
     into KNDAUSKU_ZEIGER(recordp)
     from KNDAUSKU
     where SKtkundeausku;
     break;
    default:
#endif

    EXEC SQL SELECT
        KNDAUSKU_LISTE
     into KNDAUSKU_ZEIGER(recordp)
     from KNDAUSKU
     where PKtkundeausku;

#ifdef SKtkundeausku
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
/*  FUNCTION: pxCustBaseInformationReadLock                                      */
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
int pxCustBaseInformationReadLock
(
    struct tKNDAUSKU* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_ReadLock;
    recordp = (struct C_KNDAUSKU *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkundeausku_U1 CURSOR WITH HOLD FOR
        SELECT
        KNDAUSKU_LISTE
    from KNDAUSKU
    where PKtkundeausku
    FOR UPDATE;
    EXEC SQL OPEN tkundeausku_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkundeausku_U1
      into KNDAUSKU_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KNDAUSKU_LISTE
    into KNDAUSKU_ZEIGER(recordp)
    from KNDAUSKU    HOLDLOCK
    where PKtkundeausku;
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
/*  FUNCTION: pxCustBaseInformationUpdate                                        */
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

int pxCustBaseInformationUpdate
(
    struct tKNDAUSKU* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_Update;
    recordp = (struct C_KNDAUSKU *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KNDAUSKU
    SET
    KNDAUSKU_UPDATE(recordp)
    where current of tkundeausku_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkundeausku_U1;
    }
#else

    EXEC SQL UPDATE
    KNDAUSKU
    SET
    KNDAUSKU_UPDATE(recordp)
    where PKtkundeausku;
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
/*  FUNCTION: pxCustBaseInformationInsert                                       */
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
int pxCustBaseInformationInsert
(
    struct tKNDAUSKU* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_Insert;
    recordp = (struct C_KNDAUSKU *) record;

    EXEC SQL INSERT INTO
    KNDAUSKU
    (KNDAUSKU_LISTE)
    VALUES ( KNDAUSKU_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KNDAUSKU
    VALUES ( KNDAUSKU_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustBaseInformationDelete                                        */
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

int pxCustBaseInformationDelete
(
    struct tKNDAUSKU* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KNDAUSKU * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KNDAUSKU*10+F_Delete;
    recordp = (struct C_KNDAUSKU *) record;

    EXEC SQL DELETE FROM
    KNDAUSKU
    where PKtkundeausku;

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
