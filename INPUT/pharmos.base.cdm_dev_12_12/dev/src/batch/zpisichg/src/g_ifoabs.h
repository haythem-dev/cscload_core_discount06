#ifndef G_IFOABS_INCLUDED
#define G_IFOABS_INCLUDED


#include "zifaoabschlag.h"
#include "ifa_satz.h"


/* ----------------------------------- */

int TestIfaOabschlagInsertMode( char *errmld );


long ReadIfaOabschlag  ( struct ZIFAOABSCHLAG *ifa, long artikel_nr, char *errmld );
long InsertIfaOabschlag( struct ZIFAOABSCHLAG *ifa, char *errmld );
long UpdateIfaOabschlag( struct ZIFAOABSCHLAG *ifa, char *errmld );
long DeleteIfaOabschlag( char *errmld );

long Open_IfaOabschlag_FDs( char *errmld );
void Close_IfaOabschlag_FDs();

int  IfaOabschlagFill( struct ZIFAOABSCHLAG *ifa, sSatzArt *pSart, long tages_datum, char *errmld );

long IfaOabschlagAendere( sSatzArt *pSart, struct ZIFAOABSCHLAG *ifa,
                     long tages_datum, long Pzn, char Ssatz, 
                     long *anz_upd, long *anz_del, long *anz_ins,
                     char *errmld );

int GetIfaPzn    ( long *pzn,     sSatzArt *pSart, char *errmld );
int GetIfaStatus ( char *ssatz,   sSatzArt *pSart, char *errmld );

char *GetRefToIfaOabschlagPlausi();

int IsPruefzifferOk( long zahl );

int IsNoValue( int pos );

#endif  /* G_IFOABS_INCLUDED */

