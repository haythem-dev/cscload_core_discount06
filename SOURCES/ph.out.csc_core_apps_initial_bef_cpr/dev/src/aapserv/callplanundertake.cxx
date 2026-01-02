/******************************************************************************/
/*                                                                            */
/* header  : MCallPlanUndertake.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:53:42 2022                                         */
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
#include "callplanundertake.h"

/* MCallPlanUndertake: Select *************************************************/

/* MCallPlanUndertake::SelCountAvailable **************************************/

retClient Mcallplanundertake_SelCountAvailable(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanundertake_SelCountAvailable";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select KundeAnrufplanTag.datum,
count(*)
                into :d->DATUM,
:d->KUNDENNR
                from KUNDEANRUFPLANTAG
              where KundeAnrufplanTag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeAnrufplanTag.datum =:d->DATUM and
                    KundeAnrufplanTag.RufEinstellung ="1"
                    group by KundeAnrufplanTag.datum;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCallPlanUndertake::SelCountAvailablePhon **********************************/

retClient Mcallplanundertake_SelCountAvailablePhon(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanundertake_SelCountAvailablePhon";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select count(*),
tagplan.datum
                into :d->KUNDENNR,
:d->DATUM
                from Tagplan
              where Tagplan.FilialNr  =	:d->VERTRIEBSZENTRUMNR	and
                    Tagplan.datum  =	:d->DATUM
                    group by Tagplan.datum;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCallPlanUndertake: Insert *************************************************/

/* MCallPlanUndertake::Insert *************************************************/

retClient Mcallplanundertake_Insert(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanundertake_Insert";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    {
    exec sql begin declare section;
    long lTime =ppGGetUniqueTime(50);
    long lDate = ppGGetDate();
    exec sql end declare section;
    exec sql insert into kundeanrufplanprot(VERTRIEBSZENTRUMNR,KUNDENNR,DATUM,URRUFZEIT,
                                                                 RUFZEIT,UHRZEIT,UID,DATUMANLAGE) values(
    :d->VERTRIEBSZENTRUMNR, :d->KUNDENNR, :d->DATUM, :d->URRUFZEIT, :d->RUFZEIT,:lTime,0,:lDate);
    if ( ( rc=CheckSql( fun, stError, "%s", "insert into kundeanruplanprot" ) ) != IS_OK )
    {
      if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
      {
         exec sql rollback work;
         return rc;
      }
      return rc;
  }
}
    exec sql insert into kundeanrufplantag (VertriebszentrumNr,
                     KundenNr,
                     datum,
                     UrRufzeit,
                     rufzeit,
                     UmkStatus,
                     AnrufStatus,
                     AnrufZaehler,
                     tagnr,
                     tourid,
                     STourDefinitiv,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     skdanrufgenerell)
        values (:d->VERTRIEBSZENTRUMNR,
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
                     :d->SKDANRUFGENERELL);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kundeanrufplantag" ) ) != IS_OK )
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



/* MCallPlanUndertake: Update *************************************************/



/* MCallPlanUndertake: Select *************************************************/

/* MCallPlanUndertake::DelAll *************************************************/

retClient Mcallplanundertake_DelAll(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcallplanundertake_DelAll";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAll2 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     UrRufzeit,
                     rufzeit,
                     UmkStatus,
                     AnrufStatus,
                     AnrufZaehler,
                     tagnr,
                     tourid,
                     STourDefinitiv,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     skdanrufgenerell
               from KUNDEANRUFPLANTAG
              where KundeAnrufplanTag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeAnrufplanTag.datum	 =	:d->DATUM
              for update;
    exec sql open CDelAll2;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAll2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAll2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAll2" ) ) != IS_OK )
            break;
        exec sql delete from kundeanrufplantag where current of CDelAll2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAll2" ) ) != IS_OK )
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

/* MCallPlanUndertake::DelAllOlder ********************************************/

retClient Mcallplanundertake_DelAllOlder(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcallplanundertake_DelAllOlder";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    exec sql declare CDelAllOlder3 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     UrRufzeit,
                     rufzeit,
                     UmkStatus,
                     AnrufStatus,
                     AnrufZaehler,
                     tagnr,
                     tourid,
                     STourDefinitiv,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     skdanrufgenerell
               from KUNDEANRUFPLANTAG
              where KundeAnrufplanTag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeAnrufplanTag.datum	<=	:d->DATUM	 and
                    KundeAnrufplanTag.datum	!=	:lDate
              for update;
    exec sql open CDelAllOlder3;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllOlder3" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllOlder3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllOlder3" ) ) != IS_OK )
            break;
        exec sql delete from kundeanrufplantag where current of CDelAllOlder3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllOlder3" ) ) != IS_OK )
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



/* MCallPlanUndertake: Other **************************************************/

/* MCallPlanUndertake::AIncludeDummy ******************************************/

retClient Mcallplanundertake_AIncludeDummy(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
}
#include "callplan.h"
void Mcallplanundertake_AIncludeDummyEnde()
{
}

/* MCallPlanUndertake::CheckAvailableEntries **********************************/

retClient Mcallplanundertake_CheckAvailableEntries(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    char *fun = "Mcallplanundertake_CheckAvailableEntries";
    exec sql begin declare section;
    exec sql end declare section;
    mcallplanloadS srvLoad;

    if ( bIsTrans ); /*only because preprozessor*/
    
    memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
    srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvLoad.LADEDATUM = a->DATUM;
    if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
    {
       return CheckSql( fun, stError, "%s", stError->spError );
    }
    a->DATUM = srvLoad.LADEDATUM;
    return (retClient)Mcallplanundertake_SelCountAvailable( a, stError, FALSE );
}

/* MCallPlanUndertake::CheckAvailableEntriesPhon ******************************/

retClient Mcallplanundertake_CheckAvailableEntriesPhon(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    char *fun = "Mcallplanundertake_CheckAvailableEntriesPhon";
    exec sql begin declare section;
    exec sql end declare section;
    mcallplanloadS srvLoad;

    if ( bIsTrans ); /*only because preprozessor*/

    memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
    srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvLoad.LADEDATUM = a->DATUM;
    if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
    {
       return CheckSql( fun, stError, "%s", stError->spError );
    }
    a->DATUM = srvLoad.LADEDATUM;
    return (retClient)Mcallplanundertake_SelCountAvailablePhon( a, stError, FALSE );
}

/* MCallPlanUndertake::DelAllPhon *********************************************/

retClient Mcallplanundertake_DelAllPhon(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplanphonS srvHist;
    exec sql end declare section;

    srvHist.FILIALNR = a->VERTRIEBSZENTRUMNR;
    srvHist.DATUM = a->DATUM;
    return Mcustomercallplanphon_DelAll(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::DelAllPhonOlder ****************************************/

retClient Mcallplanundertake_DelAllPhonOlder(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplanphonS srvHist;
    exec sql end declare section;

    srvHist.FILIALNR = a->VERTRIEBSZENTRUMNR;
    srvHist.DATUM = a->DATUM;
    return Mcustomercallplanphon_DelAllOlder(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::DelCallPlanLoadOlder ***********************************/

retClient Mcallplanundertake_DelCallPlanLoadOlder(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcallplanloadS srvLoad;
    exec sql end declare section;
 
    srvLoad.DATUM = a->DATUM;
    return Mcallplanload_DelCallPlanLoadOlder(&srvLoad, stError, bIsTrans);
}

/* MCallPlanUndertake::DelEvents **********************************************/

retClient Mcallplanundertake_DelEvents(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplandayhistS srvHist;
    exec sql end declare section;

    srvHist.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvHist.DATUM = a->DATUM;
    return Mcustomercallplandayhist_DelAll(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::DelEventsOlder *****************************************/

retClient Mcallplanundertake_DelEventsOlder(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplandayhistS srvHist;
    exec sql end declare section;

    srvHist.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvHist.DATUM = a->DATUM;
    return Mcustomercallplandayhist_DelAllOlder(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::DelEventsPhon ******************************************/

retClient Mcallplanundertake_DelEventsPhon(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplanphonprotS srvHist;
    exec sql end declare section;

    srvHist.DATUM = a->DATUM;
    srvHist.FILIALNR = a->VERTRIEBSZENTRUMNR;
    return Mcustomercallplanphonprot_DelAll(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::DelEventsPhonOlder *************************************/

retClient Mcallplanundertake_DelEventsPhonOlder(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;
    mcustomercallplanphonprotS srvHist;
    exec sql end declare section;

    srvHist.DATUM = a->DATUM;
    return Mcustomercallplanphonprot_DelAllOlder(&srvHist, stError, bIsTrans);
}

/* MCallPlanUndertake::UndertakeCallplan **************************************/

retClient Mcallplanundertake_UndertakeCallplan(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanundertake_UndertakeCallplan";
    exec sql begin declare section;
    mcallplanundertakeS *d;
    mcustomervacationS v;
    mcustomercallplanS srvPlan;
    mcallplanloadS srvLoad;
    exec sql end declare section;
    long lCount = 0; 

    if ( bIsTrans ); /*only because preprozessor*/
    
    memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
    srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvPlan.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvLoad.LADEDATUM = a->DATUM;
    srvPlan.TM_DATE = a->DATUM;
    if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
       return IS_ERROR;

    d = a;
    strcpy(srvPlan.RUFEINSTELLUNG,"1"); /* auto. rufe */
    if ( Mcustomercallplan_StartBrowseUndertake(&srvPlan, stError, FALSE ) == IS_ERROR )
       return IS_ERROR;

    srvPlan.FETCH_REL = SET_OPEN;
    srvPlan.TM_DATE = a->DATUM;
    if ( ( rc=Mcustomercallplan_SelListUndertake(&srvPlan, stError, FALSE )) == IS_ERROR )
       return rc;
    else if ( rc == IS_NOTFOUND )
       return IS_OK;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }

    do {
       	if ( ++lCount % 100 == 0 )
	{
	   if ( bIsTrans )
           {
              if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                 return rc;
       	      else if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                 return rc;
	   } 
	}

        d->VERTRIEBSZENTRUMNR = srvPlan.VERTRIEBSZENTRUMNR;
        d->KUNDENNR = srvPlan.KUNDENNR;
        d->DATUM = srvLoad.LADEDATUM;
        d->URRUFZEIT = srvPlan.URRUFZEIT;
        d->RUFZEIT = srvPlan.URRUFZEIT;
        d->UMKSTATUS = 0;
        d->ANRUFZAEHLER = 0;
        strcpy(d->TAGNR, srvPlan.TAGNR);
        strcpy(d->RUFPROTOKOLL, srvPlan.RUFPROTOKOLL );
        d->RUFSTEUERUNG = srvPlan.RUFSTEUERUNG;
        d->POOLNR = srvPlan.POOLNR;
        d->MODEMPOOLNR = srvPlan.MODEMPOOLNR;
        d->ANRUFSTATUS = 0;
        strcpy( d->RUFEINSTELLUNG, srvPlan.RUFEINSTELLUNG );
        strcpy( d->ANRUFTYP, srvPlan.ANRUFTYP );
        strcpy(d->SKDANRUFGENERELL, srvPlan.SKDANRUFGENERELL);
        strcpy( d->TOURID, " ");
        strcpy(d->STOURDEFINITIV, "0" );
        if ( memcmp(srvPlan.TOURID, " ", 1) != 0 && memcmp(srvPlan.TOURID, "0", 1) != 0 )
        {
           strcpy(d->STOURDEFINITIV, "1" );
           strcpy( d->TOURID, srvPlan.TOURID );
        }
        v.VERTRIEBSZENTRUMNR = srvPlan.VERTRIEBSZENTRUMNR;
        v.KUNDENNR = srvPlan.KUNDENNR;
        v.DATUMGUELTIGAB = srvLoad.LADEDATUM;
	if ( (rc=(retClient)Mcustomervacation_SelUni(&v, stError, FALSE)) != IS_NOTFOUND )
        {
           d->ANRUFSTATUS = 10;
        } 
	if ( (rc=(retClient)Mcallplanundertake_Insert(d, stError, FALSE)) == IS_ERROR )
	{
           if ( bIsTrans )
           {
              Rollback( fun, stError );
              return rc;
           } 
	}
        srvPlan.FETCH_REL = SET_FETCH;
    } while( (rc=(retClient)Mcustomercallplan_SelListUndertake(&srvPlan, stError, FALSE )) == IS_OK );
 

    if ( rc != IS_NOTFOUND )
       return rc;

    if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    } 

    return IS_OK;
}

/* MCallPlanUndertake::UndertakeCallplanPhon **********************************/

retClient Mcallplanundertake_UndertakeCallplanPhon(mcallplanundertakeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanundertake_UndertakeCallplanPhon";
    exec sql begin declare section;
    mcustomercallplanS srvPlan;
    mcallplanloadS srvLoad;
    mcustomervacationS v;
    mcustomercallplanphonS srvPhon;
    mcustomercallplanphonprotS srvPhonProt;
    exec sql end declare section;
    long lCount = 0; 
    const char szaWoche[7][3] = {"SO","MO","DI","MI","DO","FR","SA" };    
    const char szaRuf[4][3] = {"DP","DS","PH","DA" }; 

    memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
    if ( bIsTrans ); /*only because preprozessor*/

    srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvPlan.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvLoad.LADEDATUM = a->DATUM;
    srvPlan.TM_DATE = a->DATUM;
    if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
       return IS_ERROR;

    strcpy(srvPlan.RUFEINSTELLUNG,"0"); /* phonetische rufe */
    if ( Mcustomercallplan_StartBrowseUndertake(&srvPlan, stError, FALSE ) == IS_ERROR )
       return IS_ERROR;

    srvPlan.FETCH_REL = SET_OPEN;
    srvPlan.TM_DATE = a->DATUM;
    if ( ( rc=Mcustomercallplan_SelListUndertake(&srvPlan, stError, FALSE )) == IS_ERROR )
       return rc;
    else if ( rc == IS_NOTFOUND )
       return IS_OK;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }

    do {
       	if ( ++lCount % 100 == 0 )
	{
	   if ( bIsTrans )
           {
              if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                 return rc;
       	      else if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                 return rc;
	   } 
	}
        srvPhon.FILIALNR = a->VERTRIEBSZENTRUMNR;
        srvPhon.IDFNR = srvPlan.KUNDENNR; /*srvPlan.IDFNR;*/
        srvPhon.DATUM = srvLoad.LADEDATUM;
        srvPhon.RUFZEIT = srvPlan.URRUFZEIT;
        srvPhon.LFDAKTION = 0;
        srvPhon.PRIORITAET = srvPlan.RUFSTEUERUNG;
        strcpy( srvPhon.WOCHENTAG, srvPlan.TAGNR);
        srvPhon.POOLID = srvPlan.POOLNR;
        strcpy(srvPhon.ANRUFART, szaRuf[atoi(srvPlan.RUFPROTOKOLL)]);
        strcpy(srvPhon.MANUELL,"M");
        strcpy(srvPhon.STAGRUECKRUF, "0");
        strcpy(srvPhon.CALLINFO,srvPlan.BEMERKUNG);
        srvPhon.ZUGRIFF = 0;

        srvPhonProt.FILIALNR = a->VERTRIEBSZENTRUMNR;
        srvPhonProt.IDFNR = srvPlan.IDFNR;
        srvPhonProt.DATUM = srvLoad.LADEDATUM;
        srvPhonProt.RUFZEIT = srvPlan.URRUFZEIT;
        srvPhonProt.RUFZEITGEAENDERT = srvPlan.URRUFZEIT;
        srvPhonProt.STATUS = 7;
	srvPhonProt.ZEIT = ppGGetTime();
        v.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
        v.KUNDENNR = srvPlan.KUNDENNR;
        v.DATUMGUELTIGAB = srvLoad.LADEDATUM;
        strcpy(srvPhonProt.BEMERKUNG," ");
	if ( (rc=(retClient)Mcustomervacation_SelUni(&v, stError, FALSE)) != IS_NOTFOUND )
        {
           strcpy(srvPhonProt.BEMERKUNG,"Urlaub");
           srvPhonProt.STATUS = 4;
        } 

        if( (rc=(retClient)Mcustomercallplanphonprot_Insert(&srvPhonProt, stError, FALSE)) == IS_ERROR )
	{
           if ( bIsTrans )
           {
              Rollback( fun, stError );
              return rc;
           } 
	}
        else if( (rc=(retClient)Mcustomercallplanphon_Insert(&srvPhon, stError, FALSE)) == IS_ERROR )
	{
           if ( bIsTrans )
           {
              Rollback( fun, stError );
              return rc;
           } 
	}

        srvPlan.FETCH_REL = SET_FETCH;
    } while( (rc=(retClient)Mcustomercallplan_SelListUndertake(&srvPlan, stError, FALSE )) == IS_OK );
 

    if ( rc != IS_NOTFOUND )
       return rc;

    if ( bIsTrans )
    {
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    } 

    return IS_OK;
}



/******************************************************************************/
/*                                                                            */
/* header  : MHoliday.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:53:47 2022                                         */
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
#include "callplanundertake.h"

/* MHoliday: Select ***********************************************************/

/* MHoliday::SelCount *********************************************************/

retClient Mholiday_SelCount(mholidayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mholiday_SelCount";
    exec sql begin declare section;
    mholidayS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select count(*)
                into :d->VON_JAHR
                from FEIERTAG
              where feiertag.filialnr	 =	:d->FILIALNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    if ( d->VON_JAHR == 0 )
  return IS_NOTFOUND;
    return rc;
}

/* MHoliday::SelHoliday *******************************************************/

retClient Mholiday_SelHoliday(mholidayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mholiday_SelHoliday";
    exec sql begin declare section;
    mholidayS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelHoliday5 cursor with hold for
                  select feiertag.filialnr,
                     feiertag.modus,
                     feiertag.tag,
                     feiertag.von_jahr,
                     feiertag.bis_jahr,
                     feiertag.tagname,
                     feiertag.anteil
                from FEIERTAG
                  where feiertag.filialnr	 =	:d->FILIALNR;
        exec sql open CSelHoliday5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelHoliday5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelHoliday5;
        return CheckSql( fun, stError, "%s", "close CSelHoliday5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelHoliday5 into :d->FILIALNR,
                     :d->MODUS,
                     :d->TAG,
                     :d->VON_JAHR,
                     :d->BIS_JAHR,
                     :d->TAGNAME,
                     :d->ANTEIL;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelHoliday5" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MHoliday: Insert ***********************************************************/



/* MHoliday: Update ***********************************************************/



/* MHoliday: Select ***********************************************************/



/* MHoliday: Other ************************************************************/

/* MHoliday::EndBrowse ********************************************************/

retClient Mholiday_EndBrowse(mholidayS *a, tError *stError, bool bIsTrans)
{
retClient Mholiday_inline_GetBuffer(mholidayS *a, tError *stError, bool bIsTrans);

    a->FETCH_REL = -400; /* set memory free */
    return (retClient)Mholiday_inline_GetBuffer(a, stError, bIsTrans);
}

/* MHoliday::IsHoliday ********************************************************/

retClient Mholiday_IsHoliday(mholidayS *a, tError *stError, bool bIsTrans)
{
#include <gregdate.h>
#include <phodate.h>
   retClient Mholiday_inline_GetBuffer(mholidayS *a, tError *stError, bool bIsTrans);
   
   #define BK_FEST     0
   #define BK_OSTERN   1
   #define BK_BEWEG_1  2

   retClient rc;
   long gregdat = (long)a->ANTEIL;
   long ostern;
   long vgldatum;
   int  jahr, monat, tag;
   int  wotag;
   int  bew1_monat, bew1_woche, bew1_wochentag;

   if ( gregdat < 1 )
      return IS_ERROR;

   PhoDateToDmy ( gregdat, &tag, &monat, &jahr );
   gregdat = DmyToGreg ( tag, monat, jahr );
   GregToDmy ( gregdat, &tag, &monat, &jahr);
   ostern = GregOstern ( jahr );

   a->FETCH_REL = -200; /* initialisierung auf Anfang Liste */
   Mholiday_inline_GetBuffer(a, stError, bIsTrans); 
   a->FETCH_REL = -300;
   while((rc=(retClient)Mholiday_inline_GetBuffer(a, stError, bIsTrans)) == IS_OK )
   {
     if ( ( a->VON_JAHR == 0 || jahr >= a->VON_JAHR ) &&
	    ( a->BIS_JAHR == 0 || jahr <= a->BIS_JAHR )    )
     {
	    switch ( a->MODUS )
		{
	       case	BK_FEST   : if ( tag == a->TAG % 100 && monat == a->TAG / 100 )
						       return IS_OK;
	                        break;
	       case BK_OSTERN : if ( gregdat == ostern + a->TAG )
	 	                       return IS_OK;
                  	        break;
	       case BK_BEWEG_1:	bew1_monat     = a->TAG / 100;
	                        bew1_woche     = a->TAG % 100;
	                        bew1_wochentag = bew1_woche % 10;
	                        bew1_woche    /= 10;
	                        vgldatum       = DmyToGreg ( 1, bew1_monat, jahr);
	                        wotag          = WeekdayOfGreg ( vgldatum );

	                        if ( wotag < a->TAG )
							{
		                       vgldatum += bew1_wochentag - wotag + 7 * ( bew1_woche - 1 );
							}
	                        else
							{
		                       vgldatum += bew1_wochentag - wotag + 7 * bew1_woche;
							}

	                        if ( gregdat == vgldatum )
						       return IS_OK;
                            break;
		}
	 }
   }

   return rc;
}

/* MHoliday::StartBrowse ******************************************************/

retClient Mholiday_StartBrowse(mholidayS *a, tError *stError, bool bIsTrans)
{
retClient Mholiday_inline_GetBuffer(mholidayS *a, tError *stError, bool bIsTrans);

    a->FETCH_REL = -100; /* load the array */
    return (retClient)Mholiday_inline_GetBuffer(a, stError, bIsTrans);
}

/* MHoliday::inline_GetBuffer *************************************************/

retClient Mholiday_inline_GetBuffer(mholidayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "inline_GetBuffer";
    static mholidayS *m_pData = NULL;
    static int m_iMax;
    static int m_iCount = 0;

    if ( a->FETCH_REL == -100 )
    {
       int i;
       m_iCount = 0;     
       
       if ((rc=Mholiday_SelCount(a, stError, FALSE)) != IS_OK )
          return rc;
       else if ( m_pData )
       {
          return IS_OK; 
       }
       m_iMax = a->VON_JAHR; 
       m_pData = (mholidayS*)malloc(sizeof(mholidayS) * m_iMax);   

       m_pData[0].FETCH_REL = SET_OPEN;
       m_pData[0].FILIALNR = a->FILIALNR;
       for(i=0; i < m_iMax ; i++ )
       {
            rc=Mholiday_SelHoliday(&m_pData[i], stError, bIsTrans);
            if (rc != IS_OK)
            {
        	/*we need all m_iMax datasets*/
        	break;
            }
            if (i < m_iMax - 1)
            {
                  /*set next fetch to SET_FETCH*/
                  m_pData[i+1].FETCH_REL = SET_FETCH;
	    }
       }
       if ( rc == IS_ERROR )
          return (retClient)CheckSql( fun, stError, "%s", stError->spError ); 
    }
    else if ( a->FETCH_REL == -200 )
    { 
       m_iCount = 0;
    }
    else if ( a->FETCH_REL == -300 )
    { 
       /* kann leider keinen pointer auf pointer mimik verwenden */
       if ( m_iCount < m_iMax )
       {
          a->FILIALNR = m_pData[m_iCount].FILIALNR;
          a->MODUS    = m_pData[m_iCount].MODUS;
          a->TAG      = m_pData[m_iCount].TAG;
          a->VON_JAHR = m_pData[m_iCount].VON_JAHR;
          a->BIS_JAHR = m_pData[m_iCount].BIS_JAHR;
          strcpy(a->TAGNAME, m_pData[m_iCount].TAGNAME); 
          a->ANTEIL   = m_pData[m_iCount].ANTEIL;
          m_iCount++;
          return IS_OK;     
       }
       return IS_NOTFOUND;
    }
    else if ( a->FETCH_REL == -400 )
    {
       free(m_pData);
    }    

    return IS_OK;
}



