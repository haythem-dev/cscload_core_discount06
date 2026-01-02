#ifndef GUARD_TARTACCT_H
#define GUARD_TARTACCT_H


/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the artikelkonto table                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsArtikelKonto
{
	cCRSARTIKELKONTO_Default	= 1,
	cCRSARTIKELKONTO_Beleg		= 2
} tCRSID_ARTIKELKONTO;


/*****************************************************************************/
/*  Artikel Konto                                                            */
/*  Artikel Bewegungs Tabelle                                                */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tARTIKELKONTO
{
    long          LfdNr;                        /* Laufende Nummer */
    short         FilialNr;                     /* Filialnummer */
    long          ArtikelNr;                    /* Artikelnummer */
    char          BewegungsArt;                 /* Bewegungs Art */
    long          Menge;                        /* Menge */
    long          BelegNr;                      /* Beleg Nummer */
    long          Uid;                          /* Benutzer Nummer */
    long          IDFNr;                        /* Kundennummer IDF */
    long          MengeNeu;                     /* Menge Neu */
    long          ZeitUnix;                     /* Zeit Unix */
    long          BewegungSchluessel;           /* Bewegungs Schluessel */
    long          StockReserved;                /* Stock reserved */
    short         MoveType;                     /* Move Type */
    long          PosNr;                        /* Positionsnummer Kundenauftrag */
    char          BelegArt[2+1];                /*Beleg Art - AuftragsArt*/
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


int pxRArtikelKontoRead         ( struct tARTIKELKONTO* record, const char* computer);
int pxRArtikelKontoReadLock     ( struct tARTIKELKONTO* record, const char* computer);
int pxRArtikelKontoUpdate       ( struct tARTIKELKONTO* record, const char* computer);
int pxRArtikelKontoInsert       ( struct tARTIKELKONTO* record, const char* computer);
int pxRArtikelKontoDelete       ( struct tARTIKELKONTO* record, const char* computer);
int pxRArtikelKontoStartBrowse  ( struct tARTIKELKONTO* record, const char* computer, int browseid);
int pxRArtikelKontoGetNext      ( struct tARTIKELKONTO* record);
int pxRArtikelKontoEndBrowse    ( );


#ifdef __cplusplus
}
#endif

#endif // GUARD_TARTACCT_H
