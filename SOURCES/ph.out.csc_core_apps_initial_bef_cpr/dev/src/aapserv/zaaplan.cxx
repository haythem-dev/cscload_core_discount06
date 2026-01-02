/*** INCLUDE **************************************************************************/

#include <bufkon.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include "partikel.h"
#include "aarufpl.h"
#include <allg.h>
#include "aasrv.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/*** DEFINE ***************************************************************************/

#define NOT_FOUND        1 
#define FILE_NOT_FOUND   1
#define ERROR           -1
#define WARNING         -2
#define YES              1
#define NO               0
#define F_SETGRASP      -9
#define F_UNSET         -8
#define SCODE			 sqlca.sqlcode
#define SISAM            sqlca.sqlerrd[1] 
#define SUPDA			 sqlca.sqlerrd[2]
#define SERRM			 sqlca.sqlerrm


/*** MACROS ***************************************************************************/

#define SQLERROR(x,y) if ( SCODE < 0 ) { first = 1;\
                      sprintf( error_msg, "%s: %s %ld/%ld %s",	x, y, SCODE, SISAM, SERRM );\
                      return -1; }
#define SERROR(x,y)   if ( SCODE < 0 ) { \
                      sprintf( error_msg, "%s: %s %ld/%ld %s",	x, y, SCODE, SISAM, SERRM );\
                      return -1; }
#define SRERROR(x,y)  if ( SCODE < 0 || SUPDA == 0 ) { \
                      sprintf( error_msg, "%s: %s %ld/%ld %s",	x, y, SCODE, SISAM, SERRM );\
                      Rollback( error_msg ); \
                      return -1; }
#define NOTFOUND      sqlca.sqlcode == SQLNOTFOUND
#define ISFOUND       NOTFOUND ? NOT_FOUND : 0

/*** GLOBALE *************************************************************************/

exec sql begin declare section;
extern char haus_nr[4 + 1];
extern long UID;
exec sql end declare section;

/*** DECLARATION *********************************************************************/

static char *WeekDay( long );
static int  Begin( char * );
static int  Commit( char * );
static int  Rollback( char * );
long GetTimeForCall( rufArt iFunction, int long lRealTime, short vertriebszentrum );

/*** AAPLANSEL-MPLAN-IDF **************************************************************/

int AaplanSel_mplan_idf( struct RUFPMASTER *a, char *error_msg )
{
	exec sql begin declare section;
	struct RUFPMASTER *d;
	long datum;
	char tourfix[2];
	exec sql end declare section;

	long sfetchrel;
	static short tagnr;
	static int first = 1;
	char *fun = "AaplanSel_mplan_idf";
  
	d = a;
   
	if (first) /* beim ersten mal oder bei neu deklarieren */
	{
		struct tm t;
     
		first = 0;
		AllgGetTM(&t);
		tagnr = (short)t.tm_wday; /* 0 = Sonntag   */
		datum = AllgGetDate();
	 
/*		exec sql declare Sel_mplan_idf scroll cursor with hold for
			select
				URRUFZEIT,
				RUFPROTOKOLL,
				ANRUFTYP,
				TOURID,
				STOURDEFINITIV
			from kundeanrufplantag
			where	vertriebszentrumnr	= :d->FILIALNR
			and		kundennr			= :d->IDFNR 
			and		datum				= :datum 
			order by urrufzeit;
*/
		exec sql declare Sel_mplan_idf scroll cursor with hold for
			select
				RUFZEIT,
				'2',
				'0',
				' ',
				'0'
			from tagplan
			where	filialnr	= :d->FILIALNR
			and		idfnr		= :d->IDFNR
			and		datum		= :datum
			order by rufzeit;

		exec sql open Sel_mplan_idf;
		SQLERROR( fun, "open Sel_mplan_idf" )    
	}

	if ( d->FETCH_REL == 0 )   /* close cursor */
	{
		first = 1;
		exec sql close Sel_mplan_idf;
		SQLERROR( fun, "close Sel_mplan_idf" )    
		return 1;
	}

	sfetchrel = d->FETCH_REL;
	memset( (char*)d, '0', sizeof(struct RUFPMASTER) );
	d->FETCH_REL = sfetchrel;
	exec sql fetch relative :d->FETCH_REL Sel_mplan_idf into
		:d->RUFZEIT,
		:d->PROTOKOLLART,
		:d->VERARBEITUNGART,
		:d->TOURID,
		:tourfix;
	SQLERROR( fun, "fetch Sel_mplan_idfy" )    
	if ( sqlca.sqlcode == SQLNOTFOUND )
		return 1;

	if(tourfix[0] != '1')
		sprintf(d->TOURID," ");

	switch( tagnr )
	{
		case 0:	strcpy(d->AKTIVSONNTAG, "1"); break;
		case 1:	strcpy(d->AKTIVMONTAG, "1"); break;
		case 2:	strcpy(d->AKTIVDIENSTAG, "1"); break;
		case 3:	strcpy(d->AKTIVMITTWOCH, "1"); break;
		case 4:	strcpy(d->AKTIVDONNERSTAG, "1"); break;
		case 5:	strcpy(d->AKTIVFREITAG, "1"); break;
		case 6:	strcpy(d->AKTIVSAMSTAG, "1"); break;
	}

	*d->PROTOKOLLART = *d->PROTOKOLLART + 1;
	return 0;
}

/*** AAPLANSEL-TAG-PLAN ***************************************************************/

int AaplanSel_tag_plan( struct RUFPTAG *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAG *d;
  int    ZUGRIFF;
  char   str[2048];
  int    zugriffv;
  int    zugriffb;
  long 	 zeitBisPhon;
  long 	 zeitBisPara;
  long 	 zeitBisSera;
  long 	 zeitBisMSera;
  short	VzVon;
  short VzBis;
  exec sql end declare section;
  
  static int first = 1;
  long zeitBis;
  short Vz;
  char *fun = "AaplanSel_tag_plan";

  d = a;

  if ( d->PRIORITAET == 0 )
     { 
     zugriffv = NO;
     zugriffb = YES;	 /* Saetze mit sperre lesen (dirty read) */ 
     }
     else
     {
     zugriffv = NO;
     zugriffb = NO;	 /* Saetze mit sperre lesen (dirty read) */ 
     }

  if ( first ) /* beim ersten mal oder bei neu deklarieren */
     {
     first = 0;
    
	 zeitBis = d->UID == 0 ? 2400 : ( AllgGetTime() / 100 );
	 Vz = d->REGIONNR;
	 if(d->FILIALNR == 0)
	 {
		 VzVon = 0;
		 VzBis = 99;
	 }
	 else
	 {
		 VzVon = d->FILIALNR;
		 VzBis = d->FILIALNR;
	 }

	 zeitBisPhon = GetTimeForCall( F_PHON, zeitBis, Vz );
     zeitBisPara = GetTimeForCall( F_PARA, zeitBis, Vz );
     zeitBisSera = GetTimeForCall( F_SERA, zeitBis, Vz );
     zeitBisMSera = GetTimeForCall( F_MSERA, zeitBis, Vz );

	 strcpy( str, "select zugriff, " );
	 strcat( str, RUFPTAG_PLISTE );
	 strcat( str, "from tagplan, kunde, tagplanereignis " );
	 strcat( str, "where tagplan.filialnr >= ? " );
	 strcat( str, "and tagplan.filialnr <= ? " );
	 strcat( str, "and tagplan.idfnr = tagplanereignis.idfnr " );
	 strcat( str, "and tagplan.filialnr = tagplanereignis.filialnr " );
	 strcat( str, "and tagplan.rufzeit = tagplanereignis.rufzeit " );
     strcat( str, "and tagplan.datum = tagplanereignis.datum " );
     strcat( str, "and tagplan.lfdaktion = tagplanereignis.lfdaktion " );
     strcat( str, "and tagplan.zugriff >= ? " );
     strcat( str, "and tagplan.zugriff <= ? " );
     strcat( str, "and kunde.idfnr = tagplan.idfnr " );
     strcat( str, "and kunde.filialnr = tagplan.filialnr " );
	 strcat( str, "and tagplan.datum = ? " );
     strcat( str, "and tagplanereignis.rufzeitgeaendert >= ? " );
     strcat( str, "and ( ( tagplanereignis.rufzeitgeaendert <= ? " );    
     strcat( str, "and tagplan.anrufart = \"PH\" ) or " );           
     strcat( str, "( tagplanereignis.rufzeitgeaendert <= ? " );    
     strcat( str, "and tagplan.anrufart = \"DP\" ) or " );              
     strcat( str, "( tagplanereignis.rufzeitgeaendert <= ? " );    
     strcat( str, "and tagplan.anrufart = \"DS\" ) or " );              
     strcat( str, "( tagplanereignis.rufzeitgeaendert <= ? " );    
     strcat( str, "and tagplan.anrufart = \"DA\" ) ) " );
  	 
	 if ( d->IDFNR >= 0 )												  
        strcat( str, "and tagplan.idfnr = ? " );
     else
	    strcat( str, "and tagplan.idfnr > ? " );
     
	 strcat( str, "and anrufart != ? " );		  /* ergänzt am 27.01.97 */
	 if ( d->POOLID != 0 )												  
        strcat( str, "and tagplan.poolid = ? " );
   	 else
	    strcat( str, "and tagplan.poolid >= ? " );
     
     if ( d->STATUS == 1 )
		strcat( str, "and tagplanereignis.status=1 " ); 
	 else if ( d->STATUS == 2 )
		strcat( str, "and tagplanereignis.status=2 " ); 
	 else if ( d->STATUS == 3 )
 		strcat( str, "and tagplanereignis.status=3 " ); 
	 else if ( d->STATUS == 4 )
		strcat( str, "and tagplanereignis.status=4 " ); 
	 else if ( d->STATUS == 5 )
		strcat( str, "and tagplanereignis.status=5 " ); 
	 else if ( d->STATUS == 6 )
		strcat( str, "and (tagplanereignis.status=6 or tagplanereignis.status=7) " );
	 else if ( d->STATUS == 7 )	
		strcat( str, "and (tagplanereignis.status=6 or tagplanereignis.status=7) " );
     else if ( d->STATUS == 99 )	
	    {
		strcat( str, "and (tagplanereignis.status=6 or tagplanereignis.status=7) " );
	 	zugriffv = YES;
		zugriffb = YES;
	    }
	strcat( str, "and tagplan.filialnr in ( " );
	strcat( str, "select RegionArten.RegionTeilNr from RegionArten " );
	strcat( str, "where  RegionArten.RegionNr = ? and " );
	strcat( str, "RegionArten.RegionenTyp = 1) " );

	 strcat( str, "order by tagplanereignis.rufzeitgeaendert, " );
	 strcat( str, "tagplanereignis.rufzeit, tagplan.prioritaet " );
	 
	 exec sql prepare selRufptag from :str;
	 SQLERROR( fun, "prepare selRufptag" )
     
	 exec sql declare Sel_tag_plan scroll cursor for selRufptag;
/*
	 printf("VzVon:#%d#\n",VzVon);
	 printf("VzBis:#%d#\n",VzBis);
	 printf("zugriffv:#%d#\n",zugriffv);
	 printf("zugriffb:#%d#\n",zugriffb);
	 printf("DATUM:#%d#\n",d->DATUM);
	 printf("RUFZEIT:#%d#\n",d->RUFZEIT);
	 printf("zeitBisPhon:#%d#\n",zeitBisPhon);
	 printf("zeitBisPara:#%d#\n",zeitBisPara);
	 printf("zeitBisSera:#%d#\n",zeitBisSera);
	 printf("zeitBisMSera:#%d#\n",zeitBisMSera);
	 printf("IDFNR:#%d#\n",d->IDFNR);
	 printf("ANRUFART:#%2.2s#\n",d->ANRUFART);
	 printf("POOLID:#%d#\n",d->POOLID);
	 printf("REGIONNR:#%d#\n",d->REGIONNR);
	fflush(stdout);
*/
     exec sql open Sel_tag_plan using	:VzVon,
										:VzBis,
										:zugriffv,
										:zugriffb,
										:d->DATUM, 
										:d->RUFZEIT,
										:zeitBisPhon,
										:zeitBisPara,
										:zeitBisSera,
										:zeitBisMSera,
										:d->IDFNR,
										:d->ANRUFART,
										:d->POOLID,
										:d->REGIONNR;
   	 SQLERROR( fun, "open Sel_tag_plan" )
     }

  if ( d->FETCH_REL == 0 )                              /* close cursor */
     {
     first = 1;
     exec sql close Sel_tag_plan;
     SQLERROR( fun, "close Sel_tag_plan" )
     return 1;
     }

  exec sql fetch relative :d->FETCH_REL Sel_tag_plan into :ZUGRIFF, RUFPTAG_ZEIGER(d);
  SQLERROR( fun, "fetch Sel_tag_plan" )
  if ( NOTFOUND )
     return NOT_FOUND;
  if ( ZUGRIFF ) d->STATUS = PLAN_GESPERRT;

return 0;
}

/*** AAPLANUNI-TAG-PLAN ***************************************************************/

int AaplanUni_tag_plan( struct RUFPTAG *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAG *d;
  exec sql end declare section;
  char *fun = "AaplanUni_tag_plan";

  d = a;
  exec sql select idfnr from tagplan
				where tagplan.filialnr = :d->FILIALNR
				and idfnr    = :d->IDFNR
				and datum    = :d->DATUM
				and rufzeit  = :d->RUFZEIT
				and zugriff  = 0;
    SERROR( fun, "fetch unique tagplan" )
  
  if ( NOTFOUND )
     return NOT_FOUND;
   
  return 0;
}

/*** AAPLANINS-TAG-PLAN ***************************************************************/

int AaplanIns_tag_plan( struct RUFPTAG *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAG *d;
  long time;
  int iStatus; 
  long lLfdaktion;
  exec sql end declare section;
int i;

  char *fun = "AaplanIns_tag_plan";

  d = a;
  
  /*d->LFDAKTION = 1;*/ /* wird clientseitig gerechnet */
  time = AllgGetTime();

  strcpy( d->WOCHENTAG, WeekDay( AllgGetWeekDay( d->DATUM, error_msg ) ) );

  exec sql select tagplan.lfdaktion, tagplanereignis.status  
             into :lLfdaktion, :iStatus
             from tagplan, tagplanereignis
	        where tagplan.filialnr = :d->FILIALNR
	          and tagplan.idfnr    = :d->IDFNR
		      and tagplan.datum    = :d->DATUM
              and tagplan.rufzeit  = :d->RUFZEIT
              and tagplan.idfnr = tagplanereignis.idfnr
              and tagplan.filialnr = tagplanereignis.filialnr
	          and tagplan.rufzeit = tagplanereignis.rufzeit 
              and tagplan.datum = tagplanereignis.datum 
              and tagplan.lfdaktion = tagplanereignis.lfdaktion;
  SERROR( fun, "select tagplan,tagplanereignis" )

i = sqlca.sqlcode;
  
  if ( SCODE == 0 && iStatus != 5 ) /* geloescht */
     {  
     return 1; /* satz vorhanden, in arbeit ... */ 
     }

  Begin( error_msg );
  if ( i == 0 && iStatus == 5 )
  {

     d->LFDAKTION = lLfdaktion + 1;    
	 exec sql update tagplan set lfdaktion = :d->LFDAKTION
                   		   where filialnr  = :d->FILIALNR
						     and idfnr     = :d->IDFNR
				             and datum     = :d->DATUM
				             and rufzeit   = :d->RUFZEIT;
     SRERROR( fun, "update tagplan" )
  }
  else 
  {
     exec sql insert into tagplan ( filialnr,
                                    idfnr,
	  					            datum,
	  					            rufzeit,
	  					            lfdaktion,
	  					            prioritaet,
						            wochentag,
						            poolid,
						            anrufart,
						            manuell,
						            stagrueckruf,
						            telrueckrufnr )
              	           values ( :d->FILIALNR,
				                    :d->IDFNR,
				                    :d->DATUM,
				                    :d->RUFZEIT,
				                    :d->LFDAKTION,
				                    :d->PRIORITAET,
				                    :d->WOCHENTAG,
				                    :d->POOLID,
				                    :d->ANRUFART,
				                    :d->MANUELL,
				                    :d->STAGRUECKRUF,
    			                    :d->TELRUECKRUFNR );
     SRERROR( fun, "insert" )
  } 
  
  exec sql insert into tagplanereignis ( datum,
                                         rufzeit,
										 idfnr,
										 lfdaktion,
										 status,
										 loeschgrund,
										 rufzeitgeaendert,
										 zeit,
										 uid,
										 bemerkung,
										 filialnr )
                                values ( :d->DATUM,
				                         :d->RUFZEIT,
								         :d->IDFNR,
				                         :d->LFDAKTION,
				                         :d->STATUS,
										 :d->LOESCHGRUND,
				                         :d->RUFZEITGEAENDERT,
										 :time,
										 :d->UID,
										 :d->BEMERKUNG,
										 :d->FILIALNR );
  SRERROR( fun, "insert tagplanereignis" )
 
  Commit( error_msg );

  return 0;
}

/*** AAPLANUPD-TAG-PLAN ***************************************************************/

int AaplanUpd_tag_plan( struct RUFPTAG *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAG *d;
  long time;
  exec sql end declare section;
  char *fun = "AaplanUpd_tag_plan";
  
  d = a;
  
  /* d->LFDAKTION++; */ /* wird clientseitig gerechnet */
  time = AllgGetTime();

  Begin( error_msg );
  if ( d->FETCH_REL == F_SETGRASP )                     /* Zugriffsperre   */
     {
     exec sql update tagplan set zugriff  = 1
                   		   where filialnr = :d->FILIALNR
						     and idfnr    = :d->IDFNR
				             and datum    = :d->DATUM
				             and rufzeit  = :d->RUFZEIT;
     SRERROR( fun, "update tagplan(zugriff)" )
	 Commit( error_msg );
	 return 0;
	 }
  else if ( d->FETCH_REL == F_UNSET )                    /* Zugriffsperre   */
     {
     exec sql update tagplan set zugriff  = 0
                   		   where filialnr = :d->FILIALNR
						     and idfnr    = :d->IDFNR
				             and datum    = :d->DATUM
				             and rufzeit  = :d->RUFZEIT;
     SRERROR( fun, "update tagplan(zugriff)" )
	 Commit( error_msg );
	 return 0;
	 }
  else
	 {
     exec sql update tagplan set lfdaktion     = :d->LFDAKTION,
	                             prioritaet    = :d->PRIORITAET,
		        				 anrufart      = :d->ANRUFART,
							     manuell       = :d->MANUELL,
							     stagrueckruf  = :d->STAGRUECKRUF, 
							     telrueckrufnr = :d->TELRUECKRUFNR,
							     poolid			= :d->POOLID,
								 zugriff       = :d->FETCH_REL
              			   where filialnr = :d->FILIALNR
						     and idfnr    = :d->IDFNR
				             and datum    = :d->DATUM
				             and rufzeit  = :d->RUFZEIT;
     SRERROR( fun, "update tagplan" )
							  
     exec sql insert into tagplanereignis ( datum,
	   									    rufzeit,
										    idfnr,
										    lfdaktion,
										    status,
										    loeschgrund,
										    rufzeitgeaendert,
										    zeit,
										    uid,
										    bemerkung,
											filialnr )
                                   values ( :d->DATUM,
				                            :d->RUFZEIT,
										    :d->IDFNR,
				                            :d->LFDAKTION,
				                            :d->STATUS,
										    :d->LOESCHGRUND,
				                            :d->RUFZEITGEAENDERT,
										    :time,
										    :d->UID,
										    :d->BEMERKUNG,
											:d->FILIALNR );
     SRERROR( fun, "insert tagplanereignis" )
     }
  
  Commit( error_msg );

  return 0;
}


/*** AAPLANSEL-TAG-PLAN-INF ***********************************************************/

int AaplanSel_tag_plan_inf( struct RUFPTAGINF *a, char *error_msg )
  {
  exec sql begin declare section;
  struct RUFPTAGINF *d;
  char str[1024];
  exec sql end declare section;

  static int first = 1;
  char *fun = "AaplanSel_tag_plan_inf";

  d = a;
  if ( first ) /* beim ersten mal oder bei neu deklarieren */
     {
     first = 0;
    
	 strcpy( str, "select " );
	 strcat( str, RUFPTAGINF_PLISTE );
	 strcat( str, "from tagplanereignis, outer passwd " );
	 strcat( str, "where tagplanereignis.datum = ? " );
     strcat( str, "and tagplanereignis.rufzeit = ? " );
     strcat( str, "and tagplanereignis.idfnr = ? " );
	 strcat( str, "and tagplanereignis.filialnr = ? " );
	 strcat( str, "and passwd.filialnr = tagplanereignis.filialnr " );
	 strcat( str, "and passwd.uid = tagplanereignis.uid " );
     strcat( str, "order by zeit " );

	 exec sql prepare selRufptagInf from :str;
	 SQLERROR( fun, "prepare selRufptagInf" )
     
	 exec sql declare Sel_tag_plan_inf cursor for selRufptagInf;
     exec sql open Sel_tag_plan_inf using	:d->DATUM,
											:d->RUFZEIT,
											:d->IDFNR,
											:d->FILIALNR;
   	 SQLERROR( fun, "open Sel_tag_plan_inf" )
	     }

  if ( d->FETCH_REL == 0 )                              /* close cursor */
     {
     first = 1;
     exec sql close Sel_tag_plan_inf;
     SQLERROR( fun, "close Sel_tag_plan_inf" )
     return 1;
     }

  exec sql fetch Sel_tag_plan_inf into RUFPTAGINF_ZEIGER(d);
  SQLERROR( fun, "fetch Sel_tag_plan_inf" )
  if ( NOTFOUND )
     return NOT_FOUND;
   
return 0;
}

/*** AAPLAN-SEL-COUNT ****************************************************************/

int AaplanSel_count( struct RUFPTAGSUM *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAGSUM *d;
  exec sql end declare section;

  char *fun = "AaplanSel_count";

  d = a;
  exec sql select count(*) into :d->SUMMEOFFEN from tagplanereignis
	  where datum   = :d->DATUM
		and filialnr = :d->FILIALNR
		and rufzeit > 0
		and idfnr   > 0
		and status  = 7;					                   /* unbearbeitet anrufe */
  SERROR( fun, "select count offen" )
  
  exec sql select count(*) into :d->SUMMEERLEDIGT from tagplanereignis
	  where datum   = :d->DATUM
		and filialnr = :d->FILIALNR
		and rufzeit > 0
		and idfnr   > 0
		and ( status  = 3 or status = 4 );                     /* erledigte anrufe    */
  SERROR( fun, "select count erledigt" )
  
  exec sql select count(*) into :d->SUMMEGELOESCHT from tagplanereignis
	  where datum   = :d->DATUM
		and filialnr = :d->FILIALNR
		and rufzeit > 0
		and idfnr   > 0
		and status  = 5;					                   /* unbearbeitet anrufe */
  SERROR( fun, "select count geloescht" )
   
  d->SUMMEOFFEN = d->SUMMEOFFEN - ( d->SUMMEERLEDIGT + d->SUMMEGELOESCHT );    
	  
  return 0;
}

/*** AAPLAN-SEL-TOUR ******************************************************************/

int AaplanSel_tour( struct RUFPTAGTOUR *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAGTOUR *d;
  exec sql end declare section;

  static int first = 1;
  char *fun = "AaplanSel_tour";

  d = a;
  if ( first )                            /* beim ersten mal oder bei neu deklarieren */
     {
     first = 0;
     exec sql declare Sel_tour scroll cursor with hold for
               select RUFPTAGTOUR_LISTE
                 from tourplantag
				 where idfnr     = :d->IDFNR
				 and vertriebszentrumnr  = :d->VERTRIEBSZENTRUMNR
				 and datumkommi  = :d->DATUMKOMMI
				 and tourid[1,4] > :d->TOURID;

     exec sql open Sel_tour;
	 SQLERROR( fun, "open Sel_tour" )
     }

  if ( d->FETCH_REL == 0 )                                         /* close cursor */
     {
     first = 1;
     exec sql close Sel_tour;
   	 SQLERROR( fun, "close Sel_tour" )
     
	 return 1;
     }

  exec sql fetch relative :d->FETCH_REL Sel_tour into RUFPTAGTOUR_ZEIGER( d );
  SQLERROR( fun, "fetch Sel_tour" )

  if ( NOTFOUND )
     return NOT_FOUND;

  return 0;
}

/*** AAPLAN-VOR-SEL-UNI ***************************************************************/

int AaplanVor_sel_uni( struct RUFPTAGVOR *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAGVOR   *d;
  exec sql end declare section;
  char *fun = "AaplanVor_sel_uni";

  d = a;

  if ( d->NUMMERTYP == F_PHON )
  {
	 exec sql select AnrufParameter.RufAbweichungPH	into :d->NUMMERWERT
				from AnrufParameter
			   where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
  }
  else if ( d->NUMMERTYP == F_PARA )
  {
	 exec sql select AnrufParameter.RufAbweichungDP	into :d->NUMMERWERT
				from AnrufParameter
			   where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
  }
  else if ( d->NUMMERTYP == F_SERA )
  {
	 exec sql select AnrufParameter.RufAbweichungDS	into :d->NUMMERWERT
				from AnrufParameter
			   where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
  }
  else if ( d->NUMMERTYP == F_MSERA )
  {
	 exec sql select AnrufParameter.RufAbweichungDP	into :d->NUMMERWERT
				from AnrufParameter
			   where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
  }
  SERROR( fun, "AaplanVor_sel_uni select" )		   
	  
  return ISFOUND;
}

/*** AAPLAN-VOR-SEL-UPD ***************************************************************/

int AaplanVor_sel_upd( struct RUFPTAGVOR *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAGVOR *d;
  exec sql end declare section;
  char *fun = "AaplanVor_sel_upd";

  d = a;

  if ( Begin(error_msg) )
  {
     if ( d->NUMMERTYP == F_PHON )
	 {
	    exec sql update AnrufParameter set AnrufParameter.RufAbweichungPH = :d->NUMMERWERT
			      where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
	 }
     else if ( d->NUMMERTYP == F_PARA )
	 {
	    exec sql update AnrufParameter set AnrufParameter.RufAbweichungDP = :d->NUMMERWERT
			      where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
	 }
     else if ( d->NUMMERTYP == F_SERA )
	 {
	    exec sql update AnrufParameter set AnrufParameter.RufAbweichungDS = :d->NUMMERWERT
			      where AnrufParameter.VertriebsZentrumNr = :d->NUMMERMINDEST;
	 }
     SERROR( fun, "AaplanVor_sel_upd update" )
     Commit( error_msg );
  }

  return 0;
}

/*** AAPLAN-VOR-SEL-UPD ***************************************************************/

int AaplanVor_sel_ins( struct RUFPTAGVOR *a, char *error_msg )
{
  exec sql begin declare section;
  struct RUFPTAGVOR *d;
  exec sql end declare section;
  char *fun = "AaplanVor_sel_ins";

  d = a;

  if ( Begin(error_msg) )
  {
     if ( d->NUMMERTYP == F_PHON )
	 {
	    exec sql insert into AnrufParameter(AnrufParameter.VertriebsZentrumNr,
											AnrufParameter.RufAbweichungPH)
									 values(:d->NUMMERMINDEST,
											:d->NUMMERWERT );
	 }
     else if ( d->NUMMERTYP == F_PARA )
	 {
	    exec sql insert into AnrufParameter(AnrufParameter.VertriebsZentrumNr,
											AnrufParameter.RufAbweichungDP)
									 values(:d->NUMMERMINDEST,
											:d->NUMMERWERT );
	 }
     else if ( d->NUMMERTYP == F_SERA )
	 {
	    exec sql insert into AnrufParameter(AnrufParameter.VertriebsZentrumNr,
											AnrufParameter.RufAbweichungDS)
									 values(:d->NUMMERMINDEST,
											:d->NUMMERWERT );
	 }
     Commit( error_msg );
  }
  SERROR( fun, "AaplanVor_sel_ins insert" )
  
  return 0;
}

/*** WEEK-DAY *************************************************************************/

static char *WeekDay( long day )
{
	char *weekday = "   ";
	
	switch( day )
	  {
	  case ALLG_SONNTAG    : weekday = "SO"; break;
      case ALLG_MONTAG     : weekday = "MO"; break;
	  case ALLG_DIENSTAG   : weekday = "DI"; break;
      case ALLG_MITTWOCH   : weekday = "MI"; break;
      case ALLG_DONNERSTAG : weekday = "DO"; break;
      case ALLG_FREITAG    : weekday = "FR"; break;
      case ALLG_SONNABEND  : weekday = "SA"; break;
	  default              : weekday = "??";
	  }

	return( weekday );
}

/*** BEGIN ****************************************************************************/

static int Begin( char *error_msg )
{
  char *fun = "Begin";

  EXEC SQL begin work;

  SERROR( fun, "begin" )
  
  return YES;
}

/*** COMMIT ***************************************************************************/

static int Commit( char *error_msg )
{
  char *fun = "Commit";

  exec sql commit work;
  SERROR( fun, "commit" )
  
  return YES;
}

/*** ROLLBACK *************************************************************************/

static int Rollback( char *error_msg )
{
  char *fun = "Rollback";

  exec sql Rollback work;
  SERROR( fun, "rollback" )
  
  return YES;
}

/*** GET-TIME-FOR-CALL ****************************************************************/

long GetTimeForCall( rufArt iFunction, long lRealTime, short vertriebszentrum )
{
  int  iSumMin;
  int  iHour;
  int  iMin;
  char szpTime[5];
  char error_msg[81];
  struct RUFPTAGVOR d;
  
  d.NUMMERTYP = iFunction;
  d.NUMMERMINDEST = vertriebszentrum;
  if ( AaplanVor_sel_uni( &d, error_msg ) || d.NUMMERWERT == 0 ) return lRealTime;
  
  iMin  = ( lRealTime % 100 ) + d.NUMMERWERT;
  iHour = ( lRealTime / 100 ) % 100; 
  
  iSumMin = ( iHour * 60 ) + iMin;                                  
  
  sprintf( szpTime, "%02d%02d", iSumMin / 60, iSumMin % 60 );  

  return atol( szpTime );
}

/*** END ******************************************************************************/

