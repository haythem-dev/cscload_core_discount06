#ifndef __ZART_GEN_INCLUDED_H__
#define __ZART_GEN_INCLUDED_H__

#ifdef __cplusplus
extern "C" {
#endif


	/* Default values*/
static const char* const VALUE_ZERO = "0";
static const char* const VALUE_ONE = "1";
static const char* const VALUE_BLANK = " ";
static const char* const VALUE_YES = "Y";
static const char* const VALUE_NO = "N";


void InitArtikelFields( struct ZARTIKEL *zart, const char* const user );

void InitZartswitzerlandFields( struct ZARTSWITZERLAND *spZartSwitz, const char* const user );

void InitCSafetyDataSheetFields( struct CSAFETYDATASHEET *spCSafetyDataSheet, const char* const user );

void LISatzToArtikel( struct CLIART *spLIBuf, struct ZARTIKEL *spBuf, struct ZARTIKEL *spBufOld, struct CARTICLELANG *spBufLang, int IsArtikelVorhanden );

void LISatzToArtikelSwitz( const struct CLIART *spLIBuf, struct ZARTSWITZERLAND *spBuf, struct ZARTIKEL *CZartBuf, int IsArtikelVorhanden );

void LISatzToCSafetyDataSheet( const struct CLIART *spLIBuf, struct CSAFETYDATASHEET *spBuf, struct ZARTIKEL *CZartBuf, int IsArtikelVorhanden );

int LISatzToPreis  ( const struct CLIART *spLIBuf, struct ZARTPREIS *spBuf, struct ZARTIKEL *bufArt, struct ZARTSWITZERLAND *bufSwitz, int IsArtikelVorhanden );

void LISatzToCSdsLang(const struct CLIART *spLIBuf, struct CSDSLANG *spBuf);
void LISatzToCodeATC( const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf );
void LISatzToCodeBAG( const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf );
void LISatzToCodeCDSO(const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf );
void LISatzToCodeGtin14(const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf );

void LISatzToArtWgr2( const struct CLIART *spLIBuf, struct ZARTWG *spBuf );
void LISatzToArtWgr5( const struct CLIART *spLIBuf, struct ZARTWG *spBuf );
void LISatzToArtWgrA( const struct CLIART *spLIBuf, struct ZARTWG *spBuf );
	
int IsPreisChanged   ( struct CLIART *spLIBuf, struct ZARTPREIS *spPreisCurrent );
int IsNotChanged	 ( const struct CLIART *li, const int pos );  

int IsAnyNoValue     ( const struct CLIART *spLIBuf );

int TestEanNr( char *ean );

int Trim (char *s);

void Build_EINHEIT( char *ArtEinheit, char *PgEinh, const double PgMeng, const short Multiplier );


typedef enum { LANG_EN, LANG_IT, LANG_FR, LANG_DEFAULT } CSDSLANGTYPE;


#ifdef __cplusplus
}
#endif

#endif /* ZART_GEN_INCLUDED */


