/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tparamet.c (.sqc)

    Database functions




    FUNCTIONS:

        pxParameterStartBrowse  declare and open Cursor
        pxParameterGetNext      get next record
        pxParameterEndBrowse    close cursor
        pxParameterRead         get one record
        pxParameterReadLock     get one record with lock
        pxParameterInsert       Insert record
        pxParameterUpdate       Update record
        pxParameterDelete       Delete record


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
#include <tparamet.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxParameterStartBrowse                                   */
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
int pxParameterStartBrowse
(
     struct tPARAMETER* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
#ifdef MCtparamet
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_StartBrowse;
    recordp = (struct C_PARAMETER *) record;

    if (!(sizeof(struct C_PARAMETER) == sizeof(struct tPARAMETER)))
       return cDBXR_DEFINITION;


#ifdef MCtparamet
    strcpy(matchcode,recordp->MCtparamet);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        PARAMETER_LISTE
    from PARAMETER
    DWtparamet
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        PARAMETER_LISTE
    from PARAMETER
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        PARAMETER_LISTE
    from PARAMETER
    where FILIALNR      = :recordp->FILIALNR
    and   PROGRAMMNAME  = :recordp->PROGRAMMNAME
    and   ZWECK         = :recordp->ZWECK
    and   PARAMETERNAME = :recordp->PARAMETERNAME
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
       case cCRSPARAMETER_MINT:
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
/*  FUNCTION: pxParameterGetNext                                       */
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
int pxParameterGetNext
(
    struct tPARAMETER* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_GetNext;
    recordp = (struct C_PARAMETER *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into PARAMETER_ZEIGER(recordp);
          break;
       case cCRSPARAMETER_MINT:
          EXEC SQL FETCH C2
          into PARAMETER_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into PARAMETER_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxParameterEndBrowse                                     */
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
int pxParameterEndBrowse
(
    int browseid
)
{
    functionnr = F_PARAMETER*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSPARAMETER_MINT:
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
/*  FUNCTION: pxParameterRead                                          */
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

int pxParameterRead
(
    struct tPARAMETER* record
#ifdef SKtparamet
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_Read;
    recordp = (struct C_PARAMETER *) record;

#ifdef SKtparamet
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        PARAMETER_LISTE
     into PARAMETER_ZEIGER(recordp)
     from PARAMETER
     where SKtparamet;
     break;
    default:
#endif

    EXEC SQL SELECT
        PARAMETER_LISTE
     into PARAMETER_ZEIGER(recordp)
     from PARAMETER
     where PKtparamet;

#ifdef SKtparamet
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
/*  FUNCTION: pxParameterReadLock                                      */
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
int pxParameterReadLock
(
    struct tPARAMETER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_ReadLock;
    recordp = (struct C_PARAMETER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TPARAMET_U1 CURSOR WITH HOLD FOR
        SELECT
        PARAMETER_LISTE
    from PARAMETER
    where PKtparamet
    FOR UPDATE;
    EXEC SQL OPEN TPARAMET_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TPARAMET_U1
      into PARAMETER_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         PARAMETER_LISTE
    into PARAMETER_ZEIGER(recordp)
    from PARAMETER    HOLDLOCK
    where PKtparamet;
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
/*  FUNCTION: pxParameterUpdate                                        */
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

int pxParameterUpdate
(
    struct tPARAMETER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_Update;
    recordp = (struct C_PARAMETER *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    PARAMETER
    SET
    PARAMETER_UPDATE(recordp)
    where current of TPARAMET_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TPARAMET_U1;
    }
#else

    EXEC SQL UPDATE
    PARAMETER
    SET
    PARAMETER_UPDATE(recordp)
    where PKtparamet;
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
/*  FUNCTION: pxParameterInsert                                       */
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
int pxParameterInsert
(
    struct tPARAMETER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_Insert;
    recordp = (struct C_PARAMETER *) record;

    EXEC SQL INSERT INTO
    PARAMETER
    (PARAMETER_LISTE)
    VALUES ( PARAMETER_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    PARAMETER
    VALUES ( PARAMETER_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxParameterDelete                                        */
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

int pxParameterDelete
(
    struct tPARAMETER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAMETER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAMETER*10+F_Delete;
    recordp = (struct C_PARAMETER *) record;

    EXEC SQL DELETE FROM
    PARAMETER
    where PKtparamet;

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
