/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tcustomergroup.c (.sqc)

    Database functions




    FUNCTIONS:

        pxCustomerGroupStartBrowse  declare and open Cursor
        pxCustomerGroupGetNext      get next record
        pxCustomerGroupEndBrowse    close cursor
        pxCustomerGroupRead         get one record
        pxCustomerGroupReadLock     get one record with lock
        pxCustomerGroupInsert       Insert record
        pxCustomerGroupUpdate       Update record
        pxCustomerGroupDelete       Delete record


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
#include <tcustomergroup.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerGroupStartBrowse                                   */
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
int pxCustomerGroupStartBrowse
(
     struct tCUSTOMERGROUP* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
#ifdef MCtcustomergroup
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_StartBrowse;
    recordp = (struct C_CUSTOMERGROUP *) record;

    if (!(sizeof(struct C_CUSTOMERGROUP) == sizeof(struct tCUSTOMERGROUP)))
       return cDBXR_DEFINITION;


#ifdef MCtcustomergroup
    strcpy(matchcode,recordp->MCtcustomergroup);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        CUSTOMERGROUP_LISTE
    from CUSTOMERGROUP
    DWtcustomergroup
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        CUSTOMERGROUP_LISTE
    from CUSTOMERGROUP
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
/*  FUNCTION: pxCustomerGroupGetNext                                       */
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
int pxCustomerGroupGetNext
(
    struct tCUSTOMERGROUP* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_GetNext;
    recordp = (struct C_CUSTOMERGROUP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into CUSTOMERGROUP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into CUSTOMERGROUP_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCustomerGroupEndBrowse                                     */
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
int pxCustomerGroupEndBrowse
(
    int browseid
)
{
    functionnr = F_CUSTOMERGROUP*10+F_EndBrowse;

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
/*  FUNCTION: pxCustomerGroupRead                                          */
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

int pxCustomerGroupRead
(
    struct tCUSTOMERGROUP* record
#ifdef SKtcustomergroup
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_Read;
    recordp = (struct C_CUSTOMERGROUP *) record;

#ifdef SKtcustomergroup
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        CUSTOMERGROUP_LISTE
     into CUSTOMERGROUP_ZEIGER(recordp)
     from CUSTOMERGROUP
     where SKtcustomergroup;
     break;
    default:
#endif

    EXEC SQL SELECT
        CUSTOMERGROUP_LISTE
     into CUSTOMERGROUP_ZEIGER(recordp)
     from CUSTOMERGROUP
     where PKtcustomergroup;

#ifdef SKtcustomergroup
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
/*  FUNCTION: pxCustomerGroupReadLock                                      */
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
int pxCustomerGroupReadLock
(
    struct tCUSTOMERGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_ReadLock;
    recordp = (struct C_CUSTOMERGROUP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tcustomergroup_U1 CURSOR WITH HOLD FOR
        SELECT
        CUSTOMERGROUP_LISTE
    from CUSTOMERGROUP
    where PKtcustomergroup
    FOR UPDATE;
    EXEC SQL OPEN tcustomergroup_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tcustomergroup_U1
      into CUSTOMERGROUP_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         CUSTOMERGROUP_LISTE
    into CUSTOMERGROUP_ZEIGER(recordp)
    from CUSTOMERGROUP    HOLDLOCK
    where PKtcustomergroup;
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
/*  FUNCTION: pxCustomerGroupUpdate                                        */
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

int pxCustomerGroupUpdate
(
    struct tCUSTOMERGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_Update;
    recordp = (struct C_CUSTOMERGROUP *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    CUSTOMERGROUP
    SET
    CUSTOMERGROUP_UPDATE(recordp)
    where current of tcustomergroup_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tcustomergroup_U1;
    }
#else

    EXEC SQL UPDATE
    CUSTOMERGROUP
    SET
    CUSTOMERGROUP_UPDATE(recordp)
    where PKtcustomergroup;
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
/*  FUNCTION: pxCustomerGroupInsert                                       */
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
int pxCustomerGroupInsert
(
    struct tCUSTOMERGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_Insert;
    recordp = (struct C_CUSTOMERGROUP *) record;

    EXEC SQL INSERT INTO
    CUSTOMERGROUP
    (CUSTOMERGROUP_LISTE)
    VALUES ( CUSTOMERGROUP_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    CUSTOMERGROUP
    VALUES ( CUSTOMERGROUP_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxCustomerGroupDelete                                        */
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

int pxCustomerGroupDelete
(
    struct tCUSTOMERGROUP* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CUSTOMERGROUP * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_CUSTOMERGROUP*10+F_Delete;
    recordp = (struct C_CUSTOMERGROUP *) record;

    EXEC SQL DELETE FROM
    CUSTOMERGROUP
    where PKtcustomergroup;

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
