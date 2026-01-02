#ifndef G_DCOART_INCLUDED
#define G_DCOART_INCLUDED

int DCOartFill( struct ZDCOART *dco, struct ZDCART *dc, long tages_datum, char* errmld );
void CopyPlausi( char *NB_PLAUSI_Zdcart );

int IsChangeArtText15 ();

void ze_lcpy( char *s1, char ze, int lng );

#endif
