/******************************************************************************/
/*                                                                            */
/* header  : CallBackAttach.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:33 2022                                         */
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
#include "callback.h"

/* CallBackAttach: Select *****************************************************/

/* CallBackAttach::Sel ********************************************************/

retClient Callbackattach_Sel(callbackattachS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackattach_Sel";
    exec sql begin declare section;
    callbackattachS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel0 cursor with hold for
                  select callbackattach.uid,
                     callbackattach.callbackpartno,
                     callbackattach.VertriebszentrumNr,
                     callbackattach.filialnr,
                     callbackattach.ReasonNo
                from CALLBACKATTACH
                  where callbackattach.uid	 =	:d->UID and
                        callbackattach.filialnr	 =	:d->FILIALNR	 and
                        callbackattach.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where RegionArten.RegionNr	 =	:d->REGIONNR and
                        RegionArten.RegionenTyp=1	);
        exec sql open CSel0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel0;
        return CheckSql( fun, stError, "%s", "close CSel0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel0 into :d->UID,
                     :d->CALLBACKPARTNO,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->FILIALNR,
                     :d->REASONNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel0" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallBackAttach::SelVz ******************************************************/

retClient Callbackattach_SelVz(callbackattachS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackattach_SelVz";
    exec sql begin declare section;
    callbackattachS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelVz1 cursor with hold for
                  select callbackattach.uid,
                     callbackattach.callbackpartno,
                     callbackattach.VertriebszentrumNr,
                     callbackattach.filialnr,
                     callbackattach.ReasonNo
                from CALLBACKATTACH
                  where callbackattach.uid	 =	:d->UID	 and
                        callbackattach.filialnr	 =	:d->FILIALNR	 and
                        callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelVz1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelVz1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelVz1;
        return CheckSql( fun, stError, "%s", "close CSelVz1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelVz1 into :d->UID,
                     :d->CALLBACKPARTNO,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->FILIALNR,
                     :d->REASONNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelVz1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallBackAttach: Insert *****************************************************/

/* CallBackAttach::Insert *****************************************************/

retClient Callbackattach_Insert(callbackattachS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackattach_Insert";
    exec sql begin declare section;
    callbackattachS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into callbackattach (uid,
                     callbackpartno,
                     VertriebszentrumNr,
                     filialnr,
                     ReasonNo)
        values (:d->UID,
                     :d->CALLBACKPARTNO,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->FILIALNR,
                     :d->REASONNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert callbackattach" ) ) != IS_OK )
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



/* CallBackAttach: Update *****************************************************/



/* CallBackAttach: Select *****************************************************/

/* CallBackAttach::Delete *****************************************************/

retClient Callbackattach_Delete(callbackattachS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Callbackattach_Delete";
    exec sql begin declare section;
    callbackattachS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete2 cursor with hold for
              select uid,
                     callbackpartno,
                     VertriebszentrumNr,
                     filialnr,
                     ReasonNo
               from CALLBACKATTACH
              where callbackattach.uid	 =	:d->UID	and
                    callbackattach.callbackpartno		 =	:d->CALLBACKPARTNO and
                    callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR and
                    callbackattach.filialnr	 =	:d->FILIALNR
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
        exec sql delete from callbackattach where current of CDelete2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete2" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
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



/* CallBackAttach: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CallBackPartner.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:38 2022                                         */
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
#include "callback.h"

/* CallBackPartner: Select ****************************************************/

/* CallBackPartner::SelPartner ************************************************/

retClient Callbackpartner_SelPartner(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackpartner_SelPartner";
    exec sql begin declare section;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select callbackpartner.callbackpartno,
                     callbackpartner.callbackpartner,
                     callbackpartner.callbacktime,
                     callbackpartner.VertriebszentrumNr
                into :d->CALLBACKPARTNO,
                     :d->CALLBACKPARTNER,
                     :d->CALLBACKTIME,
                     :d->VERTRIEBSZENTRUMNR
                from CALLBACKPARTNER
              where callbackpartner.callbackpartno	 =	:d->CALLBACKPARTNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallBackPartner::SelectAll *************************************************/

retClient Callbackpartner_SelectAll(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackpartner_SelectAll";
    exec sql begin declare section;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelectAll4 cursor with hold for
                  select callbackpartner.callbackpartno,
                     callbackpartner.callbackpartner,
                     callbackpartner.callbacktime,
                     callbackpartner.VertriebszentrumNr
                from CALLBACKPARTNER
                  where callbackpartner.callbackpartno	>=	0 and
                        callbackpartner.VertriebszentrumNr in 
                        (select RegionArten.RegionTeilNr from RegionArten
                         where RegionArten.RegionNr	 =	:d->VERTRIEBSZENTRUMNR and
                        RegionArten.RegionenTyp=1	)
                        order by callbackpartner.callbackpartner;
        exec sql open CSelectAll4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelectAll4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelectAll4;
        return CheckSql( fun, stError, "%s", "close CSelectAll4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelectAll4 into :d->CALLBACKPARTNO,
                     :d->CALLBACKPARTNER,
                     :d->CALLBACKTIME,
                     :d->VERTRIEBSZENTRUMNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelectAll4" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallBackPartner::SelectAllVz ***********************************************/

retClient Callbackpartner_SelectAllVz(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackpartner_SelectAllVz";
    exec sql begin declare section;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelectAllVz5 cursor with hold for
                  select callbackpartner.callbackpartno,
                     callbackpartner.callbackpartner,
                     callbackpartner.callbacktime,
                     callbackpartner.VertriebszentrumNr
                from CALLBACKPARTNER
                  where callbackpartner.callbackpartno	>=	0 and
                        callbackpartner.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	
                        order by callbackpartner.callbackpartner;
        exec sql open CSelectAllVz5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelectAllVz5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelectAllVz5;
        return CheckSql( fun, stError, "%s", "close CSelectAllVz5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelectAllVz5 into :d->CALLBACKPARTNO,
                     :d->CALLBACKPARTNER,
                     :d->CALLBACKTIME,
                     :d->VERTRIEBSZENTRUMNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelectAllVz5" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallBackPartner: Insert ****************************************************/



/* CallBackPartner: Update ****************************************************/

/* CallBackPartner::Update ****************************************************/

retClient Callbackpartner_Update(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackpartner_Update";
    exec sql begin declare section;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate6 cursor with hold for
              select callbackpartno,
                     callbackpartner,
                     callbacktime,
                     VertriebszentrumNr
               from CALLBACKPARTNER
              where callbackpartner.callbackpartno	 =	:d->CALLBACKPARTNO
              for update;
    exec sql open CUpdate6;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate6" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate6;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate6" ) ) != IS_OK )
            break;
        exec sql update callbackpartner set callbackpartno = :d->CALLBACKPARTNO,
                     callbackpartner = :d->CALLBACKPARTNER,
                     callbacktime = :d->CALLBACKTIME,
                     VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR where current of CUpdate6;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate6" ) ) != IS_OK )
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



/* CallBackPartner: Select ****************************************************/

/* CallBackPartner::DeleteCallbackPartner *************************************/

retClient Callbackpartner_DeleteCallbackPartner(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Callbackpartner_DeleteCallbackPartner";
    exec sql begin declare section;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteCallbackPartner7 cursor with hold for
              select callbackpartno,
                     callbackpartner,
                     callbacktime,
                     VertriebszentrumNr
               from CALLBACKPARTNER
              where callbackpartner.callbackpartno	 =	:d->CALLBACKPARTNO
              for update;
    exec sql open CDeleteCallbackPartner7;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteCallbackPartner7" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteCallbackPartner7;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteCallbackPartner7" ) ) != IS_OK )
            break;
        exec sql delete from callbackpartner where current of CDeleteCallbackPartner7;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteCallbackPartner7" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
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



/* CallBackPartner: Other *****************************************************/

/* CallBackPartner::InsertWithNewNo *******************************************/

retClient Callbackpartner_InsertWithNewNo(callbackpartnerS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
    retClient rc = IS_OK;
    char *fun = "InsertWithNewNo";

    exec sql begin declare section;
    int iIndicator;
    callbackpartnerS *d;
    exec sql end declare section;

    d = a;

    exec sql select MAX(callbackpartno) + 1
               into :d->CALLBACKPARTNO indicator :iIndicator
               from callbackpartner;
    if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
      return rc;
    else if ( iIndicator < 0 )
       d->CALLBACKPARTNO = 1; /* start with 1 */

    if ( bIsTrans )
    {
       #if !defined (__S390IBM__) && !defined (__ORACLE__)
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       #endif
    }

    exec sql insert into callbackpartner( callbackpartno,
                                          callbackpartner,
                                          callbacktime,
                                          vertriebszentrumnr )
                                  values( :d->CALLBACKPARTNO,
                                          :d->CALLBACKPARTNER,
                                          :d->CALLBACKTIME,
                                          :d->VERTRIEBSZENTRUMNR );
    if ( ( rc=CheckSql( fun, stError, "%s", "insert" ) ) != IS_OK )
    {    
       if ( bIsTrans )
          exec sql rollback work; 
       return rc; /* then an error has occured! */
    }
    
    return Commit( fun, stError );
}



/******************************************************************************/
/*                                                                            */
/* header  : CallBackTime.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:41 2022                                         */
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
#include "callback.h"

/* CallBackTime: Select *******************************************************/

/* CallBackTime::SelectCallbackPartner ****************************************/

retClient Callbacktime_SelectCallbackPartner(callbacktimeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktime_SelectCallbackPartner";
    exec sql begin declare section;
    callbacktimeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelectCallbackPartner8 cursor with hold for
                  select callbackofftime.callbackpartno,
                     callbackofftime.officeday,
                     callbackofftime.begintime,
                     callbackofftime.endtime
                from CALLBACKOFFTIME
                  where callbackofftime.callbackpartno	 =	:d->CALLBACKPARTNO	
                        order by callbackofftime.officeday, callbackofftime.begintime;
        exec sql open CSelectCallbackPartner8;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelectCallbackPartner8" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelectCallbackPartner8;
        return CheckSql( fun, stError, "%s", "close CSelectCallbackPartner8" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelectCallbackPartner8 into :d->CALLBACKPARTNO,
                     :d->OFFICEDAY,
                     :d->BEGINTIME,
                     :d->ENDTIME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelectCallbackPartner8" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallBackTime: Insert *******************************************************/

/* CallBackTime::Insert *******************************************************/

retClient Callbacktime_Insert(callbacktimeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktime_Insert";
    exec sql begin declare section;
    callbacktimeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into callbackofftime (callbackpartno,
                     officeday,
                     begintime,
                     endtime)
        values (:d->CALLBACKPARTNO,
                     :d->OFFICEDAY,
                     :d->BEGINTIME,
                     :d->ENDTIME);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert callbackofftime" ) ) != IS_OK )
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



/* CallBackTime: Update *******************************************************/



/* CallBackTime: Select *******************************************************/

/* CallBackTime::DeleteAllNo **************************************************/

retClient Callbacktime_DeleteAllNo(callbacktimeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Callbacktime_DeleteAllNo";
    exec sql begin declare section;
    callbacktimeS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllNo9 cursor with hold for
              select callbackpartno,
                     officeday,
                     begintime,
                     endtime
               from CALLBACKOFFTIME
              where callbackofftime.callbackpartno	 =	:d->CALLBACKPARTNO
              for update;
    exec sql open CDeleteAllNo9;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllNo9" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllNo9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllNo9" ) ) != IS_OK )
            break;
        exec sql delete from callbackofftime where current of CDeleteAllNo9;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllNo9" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
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

/* CallBackTime::DeleteCallbackTime *******************************************/

retClient Callbacktime_DeleteCallbackTime(callbacktimeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Callbacktime_DeleteCallbackTime";
    exec sql begin declare section;
    callbacktimeS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteCallbackTime10 cursor with hold for
              select callbackpartno,
                     officeday,
                     begintime,
                     endtime
               from CALLBACKOFFTIME
              where callbackofftime.callbackpartno	 =	:d->CALLBACKPARTNO	and
                    callbackofftime.officeday	 =	:d->OFFICEDAY	and
                    callbackofftime.begintime	 =	:d->BEGINTIME
              for update;
    exec sql open CDeleteCallbackTime10;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteCallbackTime10" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteCallbackTime10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteCallbackTime10" ) ) != IS_OK )
            break;
        exec sql delete from callbackofftime where current of CDeleteCallbackTime10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteCallbackTime10" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
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



/* CallBackTime: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CallbackCritical.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:44 2022                                         */
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
#include "callback.h"

/* CallbackCritical: Select ***************************************************/

/* CallbackCritical::SelCritical **********************************************/

retClient Callbackcritical_SelCritical(callbackcriticalS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackcritical_SelCritical";
    exec sql begin declare section;
    callbackcriticalS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCritical11 cursor with hold for
                  select callbackdivision.DivisionName,
kdkritik.datum,
kdkritikpos.kritiktext,
kdkritik.titel,
kdkritik.kritiknr,
callbackitems.posnr_done,
callbackitems.callbackstatusid,
kdkritik.VertriebszentrumNr,
kdkritik.KundenNr,
kdkritik.kritiklevel,
nvl(passwd.username,kdkritikpos.windowsid)
                         into :d->DIVISIONNAME, :d->DATUM, :d->KRITIKTEXT, :d->TITEL, :d->KRITIKNR, :d->POSNR_DONE, :d->STATUSID, :d->VERTRIEBSZENTRUMNR, :d->KUNDENNR, :d->KRITIKLEVEL, :d->USERNAME64
                   from KDKRITIK, KDKRITIKPOS, CALLBACKDIVISION, CALLBACKITEMS, outer PASSWD
                  where kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kdkritik.KundenNr	 =	:d->KUNDENNR	 and
                        CallbackDivision.BranchNo	 =	kdkritik.VertriebszentrumNr and
                        CallbackDivision.CallbackDivisionNo	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        kdkritik.kritiklevel	 >	0 and
                        kdkritik.filialnr	 =	passwd.filialnr and
                        kdkritik.uid	 =	passwd.uid
                        order by kdkritik.datum desc, kdkritik.kritiklevel desc;
        exec sql open CSelCritical11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCritical11" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCritical11;
        return CheckSql( fun, stError, "%s", "close CSelCritical11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCritical11;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCritical11" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackCritical: Insert ***************************************************/



/* CallbackCritical: Update ***************************************************/



/* CallbackCritical: Select ***************************************************/



/* CallbackCritical: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CallbackDivision.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:49 2022                                         */
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
#include "callback.h"

/* CallbackDivision: Select ***************************************************/

/* CallbackDivision::SelDivision **********************************************/

retClient Callbackdivision_SelDivision(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackdivision_SelDivision";
    exec sql begin declare section;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select callbackdivision.BranchNo,
                     callbackdivision.DivisionName,
                     callbackdivision.MailingList,
                     callbackdivision.CallbackDivisionNo
                into :d->BRANCHNO,
                     :d->DIVISIONNAME,
                     :d->MAILINGLIST,
                     :d->CALLBACKDIVISIONNO
                from CALLBACKDIVISION
              where CallbackDivision.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackDivision.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackDivision::SelList **************************************************/

retClient Callbackdivision_SelList(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackdivision_SelList";
    exec sql begin declare section;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList13 cursor with hold for
                  select callbackdivision.BranchNo,
                     callbackdivision.DivisionName,
                     callbackdivision.MailingList,
                     callbackdivision.CallbackDivisionNo
                from CALLBACKDIVISION
                  where CallbackDivision.BranchNo	 =	:d->BRANCHNO	 and
                        CallbackDivision.CallbackDivisionNo	>=	:d->CALLBACKSTART	 and
                        CallbackDivision.CallbackDivisionNo	 <	:d->CALLBACKEND	
                        order by CallbackDivision.BranchNo,CallbackDivision.DivisionName;
        exec sql open CSelList13;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList13" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList13;
        return CheckSql( fun, stError, "%s", "close CSelList13" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList13 into :d->BRANCHNO,
                     :d->DIVISIONNAME,
                     :d->MAILINGLIST,
                     :d->CALLBACKDIVISIONNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList13" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackDivision::SelListAll ***********************************************/

retClient Callbackdivision_SelListAll(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackdivision_SelListAll";
    exec sql begin declare section;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListAll14 cursor with hold for
                  select callbackdivision.BranchNo,
                     callbackdivision.DivisionName,
                     callbackdivision.MailingList,
                     callbackdivision.CallbackDivisionNo
                from CALLBACKDIVISION
                  where CallbackDivision.BranchNo in 
                        (select RegionArten.RegionTeilNr from RegionArten
                         where RegionArten.RegionNr	 =	:d->BRANCHNO and
                        RegionArten.RegionenTyp=1	) and
                        CallbackDivision.CallbackDivisionNo	>=	:d->CALLBACKSTART	 and
                        CallbackDivision.CallbackDivisionNo	 <	:d->CALLBACKEND
                        order by CallbackDivision.BranchNo,CallbackDivision.DivisionName;
        exec sql open CSelListAll14;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListAll14" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListAll14;
        return CheckSql( fun, stError, "%s", "close CSelListAll14" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListAll14 into :d->BRANCHNO,
                     :d->DIVISIONNAME,
                     :d->MAILINGLIST,
                     :d->CALLBACKDIVISIONNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListAll14" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackDivision: Insert ***************************************************/



/* CallbackDivision: Update ***************************************************/

/* CallbackDivision::Update ***************************************************/

retClient Callbackdivision_Update(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackdivision_Update";
    exec sql begin declare section;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->MAILINGLIST);
    if ( *d->MAILINGLIST == '\0' )
        strcpy( d->MAILINGLIST, " " );


    exec sql declare CUpdate15 cursor with hold for
              select BranchNo,
                     DivisionName,
                     MailingList,
                     CallbackDivisionNo
               from CALLBACKDIVISION
              where CallbackDivision.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackDivision.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO
              for update;
    exec sql open CUpdate15;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate15" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate15;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate15" ) ) != IS_OK )
            break;
        exec sql update callbackdivision set BranchNo = :d->BRANCHNO,
                     DivisionName = :d->DIVISIONNAME,
                     MailingList = :d->MAILINGLIST,
                     CallbackDivisionNo = :d->CALLBACKDIVISIONNO where current of CUpdate15;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate15" ) ) != IS_OK )
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



/* CallbackDivision: Select ***************************************************/

/* CallbackDivision::Delete ***************************************************/

retClient Callbackdivision_Delete(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackdivision_Delete";
    exec sql begin declare section;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete16 cursor with hold for
              select BranchNo,
                     DivisionName,
                     MailingList,
                     CallbackDivisionNo
               from CALLBACKDIVISION
              where CallbackDivision.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackDivision.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO
              for update;
    exec sql open CDelete16;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete16" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete16;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete16" ) ) != IS_OK )
            break;
        exec sql delete from callbackdivision where current of CDelete16;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete16" ) ) != IS_OK )
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



/* CallbackDivision: Other ****************************************************/

/* CallbackDivision::InsertWithNewNo ******************************************/

retClient Callbackdivision_InsertWithNewNo(callbackdivisionS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
    retClient rc = IS_OK;
    char *fun = "InsertWithNewNo";

    exec sql begin declare section;
    int iIndicator;
    callbackdivisionS *d;
    exec sql end declare section;

    d = a;

    exec sql select MAX(callbackdivisionno) + 1
               into :d->CALLBACKDIVISIONNO indicator :iIndicator
               from callbackdivision
               where branchno = :d->BRANCHNO
               and callbackdivisionno >= :d->CALLBACKSTART
               and callbackdivisionno < :d->CALLBACKEND;
    if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
      return rc;
    else if ( iIndicator < 0 )
       d->CALLBACKDIVISIONNO = 1; /* start with 1 */

    if ( bIsTrans )
    {
       #if !defined (__S390IBM__) && !defined (__ORACLE__)
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       #endif
    }

    exec sql insert into callbackdivision( branchno,
                                          divisionname,
                                          mailinglist,
                                          callbackdivisionno )
                                  values( :d->BRANCHNO,
                                          :d->DIVISIONNAME,
                                          :d->MAILINGLIST,
                                          :d->CALLBACKDIVISIONNO );
    if ( ( rc=CheckSql( fun, stError, "%s", "insert" ) ) != IS_OK )
    {    
       if ( bIsTrans )
          exec sql rollback work; 
       return rc; /* then an error has occured! */
    }
    
    return Commit( fun, stError );
}



/******************************************************************************/
/*                                                                            */
/* header  : CallbackReasons.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:53 2022                                         */
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
#include "callback.h"

/* CallbackReasons: Select ****************************************************/

/* CallbackReasons::SelList ***************************************************/

retClient Callbackreasons_SelList(callbackreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackreasons_SelList";
    exec sql begin declare section;
    callbackreasonsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList17 cursor with hold for
                  select callbackreasons.ReasonNo,
                     callbackreasons.CallbackReason,
                     callbackreasons.CallbackDivisionNo,
                     callbackreasons.MailingList,
                     callbackreasons.BranchNo,
                     callbackreasons.swOnlyMail
                from CALLBACKREASONS
                  where CallbackReasons.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO	 and
                        CallbackReasons.BranchNo	 =	:d->BRANCHNO	
                        order by CallbackReasons.BranchNo,CallbackReasons.CallbackReason;
        exec sql open CSelList17;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList17" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList17;
        return CheckSql( fun, stError, "%s", "close CSelList17" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList17 into :d->REASONNO,
                     :d->CALLBACKREASON,
                     :d->CALLBACKDIVISIONNO,
                     :d->MAILINGLIST,
                     :d->BRANCHNO,
                     :d->SWONLYMAIL;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList17" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackReasons: Insert ****************************************************/



/* CallbackReasons: Update ****************************************************/

/* CallbackReasons::Update ****************************************************/

retClient Callbackreasons_Update(callbackreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackreasons_Update";
    exec sql begin declare section;
    callbackreasonsS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->MAILINGLIST);
    if ( *d->MAILINGLIST == '\0' )
        strcpy( d->MAILINGLIST, " " );


    exec sql declare CUpdate18 cursor with hold for
              select ReasonNo,
                     CallbackReason,
                     CallbackDivisionNo,
                     MailingList,
                     BranchNo,
                     swOnlyMail
               from CALLBACKREASONS
              where CallbackReasons.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackReasons.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO	 and
                    CallbackReasons.ReasonNo	 =	:d->REASONNO
              for update;
    exec sql open CUpdate18;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate18" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate18;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate18" ) ) != IS_OK )
            break;
        exec sql update callbackreasons set ReasonNo = :d->REASONNO,
                     CallbackReason = :d->CALLBACKREASON,
                     CallbackDivisionNo = :d->CALLBACKDIVISIONNO,
                     MailingList = :d->MAILINGLIST,
                     BranchNo = :d->BRANCHNO,
                     swOnlyMail = :d->SWONLYMAIL where current of CUpdate18;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate18" ) ) != IS_OK )
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



/* CallbackReasons: Select ****************************************************/

/* CallbackReasons::Delete ****************************************************/

retClient Callbackreasons_Delete(callbackreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackreasons_Delete";
    exec sql begin declare section;
    callbackreasonsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete19 cursor with hold for
              select ReasonNo,
                     CallbackReason,
                     CallbackDivisionNo,
                     MailingList,
                     BranchNo,
                     swOnlyMail
               from CALLBACKREASONS
              where CallbackReasons.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackReasons.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO	 and
                    CallbackReasons.ReasonNo	 =	:d->REASONNO
              for update;
    exec sql open CDelete19;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete19" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete19;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete19" ) ) != IS_OK )
            break;
        exec sql delete from callbackreasons where current of CDelete19;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete19" ) ) != IS_OK )
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

/* CallbackReasons::DeleteAllNo ***********************************************/

retClient Callbackreasons_DeleteAllNo(callbackreasonsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Callbackreasons_DeleteAllNo";
    exec sql begin declare section;
    callbackreasonsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllNo20 cursor with hold for
              select ReasonNo,
                     CallbackReason,
                     CallbackDivisionNo,
                     MailingList,
                     BranchNo,
                     swOnlyMail
               from CALLBACKREASONS
              where CallbackReasons.BranchNo	 =	:d->BRANCHNO	 and
                    CallbackReasons.CallbackDivisionNo	 =	:d->CALLBACKDIVISIONNO
              for update;
    exec sql open CDeleteAllNo20;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllNo20" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllNo20;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllNo20" ) ) != IS_OK )
            break;
        exec sql delete from callbackreasons where current of CDeleteAllNo20;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllNo20" ) ) != IS_OK )
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



/* CallbackReasons: Other *****************************************************/

/* CallbackReasons::InsertWithNewNo *******************************************/

retClient Callbackreasons_InsertWithNewNo(callbackreasonsS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
    retClient rc = IS_OK;
    char *fun = "InsertWithNewNo";

    exec sql begin declare section;
    int iIndicator;
    callbackreasonsS *d;
    exec sql end declare section;

    d = a;

    exec sql select MAX(reasonno) + 1
               into :d->REASONNO indicator :iIndicator
               from callbackreasons
               where branchno = :d->BRANCHNO
               and callbackdivisionno = :d->CALLBACKDIVISIONNO;
    if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
      return rc;
    else if ( iIndicator < 0 )
       d->REASONNO = 1; /* start with 1 */

    if ( bIsTrans )
    {
       #if !defined (__S390IBM__) && !defined (__ORACLE__)
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
       #endif
    }

    exec sql insert into callbackreasons( reasonno,
                                          callbackreason,
                                          callbackdivisionno,
                                          mailinglist,
                                          branchno )
                                  values( :d->REASONNO,
                                          :d->CALLBACKREASON,
                                          :d->CALLBACKDIVISIONNO,
                                          :d->MAILINGLIST,
                                          :d->BRANCHNO );
    if ( ( rc=CheckSql( fun, stError, "%s", "insert" ) ) != IS_OK )
    {    
       if ( bIsTrans )
          exec sql rollback work; 
       return rc; /* then an error has occured! */
    }
    
    return Commit( fun, stError );
}



/******************************************************************************/
/*                                                                            */
/* header  : CallbackRemarks.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:57 2022                                         */
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
#include "callback.h"

/* CallbackRemarks: Select ****************************************************/

/* CallbackRemarks::SelList ***************************************************/

retClient Callbackremarks_SelList(callbackremarksS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackremarks_SelList";
    exec sql begin declare section;
    callbackremarksS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList21 cursor with hold for
                  select callbackremarks.RemarkNo,
                     callbackremarks.CallbackRemarkText,
                     callbackremarks.CallbackRemarkHeader
                from CALLBACKREMARKS
                  where CallbackRemarks.RemarkNo	 >	0;
        exec sql open CSelList21;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList21" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList21;
        return CheckSql( fun, stError, "%s", "close CSelList21" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList21 into :d->REMARKNO,
                     :d->CALLBACKREMARKTEXT,
                     :d->CALLBACKREMARKHEADER;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList21" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackRemarks::SelRemark *************************************************/

retClient Callbackremarks_SelRemark(callbackremarksS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackremarks_SelRemark";
    exec sql begin declare section;
    callbackremarksS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select callbackremarks.RemarkNo,
                     callbackremarks.CallbackRemarkText,
                     callbackremarks.CallbackRemarkHeader
                into :d->REMARKNO,
                     :d->CALLBACKREMARKTEXT,
                     :d->CALLBACKREMARKHEADER
                from CALLBACKREMARKS
              where CallbackRemarks.RemarkNo	 =	:d->REMARKNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackRemarks: Insert ****************************************************/

/* CallbackRemarks::Insert ****************************************************/

retClient Callbackremarks_Insert(callbackremarksS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbackremarks_Insert";
    exec sql begin declare section;
    callbackremarksS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->CALLBACKREMARKTEXT);
    if ( *d->CALLBACKREMARKTEXT == '\0' )
        strcpy( d->CALLBACKREMARKTEXT, " " );
    ppGStripLast(d->CALLBACKREMARKHEADER);
    if ( *d->CALLBACKREMARKHEADER == '\0' )
        strcpy( d->CALLBACKREMARKHEADER, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into callbackremarks (RemarkNo,
                     CallbackRemarkText,
                     CallbackRemarkHeader)
        values (:d->REMARKNO,
                     :d->CALLBACKREMARKTEXT,
                     :d->CALLBACKREMARKHEADER);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert callbackremarks" ) ) != IS_OK )
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



/* CallbackRemarks: Update ****************************************************/

/* CallbackRemarks::Update ****************************************************/

retClient Callbackremarks_Update(callbackremarksS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackremarks_Update";
    exec sql begin declare section;
    callbackremarksS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->CALLBACKREMARKTEXT);
    if ( *d->CALLBACKREMARKTEXT == '\0' )
        strcpy( d->CALLBACKREMARKTEXT, " " );
    ppGStripLast(d->CALLBACKREMARKHEADER);
    if ( *d->CALLBACKREMARKHEADER == '\0' )
        strcpy( d->CALLBACKREMARKHEADER, " " );


    exec sql declare CUpdate23 cursor with hold for
              select CallbackRemarkText,
                     CallbackRemarkHeader
               from CALLBACKREMARKS
              where CallbackRemarks.RemarkNo	 =	:d->REMARKNO
              for update;
    exec sql open CUpdate23;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate23" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate23;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate23" ) ) != IS_OK )
            break;
        exec sql update callbackremarks set CallbackRemarkText = :d->CALLBACKREMARKTEXT,
                     CallbackRemarkHeader = :d->CALLBACKREMARKHEADER where current of CUpdate23;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate23" ) ) != IS_OK )
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



/* CallbackRemarks: Select ****************************************************/

/* CallbackRemarks::DeleteRemark **********************************************/

retClient Callbackremarks_DeleteRemark(callbackremarksS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Callbackremarks_DeleteRemark";
    exec sql begin declare section;
    callbackremarksS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteRemark24 cursor with hold for
              select RemarkNo,
                     CallbackRemarkText,
                     CallbackRemarkHeader
               from CALLBACKREMARKS
              where CallbackRemarks.RemarkNo	 =	:d->REMARKNO
              for update;
    exec sql open CDeleteRemark24;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteRemark24" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteRemark24;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteRemark24" ) ) != IS_OK )
            break;
        exec sql delete from callbackremarks where current of CDeleteRemark24;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteRemark24" ) ) != IS_OK )
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



/* CallbackRemarks: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CallbackToDo.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:49:07 2022                                         */
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
#include "callback.h"

/* CallbackToDo: Select *******************************************************/

/* CallbackToDo::SelAllLocked *************************************************/

retClient Callbacktodo_SelAllLocked(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelAllLocked";
    exec sql begin declare section;
    callbacktodoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllLocked25 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKPARTNER,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackpartner.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'1' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelAllLocked25;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllLocked25" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllLocked25;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllLocked25" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelAllLockedVz ***********************************************/

retClient Callbacktodo_SelAllLockedVz(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelAllLockedVz";
    exec sql begin declare section;
    callbacktodoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllLockedVz26 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKPARTNER,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackpartner.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'1' and
                        kdkritik.VertriebszentrumNr  	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelAllLockedVz26;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllLockedVz26" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllLockedVz26;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllLockedVz26" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelAllNotDone ************************************************/

retClient Callbacktodo_SelAllNotDone(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelAllNotDone";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllNotDone27 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKPARTNER,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackpartner.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished + callbackitems.callbacktime	<	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelAllNotDone27;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllNotDone27" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllNotDone27;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllNotDone27" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelAllNotDoneVz **********************************************/

retClient Callbacktodo_SelAllNotDoneVz(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelAllNotDoneVz";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllNotDoneVz28 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKPARTNER,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackpartner.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished + callbackitems.callbacktime	<	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelAllNotDoneVz28;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllNotDoneVz28" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllNotDoneVz28;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllNotDoneVz28" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackFuture ********************************************/

retClient Callbacktodo_SelCallbackFuture(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackFuture";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackFuture29 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.callbackpartno	 =	callbackpartner.callbackpartno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'0' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1)
                        order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackFuture29;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackFuture29" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackFuture29;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackFuture29" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackFutureVz ******************************************/

retClient Callbacktodo_SelCallbackFutureVz(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackFutureVz";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackFutureVz30 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR and
                        callbackattach.VertriebszentrumNr	 =	kdkritik.VertriebszentrumNr and
                        callbackattach.callbackpartno	 =	callbackpartner.callbackpartno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'0' and
                        kdkritik.VertriebszentrumNr	=	:d->VERTRIEBSZENTRUMNR	
                        order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackFutureVz30;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackFutureVz30" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackFutureVz30;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackFutureVz30" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackOpen **********************************************/

retClient Callbacktodo_SelCallbackOpen(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackOpen";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackOpen31 cursor with hold for
                 select callbackitems.callbackno,
                        callbackpartner.callbackpartno,
                        kdkritik.idfnr,
                        callbackpartner.callbackpartner,
                        callbackitems.kritiknr,
                        callbackitems.posnr,
                        kdkritikpos.kritiktext,
                        kdkritik.titel,
                        callbackitems.kzposart,
                        callbackitems.callbacktimewished,
                        kdkritik.VertriebszentrumNr,
                        callbackitems.callbackdatewished,
                        callbackitems.state,
                        kunde.nameapo,
                        callbackitems.shiftcount,
                        kunde.ort,
                        kunde.kzkdklasse,
                        callbackitems.reference,
                        callbackstatus.callbackstatusname
                   into :d->CALLBACKNO,
                        :d->CALLBACKPARTNO,
                        :d->IDFNR,
                        :d->CALLBACKPARTNER,
                        :d->KRITIKNR,
                        :d->POSNR,
                        :d->KRITIKTEXT,
                        :d->TITEL,
                        :d->KZPOSART,
                        :d->CALLBACKTIMEWISHED,
                        :d->VERTRIEBSZENTRUMNR,
                        :d->CALLBACKDATEWISHED,
                        :d->STATE,
                        :d->NAMEAPO,
                        :d->SHIFTCOUNT,
                        :d->ORT,
                        :d->KZKDKLASSE,
                        :d->REFERENCE,
                        :d->STATUS
            from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE, CALLBACKSTATUS
            where callbackattach.uid = :d->UID and
                  callbackattach.filialnr = :d->FILIALNR and
                  callbackattach.callbackpartno = callbackpartner.callbackpartno and
                  callbackattach.callbackpartno = callbackitems.callbackpartno and
                  callbackitems.kritiknr = kdkritik.kritiknr and
                  kdkritikpos.kritiknr = kdkritik.kritiknr and
                  kdkritik.VertriebszentrumNr = kunde.VertriebszentrumNr and
                  callbackitems.posnr = kdkritikpos.posnr and
                  callbackitems.kzposart = kdkritikpos.kzposart and
                  callbackitems.callbackstatusid = callbackstatus.callbackstatusid and
                  callbackitems.posnr_done = 0 and
                        (callbackitems.state = '0' or
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	<=	:d->CALLBACKTIMEWISHED	) ) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                  callbackitems.lockkz = '0' and
                  kdkritik.VertriebszentrumNr in
                  (select RegionArten.RegionTeilNr from RegionArten
                      where RegionArten.RegionNr = :d->REGIONNR and
                      RegionArten.RegionenTyp = 1)
               order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackOpen31;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackOpen31" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCallbackOpen31;
        return CheckSql( fun, stError, "%s", "close CSelCallbackOpen31" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackOpen31;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackOpen31" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackOpenVz ********************************************/

retClient Callbacktodo_SelCallbackOpenVz(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackOpenVz";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackOpenVz32 cursor with hold for
                 select callbackitems.callbackno,
                        callbackpartner.callbackpartno,
                        kdkritik.idfnr,
                        callbackpartner.callbackpartner,
                        callbackitems.kritiknr,
                        callbackitems.posnr,
                        kdkritikpos.kritiktext,
                        kdkritik.titel,
                        callbackitems.kzposart,
                        callbackitems.callbacktimewished,
                        kdkritik.VertriebszentrumNr,
                        callbackitems.callbackdatewished,
                        callbackitems.state,
                        kunde.nameapo,
                        callbackitems.shiftcount,
                        kunde.ort,
                        kunde.kzkdklasse,
                        callbackitems.reference,
                        callbackstatus.callbackstatusname
                   into :d->CALLBACKNO,
                        :d->CALLBACKPARTNO,
                        :d->IDFNR,
                        :d->CALLBACKPARTNER,
                        :d->KRITIKNR,
                        :d->POSNR,
                        :d->KRITIKTEXT,
                        :d->TITEL,
                        :d->KZPOSART,
                        :d->CALLBACKTIMEWISHED,
                        :d->VERTRIEBSZENTRUMNR,
                        :d->CALLBACKDATEWISHED,
                        :d->STATE,
                        :d->NAMEAPO,
                        :d->SHIFTCOUNT,
                        :d->ORT,
                        :d->KZKDKLASSE,
                        :d->REFERENCE,
                        :d->STATUS
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE, CALLBACKSTATUS
                  where callbackattach.uid = : d->UID and
                        callbackattach.filialnr = : d->FILIALNR and
                        callbackattach.VertriebszentrumNr = : d->VERTRIEBSZENTRUMNR and
                        callbackattach.callbackpartno = callbackpartner.callbackpartno and
                        callbackattach.callbackpartno = callbackitems.callbackpartno and
                        callbackitems.kritiknr = kdkritik.kritiknr and
                        kdkritikpos.kritiknr = kdkritik.kritiknr and
                        callbackitems.posnr = kdkritikpos.posnr and
                        callbackitems.kzposart = kdkritikpos.kzposart and
                        callbackitems.posnr_done = 0 and
                        (callbackitems.state = '0' or
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	<=	:d->CALLBACKTIMEWISHED	) ) ) and
                        kdkritik.idfnr = kunde.idfnr and
                        kdkritik.VertriebszentrumNr = kunde.VertriebszentrumNr and
                        callbackattach.VertriebszentrumNr = kunde.VertriebszentrumNr and
                        callbackitems.callbackstatusid = callbackstatus.callbackstatusid and
                        callbackitems.lockkz = '0' and
                        kdkritik.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR
               order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackOpenVz32;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackOpenVz32" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCallbackOpenVz32;
        return CheckSql( fun, stError, "%s", "close CSelCallbackOpenVz32" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackOpenVz32;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackOpenVz32" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackWished ********************************************/

retClient Callbacktodo_SelCallbackWished(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackWished";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackWished33 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.callbackpartno	 =	callbackpartner.callbackpartno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'1' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr =  :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelCallbackWished33;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackWished33" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackWished33;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackWished33" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDo::SelCallbackWishedVz ******************************************/

retClient Callbacktodo_SelCallbackWishedVz(callbacktodoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodo_SelCallbackWishedVz";
    exec sql begin declare section;
    callbacktodoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackWishedVz34 cursor with hold for
                  select callbackitems.callbackno,
callbackpartner.callbackpartno,
kdkritik.idfnr,
callbackpartner.callbackpartner,
callbackitems.kritiknr,
callbackitems.posnr,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->CALLBACKPARTNO,
:d->IDFNR,
:d->CALLBACKPARTNER,
:d->KRITIKNR,
:d->POSNR,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKPARTNER, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR and
                        callbackattach.callbackpartno	 =	callbackpartner.callbackpartno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackattach.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'1' and
                        kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelCallbackWishedVz34;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackWishedVz34" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackWishedVz34;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackWishedVz34" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackToDo: Insert *******************************************************/



/* CallbackToDo: Update *******************************************************/



/* CallbackToDo: Select *******************************************************/



/* CallbackToDo: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CallbackToDoNew.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:49:17 2022                                         */
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
#include "callback.h"

/* CallbackToDoNew: Select ****************************************************/

/* CallbackToDoNew::SelAllLocked **********************************************/

retClient Callbacktodonew_SelAllLocked(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelAllLocked";
    exec sql begin declare section;
    callbacktodonewS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllLocked35 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackdivision.callbackdivisionno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'1' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelAllLocked35;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllLocked35" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllLocked35;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllLocked35" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelAllLockedVz ********************************************/

retClient Callbacktodonew_SelAllLockedVz(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelAllLockedVz";
    exec sql begin declare section;
    callbacktodonewS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllLockedVz36 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackdivision.callbackdivisionno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'1' and
                        kdkritik.VertriebszentrumNr  	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelAllLockedVz36;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllLockedVz36" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllLockedVz36;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllLockedVz36" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelAllNotDone *********************************************/

retClient Callbacktodonew_SelAllNotDone(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelAllNotDone";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllNotDone37 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackdivision.callbackdivisionno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished + callbackitems.callbacktime	<	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelAllNotDone37;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllNotDone37" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllNotDone37;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllNotDone37" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelAllNotDoneVz *******************************************/

retClient Callbacktodonew_SelAllNotDoneVz(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelAllNotDoneVz";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllNotDoneVz38 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackdivision.callbackdivisionno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished + callbackitems.callbacktime	<	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelAllNotDoneVz38;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllNotDoneVz38" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAllNotDoneVz38;
        return CheckSql( fun, stError, "%s", "close CSelAllNotDoneVz38" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllNotDoneVz38;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllNotDoneVz38" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackFuture *****************************************/

retClient Callbacktodonew_SelCallbackFuture(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackFuture";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackFuture39 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.callbackpartno	 =	callbackdivision.callbackdivisionno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackattach.reasonno	 =	callbackitems.reasonno and
                        callbackattach.VertriebszentrumNr	 =	kdkritik.VertriebszentrumNr and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'0' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :d->REGIONNR and 
                               RegionArten.RegionenTyp=1)
                        order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackFuture39;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackFuture39" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackFuture39;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackFuture39" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackFutureVz ***************************************/

retClient Callbacktodonew_SelCallbackFutureVz(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackFutureVz";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackFutureVz40 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKDIVISION,CALLBACKITEMS,KUNDE,KDKRITIK,KDKRITIKPOS
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR and
                        callbackattach.VertriebszentrumNr	 =	kdkritik.VertriebszentrumNr and
                        callbackattach.callbackpartno	 =	callbackdivision.callbackdivisionno and
                        callbackattach.reasonno	 =	callbackitems.reasonno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'0' and
                        kdkritik.VertriebszentrumNr	=	:d->VERTRIEBSZENTRUMNR	
                        order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackFutureVz40;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackFutureVz40" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackFutureVz40;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackFutureVz40" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackOpen *******************************************/

retClient Callbacktodonew_SelCallbackOpen(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackOpen";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackOpen41 cursor with hold for
                 select callbackitems.callbackno,
                        kdkritik.idfnr,
                        callbackdivision.DivisionName,
                        callbackitems.kritiknr,
                        callbackitems.posnr,
                        callbackdivision.CallbackDivisionNo,
                        kdkritikpos.kritiktext,
                        kdkritik.titel,
                        callbackitems.kzposart,
                        callbackitems.callbacktimewished,
                        kdkritik.VertriebszentrumNr,
                        callbackitems.callbackdatewished,
                        kdkritik.kritiklevel,
                        callbackitems.state,
                        kunde.nameapo,
                        callbackitems.shiftcount,
                        kunde.ort,
                        kunde.kzkdklasse,
                        callbackitems.reference,
                        callbackstatus.callbackstatusname
                   into :d->CALLBACKNO,
                        :d->IDFNR,
                        :d->DIVISIONNAME,
                        :d->KRITIKNR,
                        :d->POSNR,
                        :d->CALLBACKDIVISIONNO,
                        :d->KRITIKTEXT,
                        :d->TITEL,
                        :d->KZPOSART,
                        :d->CALLBACKTIMEWISHED,
                        :d->VERTRIEBSZENTRUMNR,
                        :d->CALLBACKDATEWISHED,
                        :d->KRITIKLEVEL,
                        :d->STATE,
                        :d->NAMEAPO,
                        :d->SHIFTCOUNT,
                        :d->ORT,
                        :d->KZKDKLASSE,
                        :d->REFERENCE,
                        :d->STATUS
                    from CALLBACKATTACH, CALLBACKITEMS, CALLBACKDIVISION, KDKRITIK, KDKRITIKPOS, KUNDE, CALLBACKSTATUS
                   where callbackattach.uid = :d->UID and
                         callbackattach.filialnr = :d->FILIALNR and
                         callbackattach.callbackpartno = callbackdivision.callbackdivisionno and
                         callbackattach.callbackpartno = callbackitems.callbackpartno and
                         callbackattach.reasonno = callbackitems.reasonno and
                         callbackattach.VertriebszentrumNr = kdkritik.VertriebszentrumNr and
                         callbackitems.kritiknr = kdkritik.kritiknr and
                         kdkritikpos.kritiknr = kdkritik.kritiknr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                         callbackitems.posnr = kdkritikpos.posnr and
                         callbackitems.kzposart = kdkritikpos.kzposart and
                         callbackitems.callbackstatusid = callbackstatus.callbackstatusid and
                         callbackitems.posnr_done = 0 and
                        (callbackitems.state = '0' or
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	<=	:d->CALLBACKTIMEWISHED	) ) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr in
                           (select RegionArten.RegionTeilNr from RegionArten
                            where RegionArten.RegionNr = :d->REGIONNR and 
                            RegionArten.RegionenTyp = 1)
               order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackOpen41;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackOpen41" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCallbackOpen41;
        return CheckSql( fun, stError, "%s", "close CSelCallbackOpen41" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackOpen41;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackOpen41" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackOpenVz *****************************************/

retClient Callbacktodonew_SelCallbackOpenVz(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackOpenVz";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackOpenVz42 cursor with hold for
                 select callbackitems.callbackno,
                        kdkritik.idfnr,
                        callbackdivision.DivisionName,
                        callbackitems.kritiknr,
                        callbackitems.posnr,
                        callbackdivision.CallbackDivisionNo,
                        kdkritikpos.kritiktext,
                        kdkritik.titel,
                        callbackitems.kzposart,
                        callbackitems.callbacktimewished,
                        kdkritik.VertriebszentrumNr,
                        callbackitems.callbackdatewished,
                        kdkritik.kritiklevel,
                        callbackitems.state,
                        kunde.nameapo,
                        callbackitems.shiftcount,
                        kunde.ort,
                        kunde.kzkdklasse,
                        callbackitems.reference,
                        callbackstatus.callbackstatusname
                   into :d->CALLBACKNO,
                        :d->IDFNR,
                        :d->DIVISIONNAME,
                        :d->KRITIKNR,
                        :d->POSNR,
                        :d->CALLBACKDIVISIONNO,
                        :d->KRITIKTEXT,
                        :d->TITEL,
                        :d->KZPOSART,
                        :d->CALLBACKTIMEWISHED,
                        :d->VERTRIEBSZENTRUMNR,
                        :d->CALLBACKDATEWISHED,
                        :d->KRITIKLEVEL,
                        :d->STATE,
                        :d->NAMEAPO,
                        :d->SHIFTCOUNT,
                        :d->ORT,
                        :d->KZKDKLASSE,
                        :d->REFERENCE,
                        :d->STATUS
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKDIVISION, KDKRITIK, KDKRITIKPOS, KUNDE, CALLBACKSTATUS
                  where callbackattach.uid = :d->UID and
                        callbackattach.filialnr = :d->FILIALNR and
                        callbackattach.VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR and
                        callbackattach.callbackpartno = callbackdivision.callbackdivisionno and
                        callbackattach.callbackpartno = callbackitems.callbackpartno and
                        callbackattach.reasonno = callbackitems.reasonno and
                        callbackattach.VertriebszentrumNr = kdkritik.VertriebszentrumNr and
                        callbackitems.kritiknr = kdkritik.kritiknr and
                        kdkritikpos.kritiknr = kdkritik.kritiknr and
                        callbackitems.posnr = kdkritikpos.posnr and
                        callbackitems.kzposart = kdkritikpos.kzposart and
                        callbackitems.callbackstatusid = callbackstatus.callbackstatusid and
                        callbackitems.posnr_done = 0 and
                        (callbackitems.state = '0' or
                        ( callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	<=	:d->CALLBACKTIMEWISHED	) ) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackattach.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	
               order by callbackitems.callbackdatewished, callbackitems.callbacktimewished;
        exec sql open CSelCallbackOpenVz42;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackOpenVz42" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCallbackOpenVz42;
        return CheckSql( fun, stError, "%s", "close CSelCallbackOpenVz42" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackOpenVz42;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackOpenVz42" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackWished *****************************************/

retClient Callbacktodonew_SelCallbackWished(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackWished";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackWished43 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKDIVISION, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.callbackpartno	 =	callbackdivision.callbackdivisionno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackattach.reasonno	 =	callbackitems.reasonno and
                        callbackattach.VertriebszentrumNr	 =	kdkritik.VertriebszentrumNr and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'1' and
                        kdkritik.VertriebszentrumNr in
                        (select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr =  :d->REGIONNR and 
                               RegionArten.RegionenTyp=1);
        exec sql open CSelCallbackWished43;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackWished43" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackWished43;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackWished43" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CallbackToDoNew::SelCallbackWishedVz ***************************************/

retClient Callbacktodonew_SelCallbackWishedVz(callbacktodonewS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Callbacktodonew_SelCallbackWishedVz";
    exec sql begin declare section;
    callbacktodonewS *d;
    long lDate;
    exec sql end declare section;

    d = a;

       d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackWishedVz44 cursor with hold for
                  select callbackitems.callbackno,
kdkritik.idfnr,
callbackdivision.DivisionName,
callbackitems.kritiknr,
callbackitems.posnr,
callbackdivision.CallbackDivisionNo,
kdkritikpos.kritiktext,
kdkritik.titel,
callbackitems.kzposart,
callbackitems.callbacktimewished,
kdkritik.VertriebszentrumNr,
callbackitems.callbackdatewished,
kdkritik.kritiklevel,
callbackitems.state,
kunde.nameapo,
callbackitems.shiftcount,
kunde.ort,
kunde.kzkdklasse
                         into :d->CALLBACKNO,
:d->IDFNR,
:d->DIVISIONNAME,
:d->KRITIKNR,
:d->POSNR,
:d->CALLBACKDIVISIONNO,
:d->KRITIKTEXT,
:d->TITEL,
:d->KZPOSART,
:d->CALLBACKTIMEWISHED,
:d->VERTRIEBSZENTRUMNR,
:d->CALLBACKDATEWISHED,
:d->KRITIKLEVEL,
:d->STATE,
:d->NAMEAPO,
:d->SHIFTCOUNT,
:d->ORT,
:d->KZKDKLASSE
                   from CALLBACKATTACH, CALLBACKITEMS, CALLBACKDIVISION, KDKRITIK, KDKRITIKPOS, KUNDE
                  where callbackattach.uid	 =	:d->UID	and
                        callbackattach.filialnr	 =	:d->FILIALNR	and
                        callbackattach.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR and
                        callbackattach.callbackpartno	 =	callbackdivision.callbackdivisionno and
                        callbackattach.callbackpartno	 =	callbackitems.callbackpartno and
                        callbackattach.reasonno	 =	callbackitems.reasonno and
                        callbackattach.VertriebszentrumNr	 =	kdkritik.VertriebszentrumNr and
                        callbackitems.kritiknr	 =	kdkritik.kritiknr and
                        kdkritikpos.kritiknr	 =	kdkritik.kritiknr and
                        callbackitems.posnr	 =	kdkritikpos.posnr and
                        callbackitems.kzposart	 =	kdkritikpos.kzposart and
                        callbackitems.posnr_done	=	0 and
                        ( callbackitems.callbackdatewished	 >	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktimewished	>	:d->CALLBACKTIMEWISHED	) ) and
                        kdkritik.idfnr	 =	kunde.idfnr and
                        kdkritik.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        kdkritik.VertriebszentrumNr	 =	callbackdivision.Branchno and
                        callbackattach.VertriebszentrumNr	 =	kunde.VertriebszentrumNr and
                        callbackitems.lockkz	 =	'0' and
                        callbackitems.state	 =	'1' and
                        kdkritik.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR;
        exec sql open CSelCallbackWishedVz44;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackWishedVz44" ) ) != IS_OK )
          return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackWishedVz44;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackWishedVz44" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CallbackToDoNew: Insert ****************************************************/



/* CallbackToDoNew: Update ****************************************************/



/* CallbackToDoNew: Select ****************************************************/



/* CallbackToDoNew: Other *****************************************************/


/* CallbackStatus : Select All *****************************************************/

retClient Callbackstatus_SelectAll(callbackstatusS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Callbackstatus_SelectAll";
    exec sql begin declare section;
    callbackstatusS* d;
    exec sql end declare section;

    d = a;

    if (a->FETCH_REL == SET_OPEN)
    {
        exec sql declare CCallbackstatusSelectAll1 cursor with hold for
            select callbackstatus.Callbackstatusid,
            callbackstatus.Callbackstatusname,
            NVL(PARAMETER.wert, 0) as Callbackstatusflag
            from CALLBACKSTATUS
            left join PARAMETER on
            CALLBACKSTATUS.callbackstatusid = PARAMETER.parametername and
            PARAMETER.programmname = 'callbackeditor' and
            PARAMETER.zweck = 'statusinfo'
            order by callbackstatus.Callbackstatusid;
        exec sql open CCallbackstatusSelectAll1;
        if ((rc = CheckSql(fun, stError, "%s", "open CCallbackstatusSelectAll1")) != IS_OK)
            return rc;
    }

    if (a->FETCH_REL == SET_CLOSE)
    {
        if (bIsTrans)
        {
            if ((rc = Commit(fun, stError)) != IS_OK)
                return rc;
        }
        exec sql close CCallbackstatusSelectAll1;
        return CheckSql(fun, stError, "%s", "close CCallbackstatusSelectAll1");
    }

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }
    exec sql fetch CCallbackstatusSelectAll1
       into :d->STATUSID,
            :d->STATUSNAME,
            :d->STATUSTAG;
    if ((rc = CheckSql(fun, stError, "%s", "fetch CCallbackstatusSelectAll1")) == IS_ERROR)
        return rc;
    return rc;
}

/******************************************************************************/
/*                                                                            */
/* header  : callbackitems.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:49:23 2022                                         */
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
#include "callback.h"

/* callbackitems: Select ******************************************************/

/* callbackitems::SelCallbackWish *********************************************/

retClient callbackitems_SelCallbackWish(callbackitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "callbackitems_SelCallbackWish";
    exec sql begin declare section;
    callbackitemsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelCallbackWish45 cursor with hold for
                  select callbackitems.callbackno,
                     callbackitems.callbackpartno,
                     callbackitems.kritiknr,
                     callbackitems.posnr,
                     callbackitems.kzposart,
                     callbackitems.posnr_done,
                     callbackitems.callbacktimewished,
                     callbackitems.callbackdatewished,
                     callbackitems.callbacktime,
                     callbackitems.state,
                     callbackitems.lockkz,
                     callbackitems.shiftcount,
                     callbackitems.ReasonNo,
                     callbackitems.reference,
                     callbackitems.callbackstatusid
                from CALLBACKITEMS
                  where callbackitems.kritiknr	 =	:d->KRITIKNR	and
                        callbackitems.posnr	 =	:d->POSNR	and
                        callbackitems.kzposart	 =	:d->KZPOSART;
        exec sql open CSelCallbackWish45;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelCallbackWish45" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelCallbackWish45;
        return CheckSql( fun, stError, "%s", "close CSelCallbackWish45" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelCallbackWish45 into :d->CALLBACKNO,
                     :d->CALLBACKPARTNO,
                     :d->KRITIKNR,
                     :d->POSNR,
                     :d->KZPOSART,
                     :d->POSNR_DONE,
                     :d->CALLBACKTIMEWISHED,
                     :d->CALLBACKDATEWISHED,
                     :d->CALLBACKTIME,
                     :d->STATE,
                     :d->LOCKKZ,
                     :d->SHIFTCOUNT,
                     :d->REASONNO,
                     :d->REFERENCE,
                     :d->STATUSID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelCallbackWish45" )) == IS_ERROR )
        return rc;
    return rc;
}

/* callbackitems::SelNo *******************************************************/

retClient callbackitems_SelNo(callbackitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "callbackitems_SelNo";
    exec sql begin declare section;
    callbackitemsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select callbackitems.callbackno,
                     callbackitems.callbackpartno,
                     callbackitems.kritiknr,
                     callbackitems.posnr,
                     callbackitems.kzposart,
                     callbackitems.posnr_done,
                     callbackitems.callbacktimewished,
                     callbackitems.callbackdatewished,
                     callbackitems.callbacktime,
                     callbackitems.state,
                     callbackitems.lockkz,
                     callbackitems.shiftcount,
                     callbackitems.ReasonNo,
                     callbackitems.reference,
                     callbackitems.callbackstatusid
                into :d->CALLBACKNO,
                     :d->CALLBACKPARTNO,
                     :d->KRITIKNR,
                     :d->POSNR,
                     :d->KZPOSART,
                     :d->POSNR_DONE,
                     :d->CALLBACKTIMEWISHED,
                     :d->CALLBACKDATEWISHED,
                     :d->CALLBACKTIME,
                     :d->STATE,
                     :d->LOCKKZ,
                     :d->SHIFTCOUNT,
                     :d->REASONNO,
                     :d->REFERENCE,
                     :d->STATUSID
                from CALLBACKITEMS
              where callbackitems.callbackno	 =	:d->CALLBACKNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* callbackitems::SelNotDone **************************************************/

retClient callbackitems_SelNotDone(callbackitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "callbackitems_SelNotDone";
    exec sql begin declare section;
    callbackitemsS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    d->CALLBACKTIMEWISHED = ppGGetTime()/100;
    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelNotDone47 cursor with hold for
                  select callbackitems.callbackno,
                     callbackitems.callbackpartno,
                     callbackitems.kritiknr,
                     callbackitems.posnr,
                     callbackitems.kzposart,
                     callbackitems.posnr_done,
                     callbackitems.callbacktimewished,
                     callbackitems.callbackdatewished,
                     callbackitems.callbacktime,
                     callbackitems.state,
                     callbackitems.lockkz,
                     callbackitems.shiftcount,
                     callbackitems.ReasonNo,
                     callbackitems.reference,
                     callbackitems.callbackstatusid
                from CALLBACKITEMS
                  where (callbackitems.callbackdatewished	 <	:lDate or
                        ( callbackitems.callbackdatewished	 =	:lDate and
                        callbackitems.callbacktime +  callbackitems.callbacktimewished 	 <	:d->CALLBACKTIMEWISHED	) )  and
                        callbackitems.lockkz	 =	'0';
        exec sql open CSelNotDone47;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelNotDone47" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelNotDone47;
        return CheckSql( fun, stError, "%s", "close CSelNotDone47" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelNotDone47 into :d->CALLBACKNO,
                     :d->CALLBACKPARTNO,
                     :d->KRITIKNR,
                     :d->POSNR,
                     :d->KZPOSART,
                     :d->POSNR_DONE,
                     :d->CALLBACKTIMEWISHED,
                     :d->CALLBACKDATEWISHED,
                     :d->CALLBACKTIME,
                     :d->STATE,
                     :d->LOCKKZ,
                     :d->SHIFTCOUNT,
                     :d->REASONNO,
                     :d->REFERENCE,
                     :d->STATUSID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelNotDone47" )) == IS_ERROR )
        return rc;
    return rc;
}

/* callbackitems::Sellocked ***************************************************/

retClient callbackitems_Sellocked(callbackitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "callbackitems_Sellocked";
    exec sql begin declare section;
    callbackitemsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSellocked48 cursor with hold for
                  select callbackitems.callbackno,
                     callbackitems.callbackpartno,
                     callbackitems.kritiknr,
                     callbackitems.posnr,
                     callbackitems.kzposart,
                     callbackitems.posnr_done,
                     callbackitems.callbacktimewished,
                     callbackitems.callbackdatewished,
                     callbackitems.callbacktime,
                     callbackitems.state,
                     callbackitems.lockkz,
                     callbackitems.shiftcount,
                     callbackitems.ReasonNo,
                     callbackitems.reference,
                     callbackitems.callbackstatusid
                from CALLBACKITEMS
                  where callbackitems.lockkz	 =	'1';
        exec sql open CSellocked48;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSellocked48" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSellocked48;
        return CheckSql( fun, stError, "%s", "close CSellocked48" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSellocked48 into :d->CALLBACKNO,
                     :d->CALLBACKPARTNO,
                     :d->KRITIKNR,
                     :d->POSNR,
                     :d->KZPOSART,
                     :d->POSNR_DONE,
                     :d->CALLBACKTIMEWISHED,
                     :d->CALLBACKDATEWISHED,
                     :d->CALLBACKTIME,
                     :d->STATE,
                     :d->LOCKKZ,
                     :d->SHIFTCOUNT,
                     :d->REASONNO,
                     :d->REFERENCE,
                     :d->STATUSID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSellocked48" )) == IS_ERROR )
        return rc;
    return rc;
}



/* callbackitems: Insert ******************************************************/



/* callbackitems: Update ******************************************************/

/* callbackitems::UpdateItem **************************************************/

retClient callbackitems_UpdateItem(callbackitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "callbackitems_UpdateItem";
    exec sql begin declare section;
    callbackitemsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CUpdateItem49 cursor with hold for
              select callbackno,
                     callbackpartno,
                     kritiknr,
                     posnr,
                     kzposart,
                     posnr_done,
                     callbacktimewished,
                     callbackdatewished,
                     callbacktime,
                     state,
                     lockkz,
                     shiftcount,
                     ReasonNo,
                     reference,
                     callbackstatusid
               from CALLBACKITEMS
              where callbackitems.callbackno	 =	:d->CALLBACKNO
              for update;
    exec sql open CUpdateItem49;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdateItem49" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdateItem49;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdateItem49" ) ) != IS_OK )
            break;
        exec sql update callbackitems set callbackno = :d->CALLBACKNO,
            callbackpartno = :d->CALLBACKPARTNO,
            kritiknr = :d->KRITIKNR,
            posnr = :d->POSNR,
            kzposart = :d->KZPOSART,
            posnr_done = :d->POSNR_DONE,
            callbacktimewished = :d->CALLBACKTIMEWISHED,
            callbackdatewished = :d->CALLBACKDATEWISHED,
            callbacktime = :d->CALLBACKTIME,
            state = :d->STATE,
            lockkz = :d->LOCKKZ,
            shiftcount = :d->SHIFTCOUNT,
            ReasonNo = :d->REASONNO,
            Reference = : d->REFERENCE,
            callbackstatusid = :d->STATUSID  where current of CUpdateItem49;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdateItem49" ) ) != IS_OK )
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



/* callbackitems: Select ******************************************************/



/* callbackitems: Other *******************************************************/

/* callbackitems::InsertWithNewNo *********************************************/

retClient callbackitems_InsertWithNewNo(callbackitemsS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
    retClient rc = IS_OK;
    char *fun = "InsertWithNewNo";

    exec sql begin declare section;
    int iIndicator;
    callbackitemsS *d;
    exec sql end declare section;

    d = a;

    exec sql select MAX(callbackno) + 1
               into :d->CALLBACKNO indicator :iIndicator
               from callbackitems;
    if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
      return rc;
    else if ( iIndicator < 0 )
       d->CALLBACKNO = 1; /* start with 1 */
    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql insert into callbackitems (callbackitems.callbackno,
                     callbackitems.callbackpartno,
                     callbackitems.kritiknr,
                     callbackitems.posnr,
                     callbackitems.kzposart,
                     callbackitems.posnr_done,
                     callbackitems.callbacktimewished,
                     callbackitems.callbackdatewished,
                     callbackitems.callbacktime,
                     callbackitems.state,
                     callbackitems.lockkz,
                     callbackitems.reasonno,
                     callbackitems.reference,
                     callbackitems.callbackstatusid)
        values (:d->CALLBACKNO,
                     :d->CALLBACKPARTNO,
                     :d->KRITIKNR,
                     :d->POSNR,
                     :d->KZPOSART,
                     :d->POSNR_DONE,
                     :d->CALLBACKTIMEWISHED,
                     :d->CALLBACKDATEWISHED,
                     :d->CALLBACKTIME,
                     :d->STATE,
                     :d->LOCKKZ,
                     :d->REASONNO,
                     :d->REFERENCE,
                     :d->STATUSID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert callbackitems" ) ) != IS_OK )
    {    
       if ( bIsTrans )
          exec sql rollback work; 
       return rc; /* then an error has occured! */
    }
    
    return Commit( fun, stError );
}

