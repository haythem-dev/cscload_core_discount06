/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tservices.c (.cxx)

    Database functions




    FUNCTIONS:

        pxServicesStartBrowse  declare and open Cursor
        pxServicesGetNext      get next record
        pxServicesEndBrowse    close cursor
        pxServicesRead         get one record
        pxServicesReadLock     get one record with lock
        pxServicesInsert       Insert record
        pxServicesUpdate       Update record
        pxServicesDelete       Delete record
*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <tservices.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxServicesStartBrowse                             */
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
int pxServicesStartBrowse
(
     struct tSERVICES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
#ifdef MCtservices
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SERVICES*10+F_StartBrowse;
    recordp = (struct C_SERVICES *) record;

    if (!(sizeof(struct C_SERVICES) == sizeof(struct tSERVICES)))
       return cDBXR_DEFINITION;


#ifdef MCtoeorigintypes
    strcpy(matchcode,recordp->MCtservices);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        SERVICES_LISTE
    from SERVICES
    DWtservices
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        SERVICES_LISTE
    from SERVICES
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
/*  FUNCTION: pxServicesGetNext                                 */
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
int pxServicesGetNext
(
    struct tSERVICES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SERVICES*10+F_GetNext;
    recordp = (struct C_SERVICES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into SERVICES_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into SERVICES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxServicesEndBrowse                               */
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
int pxServicesEndBrowse
(
    int browseid
)
{
    functionnr = F_SERVICES*10+F_EndBrowse;

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
/*  FUNCTION: pxServicesRead                                    */
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

int pxServicesRead
(
    struct tSERVICES* record
#ifdef SKtservices
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SERVICES*10+F_Read;
    recordp = (struct C_SERVICES *) record;

#ifdef SKtservices
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        SERVICES_LISTE
     into SERVICES_ZEIGER(recordp)
     from SERVICES
     where SKtservices;
     break;
    default:
#endif

    EXEC SQL SELECT
        SERVICES_LISTE
     into SERVICES_ZEIGER(recordp)
     from SERVICES
     where PKtservices;

#ifdef SKtservices
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
/*  FUNCTION: pxServicesReadLock                                */
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
int pxServicesReadLock
(
    struct tSERVICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SERVICES*10+F_ReadLock;
    recordp = (struct C_SERVICES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tservices_U1 CURSOR WITH HOLD FOR
        SELECT
        SERVICES_LISTE
    from SERVICES
    where PKtservices
    FOR UPDATE;
    EXEC SQL OPEN tservices_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tservices_U1
      into SERVICES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         SERVICES_LISTE
    into SERVICES_ZEIGER(recordp)
    from SERVICES    HOLDLOCK
    where PKtservices;
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
/*  FUNCTION: pxServicesUpdate                                  */
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

int pxServicesUpdate
(
    struct tSERVICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SERVICES*10+F_Update;
    recordp = (struct C_SERVICES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    SERVICES
    SET
    SERVICES_UPDATE(recordp)
    where current of tservices_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tservices_U1;
    }
#else

    EXEC SQL UPDATE
    SERVICES
    SET
    SERVICES_UPDATE(recordp)
    where PKtservices;
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
/*  FUNCTION: pxServicesInsert                                  */
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
int pxServicesInsert
(
    struct tSERVICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SERVICES*10+F_Insert;
    recordp = (struct C_SERVICES *) record;

    EXEC SQL INSERT INTO
    SERVICES
    (SERVICES_LISTE)
    VALUES ( SERVICES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    OEORIGINTYPES
    VALUES ( OEORIGINTYPES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxServicesDelete                                  */
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

int pxServicesDelete
(
    struct tSERVICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_SERVICES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SERVICES*10+F_Delete;
    recordp = (struct C_SERVICES *) record;

    EXEC SQL DELETE FROM
    SERVICES
    where PKtservices;

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
