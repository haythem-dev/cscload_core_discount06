/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tartspecialcond.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtSpecialCondStartBrowse  declare and open Cursor
        pxArtSpecialCondGetNext      get next record
        pxArtSpecialCondEndBrowse    close cursor
        pxArtSpecialCondRead         get one record
        pxArtSpecialCondReadLock     get one record with lock
        pxArtSpecialCondInsert       Insert record
        pxArtSpecialCondUpdate       Update record
        pxArtSpecialCondDelete       Delete record


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
#include <tartspecialcond.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtSpecialCondStartBrowse                                   */
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
int pxArtSpecialCondStartBrowse
(
     struct tARTSPECIALCOND* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
#ifdef MCtartspecialcond
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_StartBrowse;
    recordp = (struct C_ARTSPECIALCOND *) record;

    if (!(sizeof(struct C_ARTSPECIALCOND) == sizeof(struct tARTSPECIALCOND)))
       return cDBXR_DEFINITION;


#ifdef MCtartspecialcond
    strcpy(matchcode,recordp->MCtartspecialcond);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTSPECIALCOND_LISTE
    from ARTSPECIALCOND
    DWtartspecialcond
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTSPECIALCOND_LISTE
    from ARTSPECIALCOND
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
/*  FUNCTION: pxArtSpecialCondGetNext                                       */
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
int pxArtSpecialCondGetNext
(
    struct tARTSPECIALCOND* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_GetNext;
    recordp = (struct C_ARTSPECIALCOND *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTSPECIALCOND_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTSPECIALCOND_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtSpecialCondEndBrowse                                     */
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
int pxArtSpecialCondEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTSPECIALCOND*10+F_EndBrowse;

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
/*  FUNCTION: pxArtSpecialCondRead                                          */
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

int pxArtSpecialCondRead
(
    struct tARTSPECIALCOND* record
#ifdef SKtartspecialcond
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_Read;
    recordp = (struct C_ARTSPECIALCOND *) record;

#ifdef SKtartspecialcond
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTSPECIALCOND_LISTE
     into ARTSPECIALCOND_ZEIGER(recordp)
     from ARTSPECIALCOND
     where SKtartspecialcond;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTSPECIALCOND_LISTE
     into ARTSPECIALCOND_ZEIGER(recordp)
     from ARTSPECIALCOND
     where PKtartspecialcond;

#ifdef SKtartspecialcond
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
/*  FUNCTION: pxArtSpecialCondReadLock                                      */
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
int pxArtSpecialCondReadLock
(
    struct tARTSPECIALCOND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_ReadLock;
    recordp = (struct C_ARTSPECIALCOND *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tartspecialcond_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTSPECIALCOND_LISTE
    from ARTSPECIALCOND
    where PKtartspecialcond
    FOR UPDATE;
    EXEC SQL OPEN tartspecialcond_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tartspecialcond_U1
      into ARTSPECIALCOND_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTSPECIALCOND_LISTE
    into ARTSPECIALCOND_ZEIGER(recordp)
    from ARTSPECIALCOND    HOLDLOCK
    where PKtartspecialcond;
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
/*  FUNCTION: pxArtSpecialCondUpdate                                        */
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

int pxArtSpecialCondUpdate
(
    struct tARTSPECIALCOND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_Update;
    recordp = (struct C_ARTSPECIALCOND *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTSPECIALCOND
    SET
    ARTSPECIALCOND_UPDATE(recordp)
    where current of tartspecialcond_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tartspecialcond_U1;
    }
#else

    EXEC SQL UPDATE
    ARTSPECIALCOND
    SET
    ARTSPECIALCOND_UPDATE(recordp)
    where PKtartspecialcond;
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
/*  FUNCTION: pxArtSpecialCondInsert                                       */
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
int pxArtSpecialCondInsert
(
    struct tARTSPECIALCOND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_Insert;
    recordp = (struct C_ARTSPECIALCOND *) record;

    EXEC SQL INSERT INTO
    ARTSPECIALCOND
    (ARTSPECIALCOND_LISTE)
    VALUES ( ARTSPECIALCOND_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTSPECIALCOND
    VALUES ( ARTSPECIALCOND_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtSpecialCondDelete                                        */
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

int pxArtSpecialCondDelete
(
    struct tARTSPECIALCOND* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTSPECIALCOND * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTSPECIALCOND*10+F_Delete;
    recordp = (struct C_ARTSPECIALCOND *) record;

    EXEC SQL DELETE FROM
    ARTSPECIALCOND
    where PKtartspecialcond;

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
