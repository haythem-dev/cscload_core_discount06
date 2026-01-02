#ifndef G_LIOART_INCLUDED
#define G_LIOART_INCLUDED

int LIOartFill( struct CLIOART *lio, struct CLIART *li, long tages_datum, char* errmld, short oArtExists );
void CopyPlausi( char *NB_PLAUSI_Cliart );

void ze_lcpy( char *s1, char ze, int lng );

#endif
