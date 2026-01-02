/* aafil.cxx */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tm.h"
#include "allg.h"
#include "ppgeneric.h"
#include "texte.h"
#include "filinf.h"
#include "alterfil.h"
#include "zeitart.h"
#include "usertexte.h"
#include "aepwd.h"
#include "param.h"
#include "auftrag.h"
#include "controlling.h"
#include "parameter_change_log_defs.h"
#include "parameter_change_logging.h"
#include "parameterchangelog.h"

#define UNUSED(x) (void)(x)

EXEC SQL include sqlca;
EXEC SQL include sqltypes; 

/*  GLOBALE C-VARIABLEN  */
/* Filialnummer für Log-Einträge   */
long ppFILIAL_NR = 0;

EXEC SQL BEGIN DECLARE SECTION;
short FilialNr;
short sUserVz;
long lUID;
int FREMDSPRACHE;
char ARTIKELZENTRAL_SPRACHE[20];
char ARTIKELINDEX_SPRACHE[20];
char ARTIKELSEKBEZ_SPRACHE[20];
char ARTIKELSELECT_SPRACHE[20];
short sVzNr;
long lKundenNr;
char cKdauftragArt[3];
char cCountry[3];
EXEC SQL END DECLARE SECTION;

int AafilDel_zeitart(struct ZEITARTV *d, char *error_msg);
int AafilIns_zeitarten(struct ZEITARTV *d, char *error_msg);

int AafilWriteOldVersion(struct FILINF *d, char *error_msg)
{
   if(d->FILIALNR) ;     /* damit der Compiler nicht meckert */
   sprintf(error_msg, "Client-Version ist ungueltig! 0621 8505 492"); /* nase */
   return -1;
}

int AafilGetversion(struct PARVERSION *d, char *error_msg)
{
        strcpy(error_msg, "");     /* damit der Compiler nicht meckert */
        sprintf(d->VERSNR, "8.33");
        return 0;
}

int AafilGetdatetime(struct TM *d, char *error_msg)
{
        struct tm t;
        AllgGetTM(&t);
        d->DATUM = AllgGetDate();
        d->ZEIT = AllgGetTime();
        d->WTAG = (long)t.tm_wday; /* 0 = Sonntag   */
        d->JTAG = (long)t.tm_yday; /* 0 = 1. Januar */
        strcpy(error_msg, "");     /* damit der Compiler nicht meckert */
        return 0;
}

int AafilLogParameter(char *Tabelle, struct PARAUFBEARB *d, struct PARAUFBEARB *old, char *error_msg)
{

	EXEC SQL BEGIN DECLARE SECTION;
	struct PARAUFBEARB   *neu;
	struct PARAUFBEARB   *alt;
	parameterchangelogS log, *plog;
	parameter_change_log_defsS logdef, *plogdef;
	char buffer[1048];
	EXEC SQL END DECLARE SECTION;

	neu = d;
	alt = old;
	plog = &log;
	plogdef = &logdef;

	log.DATE_CHANGE = AllgGetDate();
	log.TIME_CHANGE = AllgGetTime();
	log.BRANCHNO = alt->FILIALNR;
	log.USER_BRANCHNO = sUserVz;
	log.USER_ID = lUID;
	strcpy(log.KEYOFCHANGE, " ");

	strcpy(buffer, "select ");
	strcat(buffer, PARAMETER_CHANGE_LOG_DEFS_PLISTE);
	strcat(buffer, " from parameter_change_log_definition ");
	strcat(buffer, "where TABLE_NAME = '");
	strcat(buffer, Tabelle);
	strcat(buffer, "'");

	EXEC SQL PREPARE sel_defs FROM : buffer;
	if (sqlca.sqlcode < 0)
	{
		sprintf(error_msg, " AafilLogParameter prepare select %ld",
			sqlca.sqlcode);
		return -1;
	}
	exec sql declare SelDefs Cursor for sel_defs;
	if (sqlca.sqlcode < 0)
	{
		sprintf(error_msg, " AafilLogParameter declare SelDefs %ld",
			sqlca.sqlcode);
		return -1;
	}
	EXEC SQL open SelDefs;
	if (sqlca.sqlcode < 0)
	{
		sprintf(error_msg, " AafilLogParameter open SelDefs %ld",
			sqlca.sqlcode);
		return -1;
	}

	for (;;)
	{
		EXEC SQL fetch SelDefs into PARAMETER_CHANGE_LOG_DEFS_ZEIGER(plogdef);
		if (sqlca.sqlcode < 0)
		{
			sprintf(error_msg, " AafilLogParameter fetch SelDefs %ld",
				sqlca.sqlcode);
			return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND)
		{
			break;
		}
		AllgEntfSpaces(logdef.FIELD_NAME);
		AllgEntfSpaces(logdef.FIELD_TYPE);
		AllgEntfSpaces(logdef.PARAMETER_NAME);
		AllgEntfSpaces(logdef.PARAMETER_TABLE);
		if (!strcmp(logdef.FIELD_NAME, "durchlaufnormal"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->DURCHLAUFNORMAL != alt->DURCHLAUFNORMAL)
				{
					sprintf(log.OLD_VALUE, "%d", alt->DURCHLAUFNORMAL);
					sprintf(log.NEW_VALUE, "%d", neu->DURCHLAUFNORMAL);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "durchlaufeilbote"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->DURCHLAUFEILBOTE != alt->DURCHLAUFEILBOTE)
				{
					sprintf(log.OLD_VALUE, "%d", alt->DURCHLAUFEILBOTE);
					sprintf(log.NEW_VALUE, "%d", neu->DURCHLAUFEILBOTE);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "maxposmenge"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->MAXPOSMENGE != alt->MAXPOSMENGE)
				{
					sprintf(log.OLD_VALUE, "%d", alt->MAXPOSMENGE);
					sprintf(log.NEW_VALUE, "%d", neu->MAXPOSMENGE);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "reservemaxqty"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->RESERVEMAXQTY != alt->RESERVEMAXQTY)
				{
					sprintf(log.OLD_VALUE, "%d", alt->RESERVEMAXQTY);
					sprintf(log.NEW_VALUE, "%d", neu->RESERVEMAXQTY);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "anzaufclose"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->ANZAUFCLOSE != alt->ANZAUFCLOSE)
				{
					sprintf(log.OLD_VALUE, "%d", alt->ANZAUFCLOSE);
					sprintf(log.NEW_VALUE, "%d", neu->ANZAUFCLOSE);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "anzposclose"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->ANZPOSCLOSE != alt->ANZPOSCLOSE)
				{
					sprintf(log.OLD_VALUE, "%d", alt->ANZPOSCLOSE);
					sprintf(log.NEW_VALUE, "%d", neu->ANZPOSCLOSE);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "tourenkippzeit"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->TOURENKIPPZEIT != alt->TOURENKIPPZEIT)
				{
					sprintf(log.OLD_VALUE, "%d", alt->TOURENKIPPZEIT);
					sprintf(log.NEW_VALUE, "%d", neu->TOURENKIPPZEIT);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "auftragzusammenmmm"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->AUFTRAGZUSAMMENMMM != alt->AUFTRAGZUSAMMENMMM)
				{
					sprintf(log.OLD_VALUE, "%d", alt->AUFTRAGZUSAMMENMMM);
					sprintf(log.NEW_VALUE, "%d", neu->AUFTRAGZUSAMMENMMM);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "auftragzusammenhhh"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "int"))
			{
				if (neu->AUFTRAGZUSAMMENHHH != alt->AUFTRAGZUSAMMENHHH)
				{
					sprintf(log.OLD_VALUE, "%d", alt->AUFTRAGZUSAMMENHHH);
					sprintf(log.NEW_VALUE, "%d", neu->AUFTRAGZUSAMMENHHH);
				}
				else continue;
			}
		}
		else if (!strcmp(logdef.FIELD_NAME, "sauftragzusammen"))
		{
			if (!strcmp(logdef.FIELD_TYPE, "char"))
			{
				if (strncmp(neu->SAUFTRAGZUSAMMEN, alt->SAUFTRAGZUSAMMEN, L_PARAUFBEARB_SAUFTRAGZUSAMMEN))
				{
					sprintf(log.OLD_VALUE, "%*.*s", L_PARAUFBEARB_SAUFTRAGZUSAMMEN, L_PARAUFBEARB_SAUFTRAGZUSAMMEN, alt->SAUFTRAGZUSAMMEN);
					sprintf(log.NEW_VALUE, "%*.*s", L_PARAUFBEARB_SAUFTRAGZUSAMMEN, L_PARAUFBEARB_SAUFTRAGZUSAMMEN, neu->SAUFTRAGZUSAMMEN);
				}
				else continue;
			}
		}
		else
		{
			continue;
		}
		strcpy(log.PARAMETER_NAME, logdef.PARAMETER_NAME);
		strcpy(log.PARAMETER_TABLE, logdef.PARAMETER_TABLE);
		EXEC SQL insert into parameter_change_logging(PARAMETERCHANGELOG_LISTE) values(PARAMETERCHANGELOG_ZEIGER(plog));
		if (sqlca.sqlcode < 0)
		{
			sprintf(error_msg, " AafilLogParameter insert %ld",
				sqlca.sqlcode);
			return -1;
		}
	}

}

int AafilGet_filiale(struct FILINF *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct FILINF   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select FILINF_LISTE into FILINF_ZEIGER(a) from filiale
where filialnr = :a->FILIALNR;

ppFILIAL_NR = a->FILIALNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilGet_filiale select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }
FilialNr = a->FILIALNR;

return 0;
}

int AafilGet_filiale_Procenter(struct FILINF *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct FILINF   *a;
char cdatenbank[256];
char tabelle[256];
char buffer[1048];
char str[1048];
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select datenbank_name into :cdatenbank from rechner
where filialnr = :a->FILIALNR;
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }

AllgEntfSpaces(cdatenbank);
sprintf(tabelle,"%s:filiale",cdatenbank);

sprintf(buffer,"select %s from %s where filialnr = ?",FILINF_PELISTE,tabelle);

strcpy(buffer,"select ");
strcat(buffer,FILINF_PELISTE);
strcat(buffer,"from ");
strcat(buffer,tabelle);
strcat(buffer," where filialnr = ? ");

EXEC SQL PREPARE sel_fili FROM :buffer;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilGet_filiale_Procenter select %ld",
   sqlca.sqlcode);
   return -1;
  }
exec sql declare SelFili Cursor for sel_fili;
EXEC SQL open SelFili using :a->FILIALNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilGet_filiale_Procenter open SelFili %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL fetch SelFili into FILINF_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilGet_filiale_Procenter fetch SelFili %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }

return 0;
}

int AafilReadpasswd(struct AEPWD *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct AEPWD   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select AEPWD_LISTE into AEPWD_ZEIGER(a) from passwd
where   filialNr=:a->FILIALNR and
                username=:a->USERNAME;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilReadpasswd select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }
return 0;
}

int AafilUpdpasswd(struct AEPWD *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct AEPWD   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdpasswd commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update passwd
set AEPWD_UPDATE(a)
where   filialNr=:a->FILIALNR and
                username=:a->USERNAME;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdpasswd update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdpasswd commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInspasswd(struct AEPWD *d, char *error_msg)
{
int i;
EXEC SQL BEGIN DECLARE SECTION;
struct AEPWD   *a;
char dummy[4];
short ind;
EXEC SQL END DECLARE SECTION;

a = d; /* nase max nummer und termid ermittel, +1 */

       EXEC SQL select MAX(uid)
           into :a->UID indicator :ind
           from passwd
           where filialnr = :a->FILIALNR;

        if (ind < 0) a->UID = 0;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg,"AafilInspasswd: max uid %ld %ld",
                 sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -2;
        }
        a->UID++;

        sprintf(dummy,"%2.2d%%", a->FILIALNR);

        /* max TERMID +1 */
        EXEC SQL select MAX(termid)
        into :a->TERMID  indicator :ind
                from passwd
                where   filialnr = :a->FILIALNR
                and             termid like :dummy;

        if (ind < 0) strcpy(a->TERMID," ");
        if (sqlca.sqlcode < 0)
        {
                sprintf(error_msg,"AafilInspasswd: max termid %ld %ld",
               sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -2;
        }

        if ( a->TERMID[0] == '\0' )     sprintf(a->TERMID,"%2.2d00", a->FILIALNR);

        for (i=3;i>=2;i--)
        {
                if (a->TERMID[i] >= '0' && a->TERMID[i] <= '9' || a->TERMID[i] >= 'A' && a->TERMID[i] <= 'Z')
                {
                        if(a->TERMID[i] == '9')
                        {
                                a->TERMID[i] = 'A';
                                break;
                        }
                        else if(a->TERMID[i] == 'Z')
                        {
                                a->TERMID[i] = '0';
                        }
                        else
                        {
                                a->TERMID[i]++;
                                break;
                        }
                }
                else
                {
                        sprintf(error_msg,"AafilInspasswd: termid ungueltig");
                        return -2;
                }
        }

/* Alle Nicht-Einsen durch Nullen ersetzen */
for (i = 0; i < L_AEPWD_AA; i++)
{
    if (a->AA[i] != '1')
        a->AA[i] = '0';
}
a->AA[L_AEPWD_AA] = '\0';

a->DAT_ANLAGE = AllgGetDate();
/*
printf("FILIALNR: #%d#\n",a->FILIALNR);
printf("USERNAME: #%s#\n",a->USERNAME);
printf("PASSWORD: #%s#\n",a->PASSWORD);
printf("UID: #%d#\n",a->UID);
printf("UID_ANLAGE: #%d#\n",a->UID_ANLAGE);
printf("DAT_LOESCH: #%d#\n",a->DAT_LOESCH);
printf("DAT_ANLAGE: #%d#\n",a->DAT_ANLAGE);
printf("ALLG_RECHTE: #%s#\n",a->ALLG_RECHTE);
printf("AA: #%s#\n",a->AA);
printf("TERMID: #%s#\n",a->TERMID);
*/

EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInspasswd commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into passwd (AEPWD_LISTE) values (AEPWD_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInspasswd insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInspasswd commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelaart(struct PARAART *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARAART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selaart scroll cursor with hold for
select PARAART_LISTE
from kdauftragart
where branchno = :a->BRANCHNO
order by KDAUFTRAGART;

     EXEC SQL open Selaart;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelaart: open Selaart %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selaart;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelaart: close Selaart %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selaart into PARAART_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelaart: fetch Selaart %ld",
   sqlca.sqlcode);
   EXEC SQL close Selaart;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdaart(struct PARAART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAART   *a;
char kdzstd[2];
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL select sstandard
into :kdzstd
from kdauftragart
where kdauftragart = :a->KDAUFTRAGART
and  branchno = :a->BRANCHNO;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaart select sstandard %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
if(kdzstd[0] != a->SSTANDARD[0])
{
        EXEC SQL declare Updaart cursor with hold for
        select sstandard
        from kdauftragart
        where branchno = :a->BRANCHNO
        for update;

        EXEC SQL open Updaart;
        if (sqlca.sqlcode < 0 )
        {
                sprintf(error_msg, " AafilUpdaart: open Updaart %ld",
                        sqlca.sqlcode);
                return -1;
        }
        for(;;)
        {
                EXEC SQL fetch Updaart;
                if (sqlca.sqlcode < 0 )
                {
                        sprintf(error_msg, " AafilUpdaart: fetch Updaart %ld",
                                sqlca.sqlcode);
                        EXEC SQL close Selaart;
                        return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND)
                {
                        break;
                }
                EXEC SQL update kdauftragart
                        set sstandard = '0'
                        where current of Updaart;
                if (sqlca.sqlcode < 0 )
                {
                        sprintf(error_msg, " AafilUpdaart: update Updaart %ld",
                                sqlca.sqlcode);
                        EXEC SQL close Updaart;
                        return -1;
                }
        }
}

EXEC SQL update kdauftragart
set PARAART_UPDATE(a)
where kdauftragart = :a->KDAUFTRAGART
and  branchno = :a->BRANCHNO;

if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaart update %ld",
                sqlca.sqlcode);
        return -1;
}
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInsaart(struct PARAART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into kdauftragart (PARAART_LISTE) values (PARAART_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInsaart insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelaart(struct PARAART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAART   *a;
long   anz;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select count(*) into :anz from auftragartkomb
where kdauftragart = :a->KDAUFTRAGART
and vertriebszentrumnr = :a->BRANCHNO;
if (anz>0)
  {
   strcpy(error_msg, TXT_LOESCH_NICHT_MOEGL);
   return -2;
  }
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from kdauftragart
where kdauftragart = :a->KDAUFTRAGART
and  branchno = :a->BRANCHNO;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelaart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelaart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelkoart(struct PARKOART *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARKOART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selkoart scroll cursor with hold for
select PARKOART_LISTE
from kommiarten
where branchno = :a->BRANCHNO
order by koart  ;

     EXEC SQL open Selkoart;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelkoart: open Selkoart %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selkoart;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelkoart: close Selkoart %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selkoart into PARKOART_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelkoart: fetch Selkoart %ld",
   sqlca.sqlcode);
   EXEC SQL close Selkoart;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdkoart(struct PARKOART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update kommiarten
set PARKOART_UPDATE(a)
where koart = :a->KOART
and branchno = :a->BRANCHNO;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdkoart update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInskoart(struct PARKOART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into kommiarten (PARKOART_LISTE) values (PARKOART_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInskoart insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelkoart(struct PARKOART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOART   *a;
long   anz;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select count(*) into :anz from auftragartkomb
where koart = :a->KOART
and branchno = :a->BRANCHNO;
if (anz>0)
  {
   strcpy(error_msg, TXT_LOESCH_NICHT_MOEGL);
   return -2;
  }
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from kommiarten
where koart = :a->KOART
and branchno = :a->BRANCHNO;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelkoart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkoart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelbuchart(struct PARBUCHART *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARBUCHART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selbuchart scroll cursor with hold for
select PARBUCHART_LISTE
from buchungsart
where branchno = :a->BRANCHNO
order by buchart  ;

     EXEC SQL open Selbuchart;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelbuchart: open Selbuchart %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selbuchart;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelbuchart: close Selbuchart %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selbuchart into PARBUCHART_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelbuchart: fetch Selbuchart %ld",
   sqlca.sqlcode);
   EXEC SQL close Selbuchart;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdbuchart(struct PARBUCHART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARBUCHART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update buchungsart
set PARBUCHART_UPDATE(a)
where buchart = :a->BUCHART
and branchno = :a->BRANCHNO;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdbuchart update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInsbuchart(struct PARBUCHART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARBUCHART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into buchungsart (PARBUCHART_LISTE) values (PARBUCHART_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInsbuchart insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelbuchart(struct PARBUCHART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARBUCHART   *a;
long   anz;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select count(*) into :anz from auftragartkomb
where buchart = :a->BUCHART
and vertriebszentrumnr = :a->BRANCHNO;
if (anz>0)
  {
   strcpy(error_msg, TXT_LOESCH_NICHT_MOEGL);
   return -2;
  }
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from buchungsart
where buchart = :a->BUCHART
and branchno = :a->BRANCHNO;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelbuchart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelbuchart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelkabakomb(struct PARKABAKOMB *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARKABAKOMB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selkabakomb scroll cursor with hold for
select PARKABAKOMB_LISTE
from auftragartkomb
where vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
order by kdauftragart,koart,buchart  ;

     EXEC SQL open Selkabakomb;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelkabakomb: open Selkabakomb %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selkabakomb;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelkabakomb: close Selkabakomb %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selkabakomb into PARKABAKOMB_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelkabakomb: fetch Selkabakomb %ld",
   sqlca.sqlcode);
   EXEC SQL close Selkabakomb;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilInskabakomb(struct PARKABAKOMB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKABAKOMB   *a;
char kz[2];
EXEC SQL END DECLARE SECTION;

a = d;
if (a->KZSTANDARD[0] == '1')
{
    EXEC SQL declare Updkabakomb cursor with hold for
                select kzstandard
        from auftragartkomb
        where
        kdauftragart = :a->KDAUFTRAGART
        and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
        for update;

        EXEC SQL open Updkabakomb;
        if (sqlca.sqlcode < 0 )
        {
                sprintf(error_msg, " AafilInskabakomb: open Updkabakomb %ld",
                sqlca.sqlcode);
                return -1;
        }
        for (;;)
        {
                EXEC SQL begin work;
                EXEC SQL fetch Updkabakomb into :kz;
                if (sqlca.sqlcode < 0 )
                {
                        sprintf(error_msg, " AafilInskabakomb: fetch Updkabakomb %ld",
                        sqlca.sqlcode);
                        EXEC SQL close Updkabakomb;
                        EXEC SQL rollback work;
                        return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND)
                {
                        EXEC SQL commit work;
                        break;
                }
                if(kz[0] == '1')
                {
                        EXEC SQL update auftragartkomb
                        set kzstandard = '0'
                        where current of Updkabakomb;
                        if (sqlca.sqlcode < 0 )
                        {
                                sprintf(error_msg, " AafilInskabakomb update %ld",
                                        sqlca.sqlcode);
                                EXEC SQL rollback work;
                                return -1;
                        }
                }
                EXEC SQL commit work;
        }
}

EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into auftragartkomb (PARKABAKOMB_LISTE) values (PARKABAKOMB_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   EXEC SQL rollback work;
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInskabakomb insert %ld",
   sqlca.sqlcode);
   EXEC SQL rollback work;
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
		return -1;
}
return 0;
}

int AafilDelkabakomb(struct PARKABAKOMB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKABAKOMB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from auftragartkomb
where   kdauftragart = :a->KDAUFTRAGART and
                buchart = :a->BUCHART and
                koart = :a->KOART and
                vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelkabakomb delete %ld",
   sqlca.sqlcode);
   EXEC SQL rollback work;
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilUpdkabakomb(struct PARKABAKOMB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKABAKOMB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update auftragartkomb set
	PARKABAKOMB_UPDATE(a)
where   kdauftragart = :a->KDAUFTRAGART and
                buchart = :a->BUCHART and
                koart = :a->KOART and
                vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdkabakomb update %ld",
   sqlca.sqlcode);
   EXEC SQL rollback work;
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkabakomb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelkondgr(struct PARKONGRP *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARKONGRP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selkondgr scroll cursor with hold for
select PARKONGRP_LISTE
from konditiongruppe
order by kondgruppennr  ;

     EXEC SQL open Selkondgr;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelkondgr: open Selkondgr %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selkondgr;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelkondgr: close Selkondgr %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selkondgr into PARKONGRP_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelkondgr: fetch Selkondgr %ld",
   sqlca.sqlcode);
   EXEC SQL close Selkondgr;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdkondgr(struct PARKONGRP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKONGRP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update konditiongruppe
set PARKONGRP_UPDATE(a)
where kondgruppennr = :a->KONDGRUPPENNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdkondgr update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInskondgr(struct PARKONGRP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKONGRP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into konditiongruppe (PARKONGRP_LISTE) values (PARKONGRP_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInskondgr insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelkondgr(struct PARKONGRP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKONGRP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from konditiongruppe
where kondgruppennr = :a->KONDGRUPPENNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelkondgr delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkondgr commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelkobehtyp(struct PARKOBEHTYP *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARKOBEHTYP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selkobehtyp scroll cursor with hold for
select PARKOBEHTYP_LISTE
from kobehaeltertyp
where filialnr = :a->FILIALNR
order by kobehaelttyp ;

     EXEC SQL open Selkobehtyp;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelkobehtyp: open Selkobehtyp %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selkobehtyp;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelkobehtyp: close Selkobehtyp %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selkobehtyp into PARKOBEHTYP_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelkobehtyp: fetch Selkobehtyp %ld",
   sqlca.sqlcode);
   EXEC SQL close Selkobehtyp;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdkobehtyp(struct PARKOBEHTYP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOBEHTYP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update kobehaeltertyp
set PARKOBEHTYP_UPDATE(a)
where filialnr = :a->FILIALNR and
        kobehaelttyp = :a->KOBEHAELTTYP;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdkobehtyp update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInskobehtyp(struct PARKOBEHTYP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOBEHTYP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into kobehaeltertyp (PARKOBEHTYP_LISTE) values (PARKOBEHTYP_ZEIGER(a));
if (sqlca.sqlcode == -239 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInskobehtyp insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelkobehtyp(struct PARKOBEHTYP *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOBEHTYP   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from kobehaeltertyp
where filialnr = :a->FILIALNR and
        kobehaelttyp = :a->KOBEHAELTTYP;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelkobehtyp delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkobehtyp commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelnachart(struct PARNACHRART* d, char* error_msg)
{
    UNUSED(d);
    UNUSED(error_msg);
    return 1;
}

int AafilUpdnachart(struct PARNACHRART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARNACHRART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update nachrichtenarten
set PARNACHRART_UPDATE(a)
where filialnr = :a->FILIALNR
and formularkuerzel = :a->FORMULARKUERZEL
and lagerbereichnr = :a->LAGERBEREICHNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdnachart update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInsnachart(struct PARNACHRART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARNACHRART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into nachrichtenarten (PARNACHRART_LISTE) values (PARNACHRART_ZEIGER(a));
if (sqlca.sqlcode == -239 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInsnachart insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelnachart(struct PARNACHRART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARNACHRART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from nachrichtenarten
where filialnr = :a->FILIALNR
and formularkuerzel = :a->FORMULARKUERZEL
and lagerbereichnr = :a->LAGERBEREICHNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelnachart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelnachart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelauferg(struct PARAUFERG *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFERG   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select PARAUFERG_LISTE into PARAUFERG_ZEIGER(a)
from paraauftrager
where filialnr = :a->FILIALNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilSelauferg: select paraauftrager %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdauferg(struct PARAUFERG *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFERG   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update paraauftrager
set PARAUFERG_UPDATE(a)
where filialnr = :a->FILIALNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdauferg update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInsauferg(struct PARAUFERG *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFERG   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into paraauftrager (PARAUFERG_LISTE) values (PARAUFERG_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInsauferg insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelauferg(struct PARAUFERG *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFERG   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from paraauftrager
where filialnr = :a->FILIALNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelauferg delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelauferg commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelaufbearb(struct PARAUFBEARB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFBEARB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select PARAUFBEARB_LISTE into PARAUFBEARB_ZEIGER(a)
from paraauftragbearb
where filialnr = :a->FILIALNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilSelaufbearb: select paraauftragbearb %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdaufbearb(struct PARAUFBEARB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFBEARB   *a;
struct PARAUFBEARB   alt,*old;
EXEC SQL END DECLARE SECTION;

old = &alt;

a = d;

EXEC SQL select PARAUFBEARB_LISTE into PARAUFBEARB_ZEIGER(old) from paraauftragbearb
where FILIALNR = :a->FILIALNR;
if (sqlca.sqlcode < 0)
{
	sprintf(error_msg, " AafilUpdaufbearb select %ld %ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}

EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update paraauftragbearb
set PARAUFBEARB_UPDATE(a)
where filialnr = :a->FILIALNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdaufbearb update %ld",
   sqlca.sqlcode);
   return -1;
  }

AafilLogParameter("paraauftragbearb", a, old, error_msg);

EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}


return 0;
}

int AafilInsaufbearb(struct PARAUFBEARB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFBEARB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into paraauftragbearb (PARAUFBEARB_LISTE) values (PARAUFBEARB_ZEIGER(a));
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInsaufbearb insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInsaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelaufbearb(struct PARAUFBEARB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFBEARB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from paraauftragbearb
where filialnr = :a->FILIALNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelaufbearb delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelaufbearb commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSelkommi(struct PARKOMMI *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARKOMMI   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Selkommi scroll cursor with hold for
select PARKOMMI_LISTE
from parakommi
order by filialnr,
        lagerebene ;

     EXEC SQL open Selkommi;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSelkommi: open Selkommi %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Selkommi;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSelkommi: close Selkommi %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Selkommi into PARKOMMI_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSelkommi: fetch Selkommi %ld",
   sqlca.sqlcode);
   EXEC SQL close Selkommi;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpdkommi(struct PARKOMMI *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOMMI   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update parakommi
set PARKOMMI_UPDATE(a)
where filialnr = :a->FILIALNR and
        lagerebene = :a->LAGEREBENE;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpdkommi update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpdkommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilInskommi(struct PARKOMMI *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOMMI   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into parakommi (PARKOMMI_LISTE) values (PARKOMMI_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilInskommi insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilInskommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDelkommi(struct PARKOMMI *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKOMMI   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from parakommi
where filialnr = :a->FILIALNR and
lagerebene = :a->LAGEREBENE;
if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 )
  {
   strcpy(error_msg, TXT_DOPP_WERT);
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDelkommi delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDelkommi commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}


int AafilSel_altfil(struct N_ALTFIL *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct N_ALTFIL   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Sel_altfil scroll cursor with hold for
select ALTFIL_LISTE
from alternativfiliale
where filialnr = :a->FILIALNR
order by reihenfolgenr  ;

     EXEC SQL open Sel_altfil;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_altfil: open Sel_altfil %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_altfil;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_altfil: close Sel_altfil %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_altfil into ALTFIL_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_altfil: fetch Sel_altfil %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_altfil;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpd_altfil(struct N_ALTFIL *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct N_ALTFIL   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpd_altfil commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL update alternativfiliale
set ALTFIL_UPDATE(a)
where filialnr = :a->FILIALNR
and reihenfolgenr = :a->REIHENFOLGENR
and vbtyp = :a->VBTYP;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilUpd_altfil update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilUpd_altfil commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilIns_altfil(struct N_ALTFIL *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct N_ALTFIL   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_altfil commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into alternativfiliale (ALTFIL_LISTE) values (ALTFIL_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilIns_altfil insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_altfil commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSel_zeitarten(struct ZEITARTV *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct ZEITARTV   *a;
long von;
long bis;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
    ppGStripLast(a->ZEITSCHLUESSEL);
        if (a->ZEITART == 0)
        {
                von = 0;
                bis = 9999999;
        }
        else
        {
                von = a->ZEITART;
                bis = a->ZEITART;
        }
     EXEC SQL declare Sel_zeitarten scroll cursor with hold for
                select ZEITARTV_LISTE
                from zeitarten
                where zeitschluessel like :a->ZEITSCHLUESSEL
                and zeitart >= :von
                and zeitart <= :bis
                and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
                order by zeitart,zeitschluessel,weekday,zeitbegin;

     EXEC SQL open Sel_zeitarten;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_zeitarten: open Sel_zeitarten %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_zeitarten;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_zeitarten: close Sel_zeitarten %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_zeitarten into ZEITARTV_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_zeitarten: fetch Sel_zeitarten %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_zeitarten;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilUpd_zeitarten(struct ZEITARTV *d, char *error_msg)
{
int rc = 0;

for(;;)
        {
        if ((rc=AafilDel_zeitart(d, error_msg)) != 0)
           break;
        if ((rc=AafilIns_zeitarten(d, error_msg)) != 0)
           break;
        break;
        }

return rc;
}

int AafilIns_zeitarten(struct ZEITARTV *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct ZEITARTV   *a;
short haus;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_zeitarten begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into zeitarten (ZEITARTV_LISTE)
values (ZEITARTV_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilIns_zeitarten insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_zeitarten commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDel_altfil(struct N_ALTFIL *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct N_ALTFIL   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_altfil begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from alternativfiliale
where filialnr = :a->FILIALNR
and reihenfolgenr = :a->REIHENFOLGENR
and vbtyp = :a->VBTYP;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDel_altfil delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_altfil commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDel_zeitart(struct ZEITARTV *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct ZEITARTV   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_zeitart begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from zeitarten
where lfdnr = :a->LFDNR;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDel_zeitart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_zeitart commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSel_usertext(struct USERTEXTV *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct USERTEXTV   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Sel_usertext scroll cursor with hold for
         select USERTEXTV_LISTE
         from usertexte
         where uid = :a->UID
         and textart = :a->TEXTART  ;

     EXEC SQL open Sel_usertext;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_usertext: open Sel_usertext %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_usertext;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_usertext: close Sel_usertext %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_usertext into USERTEXTV_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_usertext: fetch Sel_usertext %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_usertext;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilIns_usertext(struct USERTEXTV *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct USERTEXTV   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_usertext begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into usertexte (USERTEXTV_LISTE) values (USERTEXTV_ZEIGER(a));
if (sqlca.sqlcode == -239)
  {
   strcpy(error_msg, " Text bereits vorhanden");
        EXEC SQL commit work;
   return -2;
  }
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilIns_usertext insert %ld",
   sqlca.sqlcode);
        EXEC SQL commit work;
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_usertext commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilDel_usertext(struct USERTEXTV *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct USERTEXTV   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_usertext begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from usertexte
where uid = :a->UID
and textart = :a->TEXTART
and text = :a->TEXT;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDel_usertext delete %ld",
   sqlca.sqlcode);
        EXEC SQL commit work;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
        EXEC SQL select * from usertexte
        where uid = -1
        and textart = :a->TEXTART
        and text = :a->TEXT;
        EXEC SQL commit work;
        if (sqlca.sqlcode == SQLNOTFOUND)
          {
           return 4;
          }
   return 1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_usertext commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilSel_aa_passwd(struct AEPWD *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct AEPWD   *a;
EXEC SQL END DECLARE SECTION;

a = d;
AllgMakeToLike(a->AA,L_AEPWD_AA);
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Sel_aa_passwd scroll cursor with hold for
select AEPWD_LISTE
from    passwd
where   filialnr = :a->FILIALNR and
                aa like         :a->AA
order by termid;

     EXEC SQL open Sel_aa_passwd;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_aa_passwd: open Sel_aa_passwd %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_aa_passwd;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_aa_passwd: close Sel_aa_passwd %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_aa_passwd into AEPWD_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_aa_passwd: fetch Sel_aa_passwd %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_aa_passwd;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilSel_verbund(struct ZEITARTV *d, char *error_msg)
{
static int fst = 1;
long datum;
long i;
EXEC SQL BEGIN DECLARE SECTION;
struct ZEITARTV   *a;
short sWeekday;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
        fst = 0;
        datum = ppGGetDate();
    ppGStripLast(a->ZEITSCHLUESSEL);
        sWeekday = (short)ppGGetWeekDay(datum, error_msg);
     EXEC SQL declare Sel_verbund scroll cursor with hold for
                select ZEITARTV_LISTE
                from zeitarten,kunde
                where zeitarten.zeitschluessel like :a->ZEITSCHLUESSEL
                and zeitarten.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
                and zeitarten.zeitart = 1
                and zeitarten.weekday = :sWeekday
                and kunde.vertriebszentrumnr = zeitarten.vertriebszentrumnr
                and kunde.kundennr = zeitarten.zeitschluessel
                and (kunde.verbundkunde = 1
                or kunde.verbundkunde = 4)
                order by zeitarten.zeitbegin;

     EXEC SQL open Sel_verbund;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_verbund: open Sel_verbund %ld/%s",
         sqlca.sqlcode,sqlca.sqlerrm);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_verbund;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_verbund: close Sel_verbund %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_verbund into ZEITARTV_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_verbund: fetch Sel_verbund %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_verbund;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilSel_auftrendzeit(struct PARAUFTRENDZEIT *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFTRENDZEIT   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Sel_auftrendzeit scroll cursor with hold for
select PARAUFTRENDZEIT_LISTE
from kdauftragendezeit
where filialnr = :a->FILIALNR ;

     EXEC SQL open Sel_auftrendzeit;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_auftrendzeit: open Sel_auftrendzeit %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_auftrendzeit;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_auftrendzeit: close Sel_auftrendzeit %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_auftrendzeit into PARAUFTRENDZEIT_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_auftrendzeit: fetch Sel_auftrendzeit %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_auftrendzeit;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AafilDel_auftrendzeit(struct PARAUFTRENDZEIT *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFTRENDZEIT   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_auftrendzeit commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL delete from kdauftragendezeit
where   filialnr                        = :a->FILIALNR
and             batchschreiben          = :a->BATCHSCHREIBEN
and             herkunftsfilialnr       = :a->HERKUNFTSFILIALNR
and             abschlussmodus          = :a->ABSCHLUSSMODUS
and             abschlusszeit           = :a->ABSCHLUSSZEIT
        ;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilDel_auftrendzeit delete %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilDel_auftrendzeit commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilIns_auftrendzeit(struct PARAUFTRENDZEIT *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARAUFTRENDZEIT   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_auftrendzeit commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
EXEC SQL insert into kdauftragendezeit (PARAUFTRENDZEIT_LISTE) values (PARAUFTRENDZEIT_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilIns_auftrendzeit insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilIns_auftrendzeit commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
}
return 0;
}

int AafilIs_new_order_possi(struct AUFIE *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct AUFIE   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select count(*) into :a->ANZ_IE
        from werte
where bezeichner = 'AA_NEW_ORD' and zahl = 1
        and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR ;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilIs_new_order_possi select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }
return 0;
}

int AafilChecktour(struct PARKABAKOMB *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct PARKABAKOMB   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL declare Sel_tour scroll cursor with hold for
select TOURID
from tour
where tourid = :a->TOURID
and filialnr = :a->VERTRIEBSZENTRUMNR;
EXEC SQL open Sel_tour;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilChecktour: open Sel_tour %ld %ld",
        sqlca.sqlcode,sqlca.sqlerrd[1]);
        EXEC SQL close Sel_tour;
        return -1;
}
EXEC SQL fetch Sel_tour;
if (sqlca.sqlcode < 0 )
{
        sprintf(error_msg, " AafilChecktour: fetch Sel_tour %ld %ld",
        sqlca.sqlcode,sqlca.sqlerrd[1]);
        EXEC SQL close Sel_tour;
        return -1;
}
if (sqlca.sqlcode == SQLNOTFOUND)
{
        strcpy(error_msg, " Tour nicht vorhanden");
        EXEC SQL close Sel_tour;
        return -2;
}
EXEC SQL close Sel_tour;
return 0;
}

int AafilSet_actualfiliale(struct FILINF *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct FILINF   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select FILINF_LISTE into FILINF_ZEIGER(a) from filiale
where filialnr = :a->FILIALNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AafilSet_actualfiliale select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " AafilSet_actualfiliale: Abfrage lieferte kein Ergebnis");
   return -2;
  }

ppFILIAL_NR = a->FILIALNR;
FilialNr = a->FILIALNR;
return 0;
}

int AafilSet_sprache(lgtextS *d, char *error_msg)
{

        EXEC SQL BEGIN DECLARE SECTION;
        lgtextS *a;
    char szBuf[512];
        long lCount;
        EXEC SQL END DECLARE SECTION;

        a = d;

		if (!strncmp(a->LGID, "CH", 2)) strncpy(a->LGID, "FR", 2);
        sprintf(ARTIKELZENTRAL_SPRACHE,"%s%2.2s","artikelzentral",a->LGID);
        strcpy( szBuf, "select count(*) from " );
        strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
        exec sql prepare P_SPRACHE1 from :szBuf;
    if (sqlca.sqlcode == -206 )
        {
                FREMDSPRACHE = 0;
                return 0;
        }
    if ( sqlca.sqlcode < 0 )
        {
       sprintf(error_msg, " AafilSet_sprache: prepare P_SPRACHE1 %ld/%d",
                   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
        }
        EXEC SQL execute P_SPRACHE1 into :lCount;
    if (sqlca.sqlcode == -206 )
        {
                FREMDSPRACHE = 0;
                return 0;
        }
        else if(lCount == 0)
        {
                FREMDSPRACHE = 0;
                return 0;
        }

    if (sqlca.sqlcode < 0 )
        {
       sprintf(error_msg, " AafilSet_sprache: execute P_ARTSEL1 %ld/%d",
       sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
    }
        sprintf(ARTIKELINDEX_SPRACHE,"%s%2.2s","artikelindex",a->LGID);
        sprintf(ARTIKELSEKBEZ_SPRACHE,"%s%2.2s","artikelsekbez",a->LGID);
        sprintf(ARTIKELSELECT_SPRACHE,"%s%2.2s","artselect",a->LGID);
        FREMDSPRACHE = 1;
        return 0;
}

int AafilSel_zeit_heute(struct ZEITARTV *d, char *error_msg)
{
static int fst = 1;
struct tm t;

EXEC SQL BEGIN DECLARE SECTION;
struct ZEITARTV   *a;
long von;
long bis;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     AllgGetTM(&t);
     d->WEEKDAY = (long)t.tm_wday; /* 0 = Sonntag   */
     EXEC SQL declare Sel_zeit_heute scroll cursor with hold for
                select ZEITARTV_LISTE
                from zeitarten
				where weekday = :a->WEEKDAY
                and zeitart = 2
                and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
                order by zeitschluessel,zeitbegin;

     EXEC SQL open Sel_zeit_heute;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AafilSel_zeit_heute: open Sel_zeit_heute %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_zeit_heute;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AafilSel_zeit_heute: close Sel_zeit_heute %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_zeit_heute into ZEITARTV_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AafilSel_zeit_heute: fetch Sel_zeit_heute %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_zeit_heute;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}


int AafilSelLogParameter(parameter_change_loggingS *d, char *error_msg)
{
	static int fst = 1;
	static int whereclause = 1;

	EXEC SQL BEGIN DECLARE SECTION;
	parameter_change_loggingS *plog;
	char str[2048];
	char buffer[1048];
	EXEC SQL END DECLARE SECTION;

	plog = d;
	if (fst) /* beim ersten mal oder bei neu deklarieren */
	{
		fst = 0;
		ppGStripLast(plog->PARAMETER_NAME);
		strcpy(str, "select ");
		strcat(str, "PARAMETER_CHANGE_LOGGING.BRANCHNO,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.USER_ID,");
		strcat(str, "PASSWD.USERNAME,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.USER_BRANCHNO,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.DATE_CHANGE,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.TIME_CHANGE,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.PARAMETER_NAME,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.KEYOFCHANGE,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.OLD_VALUE,");
		strcat(str, "PARAMETER_CHANGE_LOGGING.NEW_VALUE ");
		strcat(str, "from PARAMETER_CHANGE_LOGGING ");
		strcat(str, "inner join passwd ");
		strcat(str, "on passwd.uid = parameter_change_logging.user_id and passwd.filialnr = parameter_change_logging.user_branchno");
		if (plog->BRANCHNO > 0)
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.user_branchno = ");
			sprintf(buffer, "%d ", plog->BRANCHNO);
			strcat(str, buffer);
		}
		if (plog->PARAMETER_NAME[0] != '\0')
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.parameter_name = '");
			sprintf(buffer, "%s ", plog->PARAMETER_NAME);
			strcat(str, buffer);
			strcat(str, "'");
		}
		if (plog->DATE_CHANGE > 0)
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.date_change >= ");
			sprintf(buffer, "%d ", plog->DATE_CHANGE);
			strcat(str, buffer);
		}
		if (plog->TIME_CHANGE > 0)
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.time_change >= ");
			sprintf(buffer, "%d ", plog->TIME_CHANGE);
			strcat(str, buffer);
		}
		if (plog->DATE_CHANGE_TO > 0)
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.date_change <= ");
			sprintf(buffer, "%d ", plog->DATE_CHANGE_TO);
			strcat(str, buffer);
		}
		if (plog->TIME_CHANGE_TO > 0)
		{
			if (whereclause)
			{
				whereclause = 0;
				strcat(str, " where ");
			}
			else
			{
				strcat(str, " and ");
			}
			strcat(str, "parameter_change_logging.time_change <= ");
			sprintf(buffer, "%d ", plog->TIME_CHANGE_TO);
			strcat(str, buffer);
		}
		EXEC SQL PREPARE dec_ChangeLog_select FROM : str;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameter: prepare dec_ChangeLog_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		EXEC SQL declare Cur_ChangeLog_select scroll cursor with hold for dec_ChangeLog_select;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameter: declare Cur_ChangeLog_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		EXEC SQL open Cur_ChangeLog_select;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameter: open Cur_ChangeLog_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
	}

	if (plog->FETCH_REL == 0)   /* close cursor */
	{
		fst = 1;
		whereclause = 1;
		EXEC SQL close Cur_ChangeLog_select;
		if (sqlca.sqlcode < 0)
		{
			sprintf(error_msg, " AafilSelLogParameter: close Cur_ChangeLog_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		return 1;
	}

	EXEC SQL fetch relative :plog->FETCH_REL Cur_ChangeLog_select
		into
		:plog->BRANCHNO,
		:plog->USER_ID,
		:plog->USERNAME,
		:plog->USER_BRANCHNO,
		:plog->DATE_CHANGE,
		:plog->TIME_CHANGE,
		:plog->PARAMETER_NAME,
		:plog->PARAMETER_TABLE,
		:plog->KEYOFCHANGE,
		:plog->OLD_VALUE,
		:plog->NEW_VALUE,
		:plog->DATE_CHANGE_TO,
		:plog->TIME_CHANGE_TO;

	if (sqlca.sqlcode < 0)
	{
		fst = 1;
		sprintf(error_msg, " AafilSelLogParameter: fetch Cur_ChangeLog_select %ld %ld",
			sqlca.sqlcode, sqlca.sqlerrd[1]);
		EXEC SQL close Cur_ChangeLog_select;
		return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		return 1;
	}
}

int AafilSelLogParameterDefinitions(parameter_change_log_defsS *d, char *error_msg)
{
	static int fst = 1;

	EXEC SQL BEGIN DECLARE SECTION;
	parameter_change_log_defsS *plog;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	plog = d;
	if (fst) /* beim ersten mal oder bei neu deklarieren */
	{
		fst = 0;

		strcpy(str, "select ");
		strcat(str, PARAMETER_CHANGE_LOG_DEFS_PLISTE);
		strcat(str, " from PARAMETER_CHANGE_LOG_DEFINITION ");

		EXEC SQL PREPARE dec_ChangeLogDefs_select FROM :str;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameterDefinitions: prepare dec_ChangeLog_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		EXEC SQL declare Cur_ChangeLogDefs_select scroll cursor with hold for dec_ChangeLogDefs_select;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameterDefinitions: declare Cur_ChangeLogDefs_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		EXEC SQL open Cur_ChangeLogDefs_select;
		if (sqlca.sqlcode < 0)
		{
			fst = 1;
			sprintf(error_msg, " AafilSelLogParameterDefinitions: open Cur_ChangeLogDefs_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
	}

	if (plog->FETCH_REL == 0)   /* close cursor */
	{
		fst = 1;
		EXEC SQL close Cur_ChangeLogDefs_select;
		if (sqlca.sqlcode < 0)
		{
			sprintf(error_msg, " AafilSelLogParameterDefinitions: close Cur_ChangeLogDefs_select %ld %ld",
				sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		return 1;
	}

	EXEC SQL fetch relative :plog->FETCH_REL Cur_ChangeLogDefs_select
		into
		PARAMETER_CHANGE_LOG_DEFS_ZEIGERSEL(plog);

	if (sqlca.sqlcode < 0)
	{
		fst = 1;
		sprintf(error_msg, " AafilSelLogParameterDefinitions: fetch Cur_ChangeLogDefs_select %ld %ld",
			sqlca.sqlcode, sqlca.sqlerrd[1]);
		EXEC SQL close Cur_ChangeLogDefs_select;
		return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		return 1;
	}
}