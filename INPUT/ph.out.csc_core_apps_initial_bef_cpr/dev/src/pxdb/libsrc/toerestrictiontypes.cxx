/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: toerestrictiontypes.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOeRestrictionTypesStartBrowse  declare and open Cursor
        pxOeRestrictionTypesGetNext      get next record
        pxOeRestrictionTypesEndBrowse    close cursor
        pxOeRestrictionTypesRead         get one record
        pxOeRestrictionTypesReadLock     get one record with lock
        pxOeRestrictionTypesInsert       Insert record
        pxOeRestrictionTypesUpdate       Update record
        pxOeRestrictionTypesDelete       Delete record


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
#include <toerestrictiontypes.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeRestrictionTypesStartBrowse                                   */
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
int pxOeRestrictionTypesStartBrowse
(
     struct tOERESTRICTIONTYPES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
#ifdef MCtoerestrictiontypes
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_StartBrowse;
    recordp = (struct C_OERESTRICTIONTYPES *) record;

    if (!(sizeof(struct C_OERESTRICTIONTYPES) == sizeof(struct tOERESTRICTIONTYPES)))
       return cDBXR_DEFINITION;


#ifdef MCtoerestrictiontypes
    strcpy(matchcode,recordp->MCtoerestrictiontypes);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        OERESTRICTIONTYPES_LISTE
    from OERESTRICTIONTYPES
    DWtoerestrictiontypes
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        OERESTRICTIONTYPES_LISTE
    from OERESTRICTIONTYPES
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
/*  FUNCTION: pxOeRestrictionTypesGetNext                                       */
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
int pxOeRestrictionTypesGetNext
(
    struct tOERESTRICTIONTYPES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_GetNext;
    recordp = (struct C_OERESTRICTIONTYPES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into OERESTRICTIONTYPES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into OERESTRICTIONTYPES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeRestrictionTypesEndBrowse                                     */
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
int pxOeRestrictionTypesEndBrowse
(
    int browseid
)
{
    functionnr = F_OERESTRICTIONTYPES*10+F_EndBrowse;

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
/*  FUNCTION: pxOeRestrictionTypesRead                                          */
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

int pxOeRestrictionTypesRead
(
    struct tOERESTRICTIONTYPES* record
#ifdef SKtoerestrictiontypes
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_Read;
    recordp = (struct C_OERESTRICTIONTYPES *) record;

#ifdef SKtoerestrictiontypes
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        OERESTRICTIONTYPES_LISTE
     into OERESTRICTIONTYPES_ZEIGER(recordp)
     from OERESTRICTIONTYPES
     where SKtoerestrictiontypes;
     break;
    default:
#endif

    EXEC SQL SELECT
        OERESTRICTIONTYPES_LISTE
     into OERESTRICTIONTYPES_ZEIGER(recordp)
     from OERESTRICTIONTYPES
     where PKtoerestrictiontypes;

#ifdef SKtoerestrictiontypes
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
/*  FUNCTION: pxOeRestrictionTypesReadLock                                      */
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
int pxOeRestrictionTypesReadLock
(
    struct tOERESTRICTIONTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_ReadLock;
    recordp = (struct C_OERESTRICTIONTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE toerestrictiontypes_U1 CURSOR WITH HOLD FOR
        SELECT
        OERESTRICTIONTYPES_LISTE
    from OERESTRICTIONTYPES
    where PKtoerestrictiontypes
    FOR UPDATE;
    EXEC SQL OPEN toerestrictiontypes_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH toerestrictiontypes_U1
      into OERESTRICTIONTYPES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         OERESTRICTIONTYPES_LISTE
    into OERESTRICTIONTYPES_ZEIGER(recordp)
    from OERESTRICTIONTYPES    HOLDLOCK
    where PKtoerestrictiontypes;
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
/*  FUNCTION: pxOeRestrictionTypesUpdate                                        */
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

int pxOeRestrictionTypesUpdate
(
    struct tOERESTRICTIONTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_Update;
    recordp = (struct C_OERESTRICTIONTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    OERESTRICTIONTYPES
    SET
    OERESTRICTIONTYPES_UPDATE(recordp)
    where current of toerestrictiontypes_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE toerestrictiontypes_U1;
    }
#else

    EXEC SQL UPDATE
    OERESTRICTIONTYPES
    SET
    OERESTRICTIONTYPES_UPDATE(recordp)
    where PKtoerestrictiontypes;
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
/*  FUNCTION: pxOeRestrictionTypesInsert                                       */
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
int pxOeRestrictionTypesInsert
(
    struct tOERESTRICTIONTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_Insert;
    recordp = (struct C_OERESTRICTIONTYPES *) record;

    EXEC SQL INSERT INTO
    OERESTRICTIONTYPES
    (OERESTRICTIONTYPES_LISTE)
    VALUES ( OERESTRICTIONTYPES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    OERESTRICTIONTYPES
    VALUES ( OERESTRICTIONTYPES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOeRestrictionTypesDelete                                        */
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

int pxOeRestrictionTypesDelete
(
    struct tOERESTRICTIONTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OERESTRICTIONTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OERESTRICTIONTYPES*10+F_Delete;
    recordp = (struct C_OERESTRICTIONTYPES *) record;

    EXEC SQL DELETE FROM
    OERESTRICTIONTYPES
    where PKtoerestrictiontypes;

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
