/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tkdauftragposrab.c (.sqc)

    Database functions




    FUNCTIONS:

        pxItemDiscountStartBrowse  declare and open Cursor
        pxItemDiscountGetNext      get next record
        pxItemDiscountEndBrowse    close cursor
        pxItemDiscountRead         get one record
        pxItemDiscountReadLock     get one record with lock
        pxItemDiscountInsert       Insert record
        pxItemDiscountUpdate       Update record
        pxItemDiscountDelete       Delete record


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
#include <tkdauftragposrab.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxItemDiscountStartBrowse                                   */
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
int pxItemDiscountStartBrowse
(
     struct tKDAUFTRAGPOSRAB* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
#ifdef MCtkdauftragposrab
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;

    if (!(sizeof(struct C_KDAUFTRAGPOSRAB) == sizeof(struct tKDAUFTRAGPOSRAB)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragposrab
    strcpy(matchcode,recordp->MCtkdauftragposrab);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGPOSRAB_LISTE
    from KDAUFTRAGPOSRAB
    DWtkdauftragposrab
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        KDAUFTRAGPOSRAB_LISTE
    from KDAUFTRAGPOSRAB
    where KDAUFTRAGNR        = :recordp->KDAUFTRAGNR
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGPOSRAB_LISTE
    from KDAUFTRAGPOSRAB
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
       case cCRSPOSRAB_KDAUFTRAGNR:
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
/*  FUNCTION: pxItemDiscountGetNext                                  */
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
int pxItemDiscountGetNext
(
    struct tKDAUFTRAGPOSRAB* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGPOSRAB_ZEIGER(recordp);
          break;
       case cCRSPOSRAB_KDAUFTRAGNR:
          EXEC SQL FETCH C2
          into KDAUFTRAGPOSRAB_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGPOSRAB_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxItemDiscountEndBrowse                                     */
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
int pxItemDiscountEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGPOSRAB*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSPOSRAB_KDAUFTRAGNR:
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
/*  FUNCTION: pxItemDiscountRead                                          */
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

int pxItemDiscountRead
(
    struct tKDAUFTRAGPOSRAB* record
#ifdef SKtkdauftragposrab
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_Read;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;

#ifdef SKtkdauftragposrab
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGPOSRAB_LISTE
     into KDAUFTRAGPOSRAB_ZEIGER(recordp)
     from KDAUFTRAGPOSRAB
     where SKtkdauftragposrab;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGPOSRAB_LISTE
     into KDAUFTRAGPOSRAB_ZEIGER(recordp)
     from KDAUFTRAGPOSRAB
     where PKtkdauftragposrab;

#ifdef SKtkdauftragposrab
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
/*  FUNCTION: pxItemDiscountReadLock                                      */
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
int pxItemDiscountReadLock
(
    struct tKDAUFTRAGPOSRAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tkdauftragposrab_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGPOSRAB_LISTE
    from KDAUFTRAGPOSRAB
    where PKtkdauftragposrab
    FOR UPDATE;
    EXEC SQL OPEN tkdauftragposrab_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tkdauftragposrab_U1
      into KDAUFTRAGPOSRAB_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGPOSRAB_LISTE
    into KDAUFTRAGPOSRAB_ZEIGER(recordp)
    from KDAUFTRAGPOSRAB    HOLDLOCK
    where PKtkdauftragposrab;
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
/*  FUNCTION: pxItemDiscountUpdate                                        */
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

int pxItemDiscountUpdate
(
    struct tKDAUFTRAGPOSRAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_Update;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGPOSRAB
    SET
    KDAUFTRAGPOSRAB_UPDATE(recordp)
    where current of tkdauftragposrab_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tkdauftragposrab_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGPOSRAB
    SET
    KDAUFTRAGPOSRAB_UPDATE(recordp)
    where PKtkdauftragposrab;
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
/*  FUNCTION: pxItemDiscountInsert                                       */
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
int pxItemDiscountInsert
(
    struct tKDAUFTRAGPOSRAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_Insert;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGPOSRAB
    (KDAUFTRAGPOSRAB_LISTE)
    VALUES ( KDAUFTRAGPOSRAB_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGPOSRAB
    VALUES ( KDAUFTRAGPOSRAB_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxItemDiscountDelete                                        */
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

int pxItemDiscountDelete
(
    struct tKDAUFTRAGPOSRAB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOSRAB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOSRAB*10+F_Delete;
    recordp = (struct C_KDAUFTRAGPOSRAB *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGPOSRAB
    where PKtkdauftragposrab;

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
