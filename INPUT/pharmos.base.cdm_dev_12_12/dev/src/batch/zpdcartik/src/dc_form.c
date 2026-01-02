/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest das DC-Format			                          *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#if defined (_WIN32)
#else
#include <unistd.h>
#include <libgen.h>
#endif

#include <voodoo_table_header/zdcart.h>

#include "dc_form.h"

/* ---------------------------------------------------------------------- */
int  OpenDCDatei( FILE **fd, const char * const datei, char *errmld )
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
void CloseDCDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetDCZeile( FILE * fd, char *zeile )
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

/* ---------------------------------------------------------------------- */
void  WriteProtHead1 ( FILE * fd ) 
{
	/* 1st headerline */
	char page[5];
	sprintf(page, "%d", pagecount);

	fputs("PROGRAMM:  ZPDCARTIK       ", fd);
	fputs("EINGESPIELTE SAETZE IN ZDCART           ", fd);
	fputs("SEITE:   ", fd);
	fputs(page, fd);
	fputs("       DATUM:   ", fd);
	fputs(daydate, fd);
	fputs("\n", fd);
	fputs("\n", fd);
}

/* ---------------------------------------------------------------------- */
void  WriteProtHead2 ( FILE * fd )
{
	/* 2nd headerline */
	fputs(" DATUM   CODE  PZN   EINHEIT   ARTIKELBEZEICHNUNG           ",fd);
	fputs(" DFO  LCODE   GEP        AEP        AVP     ",fd);
	fputs("\n", fd);
	fputs("\n", fd);
}


/* ---------------------------------------------------------------------- */
int  OpenProtDatei	( FILE **fd, const char * const datei, const long date, char *errmld )
{
	*fd = fopen(datei, "wt");
	if (*fd == NULL)
	{
       /* 
	   #ifndef _WIN32
		char systemcall [254];
		sprintf(systemcall, "mkdir %s", verzeichnis);
		system(systemcall); 

		*fd = fopen(datei, "wt");
		if (*fd == NULL)
		{
	  #endif*/
	   sprintf( errmld, "Fehler beim Oeffnen des Protokoll-Files\n%s",
                        datei );

	  /* #ifndef _WIN32
		}
		#endif*/
       return 1;
    }
	else
	{
		linecount = 0;
		pagecount = 1;
		sprintf(daydate, "%ld", date);

		WriteProtHead1(*fd);
		WriteProtHead2(*fd);
	}
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseProtDatei ( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int  WriteProtZeile ( FILE * fd, const struct ZDCART * const dc )
{
	char val[64];
	long lTmp;
	
	sprintf(val, "%ld", dc->DC_DATUMGUELTIGAB);
	fputs(val, fd);
	fputs(SPACE, fd);

	fputs(dc->DC_AECODE, fd);
	fputs(SPACE, fd);

	sprintf(val, "%ld", dc->DC_ARTIKEL_NR);
	fputs(val, fd);
	fputs(SPACE, fd);

	fputs(dc->DC_EINH_MENGE, fd);
	fputs(" ", fd);
	fputs(dc->DC_EINH_EINHEIT, fd);
	fputs(SPACE, fd);

	fputs(dc->DC_ARTIKELTEXT, fd);
	fputs(SPACE, fd);

	fputs(dc->DC_DARREICHFORM, fd);
	fputs(SPACE, fd);

	fputs(dc->DC_CODE_LIEFERANT, fd);
	fputs(SPACE, fd);

	lTmp = (long) (dc->DC_GEP * 100);
	sprintf(val, "%09d", lTmp);
	fputs(val, fd);
	fputs(SPACE, fd);

	lTmp = (long) (dc->DC_AEP * 100);
	sprintf(val, "%09d", lTmp);
	fputs(val, fd);
	fputs(SPACE, fd);

	lTmp = (long) (dc->DC_AVP * 100);
	sprintf(val, "%09d", lTmp);
	fputs(val, fd);	

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
		WriteProtHead2(fd);
	}

	return 0;
}

