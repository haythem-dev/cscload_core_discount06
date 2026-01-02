#ifndef GUARD_TREGISTERSPRICES_H
#define GUARD_TREGISTERSPRICES_H

/*****************************************************************************/
/*  REGISTERSPRICES Table                                                    */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tREGISTERSPRICES
{
    char          MinistryProductCode[25 + 1];
	long          DateValidFrom;
	double        MaxWholeSalePrice;
	double        ReferencePrice;
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

int pxRegistersPricesRead(struct tREGISTERSPRICES* record);

#ifdef __cplusplus
}
#endif

#endif   // GUARD_TREGISTERSPRICES_H
