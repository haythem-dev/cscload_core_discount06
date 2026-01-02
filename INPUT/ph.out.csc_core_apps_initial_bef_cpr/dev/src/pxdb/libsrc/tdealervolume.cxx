/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdealervolume.c (.sqc)

    Database functions




    FUNCTIONS:

        pxDealerVolumeStartBrowse  declare and open Cursor
        pxDealerVolumeGetNext      get next record
        pxDealerVolumeEndBrowse    close cursor
        pxDealerVolumeRead         get one record
        pxDealerVolumeReadLock     get one record with lock
        pxDealerVolumeInsert       Insert record
        pxDealerVolumeUpdate       Update record
        pxDealerVolumeDelete       Delete record


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
#include <tdealervolume.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDealerVolumeStartBrowse                                   */
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
int pxDealerVolumeStartBrowse
(
     struct tDEALERVOLUME* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
#ifdef MCtdealervolume
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_StartBrowse;
    recordp = (struct C_DEALERVOLUME *) record;

    if (!(sizeof(struct C_DEALERVOLUME) == sizeof(struct tDEALERVOLUME)))
       return cDBXR_DEFINITION;


#ifdef MCtdealervolume
    strcpy(matchcode,recordp->MCtdealervolume);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DEALERVOLUME_LISTE
    from DEALERVOLUME
    DWtdealervolume
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DEALERVOLUME_LISTE
    from DEALERVOLUME
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
/*  FUNCTION: pxDealerVolumeGetNext                                       */
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
int pxDealerVolumeGetNext
(
    struct tDEALERVOLUME* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_GetNext;
    recordp = (struct C_DEALERVOLUME *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DEALERVOLUME_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DEALERVOLUME_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDealerVolumeEndBrowse                                     */
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
int pxDealerVolumeEndBrowse
(
    int browseid
)
{
    functionnr = F_DEALERVOLUME*10+F_EndBrowse;

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
/*  FUNCTION: pxDealerVolumeRead                                          */
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

int pxDealerVolumeRead
(
    struct tDEALERVOLUME* record
#ifdef SKtdealervolume
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_Read;
    recordp = (struct C_DEALERVOLUME *) record;

#ifdef SKtdealervolume
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DEALERVOLUME_LISTE
     into DEALERVOLUME_ZEIGER(recordp)
     from DEALERVOLUME
     where SKtdealervolume;
     break;
    default:
#endif

    EXEC SQL SELECT
        DEALERVOLUME_LISTE
     into DEALERVOLUME_ZEIGER(recordp)
     from DEALERVOLUME
     where PKtdealervolume;

#ifdef SKtdealervolume
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
/*  FUNCTION: pxDealerVolumeReadLock                                      */
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
int pxDealerVolumeReadLock
(
    struct tDEALERVOLUME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_ReadLock;
    recordp = (struct C_DEALERVOLUME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdealervolume_U1 CURSOR WITH HOLD FOR
        SELECT
        DEALERVOLUME_LISTE
    from DEALERVOLUME
    where PKtdealervolume
    FOR UPDATE;
    EXEC SQL OPEN tdealervolume_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdealervolume_U1
      into DEALERVOLUME_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DEALERVOLUME_LISTE
    into DEALERVOLUME_ZEIGER(recordp)
    from DEALERVOLUME    HOLDLOCK
    where PKtdealervolume;
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
/*  FUNCTION: pxDealerVolumeUpdate                                        */
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

int pxDealerVolumeUpdate
(
    struct tDEALERVOLUME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_Update;
    recordp = (struct C_DEALERVOLUME *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DEALERVOLUME
    SET
    DEALERVOLUME_UPDATE(recordp)
    where current of tdealervolume_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdealervolume_U1;
    }
#else

    EXEC SQL UPDATE
    DEALERVOLUME
    SET
    DEALERVOLUME_UPDATE(recordp)
    where PKtdealervolume;
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
/*  FUNCTION: pxDealerVolumeInsert                                       */
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
int pxDealerVolumeInsert
(
    struct tDEALERVOLUME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_Insert;
    recordp = (struct C_DEALERVOLUME *) record;

    EXEC SQL INSERT INTO
    DEALERVOLUME
    (DEALERVOLUME_LISTE)
    VALUES ( DEALERVOLUME_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DEALERVOLUME
    VALUES ( DEALERVOLUME_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxDealerVolumeDelete                                        */
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

int pxDealerVolumeDelete
(
    struct tDEALERVOLUME* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DEALERVOLUME * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DEALERVOLUME*10+F_Delete;
    recordp = (struct C_DEALERVOLUME *) record;

    EXEC SQL DELETE FROM
    DEALERVOLUME
    where PKtdealervolume;

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
