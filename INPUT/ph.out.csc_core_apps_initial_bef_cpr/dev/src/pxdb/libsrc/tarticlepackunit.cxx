/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticlepackunit.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArtPackUnitStartBrowse  declare and open Cursor
        pxArtPackUnitGetNext      get next record
        pxArtPackUnitEndBrowse    close cursor
        pxArtPackUnitRead         get one record
        pxArtPackUnitReadLock     get one record with lock
        pxArtPackUnitInsert       Insert record
        pxArtPackUnitUpdate       Update record
        pxArtPackUnitDelete       Delete record


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
#include <tarticlepackunit.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtPackUnitStartBrowse                                   */
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
int pxArtPackUnitStartBrowse
(
     struct tARTICLEPACKUNIT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
#ifdef MCtarticlepackunit
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_StartBrowse;
    recordp = (struct C_ARTICLEPACKUNIT *) record;

    if (!(sizeof(struct C_ARTICLEPACKUNIT) == sizeof(struct tARTICLEPACKUNIT)))
       return cDBXR_DEFINITION;


#ifdef MCtarticlepackunit
    strcpy(matchcode,recordp->MCtarticlepackunit);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLEPACKUNIT_LISTE
    from ARTICLEPACKUNIT
    DWtarticlepackunit
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLEPACKUNIT_LISTE
    from ARTICLEPACKUNIT
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
/*  FUNCTION: pxArtPackUnitGetNext                                       */
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
int pxArtPackUnitGetNext
(
    struct tARTICLEPACKUNIT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_GetNext;
    recordp = (struct C_ARTICLEPACKUNIT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLEPACKUNIT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLEPACKUNIT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArtPackUnitEndBrowse                                     */
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
int pxArtPackUnitEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLEPACKUNIT*10+F_EndBrowse;

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
/*  FUNCTION: pxArtPackUnitRead                                          */
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

int pxArtPackUnitRead
(
    struct tARTICLEPACKUNIT* record
#ifdef SKtarticlepackunit
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_Read;
    recordp = (struct C_ARTICLEPACKUNIT *) record;

#ifdef SKtarticlepackunit
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLEPACKUNIT_LISTE
     into ARTICLEPACKUNIT_ZEIGER(recordp)
     from ARTICLEPACKUNIT
     where SKtarticlepackunit;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLEPACKUNIT_LISTE
     into ARTICLEPACKUNIT_ZEIGER(recordp)
     from ARTICLEPACKUNIT
     where PKtarticlepackunit;

#ifdef SKtarticlepackunit
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
/*  FUNCTION: pxArtPackUnitReadLock                                      */
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
int pxArtPackUnitReadLock
(
    struct tARTICLEPACKUNIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_ReadLock;
    recordp = (struct C_ARTICLEPACKUNIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tarticlepackunit_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLEPACKUNIT_LISTE
    from ARTICLEPACKUNIT
    where PKtarticlepackunit
    FOR UPDATE;
    EXEC SQL OPEN tarticlepackunit_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticlepackunit_U1
      into ARTICLEPACKUNIT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLEPACKUNIT_LISTE
    into ARTICLEPACKUNIT_ZEIGER(recordp)
    from ARTICLEPACKUNIT    HOLDLOCK
    where PKtarticlepackunit;
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
/*  FUNCTION: pxArtPackUnitUpdate                                        */
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

int pxArtPackUnitUpdate
(
    struct tARTICLEPACKUNIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_Update;
    recordp = (struct C_ARTICLEPACKUNIT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLEPACKUNIT
    SET
    ARTICLEPACKUNIT_UPDATE(recordp)
    where current of tarticlepackunit_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticlepackunit_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLEPACKUNIT
    SET
    ARTICLEPACKUNIT_UPDATE(recordp)
    where PKtarticlepackunit;
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
/*  FUNCTION: pxArtPackUnitInsert                                       */
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
int pxArtPackUnitInsert
(
    struct tARTICLEPACKUNIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_Insert;
    recordp = (struct C_ARTICLEPACKUNIT *) record;

    EXEC SQL INSERT INTO
    ARTICLEPACKUNIT
    (ARTICLEPACKUNIT_LISTE)
    VALUES ( ARTICLEPACKUNIT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLEPACKUNIT
    VALUES ( ARTICLEPACKUNIT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArtPackUnitDelete                                        */
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

int pxArtPackUnitDelete
(
    struct tARTICLEPACKUNIT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLEPACKUNIT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLEPACKUNIT*10+F_Delete;
    recordp = (struct C_ARTICLEPACKUNIT *) record;

    EXEC SQL DELETE FROM
    ARTICLEPACKUNIT
    where PKtarticlepackunit;

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
