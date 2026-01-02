/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: ttenderprogress.c (.sqc)

    Database functions




    FUNCTIONS:

        pxTenderProgressStartBrowse  declare and open Cursor
        pxTenderProgressGetNext      get next record
        pxTenderProgressEndBrowse    close cursor
        pxTenderProgressRead         get one record
        pxTenderProgressReadLock     get one record with lock
        pxTenderProgressInsert       Insert record
        pxTenderProgressUpdate       Update record
        pxTenderProgressDelete       Delete record


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
#include <ttenderprogress.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderProgressStartBrowse                                   */
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
int pxTenderProgressStartBrowse
(
     struct tTENDERPROGRESS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
#ifdef MCttenderprogress
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_StartBrowse;
    recordp = (struct C_TENDERPROGRESS *) record;

    if (!(sizeof(struct C_TENDERPROGRESS) == sizeof(struct tTENDERPROGRESS)))
       return cDBXR_DEFINITION;


#ifdef MCttenderprogress
    strcpy(matchcode,recordp->MCttenderprogress);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        TENDERPROGRESS_LISTE
    from TENDERPROGRESS
    DWttenderprogress
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        TENDERPROGRESS_LISTE
    from TENDERPROGRESS
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        TENDERPROGRESS_LISTE
    from TENDERPROGRESS
    where TENDERNO     = :recordp->TENDERNO
    and   ARTICLENO    = :recordp->ARTICLENO
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        TENDERPROGRESS_LISTE
		from TENDERPROGRESS
		where KDAUFTRAGNR	= :recordp->KDAUFTRAGNR
		and ORDERDATE		= :recordp->ORDERDATE	
		and ARTICLENO		= :recordp->ARTICLENO
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
       case cCRTPGTENDERNOARTICLENO:
          EXEC SQL OPEN C2;
          break;
	   case cCRTPGTENDERNOTENDERNO:
	      EXEC SQL OPEN C3;
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
/*  FUNCTION: pxTenderProgressGetNext                                       */
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
int pxTenderProgressGetNext
(
    struct tTENDERPROGRESS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_GetNext;
    recordp = (struct C_TENDERPROGRESS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into TENDERPROGRESS_ZEIGER(recordp);
          break;
       case cCRTPGTENDERNOARTICLENO:
          EXEC SQL FETCH C2
          into TENDERPROGRESS_ZEIGER(recordp);
          break;
	   case cCRTPGTENDERNOTENDERNO:
		  EXEC SQL FETCH C3
          into TENDERPROGRESS_ZEIGER(recordp);
          break;	   
       default:
          EXEC SQL FETCH C1
          into TENDERPROGRESS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderProgressEndBrowse                                     */
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
int pxTenderProgressEndBrowse
(
    int browseid
)
{
    functionnr = F_TENDERPROGRESS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRTPGTENDERNOARTICLENO:
          EXEC SQL CLOSE C2;
          break;
	   case cCRTPGTENDERNOTENDERNO:
          EXEC SQL CLOSE C3;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxTenderProgressRead                                          */
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

int pxTenderProgressRead
(
    struct tTENDERPROGRESS* record
#ifdef SKttenderprogress
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_Read;
    recordp = (struct C_TENDERPROGRESS *) record;

#ifdef SKttenderprogress
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        TENDERPROGRESS_LISTE
     into TENDERPROGRESS_ZEIGER(recordp)
     from TENDERPROGRESS
     where SKttenderprogress;
     break;
    default:
#endif

    EXEC SQL SELECT
        TENDERPROGRESS_LISTE
     into TENDERPROGRESS_ZEIGER(recordp)
     from TENDERPROGRESS
     where PKttenderprogress;

#ifdef SKttenderprogress
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
/*  FUNCTION: pxTenderProgressReadLock                                      */
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
int pxTenderProgressReadLock
(
    struct tTENDERPROGRESS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_ReadLock;
    recordp = (struct C_TENDERPROGRESS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE ttenderprogress_U1 CURSOR WITH HOLD FOR
        SELECT
        TENDERPROGRESS_LISTE
    from TENDERPROGRESS
    where PKttenderprogress
    FOR UPDATE;
    EXEC SQL OPEN ttenderprogress_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH ttenderprogress_U1
      into TENDERPROGRESS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         TENDERPROGRESS_LISTE
    into TENDERPROGRESS_ZEIGER(recordp)
    from TENDERPROGRESS    HOLDLOCK
    where PKttenderprogress;
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
/*  FUNCTION: pxTenderProgressUpdate                                        */
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

int pxTenderProgressUpdate
(
    struct tTENDERPROGRESS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_Update;
    recordp = (struct C_TENDERPROGRESS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    TENDERPROGRESS
    SET
    TENDERPROGRESS_UPDATE(recordp)
    where current of ttenderprogress_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE ttenderprogress_U1;
    }
#else

    EXEC SQL UPDATE
    TENDERPROGRESS
    SET
    TENDERPROGRESS_UPDATE(recordp)
    where PKttenderprogress;
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
/*  FUNCTION: pxTenderProgressInsert                                       */
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
int pxTenderProgressInsert
(
    struct tTENDERPROGRESS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_Insert;
    recordp = (struct C_TENDERPROGRESS *) record;

    EXEC SQL INSERT INTO
    TENDERPROGRESS
    (TENDERPROGRESS_LISTE)
    VALUES ( TENDERPROGRESS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    TENDERPROGRESS
    VALUES ( TENDERPROGRESS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxTenderProgressDelete                                        */
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

int pxTenderProgressDelete
(
    struct tTENDERPROGRESS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TENDERPROGRESS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TENDERPROGRESS*10+F_Delete;
    recordp = (struct C_TENDERPROGRESS *) record;

    EXEC SQL DELETE FROM
    TENDERPROGRESS
    where PKttenderprogress;

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
