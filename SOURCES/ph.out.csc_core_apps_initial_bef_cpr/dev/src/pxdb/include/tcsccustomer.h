#ifndef __PP_CSCCUSTOMER_H_
#define __PP_CSCCUSTOMER_H_

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tCSCCUSTOMER
{
	long		IDFNR;					/* kunde.idfnr */
	short		FILIALNR;				/* kunde.filialnr */
	char		NAMEAPO[40+1];           /* Name Apotheke */
	char		NAMEINHABER[30+1];       /* Name Inhaber */
	char		STRASSE[30+1];           /* Strasse */
	char		ORT[30+1];               /* Ort */
	char		POSTLEITZAHL[10+1];      /* Postleitzahl */
	char		TELNR[20+1];             /* Telefonnummer */
	char		TELNRDAFUE[20+1];        /* Telefonnummer Dafue */
	char		FAXNR[25+1];             /* Faxnummer */
	short		ANREDEKZ;                /* Kennzeichen Anrede */
	long		IMSBEZIRKNR;             /* IMS Bezirksnummer */
	char		KDGRUPPE[2+1];           /* Kundengruppe */
	long		PERSONALNRVERTR;         /* Personalnummer Vertreter */
	char		STDAUFKOBUART[4+1];      /* kunde.stdaufkobuart */
	long		TOURENKIPPZEIT;			 /* kunde.tourenkippzeit */
	char		KZSPRACHE[2+1];          /* Sprachkennzeichen*/
	char        DAFUESYSTEM[3 + 1];      /* DAFUE Systemschlüssel */

//kundeschalter
	char		SKDVERSANDAPO;           /* SKd Versnad Apotheke*/
	char		SKDSEPAUFT;              /* kundeschalter.skdsepauft */
    short       SKDFMD;                  /* kundeschalter.skdfmd */
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

/* CSCCustomer */
int CSCCustomerRead( struct tCSCCUSTOMER* record, const char* dbname );

#ifdef __cplusplus
}
#endif


#endif   // GUARD
