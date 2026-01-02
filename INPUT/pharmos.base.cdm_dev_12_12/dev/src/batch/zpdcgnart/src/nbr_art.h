#ifndef  NBR_ART_INCLUDED
#define  NBR_ART_INCLUDED

/* --- SET ISOLATION-Error SE -------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase( void );
long OpenBase( const char* const spDb, char *spErrmld );
void KaufmRunden( double *wert, int stellen );
void InitRestArtikel( struct ZARTIKEL *spArt, const char* const spUser );

/* Protokoll */
long DC_OpenProtokol( long nr, char *verzeichnis, char *errmld );
long DC_ProtokolLoe( struct ZARTIKEL *altart, char *errmld );
long DC_ProtokolNeu( struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis,struct ZARTAUSTRIA *neuaustria,struct ZARTWG *neuwgr,
                      char *errmld );
long DC_ProtokolAen( struct ZARTIKEL *altart, struct ZARTPREIS *altpreis, struct ZARTAUSTRIA *altaustria, struct ZARTWG *altwgr,
                     struct ZARTIKEL *neuart, struct ZARTPREIS *neupreis, struct ZARTAUSTRIA *neuaustria, struct ZARTWG *neuwgr,
                      char *errmld );
void DC_CloseProtokol( int ok, char *errmld );

#endif
