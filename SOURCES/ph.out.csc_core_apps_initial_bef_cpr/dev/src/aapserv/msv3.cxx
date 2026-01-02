/******************************************************************************/
/*                                                                            */
/* header  : MSV3CstInfo.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:42 2022                                         */
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
#include "msv3.h"

/* MSV3CstInfo: Select ********************************************************/

/* MSV3CstInfo::SelCstInfo ****************************************************/

retClient Msv3cstinfo_SelCstInfo(msv3cstinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msv3cstinfo_SelCstInfo";
    exec sql begin declare section;
    msv3cstinfoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCstInfo0 cursor with hold for
                  select msv3cstinfo.BranchNo,
                     msv3cstinfo.CustomerNo,
                     msv3cstinfotype.MSV3InfoDescription,
                     msv3cstinfo.MSV3CstInfoValue
                from msv3cstinfo,msv3cstinfotype
                  where MSV3CstInfo.BranchNo	 =	:d->BRANCHNO	 and
                        MSV3CstInfo.CustomerNo	 =	:d->CUSTOMERNO	 and
                        MSV3CstInfo.MSV3CstInfoTypeID	 =	MSV3CstInfoType.MSV3CstInfoTypeID
                        order by MSV3CstInfo.MSV3CstInfoTypeID;
        exec sql open CSelCstInfo0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCstInfo0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCstInfo0;
        return CheckSql( fun, stError, "%s", "close CSelCstInfo0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCstInfo0 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MSV3INFODESCRIPTION,
                     :d->MSV3CSTINFOVALUE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCstInfo0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSV3CstInfo: Insert ********************************************************/



/* MSV3CstInfo: Update ********************************************************/



/* MSV3CstInfo: Select ********************************************************/



/* MSV3CstInfo: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MSV3Einstellungen.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:45 2022                                         */
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
#include "msv3.h"

/* MSV3Einstellungen: Select **************************************************/

/* MSV3Einstellungen::SelAdjustments ******************************************/

retClient Msv3einstellungen_SelAdjustments(msv3einstellungenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msv3einstellungen_SelAdjustments";
    exec sql begin declare section;
    msv3einstellungenS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kundeschalter.skdauftragzusammen,
                     kundeschalter.skdauftragzurueck,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.XMLInfoLevel,
                     kundeschalter.skdnoclosedefvb,
                     kundeschalter.skdnosub
                into :d->SKDAUFTRAGZUSAMMEN,
                     :d->SKDAUFTRAGZURUECK,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->XMLINFOLEVEL,
                     :d->SKDNOCLOSEDEFVB,
                     :d->SKDNOSUB
                from kunde, kundeschalter
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    kundeschalter.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                    kundeschalter.KundenNr	 =	kunde.KundenNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSV3Einstellungen: Insert **************************************************/



/* MSV3Einstellungen: Update **************************************************/



/* MSV3Einstellungen: Select **************************************************/



/* MSV3Einstellungen: Other ***************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MSV3Info.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:47 2022                                         */
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
#include "msv3.h"

/* MSV3Info: Select ***********************************************************/

/* MSV3Info::SelMSV3 **********************************************************/

retClient Msv3info_SelMSV3(msv3infoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msv3info_SelMSV3";
    exec sql begin declare section;
    msv3infoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMSV32 cursor with hold for
                  select kdauftragart.kdauftragart,
NVL(auftragartkd.swmsv3,kdauftragart.sglobal) as msv3vereinbart,
NVL(auftragartkd.orderlabelcount,0) as freiekennungen
                         into :d->KDAUFTRAGART,
:d->MSV3VEREINBART,
:d->FREIEKENNUNGEN
                   from KDAUFTRAGART, KUNDESCHALTER, outer AUFTRAGARTKD
                  where kundeschalter.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR and
                        kundeschalter.KundenNr = :d->KUNDENNR and
                        kdauftragart.kdauftragart in ('NO', 'SO', 'ST', 'VH','RK') and
                        kdauftragart.kdauftragart = auftragartkd.kdauftragart and
                        auftragartkd.vertriebszentrumnr = kundeschalter.vertriebszentrumnr and
                        auftragartkd.kundennr = kundeschalter.kundennr and
                        auftragartkd.kdauftragart = kdauftragart.kdauftragart and
                        kdauftragart.branchno = auftragartkd.vertriebszentrumnr and
                        kdauftragart.branchno = kundeschalter.vertriebszentrumnr
                        order by kdauftragart.kdauftragart;
        exec sql open CSelMSV32;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMSV32" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMSV32;
        return CheckSql( fun, stError, "%s", "close CSelMSV32" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMSV32;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMSV32" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSV3Info: Insert ***********************************************************/



/* MSV3Info: Update ***********************************************************/



/* MSV3Info: Select ***********************************************************/



/* MSV3Info: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MSV3OrderInfo.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:50 2022                                         */
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
#include "msv3.h"

/* MSV3OrderInfo: Select ******************************************************/

/* MSV3OrderInfo::SelMSV3Orders ***********************************************/

retClient Msv3orderinfo_SelMSV3Orders(msv3orderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msv3orderinfo_SelMSV3Orders";
    exec sql begin declare section;
    msv3orderinfoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMSV3Orders3 cursor with hold for
                  select kdauftrag.kdauftragnr
,kdauftrag.anzpos
,kdauftrag.tourid
,kdauftrag.OrderLabel
,OrderPeriod.weekday
,OrderPeriodTime.MainTime
,OrderPeriodTime.ToTime
,OrderPeriod.tourid
,kdauftragposereignis.SendID
,count(*)
,MIN(kdauftragposereignis.datum)
,MIN(kdauftragposereignis.uhrzeit)
,oeorigintypes.origindevice
                         into :d->KDAUFTRAGNR
,:d->ANZPOS
,:d->TOURID
,:d->ORDERLABEL
,:d->WEEKDAY
,:d->MAINTIME
,:d->TOTIME
,:d->BFTOUR
,:d->SENDID
,:d->POSTRANSFERED
,:d->DATUM
,:d->ZEIT_VON
,:d->ORIGINDEVICE
                   from kdauftragposereignis, kdauftrag, kdauftragpos, orderperiodtime, orderperiod, oeorigintypes
                  where kdauftrag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kdauftrag.KundenNr	 =	:d->KUNDENNR	 and
                        kdauftrag.kdauftragnr	 =	kdauftragposereignis.kdauftragnr and
                        kdauftragpos.kdauftragnr	 =	kdauftragposereignis.kdauftragnr and
                        kdauftragpos.posnr	 =	kdauftragposereignis.posnr and
                        kdauftragpos.subgeraettyp	 =	oeorigintypes.origintype and
                        OrderPeriodTime.id	 =	kdauftrag.OrderPeriodID and
                        OrderPeriod.BranchNo	 =	kdauftrag.VertriebszentrumNr and
                        OrderPeriod.CustomerNo	 =	kdauftrag.KundenNr and
                        OrderPeriod.id	 =	OrderPeriodTime.Order_Period_ID and
                        OrderPeriod.id	 >	0
                        group by kdauftrag.kdauftragnr
                        , kdauftrag.tourid
                        , kdauftrag.OrderLabel
                        , OrderPeriod.weekday
                        , OrderPeriodTime.MainTime
                        , OrderPeriodTime.ToTime
                        , OrderPeriod.tourid
                        , kdauftragposereignis.SendID
                        , kdauftrag.anzpos
                        , oeorigintypes.origindevice
                        order by kdauftrag.kdauftragnr
                        ,MIN(kdauftragposereignis.datum)
                        ,MIN(kdauftragposereignis.uhrzeit);
        exec sql open CSelMSV3Orders3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMSV3Orders3" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMSV3Orders3;
        return CheckSql( fun, stError, "%s", "close CSelMSV3Orders3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMSV3Orders3;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMSV3Orders3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSV3OrderInfo: Insert ******************************************************/



/* MSV3OrderInfo: Update ******************************************************/



/* MSV3OrderInfo: Select ******************************************************/



/* MSV3OrderInfo: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MSV3TourInfo.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:53 2022                                         */
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
#include "msv3.h"

/* MSV3TourInfo: Select *******************************************************/

/* MSV3TourInfo::SelBFToday ***************************************************/

retClient Msv3tourinfo_SelBFToday(msv3tourinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msv3tourinfo_SelBFToday";
    exec sql begin declare section;
    msv3tourinfoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    {
    char msg[256] = { 0 };
    d->WEEKDAY = AllgGetWeekDay(AllgGetDate(), msg);
}
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelBFToday4 cursor with hold for
                  select orderperiod.CustomerNo,
                     orderperiod.tourid,
                     orderperiod.BranchNo,
                     orderperiod.weekday,
                     orderperiodtime.ToTime,
                     tourplantag.IstVerbundTour,
                     orderperiodtime.MainTime,
                     tourplantag.IsBTM,
                     tourplantag.IsKK,
                     tourplantag.IsK08,
                     tourplantag.IsK20,
                     tourplantag.ReturnsTour
                from orderperiodtime, orderperiod, tourplantag, tour
                  where OrderPeriod.BranchNo	 =	:d->BRANCHNO	 and
                        OrderPeriod.CustomerNo	 =	:d->CUSTOMERNO	 and
                        OrderPeriodTime.Order_Period_ID	 =	OrderPeriod.id and
                        tourplantag.VertriebszentrumNr	 =	OrderPeriod.BranchNo and
                        tourplantag.KundenNr	 =	OrderPeriod.CustomerNo and
                        tourplantag.tourid	 =	OrderPeriod.tourid and
                        tour.filialnr	 =	tourplantag.VertriebszentrumNr and
                        tour.tourid	 =	tourplantag.tourid and
                        tour.datumkommi	 =	tourplantag.datumkommi and
                        tourplantag.datumkommi	 =	:lDate  and
                        tourplantag.tourinaktiv	 =	'0' and
                        OrderPeriod.weekday	 =	:d->WEEKDAY	
                        order by OrderPeriod.tourid, OrderPeriodTime.MainTime;
        exec sql open CSelBFToday4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelBFToday4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelBFToday4;
        return CheckSql( fun, stError, "%s", "close CSelBFToday4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelBFToday4 into :d->CUSTOMERNO,
                     :d->TOURID,
                     :d->BRANCHNO,
                     :d->WEEKDAY,
                     :d->TOTIME,
                     :d->ISTVERBUNDTOUR,
                     :d->MAINTIME,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20,
                     :d->RETURNSTOUR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelBFToday4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSV3TourInfo: Insert *******************************************************/



/* MSV3TourInfo: Update *******************************************************/



/* MSV3TourInfo: Select *******************************************************/



/* MSV3TourInfo: Other ********************************************************/



