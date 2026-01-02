/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application

    Database functions

    FUNCTIONS:

        pxToteInfoInsert       Insert record


REVISION HISTORY

27 Oct 2014 V1.00 REV 00 written by Martin Zoephel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* ttoteinfo */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "ttoteinfo.h"
#include <pxenv.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxToteInfoInsert                                      */
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
int pxToteInfoInsert
(
	struct tTOTEINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_TOTEINFO * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_TOTEINFO*10+F_Insert;
    recordp = (struct C_TOTEINFO *) record;

    EXEC SQL insert into ToteInfo(datainfotype,toteno,ordernoibt,branchnoibt,pickingstartdatetime,branchno,tourid)
    VALUES ( :recordp->DATAINFOTYPE, :recordp->TOTENO, :recordp->ORDERNOIBT, :recordp->BRANCHNOIBT, :recordp->PICKINGSTARTDATETIME,
    		:recordp->BRANCHNO, :recordp->TOURID);

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
