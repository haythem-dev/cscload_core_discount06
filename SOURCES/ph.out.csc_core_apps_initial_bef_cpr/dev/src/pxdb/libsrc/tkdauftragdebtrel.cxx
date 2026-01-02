/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tkdauftragdebtrel.c (.sqc)

    Database functions




    FUNCTIONS:

        pxKdauftragDebtRelStartBrowse  declare and open Cursor
        pxKdauftragDebtRelGetNext      get next record
        pxKdauftragDebtRelEndBrowse    close cursor
        pxKdauftragDebtRelRead         get one record
        pxKdauftragDebtRelReadLock     get one record with lock
        pxKdauftragDebtRelInsert       Insert record
        pxKdauftragDebtRelUpdate       Update record
        pxKdauftragDebtRelDelete       Delete record


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tkdauftragdebtrel.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKdauftragDebtRelStartBrowse                                   */
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
int pxKdauftragDebtRelStartBrowse
(
     struct tKDAUFTRAGDEBTREL* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
#ifdef MCtkdauftragdebtrel
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;

    if (!(sizeof(struct C_KDAUFTRAGDEBTREL) == sizeof(struct tKDAUFTRAGDEBTREL)))
       return cDBXR_DEFINITION;


#ifdef MCtkdauftragdebtrel
    strcpy(matchcode,recordp->MCtkdauftragdebtrel);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        KDAUFTRAGDEBTREL_LISTE
    from KDAUFTRAGDEBTREL
    DWtkdauftragdebtrel
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        KDAUFTRAGDEBTREL_LISTE
    from KDAUFTRAGDEBTREL
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

     EXEC SQL DECLARE C2 CURSOR FOR
         SELECT IsReleased
     from KDAUFTRAGDEBTREL where kdauftragnr = :recordp->KDAUFTRAGNR
 #ifndef pxDATABASE_INFORMIX
     FOR BROWSE;
 #else
      ;
 #endif

      EXEC SQL DECLARE C_APPROVALDATAFORORDER CURSOR FOR
	  select
	  nvl(approvalCounter,0) sumClose,
	  nvl(cancelCounter,0) sumCancel
      from KDAUFTRAGDEBTREL where kdauftragnr = :recordp->KDAUFTRAGNR
	  and relcounter = ( select nvl(max(relcounter),0) from KDAUFTRAGDEBTREL where kdauftragnr = :recordp->KDAUFTRAGNR);
  #ifndef pxDATABASE_INFORMIX
      FOR BROWSE;
  #else
       ;
  #endif
       EXEC SQL DECLARE C_GET_DATA_MAX_REL_COUNTER CURSOR FOR
               SELECT first 1
               KDAUFTRAGDEBTREL_LISTE
           from KDAUFTRAGDEBTREL
		   where kdauftragnr = :recordp->KDAUFTRAGNR
		   order by relcounter desc
       #ifndef pxDATABASE_INFORMIX
           FOR BROWSE;
       #else
            ;
       #endif
	   EXEC SQL DECLARE C_CHECK_USER_VOTE CURSOR FOR
	   	   SELECT KDAUFTRAGDEBTREL_LISTE
		   from KDAUFTRAGDEBTREL
		   where kdauftragnr = :recordp->KDAUFTRAGNR and reluser = :recordp->RELUSER
   #ifndef pxDATABASE_INFORMIX
	   FOR BROWSE;
   #else
		;
   #endif
	   EXEC SQL DECLARE C_CHECK_VOTE CURSOR FOR
	   select KDAUFTRAGDEBTREL_LISTE
	   from KDAUFTRAGDEBTREL
	   where kdauftragnr = :recordp->KDAUFTRAGNR
	   order by relcounter desc;
   #ifndef pxDATABASE_INFORMIX
	   FOR BROWSE;
   #else
		;
   #endif
		EXEC SQL DECLARE C_SELECT_FOR_COPY CURSOR FOR
	    select KDAUFTRAGDEBTREL_LISTE
	    from KDAUFTRAGDEBTREL
	    where kdauftragnr = :recordp->KDAUFTRAGNR
	    order by relcounter asc;
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
       case cCRSDEBTREL_GETRELEASEFLAGFORORDER:
		  EXEC SQL OPEN C2;
		  break;
       case cCRSDEBTREL_GETAPPROVALDATAFORORDER:
 		  EXEC SQL OPEN C_APPROVALDATAFORORDER;
 		  break;
       case cCRSDEBTREL_GETDATAFORMAXRELCOUNT:
    	   EXEC SQL OPEN C_GET_DATA_MAX_REL_COUNTER;
    	   break;
       case cCRSDEBTREL_CHECKUSERVOTE:
    	   EXEC SQL OPEN C_CHECK_USER_VOTE;
    	   break;
       case cCRSDEBTREL_CHECKVOTE:
		   EXEC SQL OPEN C_CHECK_VOTE;
		   break;
       case cCRSDEBTREL_SELECTFORCOPY:
		   EXEC SQL OPEN C_SELECT_FOR_COPY;
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
/*  FUNCTION: pxKdauftragDebtRelGetNext                              */
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
int pxKdauftragDebtRelGetNext
(
    struct tKDAUFTRAGDEBTREL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_GetNext;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into KDAUFTRAGDEBTREL_ZEIGER(recordp);
          break;
       case cCRSDEBTREL_GETRELEASEFLAGFORORDER:
    	   EXEC SQL FETCH C2
		   into :recordp->ISRELEASED;
    	   break;
       case cCRSDEBTREL_GETAPPROVALDATAFORORDER:
 		  EXEC SQL FETCH C_APPROVALDATAFORORDER
		  into :recordp->APPROVALCOUNTER, :recordp->CANCELCOUNTER;
 		  break;
 	   case cCRSDEBTREL_GETDATAFORMAXRELCOUNT:
		  EXEC SQL FETCH C_GET_DATA_MAX_REL_COUNTER
			into KDAUFTRAGDEBTREL_ZEIGER(recordp);
		  break;
       case cCRSDEBTREL_CHECKUSERVOTE:
    	   EXEC SQL FETCH C_CHECK_USER_VOTE
		   into KDAUFTRAGDEBTREL_ZEIGER(recordp);
    	   break;
       case cCRSDEBTREL_CHECKVOTE:
		   EXEC SQL FETCH C_CHECK_VOTE
		   into KDAUFTRAGDEBTREL_ZEIGER(recordp);
		   break;
       case cCRSDEBTREL_SELECTFORCOPY:
		   EXEC SQL FETCH C_SELECT_FOR_COPY
		   into KDAUFTRAGDEBTREL_ZEIGER(recordp);
    	   break;
       default:
          EXEC SQL FETCH C1
          into KDAUFTRAGDEBTREL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKdauftragDebtRelEndBrowse                                     */
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
int pxKdauftragDebtRelEndBrowse
(
    int browseid
)
{
    functionnr = F_KDAUFTRAGDEBTREL*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSDEBTREL_GETRELEASEFLAGFORORDER:
    	  EXEC SQL CLOSE C2;
		  break;
       case cCRSDEBTREL_GETDATAFORMAXRELCOUNT:
    	  EXEC SQL CLOSE C_GET_DATA_MAX_REL_COUNTER;
		  break;
	  case cCRSDEBTREL_CHECKUSERVOTE:
		   EXEC SQL CLOSE C_CHECK_USER_VOTE;
		   break;
	  case cCRSDEBTREL_CHECKVOTE:
		   EXEC SQL CLOSE C_CHECK_VOTE;
		   break;
      case cCRSDEBTREL_SELECTFORCOPY:
		   EXEC SQL CLOSE C_SELECT_FOR_COPY;
   	   break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxKdauftragDebtRelRead                                          */
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

int pxKdauftragDebtRelRead
(
    struct tKDAUFTRAGDEBTREL* record
#ifdef SKtkdauftragdebtrel
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_Read;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;

#ifdef SKtkdauftragdebtrel
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        KDAUFTRAGDEBTREL_LISTE
     into KDAUFTRAGDEBTREL_ZEIGER(recordp)
     from KDAUFTRAGDEBTREL
     where SKtkdauftragdebtrel;
     break;
    default:
#endif

    EXEC SQL SELECT
        KDAUFTRAGDEBTREL_LISTE
     into KDAUFTRAGDEBTREL_ZEIGER(recordp)
     from KDAUFTRAGDEBTREL
     where PKtkdauftragdebtrel;

#ifdef SKtkdauftragdebtrel
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
/*  FUNCTION: pxKdauftragDebtRelReadLock                                      */
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
int pxKdauftragDebtRelReadLock
(
    struct tKDAUFTRAGDEBTREL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_ReadLock;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TKDAUFTRAGDEBTREL_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAGDEBTREL_LISTE
    from KDAUFTRAGDEBTREL
    where PKtkdauftragdebtrel
    FOR UPDATE;
    EXEC SQL OPEN TKDAUFTRAGDEBTREL_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TKDAUFTRAGDEBTREL_U1
      into KDAUFTRAGDEBTREL_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAGDEBTREL_LISTE
    into KDAUFTRAGDEBTREL_ZEIGER(recordp)
    from KDAUFTRAGDEBTREL    HOLDLOCK
    where PKtkdauftragdebtrel;
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
/*  FUNCTION: pxKdauftragDebtRelUpdate                                        */
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

int pxKdauftragDebtRelUpdate
(
    struct tKDAUFTRAGDEBTREL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_Update;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAGDEBTREL
    SET
    KDAUFTRAGDEBTREL_UPDATE(recordp)
    where current of TKDAUFTRAGDEBTREL_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TKDAUFTRAGDEBTREL_U1;
    }
#else

    EXEC SQL UPDATE
    KDAUFTRAGDEBTREL
    SET
    KDAUFTRAGDEBTREL_UPDATE(recordp)
    where PKtkdauftragdebtrel;
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
/*  FUNCTION: pxKdauftragDebtRelInsert                                       */
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
int pxKdauftragDebtRelInsert
(
    struct tKDAUFTRAGDEBTREL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_Insert;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;

    EXEC SQL INSERT INTO
    KDAUFTRAGDEBTREL
    (KDAUFTRAGDEBTREL_LISTE)
    VALUES ( KDAUFTRAGDEBTREL_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    KDAUFTRAGDEBTREL
    VALUES ( KDAUFTRAGDEBTREL_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxKdauftragDebtRelDelete                                        */
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

int pxKdauftragDebtRelDelete
(
    struct tKDAUFTRAGDEBTREL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGDEBTREL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGDEBTREL*10+F_Delete;
    recordp = (struct C_KDAUFTRAGDEBTREL *) record;

    EXEC SQL DELETE FROM
    KDAUFTRAGDEBTREL
    where PKtkdauftragdebtrel;

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
