/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticlecodes.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleCodesStartBrowse  declare and open Cursor
        pxArticleCodesGetNext      get next record
        pxArticleCodesEndBrowse    close cursor
        pxArticleCodesRead         get one record
        pxArticleCodesReadLock     get one record with lock
        pxArticleCodesInsert       Insert record
        pxArticleCodesUpdate       Update record
        pxArticleCodesDelete       Delete record


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
#include <tarticlecodes.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleCodesStartBrowse                                   */
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
int pxArticleCodesStartBrowse
(
     struct tARTICLECODES* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_StartBrowse;
    recordp = (struct C_ARTICLECODES *) record;

    if (!(sizeof(struct C_ARTICLECODES) == sizeof(struct tARTICLECODES)))
       return cDBXR_DEFINITION;

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLECODES_LISTE
    from ARTICLECODES
    DWtarticlecodes;

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLECODES_LISTE
    from ARTICLECODES;

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        ARTICLECODES_LISTE
    from ARTICLECODES
    where ARTICLECODES.ARTICLENO    = :recordp->ARTICLENO
	and   ARTICLECODES.PREFERRED_FLAG = 1;

	EXEC SQL DECLARE C3 CURSOR FOR
		SELECT
		ARTICLECODES_LISTE
		from ARTICLECODES
	where ARTICLECODES.ARTICLENO = :recordp->ARTICLENO
	and   ARTICLECODES.CODE_TYPE = :recordp->CODE_TYPE;

	switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       case cCRSARTICLENO_PREFERRED:
          EXEC SQL OPEN C2;
          break;
       case cCRSARTICLENO_CODETYPE:
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
/*  FUNCTION: pxArticleCodesGetNext                                       */
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
int pxArticleCodesGetNext
(
    struct tARTICLECODES* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_GetNext;
    recordp = (struct C_ARTICLECODES *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLECODES_ZEIGER(recordp);
          break;
       case cCRSARTICLENO_PREFERRED:
          EXEC SQL FETCH C2
          into ARTICLECODES_ZEIGER(recordp);
          break;
       case cCRSARTICLENO_CODETYPE:
          EXEC SQL FETCH C3
          into ARTICLECODES_ZEIGER(recordp);
          break;
	   default:
          EXEC SQL FETCH C1
          into ARTICLECODES_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleCodesEndBrowse                                     */
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
int pxArticleCodesEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLECODES*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSARTICLENO_PREFERRED:
          EXEC SQL CLOSE C2;
          break;
       case cCRSARTICLENO_CODETYPE:
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
/*  FUNCTION: pxArticleCodesRead                                          */
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

int pxArticleCodesRead
(
    struct tARTICLECODES* record
#ifdef SKtarticlecodes
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_Read;
    recordp = (struct C_ARTICLECODES *) record;

#ifdef SKtarticlecodes
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLECODES_LISTE
     into ARTICLECODES_ZEIGER(recordp)
     from ARTICLECODES
     where SKtarticlecodes;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLECODES_LISTE
     into ARTICLECODES_ZEIGER(recordp)
     from ARTICLECODES
     where PKtarticlecodes;

#ifdef SKtarticlecodes
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
/*  FUNCTION: pxArticleCodesReadLock                                      */
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
int pxArticleCodesReadLock
(
    struct tARTICLECODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_ReadLock;
    recordp = (struct C_ARTICLECODES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tarticlecodes_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLECODES_LISTE
    from ARTICLECODES
    where PKtarticlecodes
    FOR UPDATE;
    EXEC SQL OPEN tarticlecodes_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticlecodes_U1
      into ARTICLECODES_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLECODES_LISTE
    into ARTICLECODES_ZEIGER(recordp)
    from ARTICLECODES    HOLDLOCK
    where PKtarticlecodes;
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
/*  FUNCTION: pxArticleCodesUpdate                                        */
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

int pxArticleCodesUpdate
(
    struct tARTICLECODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_Update;
    recordp = (struct C_ARTICLECODES *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLECODES
    SET
    ARTICLECODES_UPDATE(recordp)
    where current of tarticlecodes_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticlecodes_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLECODES
    SET
    ARTICLECODES_UPDATE(recordp)
    where PKtarticlecodes;
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
/*  FUNCTION: pxArticleCodesInsert                                       */
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
int pxArticleCodesInsert
(
    struct tARTICLECODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_Insert;
    recordp = (struct C_ARTICLECODES *) record;

    EXEC SQL INSERT INTO
    ARTICLECODES
    (ARTICLECODES_LISTE)
    VALUES ( ARTICLECODES_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLECODES
    VALUES ( ARTICLECODES_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArticleCodesDelete                                        */
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

int pxArticleCodesDelete
(
    struct tARTICLECODES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECODES * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECODES*10+F_Delete;
    recordp = (struct C_ARTICLECODES *) record;

    EXEC SQL DELETE FROM
    ARTICLECODES
    where PKtarticlecodes;

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
