/* ---------------------------------------------------------------------- *
 *                       F E B _ P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Uebernahme Festbetraege                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  20.10.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wr_prot.h"

#include "abs_prot.h"


/* --- Schnittstelle ------------------------------------ */

long Abs_OpenProtokol( char *datei, int mit_protokol, char *errmld )
{
   return OpenFile( datei, "abs", mit_protokol, 1, errmld );
}

void Abs_CloseProtokol( )
{
   CloseFile( );
}

long Abs_Protokol( char *buf, char *errmld )
{
	WriteFile( buf, "\n" );
	if ( FlushFile() != 0 )
	{
		strcpy( errmld, "Fehler beim Schreiben in die Protokolldatei" );
		return -1;
	}
	return 0;
}

