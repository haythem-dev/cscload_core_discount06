#include <stdio.h>
#include <string.h>
#include "aarufpl.h"
#include "allg.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define NOT_FOUND        1
#define FILE_NOT_FOUND   1
#define ERROR           -1
#define WARNING         -2
#define SCODE			 sqlca.sqlcode
#define SISAM            sqlca.sqlerrd[1] 
#define SUPDA			 sqlca.sqlerrd[2]
#define SERRM			 sqlca.sqlerrm


/*** MACROS ***************************************************************************/

#define SQLERROR(x,y) if ( SCODE < 0 ) { sprintf( error_msg, "%s: %s %ld/%ld %s",	x, y, SCODE, SISAM, SERRM );\
                      return -1; }
#define NOTFOUND      sqlca.sqlcode == SQLNOTFOUND
#define ISFOUND       NOTFOUND ? NOT_FOUND : 0


/*  externeGLOBALE C-VARIABLEN  */

EXEC SQL BEGIN DECLARE SECTION;
char str[2048];
EXEC SQL END DECLARE SECTION;


/*** kscCheck_Callplan ( Prüfen und evtl. Löschen nächsten Eintrag im Anrufplan) *******************/ 

int kscCheck_Callplan(struct RUFPTAG *d, char *error_msg)
{
	char *fun = "kscCheck_Callplan";
	EXEC SQL BEGIN DECLARE SECTION;
	struct RUFPTAG *a;
	long datum;
	long zeitVon;
	long zeit;
	short aktion;
	long rufzeit;
	EXEC SQL END DECLARE SECTION;

	a = d;


	datum = AllgGetDate();
	zeit = AllgGetTime();
	zeitVon = ( zeit / 100 );

	strcpy( str, "select  " );
	strcat( str, "tagplan.lfdaktion " );
	strcat( str, ",tagplan.rufzeit " );
	strcat( str, "from tagplan, tagplanereignis " );
	strcat( str, "where tagplan.filialnr = ? " );
	strcat( str, "and tagplan.idfnr = tagplanereignis.idfnr " );
	strcat( str, "and tagplan.filialnr = tagplanereignis.filialnr " );
	strcat( str, "and tagplan.rufzeit = tagplanereignis.rufzeit " );
	strcat( str, "and tagplan.datum = tagplanereignis.datum " );
	strcat( str, "and tagplan.lfdaktion = tagplanereignis.lfdaktion " );
	strcat( str, "and tagplan.zugriff = 0 " );
	strcat( str, "and tagplan.datum = ? " );
	strcat( str, "and tagplanereignis.rufzeitgeaendert >= ? " );
	strcat( str, "and tagplanereignis.rufzeitgeaendert <= ? " );    
	strcat( str, "and tagplan.anrufart = \"PH\" " );           
	strcat( str, "and tagplan.idfnr = ? " );
	strcat( str, "and (tagplanereignis.status=6 or tagplanereignis.status=7) " );
	strcat( str, "order by tagplanereignis.rufzeitgeaendert, " );
	strcat( str, "tagplanereignis.rufzeit, tagplan.prioritaet " );
	
	exec sql prepare selRufptag from :str;
	SQLERROR( fun, "prepare selRufptag" )
	
	exec sql declare Sel_tag_plan scroll cursor for selRufptag;
	exec sql open Sel_tag_plan using	:a->FILIALNR,
										:datum,
										:zeitVon,
										:a->RUFZEIT,
										:a->IDFNR;
	SQLERROR( fun, "open Sel_tag_plan" )
	
	exec sql fetch Sel_tag_plan into :aktion,:rufzeit;
	SQLERROR( fun, "fetch Sel_tag_plan" )
	if ( NOTFOUND ) return 0;

	aktion++;
	EXEC SQL begin work;
	SQLERROR( fun, "begin" )

	exec sql update tagplan
	set lfdaktion = :aktion,
	prioritaet = '0'
	where filialnr = :a->FILIALNR
	and idfnr    = :a->IDFNR
	and datum    = :datum
	and rufzeit  = :rufzeit;

	SQLERROR( fun, "update tagplan" )
							  
	exec sql insert into tagplanereignis (	datum,
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
	                              values (	:datum,
											:rufzeit,
											:a->IDFNR,
											:aktion,
											'3',
											'0',
											:rufzeit,
											:zeit,
											'0',
											"Order received",
											:a->FILIALNR );
	SQLERROR( fun, "insert tagplanereignis" )
	EXEC SQL commit work;
	SQLERROR( fun, "commit" )

	exec sql close Sel_tag_plan;
	SQLERROR( fun, "close Sel_tag_plan" )

	return 0;
}
