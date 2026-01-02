/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarticlecharge.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleChargeStartBrowse  declare and open Cursor
        pxArticleChargeGetNext      get next record
        pxArticleChargeEndBrowse    close cursor
        pxArticleChargeRead         get one record
        pxArticleChargeReadLock     get one record with lock
        pxArticleChargeInsert       Insert record
        pxArticleChargeUpdate       Update record
        pxArticleChargeDelete       Delete record


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
#include <tarticlecharge.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleChargeStartBrowse                             */
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
int pxArticleChargeStartBrowse
(
     struct tARTICLECHARGE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_StartBrowse;
    recordp = (struct C_ARTICLECHARGE *) record;

    if (!(sizeof(struct C_ARTICLECHARGE) == sizeof(struct tARTICLECHARGE)))
       return cDBXR_DEFINITION;

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLECHARGE_LISTE
    FROM ARTICLECHARGE
    WHERE BRANCHNO = :recordp->BRANCHNO AND ARTICLENO = :recordp->ARTICLENO;

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLECHARGE_LISTE
    from ARTICLECHARGE;

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
/*  FUNCTION: pxArticleChargeGetNext                                 */
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
int pxArticleChargeGetNext
(
    struct tARTICLECHARGE * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_GetNext;
    recordp = (struct C_ARTICLECHARGE *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLECHARGE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLECHARGE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleChargeEndBrowse                                     */
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
int pxArticleChargeEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLECHARGE*10+F_EndBrowse;

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
/*  FUNCTION: pxArticleChargeRead                                    */
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

int pxArticleChargeRead
(
    struct tARTICLECHARGE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_Read;
    recordp = (struct C_ARTICLECHARGE *) record;

    EXEC SQL SELECT
        ARTICLECHARGE_LISTE
     into ARTICLECHARGE_ZEIGER(recordp)
     from ARTICLECHARGE
     where PKtarticlecharge;

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
/*  FUNCTION: pxArticleChargeReadLock                                */
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
int pxArticleChargeReadLock
(
    struct tARTICLECHARGE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_ReadLock;
    recordp = (struct C_ARTICLECHARGE *) record;

    EXEC SQL DECLARE tarticlecharge_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLECHARGE_LISTE
    from ARTICLECHARGE
    where PKtarticlecharge
    FOR UPDATE;
    EXEC SQL OPEN tarticlecharge_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tarticlecharge_U1
      into ARTICLECHARGE_ZEIGER(recordp);
    }

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
/*  FUNCTION: pxArticleChargeUpdate                                  */
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

int pxArticleChargeUpdate
(
    struct tARTICLECHARGE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_Update;
    recordp = (struct C_ARTICLECHARGE *) record;

    EXEC SQL UPDATE
    ARTICLECHARGE
    SET
    ARTICLECHARGE_UPDATE(recordp)
    where current of tarticlecharge_U1;

    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tarticlecharge_U1;
    }

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
/*  FUNCTION: pxArticleChargeInsert                                  */
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
int pxArticleChargeInsert
(
    struct tARTICLECHARGE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_Insert;
    recordp = (struct C_ARTICLECHARGE *) record;

    EXEC SQL INSERT INTO
    ARTICLECHARGE
    (ARTICLECHARGE_LISTE)
    VALUES ( ARTICLECHARGE_ZEIGER(recordp) );

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
/*  FUNCTION: pxArticleChargeDelete                                  */
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

int pxArticleChargeDelete
(
    struct tARTICLECHARGE * record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLECHARGE * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLECHARGE*10+F_Delete;
    recordp = (struct C_ARTICLECHARGE *) record;

    EXEC SQL DELETE FROM
    ARTICLECHARGE
    where PKtarticlecharge;

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
