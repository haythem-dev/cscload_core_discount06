/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tartcompack.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtComPackStartBrowse  declare and open Cursor
        pxArtComPackGetNext      get next record
        pxArtComPackEndBrowse    close cursor
        pxArtComPackRead         get one record
        pxArtComPackReadLock     get one record with lock
        pxArtComPackInsert       Insert record
        pxArtComPackUpdate       Update record
        pxArtComPackDelete       Delete record


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
#include <tartcompack.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtComPackStartBrowse                                   */
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
int pxArtComPackStartBrowse
(
     struct tARTCOMPACK* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
#ifdef MCtartcompack
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_StartBrowse;
    recordp = (struct C_ARTCOMPACK *) record;

    if (!(sizeof(struct C_ARTCOMPACK) == sizeof(struct tARTCOMPACK)))
       return cDBXR_DEFINITION;


#ifdef MCtartcompack
    strcpy(matchcode,recordp->MCtartcompack);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTCOMPACK_LISTE
    from ARTCOMPACK
    DWtartcompack
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTCOMPACK_LISTE
    from ARTCOMPACK
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
/*  FUNCTION: pxArtComPackGetNext                                       */
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
int pxArtComPackGetNext
(
    struct tARTCOMPACK* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_GetNext;
    recordp = (struct C_ARTCOMPACK *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTCOMPACK_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTCOMPACK_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtComPackEndBrowse                                     */
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
int pxArtComPackEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTCOMPACK*10+F_EndBrowse;

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
/*  FUNCTION: pxArtComPackRead                                          */
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

int pxArtComPackRead
(
    struct tARTCOMPACK* record
#ifdef SKtartcompack
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_Read;
    recordp = (struct C_ARTCOMPACK *) record;

#ifdef SKtartcompack
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTCOMPACK_LISTE
     into ARTCOMPACK_ZEIGER(recordp)
     from ARTCOMPACK
     where SKtartcompack;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTCOMPACK_LISTE
     into ARTCOMPACK_ZEIGER(recordp)
     from ARTCOMPACK
     where PKtartcompack;

#ifdef SKtartcompack
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
/*  FUNCTION: pxArtComPackReadLock                                      */
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
int pxArtComPackReadLock
(
    struct tARTCOMPACK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_ReadLock;
    recordp = (struct C_ARTCOMPACK *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tartcompack_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTCOMPACK_LISTE
    from ARTCOMPACK
    where PKtartcompack
    FOR UPDATE;
    EXEC SQL OPEN tartcompack_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tartcompack_U1
      into ARTCOMPACK_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTCOMPACK_LISTE
    into ARTCOMPACK_ZEIGER(recordp)
    from ARTCOMPACK    HOLDLOCK
    where PKtartcompack;
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
/*  FUNCTION: pxArtComPackUpdate                                        */
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

int pxArtComPackUpdate
(
    struct tARTCOMPACK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_Update;
    recordp = (struct C_ARTCOMPACK *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTCOMPACK
    SET
    ARTCOMPACK_UPDATE(recordp)
    where current of tartcompack_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tartcompack_U1;
    }
#else

    EXEC SQL UPDATE
    ARTCOMPACK
    SET
    ARTCOMPACK_UPDATE(recordp)
    where PKtartcompack;
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
/*  FUNCTION: pxArtComPackInsert                                       */
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
int pxArtComPackInsert
(
    struct tARTCOMPACK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_Insert;
    recordp = (struct C_ARTCOMPACK *) record;

    EXEC SQL INSERT INTO
    ARTCOMPACK
    (ARTCOMPACK_LISTE)
    VALUES ( ARTCOMPACK_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTCOMPACK
    VALUES ( ARTCOMPACK_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtComPackDelete                                        */
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

int pxArtComPackDelete
(
    struct tARTCOMPACK* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTCOMPACK * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTCOMPACK*10+F_Delete;
    recordp = (struct C_ARTCOMPACK *) record;

    EXEC SQL DELETE FROM
    ARTCOMPACK
    where PKtartcompack;

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
