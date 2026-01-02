/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustomergrpflags.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustomerGrpFlagsStartBrowse  declare and open Cursor
        pxCustomerGrpFlagsGetNext      get next record
        pxCustomerGrpFlagsEndBrowse    close cursor
        pxCustomerGrpFlagsRead         get one record
        pxCustomerGrpFlagsReadLock     get one record with lock
        pxCustomerGrpFlagsInsert       Insert record
        pxCustomerGrpFlagsUpdate       Update record
        pxCustomerGrpFlagsDelete       Delete record


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
#include <tcustomergrpflags.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerGrpFlagsStartBrowse                                   */
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
int pxCustomerGrpFlagsStartBrowse
(
     struct tCUSTOMERGRPFLAGS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
#ifdef MCtcustomergrpflags
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;

    if (!(sizeof(struct C_CUSTOMERGRPFLAGS) == sizeof(struct tCUSTOMERGRPFLAGS)))
       return cDBXR_DEFINITION;


#ifdef MCtcustomergrpflags
    strcpy(matchcode,recordp->MCtcustomergrpflags);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERGRPFLAGS_LISTE
    from CUSTOMERGRPFLAGS
    DWtcustomergrpflags
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERGRPFLAGS_LISTE
    from CUSTOMERGRPFLAGS
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
/*  FUNCTION: pxCustomerGrpFlagsGetNext                                       */
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
int pxCustomerGrpFlagsGetNext
(
    struct tCUSTOMERGRPFLAGS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_GetNext;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERGRPFLAGS_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERGRPFLAGS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerGrpFlagsEndBrowse                                     */
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
int pxCustomerGrpFlagsEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERGRPFLAGS*10+F_EndBrowse;

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
/*  FUNCTION: pxCustomerGrpFlagsRead                                          */
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

int pxCustomerGrpFlagsRead
(
    struct tCUSTOMERGRPFLAGS* record
#ifdef SKtcustomergrpflags
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_Read;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;

#ifdef SKtcustomergrpflags
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERGRPFLAGS_LISTE
     into CUSTOMERGRPFLAGS_ZEIGER(recordp)
     from CUSTOMERGRPFLAGS
     where SKtcustomergrpflags;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERGRPFLAGS_LISTE
     into CUSTOMERGRPFLAGS_ZEIGER(recordp)
     from CUSTOMERGRPFLAGS
     where PKtcustomergrpflags;

#ifdef SKtcustomergrpflags
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
/*  FUNCTION: pxCustomerGrpFlagsReadLock                                      */
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
int pxCustomerGrpFlagsReadLock
(
    struct tCUSTOMERGRPFLAGS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_ReadLock;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcustomergrpflags_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERGRPFLAGS_LISTE
    from CUSTOMERGRPFLAGS
    where PKtcustomergrpflags
    FOR UPDATE;
    EXEC SQL OPEN tcustomergrpflags_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcustomergrpflags_U1
      into CUSTOMERGRPFLAGS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERGRPFLAGS_LISTE
    into CUSTOMERGRPFLAGS_ZEIGER(recordp)
    from CUSTOMERGRPFLAGS    HOLDLOCK
    where PKtcustomergrpflags;
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
/*  FUNCTION: pxCustomerGrpFlagsUpdate                                        */
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

int pxCustomerGrpFlagsUpdate
(
    struct tCUSTOMERGRPFLAGS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_Update;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERGRPFLAGS
    SET
    CUSTOMERGRPFLAGS_UPDATE(recordp)
    where current of tcustomergrpflags_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcustomergrpflags_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERGRPFLAGS
    SET
    CUSTOMERGRPFLAGS_UPDATE(recordp)
    where PKtcustomergrpflags;
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
/*  FUNCTION: pxCustomerGrpFlagsInsert                                       */
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
int pxCustomerGrpFlagsInsert
(
    struct tCUSTOMERGRPFLAGS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_Insert;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;

    EXEC SQL INSERT INTO
    CUSTOMERGRPFLAGS
    (CUSTOMERGRPFLAGS_LISTE)
    VALUES ( CUSTOMERGRPFLAGS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERGRPFLAGS
    VALUES ( CUSTOMERGRPFLAGS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustomerGrpFlagsDelete                                        */
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

int pxCustomerGrpFlagsDelete
(
    struct tCUSTOMERGRPFLAGS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGRPFLAGS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGRPFLAGS*10+F_Delete;
    recordp = (struct C_CUSTOMERGRPFLAGS *) record;

    EXEC SQL DELETE FROM
    CUSTOMERGRPFLAGS
    where PKtcustomergrpflags;

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
