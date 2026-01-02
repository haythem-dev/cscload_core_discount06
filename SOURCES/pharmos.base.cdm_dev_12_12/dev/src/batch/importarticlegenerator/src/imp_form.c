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

#include "imp_form.h"

/* ---------------------------------------------------------------------- */
void  WriteProtHead1 ( FILE * fd ) 
{
	/* 1st headerline */
	char page[5];
	
	sprintf(page, "%d", pagecount);
	
	fputs("PROGRAMM:  IMPORTARTICLEGENERATOR           ", fd);
	fputs("LADEN IMPORT-ARTIKEL FUER D-BESORGER       ", fd);
	fputs("       DATUM: ", fd);
	fputs(daydate, fd); 
	fputs("     ZEIT: ", fd);
	fputs(daytime, fd);
	fputs("       BLATT:   ", fd);
	fputs(page, fd);
	fputs("\n", fd);
	fputs("\n", fd);

	fflush( fd );
}

/* ---------------------------------------------------------------------- */
int  OpenProtDatei	( FILE **fd, const char * const datei, const long date, const long time, char *errmld )
{
	*fd = fopen(datei, "wt");
		
	if (*fd == NULL)
	{
  	    sprintf( errmld, "Fehler beim Oeffnen des Protokoll-Files\n%s\n",
                        datei );
		
		return 1;
    }
	else
	{
		linecount = 0;
		pagecount = 1;
		sprintf(daytime, "%06ld", time);
		sprintf(daydate, "%ld", date);
	
		WriteProtHead1(*fd);
	}
    return 0;
}

/* ---------------------------------------------------------------------- */
void newLine(FILE * fd)
{
	/* linefeed*/
	fputs("\n", fd);
	linecount++;

	if ( linecount > LINES_PER_PAGE ) /*Seitenumbruch */
	{
		linecount = 0;
		pagecount++;
		//fputs("\n", fd);
		//fputs("\n", fd);
		//WriteProtHead1(fd);
		fflush( fd );
	}
}


/* ---------------------------------------------------------------------- */
void CloseProtDatei ( FILE *fd )
{
    fputs("                               XXXXXXXX  ENDE DER LISTE  XXXXXXXX", fd);
		
	if (fd != NULL)
	{
		fflush( fd );
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int  WriteProtZeile ( FILE * fd, const char * const msg )
{
	fputs(msg, fd);
	newLine(fd);
	return 0;
}

