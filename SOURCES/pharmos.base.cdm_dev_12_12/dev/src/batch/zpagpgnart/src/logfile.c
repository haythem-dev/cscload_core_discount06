
/* ---------------------------------------------------------------------- *
 *  						logfile.c   								  *
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

#define LOG_FILE   "zpagpgnart" 		   /* Name der Logdatei */

int IsLog = 1;

static char *gen_status(int status)
{
	if (status == S_HINWEIS)   /* HINWEIS */
		return "INF";
	if (status == S_FEHLER)    /* FEHLER (schwer) */
		return "ERR";
	if (status == S_WARNUNG)   /* WARNUNG */
		return "WRN";
	if (status == S_DEBUG)	   /* DEBUG INFO */
		return "DBG";
	return "?";
}

int write_logfile(int status, char *Anwendung, char *text)
{
	if (IsLog)
	{
		char *datei;
		FILE *fp;
		struct tm *localtime();
		struct tm *zeit;
		time_t hour1;
		time_t hour2;
		char log_file[812 + 1];
#if !defined(WIN32)
		char *LOG_PATH;
#endif
		/* doesn't compile under win64, has no effect
		long time(); */

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
		zeit = localtime(&hour1);


#if defined(WIN32)
		strcpy(log_file, "c:\\temp\\");
#else
		LOG_PATH = getcwd(log_file, 813);

		strcpy(log_file, LOG_PATH);
		strcat(log_file, "/../log/");
#endif

		sprintf(log_file, "%s%s_%02d_%02d_%02d.log", log_file, datei, zeit->tm_year % 100, zeit->tm_mon + 1, zeit->tm_mday);
		fp = fopen(log_file, "a");
		if (fp != NULL)
		{
			fprintf(fp,
				"%s:%02d.%02d.%02d-%02d:%02d:%02d:pid=%05ld:ProgMode=%s:%s\n",
				gen_status(status),
				zeit->tm_mday,
				zeit->tm_mon + 1,
				zeit->tm_year % 100,
				zeit->tm_hour,
				zeit->tm_min,
				zeit->tm_sec,
				pid,
				Anwendung,
				text);

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

int write_logdatei(int status, char *Anwendung, char *text, char *datei)
{
	if (IsLog)
	{
		FILE *fp;
		struct tm *localtime();
		struct tm *zeit;
		time_t hour1;
		time_t hour2;
		char log_file[812 + 1];

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

		hour1 = time(&hour2);
		zeit = localtime(&hour1);

		strcpy(log_file, "../log/");
		strcat(log_file, datei);

		fp = fopen(log_file, "a");
		if (fp != NULL)
		{
			char info[80];
			size_t lng;
			int i;
			lng = strlen(text);

			if (lng < LOGD_LNG)
			{
				strcpy(info, text);
			}
			else
			{
				memcpy(info, text, LOGD_LNG);
				info[LOGD_LNG] = '\0';
			}

			fprintf(fp,
				"%s:%02d.%02d.%02d-%02d:%02d:%02d:pid=%05ld:ProgMode=%s:%s\n",
				gen_status(status),
				zeit->tm_mday,
				zeit->tm_mon + 1,
				zeit->tm_year % 100,
				zeit->tm_hour,
				zeit->tm_min,
				zeit->tm_sec,
				pid,
				Anwendung,
				info);

			i = LOGD_LNG;
			while (i < lng)
			{
				memcpy(info, &text[i], LOGD_LNG);
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

void displ_logfile(int status, char *text)
{
	char info[80];
	size_t lng;
	int i;
	lng = strlen(text);

	if (lng < DISP_LNG)
	{
		strcpy(info, text);
	}
	else
	{
		memcpy(info, text, DISP_LNG);
		info[DISP_LNG] = '\0';
	}

	printf("%s %s\n",
		gen_status(status),
		info);

	i = DISP_LNG;
	while (i < lng)
	{
		memcpy(info, &text[i], DISP_LNG);
		info[DISP_LNG] = '\0';
		printf("     %s\n", info);
		i += DISP_LNG;
	}
}

int  wrap_logging(int status, char *Anwendung, char *text) {
	static int logLevel = 0;
	int answer = 0;

	if (NULL == Anwendung && NULL == text) {
		logLevel = status;
	}
	else
	{
		if (status <= logLevel) {
			answer = write_logfile(status, Anwendung, text);
		}
	}
	return answer;
}
