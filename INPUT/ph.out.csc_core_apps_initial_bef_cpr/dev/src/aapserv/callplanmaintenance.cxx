/******************************************************************************/
/*                                                                            */
/* header  : MCallParamater.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:51:53 2022                                         */
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
#include "callplanmaintenance.h"

/* MCallParamater: Select *****************************************************/

/* MCallParamater::SelCallParameter *******************************************/

retClient Mcallparamater_SelCallParameter(mcallparamaterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamater_SelCallParameter";
    exec sql begin declare section;
    mcallparamaterS *d;
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
                     anrufparameter.AnzRufVerschieben,
                     anrufparameter.MinRufVerschieben,
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
                     :d->ANZRUFVERSCHIEBEN,
                     :d->MINRUFVERSCHIEBEN,
                     :d->CALLPLANSTARTSTOP,
                     :d->STOPSTARTZEIT
                from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCallParamater::SelList ****************************************************/

retClient Mcallparamater_SelList(mcallparamaterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamater_SelList";
    exec sql begin declare section;
    mcallparamaterS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select anrufparameter.VertriebszentrumNr,
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
                     anrufparameter.AnzRufVerschieben,
                     anrufparameter.MinRufVerschieben,
                     anrufparameter.CallplanStartStop,
                     anrufparameter.StopStartZeit
                from ANRUFPARAMETER
                  where AnrufParameter.VertriebszentrumNr	 >	0
                        order by AnrufParameter.VertriebszentrumNr;
        exec sql open CSelList1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList1;
        return CheckSql( fun, stError, "%s", "close CSelList1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList1 into :d->VERTRIEBSZENTRUMNR,
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
                     :d->ANZRUFVERSCHIEBEN,
                     :d->MINRUFVERSCHIEBEN,
                     :d->CALLPLANSTARTSTOP,
                     :d->STOPSTARTZEIT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCallParamater: Insert *****************************************************/

/* MCallParamater::Insert *****************************************************/

retClient Mcallparamater_Insert(mcallparamaterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamater_Insert";
    exec sql begin declare section;
    mcallparamaterS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    /*reflection activated */

    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    strcpy( d->CHANGEID, "I" );
    /*reflection activated */

    exec sql insert into anrufparameter (VertriebszentrumNr,
                     RufzeitVerschieben,
                     AnzRufwiederholung,
                     ZeitFensterAuftrag,
                     ZeitAnzPosAuftrag,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     UmkRufwiederholung,
                     KabRufwiederholung,
                     AnzRufVerschieben,
                     MinRufVerschieben,
                     CallplanStartStop,
                     StopStartZeit)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->RUFZEITVERSCHIEBEN,
                     :d->ANZRUFWIEDERHOLUNG,
                     :d->ZEITFENSTERAUFTRAG,
                     :d->ZEITANZPOSAUFTRAG,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->UMKRUFWIEDERHOLUNG,
                     :d->KABRUFWIEDERHOLUNG,
                     :d->ANZRUFVERSCHIEBEN,
                     :d->MINRUFVERSCHIEBEN,
                     :d->CALLPLANSTARTSTOP,
                     :d->STOPSTARTZEIT);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert anrufparameter" ) ) != IS_OK )
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



/* MCallParamater: Update *****************************************************/

/* MCallParamater::UpdCallparameter *******************************************/

retClient Mcallparamater_UpdCallparameter(mcallparamaterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallparamater_UpdCallparameter";
    exec sql begin declare section;
    mcallparamaterS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdCallparameter2 cursor with hold for
              select VertriebszentrumNr,
                     RufzeitVerschieben,
                     AnzRufwiederholung,
                     ZeitFensterAuftrag,
                     ZeitAnzPosAuftrag,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     UmkRufwiederholung,
                     KabRufwiederholung,
                     AnzRufVerschieben,
                     MinRufVerschieben,
                     CallplanStartStop,
                     StopStartZeit
               from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR
              for update;
    exec sql open CUpdCallparameter2;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdCallparameter2" ) ) != IS_OK )
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
        exec sql fetch CUpdCallparameter2;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdCallparameter2" ) ) != IS_OK )
            break;
        exec sql update anrufparameter set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     RufzeitVerschieben = :d->RUFZEITVERSCHIEBEN,
                     AnzRufwiederholung = :d->ANZRUFWIEDERHOLUNG,
                     ZeitFensterAuftrag = :d->ZEITFENSTERAUFTRAG,
                     ZeitAnzPosAuftrag = :d->ZEITANZPOSAUFTRAG,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     UmkRufwiederholung = :d->UMKRUFWIEDERHOLUNG,
                     KabRufwiederholung = :d->KABRUFWIEDERHOLUNG,
                     AnzRufVerschieben = :d->ANZRUFVERSCHIEBEN,
                     MinRufVerschieben = :d->MINRUFVERSCHIEBEN,
                     CallplanStartStop = :d->CALLPLANSTARTSTOP,
                     StopStartZeit = :d->STOPSTARTZEIT where current of CUpdCallparameter2;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdCallparameter2" ) ) != IS_OK )
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



/* MCallParamater: Select *****************************************************/

/* MCallParamater::DelCallParameter *******************************************/

retClient Mcallparamater_DelCallParameter(mcallparamaterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallparamater_DelCallParameter";
    exec sql begin declare section;
    mcallparamaterS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelCallParameter3 cursor with hold for
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
                     AnzRufVerschieben,
                     MinRufVerschieben,
                     CallplanStartStop,
                     StopStartZeit
               from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR
              for update;
    exec sql open CDelCallParameter3;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelCallParameter3" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    exec sql update ANRUFPARAMETER set
              tm_date = :d->TM_DATE,
              tm_time = :d->TM_TIME,
              changeid = "D" 
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
    if ( ( rc=CheckSql( fun, stError,  "%s", "update reflectiontable: ANRUFPARAMETER" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
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
    /*reflection activated */

    for(;;)
    {
        exec sql fetch CDelCallParameter3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelCallParameter3" ) ) != IS_OK )
            break;
        exec sql delete from anrufparameter where current of CDelCallParameter3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelCallParameter3" ) ) != IS_OK )
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



/* MCallParamater: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCallParamterTimes.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:51:57 2022                                         */
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
#include "callplanmaintenance.h"

/* MCallParamterTimes: Select *************************************************/

/* MCallParamterTimes::SelParameter *******************************************/

retClient Mcallparamtertimes_SelParameter(mcallparamtertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamtertimes_SelParameter";
    exec sql begin declare section;
    mcallparamtertimesS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select anrufparameter.VertriebszentrumNr,
                     anrufparameter.RufAbweichungPH,
                     anrufparameter.RufAbweichungDP,
                     anrufparameter.RufAbweichungDS,
                     anrufparameter.tm_date,
                     anrufparameter.tm_time,
                     anrufparameter.loginId,
                     anrufparameter.changeId
                into :d->VERTRIEBSZENTRUMNR,
                     :d->RUFABWEICHUNGPH,
                     :d->RUFABWEICHUNGDP,
                     :d->RUFABWEICHUNGDS,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID
                from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCallParamterTimes: Insert *************************************************/

/* MCallParamterTimes::Insert *************************************************/

retClient Mcallparamtertimes_Insert(mcallparamtertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallparamtertimes_Insert";
    exec sql begin declare section;
    mcallparamtertimesS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    /*reflection activated */

    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    strcpy( d->CHANGEID, "I" );
    /*reflection activated */

    exec sql insert into anrufparameter (VertriebszentrumNr,
                     RufAbweichungPH,
                     RufAbweichungDP,
                     RufAbweichungDS,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->RUFABWEICHUNGPH,
                     :d->RUFABWEICHUNGDP,
                     :d->RUFABWEICHUNGDS,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert anrufparameter" ) ) != IS_OK )
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



/* MCallParamterTimes: Update *************************************************/

/* MCallParamterTimes::UpdParameter *******************************************/

retClient Mcallparamtertimes_UpdParameter(mcallparamtertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallparamtertimes_UpdParameter";
    exec sql begin declare section;
    mcallparamtertimesS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdParameter5 cursor with hold for
              select VertriebszentrumNr,
                     RufAbweichungPH,
                     RufAbweichungDP,
                     RufAbweichungDS,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId
               from ANRUFPARAMETER
              where AnrufParameter.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR
              for update;
    exec sql open CUpdParameter5;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdParameter5" ) ) != IS_OK )
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
        exec sql fetch CUpdParameter5;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdParameter5" ) ) != IS_OK )
            break;
        exec sql update anrufparameter set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     RufAbweichungPH = :d->RUFABWEICHUNGPH,
                     RufAbweichungDP = :d->RUFABWEICHUNGDP,
                     RufAbweichungDS = :d->RUFABWEICHUNGDS,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID where current of CUpdParameter5;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdParameter5" ) ) != IS_OK )
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



/* MCallParamterTimes: Select *************************************************/



/* MCallParamterTimes: Other **************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCallPlanLoad.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:04 2022                                         */
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
#include "callplanmaintenance.h"

/* MCallPlanLoad: Select ******************************************************/

/* MCallPlanLoad::SelCallPlanLoad *********************************************/

retClient Mcallplanload_SelCallPlanLoad(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanload_SelCallPlanLoad";
    exec sql begin declare section;
    mcallplanloadS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select ladeanrufplan.VertriebszentrumNr,
                     ladeanrufplan.datum,
                     ladeanrufplan.wochentag,
                     ladeanrufplan.LadeDatum,
                     ladeanrufplan.LadeVZ,
                     ladeanrufplan.bundesland,
                     ladeanrufplan.tourid,
                     ladeanrufplan.LadeZeitAb,
                     ladeanrufplan.LadeZeitBis
                into :d->VERTRIEBSZENTRUMNR,
                     :d->DATUM,
                     :d->WOCHENTAG,
                     :d->LADEDATUM,
                     :d->LADEVZ,
                     :d->BUNDESLAND,
                     :d->TOURID,
                     :d->LADEZEITAB,
                     :d->LADEZEITBIS
                from LADEANRUFPLAN
              where LadeAnrufplan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    LadeAnrufplan.LadeDatum	 =	:d->LADEDATUM;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    d->LADEKIPPZEIT=0;
    return rc;
}

/* MCallPlanLoad::SelList *****************************************************/

retClient Mcallplanload_SelList(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanload_SelList";
    exec sql begin declare section;
    mcallplanloadS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList7 cursor with hold for
                  select ladeanrufplan.VertriebszentrumNr,
                     ladeanrufplan.datum,
                     ladeanrufplan.wochentag,
                     ladeanrufplan.LadeDatum,
                     ladeanrufplan.LadeVZ,
                     ladeanrufplan.bundesland,
                     ladeanrufplan.tourid,
                     ladeanrufplan.LadeZeitAb,
                     ladeanrufplan.LadeZeitBis
                from LADEANRUFPLAN
                  where LadeAnrufplan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelList7;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList7" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList7;
        return CheckSql( fun, stError, "%s", "close CSelList7" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList7 into :d->VERTRIEBSZENTRUMNR,
                     :d->DATUM,
                     :d->WOCHENTAG,
                     :d->LADEDATUM,
                     :d->LADEVZ,
                     :d->BUNDESLAND,
                     :d->TOURID,
                     :d->LADEZEITAB,
                     :d->LADEZEITBIS;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList7" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCallPlanLoad: Insert ******************************************************/

/* MCallPlanLoad::Insert ******************************************************/

retClient Mcallplanload_Insert(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcallplanload_Insert";
    exec sql begin declare section;
    mcallplanloadS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into ladeanrufplan (VertriebszentrumNr,
                     datum,
                     wochentag,
                     LadeDatum,
                     LadeVZ,
                     bundesland,
                     tourid,
                     LadeZeitAb,
                     LadeZeitBis)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->DATUM,
                     :d->WOCHENTAG,
                     :d->LADEDATUM,
                     :d->LADEVZ,
                     :d->BUNDESLAND,
                     :d->TOURID,
                     :d->LADEZEITAB,
                     :d->LADEZEITBIS);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert ladeanrufplan" ) ) != IS_OK )
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



/* MCallPlanLoad: Update ******************************************************/

/* MCallPlanLoad::UpdCallPlanLoad *********************************************/

retClient Mcallplanload_UpdCallPlanLoad(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallplanload_UpdCallPlanLoad";
    exec sql begin declare section;
    mcallplanloadS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdCallPlanLoad8 cursor with hold for
              select wochentag,
                     LadeDatum,
                     LadeVZ,
                     bundesland,
                     tourid,
                     LadeZeitAb,
                     LadeZeitBis
               from LADEANRUFPLAN
              where LadeAnrufplan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    LadeAnrufplan.LadeDatum	 =	:d->LADEDATUM
              for update;
    exec sql open CUpdCallPlanLoad8;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdCallPlanLoad8" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdCallPlanLoad8;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdCallPlanLoad8" ) ) != IS_OK )
            break;
        exec sql update ladeanrufplan set wochentag = :d->WOCHENTAG,
                     LadeDatum = :d->LADEDATUM,
                     LadeVZ = :d->LADEVZ,
                     bundesland = :d->BUNDESLAND,
                     tourid = :d->TOURID,
                     LadeZeitAb = :d->LADEZEITAB,
                     LadeZeitBis = :d->LADEZEITBIS where current of CUpdCallPlanLoad8;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdCallPlanLoad8" ) ) != IS_OK )
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



/* MCallPlanLoad: Select ******************************************************/

/* MCallPlanLoad::DelCallPlanLoad *********************************************/

retClient Mcallplanload_DelCallPlanLoad(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcallplanload_DelCallPlanLoad";
    exec sql begin declare section;
    mcallplanloadS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelCallPlanLoad9 cursor with hold for
              select VertriebszentrumNr,
                     datum,
                     wochentag,
                     LadeDatum,
                     LadeVZ,
                     bundesland,
                     tourid,
                     LadeZeitAb,
                     LadeZeitBis
               from LADEANRUFPLAN
              where LadeAnrufplan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    LadeAnrufplan.LadeDatum	 =	:d->LADEDATUM
              for update;
    exec sql open CDelCallPlanLoad9;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelCallPlanLoad9" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelCallPlanLoad9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelCallPlanLoad9" ) ) != IS_OK )
            break;
        exec sql delete from ladeanrufplan where current of CDelCallPlanLoad9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelCallPlanLoad9" ) ) != IS_OK )
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

/* MCallPlanLoad::DelCallPlanLoadOlder ****************************************/

retClient Mcallplanload_DelCallPlanLoadOlder(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcallplanload_DelCallPlanLoadOlder";
    exec sql begin declare section;
    mcallplanloadS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    exec sql declare CDelCallPlanLoadOlder10 cursor with hold for
              select VertriebszentrumNr,
                     datum,
                     wochentag,
                     LadeDatum,
                     LadeVZ,
                     bundesland,
                     tourid,
                     LadeZeitAb,
                     LadeZeitBis
               from LADEANRUFPLAN
              where LadeAnrufplan.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR  and
                    LadeAnrufplan.LadeDatum <= :d->LADEDATUM  and
                    LadeAnrufplan.LadeDatum != :lDate
              for update;
    exec sql open CDelCallPlanLoadOlder10;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelCallPlanLoadOlder10" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelCallPlanLoadOlder10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelCallPlanLoadOlder10" ) ) != IS_OK )
            break;
        exec sql delete from ladeanrufplan where current of CDelCallPlanLoadOlder10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelCallPlanLoadOlder10" ) ) != IS_OK )
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



/* MCallPlanLoad: Other *******************************************************/

/* MCallPlanLoad::AIncludeDummy ***********************************************/

retClient Mcallplanload_AIncludeDummy(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
}
#include "callplan.h"
void Mcallplanload_AIncludeDummyEnde()
{
}

/* MCallPlanLoad::GetInitializeData *******************************************/

retClient Mcallplanload_GetInitializeData(mcallplanloadS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    long lTimeLimit = a->LADEKIPPZEIT == 0 ? 70000 : a->LADEKIPPZEIT; 
    char *fun = "Mcallplanload_GetInitializeData";
    long lDate = a->LADEDATUM;

    if ( bIsTrans ); /*only because preprozessor*/
    if ( a->LADEDATUM == 0 && ppGGetTime() > lTimeLimit ) /* current day*/
       a->LADEDATUM = ppGAddDate( ppGGetDate(), 1, stError->spError );
    else if ( a->LADEDATUM == 0 && ppGGetTime() <= lTimeLimit ) /* get the last day */
       a->LADEDATUM = ppGGetDate();

    if(lDate == 0)
    {
       mholidayS srvHoliday;
       lDate = a->LADEDATUM;
       srvHoliday.FILIALNR = a->VERTRIEBSZENTRUMNR;
       if ( (rc=(retClient)Mholiday_StartBrowse(&srvHoliday, stError, FALSE)) == IS_ERROR )
          return rc;
       for(;;)
       {
          if (ppGGetWeekDay(lDate, stError->spError ) == 0 )
          {
             /* it's sunday */
             a->LADEDATUM = ppGAddDate( lDate, +1, stError->spError );
          }
          else
          {
             a->LADEDATUM = lDate;
          }
          srvHoliday.ANTEIL = a->LADEDATUM;
          if ( Mholiday_IsHoliday(&srvHoliday, stError, FALSE ) == IS_NOTFOUND )
             break;
          lDate = ppGAddDate( a->LADEDATUM, +1, stError->spError );
       } /* end for */
    }

    if ( (rc=Mcallplanload_SelCallPlanLoad(a, stError, FALSE)) == IS_ERROR )
       return CheckSql( fun, stError, "%s", stError->spError );
    else if ( rc == IS_NOTFOUND )
    {
       sprintf( a->WOCHENTAG, "%ld", ppGGetWeekDay( a->LADEDATUM, stError->spError ));
       a->LADEZEITAB = 0;
       a->LADEZEITBIS = 240000;
       a->LADEVZ = 0;
    }
    if ( a->LADEZEITBIS == 0 )
       a->LADEZEITBIS = 240000;
    return IS_OK;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlan.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:19 2022                                         */
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
#include "callplanmaintenance.h"

/* MCustomerCallPlan: Select **************************************************/

/* MCustomerCallPlan::SelAllDisabled ******************************************/

retClient Mcustomercallplan_SelAllDisabled(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_SelAllDisabled";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select count(*)
                into :d->LOGINID
                from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	 and
                    KundeMasterPlan.AnrufTyp	 <	:d->ANRUFTYP;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerCallPlan::SelList *************************************************/

retClient Mcustomercallplan_SelList(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_SelList";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList12 cursor with hold for
                  select kunde.idfnr,
                     kundemasterplan.VertriebszentrumNr,
                     kundemasterplan.KundenNr,
                     kundemasterplan.tagnr,
                     kundemasterplan.UrRufzeit,
                     kundemasterplan.RufProtokoll,
                     kundemasterplan.RufSteuerung,
                     kundemasterplan.poolnr,
                     kundemasterplan.ModemPoolNr,
                     kundemasterplan.RufEinstellung,
                     kundemasterplan.AnrufTyp,
                     kundemasterplan.tm_date,
                     kundemasterplan.tm_time,
                     kundemasterplan.loginId,
                     kundemasterplan.changeId,
                     kundemasterplan.tourid,
                     kundemasterplan.skdanrufgenerell,
                     kundemasterplan.bemerkung
                from KUNDEMASTERPLAN, KUNDE
                  where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                        KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                        KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                        KundeMasterPlan.VertriebszentrumNr	 = Kunde.VertriebszentrumNr	and
                        KundeMasterPlan.KundenNr = Kunde.KundenNr
                        order by KundeMasterPlan.UrRufzeit;
        exec sql open CSelList12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList12" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList12;
        return CheckSql( fun, stError, "%s", "close CSelList12" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList12 into :d->IDFNR,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TAGNR,
                     :d->URRUFZEIT,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->TOURID,
                     :d->SKDANRUFGENERELL,
                     :d->BEMERKUNG;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList12" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerCallPlan::SelListHist *********************************************/

retClient Mcustomercallplan_SelListHist(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_SelListHist";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    /* used for printing */
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListHist13 cursor with hold for
                  select kunde.idfnr,
                     kundemasterplan.VertriebszentrumNr,
                     kundemasterplan.KundenNr,
                     kundemasterplan.tagnr,
                     kundemasterplan.UrRufzeit,
                     kundemasterplan.RufProtokoll,
                     kundemasterplan.RufSteuerung,
                     kundemasterplan.poolnr,
                     kundemasterplan.ModemPoolNr,
                     kundemasterplan.RufEinstellung,
                     kundemasterplan.AnrufTyp,
                     kundemasterplan.tm_date,
                     kundemasterplan.tm_time,
                     kundemasterplan.loginId,
                     kundemasterplan.changeId,
                     kundemasterplan.tourid,
                     kundemasterplan.skdanrufgenerell,
                     kundemasterplan.bemerkung
                from KUNDEMASTERPLAN, KUNDE
                  where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                        KundeMasterPlan.VertriebszentrumNr	 = Kunde.VertriebszentrumNr	and
                        KundeMasterPlan.KundenNr = Kunde.KundenNr
                        order by KundeMasterPlan.tagnr, KundeMasterPlan.UrRufzeit, KundeMasterPlan.RufProtokoll;
        exec sql open CSelListHist13;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHist13" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListHist13;
        return CheckSql( fun, stError, "%s", "close CSelListHist13" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListHist13 into :d->IDFNR,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TAGNR,
                     :d->URRUFZEIT,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->TOURID,
                     :d->SKDANRUFGENERELL,
                     :d->BEMERKUNG;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListHist13" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerCallPlan: Insert **************************************************/

/* MCustomerCallPlan::Insert **************************************************/

retClient Mcustomercallplan_Insert(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_Insert";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->BEMERKUNG);
    if ( *d->BEMERKUNG == '\0' )
        strcpy( d->BEMERKUNG, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    /*reflection activated */

    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    strcpy( d->CHANGEID, "I" );
    /*reflection activated */

     d->TM_TIME = ppGGetTime();
 d->TM_DATE = ppGGetDate();
    exec sql insert into kundemasterplan (VertriebszentrumNr,
                     KundenNr,
                     tagnr,
                     UrRufzeit,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TAGNR,
                     :d->URRUFZEIT,
                     :d->RUFPROTOKOLL,
                     :d->RUFSTEUERUNG,
                     :d->POOLNR,
                     :d->MODEMPOOLNR,
                     :d->RUFEINSTELLUNG,
                     :d->ANRUFTYP,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->TOURID,
                     :d->SKDANRUFGENERELL,
                     :d->BEMERKUNG);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kundemasterplan" ) ) != IS_OK )
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



/* MCustomerCallPlan: Update **************************************************/

/* MCustomerCallPlan::UpdAllCustomerCallPlan **********************************/

retClient Mcustomercallplan_UpdAllCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdAllCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    d->TM_TIME = ppGGetTime();
d->TM_DATE = ppGGetDate();
    ppGStripLast(d->BEMERKUNG);
    if ( *d->BEMERKUNG == '\0' )
        strcpy( d->BEMERKUNG, " " );


    exec sql declare CUpdAllCustomerCallPlan14 cursor with hold for
              select RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT and
                    KundeMasterPlan.tagnr	> 0
              for update;
    exec sql open CUpdAllCustomerCallPlan14;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdAllCustomerCallPlan14" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdAllCustomerCallPlan14;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdAllCustomerCallPlan14" ) ) != IS_OK )
            break;
        exec sql update kundemasterplan set RufProtokoll = :d->RUFPROTOKOLL,
                     RufSteuerung = :d->RUFSTEUERUNG,
                     poolnr = :d->POOLNR,
                     ModemPoolNr = :d->MODEMPOOLNR,
                     RufEinstellung = :d->RUFEINSTELLUNG,
                     AnrufTyp = :d->ANRUFTYP,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     tourid = :d->TOURID,
                     skdanrufgenerell = :d->SKDANRUFGENERELL,
                     bemerkung = :d->BEMERKUNG where current of CUpdAllCustomerCallPlan14;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdAllCustomerCallPlan14" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 7 ) == 0 )
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

/* MCustomerCallPlan::UpdAllWithoutSaturday ***********************************/

retClient Mcustomercallplan_UpdAllWithoutSaturday(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdAllWithoutSaturday";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

     d->TM_TIME = ppGGetTime();
 d->TM_DATE = ppGGetDate();
    ppGStripLast(d->BEMERKUNG);
    if ( *d->BEMERKUNG == '\0' )
        strcpy( d->BEMERKUNG, " " );


    exec sql declare CUpdAllWithoutSaturday15 cursor with hold for
              select RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT and
                    KundeMasterPlan.tagnr	> 0 and
                    KundeMasterPlan.tagnr	< 6
              for update;
    exec sql open CUpdAllWithoutSaturday15;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdAllWithoutSaturday15" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdAllWithoutSaturday15;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdAllWithoutSaturday15" ) ) != IS_OK )
            break;
        exec sql update kundemasterplan set RufProtokoll = :d->RUFPROTOKOLL,
                     RufSteuerung = :d->RUFSTEUERUNG,
                     poolnr = :d->POOLNR,
                     ModemPoolNr = :d->MODEMPOOLNR,
                     RufEinstellung = :d->RUFEINSTELLUNG,
                     AnrufTyp = :d->ANRUFTYP,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     tourid = :d->TOURID,
                     skdanrufgenerell = :d->SKDANRUFGENERELL,
                     bemerkung = :d->BEMERKUNG where current of CUpdAllWithoutSaturday15;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdAllWithoutSaturday15" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 6 ) == 0 )
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

/* MCustomerCallPlan::UpdCustomerCallPlan *************************************/

retClient Mcustomercallplan_UpdCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomercallplan_UpdCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->BEMERKUNG);
    if ( *d->BEMERKUNG == '\0' )
        strcpy( d->BEMERKUNG, " " );


    exec sql declare CUpdCustomerCallPlan16 cursor with hold for
              select RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT
              for update;
    exec sql open CUpdCustomerCallPlan16;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdCustomerCallPlan16" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    exec sql insert into MKundemasterPlan select * 
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: MKundemasterPlan" ) ) != IS_OK )
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
        exec sql fetch CUpdCustomerCallPlan16;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdCustomerCallPlan16" ) ) != IS_OK )
            break;
        exec sql update kundemasterplan set RufProtokoll = :d->RUFPROTOKOLL,
                     RufSteuerung = :d->RUFSTEUERUNG,
                     poolnr = :d->POOLNR,
                     ModemPoolNr = :d->MODEMPOOLNR,
                     RufEinstellung = :d->RUFEINSTELLUNG,
                     AnrufTyp = :d->ANRUFTYP,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     tourid = :d->TOURID,
                     skdanrufgenerell = :d->SKDANRUFGENERELL,
                     bemerkung = :d->BEMERKUNG where current of CUpdCustomerCallPlan16;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdCustomerCallPlan16" ) ) != IS_OK )
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



/* MCustomerCallPlan: Select **************************************************/

/* MCustomerCallPlan::DelAllCustomerCallPlan **********************************/

retClient Mcustomercallplan_DelAllCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_DelAllCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAllCustomerCallPlan17 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     tagnr,
                     UrRufzeit,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT
              for update;
    exec sql open CDelAllCustomerCallPlan17;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllCustomerCallPlan17" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllCustomerCallPlan17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllCustomerCallPlan17" ) ) != IS_OK )
            break;
        exec sql delete from kundemasterplan where current of CDelAllCustomerCallPlan17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllCustomerCallPlan17" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 8 ) == 0 )
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

/* MCustomerCallPlan::DelAllWithoutSaturday ***********************************/

retClient Mcustomercallplan_DelAllWithoutSaturday(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_DelAllWithoutSaturday";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAllWithoutSaturday18 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     tagnr,
                     UrRufzeit,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT and
                    KundeMasterPlan.tagnr	> 0 and
                    KundeMasterPlan.tagnr	< 6
              for update;
    exec sql open CDelAllWithoutSaturday18;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllWithoutSaturday18" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllWithoutSaturday18;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllWithoutSaturday18" ) ) != IS_OK )
            break;
        exec sql delete from kundemasterplan where current of CDelAllWithoutSaturday18;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllWithoutSaturday18" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 8 ) == 0 )
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

/* MCustomerCallPlan::DelCallPlanCompletly ************************************/

retClient Mcustomercallplan_DelCallPlanCompletly(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_DelCallPlanCompletly";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelCallPlanCompletly19 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     tagnr,
                     UrRufzeit,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR
              for update;
    exec sql open CDelCallPlanCompletly19;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelCallPlanCompletly19" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelCallPlanCompletly19;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelCallPlanCompletly19" ) ) != IS_OK )
            break;
        exec sql delete from kundemasterplan where current of CDelCallPlanCompletly19;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelCallPlanCompletly19" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 350 ) == 0 )
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

/* MCustomerCallPlan::DelCustomerCallPlan *************************************/

retClient Mcustomercallplan_DelCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_DelCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelCustomerCallPlan20 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     tagnr,
                     UrRufzeit,
                     RufProtokoll,
                     RufSteuerung,
                     poolnr,
                     ModemPoolNr,
                     RufEinstellung,
                     AnrufTyp,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     tourid,
                     skdanrufgenerell,
                     bemerkung
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT
              for update;
    exec sql open CDelCustomerCallPlan20;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelCustomerCallPlan20" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    exec sql update KUNDEMASTERPLAN set
              tm_date = :d->TM_DATE,
              tm_time = :d->TM_TIME,
              changeid = "D" 
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT;
    if ( ( rc=CheckSql( fun, stError,  "%s", "update reflectiontable: KUNDEMASTERPLAN" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    exec sql insert into MKundemasterPlan select * 
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->URRUFZEIT;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: MKundemasterPlan" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    /*reflection activated */

    for(;;)
    {
        exec sql fetch CDelCustomerCallPlan20;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelCustomerCallPlan20" ) ) != IS_OK )
            break;
        exec sql delete from kundemasterplan where current of CDelCustomerCallPlan20;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelCustomerCallPlan20" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 8 ) == 0 )
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



/* MCustomerCallPlan: Other ***************************************************/

/* MCustomerCallPlan::InsertAll ***********************************************/

retClient Mcustomercallplan_InsertAll(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Mcustomercallplan_InsertAll";
int i;

if ( bIsTrans )
{
   if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
}

for( i = 1; i < 7; i++ )
{
 sprintf( a->TAGNR, "%d", i); 
 if ( ( rc = (retClient)Mcustomercallplan_Insert(a, stError, FALSE)) != IS_OK )
 {
     exec sql rollback work;
     return rc;
 }
}

if ( bIsTrans )
{
   if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
}
return rc;
}

/* MCustomerCallPlan::InsertAllWithoutSaturday ********************************/

retClient Mcustomercallplan_InsertAllWithoutSaturday(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Mcustomercallplan_InsertAll";
int i;

if ( bIsTrans )
{
   if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
}

for( i = 1; i < 6; i++ )
{
 sprintf( a->TAGNR, "%d", i); 
 if ( ( rc = (retClient)Mcustomercallplan_Insert(a, stError, FALSE)) != IS_OK )
 {
     exec sql rollback work;
     return rc;
 }
}

if ( bIsTrans )
{
   if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
}
return rc;
}

/* MCustomerCallPlan::SelListUndertake ****************************************/

retClient Mcustomercallplan_SelListUndertake(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_SelListUndertake";
    exec sql begin declare section;
    mcustomercallplanS *d = a;
    mcallplanloadS srvLoad;
    char SKDANRUFGENERELL[2]; 
    exec sql end declare section;
 
    /* es werden alle Rufe in den Tagesanrufplan übernommen,
       (z.Zt. nur wegen der Anzeige Rufe des Kunden in Kundenanzeige */
    if ( *d->RUFEINSTELLUNG == '1' )
    {
       strcpy( d->RUFEINSTELLUNG, "a" );
    }
    else if ( *d->RUFEINSTELLUNG == '0' )
    {
       strcpy( d->RUFEINSTELLUNG, "1" );
    }

    if ( bIsTrans ); /*only because preprozessor*/

    if ( a->FETCH_REL == SET_OPEN )
    {
       memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
       srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
       srvLoad.DATUM = a->TM_DATE;
       srvLoad.LADEDATUM = a->TM_DATE;
       if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
          return IS_ERROR;
       
       if ( srvLoad.LADEVZ > 0 && srvLoad.LADEVZ != a->VERTRIEBSZENTRUMNR )
       {
           exec sql open CSelLoadData using :srvLoad.WOCHENTAG,
		                            :d->VERTRIEBSZENTRUMNR,
		                            :srvLoad.LADEZEITAB,
                                            :srvLoad.LADEZEITBIS,
                                            :d->RUFEINSTELLUNG,
                                            :srvLoad.WOCHENTAG,
					    :srvLoad.LADEVZ,
					    :srvLoad.BUNDESLAND,
                                            :d->RUFEINSTELLUNG,
                                            :srvLoad.LADEZEITAB,
                                            :srvLoad.LADEZEITBIS; 	
       }
       else
       {	
           exec sql open CSelLoadData using :srvLoad.WOCHENTAG,
	                                    :d->VERTRIEBSZENTRUMNR,
	                                    :srvLoad.LADEZEITAB,
                                            :srvLoad.LADEZEITBIS,
                                            :d->RUFEINSTELLUNG;
       }
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
      exec sql close CSelLoadData;
      return CheckSql( fun, stError, "%s", "close CSelDataX" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelLoadData into MCUSTOMERCALLPLAN_ZEIGERSEL(d),
                                     :SKDANRUFGENERELL;
    if ( (rc=CheckSql( fun, stError, "%s", "fetch CSelLoadData" )) != IS_OK )
       return rc;
    else if ( *SKDANRUFGENERELL == '1' )
    {
       strcpy( d->SKDANRUFGENERELL, SKDANRUFGENERELL );
    }
    
    return rc;
}

/* MCustomerCallPlan::StartBrowseUndertake ************************************/

retClient Mcustomercallplan_StartBrowseUndertake(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char buf2[40];
    char *fun = "Mcustomercallplan_StartBrowseUndertake";
    exec sql begin declare section;
    char szBuf[2560];
    char szBufAdd[1024];
    exec sql end declare section;
	
    mcallplanloadS srvLoad;

    if ( bIsTrans ); /*only because preprozessor*/
    memset((char*)&srvLoad, 0, sizeof(mcallplanloadS));
    srvLoad.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    srvLoad.DATUM = a->TM_DATE;
    srvLoad.LADEDATUM = a->TM_DATE;

    if ( Mcallplanload_GetInitializeData( &srvLoad, stError, FALSE ) == IS_ERROR )
       return IS_ERROR;
    sprintf( buf2, "kundenotdienstplan.datum= %ld ",srvLoad.LADEDATUM );

    /* sequenz scan */
    strcpy( szBuf, "select " );
    strcat( szBuf, MCUSTOMERCALLPLAN_PLISTE ); 
    strcat( szBuf, ",kundeschalter.SKDANRUFGENERELL " ); 
    strcat( szBuf, " from KUNDEMASTERPLAN, KUNDE, KUNDESCHALTER " );
    strcat( szBuf, "where (kundemasterplan.tagnr=? and " );
    strcat( szBuf, "kunde.vertriebszentrumnr=? and " );
    strcat( szBuf, "kunde.vertriebszentrumnr=kundemasterplan.vertriebszentrumnr and " );
    strcat( szBuf, "kundeschalter.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBuf, "kundeschalter.kundennr=kunde.kundennr and " );
    strcat( szBuf, "kundeschalter.skdkundeaegesperrt = \"0\" and " );
    strcat( szBuf, "kunde.kundennr=kundemasterplan.kundennr and " );	
    strcat( szBuf, "kundemasterplan.anruftyp < \"3\" and " );
    strcat( szBuf, "kundemasterplan.urrufzeit>=? and " );
    strcat( szBuf, "kundemasterplan.urrufzeit<=? and " );
    strcat( szBuf, "kundemasterplan.rufeinstellung!=? and " );
    strcat( szBuf, "(kundemasterplan.anruftyp = \"0\" or " );
    strcat( szBuf, "(kundemasterplan.anruftyp = \"1\" and " );
    strcat( szBuf, "EXISTS " );
    strcat( szBuf, "(select * from KUNDENOTDIENSTPLAN " );
    strcat( szBuf, "where kundenotdienstplan.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBuf, "kundenotdienstplan.kundennr=kunde.kundennr and " );
    strcat( szBuf, buf2 );
    strcat( szBuf, " )) or " );
    strcat( szBuf, "(kundemasterplan.anruftyp = \"2\" and " );
    strcat( szBuf, "NOT EXISTS " );
    strcat( szBuf, "(select * from KUNDENOTDIENSTPLAN " );
    strcat( szBuf, "where kundenotdienstplan.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBuf, "kundenotdienstplan.kundennr=kunde.kundennr and " );
    strcat( szBuf, buf2 );
    strcat( szBuf, " )) ) )" );
 
    strcpy( szBufAdd, " or (" );
    strcat( szBufAdd, "kundemasterplan.tagnr=? and " );
    strcat( szBufAdd, "kunde.vertriebszentrumnr=? and " );
    strcat( szBufAdd, "kunde.vertriebszentrumnr=kundemasterplan.vertriebszentrumnr and " );
    strcat( szBufAdd, "kundeschalter.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBufAdd, "kundeschalter.kundennr=kunde.kundennr and " );
    strcat( szBufAdd, "kundeschalter.skdkundeaegesperrt = \"0\" and " );
    strcat( szBufAdd, "kunde.kundennr=kundemasterplan.kundennr and " );	
    strcat( szBufAdd, "bundesland=? and " );
    strcat( szBufAdd, "kundemasterplan.anruftyp < \"3\" and " );
    strcat( szBufAdd, "kundemasterplan.rufeinstellung!=? and " );
    strcat( szBufAdd, "kundemasterplan.urrufzeit>=? and " );
    strcat( szBufAdd, "kundemasterplan.urrufzeit<=? and " );
    strcat( szBufAdd, "(kundemasterplan.anruftyp = \"0\" or " );
    strcat( szBufAdd, "(kundemasterplan.anruftyp = \"1\" and " );
    strcat( szBufAdd, "EXISTS " );
    strcat( szBufAdd, "(select * from KUNDENOTDIENSTPLAN " );
    strcat( szBufAdd, "where kundenotdienstplan.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBufAdd, "kundenotdienstplan.kundennr=kunde.kundennr and " );
    strcat( szBufAdd, buf2 );
    strcat( szBufAdd, " )) or " );
    strcat( szBufAdd, "(kundemasterplan.anruftyp = \"2\" and " );
    strcat( szBufAdd, "NOT EXISTS " );
    strcat( szBufAdd, "(select * from KUNDENOTDIENSTPLAN " );
    strcat( szBufAdd, "where kundenotdienstplan.vertriebszentrumnr=kunde.vertriebszentrumnr and " );
    strcat( szBufAdd, "kundenotdienstplan.kundennr=kunde.kundennr and " );
    strcat( szBufAdd, buf2 );
    strcat( szBufAdd, " )) ) )" );

    if ( srvLoad.LADEVZ > 0 && srvLoad.LADEVZ != a->VERTRIEBSZENTRUMNR )
    {
       strcat( szBuf, szBufAdd ); 
    }	
    
    strcat( szBuf, "order by kundemasterplan.urrufzeit,kundemasterplan.kundennr");
	
    exec sql prepare p_SelLoadData from :szBuf;
    if ( ( rc=CheckSql( fun, stError, "%s", "prepare p_SelLoadData" ) ) != IS_OK )
        return rc;
    exec sql declare CSelLoadData cursor with hold for p_SelLoadData;
    exec sql free p_SelLoadData;
    if ( ( rc=CheckSql( fun, stError, "%s", "free p_SelLoadData" ) ) != IS_OK )
        return rc;
    return rc;
}

/* MCustomerCallPlan::UpdCallPlanDisable **************************************/

retClient Mcustomercallplan_UpdCallPlanDisable(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;  
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdCallPlanDisable";
    exec sql begin declare section;
    mcustomercallplanS *d = a;
    char sAnrufTyp[2];
    exec sql end declare section;

    d->TM_DATE = ppGGetDate();
    d->TM_TIME = ppGGetTime();
    exec sql declare CUpdDisableC11 cursor with hold for
              select kundemasterplan.AnrufTyp
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr = :d->KUNDENNR	
              for update;
    exec sql open CUpdDisableC11;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdDisableC11" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    for(;;)
    {
       exec sql fetch CUpdDisableC11 into :sAnrufTyp;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdDisableC11" ) ) != IS_OK )
          break;
       *sAnrufTyp = (atoi(sAnrufTyp) + atoi(d->ANRUFTYP)) + '0';
       exec sql update kundemasterplan set
                     kundemasterplan.AnrufTyp = :sAnrufTyp,
                     kundemasterplan.tm_date = :d->TM_DATE,
                     kundemasterplan.tm_time = :d->TM_TIME,
                     kundemasterplan.loginId = :d->LOGINID,
                     kundemasterplan.changeId = :d->CHANGEID
                     where current of CUpdDisableC11;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdDisableC11" ) ) != IS_OK )
          break;
       if ( ( iTrans++ % 100 ) == 0 )
       {
          if ( bIsTrans )
          {
             if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
             if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                return rc;
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
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MCustomerCallPlan::UpdCallPlanEnable ***************************************/

retClient Mcustomercallplan_UpdCallPlanEnable(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
   retClient rc = IS_OK;  
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdCallPlanEnable";
    exec sql begin declare section;
    mcustomercallplanS *d = a;
    char sAnrufTyp[2];
    exec sql end declare section;

    d->TM_DATE = ppGGetDate();
    d->TM_TIME = ppGGetTime();
    exec sql declare CUpdEnableC11 cursor with hold for
              select kundemasterplan.AnrufTyp
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr = :d->KUNDENNR	
              for update;
    exec sql open CUpdEnableC11;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdEnableC11" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    for(;;)
    {
       exec sql fetch CUpdEnableC11 into :sAnrufTyp;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdEnableC11" ) ) != IS_OK )
          break;
        *sAnrufTyp = (atoi(sAnrufTyp) - atoi(d->ANRUFTYP)) + '0';
       exec sql update kundemasterplan set
                     kundemasterplan.AnrufTyp = :sAnrufTyp,
                     kundemasterplan.tm_date = :d->TM_DATE,
                     kundemasterplan.tm_time = :d->TM_TIME,
                     kundemasterplan.loginId = :d->LOGINID,
                     kundemasterplan.changeId = :d->CHANGEID
                     where current of CUpdEnableC11;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdEnableC11" ) ) != IS_OK )
          break;
       if ( ( iTrans++ % 100 ) == 0 )
       {
          if ( bIsTrans )
          {
             if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
             if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                return rc;
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
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MCustomerCallPlan::UpdTimeAllCustomerCallPlan ******************************/

retClient Mcustomercallplan_UpdTimeAllCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;  
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdTimeAllCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d = a;
    exec sql end declare section;

    d->TM_TIME = ppGGetTime();
    d->TM_DATE = ppGGetDate();
    exec sql declare CUpdTimeC11 cursor with hold for
              select kundemasterplan.RufProtokoll,
                     kundemasterplan.RufSteuerung,
                     kundemasterplan.poolnr,
                     kundemasterplan.ModemPoolNr,
                     kundemasterplan.RufEinstellung,
                     kundemasterplan.AnrufTyp,
                     kundemasterplan.tm_date,
                     kundemasterplan.tm_time,
                     kundemasterplan.loginId,
                     kundemasterplan.changeId
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->FETCH_REL and
                    KundeMasterPlan.tagnr	> 0
              for update;
    exec sql open CUpdTimeC11;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdTimeC11" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    for(;;)
    {
       exec sql fetch CUpdTimeC11;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdTimeC11" ) ) != IS_OK )
          break;
       exec sql update kundemasterplan set
                     kundemasterplan.UrRufZeit = :d->URRUFZEIT,
                     kundemasterplan.RufProtokoll = :d->RUFPROTOKOLL,
                     kundemasterplan.RufSteuerung = :d->RUFSTEUERUNG,
                     kundemasterplan.poolnr = :d->POOLNR,
                     kundemasterplan.ModemPoolNr = :d->MODEMPOOLNR,
                     kundemasterplan.RufEinstellung = :d->RUFEINSTELLUNG,
                     kundemasterplan.AnrufTyp = :d->ANRUFTYP,
                     kundemasterplan.tm_date = :d->TM_DATE,
                     kundemasterplan.tm_time = :d->TM_TIME,
                     kundemasterplan.loginId = :d->LOGINID,
                     kundemasterplan.changeId = :d->CHANGEID,
                     kundemasterplan.tourid = :d->TOURID,
                     kundemasterplan.skdanrufgenerell = :d->SKDANRUFGENERELL
                     where current of CUpdTimeC11;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdTimeC11" ) ) != IS_OK )
          break;
       if ( ( iTrans++ % 7 ) == 0 )
       {
          if ( bIsTrans )
          {
             if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
             if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                return rc;
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
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MCustomerCallPlan::UpdTimeAllWithoutSaturday *******************************/

retClient Mcustomercallplan_UpdTimeAllWithoutSaturday(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    int iTrans = 0;
    char *fun = "Mcustomercallplan_UpdTimAllWithoutSaturday";
    exec sql begin declare section;
    mcustomercallplanS *d = a;
    exec sql end declare section;

    d->TM_TIME = ppGGetTime();
    d->TM_DATE = ppGGetDate();  
    exec sql declare CUpdTimeSa12 cursor with hold for
              select kundemasterplan.RufProtokoll,
                     kundemasterplan.RufSteuerung,
                     kundemasterplan.poolnr,
                     kundemasterplan.ModemPoolNr,
                     kundemasterplan.RufEinstellung,
                     kundemasterplan.AnrufTyp,
                     kundemasterplan.tm_date,
                     kundemasterplan.tm_time,
                     kundemasterplan.loginId,
                     kundemasterplan.changeId
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->FETCH_REL and
                    KundeMasterPlan.tagnr	> 0 and
                    KundeMasterPlan.tagnr	< 6
              for update;
    exec sql open CUpdTimeSa12;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdTimeSa12" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    for(;;)
    {
       exec sql fetch CUpdTimeSa12;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdTimeSa12" ) ) != IS_OK )
          break;
       exec sql update kundemasterplan set
                     kundemasterplan.UrRufZeit = :d->URRUFZEIT,
                     kundemasterplan.RufProtokoll = :d->RUFPROTOKOLL,
                     kundemasterplan.RufSteuerung = :d->RUFSTEUERUNG,
                     kundemasterplan.poolnr = :d->POOLNR,
                     kundemasterplan.ModemPoolNr = :d->MODEMPOOLNR,
                     kundemasterplan.RufEinstellung = :d->RUFEINSTELLUNG,
                     kundemasterplan.AnrufTyp = :d->ANRUFTYP,
                     kundemasterplan.tm_date = :d->TM_DATE,
                     kundemasterplan.tm_time = :d->TM_TIME,
                     kundemasterplan.loginId = :d->LOGINID,
                     kundemasterplan.changeId = :d->CHANGEID,
                     kundemasterplan.tourid = :d->TOURID,
                     kundemasterplan.skdanrufgenerell = :d->SKDANRUFGENERELL
                     where current of CUpdTimeSa12;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdTimeSa12" ) ) != IS_OK )
          break;
       if ( ( iTrans++ % 6 ) == 0 )
       {
          if ( bIsTrans )
          {
             if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
             if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                return rc;
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
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}

/* MCustomerCallPlan::UpdTimeCustomerCallPlan *********************************/

retClient Mcustomercallplan_UpdTimeCustomerCallPlan(mcustomercallplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplan_UpdTimeCustomerCallPlan";
    exec sql begin declare section;
    mcustomercallplanS *d;
    exec sql end declare section;

    d = a;
    d->TM_TIME = ppGGetTime();
    d->TM_DATE = ppGGetDate();
    exec sql declare CUpdTimeCal3 cursor with hold for
              select kundemasterplan.RufProtokoll,
                     kundemasterplan.RufSteuerung,
                     kundemasterplan.poolnr,
                     kundemasterplan.ModemPoolNr,
                     kundemasterplan.RufEinstellung,
                     kundemasterplan.AnrufTyp,
                     kundemasterplan.tm_date,
                     kundemasterplan.tm_time,
                     kundemasterplan.loginId,
                     kundemasterplan.changeId
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->FETCH_REL
              for update;
    exec sql open CUpdTimeCal3;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdTimeCal3" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    /*reflection activated */
    exec sql insert into MKundemasterPlan select * 
               from KUNDEMASTERPLAN
              where KundeMasterPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    KundeMasterPlan.KundenNr	 =	:d->KUNDENNR	and
                    KundeMasterPlan.tagnr	 =	:d->TAGNR	and
                    KundeMasterPlan.UrRufzeit	 =	:d->FETCH_REL;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: MKundemasterPlan" ) ) != IS_OK )
      return rc;
    if ( d->FETCH_REL != SET_MIRROR )
       {
       d->TM_TIME = ppGGetTime();
       d->TM_DATE = ppGGetDate();
       }
    strcpy( d->CHANGEID, "U" );
    /*reflection activated */

    for(;;)
    {
       exec sql fetch CUpdTimeCal3;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdTimeCal3" ) ) != IS_OK )
          break;
       exec sql update kundemasterplan set
                     kundemasterplan.UrRufzeit = :d->URRUFZEIT,
                     kundemasterplan.RufProtokoll = :d->RUFPROTOKOLL,
                     kundemasterplan.RufSteuerung = :d->RUFSTEUERUNG,
                     kundemasterplan.poolnr = :d->POOLNR,
                     kundemasterplan.ModemPoolNr = :d->MODEMPOOLNR,
                     kundemasterplan.RufEinstellung = :d->RUFEINSTELLUNG,
                     kundemasterplan.AnrufTyp = :d->ANRUFTYP,
                     kundemasterplan.tm_date = :d->TM_DATE,
                     kundemasterplan.tm_time = :d->TM_TIME,
                     kundemasterplan.loginId = :d->LOGINID,
                     kundemasterplan.changeId = :d->CHANGEID,
                     kundemasterplan.tourid = :d->TOURID,
                     kundemasterplan.skdanrufgenerell = :d->SKDANRUFGENERELL
                     where current of CUpdTimeCal3;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdTimeCal3" ) ) != IS_OK )
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
       if ( ( rc = Commit( fun, stError ) ) != IS_OK )
          return rc;
    }
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlanPhonProt.cxx                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:23 2022                                         */
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
#include "callplanmaintenance.h"

/* MCustomerCallPlanPhonProt: Select ******************************************/



/* MCustomerCallPlanPhonProt: Insert ******************************************/

/* MCustomerCallPlanPhonProt::Insert ******************************************/

retClient Mcustomercallplanphonprot_Insert(mcustomercallplanphonprotS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanphonprot_Insert";
    exec sql begin declare section;
    mcustomercallplanphonprotS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->BEMERKUNG);
    if ( *d->BEMERKUNG == '\0' )
        strcpy( d->BEMERKUNG, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into tagplanereignis (datum,
                     rufzeit,
                     idfnr,
                     status,
                     rufzeitgeaendert,
                     zeit,
                     uid,
                     bemerkung,
                     filialnr)
        values (:d->DATUM,
                     :d->RUFZEIT,
                     :d->IDFNR,
                     :d->STATUS,
                     :d->RUFZEITGEAENDERT,
                     :d->ZEIT,
                     :d->UID,
                     :d->BEMERKUNG,
                     :d->FILIALNR);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert tagplanereignis" ) ) != IS_OK )
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



/* MCustomerCallPlanPhonProt: Update ******************************************/



/* MCustomerCallPlanPhonProt: Select ******************************************/

/* MCustomerCallPlanPhonProt::DelAll ******************************************/

retClient Mcustomercallplanphonprot_DelAll(mcustomercallplanphonprotS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplanphonprot_DelAll";
    exec sql begin declare section;
    mcustomercallplanphonprotS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAll21 cursor with hold for
              select datum,
                     rufzeit,
                     idfnr,
                     status,
                     rufzeitgeaendert,
                     zeit,
                     uid,
                     bemerkung,
                     filialnr
               from TAGPLANEREIGNIS
              where tagplanereignis.datum	 =	:d->DATUM and
                    tagplanereignis.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CDelAll21;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAll21" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAll21;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAll21" ) ) != IS_OK )
            break;
        exec sql delete from tagplanereignis where current of CDelAll21;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAll21" ) ) != IS_OK )
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

/* MCustomerCallPlanPhonProt::DelAllOlder *************************************/

retClient Mcustomercallplanphonprot_DelAllOlder(mcustomercallplanphonprotS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplanphonprot_DelAllOlder";
    exec sql begin declare section;
    mcustomercallplanphonprotS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    exec sql declare CDelAllOlder22 cursor with hold for
              select datum,
                     rufzeit,
                     idfnr,
                     status,
                     rufzeitgeaendert,
                     zeit,
                     uid,
                     bemerkung,
                     filialnr
               from TAGPLANEREIGNIS
              where tagplanereignis.datum	<=	:d->DATUM	 and
                    tagplanereignis.datum	!=	:lDate
              for update;
    exec sql open CDelAllOlder22;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllOlder22" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllOlder22;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllOlder22" ) ) != IS_OK )
            break;
        exec sql delete from tagplanereignis where current of CDelAllOlder22;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllOlder22" ) ) != IS_OK )
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



/* MCustomerCallPlanPhonProt: Other *******************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallPlanTour.cxx                                        */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:26 2022                                         */
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
#include "callplanmaintenance.h"

/* MCustomerCallPlanTour: Select **********************************************/

/* MCustomerCallPlanTour::SelList *********************************************/

retClient Mcustomercallplantour_SelList(mcustomercallplantourS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplantour_SelList";
    exec sql begin declare section;
    mcustomercallplantourS *d;
    exec sql end declare section;

    d = a;

    if ( a->WEEKDAY == -1 )
{
  a->WEEKDAY = ppGGetWeekDay(a->DATUMKOMMI, stError->spError);
}
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList23 cursor with hold for
                  select tourplantag.datumkommi,
                     tourplantag.IstVerbundTour,
                     tourplantag.VertriebszentrumNr,
                     tourplantag.KundenNr,
                     tourplanwoche.tourid,
                     tourplanwoche.filialnr,
                     tourplanwoche.weekday
                from TOURPLANTAG, TOURPLANWOCHE
                  where tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        tourplantag.KundenNr	 =	:d->KUNDENNR	 and
                        TourPlanWoche.tourid	 =	tourplantag.tourid and
                        TourPlanWoche.weekday	 =	:d->WEEKDAY and
                        TourPlanWoche.filialnr = :d->FILIALNR	 and
                        tourplantag.datumkommi	 =	:d->DATUMKOMMI	and
                        tourplantag.tourinaktiv	 =	'0'	
                        order by TourPlanWoche.tourid;
        exec sql open CSelList23;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList23" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList23;
        return CheckSql( fun, stError, "%s", "close CSelList23" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList23 into :d->DATUMKOMMI,
                     :d->ISTVERBUNDTOUR,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TOURID,
                     :d->FILIALNR,
                     :d->WEEKDAY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList23" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerCallPlanTour::SelListHist *****************************************/

retClient Mcustomercallplantour_SelListHist(mcustomercallplantourS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplantour_SelListHist";
    exec sql begin declare section;
    mcustomercallplantourS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListHist24 cursor with hold for
                  select TourPlanWoche.weekday
                         into :d->WEEKDAY
                   from TOURPLANWOCHE
                  where TourPlanWoche.tourid	 =	:d->TOURID and 
                        TourPlanWoche.filialnr	 =	:d->FILIALNR;
        exec sql open CSelListHist24;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHist24" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListHist24;
        return CheckSql( fun, stError, "%s", "close CSelListHist24" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListHist24;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListHist24" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerCallPlanTour: Insert **********************************************/



/* MCustomerCallPlanTour: Update **********************************************/



/* MCustomerCallPlanTour: Select **********************************************/



/* MCustomerCallPlanTour: Other ***********************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerCallplanPhon.cxx                                        */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:30 2022                                         */
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
#include "callplanmaintenance.h"

/* MCustomerCallplanPhon: Select **********************************************/



/* MCustomerCallplanPhon: Insert **********************************************/

/* MCustomerCallplanPhon::Insert **********************************************/

retClient Mcustomercallplanphon_Insert(mcustomercallplanphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomercallplanphon_Insert";
    exec sql begin declare section;
    mcustomercallplanphonS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->CALLINFO);
    if ( *d->CALLINFO == '\0' )
        strcpy( d->CALLINFO, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into tagplan (filialnr,
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
                     zugriff,
                     CallInfo)
        values (:d->FILIALNR,
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
                     :d->ZUGRIFF,
                     :d->CALLINFO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert tagplan" ) ) != IS_OK )
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



/* MCustomerCallplanPhon: Update **********************************************/



/* MCustomerCallplanPhon: Select **********************************************/

/* MCustomerCallplanPhon::DelAll **********************************************/

retClient Mcustomercallplanphon_DelAll(mcustomercallplanphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplanphon_DelAll";
    exec sql begin declare section;
    mcustomercallplanphonS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelAll25 cursor with hold for
              select filialnr,
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
                     zugriff,
                     CallInfo
               from TAGPLAN
              where tagplan.filialnr	 =	:d->FILIALNR	 and
                    tagplan.datum	 =	:d->DATUM
              for update;
    exec sql open CDelAll25;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAll25" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAll25;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAll25" ) ) != IS_OK )
            break;
        exec sql delete from tagplan where current of CDelAll25;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAll25" ) ) != IS_OK )
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

/* MCustomerCallplanPhon::DelAllOlder *****************************************/

retClient Mcustomercallplanphon_DelAllOlder(mcustomercallplanphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomercallplanphon_DelAllOlder";
    exec sql begin declare section;
    mcustomercallplanphonS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    exec sql declare CDelAllOlder26 cursor with hold for
              select filialnr,
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
                     zugriff,
                     CallInfo
               from TAGPLAN
              where tagplan.filialnr	 =	:d->FILIALNR	 and
                    tagplan.datum	<=	:d->DATUM	 and
                    tagplan.datum	!=	:lDate
              for update;
    exec sql open CDelAllOlder26;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelAllOlder26" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelAllOlder26;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelAllOlder26" ) ) != IS_OK )
            break;
        exec sql delete from tagplan where current of CDelAllOlder26;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelAllOlder26" ) ) != IS_OK )
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



/* MCustomerCallplanPhon: Other ***********************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerDisplay.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:35 2022                                         */
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
#include "callplanmaintenance.h"

/* MCustomerDisplay: Select ***************************************************/

/* MCustomerDisplay::SelCustomer **********************************************/

retClient Mcustomerdisplay_SelCustomer(mcustomerdisplayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomerdisplay_SelCustomer";
    exec sql begin declare section;
    mcustomerdisplayS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.idfnr,
                     kunde.filialnr,
                     kunde.anredekz,
                     kunde.nameapo,
                     kunde.nameinhaber,
                     kunde.strasse,
                     kunde.ort,
                     kunde.postleitzahl,
                     kunde.telnr,
                     kunde.telnrdafue,
                     kunde.telkurzwahl,
                     kundeschalter.skdkundeaegesperrt,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kundeschalter.skdanrufgenerell
                into :d->IDFNR,
                     :d->FILIALNR,
                     :d->ANREDEKZ,
                     :d->NAMEAPO,
                     :d->NAMEINHABER,
                     :d->STRASSE,
                     :d->ORT,
                     :d->POSTLEITZAHL,
                     :d->TELNR,
                     :d->TELNRDAFUE,
                     :d->TELKURZWAHL,
                     :d->SKDKUNDEAEGESPERRT,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->SKDANRUFGENERELL
                from KUNDE, KUNDESCHALTER
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	and
                    kunde.KundenNr	 =	:d->KUNDENNR and
                    kundeschalter.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                    kundeschalter.KundenNr	 =	kunde.KundenNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerDisplay: Insert ***************************************************/



/* MCustomerDisplay: Update ***************************************************/

/* MCustomerDisplay::UpdTelNo *************************************************/

retClient Mcustomerdisplay_UpdTelNo(mcustomerdisplayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomerdisplay_UpdTelNo";
    exec sql begin declare section;
    mcustomerdisplayS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdTelNo28 cursor with hold for
              select telnr,
                     telnrdafue,
                     telkurzwahl
               from KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR
              for update;
    exec sql open CUpdTelNo28;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdTelNo28" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdTelNo28;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdTelNo28" ) ) != IS_OK )
            break;
        exec sql update kunde set telnr = :d->TELNR,
                     telnrdafue = :d->TELNRDAFUE,
                     telkurzwahl = :d->TELKURZWAHL where current of CUpdTelNo28;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdTelNo28" ) ) != IS_OK )
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



/* MCustomerDisplay: Select ***************************************************/



/* MCustomerDisplay: Other ****************************************************/

/* MCustomerDisplay::UpdProperties ********************************************/

retClient Mcustomerdisplay_UpdProperties(mcustomerdisplayS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = FALSE;
    char *fun = "Mcustomerdisplay_UpdProperties";
    exec sql begin declare section;
    mcustomerdisplayS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CUpdPropX cursor with hold for
              select skdanrufgenerell
               from KUNDESCHALTER
              where KUNDESCHALTER.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR and
                    KUNDESCHALTER.KundenNr = :d->KUNDENNR
              for update;
    exec sql open CUpdPropX;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdPropX" ) ) != IS_OK )
      return rc;
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       bInTrans = TRUE;
    }
    for(;;)
    {
       exec sql fetch CUpdPropX;
       if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdPropX" ) ) != IS_OK )
          break;
       exec sql update KUNDESCHALTER set skdanrufgenerell = :d->SKDANRUFGENERELL
                 where current of CUpdPropX;
       if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdPropX" ) ) != IS_OK )
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



/******************************************************************************/
/*                                                                            */
/* header  : MDevicePlanMaintenance.cxx                                       */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:42 2022                                         */
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
#include "callplanmaintenance.h"

/* MDevicePlanMaintenance: Select *********************************************/

/* MDevicePlanMaintenance::SelDevicePlanUni ***********************************/

retClient Mdeviceplanmaintenance_SelDevicePlanUni(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplanmaintenance_SelDevicePlanUni";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
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
                     modemanrufplan.geraeteart,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.modemtyp,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.umknr,
                     modemanrufplan.tm_date,
                     modemanrufplan.tm_time,
                     modemanrufplan.loginId,
                     modemanrufplan.changeId,
                     modemanrufplan.aktiv,
                     modemanrufplan.umknst
                into :d->REGIONENTYP,
                     :d->FILIALNR,
                     :d->GERAETEID,
                     :d->GERAETEART,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->MODEMTYP,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->UMKNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->AKTIV,
                     :d->UMKNST
                from REGIONARTEN, MODEMANRUFPLAN
              where RegionArten.RegionNr = :d->VERTRIEBSZENTRUMNR and
                    RegionArten.RegionenTyp = :d->REGIONENTYP and
                    RegionArten.RegionTeilNr  = ModemAnrufplan.filialnr and
                    ModemAnrufplan.filialnr = :d->FILIALNR and
                    ModemAnrufplan.geraeteid  = :d->GERAETEID;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MDevicePlanMaintenance::SelList ********************************************/

retClient Mdeviceplanmaintenance_SelList(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplanmaintenance_SelList";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList30 cursor with hold for
                  select regionarten.RegionenTyp,
                     modemanrufplan.filialnr,
                     modemanrufplan.geraeteid,
                     modemanrufplan.geraeteart,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.modemtyp,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.umknr,
                     modemanrufplan.tm_date,
                     modemanrufplan.tm_time,
                     modemanrufplan.loginId,
                     modemanrufplan.changeId,
                     modemanrufplan.aktiv,
                     modemanrufplan.umknst
                from MODEMANRUFPLAN, REGIONARTEN
                  where RegionArten.RegionNr	 =	:d->VERTRIEBSZENTRUMNR	and
                        RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                        RegionArten.RegionTeilNr	 =	ModemAnrufplan.filialnr
                        order by ModemAnrufplan.filialnr, ModemAnrufplan.geraeteid;
        exec sql open CSelList30;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList30" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList30;
        return CheckSql( fun, stError, "%s", "close CSelList30" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList30 into :d->REGIONENTYP,
                     :d->FILIALNR,
                     :d->GERAETEID,
                     :d->GERAETEART,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->MODEMTYP,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->UMKNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->AKTIV,
                     :d->UMKNST;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList30" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MDevicePlanMaintenance::SelNst *********************************************/

retClient Mdeviceplanmaintenance_SelNst(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplanmaintenance_SelNst";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
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
                     modemanrufplan.geraeteart,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.modemtyp,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.umknr,
                     modemanrufplan.tm_date,
                     modemanrufplan.tm_time,
                     modemanrufplan.loginId,
                     modemanrufplan.changeId,
                     modemanrufplan.aktiv,
                     modemanrufplan.umknst
                into :d->REGIONENTYP,
                     :d->FILIALNR,
                     :d->GERAETEID,
                     :d->GERAETEART,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->MODEMTYP,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->UMKNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->AKTIV,
                     :d->UMKNST
                from MODEMANRUFPLAN, REGIONARTEN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	 and
                    ModemAnrufplan.geraetnst	 =	:d->GERAETNST and
                    RegionArten.RegionNr = :d->VERTRIEBSZENTRUMNR and
                    RegionArten.RegionenTyp = :d->REGIONENTYP and
                    RegionArten.RegionTeilNr  = ModemAnrufplan.filialnr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MDevicePlanMaintenance: Insert *********************************************/



/* MDevicePlanMaintenance: Update *********************************************/

/* MDevicePlanMaintenance::UpdDevicePlan **************************************/

retClient Mdeviceplanmaintenance_UpdDevicePlan(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mdeviceplanmaintenance_UpdDevicePlan";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdDevicePlan32 cursor with hold for
              select geraeteart,
                     geraetnst,
                     geraeteverw1,
                     modemtyp,
                     VertriebszentrumNr,
                     umknr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     aktiv,
                     umknst
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID
              for update;
    exec sql open CUpdDevicePlan32;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdDevicePlan32" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    exec sql insert into mModemAnrufplan select * 
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: mModemAnrufplan" ) ) != IS_OK )
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
        exec sql fetch CUpdDevicePlan32;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdDevicePlan32" ) ) != IS_OK )
            break;
        exec sql update modemanrufplan set geraeteart = :d->GERAETEART,
                     geraetnst = :d->GERAETNST,
                     geraeteverw1 = :d->GERAETEVERW1,
                     modemtyp = :d->MODEMTYP,
                     VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     umknr = :d->UMKNR,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     aktiv = :d->AKTIV,
                     umknst = :d->UMKNST where current of CUpdDevicePlan32;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdDevicePlan32" ) ) != IS_OK )
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

/* MDevicePlanMaintenance::UpdSaleCenterNo ************************************/

retClient Mdeviceplanmaintenance_UpdSaleCenterNo(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mdeviceplanmaintenance_UpdSaleCenterNo";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdSaleCenterNo33 cursor with hold for
              select geraeteart,
                     geraetnst,
                     geraeteverw1,
                     modemtyp,
                     VertriebszentrumNr,
                     umknr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     aktiv,
                     umknst
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteverw1	 =	:d->GERAETEVERW1
              for update;
    exec sql open CUpdSaleCenterNo33;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdSaleCenterNo33" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdSaleCenterNo33;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdSaleCenterNo33" ) ) != IS_OK )
            break;
        exec sql update modemanrufplan set geraeteart = :d->GERAETEART,
                     geraetnst = :d->GERAETNST,
                     geraeteverw1 = :d->GERAETEVERW1,
                     modemtyp = :d->MODEMTYP,
                     VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     umknr = :d->UMKNR,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     aktiv = :d->AKTIV,
                     umknst = :d->UMKNST where current of CUpdSaleCenterNo33;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdSaleCenterNo33" ) ) != IS_OK )
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
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* MDevicePlanMaintenance: Select *********************************************/

/* MDevicePlanMaintenance::Delete *********************************************/

retClient Mdeviceplanmaintenance_Delete(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mdeviceplanmaintenance_Delete";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete34 cursor with hold for
              select filialnr,
                     geraeteid,
                     geraeteart,
                     geraetnst,
                     geraeteverw1,
                     modemtyp,
                     VertriebszentrumNr,
                     umknr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     aktiv,
                     umknst
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID
              for update;
    exec sql open CDelete34;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete34" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    exec sql update MODEMANRUFPLAN set
              tm_date = :d->TM_DATE,
              tm_time = :d->TM_TIME,
              changeid = "D" 
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID;
    if ( ( rc=CheckSql( fun, stError,  "%s", "update reflectiontable: MODEMANRUFPLAN" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    exec sql insert into mModemAnrufplan select * 
               from MODEMANRUFPLAN
              where ModemAnrufplan.filialnr	 =	:d->FILIALNR	and
                    ModemAnrufplan.geraeteid	 =	:d->GERAETEID;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: mModemAnrufplan" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    /*reflection activated */

    for(;;)
    {
        exec sql fetch CDelete34;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete34" ) ) != IS_OK )
            break;
        exec sql delete from modemanrufplan where current of CDelete34;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete34" ) ) != IS_OK )
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



/* MDevicePlanMaintenance: Other **********************************************/

/* MDevicePlanMaintenance::InsertDevice ***************************************/

retClient Mdeviceplanmaintenance_InsertDevice(mdeviceplanmaintenanceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mdeviceplanmaintenance_InsertDevice";
    exec sql begin declare section;
    mdeviceplanmaintenanceS *d;
    exec sql end declare section;
    short sGeraetID;

    d = a;

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    /*reflection activated */

    if ( d->FETCH_REL != SET_MIRROR )
       {
       d->TM_TIME = ppGGetTime();
       d->TM_DATE = ppGGetDate();
       }
    strcpy( d->CHANGEID, "I" );
    /*reflection activated */

    exec sql select MAX(modemanrufplan.geraeteid) into :d->GERAETEID
               from modemanrufplan;
    if ( ( rc = CheckSql( fun, stError,  "%s", "select max modemanrufplan" ) ) != IS_OK )
    {
      if ( bIsTrans )
         exec sql rollback work;
      return rc;
    }

    if ( (sGeraetID=atoi(d->GERAETEID)) == 0)
       strcpy(d->GERAETEID, "0001");
    else
       sprintf(d->GERAETEID, "%04d", sGeraetID + 1); 
  
    exec sql insert into modemanrufplan (modemanrufplan.filialnr,
                     modemanrufplan.geraeteid,
                     modemanrufplan.geraeteart,
                     modemanrufplan.geraetnst,
                     modemanrufplan.geraeteverw1,
                     modemanrufplan.modemtyp,
                     modemanrufplan.VertriebszentrumNr,
                     modemanrufplan.umknr,
                     modemanrufplan.umknst,
                     modemanrufplan.tm_date,
                     modemanrufplan.tm_time,
                     modemanrufplan.loginId,
                     modemanrufplan.changeId)
        values (:d->FILIALNR,
                     :d->GERAETEID,
                     :d->GERAETEART,
                     :d->GERAETNST,
                     :d->GERAETEVERW1,
                     :d->MODEMTYP,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->UMKNR,
                     :d->UMKNST,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert modemanrufplan" ) ) != IS_OK )
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



/******************************************************************************/
/*                                                                            */
/* header  : MRegion.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:46 2022                                         */
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
#include "callplanmaintenance.h"

/* MRegion: Select ************************************************************/

/* MRegion::SelList ***********************************************************/

retClient Mregion_SelList(mregionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mregion_SelList";
    exec sql begin declare section;
    mregionS *d;
    exec sql end declare section;

    d = a;

    if ( a->REGIONNR != 0 )
{
    a->REGIONTEILNR =  a->REGIONNR; /* only one region will select */
}
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList35 cursor with hold for
                  select regionarten.RegionenTyp,
                     regionarten.RegionNr,
                     regionarten.RegionTeilNr,
                     filiale.name,
                     regionarten.tm_date,
                     regionarten.tm_time,
                     regionarten.loginId,
                     regionarten.changeId
                from REGIONARTEN, outer FILIALE
                  where RegionArten.RegionenTyp =:d->REGIONENTYP	and
                        RegionArten.RegionNr	>=	:d->REGIONNR and
                        RegionArten.RegionNr	<=	:d->REGIONTEILNR and
                        RegionArten.RegionTeilNr	 =	filiale.filialnr
                        order by RegionArten.RegionTeilNr;
        exec sql open CSelList35;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList35" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList35;
        return CheckSql( fun, stError, "%s", "close CSelList35" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList35 into :d->REGIONENTYP,
                     :d->REGIONNR,
                     :d->REGIONTEILNR,
                     :d->NAME,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList35" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MRegion::SelRegion *********************************************************/

retClient Mregion_SelRegion(mregionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mregion_SelRegion";
    exec sql begin declare section;
    mregionS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select regionarten.RegionenTyp,
                     regionarten.RegionNr,
                     regionarten.RegionTeilNr,
                     filiale.name,
                     regionarten.tm_date,
                     regionarten.tm_time,
                     regionarten.loginId,
                     regionarten.changeId
                into :d->REGIONENTYP,
                     :d->REGIONNR,
                     :d->REGIONTEILNR,
                     :d->NAME,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID
                from REGIONARTEN, FILIALE
              where RegionArten.RegionNr	 =	:d->REGIONNR	 and
                    RegionArten.RegionTeilNr	=	:d->REGIONTEILNR	 and
                    RegionArten.RegionenTyp	 =	:d->REGIONENTYP and
                    filiale.filialnr	 =	RegionArten.RegionTeilNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MRegion: Insert ************************************************************/

/* MRegion::Insert ************************************************************/

retClient Mregion_Insert(mregionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mregion_Insert";
    exec sql begin declare section;
    mregionS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    /*reflection activated */

    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    strcpy( d->CHANGEID, "I" );
    /*reflection activated */

    exec sql insert into regionarten (RegionenTyp,
                     RegionNr,
                     RegionTeilNr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId)
        values (:d->REGIONENTYP,
                     :d->REGIONNR,
                     :d->REGIONTEILNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert regionarten" ) ) != IS_OK )
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



/* MRegion: Update ************************************************************/



/* MRegion: Select ************************************************************/

/* MRegion::DelRegion *********************************************************/

retClient Mregion_DelRegion(mregionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mregion_DelRegion";
    exec sql begin declare section;
    mregionS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelRegion37 cursor with hold for
              select RegionenTyp,
                     RegionNr,
                     RegionTeilNr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId
               from REGIONARTEN
              where RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                    RegionArten.RegionNr	 =	:d->REGIONNR	and
                    RegionArten.RegionTeilNr	 =	:d->REGIONTEILNR
              for update;
    exec sql open CDelRegion37;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelRegion37" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    /*reflection activated */
    if ( d->FETCH_REL != SET_MIRROR )
        {
        d->TM_TIME = ppGGetTime();
        d->TM_DATE = ppGGetDate();
        }
    exec sql update REGIONARTEN set
              tm_date = :d->TM_DATE,
              tm_time = :d->TM_TIME,
              changeid = "D" 
              where RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                    RegionArten.RegionNr	 =	:d->REGIONNR	and
                    RegionArten.RegionTeilNr	 =	:d->REGIONTEILNR;
    if ( ( rc=CheckSql( fun, stError,  "%s", "update reflectiontable: REGIONARTEN" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    exec sql insert into mRegionArten select * 
               from REGIONARTEN
              where RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                    RegionArten.RegionNr	 =	:d->REGIONNR	and
                    RegionArten.RegionTeilNr	 =	:d->REGIONTEILNR;

    if ( ( rc=CheckSql( fun, stError,  "%s", "insert into reflectiontable: mRegionArten" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    /*reflection activated */

    for(;;)
    {
        exec sql fetch CDelRegion37;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelRegion37" ) ) != IS_OK )
            break;
        exec sql delete from regionarten where current of CDelRegion37;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelRegion37" ) ) != IS_OK )
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



/* MRegion: Other *************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MSaleCenter.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:48 2022                                         */
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
#include "callplanmaintenance.h"

/* MSaleCenter: Select ********************************************************/

/* MSaleCenter::SelList *******************************************************/

retClient Msalecenter_SelList(msalecenterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msalecenter_SelList";
    exec sql begin declare section;
    msalecenterS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList38 cursor with hold for
                  select filiale.filialnr,
                     filiale.name
                from filiale
                  where filiale.filialnr	!=	:d->FILIALNR	
                        order by filiale.filialnr;
        exec sql open CSelList38;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList38" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList38;
        return CheckSql( fun, stError, "%s", "close CSelList38" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList38 into :d->FILIALNR,
                     :d->NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList38" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MSaleCenter::SelSaleCenter *************************************************/

retClient Msalecenter_SelSaleCenter(msalecenterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Msalecenter_SelSaleCenter";
    exec sql begin declare section;
    msalecenterS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select filiale.filialnr,
                     filiale.name
                into :d->FILIALNR,
                     :d->NAME
                from filiale
              where filiale.filialnr	 =	:d->FILIALNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MSaleCenter: Insert ********************************************************/



/* MSaleCenter: Update ********************************************************/



/* MSaleCenter: Select ********************************************************/



/* MSaleCenter: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MUmkConnection.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:52:54 2022                                         */
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
#include "callplanmaintenance.h"

/* MUmkConnection: Select *****************************************************/

/* MUmkConnection::SelList ****************************************************/

retClient Mumkconnection_SelList(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mumkconnection_SelList";
    exec sql begin declare section;
    mumkconnectionS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList40 cursor with hold for
                  select regionarten.RegionenTyp,
                     regionarten.RegionNr,
                     umkverwaltung.filialnr,
                     umkverwaltung.umknr,
                     umkverwaltung.RechnerName,
                     umkverwaltung.PortNr,
                     umkverwaltung.tm_date,
                     umkverwaltung.tm_time,
                     umkverwaltung.loginId,
                     umkverwaltung.changeId
                from REGIONARTEN, UMKVERWALTUNG
                  where RegionArten.RegionNr	 =	:d->REGIONNR	and
                        RegionArten.RegionenTyp	 =	:d->REGIONENTYP	and
                        RegionArten.RegionTeilNr	 =	UmkVerwaltung.filialnr
                        order by UmkVerwaltung.filialnr, UmkVerwaltung.umknr;
        exec sql open CSelList40;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList40" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList40;
        return CheckSql( fun, stError, "%s", "close CSelList40" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList40 into :d->REGIONENTYP,
                     :d->REGIONNR,
                     :d->FILIALNR,
                     :d->UMKNR,
                     :d->RECHNERNAME,
                     :d->PORTNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList40" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MUmkConnection::SelUmkConnection *******************************************/

retClient Mumkconnection_SelUmkConnection(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mumkconnection_SelUmkConnection";
    exec sql begin declare section;
    mumkconnectionS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select UmkVerwaltung.filialnr, 
UmkVerwaltung.umknr,
UmkVerwaltung.RechnerName,
 UmkVerwaltung.PortNr
                into :d->FILIALNR,
:d->UMKNR,
:d->RECHNERNAME,
:d->PORTNR
                from UMKVERWALTUNG
              where UmkVerwaltung.filialnr	 =	:d->FILIALNR	and
                    UmkVerwaltung.umknr	 =	:d->UMKNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MUmkConnection: Insert *****************************************************/

/* MUmkConnection::Insert *****************************************************/

retClient Mumkconnection_Insert(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mumkconnection_Insert";
    exec sql begin declare section;
    mumkconnectionS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into umkverwaltung (filialnr,
                     umknr,
                     RechnerName,
                     PortNr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId)
        values (:d->FILIALNR,
                     :d->UMKNR,
                     :d->RECHNERNAME,
                     :d->PORTNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert umkverwaltung" ) ) != IS_OK )
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



/* MUmkConnection: Update *****************************************************/

/* MUmkConnection::UpdUmkConnection *******************************************/

retClient Mumkconnection_UpdUmkConnection(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mumkconnection_UpdUmkConnection";
    exec sql begin declare section;
    mumkconnectionS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdUmkConnection42 cursor with hold for
              select filialnr,
                     umknr,
                     RechnerName,
                     PortNr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId
               from UMKVERWALTUNG
              where UmkVerwaltung.filialnr	 =	:d->FILIALNR	and
                    UmkVerwaltung.umknr	 =	:d->UMKNR
              for update;
    exec sql open CUpdUmkConnection42;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdUmkConnection42" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdUmkConnection42;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdUmkConnection42" ) ) != IS_OK )
            break;
        exec sql update umkverwaltung set filialnr = :d->FILIALNR,
                     umknr = :d->UMKNR,
                     RechnerName = :d->RECHNERNAME,
                     PortNr = :d->PORTNR,
                     tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID where current of CUpdUmkConnection42;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdUmkConnection42" ) ) != IS_OK )
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



/* MUmkConnection: Select *****************************************************/

/* MUmkConnection::DelUmkConnection *******************************************/

retClient Mumkconnection_DelUmkConnection(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mumkconnection_DelUmkConnection";
    exec sql begin declare section;
    mumkconnectionS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelUmkConnection43 cursor with hold for
              select filialnr,
                     umknr,
                     RechnerName,
                     PortNr,
                     tm_date,
                     tm_time,
                     loginId,
                     changeId
               from UMKVERWALTUNG
              where UmkVerwaltung.filialnr	 =	:d->FILIALNR	and
                    UmkVerwaltung.umknr	 =	:d->UMKNR
              for update;
    exec sql open CDelUmkConnection43;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelUmkConnection43" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelUmkConnection43;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelUmkConnection43" ) ) != IS_OK )
            break;
        exec sql delete from umkverwaltung where current of CDelUmkConnection43;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelUmkConnection43" ) ) != IS_OK )
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



/* MUmkConnection: Other ******************************************************/

/* MUmkConnection::WriteLog ***************************************************/

retClient Mumkconnection_WriteLog(mumkconnectionS *a, tError *stError, bool bIsTrans)
{
    char *fun = "MUmkConnection_WriteLog";

    if ( bIsTrans ); /*only because preprozessor*/
    CheckSql( fun, stError, "%s", a->RECHNERNAME );
    return IS_WARNING;
}



