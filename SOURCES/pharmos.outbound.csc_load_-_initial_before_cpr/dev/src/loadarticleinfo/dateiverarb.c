/*** INCLUDE ******************************************************************/

#include <stdio.h>
#include <dirent.h>
#include <errno.h>                                     
#include <string.h>
#include <stdlib.h>
#include "dateiverarb.h"

/********************************************************************************/
/* DEFINE */
/********************************************************************************/
#define OK                 0
#define NO                 0
#define YES                1
#define ERROR             -1
#define INSERT             1
#define NOT_FOUND          1
#define FILE_NOT_FOUND     1

/*** GLOBALE ******************************************************************/

char infodirectory[257];
char infofilename[180];
char newinfofilename[180];
static FILE *inputfile;
struct loaddata
{
	long PZN;
	char infofilename[81];
	struct loaddata *nextpos;
};
static struct loaddata *actpos;
static struct loaddata *newpos;
static struct loaddata *startpos = NULL;

/****************************************************************************/
/* static int GetDir()														*/
/****************************************************************************/

int InfoGetDir()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "InfoGetDir";
    char *env;
	int len;
	char huelse[81];
	DIR *dirp;
	struct dirent *direntp;

	env = getenv( "DATA_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( infodirectory, "%s", env );

	if((dirp = opendir(infodirectory)) == NULL)
	{
		return FILE_NOT_FOUND;
	}
	while ( (direntp = readdir(dirp)) != NULL)
	{
		if (!strncmp(direntp->d_name,"Article",7))
		{
		}
		else if (!strncmp(direntp->d_name,"article",7))
		{
		}
		else
		{
			continue;
		}
		for(len=7;len<strlen(direntp->d_name);len++)
		{
			if(direntp->d_name[len] == '.') break;
		}
		if(len >= strlen(direntp->d_name)) continue;
		len = len-7;
		newpos = (struct loaddata *)malloc(sizeof(struct loaddata));
		memcpy(huelse,direntp->d_name+7,len);
		huelse[len] = '\0';
		newpos->PZN = atol(huelse);
		strcpy(newpos->infofilename,direntp->d_name);
		newpos->nextpos = NULL;
		if (startpos == NULL)	/* erster Satz in Liste */
		{
			startpos = newpos;
			actpos = newpos;
			continue;
		}
		actpos->nextpos = newpos;
		actpos = newpos;
	}                                                    
	closedir(dirp);
	actpos = startpos;
	return OK;
}

/****************************************************************************/
/* static int GetFile()														*/
/****************************************************************************/

int InfoGetFile()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "InfoGetFile";

	if(actpos == NULL) return -1;
	sprintf(infofilename,"%s/%s",infodirectory,actpos->infofilename);
	if((inputfile = fopen( infofilename, "r" )) == NULL)
	{
		return ERROR;
	}
	return actpos->PZN;
}

/****************************************************************************/
/* static int ReadFile()													*/
/****************************************************************************/

int InfoReadFile(char *daten)
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "InfoReadFile";

	if ((fgets(daten , 1024 , inputfile)) == NULL)
	{
		return ERROR;
	}
	return OK;
}

/****************************************************************************/
/* static int ClearFile()													*/
/****************************************************************************/

int InfoClearFile()
{
	/*************************/
	/* Variablen-Deklaration */
	/*************************/
	char*	fun = "InfoClearFile";

	sprintf(newinfofilename,"%s/old/%s",infodirectory,actpos->infofilename);
	actpos = actpos->nextpos;
	return rename(infofilename,newinfofilename);

}
