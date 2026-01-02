/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application

    Database functions

    FUNCTIONS:

        pxCremaMailStartBrowse  declare and open Cursor
        pxCremaMailGetNext      get next record
        pxCremaMailEndBrowse    close cursor
        pxCremaMailRead         get one record
        pxCremaMailReadLock     get one record with lock
        pxCremaMailInsert       Insert record
        pxCremaMailUpdate       Update record
        pxCremaMailDelete       Delete record


REVISION HISTORY

18 Mar 2013 V1.00 REV 00 written by Martin Zoephel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* tKDAUFTRAG */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tauftrag.h"
#include "kauftrag.h"       /* key definitions */
#include <pxenv.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailStartBrowse                                 */
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
int pxMSV3OrderStartBrowse( struct tKDAUFTRAG* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * recordp;
    EXEC SQL END   DECLARE SECTION;

    //functionnr = F_KDAUFTRAG*10+F_StartBrowse;
    recordp = (struct C_KDAUFTRAG *) record;

    if (!(sizeof(struct C_KDAUFTRAG) == sizeof(struct tKDAUFTRAG)))
       return cDBXR_DEFINITION;	

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
		
		SELECT DISTINCT a.orderlabel FROM kdauftrag a
		JOIN auftragartkd aa ON aa.vertriebszentrumnr = a.filialnr 
			AND aa.idfnr = a.idfnr 
			AND aa.kdauftragart = a.kdauftragart
		WHERE a.filialnr = :recordp->FILIALNR
		AND a.idfnr = :recordp->IDFNR
		AND a.orderperiodid = :recordp->ORDERPERIODID // AUFTRAEGE AUS GLEICHEM BESTELLFENSTER
		AND a.kdauftragart = :recordp->KDAUFTRAGART // GLEICHE AUFTRAGSART
		AND a.kdauftragart != 'RK'
		AND a.kdauftragstat NOT LIKE '_________1%' // KEINE STORNOS
		AND TRIM(a.orderlabel) != '' // NUR AUFTRAEGE MIT AUFTRAGSKENNUNG
		AND TRIM(a.orderlabel) != TRIM(aa.orderidentificatio) // OHNE DEFAULT AUFTRAGSKENNUNG DER AUFTRAGSART 

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    switch (browseid)
    {
       case cCRSMSV3ORDER_GETDISTINCTORDERLABEL:
          EXEC SQL OPEN C0;
          break;
       default:
          EXEC SQL OPEN C0;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailGetNext                                     */
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
int pxMSV3OrderGetNext( struct tKDAUFTRAG* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * recordp;
    EXEC SQL END   DECLARE SECTION;

    //functionnr = F_KDAUFTRAG*10+F_GetNext;
    recordp = (struct C_KDAUFTRAG *) record;

    switch (browseid)
    {    
       case cCRSMSV3ORDER_GETDISTINCTORDERLABEL:
          EXEC SQL FETCH C0
          into :recordp->ORDERLABEL;
          break;       
       default:
          EXEC SQL FETCH C0
          into :recordp->ORDERLABEL;
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailEndBrowse                                   */
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
int pxMSV3OrderEndBrowse( int browseid )
{
    //functionnr = F_SMTPUSERGROUPS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRSMSV3ORDER_GETDISTINCTORDERLABEL:
          EXEC SQL CLOSE C0;
          break;       
       default:
          EXEC SQL CLOSE C0;
          break;
    }
    return 0;
}

