/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderExist.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:49:57 2022                                         */
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
#include "callplanday.h"

/* CheckOrderExist: Select ****************************************************/



/* CheckOrderExist: Insert ****************************************************/



/* CheckOrderExist: Update ****************************************************/



/* CheckOrderExist: Select ****************************************************/



/* CheckOrderExist: Other *****************************************************/

/* CheckOrderExist::SelAuftrag ************************************************/

retClient Checkorderexist_SelAuftrag(checkorderexistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "CheckOrderExist_SelAuftrag";
    exec sql begin declare section;
    checkorderexistS *d;
    int iID = 0; /* indicator */
	long ldate;
    exec sql end declare section;

    d = a;

    /* Zeit auf kdauftragereignis mit Millisekunden */
    d->TM_TIME = ppGGetTime()*1000 - d->TM_TIME*100000;
    ldate = ppGGetDate();

    exec sql select MAX(kdauftrag.kdauftragnr) into :d->KDAUFTRAGNR
       indicator :iID
       from kdauftrag,kdauftragereignis where
         kdauftrag.vertriebszentrumnr = :d->VERTRIEBSZENTRUMNR and
         kdauftrag.kundennr = :d->KUNDENNR and
         kdauftrag.anzposdafue >= :d->KDAUFTRAGNR and
         kdauftrag.kdauftragstat[10] = '0' and
         kdauftrag.batchschreiben = 0 and
         kdauftragereignis.kdauftragnr = kdauftrag.kdauftragnr and
         kdauftragereignis.datum = :ldate and
         kdauftragereignis.zeit > :d->TM_TIME and
         ( kdauftragereignis.ereignisart = 3 or
         kdauftragereignis.ereignisart = 4);
    if ( (rc=CheckSql( fun, stError, "%s", "select kdauftagnr" )) != IS_OK )
       return rc; 
    else if ( iID < 0 )
    {
       d->KDAUFTRAGNR = 0;
       return 0;
    } 
    return 0;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCallParamterDriver.cxx                                          */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:02 2022                                         */
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
#include "callplanday.h"

/* MCallParamterDriver: Select ************************************************/

/* MCallParamterDriver::SelParameter ******************************************/

retClient Mcallparamterdriver_SelParameter(mcallparamterdriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamterdriver_SelParameter";
    exec sql begin declare section;
    mcallparamterdriverS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select anrufparameter.VertriebszentrumNr,
                     anrufparameter.RufzeitVerschieben,
                     anrufparameter.AnzRufwiederholung,
                     anrufparameter.RufAbweichungPH,
                     anrufparameter.RufAbweichungDP,
                     anrufparameter.RufAbweichungDS,
                     anrufparameter.ZeitFensterAuftrag,
                     anrufparameter.ZeitAnzPosAuftrag,
                     anrufparameter.tm_date,
                     anrufparameter.tm_time,
                     anrufparameter.loginId,
                     anrufparameter.changeId,
                     anrufparameter.UmkRufwiederholung,
                     anrufparameter.KabRufwiederholung,
                     anrufparameter.CallplanStartStop,
                     anrufparameter.StopStartZeit
                into :d->VERTRIEBSZENTRUMNR,
                     :d->RUFZEITVERSCHIEBEN,
                     :d->ANZRUFWIEDERHOLUNG,
                     :d->RUFABWEICHUNGPH,
                     :d->RUFABWEICHUNGDP,
                     :d->RUFABWEICHUNGDS,
                     :d->ZEITFENSTERAUFTRAG,
                     :d->ZEITANZPOSAUFTRAG,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->UMKRUFWIEDERHOLUNG,
                     :d->KABRUFWIEDERHOLUNG,
                     :d->CALLPLANSTARTSTOP,
                     :d->STOPSTARTZEIT
                from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCallParamterDriver: Insert ************************************************/



/* MCallParamterDriver: Update ************************************************/

/* MCallParamterDriver::UpdTime ***********************************************/

retClient Mcallparamterdriver_UpdTime(mcallparamterdriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallparamterdriver_UpdTime";
    exec sql begin declare section;
    mcallparamterdriverS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdTime1 cursor with hold for
              select VertriebszentrumNr,
                     RufzeitVerschieben,
                     AnzRufwiederholung,
                     RufAbweichungPH,
                     RufAbweichungDP,
                     RufAbweichungDS,
                     ZeitFensterAuftrag,
                     ZeitAnzPosAuftrag,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     UmkRufwiederholung,
                     KabRufwiederholung,
                     CallplanStartStop,
                     StopStartZeit
               from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR
              for update;
    exec sql open CUpdTime1;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdTime1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    exec sql insert into MAnrufParameter select * 
               from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: MAnrufParameter" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    strcpy( d->CHANGEID, "U" );
    /*reflection activated */

    for(;;)
    {
        exec sql fetch CUpdTime1;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdTime1" ) ) != IS_OK )
            break;
        exec sql update anrufparameter set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     RufzeitVerschieben = :d->RUFZEITVERSCHIEBEN,
                     AnzRufwiederholung = :d->ANZRUFWIEDERHOLUNG,
                     RufAbweichungPH = :d->RUFABWEICHUNGPH,
                     RufAbweichungDP = :d->RUFABWEICHUNGDP,
                     RufAbweichungDS = :d->RUFABWEICHUNGDS,
                     ZeitFensterAuftrag = :d->ZEITFENSTERAUFTRAG,
                     ZeitAnzPosAuftrag = :d->ZEITANZPOSAUFTRAG,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     UmkRufwiederholung = :d->UMKRUFWIEDERHOLUNG,
                     KabRufwiederholung = :d->KABRUFWIEDERHOLUNG,
                     CallplanStartStop = :d->CALLPLANSTARTSTOP,
                     StopStartZeit = :d->STOPSTARTZEIT where current of CUpdTime1;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdTime1" ) ) != IS_OK )
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



/* MCallParamterDriver: Select ************************************************/



/* MCallParamterDriver: Other *************************************************/

/* MCallParamterDriver::SetCallsToFinish **************************************/

retClient Mcallparamterdriver_SetCallsToFinish(mcallparamterdriverS *a, tError *stError, bool bIsTrans)
{
retClient Mcustomercallplandaydriver_UpdCustomerCallplan(mcustomercallplandaydriverS *d, tError *stError, bool bTrans);
    retClient rc = IS_OK;
    int iCount;
    char *fun = "McallparameterDriver_SetCallsToFinish";
    exec sql begin declare section;
    char szBuf[2048];
    mcustomercallplandaydriverS xMemory, *pCallplanDay;
    mcallparamterdriverS *d = a;
    long lDate = ppGGetDate();
    exec sql end declare section;
   
    if ( bIsTrans );
    pCallplanDay = &xMemory;

    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERCALLPLANDAYDRIVER_PLISTE ); 
    strcat( szBuf, " from KUNDEANRUFPLANTAG, KUNDE, KUNDEANRUFPLANPROT " );
    strcat( szBuf, "where KundeAnrufplanTag.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.datum=? and " );
    strcat( szBuf, "KundeAnrufplanTag.rufzeit < ? and " );	
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=3 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=7 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=8 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=9 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=10 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=11 and " );
/* phonetische Rufe NICHT rufen!!!! */
    strcat( szBuf, "KundeAnrufplanTag.Rufeinstellung != \"0\" and " );
    strcat( szBuf, "Kunde.KundenNr=KundeAnrufplanTag.KundenNr and " );
    strcat( szBuf, "Kunde.VertriebszentrumNr=KundeAnrufplanTag.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.VertriebszentrumNr=KundeAnrufplanprot.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=KundeAnrufplanprot.KundenNr and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=KundeAnrufplanprot.UrRufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Rufzeit=KundeAnrufplanprot.Rufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Datum=KundeAnrufplanprot.Datum and " );
    strcat( szBuf, "KundeAnrufplanTag.Anrufstatus=KundeAnrufplanprot.Anrufstatus and " );
    strcat( szBuf, "KundeAnrufplanprot.uhrzeit=(" );
    strcat( szBuf, "select max(uhrzeit) from KundeAnrufplanprot where " );
    strcat( szBuf, "KundeAnrufplanTag.VertriebszentrumNr=KundeAnrufplanprot.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=KundeAnrufplanprot.KundenNr and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=KundeAnrufplanprot.UrRufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Rufzeit=KundeAnrufplanprot.Rufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Datum=KundeAnrufplanprot.Datum and " );
    strcat( szBuf, "KundeAnrufplanTag.Anrufstatus=KundeAnrufplanprot.Anrufstatus " );
    strcat( szBuf, ") " );
   
    exec sql prepare p_SelFDataF from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelFDataF" ) ) != IS_OK )
        return rc;

    exec sql declare CSelFDataF cursor with hold for p_SelFDataF;
    exec sql open CSelFDataF using :d->VERTRIEBSZENTRUMNR,
                                   :lDate,
                                   :d->STOPSTARTZEIT;
    if ( ( rc=CheckSql( fun, stError, "%s", "open p_SelFDataF" ) ) != IS_OK )
        return rc;
    else if ( ( rc = Begin( fun, stError ) ) != IS_OK )
        return rc;

    exec sql free p_SelFDataF;
    for(iCount=0;;iCount++)
    {
       exec sql fetch CSelFDataF into MCUSTOMERCALLPLANDAYDRIVER_ZEIGERSEL(pCallplanDay);
       if ( (rc=CheckSql( fun, stError, "%s", "fetch CSelFDataF" )) == IS_ERROR )
       {
          exec sql rollback work;  
          return rc;
       }
       else if ( rc == IS_NOTFOUND )
          break;

       pCallplanDay->ANRUFSTATUS = 9; /*ready*/
       pCallplanDay->POOLNR = d->VERTRIEBSZENTRUMNR;  /*:d->FILIALNR*/
       pCallplanDay->MODEMPOOLNR = 0;    /*:d->MODEMNR*/
       pCallplanDay->RUFSTEUERUNG = 20;  /*:call finsished by plan*/
       strcpy(pCallplanDay->TELNR, "0");
       rc = (retClient)Mcustomercallplandaydriver_UpdCustomerCallplan(pCallplanDay, stError, FALSE);
       if ( rc != IS_OK )
       {
          exec sql rollback work;
          return rc;
       }
       else if ( iCount % 10 == 0 )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
          else if ( ( rc = Begin( fun, stError ) ) != IS_OK )
             return rc;
       }
    }

    strcpy(d->CALLPLANSTARTSTOP, "0");
    d->STOPSTARTZEIT=0;
    if ( (rc=(retClient)Mcallparamterdriver_UpdTime(d, stError, FALSE)) != IS_OK )
    { 
       exec sql rollback work;
       return rc;
    } 

    d->LOGINID = iCount;
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlanDay.cxx                                         */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:13 2022                                         */
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
#include "callplanday.h"

/* MCustomerCallPlanDay: Select ***********************************************/

/* MCustomerCallPlanDay::SelCallPlanDay ***************************************/

retClient Mcustomercallplanday_SelCallPlanDay(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_SelCallPlanDay";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.idfnr,
                     kunde.nameapo,
                     kunde.ort,
                     kunde.telnr,
                     kunde.telkurzwahl,
                     kunde.kzkdklasse,
                     kundeanrufplantag.VertriebszentrumNr,
                     kundeanrufplantag.KundenNr,
                     kundeanrufplantag.datum,
                     kundeanrufplantag.UrRufzeit,
                     kundeanrufplantag.rufzeit,
                     kundeanrufplantag.UmkStatus,
                     kundeanrufplantag.AnrufStatus,
                     kundeanrufplantag.AnrufZaehler,
                     kundeanrufplantag.tagnr,
                     kundeanrufplantag.tourid,
                     kundeanrufplantag.STourDefinitiv,
                     kundeanrufplantag.RufProtokoll,
                     kundeanrufplantag.RufSteuerung,
                     kundeanrufplantag.poolnr,
                     kundeanrufplantag.ModemPoolNr,
                     kundeanrufplantag.RufEinstellung,
                     kundeanrufplantag.AnrufTyp,
                     kundeanrufplantag.skdanrufgenerell
                into :d->IDFNR,
                     :d->NAMEAPO,
                     :d->ORT,
                     :d->TELNR,
                     :d->TELKURZWAHL,
                     :d->KZKDKLASSE,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->URRUFZEIT,
                     :d->RUFZEIT,
                     :d->UMKSTATUS,
                     :d->ANRUFSTATUS,
                     :d->ANRUFZAEHLER,
                     :d->TAGNR,
                     :d->TOURID,
                     :d->STOURDEFINITIV,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->SKDANRUFGENERELL
                from KUNDEANRUFPLANTAG, KUNDE
              where KundeAnrufplanTag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeAnrufplanTag.KundenNr	 =	:d->KUNDENNR	and
                    KundeAnrufplanTag.UrRufzeit	 =	:d->URRUFZEIT	and
                    KundeAnrufplanTag.datum	 =	:d->DATUM and
                    kunde.VertriebszentrumNr	 =	KundeAnrufplanTag.VertriebszentrumNr and
                    kunde.KundenNr	 =	KundeAnrufplanTag.KundenNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerCallPlanDay::SelListFuture ****************************************/

retClient Mcustomercallplanday_SelListFuture(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_SelListFuture";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListFuture3 cursor with hold for
                  select kunde.idfnr,
                     kunde.nameapo,
                     kunde.ort,
                     kunde.telnr,
                     kunde.telkurzwahl,
                     kunde.kzkdklasse,
                     kundeanrufplantag.VertriebszentrumNr,
                     kundeanrufplantag.KundenNr,
                     kundeanrufplantag.datum,
                     kundeanrufplantag.UrRufzeit,
                     kundeanrufplantag.rufzeit,
                     kundeanrufplantag.UmkStatus,
                     kundeanrufplantag.AnrufStatus,
                     kundeanrufplantag.AnrufZaehler,
                     kundeanrufplantag.tagnr,
                     kundeanrufplantag.tourid,
                     kundeanrufplantag.STourDefinitiv,
                     kundeanrufplantag.RufProtokoll,
                     kundeanrufplantag.RufSteuerung,
                     kundeanrufplantag.poolnr,
                     kundeanrufplantag.ModemPoolNr,
                     kundeanrufplantag.RufEinstellung,
                     kundeanrufplantag.AnrufTyp,
                     kundeanrufplantag.skdanrufgenerell
                from KUNDE, KUNDEANRUFPLANTAG
                  where kunde.VertriebszentrumNr =KundeAnrufplanTag.VertriebszentrumNr and
                        kunde.KundenNr =KundeAnrufplanTag.KundenNr and
                        KundeAnrufplanTag.datum =:d->DATUM and
                        KundeAnrufplanTag.VertriebszentrumNr in (
                         select RegionArten.RegionTeilNr from RegionArten 
                         where RegionArten.RegionNr=:d->VERTRIEBSZENTRUMNR and 
                                    RegionArten.RegionenTyp=3 ) and  
                        (KundeAnrufplanTag.AnrufStatus = 7 or
                        KundeAnrufplanTag.AnrufStatus = 8 )
                        order by KundeAnrufplanTag.UrRufzeit, KundeAnrufplanTag.rufzeit, KundeAnrufplanTag.VertriebszentrumNr, KundeAnrufplanTag.KundenNr;
        exec sql open CSelListFuture3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListFuture3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListFuture3;
        return CheckSql( fun, stError, "%s", "close CSelListFuture3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListFuture3 into :d->IDFNR,
                     :d->NAMEAPO,
                     :d->ORT,
                     :d->TELNR,
                     :d->TELKURZWAHL,
                     :d->KZKDKLASSE,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->URRUFZEIT,
                     :d->RUFZEIT,
                     :d->UMKSTATUS,
                     :d->ANRUFSTATUS,
                     :d->ANRUFZAEHLER,
                     :d->TAGNR,
                     :d->TOURID,
                     :d->STOURDEFINITIV,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->SKDANRUFGENERELL;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListFuture3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerCallPlanDay: Insert ***********************************************/



/* MCustomerCallPlanDay: Update ***********************************************/



/* MCustomerCallPlanDay: Select ***********************************************/



/* MCustomerCallPlanDay: Other ************************************************/

/* MCustomerCallPlanDay::EndBrowse ********************************************/

retClient Mcustomercallplanday_EndBrowse(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_EndBrowse";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql free p_SelDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelDataX" ) ) != IS_OK )
        return rc;
    exec sql free p_InsDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_InsDataX" ) ) != IS_OK )
       return rc;
    exec sql free p_UpdDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_UpdDataX" ) ) != IS_OK )
       return rc;
    exec sql free p_InsDataProtX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_InsDataProtX" ) ) != IS_OK )
       return rc;
    exec sql free p_SelTourIDX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelTourIDX" ) ) != IS_OK )
       return rc;
    exec sql free p_SelRushTourIDX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelRushTourIDX" ) ) != IS_OK )
       return rc;
    return rc;
}

/* MCustomerCallPlanDay::Insert ***********************************************/

retClient Mcustomercallplanday_Insert(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_Insert";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    long lTime;
    short sBranchNo;
    short sEvent;
    long  lModemNo;
    long  lUid;
    long  lDateFirst;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql execute p_InsDataX using :d->VERTRIEBSZENTRUMNR, 
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->URRUFZEIT,
                     :d->RUFZEIT,
                     :d->UMKSTATUS,
                     :d->ANRUFSTATUS,
                     :d->ANRUFZAEHLER,
                     :d->TAGNR,
                     :d->TOURID,
                     :d->STOURDEFINITIV,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->SKDANRUFGENERELL;
 
    if ( ( rc = CheckSql( fun, stError,  "%s", "execute p_InsDataX" ) ) != IS_OK )
    {
      if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
      {
         exec sql rollback work;
         return rc;
      }
      return rc;
    }

/*
0-angelegt
1-verschoben
2-gelöscht
3-heute kein auftrag
4-übertragen
*/

    sBranchNo = d->POOLNR;         /*:d->FILIALNR*/
    lModemNo  = d->MODEMPOOLNR;    /*:d->MODEMNR*/
    sEvent    = (short)d->IDFNR;   /*:d->EREIGNIS*/
    lUid      = atol(d->TELNR);
    lTime = ppGGetUniqueTime(200);
    lDateFirst = ppGGetDate();
    exec sql execute p_InsDataProtX using :d->VERTRIEBSZENTRUMNR,
                                          :d->KUNDENNR,
                                          :d->DATUM,
                                          :d->URRUFZEIT,
                                          :sEvent,
                                          :d->RUFZEIT,
                                          :d->UMKSTATUS,
                                          :d->ANRUFSTATUS,
                               		  :sBranchNo,
                 		          :lModemNo,
					  :lTime,
                                          :lUid,
                                          :lDateFirst; 
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_InsDataProtX" ) ) != IS_OK )
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

/* MCustomerCallPlanDay::SelList **********************************************/

retClient Mcustomercallplanday_SelList(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_SelList";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    int iID = 0; /* indicator */
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
       exec sql open CSelDataX using :d->VERTRIEBSZENTRUMNR, :d->DATUM;
       if ( ( rc=CheckSql( fun, stError, "%s", "open CSelDataX" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelDataX;
      return CheckSql( fun, stError, "%s", "close CSelDataX" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelDataX into MCUSTOMERCALLPLANDAY_ZEIGERSEL(d);
    if ( (rc=CheckSql( fun, stError, "%s", "fetch CSelDataX" )) != IS_OK )
       return rc; 
    else if ( d->TOURID[0] != ' ' )
       return rc; 
/* nur lesen wenn keine TOURID vorhanden */
    if ( d->RUFSTEUERUNG != 20 )
    {
       exec sql execute p_SelTourIDX into :d->TOURID indicator :iID 
                                                     using :d->VERTRIEBSZENTRUMNR,
                                                           :d->KUNDENNR,
                                                           :d->URRUFZEIT,
                                                           :d->DATUM;
       rc = CheckSql( fun, stError, "%s", "execute p_SelTourIDX" );
    }
    else
    {
       exec sql execute p_SelRushTourIDX into :d->TOURID indicator :iID
                                                         using :d->VERTRIEBSZENTRUMNR,
                                                               :d->KUNDENNR,
                                                               :d->URRUFZEIT,
                                                               :d->DATUM;
       rc = CheckSql( fun, stError, "%s", "execute p_SelRushTourIDX" );
    }

    if ( iID < 0 )
    {
       strcpy(d->TOURID, " " );
       /*WriteLogInfo("Keine Touren geladen", -1, -1);*/
    }

    return rc;
}

/* MCustomerCallPlanDay::SelListHist ******************************************/

retClient Mcustomercallplanday_SelListHist(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_SelListHist";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    long KundenNrVon;
    long KundenNrBis;
    long RufzeitVon;
    long RufzeitBis;
    short AnrufStatusVon;
    short AnrufStatusBis;
    short Event = a->UMKSTATUS;
    short State = 9;
    exec sql end declare section;

    d = a;

    if ( a->KUNDENNR == 0 ) 
    {
       KundenNrVon = 0;
       KundenNrBis  = 999999999;
    }
    else
    { 
       KundenNrVon = a->KUNDENNR;
       KundenNrBis  = a->KUNDENNR;
    }

    if ( a->RUFZEIT == 0 )
    {
       RufzeitVon = 0;
       RufzeitBis = 999999;
    }
    else
    {
       RufzeitVon = a->RUFZEIT;
       RufzeitBis = 999999;
    }

    if ( a->ANRUFSTATUS == 0 )
    {
       State = 0;
       AnrufStatusVon = 0;
       AnrufStatusBis = 32000;
    }
    else
    {
       /*State = a->ANRUFSTATUS;*/
       AnrufStatusVon = a->ANRUFSTATUS;
       AnrufStatusBis = a->ANRUFSTATUS;
    }

    if ( a->FETCH_REL == SET_OPEN )
    {
      ppGMakeToLike( d->TOURID, L_MCUSTOMERCALLPLANDAY_TOURID );
      if ( d->DATUM != ppGGetDate() )
         State = 0;

      exec sql declare CSelListHist3 cursor with hold for
                select kunde.idfnr,
                     kunde.nameapo,
                     kunde.ort,
                     kunde.telnr,
                     kunde.telkurzwahl,
                     kunde.kzkdklasse,
                     kundeanrufplantag.VertriebszentrumNr,
                     kundeanrufplantag.KundenNr,
                     kundeanrufplantag.datum,
                     kundeanrufplantag.UrRufzeit,
                     kundeanrufplantag.rufzeit,
                     kundeanrufplantag.UmkStatus,
                     kundeanrufplantag.AnrufStatus,
                     kundeanrufplantag.AnrufZaehler,
                     kundeanrufplantag.tagnr,
                     kundeanrufplantag.tourid,
                     kundeanrufplantag.STourDefinitiv,
                     kundeanrufplantag.RufProtokoll,
                     kundeanrufplantag.RufSteuerung,
                     kundeanrufplantag.poolnr,
                     kundeanrufplantag.ModemPoolNr,
                     kundeanrufplantag.RufEinstellung,
                     kundeanrufplantag.AnrufTyp,
                     kundeanrufplantag.SkdAnrufGenerell
                from  KUNDEANRUFPLANTAG,KUNDEANRUFPLANPROT,KUNDE
                where  KundeAnrufplanTag.Rufeinstellung != "0" and
                       KundeAnrufplanTag.VertriebszentrumNr=kunde.VertriebszentrumNr and
                       KundeAnrufplanTag.KundenNr=kunde.KundenNr and
                       KundeAnrufplanTag.AnrufStatus>= :State and 
                       KundeAnrufplanTag.tourid like  :d->TOURID and
                       KundeAnrufplanTag.rufzeit >= :RufzeitVon and
                       KundeAnrufplanTag.rufzeit <= :RufzeitBis and
                       KundeAnrufplanTag.AnrufStatus >= :AnrufStatusVon and
                       KundeAnrufplanTag.AnrufStatus <=:AnrufStatusBis and
                       KundeAnrufplanTag.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR and
                       KundeAnrufplanTag.KundenNr >= :KundenNrVon and
                       KundeAnrufplanTag.KundenNr <= :KundenNrBis and
                       KundeAnrufplanTag.Datum = :d->DATUM and 
                       KundeAnrufplanProt.Ereignis = :Event and
                       KundeAnrufplanProt.VertriebszentrumNr=KundeAnrufplanTag.VertriebszentrumNr and
                       KundeAnrufplanProt.KundenNr=KundeAnrufplanTag.KundenNr and
                       KundeAnrufplanProt.Datum=KundeAnrufplanTag.Datum and
                       KundeAnrufplanProt.Urrufzeit=KundeAnrufplanTag.Urrufzeit and
                       KundeAnrufplanTag.VertriebszentrumNr in (
                             select RegionArten.RegionTeilNr from RegionArten 
                              where RegionArten.RegionNr=:d->VERTRIEBSZENTRUMNR and 
                                    RegionArten.RegionenTyp=3 ) 
                       order by KundeAnrufplanTag.rufzeit,KundeAnrufplanTag.RufSteuerung,kunde.nameapo; 

      exec sql open CSelListHist3;
      if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHist3" ) ) != IS_OK )
        return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelListHist3;
      return CheckSql( fun, stError, "%s", "close CSelListHist3" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelListHist3 into :d->IDFNR,
                     :d->NAMEAPO,
                     :d->ORT, 
                     :d->TELNR,
                     :d->TELKURZWAHL,
                     :d->KZKDKLASSE,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->URRUFZEIT,
                     :d->RUFZEIT,
                     :d->UMKSTATUS,
                     :d->ANRUFSTATUS,
                     :d->ANRUFZAEHLER,
                     :d->TAGNR,
                     :d->TOURID,
                     :d->STOURDEFINITIV,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->SKDANRUFGENERELL;
    return CheckSql( fun, stError, "%s", "fetch CSelListHist3" );
}

/* MCustomerCallPlanDay::SetCustomerCallFree **********************************/

retClient Mcustomercallplanday_SetCustomerCallFree(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient Mcustomercallplanday_UpdCustomerCallPlanDay(mcustomercallplandayS *a, tError *stError, bool bIsTrans);

    retClient rc = IS_OK;
    bool bUpdate = TRUE;
    char *fun = "Mcustomercallplanday_SetCustomerCallFree";
    exec sql begin declare section;
    mcustomercallplandayS *d = a;
    char szGeraetID[L_MDEVICEPLANCHECK_GERAETEID + 1];
    exec sql end declare section;

    exec sql declare cxCursProt cursor for 
             select kundeanrufplanprot.geraeteid
               from kundeanrufplanprot
               where kundeanrufplanprot.vertriebszentrumnr = :d->VERTRIEBSZENTRUMNR and
                     kundeanrufplanprot.kundennr = :d->KUNDENNR and
                     kundeanrufplanprot.datum = :d->DATUM and
                     kundeanrufplanprot.urrufzeit = :d->URRUFZEIT and
                     kundeanrufplanprot.anrufstatus = 3;
    exec sql open cxCursProt;
    if ( ( rc=CheckSql( fun, stError, "%s", "open cxCursProt" ) ) != IS_OK )
       return rc;

    exec sql fetch cxCursProt into :szGeraetID;
    if ( ( rc=CheckSql( fun, stError, "%s", "fetch cxCursProt" ) ) == IS_ERROR )
    {       
       return rc;
    }
    else if ( rc == IS_NOTFOUND )
    {
       bUpdate = FALSE;
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }

    if ( bUpdate )
    {
       exec sql update modemanrufplan set sequenznr = 0
                 where geraeteid = :szGeraetID and 
                       vertriebszentrumnr = :d->VERTRIEBSZENTRUMNR and
                       kundennr = :d->KUNDENNR;
      if ( ( rc=CheckSql( fun, stError, "%s", "update modemanrufplan" ) ) != IS_OK )
      {
         Rollback( fun, stError );
         return rc;
      }
    }

    if ( (rc=(retClient)Mcustomercallplanday_UpdCustomerCallPlanDay(d, stError, FALSE)) != IS_OK )
    {
       Rollback( fun, stError );
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MCustomerCallPlanDay::StartBrowse ******************************************/

retClient Mcustomercallplanday_StartBrowse(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
     retClient rc = IS_OK;
    char *fun = "Mcustomercallplanday_StartBrowse";
    exec sql begin declare section;
    char szBuf[2048];
    exec sql end declare section;

    if ( a || bIsTrans ); /*only because preprozessor*/

    /* sequenz scan */
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERCALLPLANDAY_PLISTE ); 
    strcat( szBuf, " from KUNDEANRUFPLANTAG, KUNDE " );
    strcat( szBuf, "where KundeAnrufplanTag.VertriebszentrumNr=kunde.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=kunde.KundenNr and " );
    strcat( szBuf, "KundeAnrufplanTag.VertriebszentrumNr in (" );
    strcat( szBuf, "select RegionArten.RegionTeilNr from RegionArten " );
    strcat( szBuf, "where RegionArten.RegionNr=? and " );
    strcat( szBuf, "RegionArten.RegionenTyp=3 ) and " ); 
    strcat( szBuf, "KundeAnrufplanTag.datum=? and " );	
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=7 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=8 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=9 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=10 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=11 and " );
/* phnetische anrufe werde z.Zt. nicht geladen!!! */
    strcat( szBuf, "KundeAnrufplanTag.Rufeinstellung != \"0\" " ); 
    strcat( szBuf, "order by KundeAnrufplanTag.rufzeit,KundeAnrufplanTag.RufSteuerung,kunde.nameapo ");
    exec sql prepare p_SelDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelDataX" ) ) != IS_OK )
        return rc;
    exec sql declare CSelDataX cursor with hold for p_SelDataX;
 
    /* insert */
    strcpy( szBuf, "insert into kundeanrufplantag ( " );
    strcat( szBuf, "kundeanrufplantag.VertriebszentrumNr, " );
    strcat( szBuf, "kundeanrufplantag.KundenNr, " );
    strcat( szBuf, "kundeanrufplantag.datum, " );
    strcat( szBuf, "kundeanrufplantag.UrRufzeit, " );
    strcat( szBuf, "kundeanrufplantag.rufzeit, " );
    strcat( szBuf, "kundeanrufplantag.UmkStatus, " );
    strcat( szBuf, "kundeanrufplantag.AnrufStatus, " );
    strcat( szBuf, "kundeanrufplantag.AnrufZaehler, " );
    strcat( szBuf, "kundeanrufplantag.tagnr, " );
    strcat( szBuf, "kundeanrufplantag.tourid, " );
    strcat( szBuf, "kundeanrufplantag.STourDefinitiv, " );
    strcat( szBuf, "kundeanrufplantag.RufProtokoll, " );
    strcat( szBuf, "kundeanrufplantag.RufSteuerung, " );
    strcat( szBuf, "kundeanrufplantag.PoolNr, " );
    strcat( szBuf, "kundeanrufplantag.ModemPoolNr, " );
    strcat( szBuf, "kundeanrufplantag.RufEinstellung, " );
    strcat( szBuf, "kundeanrufplantag.SkdAnrufGenerell) " );
    strcat( szBuf, "values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?) " );
    exec sql prepare p_InsDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_InsDataX" ) ) != IS_OK )
        return rc;

    /* update */
    strcpy( szBuf, "update kundeanrufplantag set kundeanrufplantag.rufzeit=?," );
    strcat( szBuf, "kundeanrufplantag.UmkStatus=?," );
    strcat( szBuf, "kundeanrufplantag.AnrufStatus=?," );
    strcat( szBuf, "kundeanrufplantag.AnrufZaehler=?," );
    strcat( szBuf, "kundeanrufplantag.tagnr=?," );
    strcat( szBuf, "kundeanrufplantag.tourid=?," );
    strcat( szBuf, "kundeanrufplantag.STourDefinitiv=?, " );
    strcat( szBuf, "kundeanrufplantag.RufProtokoll=?, " );
    strcat( szBuf, "kundeanrufplantag.RufSteuerung=?, " );
    strcat( szBuf, "kundeanrufplantag.PoolNr=?, " );
    strcat( szBuf, "kundeanrufplantag.ModemPoolNr=?, " );
    strcat( szBuf, "kundeanrufplantag.RufEinstellung=?, " );
    strcat( szBuf, "kundeanrufplantag.SkdAnrufGenerell=? " );
    strcat( szBuf, "where KundeAnrufplanTag.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=? and " );
    strcat( szBuf, "KundeAnrufplanTag.datum=? " );
    exec sql prepare p_UpdDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_UpdDataX" ) ) != IS_OK )
        return rc;

     /* update -> insert into kundeanrufplanprot*/
    strcpy( szBuf, "insert into kundeanrufplanprot ( " );
    strcat( szBuf, "kundeanrufplanprot.VertriebszentrumNr," );
    strcat( szBuf, "kundeanrufplanprot.KundenNr," );
    strcat( szBuf, "kundeanrufplanprot.datum," );
    strcat( szBuf, "kundeanrufplanprot.UrRufzeit," );
    strcat( szBuf, "kundeanrufplanprot.Ereignis," );
    strcat( szBuf, "kundeanrufplanprot.rufzeit," );
    strcat( szBuf, "kundeanrufplanprot.UmkStatus," );
    strcat( szBuf, "kundeanrufplanprot.AnrufStatus," );
    strcat( szBuf, "kundeanrufplanprot.filialnr," );
    strcat( szBuf, "kundeanrufplanprot.ModemNr," );
    strcat( szBuf, "kundeanrufplanprot.uhrzeit, " );
    strcat( szBuf, "kundeanrufplanprot.uid, " );
    strcat( szBuf, "kundeanrufplanprot.DatumAnlage) " );
    strcat( szBuf, "values (?,?,?,?,?,?,?,?,?,?,?,?,?) " );
    exec sql prepare p_InsDataProtX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_InsDataProtX" ) ) != IS_OK )
        return rc;

    /* unique tourid scan; Call is not a rushorder! */
    strcpy( szBuf, "select min (tourplantag.tourid) " );
    strcat( szBuf, "from tourplantag,tour, paraauftragbearb " );
    strcat( szBuf, "where tourplantag.vertriebszentrumnr=? and " );
    strcat( szBuf, "paraauftragbearb.filialnr=tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.kundennr=? and " );
    strcat( szBuf, "tourplantag.tourid[1,4]>? + paraauftragbearb.durchlaufnormal and " );
    strcat( szBuf, "tourplantag.datumkommi = ? and " );
    strcat( szBuf, "tourplantag.tourid = tour.tourid and " );
    strcat( szBuf, "tourplantag.tourinaktiv = '0' and " );
    strcat( szBuf, "tour.filialnr = tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.datumkommi = tour.datumkommi " );
    exec sql prepare p_SelTourIDX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", " p_SelTourIDX" ) ) != IS_OK )
        return rc;

    /* unique tourid scan; Call is a rushorder! */
    strcpy( szBuf, "select min (tourplantag.tourid) " );
    strcat( szBuf, "from tourplantag,tour, paraauftragbearb " );
    strcat( szBuf, "where tourplantag.vertriebszentrumnr=? and " );
    strcat( szBuf, "paraauftragbearb.filialnr=tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.kundennr=? and " );
    strcat( szBuf, "tourplantag.tourid[1,4]>? + paraauftragbearb.durchlaufeilbote and " );
    strcat( szBuf, "tourplantag.datumkommi = ? and " );
    strcat( szBuf, "tourplantag.tourid = tour.tourid and " );
    strcat( szBuf, "tourplantag.tourinaktiv = '0' and " );
    strcat( szBuf, "tour.filialnr = tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.datumkommi = tour.datumkommi " );
    exec sql prepare p_SelRushTourIDX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", " p_SelRushTourIDX" ) ) != IS_OK )
        return rc;
    return rc;
}

/* MCustomerCallPlanDay::UpdCustomerCallPlanDay *******************************/

retClient Mcustomercallplanday_UpdCustomerCallPlanDay(mcustomercallplandayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = FALSE;
    char *fun = "Mcustomercallplanday_UpdCustomerCallPlanDay";
    exec sql begin declare section;
    mcustomercallplandayS *d;
    long lTime;
    short sBranchNo;
    short sEvent;
    long  lModemNo;
    long  lUid;
    long  lDateFirst;
    exec sql end declare section;

    d = a;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       bInTrans = TRUE;
    }
 
    exec sql execute p_UpdDataX using :d->RUFZEIT,
  				  :d->UMKSTATUS,
				  :d->ANRUFSTATUS,
	        		  :d->ANRUFZAEHLER,
				  :d->TAGNR,
		                  :d->TOURID,
			          :d->STOURDEFINITIV,
                                  :d->RUFPROTOKOLL,
                                  :d->RUFSTEUERUNG,
                                  :d->POOLNR,
                                  :d->MODEMPOOLNR,
                                  :d->RUFEINSTELLUNG,
                                  :d->SKDANRUFGENERELL,
         			  :d->VERTRIEBSZENTRUMNR,
				  :d->KUNDENNR,
				  :d->URRUFZEIT,
				  :d->DATUM;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_UpdDataX" ) ) != IS_OK )
       return rc;
/*
0-angelegt
1-verschoben
2-gelöscht
3-heute kein auftrag
4-übertragen
*/

    sBranchNo = d->POOLNR;         /*:d->FILIALNR*/
    lModemNo  = d->MODEMPOOLNR;    /*:d->MODEMNR*/
    sEvent    = d->IDFNR;          /*:d->EREIGNIS*/
    lUid      = atol(d->TELNR);
    lTime = ppGGetUniqueTime(800);
    lDateFirst = ppGGetDate();
    exec sql execute p_InsDataProtX using :d->VERTRIEBSZENTRUMNR,
                                          :d->KUNDENNR,
                                          :d->DATUM,
                                          :d->URRUFZEIT,
                                          :sEvent,
                                          :d->RUFZEIT,
                                          :d->UMKSTATUS,
                                          :d->ANRUFSTATUS,
                               		  :sBranchNo,
                 		          :lModemNo,
					  :lTime,
                                          :lUid,
                                          :lDateFirst;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_InsDataProtX" ) ) != IS_OK )
       return rc;
 
    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( bInTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
    }
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlanDayHist.cxx                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:27 2022                                         */
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
#include "callplanday.h"

/* MCustomerCallPlanDayHist: Select *******************************************/

/* MCustomerCallPlanDayHist::SelList ******************************************/

retClient Mcustomercallplandayhist_SelList(mcustomercallplandayhistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplandayhist_SelList";
    exec sql begin declare section;
    mcustomercallplandayhistS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList4 cursor with hold for
                  select passwd.username,
                     kundeanrufplanprot.VertriebszentrumNr,
                     kundeanrufplanprot.KundenNr,
                     kundeanrufplanprot.datum,
                     kundeanrufplanprot.UrRufzeit,
                     kundeanrufplanprot.Ereignis,
                     kundeanrufplanprot.rufzeit,
                     kundeanrufplanprot.UmkStatus,
                     kundeanrufplanprot.AnrufStatus,
                     kundeanrufplanprot.filialnr,
                     kundeanrufplanprot.ModemNr,
                     kundeanrufplanprot.uhrzeit,
                     kundeanrufplanprot.geraeteid,
                     kundeanrufplanprot.uid,
                     kundeanrufplanprot.DatumAnlage
                from KUNDEANRUFPLANPROT, outer PASSWD
                  where KundeAnrufplanProt.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                        KundeAnrufplanProt.KundenNr	 =	:d->KUNDENNR	and
                        KundeAnrufplanProt.datum	 =	:d->DATUM	and
                        KundeAnrufplanProt.UrRufzeit	 =	:d->URRUFZEIT and
                        passwd.uid = KundeAnrufplanProt.uid and
                        passwd.filialnr =KundeAnrufplanProt.filialnr
                        order by KundeAnrufplanProt.DatumAnlage,KundeAnrufplanProt.uhrzeit;
        exec sql open CSelList4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList4;
        return CheckSql( fun, stError, "%s", "close CSelList4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList4 into :d->USERNAME,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->URRUFZEIT,
                     :d->EREIGNIS,
                     :d->RUFZEIT,
                     :d->UMKSTATUS,
                     :d->ANRUFSTATUS,
                     :d->FILIALNR,
                     :d->MODEMNR,
                     :d->UHRZEIT,
                     :d->GERAETEID,
                     :d->UID,
                     :d->DATUMANLAGE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerCallPlanDayHist: Insert *******************************************/



/* MCustomerCallPlanDayHist: Update *******************************************/



/* MCustomerCallPlanDayHist: Select *******************************************/

/* MCustomerCallPlanDayHist::DelAll *******************************************/

retClient Mcustomercallplandayhist_DelAll(mcustomercallplandayhistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplandayhist_DelAll";
    exec sql begin declare section;
    mcustomercallplandayhistS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAll5 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     UrRufzeit,
                     Ereignis,
                     rufzeit,
                     UmkStatus,
                     AnrufStatus,
                     filialnr,
                     ModemNr,
                     uhrzeit,
                     geraeteid,
                     uid,
                     DatumAnlage
               from KUNDEANRUFPLANPROT
              where KundeAnrufplanProt.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeAnrufplanProt.datum	 =	:d->DATUM
              for update;
    exec sql open CDelAll5;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAll5" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAll5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAll5" ) ) != IS_OK )
            break;
        exec sql delete from kundeanrufplanprot where current of CDelAll5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAll5" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 100 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
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
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* MCustomerCallPlanDayHist::DelAllOlder **************************************/

retClient Mcustomercallplandayhist_DelAllOlder(mcustomercallplandayhistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplandayhist_DelAllOlder";
    exec sql begin declare section;
    mcustomercallplandayhistS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    exec sql declare CDelAllOlder6 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     UrRufzeit,
                     Ereignis,
                     rufzeit,
                     UmkStatus,
                     AnrufStatus,
                     filialnr,
                     ModemNr,
                     uhrzeit,
                     geraeteid,
                     uid,
                     DatumAnlage
               from KUNDEANRUFPLANPROT
              where KundeAnrufplanProt.VertriebszentrumNr	 = :d->VERTRIEBSZENTRUMNR  and
                    KundeAnrufplanProt.datum <=	:d->DATUM and
                    KundeAnrufplanProt.datum !=	:lDate
              for update;
    exec sql open CDelAllOlder6;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllOlder6" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllOlder6;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllOlder6" ) ) != IS_OK )
            break;
        exec sql delete from kundeanrufplanprot where current of CDelAllOlder6;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllOlder6" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 50 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
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
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/* MCustomerCallPlanDayHist: Other ********************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlanRecallInWork.cxx                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:31 2022                                         */
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
#include "callplanday.h"

/* MCustomerCallPlanRecallInWork: Select **************************************/

/* MCustomerCallPlanRecallInWork::Select **************************************/

retClient Mcustomercallplanrecallinwork_Select(mcustomercallplanrecallinworkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanrecallinwork_Select";
    exec sql begin declare section;
    mcustomercallplanrecallinworkS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kundeanrufplanrr.VertriebszentrumNr,
                     kundeanrufplanrr.KundenNr,
                     kundeanrufplanrr.UrRufzeit,
                     kundeanrufplanrr.datum,
                     kundeanrufplanrr.filialnr,
                     kundeanrufplanrr.uid,
                     kundeanrufplanrr.tm_time
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->URRUFZEIT,
                     :d->DATUM,
                     :d->FILIALNR,
                     :d->UID,
                     :d->TM_TIME
                from KUNDEANRUFPLANRR
              where KundeAnrufplanRR.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR and
                    KundeAnrufplanRR.KundenNr	 =:d->KUNDENNR and
                    KundeAnrufplanRR.UrRufzeit =:d->URRUFZEIT and
                    KundeAnrufplanRR.datum =:d->DATUM and
                    KundeAnrufplanRR.uid !=:d->UID;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerCallPlanRecallInWork: Insert **************************************/

/* MCustomerCallPlanRecallInWork::Insert **************************************/

retClient Mcustomercallplanrecallinwork_Insert(mcustomercallplanrecallinworkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanrecallinwork_Insert";
    exec sql begin declare section;
    mcustomercallplanrecallinworkS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    a->TM_TIME = ppGGetTime();
    exec sql insert into kundeanrufplanrr (VertriebszentrumNr,
                     KundenNr,
                     UrRufzeit,
                     datum,
                     filialnr,
                     uid,
                     tm_time)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->URRUFZEIT,
                     :d->DATUM,
                     :d->FILIALNR,
                     :d->UID,
                     :d->TM_TIME);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kundeanrufplanrr" ) ) != IS_OK )
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



/* MCustomerCallPlanRecallInWork: Update **************************************/

/* MCustomerCallPlanRecallInWork::Update **************************************/

retClient Mcustomercallplanrecallinwork_Update(mcustomercallplanrecallinworkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomercallplanrecallinwork_Update";
    exec sql begin declare section;
    mcustomercallplanrecallinworkS *d;
    exec sql end declare section;

    d = a;

    a->TM_TIME = ppGGetTime();


    exec sql declare CUpdate8 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     UrRufzeit,
                     datum,
                     filialnr,
                     uid,
                     tm_time
               from KUNDEANRUFPLANRR
              where KundeAnrufplanRR.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeAnrufplanRR.KundenNr	 =	:d->KUNDENNR	 and
                    KundeAnrufplanRR.UrRufzeit	 =	:d->URRUFZEIT	 and
                    KundeAnrufplanRR.datum	 =	:d->DATUM	 and
                    KundeAnrufplanRR.filialnr	 =	:d->FILIALNR and 
                    KundeAnrufplanRR.uid	 =	:d->UID
              for update;
    exec sql open CUpdate8;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate8" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate8;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate8" ) ) != IS_OK )
            break;
        exec sql update kundeanrufplanrr set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     UrRufzeit = :d->URRUFZEIT,
                     datum = :d->DATUM,
                     filialnr = :d->FILIALNR,
                     uid = :d->UID,
                     tm_time = :d->TM_TIME where current of CUpdate8;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate8" ) ) != IS_OK )
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



/* MCustomerCallPlanRecallInWork: Select **************************************/

/* MCustomerCallPlanRecallInWork::Delete **************************************/

retClient Mcustomercallplanrecallinwork_Delete(mcustomercallplanrecallinworkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomercallplanrecallinwork_Delete";
    exec sql begin declare section;
    mcustomercallplanrecallinworkS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete9 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     UrRufzeit,
                     datum,
                     filialnr,
                     uid,
                     tm_time
               from KUNDEANRUFPLANRR
              where KundeAnrufplanRR.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeAnrufplanRR.KundenNr	 =	:d->KUNDENNR	 and
                    KundeAnrufplanRR.UrRufzeit	 =	:d->URRUFZEIT	 and
                    KundeAnrufplanRR.datum	 =	:d->DATUM	 and
                    KundeAnrufplanRR.filialnr	 =	:d->FILIALNR	 and
                    KundeAnrufplanRR.uid	 =	:d->UID
              for update;
    exec sql open CDelete9;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete9" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete9" ) ) != IS_OK )
            break;
        exec sql delete from kundeanrufplanrr where current of CDelete9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete9" ) ) != IS_OK )
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



/* MCustomerCallPlanRecallInWork: Other ***************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallplanDayDriver.cxx                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:40 2022                                         */
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
#include "callplanday.h"

/* MCustomerCallplanDayDriver: Select *****************************************/



/* MCustomerCallplanDayDriver: Insert *****************************************/



/* MCustomerCallplanDayDriver: Update *****************************************/



/* MCustomerCallplanDayDriver: Select *****************************************/



/* MCustomerCallplanDayDriver: Other ******************************************/

/* MCustomerCallplanDayDriver::EndBrowse **************************************/

retClient Mcustomercallplandaydriver_EndBrowse(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplandaydriver_EndBrowse";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql free p_SelCDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelCDataX" ) ) != IS_OK )
        return rc;

    exec sql free p_SelUDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_UpdUDataX" ) ) != IS_OK )
       return rc;

    exec sql free p_UpdCDataX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_UpdCDataX" ) ) != IS_OK )
       return rc;

    exec sql free p_InsCDataProtX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_InsCDataProtX" ) ) != IS_OK )
       return rc;

    exec sql free p_SelCRushTourIDX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelCRushTourIDX" ) ) != IS_OK )
       return rc;

    exec sql free p_SelCTourIDX;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelCTourIDX" ) ) != IS_OK )
       return rc;
    return rc;
}

/* MCustomerCallplanDayDriver::SelList ****************************************/

retClient Mcustomercallplandaydriver_SelList(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplandaydriver_SelList";
    exec sql begin declare section;
    mcustomercallplandaydriverS *d = a;
    int iID = 0; /* indicator */
    exec sql end declare section;

    if ( a->FETCH_REL == SET_OPEN )
    {
       d->DATUM = ppGGetDate();
       exec sql open CSelCDataX using :d->VERTRIEBSZENTRUMNR, :d->DATUM;
       if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCDataX" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelCDataX;
      return CheckSql( fun, stError, "%s", "close CSelCDataX" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelCDataX into MCUSTOMERCALLPLANDAYDRIVER_ZEIGERSEL(d);
    if ( (rc=CheckSql( fun, stError, "%s", "fetch CSelCDataX" )) != IS_OK )
       return rc; 
    else if ( d->SKDANRUFGENERELL[0] != '1' )
    {
       exec sql execute p_SelCCallEver into :d->SKDANRUFGENERELL
                                      using :d->VERTRIEBSZENTRUMNR,
                                            :d->KUNDENNR; 
       if ( (rc=CheckSql( fun, stError, "%s", "p_SelCCallEver" )) != IS_OK )
          return rc;
    }

    if ( d->TOURID[0] != ' ' )
       return rc; 
/* nur lesen wenn keine TOURID vorhanden */
    if ( d->RUFSTEUERUNG != 20 )
    {
       exec sql execute p_SelCTourIDX into :d->TOURID indicator :iID
                                     using :d->VERTRIEBSZENTRUMNR,
                                           :d->KUNDENNR,
                                           :d->URRUFZEIT,
                                           :d->DATUM;
       rc = CheckSql( fun, stError, "%s", "execute p_SelCTourIDX" );
    }
    else
    {
       exec sql execute p_SelCRushTourIDX into :d->TOURID indicator :iID
                                         using :d->VERTRIEBSZENTRUMNR,
                                               :d->KUNDENNR,
                                               :d->URRUFZEIT,
                                               :d->DATUM;
       rc = CheckSql( fun, stError, "%s", "execute p_SelCRushTourIDX" );
    }

    if ( iID < 0 )
    {
       strcpy(d->TOURID, " " );
       /*WriteLog( " ", -1, "%s", "Keine Touren geladen" );*/
       /*WriteLogInfo("Keine Touren geladen", -1, -1);*/
    }

    return rc;
}

/* MCustomerCallplanDayDriver::SelUniCustomerCallplan *************************/

retClient Mcustomercallplandaydriver_SelUniCustomerCallplan(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    char *fun = "Mcustomercallplandaydriver_SelUniCustomerCallplan";
    exec sql begin declare section;
    mcustomercallplandaydriverS *d = a;
    exec sql end declare section;

    if ( bIsTrans ); /*only because preprozessor*/
    exec sql execute p_SelUDataX into MCUSTOMERCALLPLANDAYDRIVER_ZEIGERSEL(d) 
                                using :d->VERTRIEBSZENTRUMNR,
                                      :d->KUNDENNR,
                                      :d->URRUFZEIT,
                                      :d->DATUM;
    return CheckSql( fun, stError, "%s", "execute p_SelUDataX" );
}

/* MCustomerCallplanDayDriver::StartBrowse ************************************/

retClient Mcustomercallplandaydriver_StartBrowse(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplandaydriver_StartBrowse";
    exec sql begin declare section;
    char szBuf[2560];
    exec sql end declare section;

    if ( a || bIsTrans ); /*only because preprozessor*/

    /* sequenz scan */
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERCALLPLANDAYDRIVER_PLISTE ); 
    strcat( szBuf, " from KUNDEANRUFPLANTAG, KUNDE, KUNDEANRUFPLANPROT " );
    strcat( szBuf, "where KundeAnrufplanTag.VertriebszentrumNr=? and " );
/* falls Regionenarten benutzt werden sollen! 
    strcat( szBuf, " in ( " );
    strcat( szBuf, "select RegionArten.RegionTeilNr from RegionArten " );
    strcat( szBuf, "where RegionArten.RegionNr=? and " );
    strcat( szBuf, "RegionArten.RegionenTyp=3 ) and " ); 
*/
    strcat( szBuf, "KundeAnrufplanTag.datum=? and " );	
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=3 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=7 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=8 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=9 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=10 and " );
    strcat( szBuf, "KundeAnrufplanTag.AnrufStatus!=11 and " );
/* phonetische Rufe NICHT rufen!!!! */
    strcat( szBuf, "KundeAnrufplanTag.Rufeinstellung != \"0\" and " );
    strcat( szBuf, "Kunde.KundenNr=KundeAnrufplanTag.KundenNr and " );
    strcat( szBuf, "Kunde.VertriebszentrumNr=KundeAnrufplanTag.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.VertriebszentrumNr=KundeAnrufplanprot.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=KundeAnrufplanprot.KundenNr and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=KundeAnrufplanprot.UrRufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Rufzeit=KundeAnrufplanprot.Rufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Datum=KundeAnrufplanprot.Datum and " );
    strcat( szBuf, "KundeAnrufplanTag.Anrufstatus=KundeAnrufplanprot.Anrufstatus and " );
    strcat( szBuf, "KundeAnrufplanprot.uhrzeit=(" );
    strcat( szBuf, "select max(uhrzeit) from KundeAnrufplanprot where " );
    strcat( szBuf, "KundeAnrufplanTag.VertriebszentrumNr=KundeAnrufplanprot.VertriebszentrumNr and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=KundeAnrufplanprot.KundenNr and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=KundeAnrufplanprot.UrRufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Rufzeit=KundeAnrufplanprot.Rufzeit and " );
    strcat( szBuf, "KundeAnrufplanTag.Datum=KundeAnrufplanprot.Datum and " );
    strcat( szBuf, "KundeAnrufplanTag.Anrufstatus=KundeAnrufplanprot.Anrufstatus " );
    strcat( szBuf, ") " );
    strcat( szBuf, "order by KundeAnrufplanTag.rufzeit,KundeAnrufplanTag.RufSteuerung,kunde.nameapo");
    exec sql prepare p_SelCDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelCDataX" ) ) != IS_OK )
        return rc;
    exec sql declare CSelCDataX cursor with hold for p_SelCDataX;
 
    /* unique select */
    strcpy( szBuf, "select " );
    strcat( szBuf, "KUNDE.NAMEAPO," );
    strcat( szBuf, "KUNDE.TELNR," );
    strcat( szBuf, "KUNDE.TELNRDAFUE," );
    strcat( szBuf, "KUNDE.TELKURZWAHL," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.VERTRIEBSZENTRUMNR," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.KUNDENNR," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.DATUM," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.URRUFZEIT," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.RUFZEIT," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.UMKSTATUS," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.ANRUFSTATUS," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.ANRUFZAEHLER," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.TAGNR," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.TOURID," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.STOURDEFINITIV," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.RUFPROTOKOLL," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.RUFSTEUERUNG," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.POOLNR," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.MODEMPOOLNR," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.RUFEINSTELLUNG," );
    strcat( szBuf, "KUNDEANRUFPLANTAG.ANRUFTYP, " );
    strcat( szBuf, "KUNDEANRUFPLANTAG.SKDANRUFGENERELL," );
    strcat( szBuf, "0," );
    strcat( szBuf, "0," );
    strcat( szBuf, "0 " );
    strcat( szBuf, " from KUNDEANRUFPLANTAG, KUNDE " );
    strcat( szBuf, "where KundeAnrufplanTag.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=? and " );
    strcat( szBuf, "KundeAnrufplanTag.datum=? and " );	
    strcat( szBuf, "KundeAnrufplanTag.Rufeinstellung != \"0\" and " );	
    strcat( szBuf, "Kunde.KundenNr=KundeAnrufplanTag.KundenNr and " );
    strcat( szBuf, "Kunde.VertriebszentrumNr=KundeAnrufplanTag.VertriebszentrumNr " );
    exec sql prepare p_SelUDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelUDataX" ) ) != IS_OK )
        return rc;

    /* update */
    strcpy( szBuf, "update kundeanrufplantag set " );
    strcat( szBuf, MCUSTOMERCALLPLANDAYDRIVER_UPDLISTE );
    strcat( szBuf, " where KundeAnrufplanTag.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanTag.KundenNr=? and " );	
    strcat( szBuf, "KundeAnrufplanTag.Datum=? and " );	
    strcat( szBuf, "KundeAnrufplanTag.UrRufzeit=? " );	
    exec sql prepare p_UpdCDataX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_UpdCDataX" ) ) != IS_OK )
        return rc;

    /* update -> insert into kundeanrufplanprot*/
    strcpy( szBuf, "insert into kundeanrufplanprot ( " );
    strcat( szBuf, "kundeanrufplanprot.VertriebszentrumNr," );
    strcat( szBuf, "kundeanrufplanprot.KundenNr," );
    strcat( szBuf, "kundeanrufplanprot.datum," );
    strcat( szBuf, "kundeanrufplanprot.UrRufzeit," );
    strcat( szBuf, "kundeanrufplanprot.Ereignis," );
    strcat( szBuf, "kundeanrufplanprot.rufzeit," );
    strcat( szBuf, "kundeanrufplanprot.UmkStatus," );
    strcat( szBuf, "kundeanrufplanprot.AnrufStatus," );
    strcat( szBuf, "kundeanrufplanprot.filialnr," );
    strcat( szBuf, "kundeanrufplanprot.ModemNr," );
    strcat( szBuf, "kundeanrufplanprot.uhrzeit, " );
    strcat( szBuf, "kundeanrufplanprot.geraeteid, " );
    strcat( szBuf, "kundeanrufplanprot.uid, " );
    strcat( szBuf, "kundeanrufplanprot.DatumAnlage) " );
    strcat( szBuf, "values (?,?,?,?,?,?,?,?,?,?,?,?,?,?) " );
    exec sql prepare p_InsCDataProtX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_InsCDataProtX" ) ) != IS_OK )
        return rc;

   /* unique tourid scan; Call is not a rushorder! */
    strcpy( szBuf, "select min (tourplantag.tourid) " );
    strcat( szBuf, "from tourplantag,tour,paraauftragbearb " );
    strcat( szBuf, "where tourplantag.vertriebszentrumnr=? and " );
    strcat( szBuf, "paraauftragbearb.filialnr=tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.kundennr=? and " );
    strcat( szBuf, "tourplantag.tourid[1,4]>? + paraauftragbearb.durchlaufnormal and " );
    strcat( szBuf, "tourplantag.tourid = tour.tourid and " );
    strcat( szBuf, "tour.filialnr = tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.datumkommi = tour.datumkommi and " );
    strcat( szBuf, "tourplantag.datumkommi = ? " );
    exec sql prepare p_SelCTourIDX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", " p_SelCTourIDX" ) ) != IS_OK )
        return rc;

    /* unique tourid scan; Call is a rushorder! */
    strcpy( szBuf, "select min (tourplantag.tourid) " );
    strcat( szBuf, "from tourplantag,tour, paraauftragbearb " );
    strcat( szBuf, "where tourplantag.vertriebszentrumnr=? and " );
    strcat( szBuf, "paraauftragbearb.filialnr=tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.kundennr=? and " );
    strcat( szBuf, "tourplantag.tourid[1,4]>? + paraauftragbearb.durchlaufeilbote and " );
    strcat( szBuf, "tourplantag.tourid = tour.tourid and " );
    strcat( szBuf, "tour.filialnr = tourplantag.vertriebszentrumnr and " );
    strcat( szBuf, "tourplantag.datumkommi = tour.datumkommi and " );
    strcat( szBuf, "tourplantag.datumkommi = ? " );
     exec sql prepare p_SelCRushTourIDX from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", " p_SelCRushTourIDX" ) ) != IS_OK )
        return rc;

    /* unique kundeschaltert scan; is Call for ever! */
    strcpy( szBuf, "select kundeschalter.skdanrufgenerell " );
    strcat( szBuf, "from kundeschalter " );
    strcat( szBuf, "where kundeschalter.vertriebszentrumnr=? and " );
    strcat( szBuf, "kundeschalter.kundennr=? " );
    exec sql prepare p_SelCCallEver from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", " p_SelCCallEver" ) ) != IS_OK )
        return rc;
    return rc;
}

/* MCustomerCallplanDayDriver::UpdCustomerCallplan ****************************/

retClient Mcustomercallplandaydriver_UpdCustomerCallplan(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = FALSE;
    char *fun = "Mcustomercallplandaydriver_UpdCustomerCallplan";
    exec sql begin declare section;
    mcustomercallplandaydriverS *d = a;
    long lTime;
    short sBranchNo;
    short sEvent;
    long  lModemNo;
    long  lUid;
    char  szDeviceID[5];
    long  lDateFirst;
    exec sql end declare section;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       bInTrans = TRUE;
    }
 
    exec sql execute p_UpdCDataX using MCUSTOMERCALLPLANDAYDRIVER_ZEIGER(d),
                                       :d->VERTRIEBSZENTRUMNR,
                                       :d->KUNDENNR,	
                                       :d->DATUM,
                                       :d->URRUFZEIT;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_UpdCDataX" ) ) != IS_OK )
       return rc;
/*
0-angelegt
1-verschoben
2-gelöscht
3-heute kein auftrag
4-übertragen
*/

    sBranchNo = d->POOLNR;         /*:d->FILIALNR*/
    lModemNo  = d->MODEMPOOLNR;    /*:d->MODEMNR*/
    sEvent    = d->RUFSTEUERUNG;         /*:d->EREIGNIS*/
    lUid      = atol(d->TELNR);
    lTime = ppGGetUniqueTime((short)d->UHRZEIT);
    sprintf( szDeviceID, "%4.4s", d->GERAETEID );
    lDateFirst = ppGGetDate();
    exec sql execute p_InsCDataProtX using :d->VERTRIEBSZENTRUMNR,
                                          :d->KUNDENNR,
                                          :d->DATUM,
                                          :d->URRUFZEIT,
                                          :sEvent,
                                          :d->RUFZEIT,
                                          :d->UMKSTATUS,
                                          :d->ANRUFSTATUS,
                               		  :sBranchNo,
                 		          :lModemNo,
					  :lTime,
                                          :szDeviceID,
                                          :lUid,
                                          :lDateFirst;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_InsCDataProtX" ) ) != IS_OK )
    {
       printf( "Vz:%d/%ld/%ld/%ld/%ld/%d\n",
               d->VERTRIEBSZENTRUMNR,
               d->KUNDENNR,
               d->DATUM,
               d->URRUFZEIT,
               lTime,
               sEvent );
       printf( "SQL: %ld%ld\n", sqlca.sqlcode, sqlca.sqlerrd[1] );
       fflush(stdout);  
       return rc;
    }
 
    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( bInTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
    }
    return rc;
}

/* MCustomerCallplanDayDriver::UpdCustomerCallplanWithoutTransaction **********/

retClient Mcustomercallplandaydriver_UpdCustomerCallplanWithoutTransaction(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = FALSE;
    char *fun = "Mcustomercallplandaydriver_UpdCustomerCallplan";
    exec sql begin declare section;
    mcustomercallplandaydriverS *d = a;
    long lTime;
    short sBranchNo;
    short sEvent;
    long  lModemNo;
    long  lUid;
    char  szDeviceID[5];
    long  lDateFirst;
    exec sql end declare section;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       bInTrans = TRUE;
    }
 
    exec sql execute p_UpdCDataX using MCUSTOMERCALLPLANDAYDRIVER_ZEIGER(d),
                                       :d->VERTRIEBSZENTRUMNR,
                                       :d->KUNDENNR,	
                                       :d->DATUM,
                                       :d->URRUFZEIT;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_UpdCDataX" ) ) != IS_OK )
       return rc;
/*
0-angelegt
1-verschoben
2-gelöscht
3-heute kein auftrag
4-übertragen
*/

    sBranchNo = d->POOLNR;         /*:d->FILIALNR*/
    lModemNo  = d->MODEMPOOLNR;    /*:d->MODEMNR*/
    sEvent    = d->RUFSTEUERUNG;         /*:d->EREIGNIS*/
    lUid      = atol(d->TELNR);
    lTime = ppGGetUniqueTime((short)d->UHRZEIT);
    sprintf( szDeviceID, "%4.4s", d->GERAETEID );
    lDateFirst = ppGGetDate();
    exec sql execute p_InsCDataProtX using :d->VERTRIEBSZENTRUMNR,
                                          :d->KUNDENNR,
                                          :d->DATUM,
                                          :d->URRUFZEIT,
                                          :sEvent,
                                          :d->RUFZEIT,
                                          :d->UMKSTATUS,
                                          :d->ANRUFSTATUS,
                               		  :sBranchNo,
                 		          :lModemNo,
					  :lTime,
                                          :szDeviceID,
                                          :lUid,
                                          :lDateFirst;
    if ( ( rc=CheckSql( fun, stError, "%s", "execute p_InsCDataProtX" ) ) != IS_OK )
    {
       printf( "Vz:%d/%ld/%ld/%ld/%ld/%d\n",
               d->VERTRIEBSZENTRUMNR,
               d->KUNDENNR,
               d->DATUM,
               d->URRUFZEIT,
               lTime,
               sEvent );
       printf( "SQL: %ld%ld\n", sqlca.sqlcode, sqlca.sqlerrd[1] );
       fflush(stdout);  
       return rc;
    }
 
    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( bInTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
    }
    return rc;
}

/* MCustomerCallplanDayDriver::UpdWithoutTransaction **************************/

retClient Mcustomercallplandaydriver_UpdWithoutTransaction(mcustomercallplandaydriverS *a, tError *stError, bool bIsTrans)
{
    char *fun = "Mcustomercallplandaydriver_UpdWithoutTransaction";

    Mcustomercallplandaydriver_UpdCustomerCallplan(a,stError, bIsTrans);
    return CheckSql( fun, stError, "%s", stError->spError );
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerLastCall.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:44 2022                                         */
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
#include "callplanday.h"

/* MCustomerLastCall: Select **************************************************/



/* MCustomerLastCall: Insert **************************************************/



/* MCustomerLastCall: Update **************************************************/



/* MCustomerLastCall: Select **************************************************/



/* MCustomerLastCall: Other ***************************************************/

/* MCustomerLastCall::EndBrowse ***********************************************/

retClient Mcustomerlastcall_EndBrowse(mcustomerlastcallS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "McustomerLastCall_EndBrowse";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql free p_SelUniState;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelUniState" ) ) != IS_OK )
        return rc;
    return rc;
}

/* MCustomerLastCall::SelCustomerCallState ************************************/

retClient Mcustomerlastcall_SelCustomerCallState(mcustomerlastcallS *a, tError *stError, bool bIsTrans)
{
char *fun = "MCustomerLastCall_SelCustomerCallState";
exec sql begin declare section;
mcustomerlastcallS *d = a;
exec sql end declare section;

if ( bIsTrans ); /*only because preprozessor*/
exec sql execute p_SelUniState into MCUSTOMERLASTCALL_ZEIGERSEL(d) 
                                using :d->VERTRIEBSZENTRUMNR,
                                      :d->KUNDENNR,
                                      :d->URRUFZEIT,
                                      :d->DATUM,
                                      :d->ANRUFSTATUS,
                                      :d->VERTRIEBSZENTRUMNR,
                                      :d->KUNDENNR,
                                      :d->URRUFZEIT,
                                      :d->DATUM,
                                      :d->ANRUFSTATUS;
return CheckSql( fun, stError, "%s", "execute p_SelUniState" );
}

/* MCustomerLastCall::StartBrowse *********************************************/

retClient Mcustomerlastcall_StartBrowse(mcustomerlastcallS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "McustomerLastCall_StartBrowse";
    exec sql begin declare section;
    char szBuf[2560];
    exec sql end declare section;

    if ( a || bIsTrans ); /*only because preprozessor*/

    /* unique select */
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERLASTCALL_PLISTE ); 
    strcat( szBuf, " from KUNDEANRUFPLANPROT where " );
    strcat( szBuf, "KundeAnrufplanprot.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanprot.KundenNr=? and " );
    strcat( szBuf, "KundeAnrufplanprot.UrRufzeit=? and " );
    strcat( szBuf, "KundeAnrufplanprot.Datum=? and " );
    strcat( szBuf, "KundeAnrufplanprot.Anrufstatus=? and " );
    strcat( szBuf, "KundeAnrufplanprot.uhrzeit=(" );
    strcat( szBuf, "select max(uhrzeit) from KundeAnrufplanprot where " );
    strcat( szBuf, "KundeAnrufplanprot.VertriebszentrumNr=? and " );
    strcat( szBuf, "KundeAnrufplanprot.KundenNr=? and " );
    strcat( szBuf, "KundeAnrufplanprot.UrRufzeit=? and " );
    strcat( szBuf, "KundeAnrufplanprot.Datum=? and " );
    strcat( szBuf, "KundeAnrufplanprot.Anrufstatus=?) " );
    
    exec sql prepare p_SelUniState from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelUniState" ) ) != IS_OK )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerOrder.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:48 2022                                         */
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
#include "callplanday.h"

/* MCustomerOrder: Select *****************************************************/



/* MCustomerOrder: Insert *****************************************************/



/* MCustomerOrder: Update *****************************************************/



/* MCustomerOrder: Select *****************************************************/



/* MCustomerOrder: Other ******************************************************/

/* MCustomerOrder::EndBrowse **************************************************/

retClient Mcustomerorder_EndBrowse(mcustomerorderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomerorder_EndBrowse";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql free p_SelPCheck;
    if ( ( rc = CheckSql( fun, stError, "%s", "free p_SelPCheck" ) ) != IS_OK )
       return rc;
    exec sql free p_SelEDev;
    if ( ( rc = CheckSql( fun, stError, "%s", "free p_SelEDev" ) ) != IS_OK )
       return rc;
    exec sql free p_SelUDev; 
    return CheckSql( fun, stError, "%s", "free p_SelUDev" );
}

/* MCustomerOrder::SelAvailableOrder ******************************************/

retClient Mcustomerorder_SelAvailableOrder(mcustomerorderS *a, tError *stError, bool bIsTrans)
{
   #define MAX_AUFTRAG   20
    char *fun = "MCustomerOrder_SelAvailableOrder";
    retClient rc = IS_OK;
    exec sql begin declare section;
    mcustomerorderS *d = a; 
    long lDate = ppGGetDate();
    long laKdauftrag[MAX_AUFTRAG]; 
    char szBuf[1024]; 
    exec sql end declare section;

    char szAuftragBuf[256];
    int i;
 
    if ( bIsTrans ); /*only because preprozessor*/

    exec sql open CSelAufNr using :d->VERTRIEBSZENTRUMNR,
                                  :d->KUNDENNR,
                                  :d->ANZPOS;
    
    for( i = 0; i < MAX_AUFTRAG; i++ )
    { 
       exec sql fetch CSelAufNr into :laKdauftrag[i];
       if ( (rc=CheckSql( fun, stError, "%s", "fetch CHelpCu" ) ) == IS_ERROR )
          return rc;
       else if ( rc == IS_NOTFOUND && i == 0 )
          return rc; /* no order found -> exit */
       else if ( rc == IS_NOTFOUND )
          break; 
       else if ( i == 0)
       {
          sprintf( szAuftragBuf, "%ld", laKdauftrag[i] ); 
       }
       else
       {
          char szAuftrag[12];
		  sprintf( szAuftrag, ",%ld", laKdauftrag[i] );  
          strcat( szAuftragBuf, szAuftrag );
       }  
    }

    /* dynamic select is needed */
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERORDER_PLISTE ); 
    strcat( szBuf, " from kdauftrag,kdauftragereignis " );
    strcat( szBuf, "where kdauftragereignis.datum=? and " );	
    strcat( szBuf, "kdauftragereignis.ereignisart=1 and " );	
    strcat( szBuf, "kdauftrag.kdauftragnr=kdauftragereignis.kdauftragnr and " );
    strcat( szBuf, "kdauftragereignis.kdauftragnr in (" );
    strcat( szBuf, szAuftragBuf );
    strcat( szBuf, ") and " );                                   
    strcat( szBuf, "trunc(kdauftragereignis.zeit/1000) > ? " );
    strcat( szBuf, "order by kdauftragereignis.zeit desc " ); 

    exec sql prepare p_SelDynDev from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelDynDev" ) ) != IS_OK )
        return rc;

    exec sql declare CSelDynDev cursor with hold for p_SelDynDev;
	exec sql open CSelDynDev using :lDate,
                                   :d->ZEIT;

    exec sql fetch CSelDynDev into :*d;
    return CheckSql( fun, stError, "%s", "fetch CSelDynDev" );
}

/* MCustomerOrder::SelCustomerCalled ******************************************/

retClient Mcustomerorder_SelCustomerCalled(mcustomerorderS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MCustomerOrder_SelCustomerCalled";
    exec sql begin declare section;
    int iResult;  /* indicator, because max-selection! */
    mcustomerorderS *d = a; 
    long lDate = ppGGetDate();
    exec sql end declare section;

    if ( bIsTrans ); /*only because preprozessor*/
    
    exec sql execute p_SelPCheck into :d->ZEIT indicator :iResult
                                using :lDate,
                                      :d->VERTRIEBSZENTRUMNR,
                                      :d->KUNDENNR;
    if ( iResult < 0 || d->ZEIT < 0 )
       d->ZEIT = 0;
    return CheckSql( fun, stError, "%s", "execute p_SelPCheck" );
}

/* MCustomerOrder::SelDeviceOrder *********************************************/

retClient Mcustomerorder_SelDeviceOrder(mcustomerorderS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MCustomerOrder_SelDeviceOrder";
    exec sql begin declare section;
    mcustomerorderS *d = a; 
    long lDate = ppGGetDate();
    exec sql end declare section;

    if ( bIsTrans ); /*only because preprozessor*/
    
    exec sql execute p_SelUDev using :d->VERTRIEBSZENTRUMNR,
                                     :d->KUNDENNR,
                                     :d->GERAETNAME,
                                     :lDate,
                                     :d->GERAETNAME,
                                     :d->ZEIT;

    return CheckSql( fun, stError, "%s", "execute p_SelUDev" );
}

/* MCustomerOrder::StartBrowse ************************************************/

retClient Mcustomerorder_StartBrowse(mcustomerorderS *a, tError *stError, bool bIsTrans)
{
   #define MAX_GERAET   30
    retClient rc = IS_OK;
    char *fun = "MCustomerOrder_StartBrowse";
    exec sql begin declare section;
    char szBuf[2048];
    char szGeraet[L_MCUSTOMERCALLPLANDAYDRIVER_GERAETEID + 1]; 
    mcustomerorderS *d = a;
    exec sql end declare section;

    char szGeraetBuf[256];
    int i;
 
    if ( bIsTrans ); /*only because preprozessor*/

    exec sql declare CHelpCu cursor for
             select geraeteid 
               from MODEMANRUFPLAN, REGIONARTEN
              where RegionArten.RegionNr = :d->VERTRIEBSZENTRUMNR and 
                    RegionArten.RegionenTyp = 2 and
                    RegionArten.RegionTeilNr = ModemAnrufplan.filialnr and 
                    geraeteverw1 in ( "O", "D" );
    exec sql open CHelpCu;
    
    for( i = 0; i < MAX_GERAET; i++ )
    { 
       exec sql fetch CHelpCu into :szGeraet;
       if ( (rc=CheckSql( fun, stError, "%s", "fetch CHelpCu" ) ) == IS_ERROR )
          return rc;
       else if ( rc == IS_NOTFOUND )
       {
          strcpy( szGeraetBuf, "\"NOTF\"" );
          break;
       }
       else if ( i == 0)
       {
          sprintf( szGeraetBuf, "\"%s\"", szGeraet ); 
       }
       else
       {
          strcat( szGeraetBuf, ",\"" );
          strcat( szGeraetBuf, szGeraet );
          strcat( szGeraetBuf, "\"" );
       }  
    }                                          
 
    /* sequ-scan, first control select */
    strcpy( szBuf, "select kdauftrag.kdauftragnr " );
    strcat( szBuf, "from kdauftrag " );
    strcat( szBuf, "where kdauftrag.vertriebszentrumnr=? and " );
    strcat( szBuf, "kdauftrag.kundennr=? and " );
    strcat( szBuf, "kdauftrag.kdauftragstat[10]=\"0\" and " );
    strcat( szBuf, "kdauftrag.anzpos>=? and " );
    strcat( szBuf, "kdauftrag.geraetname in (" );
    strcat( szBuf, szGeraetBuf );
    strcat( szBuf, ") " );                                   
 
    exec sql prepare p_SelEDev from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelEDev" ) ) != IS_OK )
        return rc;

    exec sql declare CSelAufNr cursor with hold for p_SelEDev;

   /* unique check-select modemanrufplan*/
    strcpy( szBuf, "select max(modemanrufplan.startzeit) " );
    strcat( szBuf, "from modemanrufplan where " );
    strcat( szBuf, "modemanrufplan.datum=? and " );
    strcat( szBuf, "modemanrufplan.vertriebszentrumnr=? and " );
    strcat( szBuf, "modemanrufplan.kundennr=? and " ); 
    strcat( szBuf, "modemanrufplan.sequenznr!=0 and " );
    strcat( szBuf, "geraeteverw1 in (\"P\", \"D\") " ); 	
    exec sql prepare p_SelPCheck from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelPCheck" ) ) != IS_OK )
        return rc;
 
   /* unique check-select kdauftrag*/
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERORDER_PLISTE ); 
    strcat( szBuf, " from kdauftrag,kdauftragereignis " );
    strcat( szBuf, "where kdauftrag.vertriebszentrumnr=? and " );
    strcat( szBuf, "kdauftrag.kundennr=? and " );
    strcat( szBuf, "kdauftrag.geraetname=? and " );
    strcat( szBuf, "kdauftrag.kdauftragstat[10]=\"0\" and " ); 
    strcat( szBuf, "kdauftragereignis.datum = ? and " );	
    strcat( szBuf, "kdauftragereignis.ereignisart=1 and " );	
    strcat( szBuf, "kdauftragereignis.geraetname=? and " );	
    strcat( szBuf, "kdauftrag.kdauftragnr=kdauftragereignis.kdauftragnr and " );
    strcat( szBuf, "trunc(kdauftragereignis.zeit/1000) >= ? ");
    exec sql prepare p_SelUDev from :szBuf;
    return CheckSql( fun, stError, "%s", "prepare p_SelUDev" );
}



/******************************************************************************/
/*                                                                            */
/* header  : MDevicePlanCheck.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:50:54 2022                                         */
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
#include "callplanday.h"

/* MDevicePlanCheck: Select ***************************************************/

/* MDevicePlanCheck::SelDeviceID **********************************************/

retClient Mdeviceplancheck_SelDeviceID(mdeviceplancheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplancheck_SelDeviceID";
    exec sql begin declare section;
    mdeviceplancheckS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select regionarten.RegionenTyp,
                     modemanrufplan.filialnr,
                     modemanrufplan.geraeteid,
                     modemanrufplan.sequenznr,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.terminalstatus,
                     modemanrufplan.startzeit,
                     modemanrufplan.endezeit,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.KundenNr,
                     modemanrufplan.UrRufzeit,
                     modemanrufplan.datum,
                     modemanrufplan.AuftragStatus,
                     modemanrufplan.kdauftragnr1,
                     modemanrufplan.poolnr,
                     modemanrufplan.umknr,
                     modemanrufplan.aktiv
                into :d->REGIONENTYP,
                     :d->FILIALNR,
                     :d->GERAETEID,
                     :d->SEQUENZNR,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->TERMINALSTATUS,
                     :d->STARTZEIT,
                     :d->ENDEZEIT,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->URRUFZEIT,
                     :d->DATUM,
                     :d->AUFTRAGSTATUS,
                     :d->KDAUFTRAGNR1,
                     :d->POOLNR,
                     :d->UMKNR,
                     :d->AKTIV
                from MODEMANRUFPLAN, REGIONARTEN
              where RegionArten.RegionNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                    RegionArten.RegionTeilNr	 =	ModemAnrufplan.filialnr and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MDevicePlanCheck::SelList **************************************************/

retClient Mdeviceplancheck_SelList(mdeviceplancheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplancheck_SelList";
    exec sql begin declare section;
    mdeviceplancheckS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList11 cursor with hold for
                  select regionarten.RegionenTyp,
                     modemanrufplan.filialnr,
                     modemanrufplan.geraeteid,
                     modemanrufplan.sequenznr,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.terminalstatus,
                     modemanrufplan.startzeit,
                     modemanrufplan.endezeit,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.KundenNr,
                     modemanrufplan.UrRufzeit,
                     modemanrufplan.datum,
                     modemanrufplan.AuftragStatus,
                     modemanrufplan.kdauftragnr1,
                     modemanrufplan.poolnr,
                     modemanrufplan.umknr,
                     modemanrufplan.aktiv
                from MODEMANRUFPLAN, REGIONARTEN
                  where RegionArten.RegionNr	 =	:d->VERTRIEBSZENTRUMNR	and
                        RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                        RegionArten.RegionTeilNr	 =	ModemAnrufplan.filialnr
                        order by ModemAnrufplan.filialnr, ModemAnrufplan.geraeteverw1 desc, ModemAnrufplan.geraeteid;
        exec sql open CSelList11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList11" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList11;
        return CheckSql( fun, stError, "%s", "close CSelList11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList11 into :d->REGIONENTYP,
                     :d->FILIALNR,
                     :d->GERAETEID,
                     :d->SEQUENZNR,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->TERMINALSTATUS,
                     :d->STARTZEIT,
                     :d->ENDEZEIT,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->URRUFZEIT,
                     :d->DATUM,
                     :d->AUFTRAGSTATUS,
                     :d->KDAUFTRAGNR1,
                     :d->POOLNR,
                     :d->UMKNR,
                     :d->AKTIV;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList11" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MDevicePlanCheck::SelListHist **********************************************/

retClient Mdeviceplancheck_SelListHist(mdeviceplancheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplancheck_SelListHist";
    exec sql begin declare section;
    mdeviceplancheckS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListHist12 cursor with hold for
                  select ModemAnrufplan.umknr,
ModemAnrufplan.filialnr
                         into :d->UMKNR,
:d->FILIALNR
                   from MODEMANRUFPLAN, REGIONARTEN
                  where RegionArten.RegionNr = :d->VERTRIEBSZENTRUMNR and
                        RegionArten.RegionenTyp = :d->REGIONENTYP and
                        RegionArten.RegionTeilNr = ModemAnrufplan.filialnr and
                        ModemAnrufplan.geraeteverw1 = "P"
                        group by ModemAnrufplan.umknr, ModemAnrufplan.filialnr
                        order by ModemAnrufplan.filialnr, ModemAnrufplan.umknr;
        exec sql open CSelListHist12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHist12" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListHist12;
        return CheckSql( fun, stError, "%s", "close CSelListHist12" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListHist12;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListHist12" )) == IS_ERROR )
        return rc;
    if ( rc ==IS_NOTFOUND )
  return rc;
exec sql select count(*) into :d->STARTZEIT from modemanrufplan 
                                                                     where modemanrufplan.umknr = :d->UMKNR and
                                                                                modemanrufplan.filialnr = :d->FILIALNR and
                                                                                modemanrufplan.aktiv  = "1" and
                                                                                ModemAnrufplan.geraeteverw1 = "P";
if ( ( rc=CheckSql( fun, stError, "%s", "select count(*)" ) ) != IS_OK )
   return rc;
    return rc;
}



/* MDevicePlanCheck: Insert ***************************************************/



/* MDevicePlanCheck: Update ***************************************************/

/* MDevicePlanCheck::UpdUMKDecivePlan *****************************************/

retClient Mdeviceplancheck_UpdUMKDecivePlan(mdeviceplancheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mdeviceplancheck_UpdUMKDecivePlan";
    exec sql begin declare section;
    mdeviceplancheckS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdUMKDecivePlan13 cursor with hold for
              select sequenznr,
                     terminalstatus,
                     startzeit,
                     endezeit,
                     VertriebszentrumNr,
                     KundenNr,
                     UrRufzeit,
                     datum,
                     AuftragStatus,
                     kdauftragnr1,
                     aktiv
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	 and
                    ModemAnrufplan.umknr	 =	:d->UMKNR and
                    ModemAnrufplan.geraeteverw1	 =	"P"
              for update;
    exec sql open CUpdUMKDecivePlan13;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdUMKDecivePlan13" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdUMKDecivePlan13;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdUMKDecivePlan13" ) ) != IS_OK )
            break;
        exec sql update modemanrufplan set sequenznr = :d->SEQUENZNR,
                     terminalstatus = :d->TERMINALSTATUS,
                     startzeit = :d->STARTZEIT,
                     endezeit = :d->ENDEZEIT,
                     VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     UrRufzeit = :d->URRUFZEIT,
                     datum = :d->DATUM,
                     AuftragStatus = :d->AUFTRAGSTATUS,
                     kdauftragnr1 = :d->KDAUFTRAGNR1,
                     aktiv = :d->AKTIV where current of CUpdUMKDecivePlan13;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdUMKDecivePlan13" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 20 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
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

/* MDevicePlanCheck::UpdateDirect *********************************************/

retClient Mdeviceplancheck_UpdateDirect(mdeviceplancheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mdeviceplancheck_UpdateDirect";
    exec sql begin declare section;
    mdeviceplancheckS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdateDirect14 cursor with hold for
              select sequenznr,
                     terminalstatus,
                     startzeit,
                     endezeit,
                     VertriebszentrumNr,
                     KundenNr,
                     UrRufzeit,
                     datum,
                     AuftragStatus,
                     kdauftragnr1,
                     aktiv
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	 and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID
              for update;
    exec sql open CUpdateDirect14;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdateDirect14" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdateDirect14;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdateDirect14" ) ) != IS_OK )
            break;
        exec sql update modemanrufplan set sequenznr = :d->SEQUENZNR,
                     terminalstatus = :d->TERMINALSTATUS,
                     startzeit = :d->STARTZEIT,
                     endezeit = :d->ENDEZEIT,
                     VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     UrRufzeit = :d->URRUFZEIT,
                     datum = :d->DATUM,
                     AuftragStatus = :d->AUFTRAGSTATUS,
                     kdauftragnr1 = :d->KDAUFTRAGNR1,
                     aktiv = :d->AKTIV where current of CUpdateDirect14;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdateDirect14" ) ) != IS_OK )
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



/* MDevicePlanCheck: Select ***************************************************/



/* MDevicePlanCheck: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MDevicePlanDriver.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:51:03 2022                                         */
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
#include "callplanday.h"

/* MDevicePlanDriver: Select **************************************************/



/* MDevicePlanDriver: Insert **************************************************/



/* MDevicePlanDriver: Update **************************************************/



/* MDevicePlanDriver: Select **************************************************/



/* MDevicePlanDriver: Other ***************************************************/

/* MDevicePlanDriver::EndBrowse ***********************************************/

retClient Mdeviceplandriver_EndBrowse(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc;
    char *fun = "Mdeviceplandriver_EndBrowse";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql free p_SelDev;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelDev" ) ) != IS_OK )
        return rc;

    exec sql free p_SelUniDev;
    if ( (rc=CheckSql( fun, stError, "%s", "free p_SelUniDev" )) != IS_OK )
       return rc;
    
    exec sql free p_UpdDev;
    return CheckSql( fun, stError, "%s", "free p_UpdDev" );
}

/* MDevicePlanDriver::SelList *************************************************/

retClient Mdeviceplandriver_SelList(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplandriver_SelList";
    exec sql begin declare section;
    mdeviceplandriverS *d = a;
    exec sql end declare section;

    if ( a->FETCH_REL == SET_OPEN )
    {
       exec sql open CSelDev using :d->VERTRIEBSZENTRUMNR,
                                   :d->REGIONENTYP,
                                   :d->STARTZEIT,
                                   :d->VERTRIEBSZENTRUMNR,
                                   :d->REGIONENTYP,
                                   :d->ENDEZEIT,
                                   :d->VERTRIEBSZENTRUMNR,
                                   :d->REGIONENTYP;                                   
       if ( ( rc=CheckSql( fun, stError, "%s", "open CSelDev" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelDev;
      return CheckSql( fun, stError, "%s", "close CSelDev" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelDev into MDEVICEPLANDRIVER_ZEIGERSEL(d);
    return CheckSql( fun, stError, "%s", "fetch CSelDev" );
}

/* MDevicePlanDriver::SelWithSequenzNo ****************************************/

retClient Mdeviceplandriver_SelWithSequenzNo(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mdeviceplandriverS *d = a;
    exec sql end declare section;
    char *fun = "Mdeviceplandriver_SelWithSequenzNo";

    if ( bIsTrans ); /*only because preprozessor*/
    exec sql execute p_SelUniDev into MDEVICEPLANDRIVER_ZEIGERSEL(d)
                                using :d->SEQUENZNR, :d->FILIALNR;
    return CheckSql( fun, stError, "%s", "execute p_SelUniDev" );
}

/* MDevicePlanDriver::StartBrowse *********************************************/

retClient Mdeviceplandriver_StartBrowse(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplandriver_StartBrowse";
    exec sql begin declare section;
    char szBuf[2048];
    exec sql end declare section;

    if ( a || bIsTrans ); /*only because preprozessor*/

    /* sequenz scan */
    strcpy( szBuf, "select " );
    strcat( szBuf, MDEVICEPLANDRIVER_PLISTE ); 
    strcat( szBuf, " from modemanrufplan " );
    strcat( szBuf, "where ModemAnrufplan.filialnr in (" );
    strcat( szBuf, "select RegionArten.RegionTeilNr from RegionArten " );
    strcat( szBuf, "where RegionArten.RegionNr=? and " );
    strcat( szBuf, "RegionArten.RegionenTyp=? ) and " );
    strcat( szBuf, "ModemAnrufplan.sequenznr = 0 and " );	
    strcat( szBuf, "ModemAnrufplan.geraeteverw1=\"P\" and " );
    strcat( szBuf, "ModemAnrufplan.aktiv=\"1\" or " );
    strcat( szBuf, "(ModemAnrufplan.sequenznr!=0 and " );
    strcat( szBuf, "ModemAnrufplan.geraeteverw1=\"P\" and " );
    strcat( szBuf, "ModemAnrufplan.aktiv=\"1\" and " );
    strcat( szBuf, "((startzeit<? and filialnr in (" );
    strcat( szBuf, "select RegionArten.RegionTeilNr from RegionArten " );
    strcat( szBuf, "where RegionArten.RegionNr=? and " );
    strcat( szBuf, "RegionArten.RegionenTyp=? )) or " );
    strcat( szBuf, "(startzeit>? and filialnr in (" );
    strcat( szBuf, "select RegionArten.RegionTeilNr from RegionArten " );
    strcat( szBuf, "where RegionArten.RegionNr=? and " );
    strcat( szBuf, "RegionArten.RegionenTyp=? )))) " );
    strcat( szBuf, "order by modemanrufplan.sequenznr desc, " );
    strcat( szBuf, "modemanrufplan.geraeteid " );
 
    exec sql prepare p_SelDev from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelDev" ) ) != IS_OK )
        return rc;
    exec sql declare CSelDev cursor with hold for p_SelDev;
 
    /* unique select */
    strcpy( szBuf, "select " );
    strcat( szBuf, MDEVICEPLANDRIVER_PLISTE ); 
    strcat( szBuf, " from modemanrufplan " );
    strcat( szBuf, "where ModemAnrufplan.sequenznr=? " );
    strcat( szBuf, "and FilialNr=? " );

    exec sql prepare p_SelUniDev from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelUniDev" ) ) != IS_OK )
        return rc;

   /* direct update */
    strcpy( szBuf, "update ModemAnrufplan set " );
    strcat( szBuf, MDEVICEPLANDRIVER_UPDLISTE );
    strcat( szBuf, " where filialnr=? and " );
    strcat( szBuf, " geraeteid=? and " );
    strcat( szBuf, " sequenznr=? " );
    exec sql prepare p_UpdDirect from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_UpdDirect" ) ) != IS_OK )
        return rc;

   /* update */
    strcpy( szBuf, "update ModemAnrufplan set " );
    strcat( szBuf, MDEVICEPLANDRIVER_UPDLISTE );
    strcat( szBuf, " where current of CSelDev " );
    exec sql prepare p_UpdDev from :szBuf;
    return CheckSql( fun, stError, "%s", "prepare p_UpdDev" );
}

/* MDevicePlanDriver::UpdDevicePlan *******************************************/

retClient Mdeviceplandriver_UpdDevicePlan(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplandriver_UpdDevicePlan";
    exec sql begin declare section;
    mdeviceplandriverS *d = a;
    exec sql end declare section;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
 
    exec sql execute p_UpdDev using MDEVICEPLANDRIVER_ZEIGER(d);
    rc=CheckSql( fun, stError, "%s", "execute p_UpdDev" );
    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MDevicePlanDriver::UpdUMKDevicePlan ****************************************/

retClient Mdeviceplandriver_UpdUMKDevicePlan(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = FALSE;
    int iTrans = 0;
    char *fun = "Mdeviceplandriver_UpdUMKDevicePlan";
    exec sql begin declare section;
    mdeviceplandriverS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CUpdAktiv cursor with hold for
              select modemanrufplan.umknr
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	 and
                    ModemAnrufplan.umknr	 =	:d->UMKNR and
                    ModemAnrufplan.geraeteverw1	 =	"P"
              for update;
    exec sql open CUpdAktiv;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdAktiv" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       bInTrans = TRUE;
    }
    for(;;)
    {
       exec sql fetch CUpdAktiv;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdAktiv" ) ) != IS_OK )
          break;
       exec sql update modemanrufplan set modemanrufplan.aktiv = :d->AKTIV
                 where current of CUpdAktiv;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdAktiv" ) ) != IS_OK )
          break;
       if ( ( iTrans++ % 20 ) == 0 )
       {
          if ( bIsTrans )
          {
             if ( bInTrans )
             {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                   return rc;
             }
          }
          if ( bIsTrans )
          {
             if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                return rc;
             bInTrans = TRUE;
          }
       }
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

/* MDevicePlanDriver::UpdWithoutTransaction ***********************************/

retClient Mdeviceplandriver_UpdWithoutTransaction(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
/* Tarnsaktion muss übergeordnet gesteuert werden */
    retClient rc = IS_OK;
    char *fun = "Mdeviceplandriver_UpdDevicePlan";
    exec sql begin declare section;
    mdeviceplandriverS *d = a;
    exec sql end declare section;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
 
    exec sql execute p_UpdDev using MDEVICEPLANDRIVER_ZEIGER(d);
    rc=CheckSql( fun, stError, "%s", "execute p_UpdDev" );
    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    else if ( rc == IS_ERROR )
    {
       printf("Daten:%d/%s/%ld (%ld/%ld)", d->FILIALNR,d->GERAETEID, d->SEQUENZNR,sqlca.sqlcode,sqlca.sqlerrd[1]); 	
    }
   
    return rc;
}

/* MDevicePlanDriver::UpdWithoutTransactionDirect *****************************/

retClient Mdeviceplandriver_UpdWithoutTransactionDirect(mdeviceplandriverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplandriver_UpdWithoutTransactionDirect";
    exec sql begin declare section;
    mdeviceplandriverS *d = a;
    exec sql end declare section;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
 
    exec sql execute p_UpdDirect using MDEVICEPLANDRIVER_ZEIGER(d),
                                        :d->FILIALNR,
                                        :d->GERAETEID,
                                        :d->SCHLUESSEL;
    rc=CheckSql( fun, stError, "%s", "execute p_UpdDirect" );
    if ( rc == IS_ERROR )
    {
       printf( "Daten:%d/%s/%ld /%ld/%ld)", d->FILIALNR,d->GERAETEID, d->SCHLUESSEL,sqlca.sqlcode,sqlca.sqlerrd[1]); 	
    }
    else if ( rc == IS_OK )
       d->SCHLUESSEL = sqlca.sqlerrd[2];
    else
       d->SCHLUESSEL = 0;

    if ( bIsTrans && rc < 0 )
    {
       exec sql rollback work;
       return rc;
    }
    else if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MNumber.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:51:06 2022                                         */
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
#include "callplanday.h"

/* MNumber: Select ************************************************************/

/* MNumber::SelNumber *********************************************************/

retClient Mnumber_SelNumber(mnumberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mnumber_SelNumber";
    exec sql begin declare section;
    mnumberS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select nummer.nummertyp,
                     nummer.nummerwert,
                     nummer.nummermindest,
                     nummer.nummerhoechst,
                     nummer.nummerinkrement,
                     nummer.nummermodus
                into :d->NUMMERTYP,
                     :d->NUMMERWERT,
                     :d->NUMMERMINDEST,
                     :d->NUMMERHOECHST,
                     :d->NUMMERINKREMENT,
                     :d->NUMMERMODUS
                from NUMMER
              where nummer.nummertyp	 =	:d->NUMMERTYP;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MNumber: Insert ************************************************************/

/* MNumber::Insert ************************************************************/

retClient Mnumber_Insert(mnumberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mnumber_Insert";
    exec sql begin declare section;
    mnumberS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into nummer (nummertyp,
                     nummerwert,
                     nummermindest,
                     nummerhoechst,
                     nummerinkrement,
                     nummermodus)
        values (:d->NUMMERTYP,
                     :d->NUMMERWERT,
                     :d->NUMMERMINDEST,
                     :d->NUMMERHOECHST,
                     :d->NUMMERINKREMENT,
                     :d->NUMMERMODUS);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert nummer" ) ) != IS_OK )
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



/* MNumber: Update ************************************************************/

/* MNumber::UpdNumber *********************************************************/

retClient Mnumber_UpdNumber(mnumberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mnumber_UpdNumber";
    exec sql begin declare section;
    mnumberS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdNumber16 cursor with hold for
              select nummerwert
               from NUMMER
              where nummer.nummertyp	 =	:d->NUMMERTYP
              for update;
    exec sql open CUpdNumber16;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdNumber16" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdNumber16;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdNumber16" ) ) != IS_OK )
            break;
        exec sql update nummer set nummerwert = :d->NUMMERWERT where current of CUpdNumber16;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdNumber16" ) ) != IS_OK )
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



/* MNumber: Select ************************************************************/



/* MNumber: Other *************************************************************/

/* MNumber::Increment *********************************************************/

retClient Mnumber_Increment(mnumberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mnumber_Increment";

    exec sql begin declare section;
    mnumberS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    } 
    
    exec sql declare CUpdNumberO1 cursor with hold for
              select nummerwert, nummerinkrement, nummerhoechst, nummermindest
               from NUMMER
              where nummer.nummertyp	 =	:d->NUMMERTYP
              for update;

    exec sql open CUpdNumberO1;

    rc=CheckSql( fun, stError, "%s", "open CUpdNumberO1" );

    if ( rc == IS_NOTFOUND )
    {
       d->NUMMERWERT=1;
       d->NUMMERINKREMENT = 1;
       d->NUMMERHOECHST = 65535;
       d->NUMMERMINDEST = 0; 

       if ( (rc=(retClient)Mnumber_Insert(a, stError, FALSE)) != IS_OK )
       {
          exec sql rollback work;
          return rc;
       } 
    }

    if ( rc != IS_OK )
      return rc;

    exec sql fetch CUpdNumberO1 into :d->NUMMERWERT, :d->NUMMERINKREMENT, :d->NUMMERHOECHST, :d->NUMMERMINDEST;
    if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdNumberO1" ) ) != IS_OK )
       return rc;

    if ( (d->NUMMERWERT=d->NUMMERWERT+d->NUMMERINKREMENT) > d->NUMMERHOECHST )
       d->NUMMERWERT = d->NUMMERMINDEST;

    exec sql update nummer set nummerwert = :d->NUMMERWERT where current of CUpdNumberO1;
    if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdNumberO1" ) ) != IS_OK )
    {
       exec sql rollback work;
       return rc;
    } 

    if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    } 
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MTransaktion.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:51:12 2022                                         */
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
#include "callplanday.h"

/* MTransaktion: Select *******************************************************/



/* MTransaktion: Insert *******************************************************/



/* MTransaktion: Update *******************************************************/



/* MTransaktion: Select *******************************************************/



/* MTransaktion: Other ********************************************************/

/* MTransaktion::BeginTransaction *********************************************/

retClient Mtransaktion_BeginTransaction(mtransaktionS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MTransaction_BeginTransaction";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql begin work;
    return CheckSql( fun, stError, "%s", "begin work" );
}

/* MTransaktion::EndTransaction ***********************************************/

retClient Mtransaktion_EndTransaction(mtransaktionS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MTransaction_EndTransaction";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql commit work;
    return CheckSql( fun, stError, "%s", "commit work" );
}

/* MTransaktion::GetDate ******************************************************/

retClient Mtransaktion_GetDate(mtransaktionS *a, tError *stError, bool bIsTrans)
{
 char *fun = "Mtransaktion_GetDate";
   
  if ( bIsTrans ); 
  a->TM_DATE = ppGGetDate();
  
  sqlca.sqlcode = 0;
  if ( !a->TM_DATE )
     sqlca.sqlcode = -2;
  return CheckSql( fun, stError, "%s", "ppGGetDate" );
}

/* MTransaktion::GetDateTime **************************************************/

retClient Mtransaktion_GetDateTime(mtransaktionS *a, tError *stError, bool bIsTrans)
{
  char *fun = "Mtransaktion_GetDateTime";
   
  if ( bIsTrans ); 
  a->TM_DATE = ppGGetDate();
  a->TM_TIME = ppGGetTime();
  
  sqlca.sqlcode = 0;
  if ( !a->TM_DATE || !a->TM_TIME )
     sqlca.sqlcode = -2;
  return CheckSql( fun, stError, "%s", "ppGGetDate/ppGGetTime" );
}

/* MTransaktion::GetTime ******************************************************/

retClient Mtransaktion_GetTime(mtransaktionS *a, tError *stError, bool bIsTrans)
{
  char *fun = "Mtransaktion_GetTime";
   
  if ( bIsTrans ); 
  a->TM_TIME = ppGGetTime();
  
  sqlca.sqlcode = 0;
  if ( !a->TM_TIME )
     sqlca.sqlcode = -2;
  return CheckSql( fun, stError, "%s", "ppGGetTime" );
}

/* MTransaktion::RollbackTransaction ******************************************/

retClient Mtransaktion_RollbackTransaction(mtransaktionS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MTransaction_RollbackTransaction";

    if ( a || bIsTrans ); /*only because preprozessor*/
    exec sql rollback work;
    return CheckSql( fun, stError, "%s", "rollback work" );
}

/* MTransaktion::SetCommitedRead **********************************************/

retClient Mtransaktion_SetCommitedRead(mtransaktionS *a, tError *stError, bool bIsTrans)
{
    retClient rc;
    if ( a || bIsTrans ); /*only because preprozessor*/
    if ( (rc=(retClient)SetIsolation(COMMITTED_READ, stError ) ) != IS_OK )
    {
       /*WriteLogInfo( stError->spError, -1, 0 );*/
    }
    return rc;
}

/* MTransaktion::SetDirtyRead *************************************************/

retClient Mtransaktion_SetDirtyRead(mtransaktionS *a, tError *stError, bool bIsTrans)
{
    if ( a || bIsTrans ); /*only because preprozessor*/
    return SetIsolation( DIRTY_READ, stError );
}



