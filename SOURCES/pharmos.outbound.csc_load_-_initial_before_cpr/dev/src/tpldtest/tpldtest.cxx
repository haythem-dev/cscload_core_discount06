/*** INCLUDE ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <libtpld/hsystfkt.h>
#include <dirent.h>                                     
#include <errno.h>

 #include "pplib/allg.h"
 #include "libtpld/qtime.h"


EXEC SQL include sqlca; 
EXEC SQL include sqltypes; 

/* #undef NULL  */ 

#define DEBUG_SECTION      if ( debug_enabled ) { 
#define END_DEBUG_SECTION  } 
#define OK                 0 
#define NO                 0 
#define YES                1 
#define ERROR             -1 
#define INSERT             1 
#define NOT_FOUND          1 
#define FILE_NOT_FOUND     1 
#define WARNING           -2 
#define HINW             'H' 
#define FEHL             'F' 
#define RIO_EOF          110 
#define STR_NULL         "+000000000000000" 
#define STR_NULL2        "+00000,00" 
#define BLANC            ' ' 
#define MAX_TRANSAKTION     300 
#define SQLISAM         sqlca.sqlerrd[1]         /* Sql-Cisam-Fehler       */ 
#define L_TEXT             81
#define FEHLER             'F' 

 #define ERROR_MSG( x )      if ( SQLCODE < 0 ) { PrintMsg( fun, x, FEHLER ); \
				 return ERROR; }

typedef struct timeval timeval_t; 


exec sql begin declare section;
char str[2048];
long lDatumEreignis;
long lDatumAktuell;
long lZeitEreignis;
long datedelphone;
int iFilialNr = 0;
char folderpath[255] = { 0 };
exec sql end declare section;


/***** PRINT-MSG ************************************************************/

 void PrintMsg( char *fun, char *error_msg, char mld )
 {
	 static int fst = 1;
   FILE *fp;
   struct tm *localtime();
   struct tm *zeit;
   long hour1;
   pid_t pid;
   long time();
   char logFile[100];
  
   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );

   sprintf( logFile, "./tpldtest.log"  );
   if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
      return;

   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d "
               "pid=%05ld %.8s %s %s->%d/%d\n",
            mld,
            99,
            zeit->tm_mday,
            zeit->tm_mon + 1,
            (zeit->tm_year+1900)%100,
            zeit->tm_hour,
            zeit->tm_min,
            zeit->tm_sec,
            pid,
            "tpldauftr",
            fun,
            error_msg,
         SQLCODE,
         SQLISAM );

   fclose(fp);
}

static int GetCSVImportFolder()
{

	char *fun = "GetCSVImportFolder";
	char *error_msg;

	exec sql select auspraegung INTO :folderpath FROM parameter WHERE programmname = 'KSC' and zweck = 'CSVIMPORTSERVER';
	ERROR_MSG("from parameter");

	return 0;
}

static char *trimwhitespace(char *str)
{
	char *end;

	// Trim leading space
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator character
	end[1] = '\0';
	return str;

}

/***** DELETE-OLD CSV***********************************************************/
static int DeleteOldCSV(const int iNumberOfDay)
{
	char meld[81];
	int rc;
	char szCommand[512];
	char ausgabe[101];

	timeval_t timev_s;
	timeStr   *time_DueDate, *time_FileDate;
	long lDueDate;
	long lFileDate;

	if (GetCSVImportFolder() != OK)
	{
		return -1;
	}
	PrintMsg(meld, "CSV folder gelesen", 'H');

	gettimeofday(&timev_s, NULL);
	timev_s.tv_sec = timev_s.tv_sec - (24 * 60 * 60 * iNumberOfDay); /*7776000 == 90 Tage in Sec         */

	time_DueDate = (timeStr *)TimeOfDay(timev_s.tv_sec);
	sprintf(str, "%04d%02d%02d", time_DueDate->year, time_DueDate->mon, time_DueDate->day);
	lDueDate = atol(str);


	DIR *dirp;
	static struct dirent *direntp;
	char *fpath;
	fpath = trimwhitespace(folderpath);
	PrintMsg(meld, "trimwhitespace done", 'H');

	if ((dirp = opendir(fpath)) == NULL)
	{
		sprintf(ausgabe, " opendir fehler; rc = %d", errno);
		PrintMsg(meld, ausgabe, 'F');
		return 1;
	}

	while ((direntp = readdir(dirp)) != NULL)
	{
		char file_name[2048];
		struct stat attr;
		struct tm * time_;

		if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
		{
			continue;
		}
		else
		{
			sprintf(file_name, "%s%s", folderpath, direntp->d_name);
		}

		stat(file_name, &attr);

		time_FileDate = (timeStr *)TimeOfDay(attr.st_mtime);
		sprintf(str, "%04d%02d%02d", time_FileDate->year, time_FileDate->mon, time_FileDate->day);
		lFileDate = atol(str);

		if (lDueDate >= lFileDate)
		{
			sprintf(szCommand, "rm -f %s", file_name);
			if ((rc = h_system(szCommand)) < 0)
			{
				sprintf(ausgabe, " Loeschen der Datei %s nicht moeglich; rc = %d", file_name, rc);
				PrintMsg(meld, ausgabe, 'F');
			}
			else
			{
				sprintf(ausgabe, " Datei %s gelöscht ", file_name);
				PrintMsg(meld, ausgabe, 'H');
			}
		}
	}

	return OK;

}


int main(int argc, char **argv)
{
	long days = 140;
	if (argc > 1)
		days = atol(argv[1]);
		
	exec sql database ode21@ode21_shm;
	DeleteOldCSV(days);
}
