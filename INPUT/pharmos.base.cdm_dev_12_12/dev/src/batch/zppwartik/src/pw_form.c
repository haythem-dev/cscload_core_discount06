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

#include "sql_pwartik.h"
#include "pnamcode.h"
#include "pw_form.h"

/* ---------------------------------------------------------------------- */
int OpenPwDatei( FILE **fd, const char * const datei, char *errmld )
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
void ClosePwDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetPwZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, NO_SIGNS, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2;/*Dateiende*/
		else
			return 1;/*Error*/
	}

	if (strlen(zeile) < 151 || strlen(zeile) > 152 )
		return 1;

	return 0;
}

/* ---------------------------------------------------------------------- */
void  WriteProtHead1 ( FILE * fd ) 
{
	/* 1st headerline */
	char page[5];
	char *temp = NULL;
	char dat[10];
	char tim[10];

	sprintf(page, "%d", pagecount);
	
	temp = daydate + 6;
	strcat(dat, temp);
	strcat(dat, ".");
	temp = daydate + 4;
	strncat(dat, temp, 2);
	strcat(dat, ".");
	temp = daydate + 2;
	strncat(dat, temp, 2);

	strncat (tim, daytime, 2);
	strcat(tim, ":");
	temp = daytime + 2;
	strncat (tim, temp, 2);
	
	fputs("PROGRAMM:  ZPPWARTIK        FIL: 83           ", fd);
	fputs("LADEN MASTER_OUT VON TEVA       ", fd);
	fputs("       DATUM: ", fd);
	fputs(dat, fd); 
	fputs("     ZEIT: ", fd);
	fputs(tim, fd);
	fputs("       BLATT:   ", fd);
	fputs(page, fd);
	fputs("\n", fd);
	fputs("\n", fd);
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
		fputs("\n", fd);
		fputs("\n", fd);
		WriteProtHead1(fd);
	}
}


/* ---------------------------------------------------------------------- */
void CloseProtDatei ( FILE *fd )
{
    fputs("                               XXXXXXXX  ENDE DER LISTE  XXXXXXXX", fd);
		
	if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int  WriteProtZeile ( FILE * fd )
{
	return 0;
}

