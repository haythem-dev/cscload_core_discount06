
/* ---------------------------------------------------------------------- *
 *                          logfile.c                                     *
 * ---------------------------------------------------------------------- */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logfile.h"

#if defined (_WIN32)
#include <process.h>
#else
#include <unistd.h>
#include <libgen.h>
#endif

#define LOG_FILE   "zplfzart.log"           /* Name der Logdatei */

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
#if !defined(_WIN32)
		long hour1;
		long hour2;
		long time();
#else
		time_t hour1;
		time_t hour2;
		time_t time();
#endif
		char log_file[812 + 1];
#if !defined(_WIN32)
		char *LOG_PATH; 
#endif

#ifdef _WIN32
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

#if defined(_WIN32)
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

#define LOGD_LNG  46

int write_logdatei( int status, short filial_nr, char *Str, char *datei )
{
	if (IsLog)
    {
		FILE *fp;
		struct tm *localtime();
		struct tm *zeit;
#if !defined(_WIN32)
		long hour1;
		long hour2;
		long time();
#else
		time_t hour1;
		time_t hour2;
		time_t time();
#endif
		char log_file[812 + 1];
/*		char *LOG_PATH; */

#ifdef _WIN32
		long  pid;
		pid = _getpid();
#else
		pid_t pid;
		pid = getpid();
#endif

		hour1 = time(&hour2);
		zeit  = localtime(&hour1);

/*		if ((LOG_PATH = getenv("LOG_PATH")) == (char *)NULL)
	        strcpy(log_file, ".");
		else
			strcpy(log_file, LOG_PATH);

		strcat( log_file, "/" ); */

		strcpy( log_file, "../log/");
		strcat( log_file, datei );

		fp = fopen(log_file, "a");
		if ( fp != NULL )
        {
			char info[80];
			int lng;
			int i;
			lng = strlen( Str );

			if ( lng < LOGD_LNG )
            {
				strcpy( info, Str );
            }
			else
            {
				memcpy( info, Str, LOGD_LNG );
				info[LOGD_LNG] = '\0';
            }

			fprintf(fp,
              "%s %.2hd %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s\n",
              gen_status( status ),
              filial_nr,
              zeit->tm_mday,
              zeit->tm_mon + 1,
              zeit->tm_year%100,
              zeit->tm_hour,
              zeit->tm_min,
              zeit->tm_sec,
              pid,
              info);

			i = LOGD_LNG;
			while ( i < lng )
	        {
				memcpy( info, &Str[i], LOGD_LNG );
				info[LOGD_LNG] = '\0';
				fprintf(fp, "%-33.33s%s\n", " ", info);
				i += LOGD_LNG;
			}

			fclose(fp);
		}
	}

	return 0;
}

#define DISP_LNG 74

void displ_logfile ( int status, short filial_nr, char *Str )
{
	char info[80];
    int lng;
    int i;
    lng = strlen( Str );

    if ( lng < DISP_LNG )
    {
		strcpy( info, Str );
    }
    else
	{
		memcpy( info, Str, DISP_LNG );
        info[DISP_LNG] = '\0';
    }

    printf( "%s %.2hd %s\n",
            gen_status( status ),
            filial_nr,
            info );

    i = DISP_LNG;
    while ( i < lng )
    {
        memcpy( info, &Str[i], DISP_LNG );
        info[DISP_LNG] = '\0';
        printf( "     %s\n", info );
        i += DISP_LNG;
    }
}
