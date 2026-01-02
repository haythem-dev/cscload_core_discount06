
#include <stdio.h>
#include <time.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "tm.h"
#include "allg.h"
#include "texte.h"
#include "seralog.h"
#ifndef WIN32
#include <unistd.h>
#include <dirent.h>                                     
#include <errno.h>                                     
#endif
#include "param.h"
static char directory[50];

#define UNUSED(x) (void)(x)

int AaseraLes_dir(struct SERALOGH *a, char *error_msg)
{
    UNUSED(error_msg);

#ifdef WIN32
    UNUSED(a);
	return 0;
#else
static int fst = 1;
static int neu = 1;
static long m_IDF;
static long m_Zeit;
static long m_Datum;
static char m_Tid[4+1];
char zw_AUFTR[10];
static char  serapath[256 + 1];
char  *SERALOG;
long zw_IDF;
long zw_Zeit;
char zw_Tid[4+1];
char huelse[30];                                      
int count;                                      
DIR *dirp;
struct sera
{
	long Zeit;
	long IDF;
	char Tid[4+1];
	char AUFTR[10];
	struct sera *lastpos;
	struct sera *nextpos;
};
static struct sera *actpos;
static struct sera *newpos;
static struct sera *endpos = NULL;
static struct sera *startpos = NULL;
static struct dirent *direntp;
if (neu)   /* beim ersten mal seralog-path versorgen */
{		  
   	neu = 0;
	if ( ( SERALOG = (char *)getenv("SERALOG")) == NULL )
      strcpy( serapath, "/data/seralog" );
      else
      strcpy( serapath, SERALOG );
}
   
if (fst) /* beim ersten mal oder bei neu deklarieren */
{
    fst = 0;
	m_IDF = a->IDF;
	m_Zeit = a->ZEIT;
	m_Datum = a->DATUM;
	strcpy(m_Tid,a->TID);
	sprintf(directory,"%s/ORD%08ld",serapath,m_Datum);

	if((dirp = opendir(directory)) == NULL)
	{
		fst = 1;
		return 1;
	}
	while ( (direntp = readdir(dirp)) != NULL)           
	{
		if (direntp->d_name[0] != 'O') continue;
		memcpy(huelse,direntp->d_name+1,7);
		huelse[7] = '\0';
		zw_IDF = atol(huelse);
		memcpy(huelse,direntp->d_name+12,6);
		huelse[6] = '\0';
		zw_Zeit = atol(huelse);
		memcpy(huelse,direntp->d_name+8,4);
		huelse[4] = '\0';
		strcpy(zw_Tid,huelse);
		if(strlen(direntp->d_name) == 18) zw_AUFTR[0] = '\0'; 
		else memcpy(zw_AUFTR,direntp->d_name+19,9);
		if(m_Zeit != 0 && zw_Zeit < m_Zeit) continue;
		if(m_IDF != 0 && zw_IDF != m_IDF) continue;
		if(m_Tid[0] != ' ' && (strcmp(zw_Tid,m_Tid))) continue;
		newpos = (struct sera *)malloc(sizeof(struct sera));
		newpos->IDF = zw_IDF;
		newpos->Zeit = zw_Zeit;
		strcpy(newpos->Tid,zw_Tid);
		strcpy(newpos->AUFTR,zw_AUFTR);
		newpos->lastpos = NULL;
		newpos->nextpos = NULL;
		if (startpos == NULL)	/* erster Satz in Liste */
		{
			startpos = newpos;
			endpos = newpos;
			continue;
		}
		actpos = endpos;
		for(;;)
		{
			if(newpos->Zeit > actpos->Zeit)  /* danach einfuegen */
			{
				newpos->lastpos = actpos;
				newpos->nextpos = actpos->nextpos;
				actpos->nextpos = newpos;
				if(endpos == actpos) endpos = newpos; /* am Ende ? */
				else
				{
					actpos = newpos->nextpos;
					actpos->lastpos = newpos;
				}
				break;
			}
			if(actpos->lastpos == NULL)    /* anfang der Liste ? */
			{
				actpos->lastpos = newpos;
				newpos->nextpos = actpos;
				startpos = newpos;
				break;
			}
			actpos = actpos->lastpos;      /* vorwaerts in Liste */
		}
	}                                                    
	closedir(dirp);
	actpos = startpos;
	if(startpos == NULL) return 1; /* keine Sätze vorhanden */
	a->IDF = actpos->IDF;
	a->ZEIT = actpos->Zeit;
	strcpy(a->TID,actpos->Tid);
	strcpy(a->AUFTR,actpos->AUFTR);
	return 0;
}

if(a->FETCH_REL == 0)   /* close cursor */
{
	fst = 1;
	if(startpos == NULL) return 1;
	for(actpos=startpos;;)
	{
		newpos=actpos->nextpos;
		free(actpos);
		if(newpos == NULL)
		{
			endpos = NULL;
			startpos = NULL;
			break;
		}
		actpos=newpos;
	}
    return 1;
}

if(startpos == NULL) return 1; /* keine Sätze vorhanden */
if(a->FETCH_REL < 0)  /* zurueckpositionieren */
{
	for(count = a->FETCH_REL;count < 0;count++)
	{
		if(actpos->lastpos == NULL) return 1;
		actpos = actpos->lastpos;
	}
	a->IDF = actpos->IDF;
	a->ZEIT = actpos->Zeit;
	strcpy(a->AUFTR,actpos->AUFTR);
	strcpy(a->TID,actpos->Tid);
	return 0;
}
else	  /* vorwaertspositionieren */
{
	for(count = a->FETCH_REL;count > 0;count--)
	{
		if(actpos->nextpos == NULL) return 1;
		actpos = actpos->nextpos;
	}
	a->IDF = actpos->IDF;
	a->ZEIT = actpos->Zeit;
	strcpy(a->TID,actpos->Tid);
	strcpy(a->AUFTR,actpos->AUFTR);
	return 0;
}
#endif
}

int AaseraLes_data(struct SERALOGD *d, char *error_msg)
{
static int fst = 1;
char filename[80];
static FILE *fp;
UNUSED(error_msg);
if (fst) /* beim ersten mal oder bei neu deklarieren */
{
    fst = 0;
	AllgEntfSpaces(d->DATEN);
	sprintf(filename,"%s/%s",directory,d->DATEN);
	if((fp = fopen( filename, "r" )) == NULL)
	{
		fst = 1;
		return 1;
	}
}

if ((fgets(d->DATEN , L_SERALOG_DATEN , fp)) == (char *)0)
{
	fst = 1;
	fclose( fp );
	return 1;
}
d->DATEN[strlen(d->DATEN)-1] = '\0';
return 0;
}
