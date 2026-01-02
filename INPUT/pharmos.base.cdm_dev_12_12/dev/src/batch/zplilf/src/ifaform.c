/* ---------------------------------------------------------------------- *
 *                            IFAFORM.C                                   *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest das neue IFA-Format                             *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 02.04.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "asciidat.h"
#include "ifa_form.h"

int  OpenIfaDatei( int *fd, char *datei, char *errmld )
{
    int  status;

    status = AscOpenRd( datei, fd, 2048, &AscNormFkt );

    if ( status != RDA_OK )
    {
       sprintf( errmld, "Fehler %d beim Oeffnen der Datei\n%s",
                        status, datei );
       return 1;
    }
    return 0;
}

void CloseIfaDatei( int fd )
{
    AscClose( fd );
}

int RewindIfaDatei( int fd, char *datei, char *errmld )
{
    int status;
    status = AscRewind( fd );
    if ( status != 0 )
    {
       sprintf( errmld, "Fehler %d beim Rewind der Datei\n%s",
                        status, datei );
       return 1;
    }
    return 0;
}

int GetIfaZeile( int fd, char *zeile )
{
    if ( AscRead( zeile, fd ) == RDA_OK )
    {
/*    printf( "%s\n" , zeile );  */
      return 0;
    }
    else
      return 1;
}


