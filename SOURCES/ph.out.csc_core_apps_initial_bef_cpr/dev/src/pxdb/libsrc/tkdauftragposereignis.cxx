/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragposereignis.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderPosEventStartBrowse  declare and open Cursor
        pxOrderPosEventGetNext      get next record
        pxOrderPosEventEndBrowse    close cursor
        pxOrderPosEventRead         get one record
        pxOrderPosEventReadLock     get one record with lock
        pxOrderPosEventInsert       Insert record
        pxOrderPosEventUpdate       Update record
        pxOrderPosEventDelete       Delete record


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
#include <tkdauftragposereignis.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosEventStartBrowse                             */
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
int pxOrderPosEventStartBrowse
(
     struct tKDAUFTRAGPOSEREIGNIS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
#ifdef MCtkdauftragposereignis
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSEREIGNIS) == sizeof(struct tKDAUFTRAGPOSEREIGNIS)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragposereignis
    strcpy(matchcode,recordp->MCtkdauftragposereignis);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSEREIGNIS_LISTE
    from KDAUFTRAGPOSEREIGNIS
    DWtkdauftragposereignis
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSEREIGNIS_LISTE
    from KDAUFTRAGPOSEREIGNIS
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
/*  FUNCTION: pxOrderPosEventGetNext                                 */
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
int pxOrderPosEventGetNext
(
    struct tKDAUFTRAGPOSEREIGNIS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderPosEventEndBrowse                               */
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
int pxOrderPosEventEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderPosEventRead                                    */
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

int pxOrderPosEventRead
(
    struct tKDAUFTRAGPOSEREIGNIS* record
#ifdef SKtkdauftragposereignis
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;

#ifdef SKtkdauftragposereignis
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSEREIGNIS_LISTE
     into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp)
     from KDAUFTRAGPOSEREIGNIS
     where SKtkdauftragposereignis;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSEREIGNIS_LISTE
     into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp)
     from KDAUFTRAGPOSEREIGNIS
     where PKtkdauftragposereignis;

#ifdef SKtkdauftragposereignis
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
/*  FUNCTION: pxOrderPosEventReadLock                                */
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
int pxOrderPosEventReadLock
(
    struct tKDAUFTRAGPOSEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tKDAUFTRAGPOSEREIGNIS_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSEREIGNIS_LISTE
    from KDAUFTRAGPOSEREIGNIS
    where PKtkdauftragposereignis
    FOR UPDATE;
    EXEC SQL OPEN tKDAUFTRAGPOSEREIGNIS_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tKDAUFTRAGPOSEREIGNIS_U1
      into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSEREIGNIS_LISTE
    into KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp)
    from KDAUFTRAGPOSEREIGNIS    HOLDLOCK
    where PKtkdauftragposereignis;
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
/*  FUNCTION: pxOrderPosEventUpdate                                  */
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

int pxOrderPosEventUpdate
(
    struct tKDAUFTRAGPOSEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSEREIGNIS
    SET
    KDAUFTRAGPOSEREIGNIS_UPDATE(recordp)
    where current of tKDAUFTRAGPOSEREIGNIS_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tKDAUFTRAGPOSEREIGNIS_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSEREIGNIS
    SET
    KDAUFTRAGPOSEREIGNIS_UPDATE(recordp)
    where PKtkdauftragposereignis;
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
/*  FUNCTION: pxOrderPosEventInsert                                  */
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
int pxOrderPosEventInsert
(
    struct tKDAUFTRAGPOSEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSEREIGNIS
    (KDAUFTRAGPOSEREIGNIS_LISTE)
    VALUES ( KDAUFTRAGPOSEREIGNIS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    tKDAUFTRAGPOSEREIGNIS
    VALUES ( tKDAUFTRAGPOSEREIGNIS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderPosEventDelete                                  */
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

int pxOrderPosEventDelete
(
    struct tKDAUFTRAGPOSEREIGNIS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSEREIGNIS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSEREIGNIS*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSEREIGNIS *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSEREIGNIS
    where PKtkdauftragposereignis;

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
