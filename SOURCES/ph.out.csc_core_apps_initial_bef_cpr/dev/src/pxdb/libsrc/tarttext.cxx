/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tarttext.c (.sqc)

    Database functions




    FUNCTIONS:

        pxArticleTextStartBrowse  declare and open Cursor
        pxArticleTextGetNext      get next record
        pxArticleTextEndBrowse    close cursor
        pxArticleTextRead         get one record
        pxArticleTextReadLock     get one record with lock
        pxArticleTextInsert       Insert record
        pxArticleTextUpdate       Update record
        pxArticleTextDelete       Delete record


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
#include <tarttext.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleTextStartBrowse                                   */
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
int pxArticleTextStartBrowse
(
     struct tARTICLETEXT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtarttext
    struct C_ARTICLETEXT * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_StartBrowse;
#ifdef MCtarttext
    recordp = (struct C_ARTICLETEXT *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_ARTICLETEXT) == sizeof(struct tARTICLETEXT)))
       return cDBXR_DEFINITION;


#ifdef MCtarttext
    strcpy(matchcode,recordp->MCtarttext);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        ARTICLETEXT_LISTE
    from ARTICLETEXT
    DWtarttext
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        ARTICLETEXT_LISTE
    from ARTICLETEXT
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
/*  FUNCTION: pxArticleTextGetNext                                       */
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
int pxArticleTextGetNext
(
    struct tARTICLETEXT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_GetNext;
    recordp = (struct C_ARTICLETEXT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into ARTICLETEXT_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into ARTICLETEXT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxArticleTextEndBrowse                                     */
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
int pxArticleTextEndBrowse
(
    int browseid
)
{
    functionnr = F_ARTICLETEXT*10+F_EndBrowse;

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
/*  FUNCTION: pxArticleTextRead                                          */
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

int pxArticleTextRead
(
    struct tARTICLETEXT* record
#ifdef SKtarttext
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_Read;
    recordp = (struct C_ARTICLETEXT *) record;

#ifdef SKtarttext
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        ARTICLETEXT_LISTE
     into ARTICLETEXT_ZEIGER(recordp)
     from ARTICLETEXT
     where SKtarttext;
     break;
    default:
#endif

    EXEC SQL SELECT
        ARTICLETEXT_LISTE
     into ARTICLETEXT_ZEIGER(recordp)
     from ARTICLETEXT
     where PKtarttext;

#ifdef SKtarttext
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
/*  FUNCTION: pxArticleTextReadLock                                      */
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
int pxArticleTextReadLock
(
    struct tARTICLETEXT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_ReadLock;
    recordp = (struct C_ARTICLETEXT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TARTTEXT_U1 CURSOR WITH HOLD FOR
        SELECT
        ARTICLETEXT_LISTE
    from ARTICLETEXT
    where PKtarttext
    FOR UPDATE;
    EXEC SQL OPEN TARTTEXT_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TARTTEXT_U1
      into ARTICLETEXT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         ARTICLETEXT_LISTE
    into ARTICLETEXT_ZEIGER(recordp)
    from ARTICLETEXT    HOLDLOCK
    where PKtarttext;
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
/*  FUNCTION: pxArticleTextUpdate                                    */
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

int pxArticleTextUpdate
(
    struct tARTICLETEXT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_Update;
    recordp = (struct C_ARTICLETEXT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    ARTICLETEXT
    SET
    ARTICLETEXT_UPDATE(recordp)
    where current of TARTTEXT_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TARTTEXT_U1;
    }
#else

    EXEC SQL UPDATE
    ARTICLETEXT
    SET
    ARTICLETEXT_UPDATE(recordp)
    where PKtarttext;
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
/*  FUNCTION: pxArticleTextInsert                                       */
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
int pxArticleTextInsert
(
    struct tARTICLETEXT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_Insert;
    recordp = (struct C_ARTICLETEXT *) record;

    EXEC SQL INSERT INTO
    ARTICLETEXT
    (ARTICLETEXT_LISTE)
    VALUES ( ARTICLETEXT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    ARTICLETEXT
    VALUES ( ARTICLETEXT_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxArticleTextDelete                                        */
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

int pxArticleTextDelete
(
    struct tARTICLETEXT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTICLETEXT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTICLETEXT*10+F_Delete;
    recordp = (struct C_ARTICLETEXT *) record;

    EXEC SQL DELETE FROM
    ARTICLETEXT
    where PKtarttext;

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
