#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aatour.h"
#include "allg.h"
#include "texte.h"
#include "aeorderstat.h"
 
EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define NOT_FOUND        1
#define FILE_NOT_FOUND   1
#define ERROR           -1
#define WARNING         -2

extern long UID;


int AatourSel_tour_uebers(struct TOURUEBERS *d, char *error_msg)
{

/*in a->TOURSTRECKE wird die FilialNr mit∆bergeben!*/

static int fst = 1;
int i;

EXEC SQL BEGIN DECLARE SECTION;
struct TOURUEBERS   *a;
char   TOUR[L_TOURUEBERS_TOURID + 1 ];
char   TOURZEIT[L_TOURUEBERS_TOURID + 1 ];
char   KDAUFTRAGSTAT[L_TOURINHALT_KDAUFTRAGSTAT];
long   ANZBEHAELT;
long	DATUM;
EXEC SQL END DECLARE SECTION;

a = d;

a->ANZ_ERFASST	= 0;
a->ANZ_FAKTUR	= 0;
a->ANZ_WANNEN	= 0;
ANZBEHAELT		= 0;

if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
	DATUM = AllgGetDate();
	AllgMakeToLike(a->BEZEICHNUNG,L_TOURUEBERS_BEZEICHNUNG);
	if( a->TOURID[4] != '?' && a->TOURID[0] == '?' ) /* nur Bahnhof gesetzt */
	{
		/* alle Zeiten f∆r diesen Bahnhof ermitteln */
		for(i=0;i<4;i++) TOUR[i] = '_';
		for(i=4;i<6;i++) TOUR[i] = a->TOURID[i];
		TOUR[6] = '\0';
		AllgStrCopy(TOURZEIT,"000000",L_TOURUEBERS_TOURID); /* alle Zeiten */
	}
	else if( a->TOURID[4] == '?' && a->TOURID[0] != '?' ) /* nur Zeit gesetzt */
	{
		TOUR[0] = '%';
		TOUR[1] = '\0';
		for(i=0;i<4;i++) TOURZEIT[i] = a->TOURID[i];
		for(i=4;i<6;i++) TOURZEIT[i] = '0';
		TOURZEIT[6] = '\0';
	}
	else if( a->TOURID[4] == '?' && a->TOURID[0] == '?' ) /* nichts gesetzt */
	{
		TOUR[0] = '%';
		TOUR[1] = '\0';
		AllgStrCopy(TOURZEIT,"000000",L_TOURUEBERS_TOURID); /* alle Zeiten */
	}
	else /* gesammte Tour */
	{
		if (a->TOURSTAT[0] == '1') /* Zeit und Tour wurde separat eingegeben */
		{
			for(i=0;i<4;i++) TOUR[i] = '_';
			for(i=4;i<6;i++) TOUR[i] = a->TOURID[i];
			TOUR[6] = '\0';
			for(i=0;i<4;i++) TOURZEIT[i] = a->TOURID[i];
			for(i=4;i<6;i++) TOURZEIT[i] = '0';
			TOURZEIT[6] = '\0';
		}
		else
		{
			TOUR[0] = '%';
			TOUR[1] = '\0';
		}
		AllgStrCopy(TOURZEIT,a->TOURID,L_TOURUEBERS_TOURID); /* alle Zeiten */
	}

	EXEC SQL declare Sel_tour_uebers scroll cursor with hold for
	select 
		TOUR.TOURID,
		TOUR.BEZEICHNUNG,
		TOUR.TOURSTAT,
		TOUR.DRUCKSTAT,
		TOUR.VORABSCHEINDRUCKEN,
		TOUR.FAHRTZEIT,  
		TOUR.TOURSTRECKE,
		TOUR.DRUCKFACHNR
	from 
		tour
	where  
		TOUR.DATUMKOMMI		=		:DATUM				and
		TOUR.TOURID			like	:TOUR				and
		TOUR.TOURID			>=		:TOURZEIT			and
 		TOUR.BEZEICHNUNG	like	:a->BEZEICHNUNG		and
		TOUR.FILIALNR		=		:a->TOURSTRECKE
		order by TOURID;

    EXEC SQL open Sel_tour_uebers;
    if (sqlca.sqlcode < 0 )
      {
		fst = 1;
		sprintf(error_msg, " AatourSel_tour_uebers: open Sel_tour_uebers %ld",
				sqlca.sqlcode);
		return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_tour_uebers;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AatourSel_tour_uebers: close Sel_tour_uebers %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_tour_uebers
	into 
		:a->TOURID,
		:a->BEZEICHNUNG,
		:a->TOURSTAT,
		:a->DRUCKSTAT,
		:a->VORABSCHEINDRUCKEN,
		:a->FAHRTZEIT,  
		:a->TOURSTRECKE,
		:a->DRUCKFACHNR;
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AatourSel_tour_uebers: fetch Sel_tour_uebers %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_tour_uebers;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

EXEC SQL declare Sel_Knd_Tou cursor with hold for
select 
	KDAUFTRAGSTAT,
	ANZBEHAELT
from 
	kdauftrag
where  
	tourid = :a->TOURID;

EXEC SQL open Sel_Knd_Tou;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourSel_tour_uebers: open Sel_Knd_Tou %ld",
			sqlca.sqlcode);
	return -1;
}

for(;;)
{
	EXEC SQL fetch Sel_Knd_Tou
		into 
		:KDAUFTRAGSTAT,
		:ANZBEHAELT;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AatourSel_tour_uebers: fetch Sel_Knd_Tou %ld",
		sqlca.sqlcode);
		EXEC SQL close Sel_tour_uebers;
		return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		EXEC SQL close Sel_Knd_Tou;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AatourSel_tour_uebers: close Sel_tour_uebers %ld",
			sqlca.sqlcode);
			return -1;
		}
		break;
	}
	else
	{
		if ( KDAUFTRAGSTAT[AEORD_POS_ERFASST]	  == '1' ) a->ANZ_ERFASST++;
		if ( KDAUFTRAGSTAT[AEORD_POS_FAKTUR_ENDE] == '1' ) a->ANZ_FAKTUR++;
		a->ANZ_WANNEN += ANZBEHAELT; 
	}
}
return 0;
}

int AatourGet_tour_kopf(struct TOURUEBERS *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct TOURUEBERS   *a;
char   KDAUFTRAGSTAT[L_TOURINHALT_KDAUFTRAGSTAT];
long   ANZBEHAELT;
long DATUM;
EXEC SQL END DECLARE SECTION;

a = d;

a->ANZ_ERFASST	= 0;
a->ANZ_FAKTUR	= 0;
a->ANZ_WANNEN	= 0;
ANZBEHAELT		= 0;

DATUM = AllgGetDate();

EXEC SQL select 
		TOUR.TOURID,
		TOUR.BEZEICHNUNG,
		TOUR.TOURSTAT,
		TOUR.DRUCKSTAT,
		TOUR.VORABSCHEINDRUCKEN,
		TOUR.FAHRTZEIT,  
		TOUR.TOURSTRECKE,
		TOUR.DRUCKFACHNR
	into 
		:a->TOURID,
		:a->BEZEICHNUNG,
		:a->TOURSTAT,
		:a->DRUCKSTAT,
		:a->VORABSCHEINDRUCKEN,
		:a->FAHRTZEIT,  
		:a->TOURSTRECKE,
		:a->DRUCKFACHNR
	from 
		tour
	where  
		TOUR.TOURID		=	:a->TOURID		and
		TOUR.DATUMKOMMI	=	:DATUM			and
		TOUR.FILIALNR	=	:a->TOURSTRECKE;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourGet_tour_kopf select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }

EXEC SQL declare Sel_Knd_Tou2 cursor with hold for
select 
	KDAUFTRAGSTAT,
	ANZBEHAELT
from 
	kdauftrag
where  
	tourid = :a->TOURID;

EXEC SQL open Sel_Knd_Tou2;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourGet_tour_kopf: open Sel_Knd_Tou2 %ld",
			sqlca.sqlcode);
	return -1;
}

for(;;)
{
	EXEC SQL fetch Sel_Knd_Tou2
	into 
		:KDAUFTRAGSTAT,
		:ANZBEHAELT;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AatourGet_tour_kopf: fetch Sel_Knd_Tou2 %ld",
		sqlca.sqlcode);
		EXEC SQL close Sel_Knd_Tou2;
		return -1;
	}
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		EXEC SQL close Sel_Knd_Tou2;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AatourGet_tour_kopf: close Sel_Knd_Tou2 %ld",
			sqlca.sqlcode);
			return -1;
		}
		break;
	}
	else
	{
		if ( KDAUFTRAGSTAT[AEORD_POS_ERFASST]	  == '1' ) a->ANZ_ERFASST++;
		if ( KDAUFTRAGSTAT[AEORD_POS_FAKTUR_ENDE] == '1' ) a->ANZ_FAKTUR++;
		a->ANZ_WANNEN += ANZBEHAELT; 
	}
}

return 0;
}

int AatourSel_auf_tour(struct TOURINHALT *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct TOURINHALT   *a;
long DATUM;
short indi2;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
	DATUM = AllgGetDate();
    EXEC SQL declare Sel_auf_tour scroll cursor with hold for
		select TOURINHALT_LISTE
	from kdauftrag, kunde, tourplantag
	where 
		KDAUFTRAG.TOURID				= :a->TOURID					and
		KDAUFTRAG.VERTRIEBSZENTRUMNR	= :a->ANZBTM					and
		KUNDE.VERTRIEBSZENTRUMNR		= KDAUFTRAG.VERTRIEBSZENTRUMNR	and
		KUNDE.KUNDENNR					= KDAUFTRAG.KUNDENNR			and
		TOURPLANTAG.VERTRIEBSZENTRUMNR	= KDAUFTRAG.VERTRIEBSZENTRUMNR	and
		TOURPLANTAG.KUNDENNR			= KDAUFTRAG.KUNDENNR			and
		TOURPLANTAG.TOURID				= :a->TOURID					and
		TOURPLANTAG.DATUMKOMMI			= :DATUM
	order by TOURPLANTAG.REIHENFOLGENR;

     EXEC SQL open Sel_auf_tour;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AatourSel_auf_tour: open Sel_auf_tour %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_auf_tour;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AatourSel_auf_tour: close Sel_auf_tour %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_auf_tour into 
	:a->KDAUFTRAGNR, 
	:a->KDAUFTRAGSTAT, 
	:a->IDFNR, 
	:a->TOURID, 
	:a->KDAUFTRAGART, 
	:a->ANZBTM, 
	:a->ANZCONTAINER, 
	:a->ANZBEHAELTWECHSEL, 
	:a->ANZBEHAELT, 
	:a->ANZSONDERWANNE, 
	:a->NAMEAPO, 
	:a->ORT, 
	:a->REIHENFOLGENR indicator :indi2, 
	:a->TOURIDALT,
	:a->TELKURZWAHL;

if (indi2 < 0) a->REIHENFOLGENR = 0;
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AatourSel_auf_tour: fetch Sel_auf_tour %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_auf_tour;
   return -1;									 
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AatourUpd_sond_wann(struct TOURINHALT *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct TOURINHALT   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_sond_wann commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
EXEC SQL update kdauftrag
set 
	ANZSONDERWANNE	= :a->ANZSONDERWANNE
where 
	KDAUFTRAGNR		= :a->KDAUFTRAGNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourUpd_sond_wann update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_sond_wann commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
return 0;
}

int AatourUpd_auf_tour(struct TOURINHALT *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct TOURINHALT   *a;
int ANZ;
long DATUM;
long kundennr;
short vz;
long zeit;
long uid;
EXEC SQL END DECLARE SECTION;

a = d;
uid = UID;
DATUM = AllgGetDate();

/* Kundennummer und TOURIDALT bestimmen */
EXEC SQL   select 
	IDFNR,
	TOURID
into
	:a->IDFNR,
	:a->TOURIDALT
from kdauftrag
where 
	kdauftragnr = :a->KDAUFTRAGNR;
if (sqlca.sqlcode != 0 )
  {
   sprintf(error_msg, " AatourUpd_auf_tour select kdauftrag%ld",
   sqlca.sqlcode);
   return -1;
  }

/* Kontrolle ob die Tour existiert */
EXEC SQL   select 
	count(*)
into
	:ANZ
from tour
where 
	tourid     = :a->TOURID	and
	datumkommi = :DATUM;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourUpd_auf_tour select tour%ld",
   sqlca.sqlcode);

   return -1;
  }
if( ANZ == 0 ) /* Tour fuer den Kunden nicht vorgesehen */
{
   strcpy(error_msg, TXT_TOUR_NICHT_VORH);
   return -2;
}

/* Kontrolle ob dem Kunden die Tour zugeordnet ist */
EXEC SQL   select 
	count(*)
into
	:ANZ
from tourplantag
where 
	idfnr      = :a->IDFNR	and
	tourid     = :a->TOURID	and
	datumkommi = :DATUM;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourUpd_auf_tour select %ld",
   sqlca.sqlcode);
   return -1;
  }
if( ANZ == 0 ) /* Tour fuer den Kunden nicht vorgesehen */
{
	if(a->ANZBTM != 1) /* Warnung wurde noch nicht ausgegeben */
	{
		return 1;
	}
	else	/* Tour f∆r den Kunden aufnehmen */
	{
		zeit = AllgGetTime();
		EXEC SQL select
			kundennr,
			vertriebszentrumnr
			into
			:kundennr,
			:vz
			from kunde
			where idfnr = :a->IDFNR;

		EXEC SQL begin work;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AatourUpd_auf_tour commit work %ld %ld",
			sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
		EXEC SQL insert into tourplantag
			(
			IDFNR,
			DATUMKOMMI,
			TOURID,
			REIHENFOLGENR,
			FAHRTZEIT,
			VERTRIEBSZENTRUMNR,
			KUNDENNR,
			TM_DATE,
			TM_TIME,
			LOGINID,
			CHANGEID
			)
		values
			(
			:a->IDFNR,         
			:DATUM,    
			:a->TOURID,        
			:a->REIHENFOLGENR, 
			1,
			:vz,
			:kundennr,
			:DATUM,
			:zeit,
			:uid,
			'I'
			);
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AatourUpd_auf_tour insert %ld",
			sqlca.sqlcode);
			return -1;
		}
		EXEC SQL commit work;
		if (sqlca.sqlcode < 0 )
		{
			sprintf(error_msg, " AatourUpd_auf_tour commit work %ld %ld",
			sqlca.sqlcode, sqlca.sqlerrd[1]);
			return -1;
		}
	}
} /* Ende if Tour fuer diesen Kunden nicht vorgesehen */

/* Aenderung der Tour auf dem Auftrag */
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_auf_tour commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}

EXEC SQL update kdauftrag
set 
	TOURID		= :a->TOURID,
	TOURIDALT	= :a->TOURIDALT
where 
	KDAUFTRAGNR		= :a->KDAUFTRAGNR;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourUpd_auf_tour update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_auf_tour commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
return 0;
}

int AatourUpd_folgenr(struct TOURINHALT *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct TOURINHALT   *a;
long DATUM;
EXEC SQL END DECLARE SECTION;

a = d;
DATUM = AllgGetDate();

/* Kundennummer */
EXEC SQL   select 
	IDFNR
into
	:a->IDFNR
from kdauftrag
where 
	kdauftragnr = :a->KDAUFTRAGNR;
if (sqlca.sqlcode != 0 )
  {
   sprintf(error_msg, " AatourUpd_folgenr select kdauftrag%ld",
   sqlca.sqlcode);
   return -1;
  }


EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_folgenr commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
EXEC SQL update tourplantag
set 
	reihenfolgenr = :a->REIHENFOLGENR
where 
	idfnr      = :a->IDFNR	and
	tourid     = :a->TOURID	and
	datumkommi = :DATUM;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AatourUpd_folgenr update %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AatourUpd_folgenr commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
return 0;
}

