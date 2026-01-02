/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragwerte.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderValuesStartBrowse  declare and open Cursor
        pxOrderValuesGetNext      get next record
        pxOrderValuesEndBrowse    close cursor
        pxOrderValuesRead         get one record
        pxOrderValuesReadLock     get one record with lock
        pxOrderValuesInsert       Insert record
        pxOrderValuesUpdate       Update record
        pxOrderValuesDelete       Delete record


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
#include <tkdauftragwerte.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderValuesStartBrowse                                   */
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
int pxOrderValuesStartBrowse
(
     struct tKDAUFTRAGWERTE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
#ifdef MCtkdauftragwerte
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGWERTE *) record;

    if (!(sizeof(struct C_KDAUFTRAGWERTE) == sizeof(struct tKDAUFTRAGWERTE)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragwerte
    strcpy(matchcode,recordp->MCtkdauftragwerte);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGWERTE_LISTE
    from KDAUFTRAGWERTE
    DWtkdauftragwerte
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGWERTE_LISTE
    from KDAUFTRAGWERTE
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
/*  FUNCTION: pxOrderValuesGetNext                                       */
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
int pxOrderValuesGetNext
(
    struct tKDAUFTRAGWERTE* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGWERTE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGWERTE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGWERTE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderValuesEndBrowse                                     */
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
int pxOrderValuesEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGWERTE*10+F_EndBrowse;

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
/*  FUNCTION: pxOrderValuesRead                                          */
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

int pxOrderValuesRead
(
    struct tKDAUFTRAGWERTE* record
#ifdef SKtkdauftragwerte
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_Read;
    recordp = (struct C_KDAUFTRAGWERTE *) record;

#ifdef SKtkdauftragwerte
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGWERTE_LISTE
     into KDAUFTRAGWERTE_ZEIGER(recordp)
     from KDAUFTRAGWERTE
     where SKtkdauftragwerte;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGWERTE_LISTE
     into KDAUFTRAGWERTE_ZEIGER(recordp)
     from KDAUFTRAGWERTE
     where PKtkdauftragwerte;

#ifdef SKtkdauftragwerte
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
/*  FUNCTION: pxOrderValuesReadLock                                      */
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
int pxOrderValuesReadLock
(
    struct tKDAUFTRAGWERTE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGWERTE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragwerte_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGWERTE_LISTE
    from KDAUFTRAGWERTE
    where PKtkdauftragwerte
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragwerte_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragwerte_U1
      into KDAUFTRAGWERTE_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGWERTE_LISTE
    into KDAUFTRAGWERTE_ZEIGER(recordp)
    from KDAUFTRAGWERTE    HOLDLOCK
    where PKtkdauftragwerte;
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
/*  FUNCTION: pxOrderValuesUpdate                                        */
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

int pxOrderValuesUpdate
(
    struct tKDAUFTRAGWERTE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_Update;
    recordp = (struct C_KDAUFTRAGWERTE *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGWERTE
    SET
    KDAUFTRAGWERTE_UPDATE(recordp)
    where current of tkdauftragwerte_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragwerte_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGWERTE
    SET
    KDAUFTRAGWERTE_UPDATE(recordp)
    where PKtkdauftragwerte;
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
/*  FUNCTION: pxOrderValuesInsert                                       */
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
int pxOrderValuesInsert
(
    struct tKDAUFTRAGWERTE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_Insert;
    recordp = (struct C_KDAUFTRAGWERTE *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGWERTE
    (KDAUFTRAGWERTE_LISTE)
    VALUES ( KDAUFTRAGWERTE_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGWERTE
    VALUES ( KDAUFTRAGWERTE_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderValuesDelete                                        */
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

int pxOrderValuesDelete
(
    struct tKDAUFTRAGWERTE* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGWERTE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGWERTE*10+F_Delete;
    recordp = (struct C_KDAUFTRAGWERTE *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGWERTE
    where PKtkdauftragwerte;

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
