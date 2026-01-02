
/* ---------------------------------------------------------------------- *
 *  						logfile.c   								  *
 * ---------------------------------------------------------------------- */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logfile.h"

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#include <libgen.h>
#endif

#define LOG_FILE   "zpconsig.log" 		   /* Name of Logile */

static char *gen_status( int status )
{
	if (status == S_INFO)   /* INFO */
	   return "I";
	if (status == S_ERROR)    /* ERROR */
	   return "E";
	if (status == S_WARNING)   /* WARNING */
	   return "W";

	return "?";
}

int write_logfile( int status, char *function, char *strmsg)
{
	char *logfile;
	FILE *fp;
	struct tm *localtime();
	struct tm *timeval;
	time_t hour1;
	time_t hour2;
	char log_fullname[812 + 1];
	char *LOG_PATH; 
	char data[5000];

#ifdef WIN32
	long  pid;
	pid = _getpid();
	char strDel[] = { "\\" };
#else
	pid_t pid;
	pid = getpid();
	char strDel[] = { "/" };
#endif
	logfile = LOG_FILE;
	hour1   = time(&hour2);
	timeval = localtime(&hour1);
	  
	if ((LOG_PATH = getenv("LOG_PATH")) == (char *)NULL)
		strcpy(log_fullname, ".");
	else
		strcpy(log_fullname, LOG_PATH);

	strcat(log_fullname, strDel );
	strcat(log_fullname, logfile);

	sprintf(data, "%s %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %-8.8s %s\n",
		gen_status(status),
		timeval->tm_mday,
		timeval->tm_mon + 1,
		timeval->tm_year % 100,
		timeval->tm_hour,
		timeval->tm_min,
		timeval->tm_sec,
		pid,
		function,
		strmsg);

	fp = fopen(log_fullname, "a");
	if ( fp != NULL )
	{
		// into file
		fprintf(fp, data);			
		fclose(fp);
	}
	else
	{
		return 1;
	}
	return 0;
}
