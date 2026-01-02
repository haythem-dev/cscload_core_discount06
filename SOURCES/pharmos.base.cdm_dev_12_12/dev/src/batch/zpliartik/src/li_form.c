/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest das LI-Format			                          *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef _WIN32
#include <unistd.h>
#include <libgen.h>
#endif

#include "li_form.h"

/* ---------------------------------------------------------------------- */
int  OpenLiDatei( FILE **fd, const char * const datei, char *errmld )
{
#ifndef _WIN32
	char systemcall [254];
	sprintf(systemcall, "dos2unix %s %s", datei, datei);
	system(systemcall); 
#endif
	
	*fd = fopen(datei, "rt");
	
	if (*fd == NULL)
	{
       sprintf( errmld, "Fehler beim Oeffnen der Datei\n%s",
                        datei );
       return 1;
    }
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseLiDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetLiZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, NO_SIGNS, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2;/*Dateiende*/
		else
			return 1;/*Error*/
	}
	return 0;
}
