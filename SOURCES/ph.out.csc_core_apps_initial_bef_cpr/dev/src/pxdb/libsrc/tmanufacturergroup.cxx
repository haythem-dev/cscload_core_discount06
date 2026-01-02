/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tmanufacturergroup.c (.sqc)

    Database functions




    FUNCTIONS:

        pxManufacturerGroupStartBrowse  declare and open Cursor
        pxManufacturerGroupGetNext      get next record
        pxManufacturerGroupEndBrowse    close cursor
        pxManufacturerGroupRead         get one record
        pxManufacturerGroupReadLock     get one record with lock
        pxManufacturerGroupInsert       Insert record
        pxManufacturerGroupUpdate       Update record
        pxManufacturerGroupDelete       Delete record


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
#include <tmanufacturergroup.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxManufacturerGroupStartBrowse                                   */
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
int pxManufacturerGroupStartBrowse
(
     struct tMANUFACTURERGROUP * record,
     int browseid,
	 short VzNr,
	 long CustomerNo
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_MANUFACTURERGROUP *recordp;
	short sVzNr;
	long lCustomerNo;
#ifdef MCtmanufacturergroup
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_MANUFACTURERGROUP*10+F_StartBrowse;
    if (!(sizeof(struct C_MANUFACTURERGROUP) == sizeof(struct tMANUFACTURERGROUP)))
       return cDBXR_DEFINITION;
    recordp = (struct C_MANUFACTURERGROUP *) record;
    sVzNr = VzNr;
    lCustomerNo = CustomerNo;

#ifdef MCtmanufacturergroup
    strcpy(matchcode,recordp->MCtmanufacturergroup);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        MANUFACTURERGROUP_LISTE
    from MANUFACTURERGROUP
    DWtmanufacturergroup
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        MANUFACTURERGROUP_LISTE
    from MANUFACTURERGROUP
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        MANUFACTURERGROUP_LISTE
    from MANUFACTURERGROUP
	where
	MANUFACTURERGROUP.KONSIG_PARTNER_NR = :recordp->KONSIG_PARTNER_NR
		and MANUFACTURERGROUP.PHARMACYGROUPID in (
		   select customerpharmacygr.pharmacygroupid
		   from customerpharmacygr
		   where customerpharmacygr.branchno = :sVzNr
		   and customerpharmacygr.customerno = :lCustomerNo )

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
       case cCRSKONSIGPARTNERNR:
          EXEC SQL OPEN C2;
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
/*  FUNCTION: pxManufacturerGroupGetNext                                       */
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
int pxManufacturerGroupGetNext
(
    struct tMANUFACTURERGROUP * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_MANUFACTURERGROUP *recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_MANUFACTURERGROUP*10+F_GetNext;
    recordp = (struct C_MANUFACTURERGROUP *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into MANUFACTURERGROUP_ZEIGER(recordp);
          break;
       case cCRSKONSIGPARTNERNR:
          EXEC SQL FETCH C2
          into MANUFACTURERGROUP_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into MANUFACTURERGROUP_ZEIGER(recordp);
          break;
    }

    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxManufacturerGroupEndBrowse                                     */
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
int pxManufacturerGroupEndBrowse
(
    int browseid
)
{
    functionnr = F_MANUFACTURERGROUP*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSKONSIGPARTNERNR:
          EXEC SQL CLOSE C2;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
