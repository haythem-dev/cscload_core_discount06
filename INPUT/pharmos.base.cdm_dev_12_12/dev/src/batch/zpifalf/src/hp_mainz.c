/* ---------------------------------------------------------------------- *
 *                            HP_MAINZ.C                                  *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Manipuliert die Protokoll-Datei                     *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 09.07.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>

/* --------- Prototype ------------- */

void ProgUsage  ( char *buf );
long ProgAuswahl( int argc, char *argv[], char *buf );

/* ---------------- UebertragungsPuffer ------------ */

static char ret_buf[1000];

/* ---------- Abbruch-Signal------------------------------------- */

   int sig_accepted = 0;

/* ---------------- main-Programm ------------------ */

#if defined(MSDOS) || defined(WIN32)

void main ( int argc, char *argv[] )
{
   long s;
   HNMP handle;

      if ( ( s = ViaEshuOpen( &handle, "zdev1", "uiserv" ) ) == 0 )
      {
         if ( argc > 1 )
            s = ProgAuswahl( argc - 1, &argv[1], ret_buf );
         else
         {
            s = 1;
            ProgUsage( ret_buf );
         }
         NmpCloseHandle ( handle );
      }
      else
      {
         strcpy( ret_buf, "Pipe nicht eroeffnet: " );
         strcat( ret_buf, DynErrmld() );
      }

   if ( s == 0  )
      printf( "%s\n", ret_buf );
   else
      printf( "%s\n", ret_buf );

   if ( s == 0  )
      exit( 0 );
   else
      exit( 1 );
}

#else

#include <sys/types.h>
#include <sys/stat.h>

/* --- Signal-Behandlung ------------------------------------------- */

#include <signal.h>


static void intrpt_term( int sig )
{
    signal( SIGTERM, SIG_IGN );
    sig_accepted = 1;
}

static void signal_beh( void )
{
    signal(SIGTERM,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
/*  signal(SIGCHLD,SIG_IGN);  */   /* weglassen wegen h_system( "mv .." ) */
}

/* ------------ LogFile ------------------------------ */

#include "logfile.h"

#define MAX_PROG 30
static char program[MAX_PROG + 1];              /* Programmname */

void LogOut( int status, char *str )
{
   char *str1;
   char ze;
   while ( *str )
   {
     str1 = str;
     while ( *str && *str != '\n' ) str++;
     ze = *str;
     *str = '\0';
     write_logfile( status, 0, program, str1 );
     *str = ze;
     if ( ze == '\n' ) str++;
   }
}

static void LogOutParam( int status, int anz, char *str[] )
{
   char *str1;
   int lng;
   int i;

   lng = 0;
   for ( i = 0; i < anz; i++ )
	   lng += strlen( str[i] );

   str1 = malloc( lng + anz + 1 );
   if ( str1 == NULL )
	   return;

   *str1 = '\0';
   for ( i = 0; i < anz; i++ )
   {
	   strcat( str1, str[i] );
	   if ( i < anz - 1 )
		   strcat( str1, " " );
   }

   write_logfile( status, 0, program, str1 );
   free ( str1 );
}

static void GetProgram( char *prog, char *str )
{
   int i;
   int found;
   found = 0;
   i = strlen( str ) - 1;

   while ( i >= 0 && !found )
   {
      found = str[i] == ':' || str[i] == '\\' || str[i] == '/';
      if ( !found ) i--;
   }
   i++;
   if ( strlen( &str[i] ) <= MAX_PROG )
      strcpy( prog, &str[i] );
   else
   {
      memcpy( prog, &str[i], MAX_PROG );
      prog[MAX_PROG] = '\0';
   }
}


/* --- Main-Programm ----------------------------------------------- */

void main ( int argc, char *argv[] )
{
    int  lng;
    int  anz_arg;
    int  lokal;
    long s;
	char logmsg[100];

    GetProgram( program, argv[0] );              /* Programmname */

    /* --- Signal-Behandlung */
    signal_beh();

    lng = PipwRead ( argc, argv, ret_buf, 0 );   /* nichts lesen */
    if ( lng == -1 )
    {
        anz_arg = argc;     /* Programm wurde lokal aufgerufen */
        lokal = 1;
    }
    else
    {
        anz_arg = argc - 1;  /* von PipwRead wurde ein Zusatzparam. anghaengt */
                             /* argc darf nicht veraendert werden !!!!! */
        lokal = 0;
    }

	
	strcpy( logmsg, "--------------------------------------------------" );
	LogOut( S_HINWEIS, logmsg );
    strcpy( logmsg, "START" );
	LogOut( S_HINWEIS, logmsg );

    if ( anz_arg > 1 )
    {
        sig_accepted = 0;
        signal( SIGTERM, intrpt_term );
		LogOutParam( S_HINWEIS, anz_arg - 1, &argv[1] );
        s = ProgAuswahl( anz_arg - 1, &argv[1], ret_buf );
    }
    else
    {
        s = 1;
        ProgUsage( ret_buf );
    }

    if ( !lokal )
        PipwWrite( argc, argv, ret_buf, strlen( ret_buf) );

/*	else */
    if ( s == 0 )
    {
        printf( "%s\n", ret_buf );
        LogOut( S_HINWEIS, ret_buf );
    }
    else
    {
        printf( "%s\n", ret_buf );
        LogOut( S_FEHLER, ret_buf );
    }

	strcpy( logmsg, "ENDE" );
	LogOut( S_HINWEIS, logmsg );
	
	exit( s );
}

#endif  /* MSDOS */
