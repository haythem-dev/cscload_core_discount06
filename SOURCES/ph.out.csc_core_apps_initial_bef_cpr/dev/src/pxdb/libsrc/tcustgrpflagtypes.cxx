/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustgrpflagtypes.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustGrpFlagTypesStartBrowse  declare and open Cursor
        pxCustGrpFlagTypesGetNext      get next record
        pxCustGrpFlagTypesEndBrowse    close cursor
        pxCustGrpFlagTypesRead         get one record
        pxCustGrpFlagTypesReadLock     get one record with lock
        pxCustGrpFlagTypesInsert       Insert record
        pxCustGrpFlagTypesUpdate       Update record
        pxCustGrpFlagTypesDelete       Delete record


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
#include <tcustgrpflagtypes.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustGrpFlagTypesStartBrowse                                   */
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
int pxCustGrpFlagTypesStartBrowse
(
     struct tCUSTGRPFLAGTYPES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
#ifdef MCtcustgrpflagtypes
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_StartBrowse;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;

    if (!(sizeof(struct C_CUSTGRPFLAGTYPES) == sizeof(struct tCUSTGRPFLAGTYPES)))
       return cDBXR_DEFINITION;


#ifdef MCtcustgrpflagtypes
    strcpy(matchcode,recordp->MCtcustgrpflagtypes);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTGRPFLAGTYPES_LISTE
    from CUSTGRPFLAGTYPES
    DWtcustgrpflagtypes
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTGRPFLAGTYPES_LISTE
    from CUSTGRPFLAGTYPES
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
/*  FUNCTION: pxCustGrpFlagTypesGetNext                                       */
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
int pxCustGrpFlagTypesGetNext
(
    struct tCUSTGRPFLAGTYPES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_GetNext;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTGRPFLAGTYPES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTGRPFLAGTYPES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustGrpFlagTypesEndBrowse                                     */
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
int pxCustGrpFlagTypesEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTGRPFLAGTYPES*10+F_EndBrowse;

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
/*  FUNCTION: pxCustGrpFlagTypesRead                                          */
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

int pxCustGrpFlagTypesRead
(
    struct tCUSTGRPFLAGTYPES* record
#ifdef SKtcustgrpflagtypes
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_Read;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;

#ifdef SKtcustgrpflagtypes
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTGRPFLAGTYPES_LISTE
     into CUSTGRPFLAGTYPES_ZEIGER(recordp)
     from CUSTGRPFLAGTYPES
     where SKtcustgrpflagtypes;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTGRPFLAGTYPES_LISTE
     into CUSTGRPFLAGTYPES_ZEIGER(recordp)
     from CUSTGRPFLAGTYPES
     where PKtcustgrpflagtypes;

#ifdef SKtcustgrpflagtypes
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
/*  FUNCTION: pxCustGrpFlagTypesReadLock                                      */
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
int pxCustGrpFlagTypesReadLock
(
    struct tCUSTGRPFLAGTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_ReadLock;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcustgrpflagtypes_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTGRPFLAGTYPES_LISTE
    from CUSTGRPFLAGTYPES
    where PKtcustgrpflagtypes
    FOR UPDATE;
    EXEC SQL OPEN tcustgrpflagtypes_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcustgrpflagtypes_U1
      into CUSTGRPFLAGTYPES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTGRPFLAGTYPES_LISTE
    into CUSTGRPFLAGTYPES_ZEIGER(recordp)
    from CUSTGRPFLAGTYPES    HOLDLOCK
    where PKtcustgrpflagtypes;
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
/*  FUNCTION: pxCustGrpFlagTypesUpdate                                        */
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

int pxCustGrpFlagTypesUpdate
(
    struct tCUSTGRPFLAGTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_Update;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTGRPFLAGTYPES
    SET
    CUSTGRPFLAGTYPES_UPDATE(recordp)
    where current of tcustgrpflagtypes_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcustgrpflagtypes_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTGRPFLAGTYPES
    SET
    CUSTGRPFLAGTYPES_UPDATE(recordp)
    where PKtcustgrpflagtypes;
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
/*  FUNCTION: pxCustGrpFlagTypesInsert                                       */
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
int pxCustGrpFlagTypesInsert
(
    struct tCUSTGRPFLAGTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_Insert;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;

    EXEC SQL INSERT INTO
    CUSTGRPFLAGTYPES
    (CUSTGRPFLAGTYPES_LISTE)
    VALUES ( CUSTGRPFLAGTYPES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTGRPFLAGTYPES
    VALUES ( CUSTGRPFLAGTYPES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustGrpFlagTypesDelete                                        */
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

int pxCustGrpFlagTypesDelete
(
    struct tCUSTGRPFLAGTYPES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTGRPFLAGTYPES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTGRPFLAGTYPES*10+F_Delete;
    recordp = (struct C_CUSTGRPFLAGTYPES *) record;

    EXEC SQL DELETE FROM
    CUSTGRPFLAGTYPES
    where PKtcustgrpflagtypes;

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
