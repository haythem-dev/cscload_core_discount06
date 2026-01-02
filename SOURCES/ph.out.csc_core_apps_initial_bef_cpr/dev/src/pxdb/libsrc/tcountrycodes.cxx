/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcountrycodes.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCountryCodesStartBrowse  declare and open Cursor
        pxCountryCodesGetNext      get next record
        pxCountryCodesEndBrowse    close cursor
        pxCountryCodesRead         get one record
        pxCountryCodesReadLock     get one record with lock
        pxCountryCodesInsert       Insert record
        pxCountryCodesUpdate       Update record
        pxCountryCodesDelete       Delete record


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
#include <tcountrycodes.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCountryCodesStartBrowse                              */
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
int pxCountryCodesStartBrowse
(
     struct tCOUNTRYCODES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
#ifdef MCtcountrycodes
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_StartBrowse;
    recordp = (struct C_COUNTRYCODES *) record;

    if (!(sizeof(struct C_COUNTRYCODES) == sizeof(struct tCOUNTRYCODES)))
       return cDBXR_DEFINITION;


#ifdef MCtcountrycodes
    strcpy(matchcode,recordp->MCtcountrycodes);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        COUNTRYCODES_LISTE
    from COUNTRYCODES
    DWtcountrycodes
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        COUNTRYCODES_LISTE
    from COUNTRYCODES
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        COUNTRYCODES_LISTE
    from COUNTRYCODES
    where BRANCHNO      = :recordp->BRANCHNO
    and   XMLCODE       = :recordp->XMLCODE
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
       case cCRSCOUNTRYCODES_XMLCODE:
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
/*  FUNCTION: pxCountryCodesGetNext                                       */
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
int pxCountryCodesGetNext
(
    struct tCOUNTRYCODES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_GetNext;
    recordp = (struct C_COUNTRYCODES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into COUNTRYCODES_ZEIGER(recordp);
          break;
       case cCRSCOUNTRYCODES_XMLCODE:
          EXEC SQL FETCH C2
          into COUNTRYCODES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into COUNTRYCODES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCountryCodesEndBrowse                                     */
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
int pxCountryCodesEndBrowse
(
    int browseid
)
{
    functionnr = F_COUNTRYCODES*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSCOUNTRYCODES_XMLCODE:
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
/*  FUNCTION: pxCountryCodesRead                                          */
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

int pxCountryCodesRead
(
    struct tCOUNTRYCODES* record
#ifdef SKtcountrycodes
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_Read;
    recordp = (struct C_COUNTRYCODES *) record;

#ifdef SKtcountrycodes
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        COUNTRYCODES_LISTE
     into COUNTRYCODES_ZEIGER(recordp)
     from COUNTRYCODES
     where SKtcountrycodes;
     break;
    default:
#endif

    EXEC SQL SELECT
        COUNTRYCODES_LISTE
     into COUNTRYCODES_ZEIGER(recordp)
     from COUNTRYCODES
     where PKtcountrycodes;

#ifdef SKtcountrycodes
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
/*  FUNCTION: pxCountryCodesReadLock                                      */
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
int pxCountryCodesReadLock
(
    struct tCOUNTRYCODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_ReadLock;
    recordp = (struct C_COUNTRYCODES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcountrycodes_U1 CURSOR WITH HOLD FOR
        SELECT
        COUNTRYCODES_LISTE
    from COUNTRYCODES
    where PKtcountrycodes
    FOR UPDATE;
    EXEC SQL OPEN tcountrycodes_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcountrycodes_U1
      into COUNTRYCODES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         COUNTRYCODES_LISTE
    into COUNTRYCODES_ZEIGER(recordp)
    from COUNTRYCODES    HOLDLOCK
    where PKtcountrycodes;
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
/*  FUNCTION: pxCountryCodesUpdate                                        */
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

int pxCountryCodesUpdate
(
    struct tCOUNTRYCODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_Update;
    recordp = (struct C_COUNTRYCODES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    COUNTRYCODES
    SET
    COUNTRYCODES_UPDATE(recordp)
    where current of tcountrycodes_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcountrycodes_U1;
    }
#else

    EXEC SQL UPDATE
    COUNTRYCODES
    SET
    COUNTRYCODES_UPDATE(recordp)
    where PKtcountrycodes;
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
/*  FUNCTION: pxCountryCodesInsert                                       */
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
int pxCountryCodesInsert
(
    struct tCOUNTRYCODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_Insert;
    recordp = (struct C_COUNTRYCODES *) record;

    EXEC SQL INSERT INTO
    COUNTRYCODES
    (COUNTRYCODES_LISTE)
    VALUES ( COUNTRYCODES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    COUNTRYCODES
    VALUES ( COUNTRYCODES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCountryCodesDelete                                        */
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

int pxCountryCodesDelete
(
    struct tCOUNTRYCODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_COUNTRYCODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_COUNTRYCODES*10+F_Delete;
    recordp = (struct C_COUNTRYCODES *) record;

    EXEC SQL DELETE FROM
    COUNTRYCODES
    where PKtcountrycodes;

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
