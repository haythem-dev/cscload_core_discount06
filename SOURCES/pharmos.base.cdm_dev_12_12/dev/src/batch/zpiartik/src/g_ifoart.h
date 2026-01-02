#ifndef G_IFOART_INCLUDED
#define G_IFOART_INCLUDED


#include <zifaoart.h>

/* ---------------------------------- */

#define P_IFAOART          ZIFAOART
#define PROJ_P_IFAOART     "*"
#define REL_P_IFAOART      FROM_ZIFAOART

/* ----------------------------------- */

int TestIfaOartInsertMode( char *errmld );


long ReadIfaOart  ( struct P_IFAOART *ifa, long artikel_nr, char *errmld );
long InsertIfaOart( struct P_IFAOART *ifa, char *errmld );
long UpdateIfaOart( struct P_IFAOART *ifa, char *errmld );
long DeleteIfaOart( char *errmld );

long Open_IfaOart_FDs( char *errmld );
void Close_IfaOart_FDs();

int  IfaOartFill( struct P_IFAOART *ifa, sSatzArt *pSart, long tages_datum, char *errmld );

long IfaOartAendere( sSatzArt *pSart, struct P_IFAOART *ifa, struct P_IFAOART* old_ifa,
                     long tages_datum, long Pzn, char Ssatz, char LoeKenn, 
                     long *anz_upd, long *anz_del, long *anz_ins,
                     char *errmld );

int GetIfaPzn    ( long *pzn,     sSatzArt *pSart, char *errmld );
int GetIfaPznNF  ( long *pzn,     sSatzArt *pSart, char *errmld );
int GetIfaStatus ( char *ssatz,   sSatzArt *pSart, char *errmld );
int GetLoeschKenn( char *LoeKenn, sSatzArt *pSart, char *errmld );

int GetA01SGEPDM( char *Kenn, sSatzArt *pSart, char *errmld );
int GetA01SAEPDM( char *Kenn, sSatzArt *pSart, char *errmld );
int GetA01SAVPDM( char *Kenn, sSatzArt *pSart, char *errmld );
int GetA01SZBV  ( char *Kenn, sSatzArt *pSart, char *errmld );
int GetA01SUVP  ( char *Kenn, sSatzArt *pSart, char *errmld );
int GetA01SAB130A  ( char *Kenn, sSatzArt *pSart, char *errmld );


char *GetRefToIfaOartPlausi();

long sel_ArtNoByCode	( const long code, char* errmld );
int TestPruefZiffer7 ( long zahl );

int IsPruefzifferOk( long zahl );

#endif  /* G_IFOART_INCLUDED */

