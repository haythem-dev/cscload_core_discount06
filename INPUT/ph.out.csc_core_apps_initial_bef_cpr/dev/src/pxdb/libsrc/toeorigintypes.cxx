/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: toeorigintypes.c (.cxx)

    Database functions




    FUNCTIONS:

        pxOeOriginTypesStartBrowse  declare and open Cursor
        pxOeOriginTypesGetNext      get next record
        pxOeOriginTypesEndBrowse    close cursor
        pxOeOriginTypesRead         get one record
        pxOeOriginTypesReadLock     get one record with lock
        pxOeOriginTypesInsert       Insert record
        pxOeOriginTypesUpdate       Update record
        pxOeOriginTypesDelete       Delete record


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
#include <toeorigintypes.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeOriginTypesStartBrowse                             */
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
int pxOeOriginTypesStartBrowse
(
     struct tOEORIGINTYPES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
#ifdef MCtoeorigintypes
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_StartBrowse;
    recordp = (struct C_OEORIGINTYPES *) record;

    if (!(sizeof(struct C_OEORIGINTYPES) == sizeof(struct tOEORIGINTYPES)))
       return cDBXR_DEFINITION;


#ifdef MCtoeorigintypes
    strcpy(matchcode,recordp->MCtoeorigintypes);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        OEORIGINTYPES_LISTE
    from OEORIGINTYPES
    DWtoeorigintypes
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        OEORIGINTYPES_LISTE
    from OEORIGINTYPES
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
/*  FUNCTION: pxOeOriginTypesGetNext                                 */
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
int pxOeOriginTypesGetNext
(
    struct tOEORIGINTYPES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_GetNext;
    recordp = (struct C_OEORIGINTYPES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into OEORIGINTYPES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into OEORIGINTYPES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOeOriginTypesEndBrowse                               */
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
int pxOeOriginTypesEndBrowse
(
    int browseid
)
{
    functionnr = F_OEORIGINTYPES*10+F_EndBrowse;

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
/*  FUNCTION: pxOeOriginTypesRead                                    */
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

int pxOeOriginTypesRead
(
    struct tOEORIGINTYPES* record
#ifdef SKtoeorigintypes
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_Read;
    recordp = (struct C_OEORIGINTYPES *) record;

#ifdef SKtoeorigintypes
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        OEORIGINTYPES_LISTE
     into OEORIGINTYPES_ZEIGER(recordp)
     from OEORIGINTYPES
     where SKtoeorigintypes;
     break;
    default:
#endif

    EXEC SQL SELECT
        OEORIGINTYPES_LISTE
     into OEORIGINTYPES_ZEIGER(recordp)
     from OEORIGINTYPES
     where PKtoeorigintypes;

#ifdef SKtoeorigintypes
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
/*  FUNCTION: pxOeOriginTypesReadLock                                */
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
int pxOeOriginTypesReadLock
(
    struct tOEORIGINTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_ReadLock;
    recordp = (struct C_OEORIGINTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE toeorigintypes_U1 CURSOR WITH HOLD FOR
        SELECT
        OEORIGINTYPES_LISTE
    from OEORIGINTYPES
    where PKtoeorigintypes
    FOR UPDATE;
    EXEC SQL OPEN toeorigintypes_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH toeorigintypes_U1
      into OEORIGINTYPES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         OEORIGINTYPES_LISTE
    into OEORIGINTYPES_ZEIGER(recordp)
    from OEORIGINTYPES    HOLDLOCK
    where PKtoeorigintypes;
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
/*  FUNCTION: pxOeOriginTypesUpdate                                  */
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

int pxOeOriginTypesUpdate
(
    struct tOEORIGINTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_Update;
    recordp = (struct C_OEORIGINTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    OEORIGINTYPES
    SET
    OEORIGINTYPES_UPDATE(recordp)
    where current of toeorigintypes_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE toeorigintypes_U1;
    }
#else

    EXEC SQL UPDATE
    OEORIGINTYPES
    SET
    OEORIGINTYPES_UPDATE(recordp)
    where PKtoeorigintypes;
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
/*  FUNCTION: pxOeOriginTypesInsert                                  */
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
int pxOeOriginTypesInsert
(
    struct tOEORIGINTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_Insert;
    recordp = (struct C_OEORIGINTYPES *) record;

    EXEC SQL INSERT INTO
    OEORIGINTYPES
    (OEORIGINTYPES_LISTE)
    VALUES ( OEORIGINTYPES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    OEORIGINTYPES
    VALUES ( OEORIGINTYPES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOeOriginTypesDelete                                  */
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

int pxOeOriginTypesDelete
(
    struct tOEORIGINTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_OEORIGINTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_OEORIGINTYPES*10+F_Delete;
    recordp = (struct C_OEORIGINTYPES *) record;

    EXEC SQL DELETE FROM
    OEORIGINTYPES
    where PKtoeorigintypes;

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
