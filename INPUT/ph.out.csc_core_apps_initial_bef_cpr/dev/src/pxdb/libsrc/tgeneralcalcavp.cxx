/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tgeneralcalcavp.c (.sqc)

    Database functions




    FUNCTIONS:

        pxGeneralCalcAvpStartBrowse  declare and open Cursor
        pxGeneralCalcAvpGetNext      get next record
        pxGeneralCalcAvpEndBrowse    close cursor
        pxGeneralCalcAvpRead         get one record
        pxGeneralCalcAvpReadLock     get one record with lock
        pxGeneralCalcAvpInsert       Insert record
        pxGeneralCalcAvpUpdate       Update record
        pxGeneralCalcAvpDelete       Delete record


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
#include <tgeneralcalcavp.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxGeneralCalcAvpStartBrowse                                   */
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
int pxGeneralCalcAvpStartBrowse
(
     struct tGENERALCALCAVP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtgeneralcalcavp
    struct C_GENERALCALCAVP * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_StartBrowse;
#ifdef MCtgeneralcalcavp
    recordp = (struct C_GENERALCALCAVP *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_GENERALCALCAVP) == sizeof(struct tGENERALCALCAVP)))
       return cDBXR_DEFINITION;


#ifdef MCtgeneralcalcavp
    strcpy(matchcode,recordp->MCtgeneralcalcavp);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        GENERALCALCAVP_LISTE
    from GENERALCALCAVP
    DWtgeneralcalcavp
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        GENERALCALCAVP_LISTE
    from GENERALCALCAVP
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
/*  FUNCTION: pxGeneralCalcAvpGetNext                                       */
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
int pxGeneralCalcAvpGetNext
(
    struct tGENERALCALCAVP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_GetNext;
    recordp = (struct C_GENERALCALCAVP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into GENERALCALCAVP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into GENERALCALCAVP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxGeneralCalcAvpEndBrowse                                     */
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
int pxGeneralCalcAvpEndBrowse
(
    int browseid
)
{
    functionnr = F_GENERALCALCAVP*10+F_EndBrowse;

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
/*  FUNCTION: pxGeneralCalcAvpRead                                          */
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

int pxGeneralCalcAvpRead
(
    struct tGENERALCALCAVP* record
#ifdef SKtgeneralcalcavp
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_Read;
    recordp = (struct C_GENERALCALCAVP *) record;

#ifdef SKtgeneralcalcavp
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        GENERALCALCAVP_LISTE
     into GENERALCALCAVP_ZEIGER(recordp)
     from GENERALCALCAVP
     where SKtgeneralcalcavp;
     break;
    default:
#endif

    EXEC SQL SELECT
        GENERALCALCAVP_LISTE
     into GENERALCALCAVP_ZEIGER(recordp)
     from GENERALCALCAVP
     where PKtgeneralcalcavp;

#ifdef SKtgeneralcalcavp
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
/*  FUNCTION: pxGeneralCalcAvpReadLock                                      */
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
int pxGeneralCalcAvpReadLock
(
    struct tGENERALCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_ReadLock;
    recordp = (struct C_GENERALCALCAVP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tgeneralcalcavp_U1 CURSOR WITH HOLD FOR
        SELECT
        GENERALCALCAVP_LISTE
    from GENERALCALCAVP
    where PKtgeneralcalcavp
    FOR UPDATE;
    EXEC SQL OPEN tgeneralcalcavp_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tgeneralcalcavp_U1
      into GENERALCALCAVP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         GENERALCALCAVP_LISTE
    into GENERALCALCAVP_ZEIGER(recordp)
    from GENERALCALCAVP    HOLDLOCK
    where PKtgeneralcalcavp;
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
/*  FUNCTION: pxGeneralCalcAvpUpdate                                        */
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

int pxGeneralCalcAvpUpdate
(
    struct tGENERALCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_Update;
    recordp = (struct C_GENERALCALCAVP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    GENERALCALCAVP
    SET
    GENERALCALCAVP_UPDATE(recordp)
    where current of tgeneralcalcavp_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tgeneralcalcavp_U1;
    }
#else

    EXEC SQL UPDATE
    GENERALCALCAVP
    SET
    GENERALCALCAVP_UPDATE(recordp)
    where PKtgeneralcalcavp;
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
/*  FUNCTION: pxGeneralCalcAvpInsert                                       */
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
int pxGeneralCalcAvpInsert
(
    struct tGENERALCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_Insert;
    recordp = (struct C_GENERALCALCAVP *) record;

    EXEC SQL INSERT INTO
    GENERALCALCAVP
    (GENERALCALCAVP_LISTE)
    VALUES ( GENERALCALCAVP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    GENERALCALCAVP
    VALUES ( GENERALCALCAVP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxGeneralCalcAvpDelete                                        */
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

int pxGeneralCalcAvpDelete
(
    struct tGENERALCALCAVP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_GENERALCALCAVP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_GENERALCALCAVP*10+F_Delete;
    recordp = (struct C_GENERALCALCAVP *) record;

    EXEC SQL DELETE FROM
    GENERALCALCAVP
    where PKtgeneralcalcavp;

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
