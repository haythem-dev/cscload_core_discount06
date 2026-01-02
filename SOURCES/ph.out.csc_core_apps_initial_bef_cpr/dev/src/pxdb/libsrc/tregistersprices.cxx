#include <ndefs.h>
#include <tregistersprices.h>

/* Global variables */
//extern int  functionnr;

int pxRegistersPricesRead
(
    struct tREGISTERSPRICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tREGISTERSPRICES* recordp;
    EXEC SQL END DECLARE SECTION;

    recordp = record;

	EXEC SQL SELECT FIRST 1
		REGISTERSPRICES.MINISTRYPRODUCTCODE,
		REGISTERSPRICES.DATEVALIDFROM,
		REGISTERSPRICES.MAXWHOLESALEPRICE,
		REGISTERSPRICES.REFERENCEPRICE
	INTO
		:recordp->MinistryProductCode,
		:recordp->DateValidFrom,
		:recordp->MaxWholeSalePrice,
		:recordp->ReferencePrice
	FROM REGISTERSPRICES
	WHERE 
		MINISTRYPRODUCTCODE = :recordp->MinistryProductCode AND
		DATEVALIDFROM <= TO_CHAR(TODAY, '%Y%m%d')::INT
	ORDER BY DATEVALIDFROM DESC;

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
