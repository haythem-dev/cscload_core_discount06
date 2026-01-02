/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die Galdat-Datei		                          *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 08.06.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/zartprei.h>

#include "sql_zplfzart.h"

#include "zplfzart_form.h"

/* ---------------------------------------------------------------------- */
int  OpenMWEDatei( FILE **fd, const char * const datei, char *errmld )
{
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
void CloseMWEDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetMWEZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, MAX_LENGTH_MWE, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2; /* Dateiende */
		else
			return 1; /* Error */
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int  OpenEANDatei( FILE **fd, const char * const datei, char *errmld )
{
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
void CloseEANDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetEANZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, MAX_LENGTH_EAN, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2; /* Dateiende */
		else
			return 1; /* Error */
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int  OpenHealthInsuranceDatei( FILE **fd, const char * const datei, char *errmld )
{
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
void CloseHealthInsuranceDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetHealthInsuranceZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, MAX_LENGTH_HI, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2; /* Dateiende */
		else
			return 1; /* Error */
	}
	return 0;
}


