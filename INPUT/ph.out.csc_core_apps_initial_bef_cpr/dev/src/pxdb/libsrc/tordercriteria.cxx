/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tordercriteria.c (.sqc)

    Database functions




    FUNCTIONS:

        pxOrderCriteriaStartBrowse  declare and open Cursor
        pxOrderCriteriaGetNext      get next record
        pxOrderCriteriaEndBrowse    close cursor
        pxOrderCriteriaRead         get one record
        pxOrderCriteriaReadLock     get one record with lock
        pxOrderCriteriaInsert       Insert record
        pxOrderCriteriaUpdate       Update record
        pxOrderCriteriaDelete       Delete record


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
#include <tordercriteria.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderCriteriaStartBrowse                                   */
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
int pxOrderCriteriaStartBrowse
(
     struct tORDERCRITERIA* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
#ifdef MCtordercriteria
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_StartBrowse;
    recordp = (struct C_ORDERCRITERIA *) record;

    if (!(sizeof(struct C_ORDERCRITERIA) == sizeof(struct tORDERCRITERIA)))
       return cDBXR_DEFINITION;


#ifdef MCtordercriteria
    strcpy(matchcode,recordp->MCtordercriteria);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
    DWtordercriteria
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
    where BRANCHNO     = :recordp->BRANCHNO
    and   ARTICLENO    = :recordp->ARTICLENO
    and   ORDER_TYPE    = :recordp->ORDER_TYPE
    and   PHARMACYGROUPID  = :recordp->PHARMACYGROUPID
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
    where BRANCHNO     = :recordp->BRANCHNO
    and   ARTICLENO    = :recordp->ARTICLENO
    and   MANUFACTURERNO   = :recordp->MANUFACTURERNO
    and   CUSTOMERNO   = :recordp->CUSTOMERNO

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
    where BRANCHNO     = :recordp->BRANCHNO
    and   ORDERCRITERIA.ARTICLENO      = 0
    and   ORDERCRITERIA.MANUFACTURERNO = 0
    and  (ORDERCRITERIA.CUSTOMERNO     = 0 or  ORDERCRITERIA.CUSTOMERNO = :recordp->CUSTOMERNO )
    and  (ORDERCRITERIA.PHARMACYGROUPID='000'
    or    ORDERCRITERIA.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and   ORDER_TYPE    = :recordp->ORDER_TYPE
    and   LIMIT_ACTION  = :recordp->LIMIT_ACTION
    and   ADDONCHARGEARTNO > 0



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
       case cCRORDERTYPCSTPHARMGRP       :
          EXEC SQL OPEN C2;
          break;
       case cCRMANUFACTNOCSTNO           :
          EXEC SQL OPEN C3;
          break;
       case cCRORDERTYPLIMITACTION       :
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
/*  FUNCTION: pxOrderCriteriaGetNext                                       */
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
int pxOrderCriteriaGetNext
(
    struct tORDERCRITERIA* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_GetNext;
    recordp = (struct C_ORDERCRITERIA *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ORDERCRITERIA_ZEIGER(recordp);
          break;
       case cCRORDERTYPCSTPHARMGRP      :
          EXEC SQL FETCH C2
          into ORDERCRITERIA_ZEIGER(recordp);
          break;
       case cCRMANUFACTNOCSTNO          :
          EXEC SQL FETCH C3
          into ORDERCRITERIA_ZEIGER(recordp);
          break;
       case cCRORDERTYPLIMITACTION      :
          EXEC SQL FETCH C4
          into ORDERCRITERIA_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ORDERCRITERIA_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOrderCriteriaEndBrowse                                     */
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
int pxOrderCriteriaEndBrowse
(
    int browseid
)
{
    functionnr = F_ORDERCRITERIA*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRORDERTYPCSTPHARMGRP        :
          EXEC SQL CLOSE C2;
          break;
       case cCRMANUFACTNOCSTNO        :
          EXEC SQL CLOSE C3;
          break;
       case cCRORDERTYPLIMITACTION    :
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
/*  FUNCTION: pxOrderCriteriaRead                                          */
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

int pxOrderCriteriaRead
(
    struct tORDERCRITERIA* record
#ifdef SKtordercriteria
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_Read;
    recordp = (struct C_ORDERCRITERIA *) record;

#ifdef SKtordercriteria
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ORDERCRITERIA_LISTE
     into ORDERCRITERIA_ZEIGER(recordp)
     from ORDERCRITERIA
     where SKtordercriteria;
     break;
    default:
#endif

    EXEC SQL SELECT
        ORDERCRITERIA_LISTE
     into ORDERCRITERIA_ZEIGER(recordp)
     from ORDERCRITERIA
     where PKtordercriteria;

#ifdef SKtordercriteria
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
/*  FUNCTION: pxOrderCriteriaReadLock                                      */
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
int pxOrderCriteriaReadLock
(
    struct tORDERCRITERIA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_ReadLock;
    recordp = (struct C_ORDERCRITERIA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tordercriteria_U1 CURSOR WITH HOLD FOR
        SELECT
        ORDERCRITERIA_LISTE
    from ORDERCRITERIA
    where PKtordercriteria
    FOR UPDATE;
    EXEC SQL OPEN tordercriteria_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tordercriteria_U1
      into ORDERCRITERIA_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ORDERCRITERIA_LISTE
    into ORDERCRITERIA_ZEIGER(recordp)
    from ORDERCRITERIA    HOLDLOCK
    where PKtordercriteria;
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
/*  FUNCTION: pxOrderCriteriaUpdate                                        */
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

int pxOrderCriteriaUpdate
(
    struct tORDERCRITERIA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_Update;
    recordp = (struct C_ORDERCRITERIA *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ORDERCRITERIA
    SET
    ORDERCRITERIA_UPDATE(recordp)
    where current of tordercriteria_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tordercriteria_U1;
    }
#else

    EXEC SQL UPDATE
    ORDERCRITERIA
    SET
    ORDERCRITERIA_UPDATE(recordp)
    where PKtordercriteria;
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
/*  FUNCTION: pxOrderCriteriaInsert                                       */
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
int pxOrderCriteriaInsert
(
    struct tORDERCRITERIA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_Insert;
    recordp = (struct C_ORDERCRITERIA *) record;

    EXEC SQL INSERT INTO
    ORDERCRITERIA
    (ORDERCRITERIA_LISTE)
    VALUES ( ORDERCRITERIA_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ORDERCRITERIA
    VALUES ( ORDERCRITERIA_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxOrderCriteriaDelete                                        */
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

int pxOrderCriteriaDelete
(
    struct tORDERCRITERIA* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ORDERCRITERIA * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ORDERCRITERIA*10+F_Delete;
    recordp = (struct C_ORDERCRITERIA *) record;

    EXEC SQL DELETE FROM
    ORDERCRITERIA
    where PKtordercriteria;

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
