/******************************************************************************/
/*                                                                            */
/* header  : ArtStock.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:08 2022                                         */
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
#include "verbundcheck.h"

/* ArtStock: Select ***********************************************************/



/* ArtStock: Insert ***********************************************************/



/* ArtStock: Update ***********************************************************/



/* ArtStock: Select ***********************************************************/



/* ArtStock: Other ************************************************************/

/* ArtStock::SelList **********************************************************/

retClient Artstock_SelList(artstockS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artstock_SelList";
    exec sql begin declare section;
    artstockS *d;
	char str[2048];
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
		strcpy(str,"select artikellokal.filialnr,");
		strcat(str,"artikellokal.artikel_nr,");
		strcat(str,"artikellokal.bestand ");
		strcat(str,"from artikellokal ");
		strcat(str,"where artikellokal.artikel_nr = ? ");
		strcat(str,"and artikellokal.filialnr not in ");
		strcat(str,d->EXCLUDEDBRANCHES);
		EXEC SQL PREPARE dec_noibt FROM :str;
        if ( ( rc=CheckSql( fun, stError, "%s", "prepare dec_noibt" ) ) != IS_OK )
            return rc;
	    EXEC SQL declare CSelList0 cursor with hold for dec_noibt;
        exec sql open CSelList0 using :d->ARTIKEL_NR;
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
    exec sql fetch CSelList0 into :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BESTAND;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : CheckIBTDone.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:10 2022                                         */
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
#include "verbundcheck.h"

/* CheckIBTDone: Select *******************************************************/

/* CheckIBTDone::IsIBTDone ****************************************************/

retClient Checkibtdone_IsIBTDone(checkibtdoneS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkibtdone_IsIBTDone";
    exec sql begin declare section;
    checkibtdoneS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdverbundpos.herkunftfiliale,
                     kdverbundpos.kdauftragnr,
                     kdverbundpos.posnr,
                     kdverbundpos.filialnr,
                     kdverbundpos.ProcessingStatus
                into :d->HERKUNFTFILIALE,
                     :d->KDAUFTRAGNR,
                     :d->POSNR,
                     :d->FILIALNR,
                     :d->PROCESSINGSTATUS
                from KDVERBUNDPOS
              where KdverbundPos.filialnr	 =	:d->FILIALNR	 and
                    KdverbundPos.herkunftfiliale	 =	:d->HERKUNFTFILIALE	 and
                    KdverbundPos.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    KdverbundPos.posnr	 =	:d->POSNR and
                    KdverbundPos.ProcessingStatus	 =	2;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CheckIBTDone::SelIBTDoneOrder **********************************************/

retClient Checkibtdone_SelIBTDoneOrder(checkibtdoneS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkibtdone_SelIBTDoneOrder";
    exec sql begin declare section;
    checkibtdoneS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select first 1 KdverbundPos.posnr
                into :d->POSNR
                from KDVERBUNDPOS
              where KdverbundPos.herkunftfiliale	 =	:d->HERKUNFTFILIALE	 and
                    KdverbundPos.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    KdverbundPos.ProcessingStatus	 =	2;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckIBTDone: Insert *******************************************************/



/* CheckIBTDone: Update *******************************************************/



/* CheckIBTDone: Select *******************************************************/



/* CheckIBTDone: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : VERBUNDMOEGL.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:13 2022                                         */
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
#include "verbundcheck.h"

/* VERBUNDMOEGL: Select *******************************************************/



/* VERBUNDMOEGL: Insert *******************************************************/



/* VERBUNDMOEGL: Update *******************************************************/



/* VERBUNDMOEGL: Select *******************************************************/



/* VERBUNDMOEGL: Other ********************************************************/

/* VERBUNDMOEGL::SelVbBestandNeu **********************************************/

retClient Verbundmoegl_SelVbBestandNeu(verbundmoeglS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Verbundmoegl_SelVbBestand";
int pos;
exec sql begin declare section;
 verbundmoeglS *d;
 long lTime;
 long artikelnr;
 short FilNr;
 extern short FilialNr;
 long BgaNr;
 char prisoart[2];
 char cverbundartikel[2];
 char buffer[512];
exec sql end declare section;

d = a;

pos = 1;

exec sql drop table t_fili;
exec sql drop table t_allfili;
exec sql drop table t_quota;

if (d->FILIALNR == 0) FilNr = FilialNr;
else FilNr = d->FILIALNR;

 exec sql select artikellokal.artikel_nr,artikellokal.prisoart,artikellokal.verbundartikel
 into :artikelnr,:prisoart,:cverbundartikel
 from artikellokal
 where artikellokal.artikel_nr = :d->ARTIKEL_NR
 and artikellokal.verbundartikel != '0'
 and artikellokal.filialnr = :FilNr;

if ( ( rc=CheckSql( fun, stError, "%s", "select artikelnr" ) ) != IS_OK )
 return rc;

a->WEEKDAY = ppGGetWeekDay(ppGGetDate(), stError->spError);
lTime = ppGGetTime();
 
exec sql select bganr_ek
  into :BgaNr
  from filiale
  where filialnr = :FilNr;

 strcpy(buffer,"select unique alternativfiliale.verbundfilialnr");
 strcat(buffer," from alternativfiliale,zeitarten");
 strcat(buffer," where alternativfiliale.verbundfilialnr = zeitarten.zeitschluessel");
 strcat(buffer," and alternativfiliale.vbtyp in (");
 if(cverbundartikel[0] == '1')
 {
   strcat(buffer,"0");
 }
 else if(cverbundartikel[0] == '2')
 {
   strcat(buffer,"1");
 }
 else if(cverbundartikel[0] == '3')
 {
   strcat(buffer,"2");
 }
 else if(cverbundartikel[0] == '4')
 {
   strcat(buffer,"3");
 }
 else if(cverbundartikel[0] == '5')
 {
   strcat(buffer,"5");
 }
 else if(cverbundartikel[0] == '6')
 {
   strcat(buffer,"3");
   strcat(buffer,",5");
 }
 else if(cverbundartikel[0] == '7')
 {
   strcat(buffer,"0");
   strcat(buffer,",5");
 }
 else if(cverbundartikel[0] == '8')
 {
   strcat(buffer,"0");
   strcat(buffer,",3");
 }
 else
 {
   strcat(buffer,"0");
   strcat(buffer,",3");
   strcat(buffer,",5");
 }
 strcat(buffer,") and alternativfiliale.filialnr = ?");
 strcat(buffer," and ( alternativfiliale.filialtyp = 2 or alternativfiliale.filialtyp = 3 )");
 strcat(buffer," and zeitarten.weekday = ?");
 strcat(buffer," and zeitarten.zeitart = 2");
 strcat(buffer," and zeitarten.zeitbegin <= ?");
 strcat(buffer," and zeitarten.zeitende >= ?");
 strcat(buffer," and zeitarten.vertriebszentrumnr = ?");
 strcat(buffer," into temp t_allfili;");

 EXEC SQL PREPARE sel_allfili FROM :buffer;
 if ( ( rc=CheckSql( fun, stError, "%s", "declare vb-filialen" ) ) != IS_OK )
  return rc;
 exec sql execute sel_allfili
  using :FilNr,
        :d->WEEKDAY,
        :lTime,
        :lTime,
        :FilNr;
 if ( ( rc=CheckSql( fun, stError, "%s", "select vb-filialen" ) ) != IS_OK )
  return rc;

exec sql select unique alternativfiliale.verbundfilialnr
   from alternativfiliale,zeitarten,filiale
   where alternativfiliale.verbundfilialnr = zeitarten.zeitschluessel
   and alternativfiliale.filialnr = :FilNr
   and ( alternativfiliale.filialtyp = 2 or alternativfiliale.filialtyp = 3 )
   and zeitarten.weekday = :d->WEEKDAY
   and zeitarten.zeitart = 2
   and zeitarten.zeitbegin <= :lTime
   and zeitarten.zeitende >= :lTime
   and zeitarten.vertriebszentrumnr = :FilNr
   and filiale.filialnr = zeitarten.vertriebszentrumnr
   and filiale.bganr_ek not in
   (select articlequota.customerno from articlequota
   where articlequota.articleno = :artikelnr
   and (articlequota.quota - articlequota.kumqty) = 0
   and alternativfiliale.verbundfilialnr = articlequota.branchno)
  into temp t_fili;

if ( ( rc=CheckSql( fun, stError, "%s", "select filialnr" ) ) != IS_OK )
 return rc;

exec sql select MAX(artikellokal.bestand)
   into :d->BESTAND
   from artikellokal,t_fili
   where artikellokal.artikel_nr = :artikelnr
   and artikellokal.filialnr = t_fili.verbundfilialnr
   and artikellokal.bestand > 0
   and artikellokal.verbundartikel != '0';

if ( ( rc=CheckSql( fun, stError, "%s", "select bestand" ) ) != IS_OK )
 return rc;

exec sql declare CSelVbBestand3 cursor with hold for
  select artikellokal.filialnr
  from artikellokal,t_fili
  where artikellokal.bestand = :d->BESTAND
  and artikellokal.filialnr = t_fili.verbundfilialnr
  and artikellokal.artikel_nr = :artikelnr
  and artikellokal.verbundartikel != '0'
  and artikellokal.artikelaktiv = '1';

exec sql open CSelVbBestand3;
  if ( ( rc=CheckSql( fun, stError, "%s", "open CSelVbBestand3" ) ) != IS_OK )
    return rc;
  exec sql fetch CSelVbBestand3
    into :d->FILIALNR;
  if ( ( rc=CheckSql( fun, stError, "%s", "fetch CSelVbBestand3" ) ) != IS_OK )
  {
    exec sql close CSelVbBestand3;
    return rc;
  }

exec sql close CSelVbBestand3;

return CheckSql( fun, stError, "%s", "close CSelVbBestand" );
}

/* VERBUNDMOEGL::SelVbBestandTM ***********************************************/

retClient Verbundmoegl_SelVbBestandTM(verbundmoeglS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Verbundmoegl_SelVbBestandTM";
int pos;
exec sql begin declare section;
 verbundmoeglS *d;
 long lTime;
 long artikelnr;
 short FilNr;
 extern short FilialNr;
 long BgaNr;
 char prisoart[2];
 char cverbundartikel[2];
 char buffer[512];
exec sql end declare section;

d = a;

pos = 1;

exec sql drop table t_fili;
exec sql drop table t_allfili;
exec sql drop table t_quota;

if (d->FILIALNR == 0) FilNr = FilialNr;
else FilNr = d->FILIALNR;

 exec sql select artikellokal.artikel_nr,artikellokal.prisoart,artikellokal.verbundartikel
 into :artikelnr,:prisoart,:cverbundartikel
 from artikellokal
 where artikellokal.artikel_nr = :d->ARTIKEL_NR
 and artikellokal.verbundartikel != '0'
 and artikellokal.filialnr = :FilNr;

if ( ( rc=CheckSql( fun, stError, "%s", "select artikelnr" ) ) != IS_OK )
 return rc;

a->WEEKDAY = ppGGetWeekDay(ppGGetDate(), stError->spError);
lTime = ppGGetTime();
 
exec sql select bganr_ek
  into :BgaNr
  from filiale
  where filialnr = :FilNr;

 strcpy(buffer,"select unique ibtbranches.ibtbranchno");
 strcat(buffer," from ibtbranches,zeitarten");
 strcat(buffer," where ibtbranches.ibtbranchno = zeitarten.zeitschluessel");
 strcat(buffer," and ibtbranches.ibttype in (");
 if(cverbundartikel[0] == '1')
 {
   strcat(buffer,"0");
 }
 else if(cverbundartikel[0] == '2')
 {
   strcat(buffer,"1");
 }
 else if(cverbundartikel[0] == '3')
 {
   strcat(buffer,"2");
 }
 else if(cverbundartikel[0] == '4')
 {
   strcat(buffer,"3");
 }
 else if(cverbundartikel[0] == '5')
 {
   strcat(buffer,"5");
 }
 else if(cverbundartikel[0] == '6')
 {
   strcat(buffer,"3");
   strcat(buffer,",5");
 }
 else if(cverbundartikel[0] == '7')
 {
   strcat(buffer,"0");
   strcat(buffer,",5");
 }
 else if(cverbundartikel[0] == '8')
 {
   strcat(buffer,"0");
   strcat(buffer,",3");
 }
 else
 {
   strcat(buffer,"0");
   strcat(buffer,",3");
   strcat(buffer,",5");
 }
 strcat(buffer,") and ibtbranches.branchno = ?");
 strcat(buffer," and ibtbranches.active_flag = 1");
 strcat(buffer," and zeitarten.weekday = ?");
 strcat(buffer," and zeitarten.zeitart = 2");
 strcat(buffer," and zeitarten.zeitbegin <= ?");
 strcat(buffer," and zeitarten.zeitende >= ?");
 strcat(buffer," and zeitarten.vertriebszentrumnr = ?");
 strcat(buffer," into temp t_allfili;");

 EXEC SQL PREPARE sel_allfili2 FROM :buffer;
 if ( ( rc=CheckSql( fun, stError, "%s", "declare vb-filialen" ) ) != IS_OK )
  return rc;
 exec sql execute sel_allfili2
  using :FilNr,
        :d->WEEKDAY,
        :lTime,
        :lTime,
        :FilNr;
 if ( ( rc=CheckSql( fun, stError, "%s", "select vb-filialen" ) ) != IS_OK )
  return rc;

exec sql select t_allfili.ibtbranchno
    from t_allfili
    where t_allfili.ibtbranchno not in
    (select t_quota.branchno from t_quota
    where t_quota.rest = 0)
   into temp t_fili;

exec sql select unique ibtbranches.ibtbranchno
   from ibtbranches,zeitarten,filiale
   where ibtbranches.ibtbranchno = zeitarten.zeitschluessel
   and ibtbranches.branchno = :FilNr
   and ibtbranches.active_flag = 1
   and zeitarten.weekday = :d->WEEKDAY
   and zeitarten.zeitart = 2
   and zeitarten.zeitbegin <= :lTime
   and zeitarten.zeitende >= :lTime
   and zeitarten.vertriebszentrumnr = :FilNr
   and filiale.filialnr = zeitarten.vertriebszentrumnr
   and filiale.bganr_ek not in
   (select articlequota.customerno from articlequota
   where articlequota.articleno = :artikelnr
   and (articlequota.quota - articlequota.kumqty) = 0
   and ibtbranches.ibtbranchno = articlequota.branchno)
  into temp t_fili;

if ( ( rc=CheckSql( fun, stError, "%s", "select filialnr" ) ) != IS_OK )
 return rc;

exec sql select MAX(artikellokal.bestand)
   into :d->BESTAND
   from artikellokal,t_fili
   where artikellokal.artikel_nr = :artikelnr
   and artikellokal.filialnr = t_fili.ibtbranchno
   and artikellokal.bestand > 0
   and artikellokal.verbundartikel != '0';

if ( ( rc=CheckSql( fun, stError, "%s", "select bestand" ) ) != IS_OK )
 return rc;

exec sql declare CSelVbBestandTM3 cursor with hold for
  select artikellokal.filialnr
  from artikellokal,t_fili
  where artikellokal.bestand = :d->BESTAND
  and artikellokal.filialnr = t_fili.ibtbranchno
  and artikellokal.artikel_nr = :artikelnr
  and artikellokal.verbundartikel != '0'
  and artikellokal.artikelaktiv = '1';

exec sql open CSelVbBestandTM3;
  if ( ( rc=CheckSql( fun, stError, "%s", "open CSelVbBestandTM3" ) ) != IS_OK )
    return rc;
  exec sql fetch CSelVbBestandTM3
    into :d->FILIALNR;
  if ( ( rc=CheckSql( fun, stError, "%s", "fetch CSelVbBestandTM3" ) ) != IS_OK )
  {
    exec sql close CSelVbBestandTM3;
    return rc;
  }
  exec sql close CSelVbBestandTM3;

return CheckSql( fun, stError, "%s", "close CSelVbBestandTM" );
}



/******************************************************************************/
/*                                                                            */
/* header  : articlenlevelibttype.cxx                                         */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:15 2022                                         */
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
#include "verbundcheck.h"

/* articlenlevelibttype: Select ***********************************************/

/* articlenlevelibttype::SelList **********************************************/

retClient articlenlevelibttype_SelList(articlenlevelibttypeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "articlenlevelibttype_SelList";
    exec sql begin declare section;
    articlenlevelibttypeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList2 cursor with hold for
                  select ibtbrancharticleconfig.ArticleNo,
                     ibtbrancharticleconfig.BranchNo,
                     ibtassortmenttype.assortmenttypename,
                     ibttype.ibttypename,
                     ibtbrancharticleconfig.ibttypeid,
                     ibtbrancharticleconfig.ibtassortmenttypeid
                from IBTBRANCHARTICLECONFIG, IBTTYPE, IBTASSORTMENTTYPE
                  where ibtbrancharticleconfig.BranchNo	 =	:d->BRANCHNO	 and
                        ibtbrancharticleconfig.ArticleNo	 =	:d->ARTICLENO	 and
                        ibtbrancharticleconfig.ibttypeid	 =	ibttype.ibttypeid and
                        ibtbrancharticleconfig.ibtassortmenttypeid	 =	ibtassortmenttype.ibtassortmenttypeid;
        exec sql open CSelList2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList2;
        return CheckSql( fun, stError, "%s", "close CSelList2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList2 into :d->ARTICLENO,
                     :d->BRANCHNO,
                     :d->ASSORTMENTTYPENAME,
                     :d->IBTTYPENAME,
                     :d->IBTTYPEID,
                     :d->IBTASSORTMENTTYPEID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList2" )) == IS_ERROR )
        return rc;
    return rc;
}



/* articlenlevelibttype: Insert ***********************************************/



/* articlenlevelibttype: Update ***********************************************/



/* articlenlevelibttype: Select ***********************************************/



/* articlenlevelibttype: Other ************************************************/



