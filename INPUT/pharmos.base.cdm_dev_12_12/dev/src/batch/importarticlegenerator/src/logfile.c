
/* ---------------------------------------------------------------------- *
 *                          logfile.c                                     *
 * ---------------------------------------------------------------------- */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logfile.h"

#if defined (MSDOS) || defined (WIN32)
#include <process.h>
#else
#include <unistd.h>
#include <libgen.h>
#endif

#define LOG_FILE   "importarticlegenerator.log"           /* Name der Logdatei */

int IsLog = 1;

static char *gen_status( int status )
{
	if (status == S_HINWEIS)   /* HINWEIS */
       return "H";
    if (status == S_FEHLER)    /* FEHLER (schwer) */
       return "F";
    if (status == S_WARNUNG)   /* WARNUNG */
       return "W";

    return "?";
}

int write_logfile( int status, short filial_nr, char *Anwendung, char *Str )
{
	if (IsLog)
    {
		char *datei;
		FILE *fp;
		struct tm *localtime();
		struct tm *zeit;
		long hour1;
		long hour2;
		char log_file[812 + 1];
#if !defined(WIN32)
		char *LOG_PATH; 
#endif
		long time();

#ifdef MSDOS
		long  pid;
		pid = getpid();
#elif WIN32
		long  pid;
		pid = _getpid();
#else
		pid_t pid;
		pid = getpid();
#endif
		datei = LOG_FILE;
		hour1 = time(&hour2);
		zeit  = localtime(&hour1);

/*		if ((LOG_PATH = getenv("LOG_PATH")) == (char *)NULL)
			strcpy(log_file, ".");
		else
			strcpy(log_file, LOG_PATH); 

		strcat( log_file, "/" ); */

#if defined(WIN32)
		strcpy( log_file, "c:\\temp\\" );
#else
/*		strcpy (log_file, getexecname());
		LOG_PATH = dirname (log_file); */

		LOG_PATH = getcwd(log_file, 813);

		strcpy (log_file, LOG_PATH); 
		strcat (log_file, "/../log/"); 
#endif

		strcat( log_file, datei );
		fp = fopen(log_file, "a");
		if ( fp != NULL )
        {
			fprintf(fp,
              "%s %.2hd %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %-8.8s %s\n",
              gen_status( status ),
              filial_nr,
              zeit->tm_mday,
              zeit->tm_mon + 1,
              zeit->tm_year%100,
              zeit->tm_hour,
              zeit->tm_min,
              zeit->tm_sec,
              pid,
              Anwendung,
              Str);

			fclose(fp);
        }
		else 
			return 1;
    }
	else
		return 2;

   return 0;
}
