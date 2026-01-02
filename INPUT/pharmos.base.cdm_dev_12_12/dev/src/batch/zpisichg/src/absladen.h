
#ifndef G_ABSCHLAGLADEN_INCLUDED
#define G_ABSCHLAGLADEN_INCLUDED

#include "zifaoabschlag.h"

long  AbschlagLaden( long artikel_nr, long tages_datum, int wegfall, 
					 struct ZIFAOABSCHLAG *oifa,
					 char *user, char *errmld );
long Open_All_FDs( char *errmld );

long Close_All_FDs( );

#endif   /* G_ABSCHLAGLADEN_INCLUDED */

