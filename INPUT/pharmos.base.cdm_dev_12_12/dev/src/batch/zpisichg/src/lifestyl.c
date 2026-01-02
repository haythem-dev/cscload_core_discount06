/*----------------------------------------------------------------*
 *      lifestyl.c                                                *
 *----------------------------------------------------------------*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <libscsvoodoo.h>

#include "lifestyl.h"


/* --- LifeStyle -------------------------------------- */


#define MAX_LIFE 3000

static long lifestyle[MAX_LIFE + 1];

long GetLifeStyle( char *errmld )
{
	int fd;
	int i;
	long s;
	s = SqlOpenCs( &fd, "select artikel_nr from zlifestyle order by artikel_nr" );
	if ( s != 0 )
	{
		sprintf( errmld , "Fehler bei SqlOpenCs(zlifestyle) (%ld)", s);
		return s;
	}
	i = 0;
	while ( s == 0 && i < MAX_LIFE )
	{
		s = SqlFetch( fd, 1, &lifestyle[i], NULL );
		if ( s == 0 )
			i++;
	}

	SqlCloseCs( fd );

	if ( s == 0 )
	{
		sprintf( errmld , "Max. LifeStyle-Artikel = %d erreicht", i );
		return -1;
	}

	if ( s != 100 )
	{
		sprintf( errmld , "Fehler bei SqlFetch(zlifestyle) (%ld)", s);
		return s;
	}
/*	printf( "Anzahl Lifestyle: %d\n", i );  */
	lifestyle[i] = -1;
	return 0;
}

int IsLifeStyle( long artikel_nr )
{
	int i;
	i = 0;
	while ( lifestyle[i] != -1 )
	{
		if ( artikel_nr == lifestyle[i]  ) return 1;
		i++;
	}
	return 0;
}
