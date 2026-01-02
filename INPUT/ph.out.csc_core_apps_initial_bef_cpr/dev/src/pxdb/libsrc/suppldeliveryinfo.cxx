#include <string.h>
#include "tsuppldeliveryinfo.h"
#include "pxdbfunc.h"
#include <ndefs.h>

/* Global variables */
extern int  functionnr;


/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxSupplDeliveryInfoRead                                */
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

int pxSupplDeliveryInfoRead
(
    struct tSUPPLDELIVERYINFO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tSUPPLDELIVERYINFO* recordp;
    char str[256];
    EXEC SQL END DECLARE SECTION;
	
	int retval = cDBXR_NORMAL;

    functionnr = F_SUPPLDELIVERYINFO * 10 + F_Read;
    recordp = record;

    strcpy(str, "SELECT ");
    strcat(str, "ID, ARTICLENO, AVAILABILITYINFO, CAST(TO_CHAR(PREDICTEDAVAILDATE, '%Y%m%d') AS INT), ");
	strcat(str, "CAST(TO_CHAR(AVAILABLEDATE, '%Y%m%d') AS INT) FROM SUPPLDELIVERYINFO WHERE ARTICLENO = ?");

    EXEC SQL PREPARE suppldeliveryinfo_query FROM :str;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    EXEC SQL DECLARE suppldeliveryinfo_c1 CURSOR FOR suppldeliveryinfo_query;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    EXEC SQL OPEN suppldeliveryinfo_c1 USING :recordp->ArticleNo;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    EXEC SQL FETCH suppldeliveryinfo_c1 INTO
		:recordp->Id,
        :recordp->ArticleNo,
        :recordp->AvailabilityInfo,
        :recordp->PredictedAvailDate,
        :recordp->AvailableDate;

    if (SQLCODE == 0)
    {
       retval = cDBXR_NORMAL;
    }
    else if (SQLCODE == 1)                /* found, but more than 1 exists */
    {
       retval = cDBXR_ISDUPLICATE;
    }
    else if (SQLCODE == 100)
    {
       retval = cDBXR_NOTFOUND;
    }
	else
	{
       retval = cDBXR_IOERROR;
	}
    EXEC SQL CLOSE suppldeliveryinfo_c1;
    EXEC SQL FREE suppldeliveryinfo_query;
    return retval;
}
