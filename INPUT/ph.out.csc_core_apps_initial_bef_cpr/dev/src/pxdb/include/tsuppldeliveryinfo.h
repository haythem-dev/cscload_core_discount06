#ifndef GUARD_TSUPPLDELIVERYINFO_H
#define GUARD_TSUPPLDELIVERYINFO_H


/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the SUPPLDELIVERYINFO table                           */
/*----------------------------------------------------------------------------*/
//typedef enum CrsArtikelKonto
//{
//	cCRSARTIKELKONTO_Default	= 1,
//	cCRSARTIKELKONTO_Beleg		= 2
//} tCRSID_ARTIKELKONTO;


/*****************************************************************************/
/*  SUPPLDELIVERYINFO                                                        */
/*  Voraussichtiliches Lieferdatum Tabelle                                   */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tSUPPLDELIVERYINFO
{
    long          Id;                           /* Laufende Nummer */
    long          ArticleNo;                    /* Artikelnummer */
	char          AvailabilityInfo[254 + 1];
    long          PredictedAvailDate;
    long          AvailableDate;
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

int pxSupplDeliveryInfoRead     ( struct tSUPPLDELIVERYINFO* record);

#ifdef __cplusplus
}
#endif

#endif // GUARD_TSUPPLDELIVERYINFO_H
