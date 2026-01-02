/* includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>

static char *spProgname = "zplignart";

/* --------- Prototype ------------- */

void ProgUsage  ( const char *spBuf, const char *spProgname);
long ProgSelect( int argc, char *argv[], char *spBuf, const char *spProgname );

/* ---------------- buffer ------------ */

static char ret_buf[1000];

/* ---------- Signal------------------------------------- */

   int sig_accepted = 0;

/* ---------------- main-Program ------------------ */

#if defined (_WIN32)

void main ( int argc, char *argv[] )
{
   long lRetCode;
   HNMP handle;

      if ( ( lRetCode = ViaEshuOpenEx( &handle, "zdev21", "uiserv", 55260 ) ) == 0 )
      {
         if ( argc > 1 )
            lRetCode = ProgSelect( argc - 1, &argv[1], ret_buf, spProgname );
         else
         {
            lRetCode = 1;
            ProgUsage( ret_buf, spProgname );
         }
         NmpCloseHandle ( handle );
      }
      else
      {
         strcpy( ret_buf, "Pipe nicht eroeffnet: " );
         strcat( ret_buf, DynErrmld() );
      }

   if ( lRetCode == 0  )
      printf( "%s\n", ret_buf );
   else
      printf( "%s\n", ret_buf );

   if ( lRetCode == 0  )
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

void LogOut( int iStatus, char *spStr )
{
   if( *spStr )
     write_logfile( iStatus, 0, program, spStr );
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

static void GetProgram( char *spProg, char *spStr )
{
   int i;
   int iFound;
   iFound = 0;
   i = strlen( spStr ) - 1;

   while ( i >= 0 && !iFound )
   {
      iFound = spStr[i] == ':' || spStr[i] == '\\' || spStr[i] == '/';
      if ( !iFound ) i--;
   }
   i++;
   if ( strlen( &spStr[i] ) <= MAX_PROG )
      strcpy( spProg, &spStr[i] );
   else
   {
      memcpy( spProg, &spStr[i], MAX_PROG );
      spProg[MAX_PROG] = '\0';
   }
}


/* --- Main-Programm ----------------------------------------------- */

void main ( int argc, char *argv[] )
{
    int  iLng;
    int  anz_arg;
    int  iLocal;
    long lRetCode;

    GetProgram( program, argv[0] );              /* Programmname */

    /* --- Signal-Behandlung */
    signal_beh();

    iLng = PipwRead ( argc, argv, ret_buf, 0 );   /* nichts lesen */
    if ( iLng == -1 )
    {
        anz_arg = argc;  
        iLocal = 1;
    }
    else
    {
        anz_arg = argc - 1;  /* von PipwRead wurde ein Zusatzparam. anghaengt */
                             /* argc darf nicht veraendert werden !!!!! */
        iLocal = 0;
    }

	LogOut( S_HINWEIS, "--------------------------------------------------" );
	LogOut( S_HINWEIS, "START" );

    if ( anz_arg > 1 )
    {
        sig_accepted = 0;
        signal( SIGTERM, intrpt_term );
		LogOutParam( S_HINWEIS, anz_arg - 1, &argv[1] );
        lRetCode = ProgSelect( anz_arg - 1, &argv[1], ret_buf,spProgname );
    }
    else
    {
        lRetCode = 1;
        ProgUsage( ret_buf, spProgname );
    }

    if ( !iLocal )
        PipwWrite( argc, argv, ret_buf, strlen( ret_buf) );

/*	else */
    if ( lRetCode == 0 )
    {
        printf( "%s\n", ret_buf );
        LogOut( S_HINWEIS, ret_buf );
    }
    else
    {
        printf( "%s\n", ret_buf );
        LogOut( S_FEHLER, ret_buf );
    }

    LogOut( S_HINWEIS, "ENDE" );

    if ( lRetCode == 0  )
		exit( 0 );
    else
		exit( 1 );
}

#endif  /* MSDOS */
