#include <stdio.h>
#include <string.h>
#include "kndsel.h"
#include "tm.h"
#include <time.h>
#include "allg.h"
#include "texte.h"
#include "ppgeneric.h"
EXEC SQL include sqlca;

int AafilGetdatetime(struct TM *vez, char *error_msg);

static long lZeitbeginn,lZeitende;
static short sVzNr;
 
int AakundeSel_kndnr(struct KNDSEL *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDSEL   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select KNDSEL_LISTE into KNDSEL_ZEIGER(a) from kunde,kundeschalter
where kunde.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and kunde.kundennr = :a->KUNDENNR
and	kundeschalter.kundennr = kunde.kundennr
and	kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr
and	kundeschalter.skdkundeaegesperrt <= :a->SKDKUNDEAEGESPERRT;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_kndnr select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, TXT_KEIN_KUNDE_IDF);
   return -2;
  }
return 0;
}

int AakundeSel_idf(struct KNDSEL *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDSEL   *a;
int vz_von;
int vz_bis;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
   	fst = 0;
    
	if (a->VERTRIEBSZENTRUMNR != 0)
	{
		vz_von = a->VERTRIEBSZENTRUMNR;
		vz_bis = a->VERTRIEBSZENTRUMNR;
	}
	else
	{
		vz_von = 0;
		vz_bis = 99;
	}

    EXEC SQL declare Sel_idf scroll cursor with hold for
		select KNDSEL_LISTE
		from kunde,kundeschalter
		where 	kunde.idfnr = :a->IDFNR and
				kunde.vertriebszentrumnr	<=	:vz_bis and 
				kunde.vertriebszentrumnr	>=	:vz_von and
				kundeschalter.kundennr = kunde.kundennr and
				kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr and
				kundeschalter.skdkundeaegesperrt <= :a->SKDKUNDEAEGESPERRT and
				kunde.vertriebszentrumnr in (
                    select RegionArten.RegionTeilNr from RegionArten
		             where RegionArten.RegionNr= :a->REGIONNR and 
                           RegionArten.RegionenTyp=1)
		order by nameapo, ort, originalfilialnr;

    EXEC SQL open Sel_idf;
    if (sqlca.sqlcode < 0 )
      {
       	fst = 1;
   		sprintf(error_msg, " AakundeSel_idf: open Sel_idf %ld",
        	sqlca.sqlcode);
        return -1;
      }
   } /* Ende OPEN */

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_idf;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_idf: close Sel_idf %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_idf into KNDSEL_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_idf: fetch Sel_idf %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_idf;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }
return 0; 
}

int AakundeSel_mc(struct KNDSEL *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDSEL   *a;
int fili_von;
int fili_bis;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
   	fst = 0;
    
	if (a->VERTRIEBSZENTRUMNR != 0)
	{
		fili_von = a->VERTRIEBSZENTRUMNR;
		fili_bis = a->VERTRIEBSZENTRUMNR;
	}
	else
	{
		fili_von = 0;
		fili_bis = 99;
	}

    AllgMakeToLike(a->MATCHCODE,L_KNDSEL_MATCHCODE);
	AllgMakeToLike(a->NAMEINHABER,L_KNDSEL_NAMEINHABER);
    AllgMakeToLike(a->ORT,L_KNDSEL_ORT);
    
    EXEC SQL declare Sel_mc scroll cursor with hold for
		select KNDSEL_LISTE
		from kunde,kundeschalter
		where 	kunde.matchcode 	like :a->MATCHCODE and
				kunde.nameinhaber	like :a->NAMEINHABER and
				kunde.ort			like :a->ORT and
				kunde.vertriebszentrumnr	<=	:fili_bis and 
				kunde.vertriebszentrumnr	>=	:fili_von and
				kundeschalter.kundennr = kunde.kundennr and
				kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr and
				kundeschalter.skdkundeaegesperrt <= :a->SKDKUNDEAEGESPERRT and
				kunde.vertriebszentrumnr in (
                    select RegionArten.RegionTeilNr from RegionArten
		             where RegionArten.RegionNr= :a->REGIONNR and 
                           RegionArten.RegionenTyp=1)
		order by nameapo, ort, originalfilialnr;

    EXEC SQL open Sel_mc;
    if (sqlca.sqlcode < 0 )
      {
       	fst = 1;
   		sprintf(error_msg, " AakundeSel_mc: open Sel_mc %ld %s",
        	sqlca.sqlcode,sqlca.sqlerrm);
        return -1;
      }
   } /* Ende OPEN */

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_mc;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_mc: close Sel_mc %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_mc into KNDSEL_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_mc: fetch Sel_mc %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_mc;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }
return 0; 
}

int AakundeSel_knd_info(struct KNDINF *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDINF   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select KNDINF_LISTE into KNDINF_ZEIGER(a) from kunde,kundeschalter
where kunde.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and kunde.kundennr = :a->KUNDENNR
and kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr
and kundeschalter.kundennr = kunde.kundennr;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_knd_info select %ld/%ld %s",
   sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, TXT_KEIN_KUNDE_IDF);
   return -2;
  }
return 0;
}

int AakundeSel_aufart(struct KNDAUFART *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDAUFART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
     EXEC SQL declare Sel_aufart scroll cursor with hold for
select KNDAUFART_LISTE
from auftragartkd
where auftragartkd.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and auftragartkd.kundennr = :a->KUNDENNR  ;

     EXEC SQL open Sel_aufart;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AakundeSel_aufart: open Sel_aufart %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_aufart;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_aufart: close Sel_aufart %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_aufart into KNDAUFART_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_aufart: fetch Sel_aufart %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_aufart;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AakundeSel_offen(struct KNDOFFEN *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
short sWeekday;
struct KNDOFFEN   *a;
EXEC SQL END DECLARE SECTION;

a = d;
sWeekday = (short)ppGGetWeekDay(ppGGetDate(), error_msg);

EXEC SQL select KNDOFFEN_LISTE into KNDOFFEN_ZEIGER(a)
from kdbetriebsende
where kdbetriebsende.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and kdbetriebsende.kundennr = :a->KUNDENNR
and	kdbetriebsende.weekday = :sWeekday;	
/* and	kdbetriebsende.tagestyp = :a->TAGESTYP;	*/

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_offen select %ld",
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

int AakundeSel_touren(kndtourenS* d, char* error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
kndtourenS *a;
long DATUM;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
	DATUM = AllgGetDate();
	EXEC SQL declare Sel_touren scroll cursor with hold for
	SELECT
		TOURPLANTAG.IDFNR,
		TOURPLANTAG.TOURID,
		TOURPLANTAG.REIHENFOLGENR,
		TOURPLANTAG.FAHRTZEIT,
		TOUR.DATUMVERSAND,
		TOUR.ZEITVERSAND,
		TOUR.BAHNHOFVERSAND,
		TOUR.LAGRECHTOUR,
		TOURPLANTAG.KUNDENNR,
		TOURPLANTAG.VERTRIEBSZENTRUMNR,
		TOURPLANTAG.ISTVERBUNDTOUR,
		TOURPLANTAG.KOART,
		TOURPLANTAG.KZAUTOZUORD,
		0,
		TOURPLANTAG.KDAUFTRAGART,
		TOURPLANTAG.RETURNSTOUR,
		TOURPLANTAG.TRANSPEXCLPSYCHO,
		TOURPLANTAG.KIPPZEIT,				// prio1_kippz_ktour
		TOUR.KIPPZEIT,						// prio2_kippz_ftour
		KUNDE.TOURENKIPPZEIT,				// prio3_kippz_kunde
		PARAAUFTRAGBEARB.TOURENKIPPZEIT 	// prio4_kippz_filiale
		FROM tourplantag, tour, kunde, paraauftragbearb
	WHERE kunde.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
		AND	kunde.kundennr = :a->KUNDENNR
		AND	tourplantag.vertriebszentrumnr = kunde.vertriebszentrumnr
		AND	tourplantag.kundennr = kunde.kundennr
		AND	tourplantag.datumkommi = :DATUM
		AND	tour.tourid = tourplantag.tourid
		AND	tour.filialnr = kunde.filialnr
		AND	tourplantag.tourinaktiv != '1'
		AND	tour.tourinaktiv != '1'
		AND	tour.filialnr = kunde.filialnr
		AND	tour.datumkommi = tourplantag.datumkommi
		AND	kunde.vertriebszentrumnr = paraauftragbearb.filialnr;

     EXEC SQL open Sel_touren;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AakundeSel_touren: open Sel_touren %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_touren;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_touren: close Sel_touren %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_touren into
			:a->IDFNR,
			:a->TOURID,
			:a->REIHENFOLGENR,
			:a->FAHRTZEIT,
			:a->DATUMVERSAND,
			:a->ZEITVERSAND,
			:a->BAHNHOFVERSAND,
			:a->LAGRECHTOUR,
			:a->KUNDENNR,
			:a->VERTRIEBSZENTRUMNR,
			:a->ISTVERBUNDTOUR,
			:a->KOART,
			:a->KZAUTOZUORD,
			:a->WEEKDAY,
			:a->KDAUFTRAGART,
			:a->RETURNSTOUR,
			:a->TRANSPEXCLPSYCHO,
			:a->KIPPZEIT,
			:a->PRIO2_KIPPZ_FTOUR,
			:a->PRIO3_KIPPZ_KUNDE,
			:a->PRIO4_KIPPZ_FILIALE;

if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_touren: fetch Sel_touren %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_touren;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }
if (a->KIPPZEIT > 0) ;
else if (a->PRIO2_KIPPZ_FTOUR > 0) a->KIPPZEIT = a->PRIO2_KIPPZ_FTOUR;
else if (a->PRIO3_KIPPZ_KUNDE > 0) a->KIPPZEIT = (short)(a->PRIO3_KIPPZ_KUNDE);
else a->KIPPZEIT = (short)(a->PRIO4_KIPPZ_FILIALE);
return 0;
}

int AakundeSel_nachttouren(kndtourenS *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
kndtourenS *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
    fst = 0;
    EXEC SQL declare Sel_nachttour cursor with hold for
	select
 		tourplanwoche.LAGRECHTOUR
	from tourplantagwoche, tourplanwoche 
	where tourplantagwoche.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
	and tourplantagwoche.kundennr = :a->KUNDENNR
	and	tourplanwoche.tourid = tourplantagwoche.tourid
	and	tourplanwoche.filialnr = tourplantagwoche.vertriebszentrumnr
	and	tourplanwoche.weekday = :a->WEEKDAY
	and	tourplantagwoche.weekday = tourplanwoche.weekday
	and tourplanwoche.tourid > "200000"
	and tourplanwoche.tourid < "240000"
	order by tourplanwoche.tourid;

     EXEC SQL open Sel_nachttour;
     if (sqlca.sqlcode < 0 )
      {
       fst = 1;
   sprintf(error_msg, " AakundeSel_nachttouren: open Sel_nachttour %ld",
         sqlca.sqlcode);
       return -1;
      }
   }

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_nachttour;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_nachttouren: close Sel_nachttour %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

  EXEC SQL fetch Sel_nachttour into :a->LAGRECHTOUR;
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_nachttouren: fetch Sel_nachttour %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_nachttour;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AakundeSel_ausku(struct KNDAUSKU *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDAUSKU   *a;
struct I_KNDAUSKU  i;
long partnernr;
long saveumsatz;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select kunde.partnernr,KNDAUSKU_LISTE into 
	:partnernr,
	:a->EILBOTENZUSCHLAG	indicator :i.EILBOTENZUSCHLAG, 
	:a->MONATSUMSATZ		indicator :i.MONATSUMSATZ, 
	:a->MALUSFREI_PROZ		indicator :i.MALUSFREI_PROZ, 
	:a->VERTRETER_2			indicator :i.VERTRETER_2, 
	:a->IDFNR, 
	:a->MATCHCODE, 
	:a->FILIALNR, 
	:a->ETARTKLASSE1, 
	:a->ETARTKLASSE2,
	:a->ETKDMERKMAL1, 
	:a->ETKDMERKMAL2, 
	:a->NAMEAPO, 
	:a->NAMEINHABER, 
	:a->STRASSE, 
	:a->ORT, 
	:a->POSTLEITZAHL, 
	:a->TELNR, 
	:a->TELNRDAFUE, 
	:a->FAXNR, 
	:a->TELKURZWAHL, 
	:a->IMSBEZIRKNR,
	:a->PERSONALNRVERTR, 
	:a->SKDSCHWERPUNKT1	indicator :i.SKDSCHWERPUNKT1, 
	:a->SKDSCHWERPUNKT2	indicator :i.SKDSCHWERPUNKT2, 
	:a->SKDSCHWERPUNKT3	indicator :i.SKDSCHWERPUNKT3, 
	:a->SKDSCHWERPUNKT4	indicator :i.SKDSCHWERPUNKT4, 
	:a->SKDSCHWERPUNKT5	indicator :i.SKDSCHWERPUNKT5, 
	:a->SKDKDKRITISCH	indicator :i.SKDKDKRITISCH, 
	:a->MENGENATRABASIS	indicator :i.MENGENATRABASIS, 
	:a->MENGENATRA		indicator :i.MENGENATRA, 
	:a->KUNDE_SEIT		indicator :i.KUNDE_SEIT,
	:a->URLAUB_VON		indicator :i.URLAUB_VON, 
	:a->URLAUB_BIS		indicator :i.URLAUB_BIS, 
	:a->VERSAND_KOSTEN	indicator :i.VERSAND_KOSTEN, 
	:a->SKDEILSPERRE	indicator :i.SKDEILSPERRE, 
	:a->SKDVIPKUNDE		indicator :i.SKDVIPKUNDE,
	:a->KUNDENNR,
	:a->VERTRIEBSZENTRUMNR,
	:a->IMS3000,
	:a->LOGISTIKAUFSCHLAG	indicator :i.LOGISTIKAUFSCHLAG
from kunde, outer (kndausku,kundeschalter,kundekondi) 
where kunde.kundennr = :a->KUNDENNR and
	  kunde.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR and
      kndausku.kundennr = kunde.kundennr and
      kndausku.vertriebszentrumnr = kunde.vertriebszentrumnr and
      kundekondi.kundennr = kunde.kundennr and
      kundekondi.vertriebszentrumnr = kunde.vertriebszentrumnr and
      kundeschalter.kundennr = kunde.kundennr and
      kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr ;

if( i.EILBOTENZUSCHLAG	< 0 ) a->EILBOTENZUSCHLAG	= 0;
if( i.LOGISTIKAUFSCHLAG	< 0 ) a->LOGISTIKAUFSCHLAG	= 0;
if( i.MONATSUMSATZ		< 0 ) a->MONATSUMSATZ		= 0;    
if( i.MALUSFREI_PROZ	< 0 ) a->MALUSFREI_PROZ		= 0;  
if( i.VERTRETER_2		< 0 ) a->VERTRETER_2		= 0;     
if( i.SKDSCHWERPUNKT1	< 0 ) strcpy(a->SKDSCHWERPUNKT1	," ");
if( i.SKDSCHWERPUNKT2	< 0 ) strcpy(a->SKDSCHWERPUNKT2	," ");
if( i.SKDSCHWERPUNKT3	< 0 ) strcpy(a->SKDSCHWERPUNKT3	," ");
if( i.SKDSCHWERPUNKT4	< 0 ) strcpy(a->SKDSCHWERPUNKT4	," ");
if( i.SKDSCHWERPUNKT5	< 0 ) strcpy(a->SKDSCHWERPUNKT5	," ");
if( i.SKDKDKRITISCH		< 0 ) strcpy(a->SKDKDKRITISCH	," ");  
if( i.MENGENATRABASIS	< 0 ) a->MENGENATRABASIS	= 0;
if( i.MENGENATRA		< 0 ) a->MENGENATRA			= 0;     
if( i.KUNDE_SEIT		< 0 ) a->KUNDE_SEIT			= 0;     
if( i.URLAUB_VON		< 0 ) a->URLAUB_VON			= 0;     
if( i.URLAUB_BIS		< 0 ) a->URLAUB_BIS			= 0;     
if( i.VERSAND_KOSTEN 	< 0 ) a->VERSAND_KOSTEN 	= 0; 
if( i.SKDEILSPERRE 		< 0 ) strcpy(a->SKDEILSPERRE	," ");   
if( i.SKDVIPKUNDE    	< 0 ) strcpy(a->SKDVIPKUNDE	    ," "); 

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_ausku select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }
if (partnernr != 0)
{
	EXEC SQL select sum(a.monatsumsatz) into :a->MONATSUMSATZ
		from kndausku a,kunde k
		where k.partnernr = :partnernr
		and k.vertriebszentrumnr = a.vertriebszentrumnr
		and k.kundennr = a.idfnr;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakundeSel_ausku select kndausku %ld",	sqlca.sqlcode);
		return -1;
	}
}
return 0;
}


int AakundeSel_kndschalter(struct KNDSCHALTER *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDSCHALTER   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL select KNDSCHALTER_LISTE into KNDSCHALTER_ZEIGER(a) from kundeschalter
where vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and kundennr = :a->KUNDENNR  ;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_kndschalter select %ld/%ld %s",
   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
   return -2;
  }
return 0;
}

int AakundeIns_aufart(struct KNDAUFART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDAUFART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
/* Überprüfen ob Auftragsart bereits vorhanden */
EXEC SQL select KNDAUFART_LISTE 
from auftragartkd
where auftragartkd.kundennr = :a->KUNDENNR 
and auftragartkd.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR 
and auftragartkd.kdauftragart = :a->KDAUFTRAGART ;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeIns_aufart select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode != SQLNOTFOUND )
  {
   strcpy(error_msg, " Auftragsart für diesen Kunden bereits vorhanden");
   return -2;
  }
/* Wenn nicht vorhanden , dann Insert */ 
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeIns_aufart begin work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
EXEC SQL insert into auftragartkd (KNDAUFART_LISTE) values (KNDAUFART_ZEIGER(a));
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeIns_aufart insert %ld",
   sqlca.sqlcode);
   return -1;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeIns_aufart commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
return 0;
}

int AakundeDel_aufart(struct KNDAUFART *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
struct KNDAUFART   *a;
EXEC SQL END DECLARE SECTION;

a = d;
EXEC SQL begin work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeDel_aufart commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
EXEC SQL delete 
from auftragartkd
where auftragartkd.kundennr = :a->KUNDENNR 
and auftragartkd.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR 
and auftragartkd.kdauftragart = :a->KDAUFTRAGART ;
if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeDel_aufart delete %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND )
  {
   strcpy(error_msg, " Diese Auftragsart für diesen Kunden nicht vorhanden");
   return -2;
  }
EXEC SQL commit work;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeDel_aufart commit work %ld %ld",
	sqlca.sqlcode, sqlca.sqlerrd[1]);
	return -1;
}
return 0;
}

int AakundeSel_monums(struct KNDMONUMS *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDMONUMS   *a;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
		fst = 0;
		EXEC SQL declare Sel_monums scroll cursor with hold for
		select KNDMONUMS_LISTE
		from kundemonums
		where	kundemonums.kundennr = :a->KUNDENNR
		and		kundemonums.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
		order by jahr desc,monat desc  ;
	
		EXEC SQL open Sel_monums;
		if (sqlca.sqlcode < 0 )
		{
			fst = 1;
			sprintf(error_msg, " AakundeSel_monums: open Sel_monums %ld",
				sqlca.sqlcode);
			return -1;
		}
	}

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_monums;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_monums: close Sel_monums %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_monums into KNDMONUMS_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_monums: fetch Sel_monums %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_monums;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }

return 0;
}

int AakundeSel_telnr(struct KNDINF *d, char *error_msg)
{
static int first = 0;
EXEC SQL BEGIN DECLARE SECTION;
char str[2048];
struct KNDINF   *a;
EXEC SQL END DECLARE SECTION;

a = d;

if(first == 0)
{
	first = 1;
	strcpy( str, "select " );
	strcat( str, KNDINF_PLISTE );
	strcat( str, " from kunde,kundeschalter,customerphoneno" );
	strcat( str, " where kunde.vertriebszentrumnr = ?" );
	strcat( str, " and customerphoneno.telnr = ?" );
	strcat( str, " and kunde.vertriebszentrumnr = kundeschalter.vertriebszentrumnr" );
	strcat( str, " and kunde.kundennr = kundeschalter.kundennr" );
	strcat( str, " and kunde.vertriebszentrumnr = customerphoneno.vertriebszentrumnr" );
	strcat( str, " and kunde.kundennr = customerphoneno.kundennr" );
	strcat( str, " and kundeschalter.skdkundeaegesperrt = '0'" );
	strcat( str, " order by kunde.kundennr" );

	exec sql prepare Sel_telnr from :str;
	exec sql declare CSel_telnr cursor for Sel_telnr;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakundeSel_telnr declare %ld/%ld",
		sqlca.sqlcode,sqlca.sqlerrd[1]);
		return -1;
	}
}

exec sql open CSel_telnr using :a->VERTRIEBSZENTRUMNR,:a->TELNR;
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeSel_telnr open %ld/%ld",
	sqlca.sqlcode,sqlca.sqlerrd[1]);
	return -1;
}
exec sql fetch CSel_telnr into KNDINF_ZEIGER(a);
if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeSel_telnr fetch %ld/%ld",
	sqlca.sqlcode,sqlca.sqlerrd[1]);
	return -1;
}
if (sqlca.sqlcode == SQLNOTFOUND)
{
    return 1;
}
return 0;
}

int AakundeSel_name(struct KNDSEL *d, char *error_msg)
{
static int fst = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDSEL   *a;
char SUCHE[L_KNDSEL_NAMEAPO+2];
int fili_von;
int fili_bis;
EXEC SQL END DECLARE SECTION;

a = d;
if (fst) /* beim ersten mal oder bei neu deklarieren */
   {
   	fst = 0;
    
	if (a->VERTRIEBSZENTRUMNR != 0)
	{
		fili_von = a->VERTRIEBSZENTRUMNR;
		fili_bis = a->VERTRIEBSZENTRUMNR;
	}
	else
	{
		fili_von = 0;
		fili_bis = 99;
	}

	AllgMakeToLike(a->NAMEAPO,L_KNDSEL_NAMEAPO);
	sprintf(SUCHE,"%%%s",a->NAMEAPO);
    AllgMakeToLike(a->ORT,L_KNDSEL_ORT);
    
    EXEC SQL declare Sel_name scroll cursor with hold for
		select KNDSEL_LISTE
		from kunde,kundeschalter
		where 	(kunde.nameapo 	like :SUCHE or
				kunde.nameinhaber	like :SUCHE) and
				kunde.ort			like :a->ORT and
				kunde.vertriebszentrumnr	<=	:fili_bis and 
				kunde.vertriebszentrumnr	>=	:fili_von and
				kundeschalter.kundennr = kunde.kundennr and
				kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr and
				kundeschalter.skdkundeaegesperrt <= :a->SKDKUNDEAEGESPERRT and
				kunde.vertriebszentrumnr in (
                    select RegionArten.RegionTeilNr from RegionArten
		             where RegionArten.RegionNr= :a->REGIONNR and 
                           RegionArten.RegionenTyp=1)
		order by nameapo, ort, originalfilialnr;

    EXEC SQL open Sel_name;
    if (sqlca.sqlcode < 0 )
      {
       	fst = 1;
   		sprintf(error_msg, " AakundeSel_name: open Sel_mc %ld",
        	sqlca.sqlcode);
        return -1;
      }
   } /* Ende OPEN */

if(a->FETCH_REL == 0)   /* close cursor */
  {
     fst = 1;
     EXEC SQL close Sel_name;
     if (sqlca.sqlcode < 0 )
      {
       sprintf(error_msg, " AakundeSel_name: close Sel_mc %ld",
       sqlca.sqlcode);
       return -1;
       }
    return 1;
  }

EXEC SQL fetch relative :a->FETCH_REL Sel_name into KNDSEL_ZEIGER(a);
if (sqlca.sqlcode < 0 )
  {
   fst = 1;
   sprintf(error_msg, " AakundeSel_name: fetch Sel_mc %ld",
   sqlca.sqlcode);
   EXEC SQL close Sel_name;
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   return 1;
  }
return 0; 
}

int AakundeSel_knd_info_hipath(struct KNDINF *d, char *error_msg)
{
static int first = 1;

EXEC SQL BEGIN DECLARE SECTION;
struct KNDINF   *a;
char tagart[3];
struct TM zeit;
static long Zeitbeginn,Zeitende;
static short VzNr;
EXEC SQL END DECLARE SECTION;

a = d;

AafilGetdatetime(&zeit,error_msg);
switch(zeit.WTAG)
{
	case 0 : strcpy(tagart, "SO"); break;
	case 1 : strcpy(tagart, "MO"); break;
	case 2 : strcpy(tagart, "DI"); break;
	case 3 : strcpy(tagart, "MI"); break;
	case 4 : strcpy(tagart, "DO"); break;
	case 5 : strcpy(tagart, "FR"); break;
	case 6 : strcpy(tagart, "SA"); break;
}
EXEC SQL select zeitschluessel
	into :VzNr
	from zeitarten
	where vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
	and zeitart = 4
	and zeitbegin <= :zeit.ZEIT
	and zeitende >= :zeit.ZEIT
	and weekday = :zeit.WTAG;
/*	and tagestyp = :tagart; */

if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeSel_knd_info_hipath select zeitarten %ld",
	sqlca.sqlcode);
	return -1;
}
if (sqlca.sqlcode != SQLNOTFOUND)
{
	a->VERTRIEBSZENTRUMNR = VzNr;
}

/*	zwecks Notfallunterstuetzung routing-Tabelle abfragen */
zeit.ZEIT = zeit.ZEIT/100;
EXEC SQL select destbranchno
	into :VzNr
	from customerrouting
	where branchno = :a->VERTRIEBSZENTRUMNR
	and customerno = :a->KUNDENNR
	and timefrom <= :zeit.ZEIT
	and timeto >= :zeit.ZEIT
	and weekday = :zeit.WTAG;

if (sqlca.sqlcode < 0 )
{
	sprintf(error_msg, " AakundeSel_knd_info_hipath select customerrouting %ld",
	sqlca.sqlcode);
	return -1;
}
if (sqlca.sqlcode != SQLNOTFOUND)
{
	a->VERTRIEBSZENTRUMNR = VzNr;
}

EXEC SQL select KNDINF_LISTE into KNDINF_ZEIGER(a) from kunde,kundeschalter
where kunde.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
and kunde.kundennr = :a->KUNDENNR
and kundeschalter.vertriebszentrumnr = kunde.vertriebszentrumnr
and kundeschalter.kundennr = kunde.kundennr;

if (sqlca.sqlcode < 0 )
  {
   sprintf(error_msg, " AakundeSel_knd_info_hipath select %ld",
   sqlca.sqlcode);
   return -1;
  }
if (sqlca.sqlcode == SQLNOTFOUND)
  {
   strcpy(error_msg, TXT_KEIN_KUNDE_IDF);
   return -2;
  }
return 0;
}
