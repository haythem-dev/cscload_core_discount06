
/* ---------------------------------------------------------------------- *
 *                       P _ H I D R U K . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Protokoll Historie                                           *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  09.01.1999                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- includes --------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* static char* Druck_Prozedur = "cx -BE4D "; */
static char* Druck_Prozedur = "";

static char file_praefix[20];
static char file_datestamp[20];

static FILE *fdDruck = (FILE *) 0;

static char *CommandBuffer = NULL;

int CalledByMsdos( void );


void StorePrinfileName( char *bezeichnung )
{
   strcpy( file_praefix, bezeichnung );
}

void StorePrintfileDate ( char *bezeichnung )
{
	strcpy( file_datestamp, bezeichnung );
}

int OpenPrintFile( char *errmld )
{
	int  lng;
	char FileName[30];
	char verz[813];
#if !defined(WIN32)
	char *verz2;
#endif
	char *VerzName;

	if ( fdDruck != (FILE *) 0 )
		return 0;

	strcpy( FileName, file_praefix );
	if ( CalledByMsdos( ) )
	{
		if ( (int) strlen( FileName ) > 8 )
			FileName[8] = '\0';
	}

	strcat( FileName, ".hi" );

	if ( !CalledByMsdos( ) )
	{
		/* verz = getenv( "WWS" );
		if ( verz == NULL )
		{
	        strcpy( errmld, "Umgebungsvariable WWS nicht vorhanden" );
			return 1;
		} */

#if !defined(WIN32)
/*		strcpy (verz, getexecname());
		verz2 = dirname (verz); */

		verz2 = getcwd(verz, 813);

		strcpy (verz, verz2); 
		strcat (verz, "/../data/history/"); 
#endif

		lng = strlen( verz );
		CommandBuffer = malloc( strlen( Druck_Prozedur ) + lng + 
                             strlen( FileName ) + strlen ( file_datestamp ) + 1 );

		if ( CommandBuffer != NULL )
		{
			strcpy( CommandBuffer, Druck_Prozedur );
			strcat( CommandBuffer, verz );
/*			strcat( CommandBuffer, "/daten/historie/"  ); */
		}
   }
   else
   {
     CommandBuffer = malloc( strlen( Druck_Prozedur ) +
                             strlen( FileName ) + strlen ( file_datestamp ) + 1 );
     if ( CommandBuffer != NULL )
       strcpy( CommandBuffer, Druck_Prozedur );
   }

   if ( CommandBuffer == NULL )
   {
      strcpy ( errmld, "Protokoll: Fehler beim Allokieren des Verz.-Namens" );
      return 1;
   }

   strcat( CommandBuffer, FileName );
   strcat( CommandBuffer, file_datestamp );

   VerzName = CommandBuffer + strlen( Druck_Prozedur );

	fdDruck = fopen( VerzName, "r" );
	if ( fdDruck != (FILE *)0 )
	{
		fclose( fdDruck );
		strcpy ( errmld, "Protokolldatei / Liste bereits vorhanden!" );
		free ( CommandBuffer );
		CommandBuffer = NULL;
		return 1;         
	}
	
   fdDruck = fopen( VerzName, "w" );
   if ( fdDruck == (FILE *)0 )
   {
      sprintf( errmld,
               "Protokolldatei\n%s\nkann nicht geoeffnet werden",
               VerzName );
      free ( CommandBuffer );
      CommandBuffer = NULL;
      return -1;
   }
/* free ( VerzName );  */
   return 0;
}

int FlushPrintFile( )
{
   if ( fdDruck == (FILE *)0 ) return 0;

   if ( fflush( fdDruck ) == 0 )
     return 0;
   else
     return -1;
}

void ClosePrintFile( )
{
   if ( fdDruck != (FILE *)0 )
      fclose( fdDruck );
   fdDruck = (FILE *)0;

}

void WritePrintFile( char *buf, char *abschluss )
{
	if ( fdDruck != (FILE *)0 )
      fprintf( fdDruck, "%s%s", buf, abschluss );
}


char *GetCommandBuffer( )
{
  return CommandBuffer;
}

void FreeCommandBuffer( )
{
   if ( CommandBuffer != NULL )
      free ( CommandBuffer );
    CommandBuffer = NULL;
}

