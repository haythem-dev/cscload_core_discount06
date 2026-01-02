/******************************************************************************/
/*     Hauptmodul: lorbas                                                     */
/*         Source: zeitstempel.c                                              */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 09.04.1996                                                 */
/*        Sprache: C                                                          */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: schreibt Zeitstempel auf Datei in Microsecunden            */
/*                                                                            */
/******************************************************************************/

#ifdef _NO_MEASUREMENT_POINT_
#undef _XCICS
#endif

/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <sys/time.h>
 #include <unistd.h>

 /*#include "define.h"*/
 #include "zeitstempel.h"

/*** STRUCTUR *****************************************************************/

 typedef struct timeval timeval_t;
 static timeval_t timev_Gs;

/*** DECLARATION **************************************************************/

 static int IstZeitMessung( void );

/*** SET-START ****************************************************************/

 #ifdef _XCICS
 void SetStart( void )
 {
   gettimeofday( &timev_Gs, NULL );
   return;
 }
 #else
 void SetStart( void )
 {
   return;
 }
 #endif

/*** SET-ENDE *****************************************************************/

 #ifdef _XCICS
 void SetEnd( char *file_pc, int line_i, char *function_pc )
 {
   timeval_t timev_s;
   static FILE *fp_PpsT;
   static char *filename_Ppc;
   char fileName[81];
   long dtsec_l;
   long dtusec_l;
   pid_t pid;

/*
   if ( IstZeitMessung() )
   {
*/
      if ( fp_PpsT == (FILE*)0 && ( ( filename_Ppc == (char*)0 ) &&
         ( ( filename_Ppc = (char *)getenv( "LORBASOUT" ) ) != (char*)0 ) ) )
          {
         pid = getpid();
         sprintf( fileName, "%s.%05ld", filename_Ppc, pid );
             if ( ( fp_PpsT = fopen( fileName, "a" ) ) == NULL )
                 {
                return;
                 }
          }
/*
   }
*/
   if ( fp_PpsT != (FILE*)0 )
      {
      gettimeofday( &timev_s, NULL );
      dtsec_l = timev_s.tv_sec - timev_Gs.tv_sec;
      if ( ( dtusec_l = timev_s.tv_usec - timev_Gs.tv_usec ) < 0 )
             {
             dtusec_l = 1000000 + dtusec_l;
             dtsec_l--;
             }
        /*
         * Ausgabedatei enthaelt :
         *
         *      Funktionsname
         *      Dateiname
         *      Zeilennummer
         *      Delta - Sekunden
         *      Delta - Microsekunden
         */
      fprintf( fp_PpsT, "%s|%s|%d|%ld|%ld|\n",
                   function_pc == (char*)0 ? "function ?" : function_pc,
                   file_pc,
                   line_i,
                   dtsec_l,
                   dtusec_l );
      fflush( fp_PpsT );
      }

   return;
 }
 #else
 void SetEnd( char *file_pc, int line_i, char *function_pc )
 {
   if ( file_pc && line_i && function_pc );     /*no warnings in compile*/
      return;
 }
 #endif


/*** Ist-Zeit-Messung ********************************************************/

 static int IstZeitMessung( void )
 {
   return 0;

/*
   FILE *dz;

   if ( ( dz = fopen( (char *)getenv( "LORBASOUT" ), "r" ) ) == NULL )
   {
          return 0;
   }

   fclose( dz );
   return 1;
*/
 }

/*** SET-ENDE *****************************************************************/
