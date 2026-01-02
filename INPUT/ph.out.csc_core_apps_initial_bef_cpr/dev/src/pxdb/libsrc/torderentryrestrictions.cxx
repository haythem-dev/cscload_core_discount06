/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: torderentryrestrictions.c (.sqc)

    Database functions





    FUNCTIONS:

        pxOeRestrictionsStartBrowse  declare and open Cursor
        pxOeRestrictionsGetNext      get next record
        pxOeRestrictionsEndBrowse    close cursor
        pxOeRestrictionsRead         get one record
        pxOeRestrictionsReadLock     get one record with lock
        pxOeRestrictionsInsert       Insert record
        pxOeRestrictionsUpdate       Update record
        pxOeRestrictionsDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <torderentryrestrictions.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeRestrictionsStartBrowse                            */
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
int pxOeRestrictionsStartBrowse
(
     struct tORDERENTRYRESTRICTIONS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
#ifdef MCtorderentryrestrictions
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_StartBrowse;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;

    if (!(sizeof(struct C_ORDERENTRYRESTRICTIONS) == sizeof(struct tORDERENTRYRESTRICTIONS)))
       return cDBXR_DEFINITION;


#ifdef MCtorderentryrestrictions
    strcpy(matchcode,recordp->MCtorderentryrestrictions);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ORDERENTRYRESTRICTIONS_LISTE
    from ORDERENTRYRESTRICTIONS
    DWtorderentryrestrictions
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ORDERENTRYRESTRICTIONS_LISTE
    from ORDERENTRYRESTRICTIONS
    where BRANCHNO          = :recordp->BRANCHNO
    and  RESTRICTIONTYPE    = :recordp->RESTRICTIONTYPE
    and  RESTRICTIONVALUE   = :recordp->RESTRICTIONVALUE
    and  ORIGINTYPE         = :recordp->ORIGINTYPE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ORDERENTRYRESTRICTIONS_LISTE
    from ORDERENTRYRESTRICTIONS
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
       case cCRSOERESTRICTIONS_OVERALL:
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
/*  FUNCTION: pxOeRestrictionsGetNext                                */
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
int pxOeRestrictionsGetNext
(
    struct tORDERENTRYRESTRICTIONS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_GetNext;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ORDERENTRYRESTRICTIONS_ZEIGER(recordp);
          break;
       case cCRSOERESTRICTIONS_OVERALL:
          EXEC SQL FETCH C2
          into ORDERENTRYRESTRICTIONS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ORDERENTRYRESTRICTIONS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeRestrictionsEndBrowse                              */
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
int pxOeRestrictionsEndBrowse
(
    int browseid
)
{
    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSOERESTRICTIONS_OVERALL:
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
/*  FUNCTION: pxOeRestrictionsRead                                   */
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

int pxOeRestrictionsRead
(
    struct tORDERENTRYRESTRICTIONS* record
#ifdef SKtorderentryrestrictions
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_Read;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;

#ifdef SKtorderentryrestrictions
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ORDERENTRYRESTRICTIONS_LISTE
     into ORDERENTRYRESTRICTIONS_ZEIGER(recordp)
     from ORDERENTRYRESTRICTIONS
     where SKtorderentryrestrictions;
     break;
    default:
#endif

    EXEC SQL SELECT
        ORDERENTRYRESTRICTIONS_LISTE
     into ORDERENTRYRESTRICTIONS_ZEIGER(recordp)
     from ORDERENTRYRESTRICTIONS
     where PKtorderentryrestrictions;

#ifdef SKtorderentryrestrictions
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
/*  FUNCTION: pxOeRestrictionsReadLock                               */
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
int pxOeRestrictionsReadLock
(
    struct tORDERENTRYRESTRICTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_ReadLock;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE torderentryrestrictions_U1 CURSOR WITH HOLD FOR
        SELECT
        ORDERENTRYRESTRICTIONS_LISTE
    from ORDERENTRYRESTRICTIONS
    where PKtorderentryrestrictions
    FOR UPDATE;
    EXEC SQL OPEN torderentryrestrictions_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH torderentryrestrictions_U1
      into ORDERENTRYRESTRICTIONS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ORDERENTRYRESTRICTIONS_LISTE
    into ORDERENTRYRESTRICTIONS_ZEIGER(recordp)
    from ORDERENTRYRESTRICTIONS    HOLDLOCK
    where PKtorderentryrestrictions;
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
/*  FUNCTION: pxOeRestrictionsUpdate                                 */
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

int pxOeRestrictionsUpdate
(
    struct tORDERENTRYRESTRICTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_Update;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ORDERENTRYRESTRICTIONS
    SET
    ORDERENTRYRESTRICTIONS_UPDATE(recordp)
    where current of torderentryrestrictions_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE torderentryrestrictions_U1;
    }
#else

    EXEC SQL UPDATE
    ORDERENTRYRESTRICTIONS
    SET
    ORDERENTRYRESTRICTIONS_UPDATE(recordp)
    where PKtorderentryrestrictions;
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
/*  FUNCTION: pxOeRestrictionsInsert                                 */
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
int pxOeRestrictionsInsert
(
    struct tORDERENTRYRESTRICTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_Insert;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;

    EXEC SQL INSERT INTO
    ORDERENTRYRESTRICTIONS
    (ORDERENTRYRESTRICTIONS_LISTE)
    VALUES ( ORDERENTRYRESTRICTIONS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ORDERENTRYRESTRICTIONS
    VALUES ( ORDERENTRYRESTRICTIONS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOeRestrictionsDelete                                 */
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

int pxOeRestrictionsDelete
(
    struct tORDERENTRYRESTRICTIONS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERENTRYRESTRICTIONS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERENTRYRESTRICTIONS*10+F_Delete;
    recordp = (struct C_ORDERENTRYRESTRICTIONS *) record;

    EXEC SQL DELETE FROM
    ORDERENTRYRESTRICTIONS
    where PKtorderentryrestrictions;

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
