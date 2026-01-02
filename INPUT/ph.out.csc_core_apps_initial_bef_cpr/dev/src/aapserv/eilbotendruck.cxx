/******************************************************************************/
/*                                                                            */
/* header  : EilBotenDruck.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:31 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "eilbotendruck.h"

/* EilBotenDruck: Select ******************************************************/



/* EilBotenDruck: Insert ******************************************************/



/* EilBotenDruck: Update ******************************************************/



/* EilBotenDruck: Select ******************************************************/



/* EilBotenDruck: Other *******************************************************/

/* EilBotenDruck::druckeil ****************************************************/

retClient Eilbotendruck_druckeil(eilbotendruckS *a, tError *stError, bool bIsTrans)
{
#define DRUCK_PROZ	"druckeil"
#define UNTERSTRICH	"__________________________________________________________"
#define KASTEN	"I__I"
#include "aetexte.h"

retClient rc = IS_OK;
char *fun = "Eilbotendruck_Druckeil";
FILE *fp;
char outputFile[81];
char prntcmd[89];
char CDatum[11];
char CZeit[6];
long datum;
long zeit;
 
EXEC SQL BEGIN DECLARE SECTION;
eilbotendruckS   *d;
char nameapo[41];
char nameinhaber[31];
char strasse[31];
char ort[31];
char postleitzahl[8];
char telnr[21];
long entfernung;
EXEC SQL END DECLARE SECTION;
datum = AllgGetDate();
zeit = AllgGetTime();
d = a;

if (bIsTrans);
sprintf( outputFile, "%s/eildruck.%ld%ld%ld", (char *)getenv( "LOG_PATH" )
	,d->IDFNR,datum,zeit );

EXEC SQL select 
	kunde.nameapo,
	kunde.nameinhaber,
	kunde.strasse,
	kunde.ort,
	kunde.postleitzahl,
	kunde.telnr,
	kundelagerinfo.entfernunginkm
	into :nameapo,:nameinhaber,:strasse,:ort,:postleitzahl,:telnr,:entfernung
	from kunde,outer kundelagerinfo
	where kunde.idfnr = :d->IDFNR
	and kunde.filialnr = :d->FILIALNR
	and kunde.vertriebszentrumnr = :d->VERTRIEBSZENTRUMNR
	and kundelagerinfo.kundennr = kunde.kundennr
	and kundelagerinfo.filialnr = kunde.filialnr
	and kundelagerinfo.vertriebszentrumnr = kunde.vertriebszentrumnr;
if ( ( rc=CheckSql( fun, stError,  "%s", "select druckeil" ) ) != IS_OK )
	return rc;
if ( (fp=fopen( outputFile, "a" )) == (FILE *)0 ) return IS_WARNING;
fprintf( fp, "%s\r\n\n\n",
	"            F A H R A U F T R A G");
AllgDatumLong2CharTTMMJJJJ(datum, CDatum);
fprintf( fp, "%-15s: %s\r\n",
	AET_DATUM,CDatum);
fprintf( fp, "%-15s: %2.2s:%2.2s/%2.2s\r\n",
	AET_TOUR,d->TOURID,d->TOURID+2,d->TOURID+4);
fprintf( fp, "%-15s: %ld\r\n",
	AET_IDF_NR,d->IDFNR);
fprintf( fp, "%-15s: %s\r\n",
	AET_APOTHEKENNAME,nameapo);
fprintf( fp, "%-15s: %s\r\n",
	AET_INHABER,nameinhaber);
fprintf( fp, "%-15s: %s\r\n",
	AET_STRASSE,strasse);
fprintf( fp, "%-15s: %s %s\r\n",
	AET_PLZ_ORT,postleitzahl,ort);
fprintf( fp, "%-15s: %s\r\n",
	AET_TELEFON,telnr);
fprintf( fp, "%-15s: %s\r\n",
	AET_BEMERKUNG,d->BEMERKUNGEN);
fprintf( fp, "%-15s: %ld\r\n",
	AET_ENTFERNUNG,entfernung);
fprintf( fp, "%-15s: %s\r\n",
	AET_ANWENDER,d->USERNAME);
AllgZeitLong2CharHHMM(zeit, CZeit);
fprintf( fp, "%-15s: %s\r\n\n\n",
	AET_ZEIT,CZeit);
fprintf( fp, "%-15s: %s\r\n\n",
	"Abfahrtzeit",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"von - nach",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"von - nach",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"von - nach",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n\n",
	"von - nach",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"Spediteur",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"Fahrer",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"Entfernung Ges.",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	AET_ZEIT,UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n",
	"Kosten Ges.",UNTERSTRICH);
fprintf( fp, "%-15s: %s\r\n\n\n",
	"Weiterbelastung",UNTERSTRICH);
fprintf( fp, "%-15s%s %s   %s %s   %s %s   %s %s\r\n\f",
	"Fahrzeug",KASTEN,"Kombi",KASTEN,"Bus",KASTEN,"Transporter",KASTEN,"LKW");
fclose(fp);
sprintf(prntcmd,"%s %s %d",DRUCK_PROZ,outputFile,d->VERTRIEBSZENTRUMNR);
system(prntcmd);

return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : ExtraTourReasons.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:34 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "eilbotendruck.h"

/* ExtraTourReasons: Select ***************************************************/

/* ExtraTourReasons::SelList **************************************************/

retClient Extratourreasons_SelList(extratourreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Extratourreasons_SelList";
    exec sql begin declare section;
    extratourreasonsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select extratourreasons.ExtraTourReason,
                     extratourreasons.cscordertype
                from ExtraTourReasons
                  where  ExtraTourReasons.cscordertype	 =	:d->CSCORDERTYPE	
                        order by ExtraTourReasons.ExtraTourReason;
        exec sql open CSelList0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList0;
        return CheckSql( fun, stError, "%s", "close CSelList0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList0 into :d->EXTRATOURREASON,
                     :d->CSCORDERTYPE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ExtraTourReasons::SelListAll ***********************************************/

retClient Extratourreasons_SelListAll(extratourreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Extratourreasons_SelListAll";
    exec sql begin declare section;
    extratourreasonsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListAll1 cursor with hold for
                  select extratourreasons.ExtraTourReason,
                     extratourreasons.cscordertype
                from ExtraTourReasons
                  where ExtraTourReasons.cscordertype	!=	' '
                        order by ExtraTourReasons.cscordertype, ExtraTourReasons.ExtraTourReason;
        exec sql open CSelListAll1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListAll1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListAll1;
        return CheckSql( fun, stError, "%s", "close CSelListAll1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListAll1 into :d->EXTRATOURREASON,
                     :d->CSCORDERTYPE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListAll1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ExtraTourReasons: Insert ***************************************************/

/* ExtraTourReasons::Insert ***************************************************/

retClient Extratourreasons_Insert(extratourreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Extratourreasons_Insert";
    exec sql begin declare section;
    extratourreasonsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into extratourreasons (ExtraTourReason,
                     cscordertype)
        values (:d->EXTRATOURREASON,
                     :d->CSCORDERTYPE);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert extratourreasons" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* ExtraTourReasons: Update ***************************************************/



/* ExtraTourReasons: Select ***************************************************/

/* ExtraTourReasons::Delete ***************************************************/

retClient Extratourreasons_Delete(extratourreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Extratourreasons_Delete";
    exec sql begin declare section;
    extratourreasonsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete2 cursor with hold for
              select ExtraTourReason,
                     cscordertype
               from ExtraTourReasons
              where ExtraTourReasons.ExtraTourReason	 =	:d->EXTRATOURREASON and
                    ExtraTourReasons.cscordertype	 =	:d->CSCORDERTYPE
              for update;
    exec sql open CDelete2;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete2" ) ) != IS_OK )
            break;
        exec sql delete from extratourreasons where current of CDelete2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete2" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* ExtraTourReasons: Other ****************************************************/



