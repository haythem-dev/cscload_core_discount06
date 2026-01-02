#ifndef BSSG_H_DEFINED
#define BSSG_H_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

void CloseImsWgr( );

int IsBSSichG( long artikel_nr, char *wgr,
			   char *taxpfl, char *rezeptpfl, char *nichtuebergh, char *zuzahlung_ifa,
			   char *negativliste, char *tierarznei, char *nurkva, 
			   char *medizinprodukt, char *arzneimittel, char *rezepturarznei,
			   char *kontrazeptivum, char *impfstoff,
			   char *errmld );

long SetBSSichG( struct ZARTIKEL *z, int IsArtikelVorhanden, char *errmld );

long GetLifeStyle( char *errmld );

#ifdef __cplusplus
}
#endif

#endif /* BSSG_H_DEFINED */


