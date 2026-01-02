/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdiscountgrpmem.c (.sqc)

    Database functions




    FUNCTIONS:

        pxRangeMemberStartBrowse  declare and open Cursor
        pxRangeMemberGetNext      get next record
        pxRangeMemberEndBrowse    close cursor
        pxRangeMemberRead         get one record
        pxRangeMemberReadLock     get one record with lock
        pxRangeMemberInsert       Insert record
        pxRangeMemberUpdate       Update record
        pxRangeMemberDelete       Delete record


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
#include <tdiscountgrpmem.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRangeMemberStartBrowse                                   */
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
int pxRangeMemberStartBrowse
(
     struct tDISCOUNTGRPMEM* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
#ifdef MCtdiscountgrpmem
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_StartBrowse;
    recordp = (struct C_DISCOUNTGRPMEM *) record;

    if (!(sizeof(struct C_DISCOUNTGRPMEM) == sizeof(struct tDISCOUNTGRPMEM)))
       return cDBXR_DEFINITION;


#ifdef MCtdiscountgrpmem
    strcpy(matchcode,recordp->MCtdiscountgrpmem);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISCOUNTGRPMEM_LISTE
    from DISCOUNTGRPMEM
    DWtdiscountgrpmem
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISCOUNTGRPMEM_LISTE
    from DISCOUNTGRPMEM
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        DISCOUNTGRPMEM_LISTE
    from DISCOUNTGRPMEM
    where BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNTGRPNO    = :recordp->DISCOUNTGRPNO
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        DISCOUNTGRPMEM_LISTE
    from DISCOUNTGRPMEM
    where BRANCHNO         = :recordp->BRANCHNO
    and   MANUFACTURERNO   = :recordp->MANUFACTURERNO
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
    SELECT
    DISCOUNTGRPMEM_LISTE
    from  DISCOUNTGRPMEM
    where DISCOUNTGRPMEM.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNTGRPMEM.ARTICLENO        = :recordp->ARTICLENO
    and   DISCOUNTGRPMEM.MANUFACTURERNO   = 0
    and   DISCOUNTGRPMEM.DISCOUNTGRPNO  in (select dg.DISCOUNTGRPNO from DISCOUNTGRP dg  where dg.BRANCHNO = :recordp->BRANCHNO and dg.DISCOUNTGRPNO = DISCOUNTGRPMEM.DISCOUNTGRPNO and dg.DISCOUNTGRPTYPE = 0)
    UNION
    SELECT
    DISCOUNTGRPMEM_LISTE
    from  DISCOUNTGRPMEM
    where DISCOUNTGRPMEM.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNTGRPMEM.ARTICLENO        = 0
    and   DISCOUNTGRPMEM.MANUFACTURERNO   = :recordp->MANUFACTURERNO
    and   DISCOUNTGRPMEM.DISCOUNTGRPNO in (select dg.DISCOUNTGRPNO from DISCOUNTGRP dg where dg.BRANCHNO = :recordp->BRANCHNO
    and   dg.DISCOUNTGRPNO = DISCOUNTGRPMEM.DISCOUNTGRPNO and  dg.DISCOUNTGRPTYPE = 0)
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
       case cCRSGRPMEM_GRPMEMBERS        :
          EXEC SQL OPEN C2;
          break;
       case cCRSGRPMEM_GRPMANUFACTURER   :
          EXEC SQL OPEN C3;
          break;
       case cCRSGRPMEM_GRPARTMANUFACTURER   :
          EXEC SQL OPEN C4;
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
/*  FUNCTION: pxRangeMemberGetNext                                       */
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
int pxRangeMemberGetNext
(
    struct tDISCOUNTGRPMEM* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_GetNext;
    recordp = (struct C_DISCOUNTGRPMEM *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISCOUNTGRPMEM_ZEIGER(recordp);
          break;
       case cCRSGRPMEM_GRPMEMBERS        :
          EXEC SQL FETCH C2
          into DISCOUNTGRPMEM_ZEIGER(recordp);
          break;
       case cCRSGRPMEM_GRPMANUFACTURER        :
          EXEC SQL FETCH C3
          into DISCOUNTGRPMEM_ZEIGER(recordp);
          break;
       case cCRSGRPMEM_GRPARTMANUFACTURER     :
          EXEC SQL FETCH C4
          into DISCOUNTGRPMEM_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into DISCOUNTGRPMEM_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRangeMemberEndBrowse                                     */
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
int pxRangeMemberEndBrowse
(
    int browseid
)
{
    functionnr = F_DISCOUNTGRPMEM*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSGRPMEM_GRPMEMBERS:
          EXEC SQL CLOSE C2;
          break;
       case cCRSGRPMEM_GRPMANUFACTURER:
          EXEC SQL CLOSE C3;
          break;
       case cCRSGRPMEM_GRPARTMANUFACTURER:
          EXEC SQL CLOSE C4;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRangeMemberRead                                          */
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

int pxRangeMemberRead
(
    struct tDISCOUNTGRPMEM* record
#ifdef SKtdiscountgrpmem
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_Read;
    recordp = (struct C_DISCOUNTGRPMEM *) record;

#ifdef SKtdiscountgrpmem
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISCOUNTGRPMEM_LISTE
     into DISCOUNTGRPMEM_ZEIGER(recordp)
     from DISCOUNTGRPMEM
     where SKtdiscountgrpmem;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISCOUNTGRPMEM_LISTE
     into DISCOUNTGRPMEM_ZEIGER(recordp)
     from DISCOUNTGRPMEM
     where PKtdiscountgrpmem;

#ifdef SKtdiscountgrpmem
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
/*  FUNCTION: pxRangeMemberReadLock                                      */
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
int pxRangeMemberReadLock
(
    struct tDISCOUNTGRPMEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_ReadLock;
    recordp = (struct C_DISCOUNTGRPMEM *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdiscountgrpmem_U1 CURSOR WITH HOLD FOR
        SELECT
        DISCOUNTGRPMEM_LISTE
    from DISCOUNTGRPMEM
    where PKtdiscountgrpmem
    FOR UPDATE;
    EXEC SQL OPEN tdiscountgrpmem_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdiscountgrpmem_U1
      into DISCOUNTGRPMEM_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISCOUNTGRPMEM_LISTE
    into DISCOUNTGRPMEM_ZEIGER(recordp)
    from DISCOUNTGRPMEM    HOLDLOCK
    where PKtdiscountgrpmem;
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
/*  FUNCTION: pxRangeMemberUpdate                                        */
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

int pxRangeMemberUpdate
(
    struct tDISCOUNTGRPMEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_Update;
    recordp = (struct C_DISCOUNTGRPMEM *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISCOUNTGRPMEM
    SET
    DISCOUNTGRPMEM_UPDATE(recordp)
    where current of tdiscountgrpmem_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdiscountgrpmem_U1;
    }
#else

    EXEC SQL UPDATE
    DISCOUNTGRPMEM
    SET
    DISCOUNTGRPMEM_UPDATE(recordp)
    where PKtdiscountgrpmem;
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
/*  FUNCTION: pxRangeMemberInsert                                       */
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
int pxRangeMemberInsert
(
    struct tDISCOUNTGRPMEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_Insert;
    recordp = (struct C_DISCOUNTGRPMEM *) record;

    EXEC SQL INSERT INTO
    DISCOUNTGRPMEM
    (DISCOUNTGRPMEM_LISTE)
    VALUES ( DISCOUNTGRPMEM_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISCOUNTGRPMEM
    VALUES ( DISCOUNTGRPMEM_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxRangeMemberDelete                                        */
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

int pxRangeMemberDelete
(
    struct tDISCOUNTGRPMEM* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNTGRPMEM * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNTGRPMEM*10+F_Delete;
    recordp = (struct C_DISCOUNTGRPMEM *) record;

    EXEC SQL DELETE FROM
    DISCOUNTGRPMEM
    where PKtdiscountgrpmem;

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
