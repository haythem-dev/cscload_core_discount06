/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tliefpo.c (.sqc)

    Database functions




    FUNCTIONS:

        pxNachLieferPosStartBrowse  declare and open Cursor
        pxNachLieferPosGetNext      get next record
        pxNachLieferPosEndBrowse    close cursor
        pxNachLieferPosRead         get one record
        pxNachLieferPosReadLock     get one record with lock
        pxNachLieferPosInsert       Insert record
        pxNachLieferPosUpdate       Update record
        pxNachLieferPosDelete       Delete record


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
#include "tliefpo.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNachLieferPosStartBrowse                                   */
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
int pxNachLieferPosStartBrowse
(
     struct tNACHLIEFERPOS* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
#ifdef MCtliefpo
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_StartBrowse;
    recordp = (struct C_NACHLIEFERPOS *) record;

    if (!(sizeof(struct C_NACHLIEFERPOS) == sizeof(struct tNACHLIEFERPOS)))
       return cDBXR_DEFINITION;


#ifdef MCtliefpo
    strcpy(matchcode,recordp->MCtliefpo);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    DWtliefpo
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where IDFNR  = :recordp->IDFNR
    and   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and   POSTYP = :recordp->POSTYP
    and   STATUS < 2
    order by DATUM ASC

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where IDFNR  = :recordp->IDFNR
    and   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where KDAUFTRAGNR = :recordp->KDAUFTRAGNR
    and  DATUM = :recordp->DATUM

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C5 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where KDAUFTRAGNR = :recordp->KDAUFTRAGNR
    and  DATUM >= :recordp->DATUM
    and   POSTYP = :recordp->POSTYP

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C6 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and   IDFNR  = :recordp->IDFNR
    and   ARTIKEL_NR = :recordp->ARTIKEL_NR
    and   POSTYP = :recordp->POSTYP

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C7 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and   ARTIKEL_NR = :recordp->ARTIKEL_NR
    and   POSTYP = :recordp->POSTYP
    and   KDAUFTRAGART != 'UW'

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C8 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where IDFNR  = :recordp->IDFNR
    and   VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and   POSTYP in (3,5)
    and   STATUS < 2
	order by POSTYP DESC, DATUM ASC

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C9 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
    and   ARTIKEL_NR = :recordp->ARTIKEL_NR
    and   POSTYP = :recordp->POSTYP
    and   KDAUFTRAGART = :recordp->KDAUFTRAGART

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C10 CURSOR FOR
        SELECT
        NACHLIEFERPOS_LISTE
        from NACHLIEFERPOS
    where VERTRIEBSZENTRUMNR = :recordp->VERTRIEBSZENTRUMNR
        and KDAUFTRAGNR = : recordp->KDAUFTRAGNR
        and IDFNR = : recordp->IDFNR
        and KDAUFTRAGART = : recordp->KDAUFTRAGART

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
       case cCRSDELPOS_IDFNRPOSTYP       :
          EXEC SQL OPEN C2;
          break;
       case cCRSDELPOS_IDFNR             :
          EXEC SQL OPEN C3;
          break;
       case cCRSDELPOS_ORDERDATUM:
          EXEC SQL OPEN C4;
          break;
       case cCRSDELPOS_ORDDATPOSTYP:
          EXEC SQL OPEN C5;
          break;
       case cCRSDELPOS_VZIDFARTPOSTYP:
          EXEC SQL OPEN C6;
          break;
       case cCRSDELPOS_ARTPOSTYPVZ:
          EXEC SQL OPEN C7;
          break;
       case cCRSDELPOS_IDFNRPOSTYP35:
          EXEC SQL OPEN C8;
          break;
       case cCRSDELPOS_ARTPOSTYPVZOTYPE:
          EXEC SQL OPEN C9;
          break;
       case cCRSDELPOS_ORDERVZIDFNROTYPE:
          EXEC SQL OPEN C10;
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
/*  FUNCTION: pxNachLieferPosGetNext                                       */
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
int pxNachLieferPosGetNext
(
    struct tNACHLIEFERPOS* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_GetNext;
    recordp = (struct C_NACHLIEFERPOS *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_IDFNRPOSTYP       :
          EXEC SQL FETCH C2
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_IDFNR             :
          EXEC SQL FETCH C3
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_ORDERDATUM:
          EXEC SQL FETCH C4
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_ORDDATPOSTYP:
          EXEC SQL FETCH C5
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_VZIDFARTPOSTYP:
          EXEC SQL FETCH C6
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_ARTPOSTYPVZ:
          EXEC SQL FETCH C7
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_IDFNRPOSTYP35:
          EXEC SQL FETCH C8
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_ARTPOSTYPVZOTYPE:
          EXEC SQL FETCH C9
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
       case cCRSDELPOS_ORDERVZIDFNROTYPE:
          EXEC SQL FETCH C10
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;

       default:
          EXEC SQL FETCH C1
          into NACHLIEFERPOS_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNachLieferPosEndBrowse                                     */
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
int pxNachLieferPosEndBrowse
(
    int browseid
)
{
    functionnr = F_NACHLIEFERPOS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSDELPOS_IDFNRPOSTYP       :
          EXEC SQL CLOSE C2;
          break;
       case cCRSDELPOS_IDFNR             :
          EXEC SQL CLOSE C3;
          break;
       case cCRSDELPOS_ORDERDATUM        :
          EXEC SQL CLOSE C4;
          break;
       case cCRSDELPOS_ORDDATPOSTYP      :
          EXEC SQL CLOSE C5;
          break;
       case cCRSDELPOS_VZIDFARTPOSTYP    :
          EXEC SQL CLOSE C6;
          break;
       case cCRSDELPOS_ARTPOSTYPVZ    :
          EXEC SQL CLOSE C7;
          break;
       case cCRSDELPOS_IDFNRPOSTYP35    :
          EXEC SQL CLOSE C8;
          break;
       case cCRSDELPOS_ARTPOSTYPVZOTYPE    :
          EXEC SQL CLOSE C9;
          break;
       case cCRSDELPOS_ORDERVZIDFNROTYPE:
           EXEC SQL CLOSE C10;
           break;

       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNachLieferPosRead                                          */
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

int pxNachLieferPosRead
(
    struct tNACHLIEFERPOS* record
#ifdef SKtliefpo
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_Read;
    recordp = (struct C_NACHLIEFERPOS *) record;

#ifdef SKtliefpo
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        NACHLIEFERPOS_LISTE
     into NACHLIEFERPOS_ZEIGER(recordp)
     from NACHLIEFERPOS
     where SKtliefpo;
     break;
    default:
#endif

    EXEC SQL SELECT
        NACHLIEFERPOS_LISTE
     into NACHLIEFERPOS_ZEIGER(recordp)
     from NACHLIEFERPOS
     where PKtliefpo;

#ifdef SKtliefpo
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
/*  FUNCTION: pxNachLieferPosReadLock                                      */
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
int pxNachLieferPosReadLock
(
    struct tNACHLIEFERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_ReadLock;
    recordp = (struct C_NACHLIEFERPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TLIEFPO_U1 CURSOR WITH HOLD FOR
        SELECT
        NACHLIEFERPOS_LISTE
    from NACHLIEFERPOS
    where PKtliefpo
    FOR UPDATE;
    EXEC SQL OPEN TLIEFPO_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TLIEFPO_U1
      into NACHLIEFERPOS_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         NACHLIEFERPOS_LISTE
    into NACHLIEFERPOS_ZEIGER(recordp)
    from NACHLIEFERPOS    HOLDLOCK
    where PKtliefpo;
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
/*  FUNCTION: pxNachLieferPosUpdate                                        */
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

int pxNachLieferPosUpdate
(
    struct tNACHLIEFERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_Update;
    recordp = (struct C_NACHLIEFERPOS *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    NACHLIEFERPOS
    SET
    NACHLIEFERPOS_UPDATE(recordp)
    where current of TLIEFPO_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TLIEFPO_U1;
    }
#else

    EXEC SQL UPDATE
    NACHLIEFERPOS
    SET
    NACHLIEFERPOS_UPDATE(recordp)
    where PKtliefpo;
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
/*  FUNCTION: pxNachLieferPosInsert                                       */
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
int pxNachLieferPosInsert
(
    struct tNACHLIEFERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_Insert;
    recordp = (struct C_NACHLIEFERPOS *) record;

    EXEC SQL INSERT INTO
    NACHLIEFERPOS
    (NACHLIEFERPOS_LISTE)
    VALUES ( NACHLIEFERPOS_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    NACHLIEFERPOS
    VALUES ( NACHLIEFERPOS_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxNachLieferPosDelete                                        */
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

int pxNachLieferPosDelete
(
    struct tNACHLIEFERPOS* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_NACHLIEFERPOS * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NACHLIEFERPOS*10+F_Delete;
    recordp = (struct C_NACHLIEFERPOS *) record;

    EXEC SQL DELETE FROM
    NACHLIEFERPOS
    where PKtliefpo;

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
