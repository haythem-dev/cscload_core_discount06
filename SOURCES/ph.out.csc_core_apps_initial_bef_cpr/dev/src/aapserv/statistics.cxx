/******************************************************************************/
/*                                                                            */
/* header  : ArtikelKontoAnz.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:42 2022                                         */
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
#include "statistics.h"

/* ArtikelKontoAnz: Select ****************************************************/



/* ArtikelKontoAnz: Insert ****************************************************/



/* ArtikelKontoAnz: Update ****************************************************/



/* ArtikelKontoAnz: Select ****************************************************/



/* ArtikelKontoAnz: Other *****************************************************/

/* ArtikelKontoAnz::SelList ***************************************************/

retClient Artikelkontoanz_SelList(artikelkontoanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Lagerrevisionanz_SelList";
    exec sql begin declare section;
    artikelkontoanzS *d;
    long artikelnrvon;
    long artikelnrbis;
    long idfnrvon;
    long idfnrbis;
    long filialnrvon;
    long filialnrbis;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
	if(d->ARTIKEL_NR == 0)
	{
		artikelnrvon = 0;
		artikelnrbis = 9999999;
	}
	else
	{
		artikelnrvon = artikelnrbis = d->ARTIKEL_NR;
	}
	if(d->IDFNR == 0)
	{
		idfnrvon = 0;
		idfnrbis = 9999999;
	}
	else
	{
		idfnrvon = idfnrbis = d->IDFNR;
	}
	if(d->FILIALNR == 0)
	{
		filialnrvon = 0;
		filialnrbis = 99;
	}
	else
	{
		filialnrvon = filialnrbis = d->FILIALNR;
	}
      exec sql declare CSelkonto cursor with hold for
                select artikelkonto.lfdnr,
                     artikelkonto.filialnr,
                     artikelkonto.artikel_nr,
                     artikelkonto.BewegungsArt,
                     artikelkonto.menge,
                     artikelkonto.BelegNr,
                     artikelkonto.uid,
                     artikelkonto.idfnr,
                     artikelkonto.MengeNeu,
                     artikelkonto.ZeitUnix,
                     artikelkonto.BewegungSchluessel,
                     artikelkonto.StockReserved,
                     artikelkonto.MoveType
                from artikelkonto
                where artikelkonto.filialnr	>=	:filialnrvon	 and
                      artikelkonto.filialnr	<=	:filialnrbis	 and
                      artikelkonto.artikel_nr	>=	:artikelnrvon	 and
                      artikelkonto.artikel_nr	<=	:artikelnrbis	 and
                      artikelkonto.idfnr	>=	:idfnrvon	 and
                      artikelkonto.idfnr	<=	:idfnrbis	 and
                      artikelkonto.ZeitUnix	>=	:d->ZEITUNIX	 and
                      artikelkonto.ZeitUnix	<=	:d->ZEIT_BIS;
      exec sql open CSelkonto;
      if ( ( rc=CheckSql( fun, stError, "%s", "open CSelkonto" ) ) != IS_OK )
        return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelkonto;
      return CheckSql( fun, stError, "%s", "close CSelkonto" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelkonto into :d->LFDNR,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BEWEGUNGSART,
                     :d->MENGE,
                     :d->BELEGNR,
                     :d->UID,
                     :d->IDFNR,
                     :d->MENGENEU,
                     :d->ZEITUNIX,
                     :d->BEWEGUNGSCHLUESSEL,
                     :d->STOCKRESERVED,
                     :d->MOVETYPE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelkonto" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : Aufwertherst.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:43 2022                                         */
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
#include "statistics.h"

/* Aufwertherst: Select *******************************************************/

/* Aufwertherst::SelList ******************************************************/

retClient Aufwertherst_SelList(aufwertherstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Aufwertherst_SelList";
    exec sql begin declare section;
    aufwertherstS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select kdauftragpos.kdauftragnr, artikelzentral.hersteller_code, 
sum( kdauftragpos.mengebestaetigt* kdauftragpos.preisekapo)
                         into :d->KDAUFTRAGNR,	:d->HERSTELLER_CODE,	:d->PREISEKAPO
                   from KDAUFTRAGPOS, ARTIKELZENTRAL
                  where kdauftragpos.kdauftragnr	 =	:d->KDAUFTRAGNR
                        and kdauftragpos.artikel_nr	 =	artikelzentral.artikel_nr
                        group by kdauftragpos.kdauftragnr, artikelzentral.hersteller_code;
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
    exec sql fetch CSelList0;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Aufwertherst: Insert *******************************************************/



/* Aufwertherst: Update *******************************************************/



/* Aufwertherst: Select *******************************************************/



/* Aufwertherst: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Feiertag.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:47 2022                                         */
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
#include "statistics.h"

/* Feiertag: Select ***********************************************************/

/* Feiertag::SelAll ***********************************************************/

retClient Feiertag_SelAll(feiertagS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Feiertag_SelAll";
    exec sql begin declare section;
    feiertagS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAll1 cursor with hold for
                  select feiertag.filialnr,
                     feiertag.modus,
                     feiertag.tag,
                     feiertag.von_jahr,
                     feiertag.bis_jahr,
                     feiertag.tagname
                from feiertag
                  where feiertag.filialnr	 =	:d->FILIALNR	
                        order by feiertag.tag;
        exec sql open CSelAll1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAll1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAll1;
        return CheckSql( fun, stError, "%s", "close CSelAll1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAll1 into :d->FILIALNR,
                     :d->MODUS,
                     :d->TAG,
                     :d->VON_JAHR,
                     :d->BIS_JAHR,
                     :d->TAGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAll1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Feiertag: Insert ***********************************************************/

/* Feiertag::Insert ***********************************************************/

retClient Feiertag_Insert(feiertagS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Feiertag_Insert";
    exec sql begin declare section;
    feiertagS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into feiertag (filialnr,
                     modus,
                     tag,
                     von_jahr,
                     bis_jahr,
                     tagname)
        values (:d->FILIALNR,
                     :d->MODUS,
                     :d->TAG,
                     :d->VON_JAHR,
                     :d->BIS_JAHR,
                     :d->TAGNAME);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert feiertag" ) ) != IS_OK )
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



/* Feiertag: Update ***********************************************************/

/* Feiertag::Update ***********************************************************/

retClient Feiertag_Update(feiertagS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Feiertag_Update";
    exec sql begin declare section;
    feiertagS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate2 cursor with hold for
              select filialnr,
                     modus,
                     tag,
                     von_jahr,
                     bis_jahr,
                     tagname
               from feiertag
              where feiertag.filialnr	 =	:d->FILIALNR	 and
                    feiertag.modus	 =	:d->MODUS_ALT	 and
                    feiertag.tag	 =	:d->TAG_ALT
              for update;
    exec sql open CUpdate2;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate2;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate2" ) ) != IS_OK )
            break;
        exec sql update feiertag set filialnr = :d->FILIALNR,
                     modus = :d->MODUS,
                     tag = :d->TAG,
                     von_jahr = :d->VON_JAHR,
                     bis_jahr = :d->BIS_JAHR,
                     tagname = :d->TAGNAME where current of CUpdate2;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate2" ) ) != IS_OK )
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
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* Feiertag: Select ***********************************************************/

/* Feiertag::Delete ***********************************************************/

retClient Feiertag_Delete(feiertagS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Feiertag_Delete";
    exec sql begin declare section;
    feiertagS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete3 cursor with hold for
              select filialnr,
                     modus,
                     tag,
                     von_jahr,
                     bis_jahr,
                     tagname
               from feiertag
              where feiertag.filialnr	 =	:d->FILIALNR	 and
                    feiertag.modus	 =	:d->MODUS	 and
                    feiertag.tag	 =	:d->TAG
              for update;
    exec sql open CDelete3;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete3" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete3" ) ) != IS_OK )
            break;
        exec sql delete from feiertag where current of CDelete3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete3" ) ) != IS_OK )
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



/* Feiertag: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : LagerRevisionAnz.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:49 2022                                         */
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
#include "statistics.h"

/* LagerRevisionAnz: Select ***************************************************/



/* LagerRevisionAnz: Insert ***************************************************/



/* LagerRevisionAnz: Update ***************************************************/



/* LagerRevisionAnz: Select ***************************************************/



/* LagerRevisionAnz: Other ****************************************************/

/* LagerRevisionAnz::SelList **************************************************/

retClient Lagerrevisionanz_SelList(lagerrevisionanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Lagerrevisionanz_SelList";
    exec sql begin declare section;
    lagerrevisionanzS *d;
	long datumvon;
	long datumbis;
	long artikelnrvon;
	long artikelnrbis;
	long filialnrvon;
	long filialnrbis;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
		if(d->DATUM == 0)
		{
			datumvon = 19990101;
			datumbis = 20991231;
		}
		else
		{
			datumvon = datumbis = d->DATUM;
		}
		if(d->ARTIKEL_NR == 0)
		{
			artikelnrvon = 0;
			artikelnrbis = 9999999;
		}
		else
		{
			artikelnrvon = artikelnrbis = d->ARTIKEL_NR;
		}
		if(d->FILIALNR == 0)
		{
			filialnrvon = 0;
			filialnrbis = 99;
		}
		else
		{
			filialnrvon = filialnrbis = d->FILIALNR;
		}
      exec sql declare CSelrevision cursor with hold for
                select lagerrevision.filialnr,
                     lagerrevision.artikel_nr,
                     lagerrevision.datum,
                     lagerrevision.uhrzeit,
                     lagerrevision.BestandKsc,
                     lagerrevision.BestandVSE
                from LAGERREVISION
                where LagerRevision.filialnr	>=	:filialnrvon	 and
                      LagerRevision.filialnr	<=	:filialnrbis	 and
                      LagerRevision.artikel_nr	>=	:artikelnrvon	 and
                      LagerRevision.artikel_nr	<=	:artikelnrbis	 and
                      LagerRevision.datum	>=	:datumvon	 and
                      LagerRevision.datum	<=	:datumbis;
      exec sql open CSelrevision;
      if ( ( rc=CheckSql( fun, stError, "%s", "open CSelrevision" ) ) != IS_OK )
        return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelrevision;
      return CheckSql( fun, stError, "%s", "close CSelrevision" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelrevision into :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->DATUM,
                     :d->UHRZEIT,
                     :d->BESTANDKSC,
                     :d->BESTANDVSE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelrevision" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : OECustomerCalls.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:52 2022                                         */
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
#include "statistics.h"

/* OECustomerCalls: Select ****************************************************/



/* OECustomerCalls: Insert ****************************************************/

/* OECustomerCalls::Insert ****************************************************/

retClient Oecustomercalls_Insert(oecustomercallsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Oecustomercalls_Insert";
    exec sql begin declare section;
    oecustomercallsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
        a->CALLDATE = ppGGetDate() ;
    a->CALLTIME = ppGGetTime() ;
    exec sql insert into oecustomercalls (BranchNo,
                     CustomerNo,
                     CallDate,
                     CallTime,
                     CallEffect,
                     cscorderno)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->CALLDATE,
                     :d->CALLTIME,
                     :d->CALLEFFECT,
                     :d->CSCORDERNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert oecustomercalls" ) ) != IS_OK )
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



/* OECustomerCalls: Update ****************************************************/

/* OECustomerCalls::Update ****************************************************/

retClient Oecustomercalls_Update(oecustomercallsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Oecustomercalls_Update";
    exec sql begin declare section;
    oecustomercallsS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate4 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     CallDate,
                     CallTime,
                     CallEffect,
                     cscorderno
               from OECustomerCalls
              where OECustomerCalls.BranchNo	 =	:d->BRANCHNO	 and
                    OECustomerCalls.CustomerNo	 =	:d->CUSTOMERNO	 and
                    OECustomerCalls.CallDate	 =	:d->CALLDATE	 and
                    OECustomerCalls.CallTime	 =	:d->CALLTIME
              for update;
    exec sql open CUpdate4;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate4" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate4" ) ) != IS_OK )
            break;
        exec sql update oecustomercalls set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     CallDate = :d->CALLDATE,
                     CallTime = :d->CALLTIME,
                     CallEffect = :d->CALLEFFECT,
                     cscorderno = :d->CSCORDERNO where current of CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate4" ) ) != IS_OK )
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
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* OECustomerCalls: Select ****************************************************/



/* OECustomerCalls: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : OffenAuftrag.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:57 2022                                         */
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
#include "statistics.h"

/* OffenAuftrag: Select *******************************************************/

/* OffenAuftrag::SelList ******************************************************/

retClient Offenauftrag_SelList(offenauftragS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Offenauftrag_SelList";
    exec sql begin declare section;
    offenauftragS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList5 cursor with hold for
                  select kdauftrag.kdauftragnr,
                     kdauftrag.filialnr,
                     kdauftragpos.mengebestellt,
                     kdauftrag.kdauftragart,
                     kdauftragpos.mengenatra,
                     kdauftrag.datumauslieferung,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.darreichform,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.hersteller_nr
                from KDAUFTRAG, KDAUFTRAGPOS, ARTIKELZENTRAL, ARTIKELLOKAL
                  where kdauftrag.kdauftragart	 =	:d->KDAUFTRAGART	 and
                        kdauftrag.koart	 =	'2' and
                        kdauftrag.buchart	 =	'2' and
                        kdauftrag.datumauslieferung	 >	0 and
                        kdauftrag.kdauftragnr	 =	kdauftragpos.kdauftragnr and
                        kdauftrag.filialnr	 =	:d->FILIALNR	 and
                        kdauftragpos.artikel_nr	 =	artikelzentral.artikel_nr and
                        kdauftragpos.artikel_nr	 =	artikellokal.artikel_nr and
                        artikellokal.filialnr	 =	kdauftrag.filialnr
                        order by artikelzentral.artikel_nr;
        exec sql open CSelList5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList5;
        return CheckSql( fun, stError, "%s", "close CSelList5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList5 into :d->KDAUFTRAGNR,
                     :d->FILIALNR,
                     :d->MENGEBESTELLT,
                     :d->KDAUFTRAGART,
                     :d->MENGENATRA,
                     :d->DATUMAUSLIEFERUNG,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->DARREICHFORM,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->HERSTELLER_NR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList5" )) == IS_ERROR )
        return rc;
    return rc;
}



/* OffenAuftrag: Insert *******************************************************/



/* OffenAuftrag: Update *******************************************************/



/* OffenAuftrag: Select *******************************************************/



/* OffenAuftrag: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : RUFSTAT.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:05 2022                                         */
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
#include "statistics.h"

/* RUFSTAT: Select ************************************************************/



/* RUFSTAT: Insert ************************************************************/



/* RUFSTAT: Update ************************************************************/



/* RUFSTAT: Select ************************************************************/



/* RUFSTAT: Other *************************************************************/

/* RUFSTAT::Sel_Tagstat *******************************************************/

retClient Rufstat_Sel_Tagstat(rufstatS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Rufstat_Sel_Tagstat";
static int fst = 1;
static int plan;
static int postpone1;
static int postpone2;
static int postpone3;
static int postpone_more;
static int postpone_total;
static long intervall;
static long vonzeit;
static long endzeit;
static int endfetch = 0;

EXEC SQL BEGIN DECLARE SECTION;
rufstatS *d;
struct a1
{
  long zeit;
  long kundennr;
  short verschoben;
  short kz;
} satz;
long zeitab;
long zeitbis;
long ldatum;
short iVZ;
exec sql end declare section;

d = a;
if (endfetch != 0)
{
	fst = 1;
	exec sql drop table t_rufe;
	endfetch = 0;
	return IS_NOTFOUND;
}

if (fst) /* beim ersten mal oder bei neu deklarieren */
{
	fst = 0;
	zeitab = d->ZEIT_VON;
	zeitbis = d->ZEIT_BIS;
	intervall = d->ANZ_PLAN - 1;
	iVZ = d->ANZ_POSTPONE1;
	if (d->DATUM == 0)
	{
		ldatum = AllgGetDate();
	}
	else
	{
		ldatum = d->DATUM;
	}
	exec sql drop table t_rufe;

	exec sql select
			kundeanrufplanprot.vertriebszentrumnr,
			kundeanrufplanprot.kundennr,
			kundeanrufplanprot.urrufzeit,
			kundeanrufplanprot.datum
		from kundeanrufplanprot,kundeanrufplantag where
			kundeanrufplanprot.datum = kundeanrufplantag.datum and
			kundeanrufplanprot.vertriebszentrumnr = kundeanrufplantag.vertriebszentrumnr and
			kundeanrufplanprot.kundennr = kundeanrufplantag.kundennr  and
			kundeanrufplanprot.urrufzeit = kundeanrufplantag.urrufzeit and
			kundeanrufplantag.rufeinstellung != 0  and
			kundeanrufplanprot.anrufstatus = 0  and
			kundeanrufplanprot.datum = :ldatum
			and kundeanrufplanprot.urrufzeit >= :zeitab 
			and kundeanrufplanprot.urrufzeit <= :zeitbis 
			and kundeanrufplanprot.vertriebszentrumnr = :iVZ 
		order by kundeanrufplanprot.urrufzeit
		into temp t_rufe;
	if ( ( rc=CheckSql( fun, stError, "%s", "select into temp" ) ) != IS_OK )
		return rc;

	exec sql declare CC cursor with hold for select
		kundeanrufplanprot.urrufzeit,
		kundeanrufplanprot.kundennr,
		count(*),
		0
	from kundeanrufplanprot,t_rufe where
		kundeanrufplanprot.datum = t_rufe.datum and
		kundeanrufplanprot.vertriebszentrumnr = t_rufe.vertriebszentrumnr and
		kundeanrufplanprot.kundennr = t_rufe.kundennr and
		kundeanrufplanprot.urrufzeit = t_rufe.urrufzeit
		and ( anrufstatus = 1 or anrufstatus = 2 )
	group by kundeanrufplanprot.urrufzeit,kundeanrufplanprot.kundennr
	union select
		kundeanrufplanprot.urrufzeit,
		kundeanrufplanprot.kundennr,
		count(*),
		1
	from kundeanrufplanprot,t_rufe where
		kundeanrufplanprot.datum = t_rufe.datum and
		kundeanrufplanprot.vertriebszentrumnr = t_rufe.vertriebszentrumnr and
		kundeanrufplanprot.kundennr = t_rufe.kundennr and
		kundeanrufplanprot.urrufzeit = t_rufe.urrufzeit
		and anrufstatus = 0
	group by kundeanrufplanprot.urrufzeit,kundeanrufplanprot.kundennr
	order by 1,2;

	exec sql open CC;
	if ( ( rc=CheckSql( fun, stError, "%s", "open CC" ) ) != IS_OK )
		return rc;

	AllgAddTime(zeitab, intervall, &endzeit);
	exec sql fetch CC into :satz;
	if ( ( rc=CheckSql( fun, stError, "%s", "open CC" ) ) < IS_OK )
		return rc;
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		fst = 1;
		exec sql close CC;
		return IS_NOTFOUND;
	}
	for(;satz.zeit > endzeit;)
	{
		AllgAddTime(endzeit, 1, &vonzeit);
		AllgAddTime(vonzeit, intervall, &endzeit);
	}

	/*	Summenfelder initialisieren */
	plan = 0;
	postpone1 = 0;
	postpone2 = 0;
	postpone3 = 0;
	postpone_more = 0;
	postpone_total = 0;
	if(satz.kz == 1) plan = 1;
	else
	{
		if(satz.verschoben == 1) postpone1 = 1;
		else if(satz.verschoben == 2) postpone2 = 1;
		else if(satz.verschoben == 3) postpone3 = 1;
		else postpone_more = 1;
	}
	postpone_total = satz.verschoben;
}

for (;;)
{
	exec sql fetch CC into :satz;
	if ( ( rc=CheckSql( fun, stError, "%s", "open CC" ) ) < IS_OK )
		return rc;
	if (sqlca.sqlcode == SQLNOTFOUND || satz.zeit > endzeit)
	{
		d->ZEIT_VON = vonzeit;
		d->ZEIT_BIS = endzeit;
		d->ANZ_PLAN = plan;
		d->ANZ_POSTPONE1 = postpone1;
		d->ANZ_POSTPONE2 = postpone2;
		d->ANZ_POSTPONE3 = postpone3;
		d->ANZ_POSTPONE_MORE = postpone_more;
		d->ANZ_POSTPONE_TOTAL = postpone_total;
		if (sqlca.sqlcode == SQLNOTFOUND)
		{
			exec sql close CC;
			endfetch = 1;
		}
		else
		{
			for(;satz.zeit > endzeit;)
			{
				AllgAddTime(endzeit, 1, &vonzeit);
				AllgAddTime(vonzeit, intervall, &endzeit);
			}
		/*	Summenfelder initialisieren */
			plan = 0;
			postpone1 = 0;
			postpone2 = 0;
			postpone3 = 0;
			postpone_more = 0;
			postpone_total = 0;
			if(satz.kz == 1) plan = 1;
			else
			{
				if(satz.verschoben == 1) postpone1 = 1;
				else if(satz.verschoben == 2) postpone2 = 1;
				else if(satz.verschoben == 3) postpone3 = 1;
				else postpone_more = 1;
			}
			postpone_total = satz.verschoben;
		}
		return IS_OK;
	}
	if(satz.kz == 1) plan++;
	else
	{
		if(satz.verschoben == 1) postpone1++;
		else if(satz.verschoben == 2) postpone2++;
		else if(satz.verschoben == 3) postpone3++;
		else postpone_more++;
	}
	postpone_total += satz.verschoben;
}
}



/******************************************************************************/
/*                                                                            */
/* header  : TourZeit.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:10 2022                                         */
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
#include "statistics.h"

/* TourZeit: Select ***********************************************************/



/* TourZeit: Insert ***********************************************************/



/* TourZeit: Update ***********************************************************/



/* TourZeit: Select ***********************************************************/



/* TourZeit: Other ************************************************************/

/* TourZeit::SelNextTour ******************************************************/

retClient Tourzeit_SelNextTour(tourzeitS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
retClient rc = IS_OK;
char *fun = "SelNextTour";

exec sql begin declare section;
tourzeitS *d;
long datum;
long zeit;
long diff;
extern short FilialNr;
exec sql end declare section;

d = a;
zeit = AllgGetTime();
datum = AllgGetDate();
  exec sql select
  durchlaufnormal into :diff
  from paraauftragbearb
  where filialnr = :FilialNr;
if ( ( rc=CheckSql( fun, stError, "%s", "select paraauftragbearb" ) ) != IS_OK )
      return rc;
zeit += diff * 100;

  exec sql select
  MIN(tourplantag.tourid) into :d->TOURID
  from tourplantag,tour
  where tourplantag.idfnr = :d->IDFNR
  and tourplantag.vertriebszentrumnr = :d->VERTRIEBSZENTRUMNR
  and tourplantag.datumkommi = :datum
  and tourplantag.tourid > :zeit
  and tourplantag.kzautozuord = '1'
  and tourplantag.tourinaktiv != '1'
  and tour.tourinaktiv != '1'
  and tour.datumkommi = tourplantag.datumkommi
  and tour.filialnr = tourplantag.vertriebszentrumnr
  and tour.tourid = tourplantag.tourid
  ;
  return CheckSql( fun, stError, "%s", "select Tourzeit" );
}



