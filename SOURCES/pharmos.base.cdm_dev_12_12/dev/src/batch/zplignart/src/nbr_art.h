#ifndef  NBR_ART_INCLUDED
#define  NBR_ART_INCLUDED

/* --- SET ISOLATION-Error SE -------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase( void );
long OpenBase( const char* const spDb, char *spErrmld );
void KaufmRunden( double *wert, int stellen );
void InitRestArtikel( struct ZARTIKEL *spArt, const char* const spUser );

/* Protokoll */
long LI_OpenProtokol( long nr, char *verzeichnis, char *errmld );
long LI_ProtokolLoe( struct ZARTIKEL *altart, char *errmld );
long LI_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,struct ZARTSWITZERLAND *neuswitz, struct EAN *spNeuEan, char *errmld );
long LI_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis, struct ZARTSWITZERLAND *altswitz, struct EAN *spAltEan,
                     struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTSWITZERLAND *neuswitz, struct EAN *spNeuEan, char *errmld );
void LI_CloseProtokol( int ok, char *errmld );

#endif
