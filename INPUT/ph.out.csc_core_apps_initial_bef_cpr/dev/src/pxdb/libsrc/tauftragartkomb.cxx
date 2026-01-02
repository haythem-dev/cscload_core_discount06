#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <pxrecord.h>
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tauftragartkomb.h"
#include "keys.h"

extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAufArtKombStartBrowse                                   */
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
int pxAufArtKombStartBrowse( struct tAUFTRAGARTKOMB* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
#ifdef MCtaufkom
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_StartBrowse;
    recordp = (struct C_AUFTRAGARTKOMB *) record;

    if (!(sizeof(struct C_AUFTRAGARTKOMB) == sizeof(struct tAUFTRAGARTKOMB)))
       return cDBXR_DEFINITION;


#ifdef MCtaufkom
    strcpy(matchcode,recordp->MCtaufkom);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        AUFTRAGARTKOMB_LISTE
    from AUFTRAGARTKOMB
    DWtaufkom
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        AUFTRAGARTKOMB_LISTE
    from AUFTRAGARTKOMB
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
int pxAufArtKombGetNext( struct tAUFTRAGARTKOMB* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_GetNext;
    recordp = (struct C_AUFTRAGARTKOMB *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into AUFTRAGARTKOMB_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into AUFTRAGARTKOMB_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/
int pxAufArtKombEndBrowse( int browseid )
{
    functionnr = F_AUFTRAGARTKOMB*10+F_EndBrowse;

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
int pxAufArtKombRead( struct tAUFTRAGARTKOMB* record
	#ifdef SKtaufkom
	    , int keyid               /* keyid if read with sec key possible */
	#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_Read;
    recordp = (struct C_AUFTRAGARTKOMB *) record;

#ifdef SKtaufkom
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        AUFTRAGARTKOMB_LISTE
     into AUFTRAGARTKOMB_ZEIGER(recordp)
     from AUFTRAGARTKOMB
     where SKtaufkom;
     break;
    default:
#endif

    EXEC SQL SELECT
        AUFTRAGARTKOMB_LISTE
     into AUFTRAGARTKOMB_ZEIGER(recordp)
     from AUFTRAGARTKOMB
     where PKtaufkom;

#ifdef SKtaufkom
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
/*  FUNCTION: pxAufArtKombReadLock                                      */
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
int pxAufArtKombReadLock
(
    struct tAUFTRAGARTKOMB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_ReadLock;
    recordp = (struct C_AUFTRAGARTKOMB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFKOM_U1 CURSOR WITH HOLD FOR
        SELECT
        AUFTRAGARTKOMB_LISTE
    from AUFTRAGARTKOMB
    where PKtaufkom
    FOR UPDATE;
    EXEC SQL OPEN TAUFKOM_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFKOM_U1
      into AUFTRAGARTKOMB_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         AUFTRAGARTKOMB_LISTE
    into AUFTRAGARTKOMB_ZEIGER(recordp)
    from AUFTRAGARTKOMB    HOLDLOCK
    where PKtaufkom;
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
/*  FUNCTION: pxAufArtKombUpdate                                        */
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

int pxAufArtKombUpdate
(
    struct tAUFTRAGARTKOMB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_Update;
    recordp = (struct C_AUFTRAGARTKOMB *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    AUFTRAGARTKOMB
    SET
    AUFTRAGARTKOMB_UPDATE(recordp)
    where current of TAUFKOM_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFKOM_U1;
    }
#else

    EXEC SQL UPDATE
    AUFTRAGARTKOMB
    SET
    AUFTRAGARTKOMB_UPDATE(recordp)
    where PKtaufkom;
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
/*  FUNCTION: pxAufArtKombInsert                                       */
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
int pxAufArtKombInsert
(
    struct tAUFTRAGARTKOMB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_Insert;
    recordp = (struct C_AUFTRAGARTKOMB *) record;

    EXEC SQL INSERT INTO
    AUFTRAGARTKOMB
    (AUFTRAGARTKOMB_LISTE)
    VALUES ( AUFTRAGARTKOMB_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    AUFTRAGARTKOMB
    VALUES ( AUFTRAGARTKOMB_ZEIGER(recordp) );   */


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
/*  FUNCTION: pxAufArtKombDelete                                        */
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

int pxAufArtKombDelete
(
    struct tAUFTRAGARTKOMB* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_AUFTRAGARTKOMB * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_AUFTRAGARTKOMB*10+F_Delete;
    recordp = (struct C_AUFTRAGARTKOMB *) record;

    EXEC SQL DELETE FROM
    AUFTRAGARTKOMB
    where PKtaufkom;

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
