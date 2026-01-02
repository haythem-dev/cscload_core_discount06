#include <ndefs.h>
#include <tnhifprices.h>


int pxNHIFPricesRead
(
    struct tNHIFPRICES* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tNHIFPRICES* recordp;
    EXEC SQL END DECLARE SECTION;

    recordp = record;

	EXEC SQL SELECT FIRST 1
		NHIFPRICES.HEALTHFUNDCODEHOSPITAL,
		NHIFPRICES.DATEVALIDFROM,
		NHIFPRICES.NHIFPRICE
	INTO
		:recordp->HealthFundCodeHospital,
		:recordp->DateValidFrom,
		:recordp->NHIFPrice
	FROM NHIFPRICES
	WHERE 
		HEALTHFUNDCODEHOSPITAL = :recordp->HealthFundCodeHospital AND
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
