#ifndef __ZART_GEN_INCLUDED_H__
#define __ZART_GEN_INCLUDED_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Default values*/
static const char* const VALUE_ZERO = "0";
static const char* const VALUE_ONE = "1";
static const char* const VALUE_FOUR = "4";
static const char* const VALUE_FIVE = "5";
static const char* const VALUE_SIX = "6";
static const char* const VALUE_BLANK = " ";
static const char* const VALUE_YES = "J";
static const char* const VALUE_NO = "N";

/* Datacare field values */
static const char* const CDC_KASSENZEICHEN_VNW = "VNW";
static const char* const CDC_KASSENZEICHEN_VN  = "VN ";
static const char* const CDC_KASSENZEICHEN_VTW = "VTW";
static const char* const CDC_KASSENZEICHEN_VT = "VT ";
static const char* const CDC_REZEPTZEICHEN_PLUSPLUS = "++";
static const char* const CDC_REZEPTZEICHEN_PLUS  = "+ ";
static const char* const CDC_REZEPTZEICHEN_SG  = "SG";
static const char* const CDC_REZEPTZEICHEN_S1  = "S1";
static const char* const CDC_REZEPTZEICHEN_S5  = "S5";
static const char* const CDC_ABGABEBES_P = "P "; 
static const char* const CDC_ABGABEBES_BLANK_T = " T"; 
static const char* const CDC_LAGERHINWEIS_K = "K"; 
static const char* const CDC_LAGERHINWEIS_E = "E"; 
static const char* const CDC_LAGERHINWEIS_T = "T"; 
static const char* const CDC_LAGERHINWEIS_M = "M";
static const char* const CDC_LAGERHINWEIS_U = "U";

void InitArtikelFields( struct ZARTIKEL *zart, const char* const user );
void InitZartaustriaFields( struct ZARTAUSTRIA *zart, const char* const user );

void DCSatzToArtWgr2( const struct ZDCART *spDCBuf, struct ZARTWG *spBuf);
void DCSatzToArtWgr4( const struct ZDCART *spDCBuf, struct ZARTWG *spBuf);

void DCSatzToArtikel( const struct ZDCART *spDCBuf, struct ZARTIKEL *spBuf,const struct  CCOMGROUPPROP *CComBuf,
                       int IsArtikelVorhanden, const struct ZARTWG *spBufWg, const struct ZARTWG *spBufZdkWgr );
void DCSatzToArtikelAustria( const struct ZDCART *spDCBuf, struct ZARTAUSTRIA *spBuf, struct ZARTIKEL *CZartBuf,
                       int IsArtikelVorhanden );
void DCSatzToPreis  ( const struct ZDCART *spDCBuf, struct ZARTPREIS *spBuf,const struct CCOMGROUPPROP *CComBuf,
                       int IsArtikelVorhanden );
int IsPreisChanged   ( struct ZDCART *spDCBuf );

int IsAnyNoValue     ( const struct ZDCART *spDCBuf );

int GetIsDCDeleted( const struct ZDCART *spDCBuf );
int GetIsDCReactivated( const struct ZDCART *spDCBuf );
int GetIsDCAH( const struct ZDCART *spDCBuf );

int TestEanNr( char *ean );

/*char Build_VERTRBIND_DC( struct ZDCART *spDCBuf );*/
/*char Build_KUEHLARTIKEL( struct ZDCART *spDCBuf );*/
/*char Build_VERFALL(  struct ZDCART *spDCBuf );*/ 
void Build_EINHEIT( char *ArtEinheit, const char *PgEinh, const char *PgMeng );


#ifdef __cplusplus
}
#endif

#endif /* ZART_GEN_INCLUDED */


