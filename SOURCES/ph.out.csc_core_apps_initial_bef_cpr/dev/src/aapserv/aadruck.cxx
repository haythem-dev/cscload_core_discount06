#include"bufkon.h"
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<ctype.h>
#include<string.h>
#include<memory.h>
#include "texte.h"
#include "aetexte.h"
#include <time.h>
#include "allg.h"
#include "druckpara.h"
#include "ppgeneric.h"
#include "artsel.h"

int AatartSel_Preferred(struct ARTAESEL *d, char *error_msg);
int AadruckNachl_vbmoegl_new(struct DRUCKPARA *d, char *error_msg);
int AadruckNachl_vbmoegl_nlevel(struct DRUCKPARA *d, char *error_msg);

#define LINE_COUNT	40
#define LINE_COUNT2	60
#define L_TEXT		81
#define DRUCK_PROZ		"druckaa"
#define DRUCK_PROZ2		"druckmp"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*  GLOBALE C-VARIABLEN  */
extern char ARTIKELZENTRAL_SPRACHE[20];
extern int FREMDSPRACHE;

EXEC SQL BEGIN DECLARE SECTION;
extern short FilialNr;
char szBuf[512];
EXEC SQL END DECLARE SECTION;


int AadruckNachl(struct DRUCKPARA *d, char *error_msg)
{
	char Out1[11];
	FILE *fp;
	char outputFile[L_TEXT];
	int zaehler,pgcount;
	char prntcmd[L_TEXT+8];
 
	EXEC SQL BEGIN DECLARE SECTION;
	struct DRUCKPARA   *a;
	long datum;
	long idfnr;
	long kdauftragnr;
	long artikel_nr;
	long menge;
	char nameapo[41];
	char faxnr[26];
	char kdauftragart[3];
	char artikel_name[31];
	char bemerkungen[241];
	char buffer[2000];
	struct ARTAESEL art;
	EXEC SQL END DECLARE SECTION;

	a = d;

	sprintf( outputFile, "%s/nachl%d.dat", (char *)getenv( "LOG_PATH" ),a->VERTRIEBSZENTRUMNR );
	if ( ( fp = fopen( outputFile, "w" ) ) == (FILE *)0 ) return 1;

	if (FREMDSPRACHE)
	{
		exec sql free SEL_SPRACHE1;
		strcpy( szBuf, "select artikel_name from " ); 
	 	strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
	 	strcat( szBuf, " where artikel_nr = ?" );
		exec sql prepare SEL_SPRACHE1 from :szBuf;
	    if ( sqlca.sqlcode < 0 )
		{
	       sprintf(error_msg, " AadruckNachl: prepare SEL_SPRACHE1 %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
	}

	strcpy(buffer,"select "); 
	strcat(buffer,"nachlieferpos.datum, ");
	strcat(buffer,"nachlieferpos.kdauftragart, ");
	strcat(buffer,"nachlieferpos.idfnr, ");
	strcat(buffer,"nachlieferpos.kdauftragnr, ");
	strcat(buffer,"nachlieferpos.artikel_nr, ");
	strcat(buffer,"nachlieferpos.menge, ");
	strcat(buffer,"kunde.nameapo, ");
	strcat(buffer,"kunde.faxnr, ");
	strcat(buffer,"artikelzentral.artikel_name, ");
	strcat(buffer,"nachlieferpos.bemerkungen ");
	strcat(buffer,"from ");
	strcat(buffer,"nachlieferpos, ");
	strcat(buffer,"artikelzentral, ");
	if (a->POSART[1] == '2')
	{
		strcat(buffer,"artikellokal, ");
	}
	strcat(buffer,"outer kunde ");
	strcat(buffer,"where nachlieferpos.idfnr = kunde.idfnr ");
	strcat(buffer,"and nachlieferpos.vertriebszentrumnr = ? ");
	strcat(buffer,"and nachlieferpos.vertriebszentrumnr = kunde.vertriebszentrumnr ");
	strcat(buffer,"and nachlieferpos.artikel_nr = artikelzentral.artikel_nr ");
	strcat(buffer,"and nachlieferpos.postyp = 3 ");
	if (a->POSART[1] == '1' || a->POSART[1] == '3')
	{
		strcat(buffer,"and trunc( artikelzentral.etartschalter1/4096 ) - 2 * trunc( artikelzentral.etartschalter1/(4096*2)) = 1 ");
	}
	else if (a->POSART[1] == '2')
	{
		strcat(buffer,"and nachlieferpos.vertriebszentrumnr = artikellokal.filialnr ");
		strcat(buffer,"and nachlieferpos.artikel_nr = artikellokal.artikel_nr ");
		strcat(buffer,"and trunc( artikellokal.etartschalter2/1 ) - 2 * trunc( artikellokal.etartschalter2/(2*1)) = 0 ");
	}
	if (a->POSART[1] == '3')
	{
		strcat(buffer,"union "); 
		strcat(buffer,"select "); 
		strcat(buffer,"nachlieferpos.datum, ");
		strcat(buffer,"nachlieferpos.kdauftragart, ");
		strcat(buffer,"nachlieferpos.idfnr, ");
		strcat(buffer,"nachlieferpos.kdauftragnr, ");
		strcat(buffer,"nachlieferpos.artikel_nr, ");
		strcat(buffer,"nachlieferpos.menge, ");
		strcat(buffer,"kunde.nameapo, ");
		strcat(buffer,"kunde.faxnr, ");
		strcat(buffer,"artikelzentral.artikel_name, ");
		strcat(buffer,"nachlieferpos.bemerkungen ");
		strcat(buffer,"from ");
		strcat(buffer,"nachlieferpos, ");
		strcat(buffer,"artikelzentral, ");
		strcat(buffer,"artikellokal, ");
		strcat(buffer,"outer kunde ");
		strcat(buffer,"where nachlieferpos.idfnr = kunde.idfnr ");
		strcat(buffer,"and nachlieferpos.vertriebszentrumnr = ? ");
		strcat(buffer,"and nachlieferpos.vertriebszentrumnr = kunde.vertriebszentrumnr ");
		strcat(buffer,"and nachlieferpos.artikel_nr = artikelzentral.artikel_nr ");
		strcat(buffer,"and nachlieferpos.postyp = 3 ");
		strcat(buffer,"and nachlieferpos.vertriebszentrumnr = artikellokal.filialnr ");
		strcat(buffer,"and nachlieferpos.artikel_nr = artikellokal.artikel_nr ");
		strcat(buffer,"and trunc( artikellokal.etartschalter2/1 ) - 2 * trunc( artikellokal.etartschalter2/(1*2)) = 0 ");
	}
	if (a->POSART[0] == '0')
	{
		strcat(buffer,"order by nachlieferpos.datum ");
	}
	else if (a->POSART[0] == '1')
	{
		strcat(buffer,"order by nachlieferpos.idfnr,nachlieferpos.artikel_nr ");
	}
	else
	{
		strcat(buffer,"order by nachlieferpos.artikel_nr,nachlieferpos.idfnr ");
	}

	exec sql prepare sel_nachl from :buffer;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl: prepare sel_nachl %ld %ld %s",
		sqlca.sqlcode , sqlca.sqlerrd[1], sqlca.sqlerrm );
		return -1;
	}
	exec sql declare Sel_nachl00 cursor with hold for sel_nachl;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl: declare Sel_nachl00 %ld %ld %s",
		sqlca.sqlcode , sqlca.sqlerrd[1], sqlca.sqlerrm );
		return -1;
	}
	if (a->POSART[1] == '3')
	{
		EXEC SQL open Sel_nachl00 using :a->VERTRIEBSZENTRUMNR,:a->VERTRIEBSZENTRUMNR;
	}
	else
	{
		EXEC SQL open Sel_nachl00 using :a->VERTRIEBSZENTRUMNR;
	}
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl: open Sel_nachl00 %ld %ld %s",
		sqlca.sqlcode , sqlca.sqlerrd[1], sqlca.sqlerrm );
		return -1;
	}

	for (zaehler = 0 , pgcount = 0;; )
	{
		EXEC SQL fetch Sel_nachl00 into 
			:datum,
			:kdauftragart,
			:idfnr,
			:kdauftragnr,
			:artikel_nr,
			:menge,
			:nameapo,
			:faxnr,
			:artikel_name,
			:bemerkungen;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl: fetch Sel_nachl00 %ld %ld %s",
			sqlca.sqlcode , sqlca.sqlerrd[1], sqlca.sqlerrm );
			return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND) break;
		if (FREMDSPRACHE)
		{
			EXEC SQL execute SEL_SPRACHE1 into :artikel_name using :artikel_nr;
		    if (sqlca.sqlcode < 0 )
			{ 
		       sprintf(error_msg, " AadruckNachl: execute SEL_SPRACHE1 %ld/%d %s",
		       sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
		       return -1;
		    }
		}
		art.ARTIKEL_NR = artikel_nr;
		AatartSel_Preferred(&art, error_msg);
		AllgDatumLong2CharTTMMJJJJ(datum, Out1);
		zaehler++;
		if ( zaehler == 1 )	/* 1. Zeile Überschrift */
		{
			fprintf( fp, "%-10s %-2s %-7s %-8s %-8s %-5s %-40s %-30s %-25s %s\n",
				AET_DATUM,
				AET_KZ_AUFTRAGSART,
				AET_IDF_NR,
				AET_AUF_NR,
				AET_PZN,
				AET_MENGE,
				AET_APOTHEKENNAME,
				AET_ARTIKELNAME,
				AET_FAX,
				AET_BEMERKUNG
				);
		}
	
		fprintf( fp, "%-10s %-2s %-7d %-8d %8.8s %-5d %-40s %-30s %-25s %s\n",
			Out1,
			kdauftragart,
			idfnr,
			kdauftragnr,
			art.ARTICLE_CODE,
			menge,
			nameapo,
			artikel_name,
			faxnr,
			bemerkungen
			);
		if ( zaehler == LINE_COUNT )	/* alle LINE_COUNT Zeilen Fußzeile */
		{
			fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
			zaehler = 0;
		}

	}
	fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
	fclose(fp);
	sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,a->VERTRIEBSZENTRUMNR);
	system(prntcmd);

	return 0;
}

int AadruckMasterplan(struct DRUCKPARA *d, char *error_msg)
{
static int fst = 0;
static int funkt;
static int vznr;
static FILE *fp;
static char outputFile[L_TEXT];
static int zaehler,pgcount;
char prntcmd[L_TEXT+8];
static char cDatum[11];
static char cZeit[6];
static char cProt[3];
static char cRufzeit[6];
static char cRufeinstellung[2];
static char cSort[8];
long lTime;
long lDatum;
static long sidfnr;
static long surrufzeit;
static char srufprotokoll[2];
static short srufsteuerung;
static char srufeinstellung[2];
static char sanruftyp[2];
static char smatchcode[13];
static long spersonalnrvertr;
static char tagtab[20];
static long fetchcount,prozent,prozcount;
static long vurrufzeit = 0;
#define leer "N  N  N  N  N  N  N" 

EXEC SQL BEGIN DECLARE SECTION;
struct DRUCKPARA   *a;
long idfnr;
char tagnr[2];
long urrufzeit;
char rufprotokoll[2];
short rufsteuerung;
char rufeinstellung[2];
char anruftyp[2];
char matchcode[13];
long personalnrvertr;
long anzahl;
EXEC SQL END DECLARE SECTION;

a = d;

// Init against C4701
idfnr = 0L;
urrufzeit = 0L;
rufsteuerung = 0;
anzahl = 0L;
personalnrvertr = 0L;

if ( fst == 0 )
{
	sprintf( outputFile, "%s/masterplan%d.dat", (char *)getenv( "LOG_PATH" ),a->VERTRIEBSZENTRUMNR );
	if ( ( fp = fopen( outputFile, "w" ) ) == (FILE *)0 ) return 1;
	fst = 1;
	lDatum = ppGGetDate();
	lTime = ppGGetTime();
	ppGDateLongToCharTTMMJJJJ(lDatum,cDatum);
	ppGTimeLongToCharHHMM(lTime,cZeit);
	zaehler = 0;
	pgcount = 0;
	prozcount = 0;
	fetchcount = 0;
	vznr = a->VERTRIEBSZENTRUMNR;
	EXEC SQL select count(*) into :anzahl from kundemasterplan
	where kundemasterplan.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
	prozent = anzahl/20;
	if (a->POSART[0] == '0' && a->POSART[1] == '0')
	{
		funkt = 0;
		EXEC SQL declare CSelmaster00 scroll cursor with hold for
		select
			kunde.idfnr,
			kundemasterplan.tagnr,
			kundemasterplan.urrufzeit,
			kundemasterplan.rufprotokoll,
			kundemasterplan.rufsteuerung,
			kundemasterplan.rufeinstellung,
			kundemasterplan.anruftyp,
			kunde.matchcode,
			kunde.personalnrvertr
		from kundemasterplan,
			kunde
		where kundemasterplan.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
		and kunde.kundennr = kundemasterplan.kundennr
		and kunde.vertriebszentrumnr = kundemasterplan.vertriebszentrumnr
		order by
			kundemasterplan.urrufzeit,
			kunde.idfnr,
			kundemasterplan.rufprotokoll,
			kundemasterplan.rufsteuerung,
			kundemasterplan.rufeinstellung,
			kundemasterplan.anruftyp;
	
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckMasterplan: declare CSelmaster00 %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			fst = 0;
			fclose(fp);
			return -1;
		}
		EXEC SQL open CSelmaster00;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckMasterplan: open CSelmaster00 %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			fst = 0;
			fclose(fp);
			return -1;
		}
		EXEC SQL fetch CSelmaster00 into
			:idfnr,
			:tagnr,
			:urrufzeit,
			:rufprotokoll,
			:rufsteuerung,
			:rufeinstellung,
			:anruftyp,
			:matchcode,
			:personalnrvertr;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckMasterplan: fetch CSelmaster00 %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			fst = 0;
			fclose(fp);
			return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND)
		{
			fst = 0;
			fclose(fp);
			return 1;
		}
	}
	else
	{
		sprintf(error_msg, " AadruckMasterplan: falscher Parameter %2.2s",a->POSART );
		fst = 0;
		fclose(fp);
		return -1;
	}

	strcpy(tagtab,leer);
	sidfnr = idfnr;
	tagtab[atoi(tagnr)*3] = 'J';
	surrufzeit = urrufzeit;
	strcpy(srufprotokoll,rufprotokoll);
	srufsteuerung = rufsteuerung;
	strcpy(srufeinstellung,rufeinstellung);
	strcpy(sanruftyp,anruftyp);
	strcpy(smatchcode,matchcode);
	spersonalnrvertr = personalnrvertr;
}

if ( fst == 1)
{
	for (;; )
	{
		if (funkt == 0)
		{
			strcpy(cSort,"Rufzeit");
			EXEC SQL fetch CSelmaster00 into 
				:idfnr,
				:tagnr,
				:urrufzeit,
				:rufprotokoll,
				:rufsteuerung,
				:rufeinstellung,
				:anruftyp,
				:matchcode,
				:personalnrvertr;
			if (sqlca.sqlcode < 0 )
			{
				sprintf(error_msg, " AadruckMasterplan: fetch CSelmaster00 %ld %ld",
				sqlca.sqlcode , sqlca.sqlerrd[1] );
				fst = 0;
				fclose(fp);
				return -1;
			}
		}
		if (sqlca.sqlcode == SQLNOTFOUND)
		{
			fst = 2;
			break;
		}
		if( surrufzeit == urrufzeit &&
			sidfnr == idfnr &&
			srufprotokoll[0] == rufprotokoll[0] &&
			srufsteuerung == rufsteuerung &&
			srufeinstellung[0] == rufeinstellung[0] &&
			sanruftyp[0] == anruftyp[0])
		{
			tagtab[atoi(tagnr)*3] = 'J';
		}
		else
		{
			zaehler++;
			if ( zaehler == 1 )	/* 1. Zeile Überschrift */
			{
				vurrufzeit = 0;
				fprintf( fp, "%-6s %-10s     %-15s %-7s     %-17s %-5s\n\n",
					"Datum:",cDatum,
					"Masterplan nach",cSort,
					"aktuelle Uhrzeit:",cZeit
					);
				fprintf( fp, "%-7s %-20s %-5s %-2s %-5s %-3s %-7s %-15s %-2s\n",
					"Rufzeit",
					"SO MO DI MI DO FR SA",
					"Prot.",
					"VA",
					"Prio.",
					"Typ",
					"IDF-Nr.",
					"Kurzbezeichnung",
					"VB"
					);
			}
			if (funkt == 0)
			{
				if(vurrufzeit == surrufzeit) strcpy(cRufzeit,"     ");
				else
				{
					ppGTimeToCharHHMM(surrufzeit,cRufzeit);
					vurrufzeit = surrufzeit;
				}
			}
			if(srufprotokoll[0] == '0') strcpy(cProt,"DP");
			else if(srufprotokoll[0] == '1') strcpy(cProt,"DS");
			else if(srufprotokoll[0] == '2') strcpy(cProt,"PH");
			else strcpy(cProt,"DA");
			if(srufeinstellung[0] == '0') strcpy(cRufeinstellung,"M");
			else strcpy(cRufeinstellung,"A");
			fprintf( fp, "%-7s %-20s %-5s %-2s %-5d %-3s %-7d %-15s %-2d\n",
					cRufzeit,
					tagtab,
					cProt,
					cRufeinstellung,
					srufsteuerung,
					sanruftyp,
					sidfnr,
					smatchcode,
					spersonalnrvertr
					);
	
			if ( zaehler == LINE_COUNT2 )	/* alle LINE_COUNT2 Zeilen Fußzeile */
			{
				fprintf( fp, "           %-17s %-2d          %s %d\n\f",
					"Vertriebszentrum:",vznr,
					AET_SEITE,
					++pgcount);
				zaehler = 0;
			}
			strcpy(tagtab,leer);
			sidfnr = idfnr;
			tagtab[atoi(tagnr)*3] = 'J';
			surrufzeit = urrufzeit;
			strcpy(srufprotokoll,rufprotokoll);
			srufsteuerung = rufsteuerung;
			strcpy(srufeinstellung,rufeinstellung);
			strcpy(sanruftyp,anruftyp);
			strcpy(smatchcode,matchcode);
			spersonalnrvertr = personalnrvertr;
		}
		fetchcount++;
		prozcount++;
		if( prozcount > prozent )
		{
			prozcount = 0;
			a->VERTRIEBSZENTRUMNR = (fetchcount*100) / anzahl;
			return 0;
		}
	}
}
if ( fst == 2 )
{
	fst = 3;
	ppGTimeToCharHHMM(surrufzeit,cRufzeit);
	if(srufprotokoll[0] == '0') strcpy(cProt,"DP");
	else if(srufprotokoll[0] == '1') strcpy(cProt,"DS");
	else if(srufprotokoll[0] == '2') strcpy(cProt,"PH");
	else strcpy(cProt,"DA");
	if(srufeinstellung[0] == '0') strcpy(cRufeinstellung,"M");
	else strcpy(cRufeinstellung,"A");
	fprintf( fp, "%-7s %-20s %-5s %-2s %-5d %-3s %-7d %-15s %-2d\n",
			cRufzeit,
			tagtab,
			cProt,
			cRufeinstellung,
			srufsteuerung,
			sanruftyp,
			sidfnr,
			smatchcode,
			spersonalnrvertr
			);

	fprintf( fp, "Ende       %-17s %-2d          %s %d\n\f",
		"Vertriebszentrum:",vznr,
		AET_SEITE,
		++pgcount);
	fclose(fp);
	a->VERTRIEBSZENTRUMNR = 100;
	return 0;
}
sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,vznr);
system(prntcmd);
fst = 0;
return 1;
}

int AadruckNachl_liefer(struct DRUCKPARA *d, char *error_msg)
{
char Out1[11];
FILE *fp;
char outputFile[L_TEXT];
int zaehler,pgcount;
char prntcmd[L_TEXT+8];
char cliefnr[10];
char cdatum_best[11];
char cmenge_best[11];
 
EXEC SQL BEGIN DECLARE SECTION;
struct DRUCKPARA   *a;
long datum;
long datumvon;
long datumbis;
long idfnr;
long kdauftragnr;
long artikel_nr;
long menge;
char nameapo[41];
char kdauftragart[3];
char artikel_name[31];
long liefnr;
long datum_best;
long menge_best;
struct ARTAESEL art;
EXEC SQL END DECLARE SECTION;

a = d;

sprintf( outputFile, "%s/nachllief%d.dat", (char *)getenv( "LOG_PATH" ),a->VERTRIEBSZENTRUMNR );
if ( ( fp = fopen( outputFile, "w" ) ) == (FILE *)0 ) return 1;

if (FREMDSPRACHE)
{
	exec sql free SEL_SPRACHELIEF;
	strcpy( szBuf, "select artikel_name from " ); 
 	strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
 	strcat( szBuf, " where artikel_nr = ?" );
	exec sql prepare SEL_SPRACHELIEF from :szBuf;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_liefer: prepare SEL_SPRACHELIEF %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

}
if(a->DATUM == 0)
{
	datumvon = 0;
	datumbis = 99999999;
}
else
{
	datumvon = datumbis = a->DATUM;
}


	EXEC SQL declare Sel_nachllief scroll cursor with hold for
	select	nachlieferpos.datum,
		nachlieferpos.kdauftragart,
		nachlieferpos.idfnr,
		nachlieferpos.kdauftragnr,
		nachlieferpos.artikel_nr,
		nachlieferpos.menge,
		kunde.nameapo,
		artikelzentral.artikel_name,
		artikelzentral.hersteller_nr
	from nachlieferpos,
		outer (kunde, artikelzentral)
	where nachlieferpos.idfnr = kunde.kundennr
	and nachlieferpos.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
	and nachlieferpos.vertriebszentrumnr = kunde.vertriebszentrumnr
	and nachlieferpos.artikel_nr = artikelzentral.artikel_nr
	and nachlieferpos.postyp = 3
	and nachlieferpos.datum >= :datumvon
	and nachlieferpos.datum <= :datumbis
	and artikelzentral.artikel_nr = nachlieferpos.artikel_nr
	order by artikelzentral.hersteller_nr,nachlieferpos.datum;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_liefer: declare Sel_nachllief %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
EXEC SQL declare Sel_offene_lief scroll cursor with hold for
select 
	BESKOPF.DATUM_BESTELL,
	BESPOSI.MENGE_BESTELL
from BESPOSI,
    BESKOPF
	where BESPOSI.ARTIKEL_NR = :artikel_nr
	and BESKOPF.BESTELL_NR = BESPOSI.BESTELL_NR
	and BESKOPF.FILIALNR = :a->VERTRIEBSZENTRUMNR
	and BESPOSI.FILIALNR = :a->VERTRIEBSZENTRUMNR
	and beskopf.STATUS_AKT in ('A','a','E','e','U','Y')
	and (beskopf.BEST_WIRKSAM='1'
		or (beskopf.BEST_WIRKSAM=' ' and besposi.BEST_WIRKSAM='1'))
	and besposi.menge_bestell > 0
	order by BESKOPF.DATUM_BESTELL desc;

	EXEC SQL open Sel_nachllief;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_liefer: open Sel_nachllief %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}


for (zaehler = 0 , pgcount = 0;; )
{
	EXEC SQL fetch Sel_nachllief into 
		:datum,
		:kdauftragart,
		:idfnr,
		:kdauftragnr,
		:artikel_nr,
		:menge,
		:nameapo,
		:artikel_name,
		:liefnr;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_lief: fetch Sel_nachllief %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND) break;
	if (FREMDSPRACHE)
	{
		EXEC SQL execute SEL_SPRACHELIEF into :artikel_name using :artikel_nr;
	    if (sqlca.sqlcode < 0 )
		{ 
	       sprintf(error_msg, " AadruckNachl_liefer: execute SEL_SPRACHELIEF %ld/%d",
	       sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
	    }
	}
	art.ARTIKEL_NR = artikel_nr;
	AatartSel_Preferred(&art, error_msg);
	AllgDatumLong2CharTTMMJJJJ(datum, Out1);
	zaehler++;
	if ( zaehler == 1 )	/* 1. Zeile Überschrift */
	{
		fprintf( fp, "%-9s %-10s %-10s %-10s %-2s %-7s %-8s %-8s %-5s %-40s %-30s\n",
			"Lieferant",
			AET_DAT_BEST,
			"Best.menge",
			AET_DATUM,
			AET_KZ_AUFTRAGSART,
			AET_IDF_NR,
			AET_AUF_NR,
			AET_PZN,
			AET_MENGE,
			AET_APOTHEKENNAME,
			AET_ARTIKELNAME
			);
	}
	EXEC SQL open Sel_offene_lief;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_lief: open Sel_offene_lief %ld",
			sqlca.sqlcode);
       return -1;
	}
	EXEC SQL fetch Sel_offene_lief into :datum_best,:menge_best;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_lief: open Sel_offene_lief %ld",
			sqlca.sqlcode);
       return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		sprintf (cdatum_best,"%s"," ");
		sprintf (cmenge_best,"%s"," ");
	}
	else
	{
		AllgDatumLong2CharTTMMJJJJ(datum_best, cdatum_best);
		sprintf (cmenge_best,"%d",menge_best);
	}
	
	fprintf( fp, "%-9d %-10s %-10s %-10s %-2s %-7d %-8d %8.8s %-5d %-40s %-30s\n",
		liefnr,
		cdatum_best,
		cmenge_best,
		Out1,
		kdauftragart,
		idfnr,
		kdauftragnr,
		art.ARTICLE_CODE,
		menge,
		nameapo,
		artikel_name
		);
	if ( zaehler == LINE_COUNT )	/* alle LINE_COUNT Zeilen Fußzeile */
	{
		fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
		zaehler = 0;
	}

}
fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
fclose(fp);
sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,a->VERTRIEBSZENTRUMNR);
system(prntcmd);

return 0;
}

int AadruckNachl_vbmoegl(struct DRUCKPARA *d, char *error_msg)
{
	int rc = 0;
	EXEC SQL BEGIN DECLARE SECTION;
		short sNLevelIBT;
		struct DRUCKPARA *a = d;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL select nlevelibt
		into :sNLevelIBT
		from paraauftragbearb
		where filialnr = :a->VERTRIEBSZENTRUMNR;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl: select paraauftragbearb %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	if(sNLevelIBT == 0)
	{
		rc = AadruckNachl_vbmoegl_new(a, error_msg);
	}

	else
	{
		rc = AadruckNachl_vbmoegl_nlevel(a, error_msg);
	}

	return rc;
}

int AadruckNachl_vbmoegl_new(struct DRUCKPARA *d, char *error_msg)
{
	char Out1[11];
	FILE *fp;
	char outputFile[L_TEXT];
	int zaehler,pgcount;
	char prntcmd[L_TEXT+8];
 
	EXEC SQL BEGIN DECLARE SECTION;
		long datum;
		long idfnr;
		long kdauftragnr;
		long artikel_nr;
		long menge;
		char nameapo[41];
		char kdauftragart[3];
		char artikel_name[31];
		long lTime;
		short sWeekday;
		long lRestmenge;
		long lBGANr;
		long lIBTCustomerno;
		short sIBTBranchno;
		struct DRUCKPARA *a = d;
		struct ARTAESEL art;
		long saveidfnr = 0;
		long savekdauftragnr = 0;
		long saveartikel_nr = 0;
	EXEC SQL END DECLARE SECTION;


	sWeekday = (short)ppGGetWeekDay(ppGGetDate(), error_msg);
	lTime = ppGGetTime();
	EXEC SQL drop table tmpvbfilialen;
	EXEC SQL select ibtbranches.ibtbranchno,ibtbranches.ibttype,ibtbranches.ibtcustomerno
		from ibtbranches,zeitarten
		where
			zeitarten.weekday = :sWeekday
			and	zeitarten.zeitart = 2
			and	zeitarten.zeitbegin <= :lTime
			and	zeitarten.zeitende >= :lTime
			and	zeitarten.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
			and	ibtbranches.branchno = :a->VERTRIEBSZENTRUMNR
			and	ibtbranches.ibtbranchno	 = zeitarten.zeitschluessel
			and	ibtbranches.active_flag = 1
		into temp tmpvbfilialen with no log;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_new: select ibtbranches %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}

	if (sqlca.sqlerrd[2] == 0 )
	{
		sprintf(error_msg, " Kein aktiver Verbund ");
		return -2;
	}

	sprintf( outputFile, "%s/vbmoegl%d.dat", (char *)getenv( "LOG_PATH" ),a->VERTRIEBSZENTRUMNR );
	if ( ( fp = fopen( outputFile, "w" ) ) == (FILE *)0 ) return 1;
	if (FREMDSPRACHE)
	{
		strcpy( szBuf, "select artikel_name from " ); 
	 	strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
	 	strcat( szBuf, " where artikel_nr = ?" );
		exec sql prepare SEL_SPRACHE_NEW from :szBuf;
	    if ( sqlca.sqlcode < 0 )
		{
	       sprintf(error_msg, " AadruckNachl_vbmoegl_new: prepare SEL_SPRACHE_NEW %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
	}

	EXEC SQL select bganr_ek into :lBGANr from filiale
		where filialnr = :a->VERTRIEBSZENTRUMNR;

    EXEC SQL BEGIN WORK;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_new: begin work %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL declare CBGANrNew cursor for select ibtcustomerno from tmpvbfilialen for update;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_new: declare CBGANrNew %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL open CBGANrNew;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_new: open CBGANrNew %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	for(;;)
	{
		EXEC SQL fetch CBGANrNew into :lIBTCustomerno;
	    if ( sqlca.sqlcode < 0 )
		{
	       sprintf(error_msg, " AadruckNachl_vbmoegl_new: fetch CBGANrNew %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND) break;
		if (lIBTCustomerno == 0)
		{
			EXEC SQL update tmpvbfilialen
				set ibtcustomerno = :lBGANr
				where current of CBGANrNew;
		}
	    if ( sqlca.sqlcode < 0 )
		{
			EXEC SQL ROLLBACK WORK;
			sprintf(error_msg, " AadruckNachl_vbmoegl_new: update tmpvbfilialen %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
	}
	EXEC SQL close CBGANrNew;

    EXEC SQL COMMIT WORK;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_new: commit work %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL declare CSelvbnew scroll cursor with hold for
	select unique
		nachlieferpos.datum,
		nachlieferpos.kdauftragart,
		nachlieferpos.idfnr,
		nachlieferpos.kdauftragnr,
		nachlieferpos.artikel_nr,
		nachlieferpos.menge,
		kunde.nameapo,
		artikelzentral.artikel_name,
		tmpvbfilialen.ibtcustomerno,
		tmpvbfilialen.ibtbranchno
		from nachlieferpos,
		artikelzentral,
		artikellokal lok,
		artikellokal ibt,
		tmpvbfilialen,
		kunde
	where artikelzentral.artikel_nr			=	nachlieferpos.artikel_nr
		and nachlieferpos.vertriebszentrumnr	=	:a->VERTRIEBSZENTRUMNR
		and kunde.vertriebszentrumnr			=	:a->VERTRIEBSZENTRUMNR
		and	ibt.filialnr						!=	:a->VERTRIEBSZENTRUMNR
		and lok.artikel_nr						=	nachlieferpos.artikel_nr
		and lok.filialnr						=	:a->VERTRIEBSZENTRUMNR
		and lok.verbundartikel					!=	0
		and (
			(lok.verbundartikel					in	(1,7,8,9)	
			and	tmpvbfilialen.ibttype			in	(0,4))
			or  (lok.verbundartikel				=	2
			and tmpvbfilialen.ibttype			=	1)
			or  (lok.verbundartikel				=	3		
			and	tmpvbfilialen.ibttype			=	2)
			or  (lok.verbundartikel				in	(4,6,8,9)		
			and	tmpvbfilialen.ibttype			=	3)
			or  (lok.verbundartikel				in	(5,6,7,9)
			and	tmpvbfilialen.ibttype			=	5))
		and ibt.verbundartikel					!=	0
		and nachlieferpos.postyp				=	3
		and nachlieferpos.status				!=	2
		and nachlieferpos.artikel_nr			=	ibt.artikel_nr
		and ibt.bestand							>	nachlieferpos.menge
		and	ibt.filialnr						=	tmpvbfilialen.ibtbranchno
		and	ibt.filialnr						!=	nachlieferpos.vertriebszentrumnr
		and nachlieferpos.idfnr					=	kunde.kundennr
		order by nachlieferpos.idfnr,nachlieferpos.artikel_nr,nachlieferpos.kdauftragnr;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_new: declare CSelvbnew %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
	EXEC SQL open CSelvbnew;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_new: open CSelvbnew %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
	for (zaehler = 0 , pgcount = 0;; )
	{
		EXEC SQL fetch CSelvbnew into 
			:datum,
			:kdauftragart,
			:idfnr,
			:kdauftragnr,
			:artikel_nr,
			:menge,
			:nameapo,
			:artikel_name,
			:lIBTCustomerno,
			:sIBTBranchno;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_new: fetch CSelvbnew %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND) break;

		/* Quota des Kunde prüfen */
		EXEC SQL select quota-kumqty into :lRestmenge
			from articlequota
			where branchno = :a->VERTRIEBSZENTRUMNR
			and articleno = :artikel_nr
			and customerno = :idfnr;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_new: select quota Kunde %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == 0 && lRestmenge < menge) continue;

		/* Quota der Shuttle-IDF prüfen */
		EXEC SQL select quota-kumqty into :lRestmenge
			from articlequota
			where branchno = :sIBTBranchno
			and articleno = :artikel_nr
			and customerno = :lIBTCustomerno;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: select quota VB-Idf %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == 0 && lRestmenge < menge) continue;

		if(saveidfnr == idfnr && savekdauftragnr == kdauftragnr && saveartikel_nr == artikel_nr) continue;	/* pro nachlieferpos nur einmal ausgeben */
		saveidfnr = idfnr;
		savekdauftragnr = kdauftragnr;
		saveartikel_nr = artikel_nr;


		if (FREMDSPRACHE)
		{
			EXEC SQL execute SEL_SPRACHE_NEW into :artikel_name using :artikel_nr;
		    if (sqlca.sqlcode < 0 )
			{ 
		       sprintf(error_msg, " AadruckNachl_vbmoegl_new: execute SEL_SPRACHE_NEW %ld/%d",
		       sqlca.sqlcode, sqlca.sqlerrd[1]);
		       return -1;
		    }
		}
		art.ARTIKEL_NR = artikel_nr;
		AatartSel_Preferred(&art, error_msg);
		AllgDatumLong2CharTTMMJJJJ(datum, Out1);
		zaehler++;
		if ( zaehler == 1 )	/* 1. Zeile Überschrift */
		{
			fprintf( fp, "%-10s %-2s %-7s %-8s %-13s %-5s %-40s %-30s\n",
				AET_DATUM,
				AET_KZ_AUFTRAGSART,
				AET_IDF_NR,
				AET_AUF_NR,
				AET_PZN,
				AET_MENGE,
				AET_APOTHEKENNAME,
				AET_ARTIKELNAME
				);
		}
	
		fprintf( fp, "%-10s %-2s %-7d %-8d %13.13s %-5d %-40s %-30s\n",
			Out1,
			kdauftragart,
			idfnr,
			kdauftragnr,
			art.ARTICLE_CODE,
			menge,
			nameapo,
			artikel_name
			);
		if ( zaehler == LINE_COUNT )	/* alle LINE_COUNT Zeilen Fußzeile */
		{
			fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
			zaehler = 0;
		}
	}

	fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
	fclose(fp);
	sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,a->VERTRIEBSZENTRUMNR);
	system(prntcmd);

	EXEC SQL close CSelvbnew;

	EXEC SQL drop table tmpvbfilialen;

	return 0;
}

int AadruckNachl_vbmoegl_nlevel(struct DRUCKPARA *d, char *error_msg)
{
	char Out1[11];
	FILE *fp;
	char outputFile[L_TEXT];
	int zaehler,pgcount;
	char prntcmd[L_TEXT+8];
 
	EXEC SQL BEGIN DECLARE SECTION;
		long datum;
		long idfnr;
		long kdauftragnr;
		long artikel_nr;
		long menge;
		char nameapo[41];
		char kdauftragart[3];
		char artikel_name[31];
		long lTime;
		long lRestmenge;
		long lBGANr;
		long lIBTCustomerno;
		short sIBTBranchno;
		short sWeekday;
		struct DRUCKPARA *a = d;
		struct ARTAESEL art;
		long saveidfnr = 0;
		long savekdauftragnr = 0;
		long saveartikel_nr = 0;
	EXEC SQL END DECLARE SECTION;

	sWeekday = (short)ppGGetWeekDay(ppGGetDate(), error_msg);
	lTime = ppGGetTime();

	EXEC SQL drop table tmpvbfilialen;
	EXEC SQL select ibtbranches.ibtbranchno,ibtbranches.nlevelibttypeid,ibtbranches.nlevelibtassortmenttypeid,ibtbranches.ibtcustomerno
		from ibtbranches,zeitarten
		where
			zeitarten.weekday = :sWeekday
			and	zeitarten.zeitart = 2
			and	zeitarten.zeitbegin <= :lTime
			and	zeitarten.zeitende >= :lTime
			and	zeitarten.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
			and	ibtbranches.branchno = :a->VERTRIEBSZENTRUMNR
			and	ibtbranches.ibtbranchno	 = zeitarten.zeitschluessel
			and	ibtbranches.active_flag = 1
		into temp tmpvbfilialen with no log;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_nlevelibt: select ibtbranches %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}

	if (sqlca.sqlerrd[2] == 0 )
	{
		sprintf(error_msg, " Kein aktiver Verbund ");
		return -2;
	}

	sprintf( outputFile, "%s/vbmoegl%d.dat", (char *)getenv( "LOG_PATH" ),a->VERTRIEBSZENTRUMNR );
	if ( ( fp = fopen( outputFile, "w" ) ) == (FILE *)0 ) return 1;
	if (FREMDSPRACHE)
	{
		strcpy( szBuf, "select artikel_name from " ); 
	 	strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
	 	strcat( szBuf, " where artikel_nr = ?" );
		exec sql prepare SEL_SPRACHE_NLEVEL from :szBuf;
	    if ( sqlca.sqlcode < 0 )
		{
	       sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: prepare SEL_SPRACHE_NLEVEL %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
	}

	EXEC SQL select bganr_ek into :lBGANr from filiale
		where filialnr = :a->VERTRIEBSZENTRUMNR;

    EXEC SQL BEGIN WORK;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: begin work %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL declare CBGANrNlevel cursor for select ibtcustomerno from tmpvbfilialen for update;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: declare CBGANrNlevel %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL open CBGANrNlevel;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_new: open CBGANrNlevel %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	for(;;)
	{
		EXEC SQL fetch CBGANrNlevel into :lIBTCustomerno;
	    if ( sqlca.sqlcode < 0 )
		{
	       sprintf(error_msg, " AadruckNachl_vbmoegl_new: fetch CBGANrNlevel %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND) break;
		if (lIBTCustomerno == 0)
		{
			EXEC SQL update tmpvbfilialen
				set ibtcustomerno = :lBGANr
				where current of CBGANrNlevel;
		}
	    if ( sqlca.sqlcode < 0 )
		{
			EXEC SQL ROLLBACK WORK;
			sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: update tmpvbfilialen %ld/%d",
			   sqlca.sqlcode, sqlca.sqlerrd[1]);
	       return -1;
		}
	}
	EXEC SQL close CBGANrNlevel;
	EXEC SQL COMMIT WORK;
    if ( sqlca.sqlcode < 0 )
	{
       sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: commit work %ld/%d",
		   sqlca.sqlcode, sqlca.sqlerrd[1]);
       return -1;
	}

	EXEC SQL declare CSelvbnlevel scroll cursor with hold for
	select unique
		nachlieferpos.datum,
		nachlieferpos.kdauftragart,
		nachlieferpos.idfnr,
		nachlieferpos.kdauftragnr,
		nachlieferpos.artikel_nr,
		nachlieferpos.menge,
		kunde.nameapo,
		artikelzentral.artikel_name,
		tmpvbfilialen.ibtcustomerno,
		tmpvbfilialen.ibtbranchno
		from nachlieferpos,
		ibtbrancharticleconfig,
		artikelzentral,
		artikellokal lok,
		artikellokal ibt,
		tmpvbfilialen,
		kunde
	where artikelzentral.artikel_nr			=	nachlieferpos.artikel_nr
		and nachlieferpos.vertriebszentrumnr	=	:a->VERTRIEBSZENTRUMNR
		and kunde.vertriebszentrumnr			=	:a->VERTRIEBSZENTRUMNR
		and	ibt.filialnr						!=	:a->VERTRIEBSZENTRUMNR
		and lok.artikel_nr						=	nachlieferpos.artikel_nr
		and lok.filialnr						=	:a->VERTRIEBSZENTRUMNR
		and ibtbrancharticleconfig.branchno		=	lok.filialnr
		and ibtbrancharticleconfig.articleno	=	lok.artikel_nr
		and ibtbrancharticleconfig.ibttypeid	=	tmpvbfilialen.nlevelibttypeid
		and ibtbrancharticleconfig.ibtassortmenttypeid	=	tmpvbfilialen.nlevelibtassortmenttypeid
		and nachlieferpos.postyp				=	3
		and nachlieferpos.status				!=	2
		and nachlieferpos.artikel_nr			=	ibt.artikel_nr
		and ibt.bestand							>	nachlieferpos.menge
		and	ibt.filialnr						=	tmpvbfilialen.ibtbranchno
		and	ibt.filialnr						!=	nachlieferpos.vertriebszentrumnr
		and nachlieferpos.idfnr					=	kunde.kundennr
		order by nachlieferpos.idfnr,nachlieferpos.artikel_nr,nachlieferpos.kdauftragnr;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: declare CSelvbnlevel %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
	EXEC SQL open CSelvbnlevel;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: open CSelvbnlevel %ld %ld",
		sqlca.sqlcode , sqlca.sqlerrd[1] );
		return -1;
	}
	for (zaehler = 0 , pgcount = 0;; )
	{
		EXEC SQL fetch CSelvbnlevel into 
			:datum,
			:kdauftragart,
			:idfnr,
			:kdauftragnr,
			:artikel_nr,
			:menge,
			:nameapo,
			:artikel_name,
			:lIBTCustomerno,
			:sIBTBranchno;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: fetch CSelvbnlevel %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == SQLNOTFOUND) break;

		/* Quota des Kunden prüfen */
		EXEC SQL select quota-kumqty into :lRestmenge
			from articlequota
			where branchno = :a->VERTRIEBSZENTRUMNR
			and articleno = :artikel_nr
			and customerno = :idfnr;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: select quota Kunde %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == 0 && lRestmenge < menge) continue;

		/* Quota der Shuttle-IDF prüfen */
		EXEC SQL select quota-kumqty into :lRestmenge
			from articlequota
			where branchno = :sIBTBranchno
			and articleno = :artikel_nr
			and customerno = :lIBTCustomerno;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: select quota VB-Idf %ld %ld",
			sqlca.sqlcode , sqlca.sqlerrd[1] );
			return -1;
		}
		if (sqlca.sqlcode == 0 && lRestmenge < menge) continue;

		if(saveidfnr == idfnr && savekdauftragnr == kdauftragnr && saveartikel_nr == artikel_nr) continue;	/* pro nachlieferpos nur einmal ausgeben */
		saveidfnr = idfnr;
		savekdauftragnr = kdauftragnr;
		saveartikel_nr = artikel_nr;

		if (FREMDSPRACHE)
		{
			EXEC SQL execute SEL_SPRACHE_NLEVEL into :artikel_name using :artikel_nr;
		    if (sqlca.sqlcode < 0 )
			{ 
		       sprintf(error_msg, " AadruckNachl_vbmoegl_nlevel: execute SEL_SPRACHE_NLEVEL %ld/%d",
		       sqlca.sqlcode, sqlca.sqlerrd[1]);
		       return -1;
		    }
		}
		art.ARTIKEL_NR = artikel_nr;
		AatartSel_Preferred(&art, error_msg);
		AllgDatumLong2CharTTMMJJJJ(datum, Out1);
		zaehler++;
		if ( zaehler == 1 )	/* 1. Zeile Überschrift */
		{
			fprintf( fp, "%-10s %-2s %-7s %-8s %-13s %-5s %-40s %-30s\n",
				AET_DATUM,
				AET_KZ_AUFTRAGSART,
				AET_IDF_NR,
				AET_AUF_NR,
				AET_PZN,
				AET_MENGE,
				AET_APOTHEKENNAME,
				AET_ARTIKELNAME
				);
		}
	
		fprintf( fp, "%-10s %-2s %-7d %-8d %13.13s %-5d %-40s %-30s\n",
			Out1,
			kdauftragart,
			idfnr,
			kdauftragnr,
			art.ARTICLE_CODE,
			menge,
			nameapo,
			artikel_name
			);
		if ( zaehler == LINE_COUNT )	/* alle LINE_COUNT Zeilen Fußzeile */
		{
			fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
			zaehler = 0;
		}
	}

	fprintf( fp, "                       %s %d\n\f",AET_SEITE,++pgcount);
	fclose(fp);
	sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,a->VERTRIEBSZENTRUMNR);
	system(prntcmd);

	EXEC SQL close CSelvbnlevel;

	EXEC SQL drop table tmpvbfilialen;

	return 0;
}
