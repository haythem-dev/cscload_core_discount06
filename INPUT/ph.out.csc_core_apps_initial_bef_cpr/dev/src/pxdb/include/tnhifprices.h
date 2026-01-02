#ifndef GUARD_TNHIFPRICES_H
#define GUARD_TNHIFPRICES_H

/*****************************************************************************/
/*  NHIFPRICES Table                                                         */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tNHIFPRICES
{
    char          HealthFundCodeHospital[25 + 1];
	long          DateValidFrom;
	double        NHIFPrice;
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/*----------------------------------------------------------------------------*/
/* forward declarations for pxverbund                                         */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int pxNHIFPricesRead(struct tNHIFPRICES* record);

#ifdef __cplusplus
}
#endif

#endif   // GUARD_TNHIFPRICES_H
