/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcstcalcavp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCstCalcAvpStartBrowse  declare and open Cursor
        pxCstCalcAvpGetNext      get next record
        pxCstCalcAvpEndBrowse    close cursor
        pxCstCalcAvpRead         get one record
        pxCstCalcAvpReadLock     get one record with lock
        pxCstCalcAvpInsert       Insert record
        pxCstCalcAvpUpdate       Update record
        pxCstCalcAvpDelete       Delete record


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
#include <tcstcalcavp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstCalcAvpStartBrowse                                   */
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
int pxCstCalcAvpStartBrowse
(
     struct tCSTCALCAVP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
#ifdef MCtcstcalcavp
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_StartBrowse;
    recordp = (struct C_CSTCALCAVP *) record;

    if (!(sizeof(struct C_CSTCALCAVP) == sizeof(struct tCSTCALCAVP)))
       return cDBXR_DEFINITION;


#ifdef MCtcstcalcavp
    strcpy(matchcode,recordp->MCtcstcalcavp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CSTCALCAVP_LISTE
    from CSTCALCAVP
    DWtcstcalcavp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CSTCALCAVP_LISTE
    from CSTCALCAVP
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
/*  FUNCTION: pxCstCalcAvpGetNext                                       */
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
int pxCstCalcAvpGetNext
(
    struct tCSTCALCAVP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_GetNext;
    recordp = (struct C_CSTCALCAVP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CSTCALCAVP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CSTCALCAVP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCstCalcAvpEndBrowse                                     */
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
int pxCstCalcAvpEndBrowse
(
    int browseid
)
{
    functionnr = F_CSTCALCAVP*10+F_EndBrowse;

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
/*  FUNCTION: pxCstCalcAvpRead                                          */
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

int pxCstCalcAvpRead
(
    struct tCSTCALCAVP* record
#ifdef SKtcstcalcavp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_Read;
    recordp = (struct C_CSTCALCAVP *) record;

#ifdef SKtcstcalcavp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CSTCALCAVP_LISTE
     into CSTCALCAVP_ZEIGER(recordp)
     from CSTCALCAVP
     where SKtcstcalcavp;
     break;
    default:
#endif

    EXEC SQL SELECT
        CSTCALCAVP_LISTE
     into CSTCALCAVP_ZEIGER(recordp)
     from CSTCALCAVP
     where PKtcstcalcavp;

#ifdef SKtcstcalcavp
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
/*  FUNCTION: pxCstCalcAvpReadLock                                      */
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
int pxCstCalcAvpReadLock
(
    struct tCSTCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_ReadLock;
    recordp = (struct C_CSTCALCAVP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcstcalcavp_U1 CURSOR WITH HOLD FOR
        SELECT
        CSTCALCAVP_LISTE
    from CSTCALCAVP
    where PKtcstcalcavp
    FOR UPDATE;
    EXEC SQL OPEN tcstcalcavp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcstcalcavp_U1
      into CSTCALCAVP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CSTCALCAVP_LISTE
    into CSTCALCAVP_ZEIGER(recordp)
    from CSTCALCAVP    HOLDLOCK
    where PKtcstcalcavp;
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
/*  FUNCTION: pxCstCalcAvpUpdate                                        */
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

int pxCstCalcAvpUpdate
(
    struct tCSTCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_Update;
    recordp = (struct C_CSTCALCAVP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CSTCALCAVP
    SET
    CSTCALCAVP_UPDATE(recordp)
    where current of tcstcalcavp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcstcalcavp_U1;
    }
#else

    EXEC SQL UPDATE
    CSTCALCAVP
    SET
    CSTCALCAVP_UPDATE(recordp)
    where PKtcstcalcavp;
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
/*  FUNCTION: pxCstCalcAvpInsert                                       */
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
int pxCstCalcAvpInsert
(
    struct tCSTCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_Insert;
    recordp = (struct C_CSTCALCAVP *) record;

    EXEC SQL INSERT INTO
    CSTCALCAVP
    (CSTCALCAVP_LISTE)
    VALUES ( CSTCALCAVP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CSTCALCAVP
    VALUES ( CSTCALCAVP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCstCalcAvpDelete                                        */
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

int pxCstCalcAvpDelete
(
    struct tCSTCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CSTCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CSTCALCAVP*10+F_Delete;
    recordp = (struct C_CSTCALCAVP *) record;

    EXEC SQL DELETE FROM
    CSTCALCAVP
    where PKtcstcalcavp;

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
