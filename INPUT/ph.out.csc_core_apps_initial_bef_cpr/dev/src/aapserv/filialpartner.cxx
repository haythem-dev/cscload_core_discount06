/******************************************************************************/
/*                                                                            */
/* header  : BackRout.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:24 2022                                         */
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
#include "filialpartner.h"

/* BackRout: Select ***********************************************************/

/* BackRout::SelList **********************************************************/

retClient Backrout_SelList(backroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Backrout_SelList";
    exec sql begin declare section;
    backroutS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select backrouting.BranchNo,
                     backrouting.Departement,
                     backrouting.PhoneNo
                from BACKROUTING
                  where BackRouting.BranchNo	 =	:d->BRANCHNO
                        order by BackRouting.Departement;
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
    exec sql fetch CSelList0 into :d->BRANCHNO,
                     :d->DEPARTEMENT,
                     :d->PHONENO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* BackRout: Insert ***********************************************************/

/* BackRout::Insert ***********************************************************/

retClient Backrout_Insert(backroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Backrout_Insert";
    exec sql begin declare section;
    backroutS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into backrouting (BranchNo,
                     Departement,
                     PhoneNo)
        values (:d->BRANCHNO,
                     :d->DEPARTEMENT,
                     :d->PHONENO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert backrouting" ) ) != IS_OK )
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



/* BackRout: Update ***********************************************************/



/* BackRout: Select ***********************************************************/

/* BackRout::Delete ***********************************************************/

retClient Backrout_Delete(backroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Backrout_Delete";
    exec sql begin declare section;
    backroutS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete1 cursor with hold for
              select BranchNo,
                     Departement,
                     PhoneNo
               from BACKROUTING
              where BackRouting.BranchNo	 =	:d->BRANCHNO	 and
                    BackRouting.Departement	 =	:d->DEPARTEMENT	 and
                    BackRouting.PhoneNo	 =	:d->PHONENO
              for update;
    exec sql open CDelete1;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete1;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete1" ) ) != IS_OK )
            break;
        exec sql delete from backrouting where current of CDelete1;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete1" ) ) != IS_OK )
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



/* BackRout: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : BranchInfo.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:27 2022                                         */
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
#include "filialpartner.h"

/* BranchInfo: Select *********************************************************/

/* BranchInfo::SelInfo ********************************************************/

retClient Branchinfo_SelInfo(branchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Branchinfo_SelInfo";
    exec sql begin declare section;
    branchinfoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select branchinfo.BranchNo,
                     branchinfo.Information,
                     branchinfo.BranchInfoType
                into :d->BRANCHNO,
                     :d->INFORMATION,
                     :d->BRANCHINFOTYPE
                from BRANCHINFO
              where BranchInfo.BranchNo	 =	:d->BRANCHNO and
                    BranchInfo.BranchInfoType	 =	:d->BRANCHINFOTYPE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* BranchInfo: Insert *********************************************************/

/* BranchInfo::Insert *********************************************************/

retClient Branchinfo_Insert(branchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Branchinfo_Insert";
    exec sql begin declare section;
    branchinfoS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->INFORMATION);
    if ( *d->INFORMATION == '\0' )
        strcpy( d->INFORMATION, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into branchinfo (BranchNo,
                     Information,
                     BranchInfoType)
        values (:d->BRANCHNO,
                     :d->INFORMATION,
                     :d->BRANCHINFOTYPE);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert branchinfo" ) ) != IS_OK )
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



/* BranchInfo: Update *********************************************************/

/* BranchInfo::Update *********************************************************/

retClient Branchinfo_Update(branchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Branchinfo_Update";
    exec sql begin declare section;
    branchinfoS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->INFORMATION);
    if ( *d->INFORMATION == '\0' )
        strcpy( d->INFORMATION, " " );


    exec sql declare CUpdate3 cursor with hold for
              select BranchNo,
                     Information,
                     BranchInfoType
               from BRANCHINFO
              where BranchInfo.BranchNo	 =	:d->BRANCHNO and
                    BranchInfo.BranchInfoType	 =	:d->BRANCHINFOTYPE
              for update;
    exec sql open CUpdate3;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate3" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate3;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate3" ) ) != IS_OK )
            break;
        exec sql update branchinfo set BranchNo = :d->BRANCHNO,
                     Information = :d->INFORMATION,
                     BranchInfoType = :d->BRANCHINFOTYPE where current of CUpdate3;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate3" ) ) != IS_OK )
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



/* BranchInfo: Select *********************************************************/



/* BranchInfo: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : BranchNames.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:29 2022                                         */
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
#include "filialpartner.h"

/* BranchNames: Select ********************************************************/

/* BranchNames::SelList *******************************************************/

retClient Branchnames_SelList(branchnamesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Branchnames_SelList";
    exec sql begin declare section;
    branchnamesS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList4 cursor with hold for
                  select rechner.filialnr,
                     rechner.rechner_name,
                     rechner.standort,
                     rechner.datenbank_name
                from rechner
                  where rechner.filialnr	 >	0
                        order by rechner.filialnr;
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
    exec sql fetch CSelList4 into :d->FILIALNR,
                     :d->RECHNER_NAME,
                     :d->STANDORT,
                     :d->DATENBANK_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* BranchNames: Insert ********************************************************/



/* BranchNames: Update ********************************************************/



/* BranchNames: Select ********************************************************/



/* BranchNames: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : IbtBranchesAdmin.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:33 2022                                         */
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
#include "filialpartner.h"

/* IbtBranchesAdmin: Select ***************************************************/

/* IbtBranchesAdmin::SelList **************************************************/

retClient Ibtbranchesadmin_SelList(ibtbranchesadminS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Ibtbranchesadmin_SelList";
    exec sql begin declare section;
    ibtbranchesadminS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList5 cursor with hold for
                  select ibtbranches.BranchNo,
                     ibtbranches.priority,
                     ibtbranches.ibtbranchno,
                     ibtbranches.ibttype,
                     ibtbranches.dayibt,
                     ibtbranches.ibtcustomerno,
                     ibtbranches.active_flag,
                     ibtbranches.nlevelibttypeid,
                     ibtbranches.nlevelibtassortmenttypeid,
                     filiale.bganr_ek
                from IBTBRANCHES, FILIALE
                  where ibtbranches.BranchNo	 =	:d->BRANCHNO and	
                        ibtbranches.BranchNo	 =	filiale.filialnr
                        order by ibtbranches.priority;
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
    exec sql fetch CSelList5 into :d->BRANCHNO,
                     :d->PRIORITY,
                     :d->IBTBRANCHNO,
                     :d->IBTTYPE,
                     :d->DAYIBT,
                     :d->IBTCUSTOMERNO,
                     :d->ACTIVE_FLAG,
                     :d->NLEVELIBTTYPEID,
                     :d->NLEVELIBTASSORTMENTTYPEID,
                     :d->BGANR_EK;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList5" )) == IS_ERROR )
        return rc;
    return rc;
}



/* IbtBranchesAdmin: Insert ***************************************************/

/* IbtBranchesAdmin::Insert ***************************************************/

retClient Ibtbranchesadmin_Insert(ibtbranchesadminS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Ibtbranchesadmin_Insert";
    exec sql begin declare section;
    ibtbranchesadminS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into ibtbranches (BranchNo,
                     priority,
                     ibtbranchno,
                     ibttype,
                     dayibt,
                     ibtcustomerno,
                     active_flag,
                     nlevelibttypeid,
                     nlevelibtassortmenttypeid)
        values (:d->BRANCHNO,
                     :d->PRIORITY,
                     :d->IBTBRANCHNO,
                     :d->IBTTYPE,
                     :d->DAYIBT,
                     :d->IBTCUSTOMERNO,
                     :d->ACTIVE_FLAG,
                     :d->NLEVELIBTTYPEID,
                     :d->NLEVELIBTASSORTMENTTYPEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert ibtbranches" ) ) != IS_OK )
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



/* IbtBranchesAdmin: Update ***************************************************/

/* IbtBranchesAdmin::Update ***************************************************/

retClient Ibtbranchesadmin_Update(ibtbranchesadminS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Ibtbranchesadmin_Update";
    exec sql begin declare section;
    ibtbranchesadminS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate6 cursor with hold for
              select BranchNo,
                     priority,
                     ibtbranchno,
                     ibttype,
                     dayibt,
                     ibtcustomerno,
                     active_flag,
                     nlevelibttypeid,
                     nlevelibtassortmenttypeid
               from ibtbranches
              where ibtbranches.BranchNo	 =	:d->BRANCHNO	 and
                    ibtbranches.priority	 =	:d->PRIORITY
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
        exec sql update ibtbranches set BranchNo = :d->BRANCHNO,
                     priority = :d->PRIORITY,
                     ibtbranchno = :d->IBTBRANCHNO,
                     ibttype = :d->IBTTYPE,
                     dayibt = :d->DAYIBT,
                     ibtcustomerno = :d->IBTCUSTOMERNO,
                     active_flag = :d->ACTIVE_FLAG,
                     nlevelibttypeid = :d->NLEVELIBTTYPEID,
                     nlevelibtassortmenttypeid = :d->NLEVELIBTASSORTMENTTYPEID where current of CUpdate6;
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



/* IbtBranchesAdmin: Select ***************************************************/

/* IbtBranchesAdmin::Delete ***************************************************/

retClient Ibtbranchesadmin_Delete(ibtbranchesadminS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Ibtbranchesadmin_Delete";
    exec sql begin declare section;
    ibtbranchesadminS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete7 cursor with hold for
              select BranchNo,
                     priority,
                     ibtbranchno,
                     ibttype,
                     dayibt,
                     ibtcustomerno,
                     active_flag,
                     nlevelibttypeid,
                     nlevelibtassortmenttypeid
               from ibtbranches
              where ibtbranches.BranchNo	 =	:d->BRANCHNO	 and
                    ibtbranches.priority	 =	:d->PRIORITY
              for update;
    exec sql open CDelete7;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete7" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete7;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete7" ) ) != IS_OK )
            break;
        exec sql delete from ibtbranches where current of CDelete7;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete7" ) ) != IS_OK )
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



/* IbtBranchesAdmin: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : NLevelIBTBranches.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:35 2022                                         */
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
#include "filialpartner.h"

/* NLevelIBTBranches: Select **************************************************/

/* NLevelIBTBranches::SelIBTBranches ******************************************/

retClient Nlevelibtbranches_SelIBTBranches(nlevelibtbranchesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Nlevelibtbranches_SelIBTBranches";
    exec sql begin declare section;
    nlevelibtbranchesS *d;
    exec sql end declare section;

    d = a;

        a->WEEKDAY =  ppGGetWeekDay(ppGGetDate(), stError->spError) ;
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelIBTBranches8 cursor with hold for
                  select ibtbranches.BranchNo,
                     ibtbranches.ibtbranchno,
                     ibtbranches.ibttype,
                     zeitarten.zeitbegin,
                     zeitarten.zeitende,
                     ibtbranches.nlevelibttypeid,
                     zeitarten.weekday
                from IBTBRANCHES, ZEITARTEN
                  where ibtbranches.ibtbranchno	 =	zeitarten.zeitschluessel and
                        ibtbranches.BranchNo	 =	zeitarten.VertriebszentrumNr and
                        zeitarten.weekday	 =	:d->WEEKDAY	 and
                        zeitarten.zeitende	!=	0 and
                        zeitarten.zeitart	 =	2
                        order by ibtbranches.ibtbranchno;
        exec sql open CSelIBTBranches8;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelIBTBranches8" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelIBTBranches8;
        return CheckSql( fun, stError, "%s", "close CSelIBTBranches8" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelIBTBranches8 into :d->BRANCHNO,
                     :d->IBTBRANCHNO,
                     :d->IBTTYPE,
                     :d->ZEITBEGIN,
                     :d->ZEITENDE,
                     :d->NLEVELIBTTYPEID,
                     :d->WEEKDAY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelIBTBranches8" )) == IS_ERROR )
        return rc;
    return rc;
}



/* NLevelIBTBranches: Insert **************************************************/



/* NLevelIBTBranches: Update **************************************************/



/* NLevelIBTBranches: Select **************************************************/



/* NLevelIBTBranches: Other ***************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : RegionBranches.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:37 2022                                         */
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
#include "filialpartner.h"

/* RegionBranches: Select *****************************************************/

/* RegionBranches::SelList ****************************************************/

retClient Regionbranches_SelList(regionbranchesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Regionbranches_SelList";
    exec sql begin declare section;
    regionbranchesS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList9 cursor with hold for
                  select regionarten.RegionNr,
                     regionarten.RegionTeilNr,
                     filiale.standort_lang
                from regionarten,filiale
                  where RegionArten.RegionNr	 =	:d->REGIONNR	 and
                        RegionArten.RegionTeilNr	 =	filiale.filialnr and
                        RegionArten.RegionenTyp	 =	1
                        order by filiale.standort_lang;
        exec sql open CSelList9;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList9" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList9;
        return CheckSql( fun, stError, "%s", "close CSelList9" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList9 into :d->REGIONNR,
                     :d->REGIONTEILNR,
                     :d->STANDORT_LANG;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList9" )) == IS_ERROR )
        return rc;
    return rc;
}



/* RegionBranches: Insert *****************************************************/



/* RegionBranches: Update *****************************************************/



/* RegionBranches: Select *****************************************************/



/* RegionBranches: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Regions.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:38 2022                                         */
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
#include "filialpartner.h"

/* Regions: Select ************************************************************/

/* Regions::SelRegion *********************************************************/

retClient Regions_SelRegion(regionsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Regions_SelRegion";
    exec sql begin declare section;
    regionsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select regions.RegionNo,
                     regions.RegionName,
                     regions.RegionBranchNo
                into :d->REGIONNO,
                     :d->REGIONNAME,
                     :d->REGIONBRANCHNO
                from Regions
              where Regions.RegionNo	 =	:d->REGIONNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Regions: Insert ************************************************************/



/* Regions: Update ************************************************************/



/* Regions: Select ************************************************************/



/* Regions: Other *************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : VBFILIALEN.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:41 2022                                         */
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
#include "filialpartner.h"

/* VBFILIALEN: Select *********************************************************/

/* VBFILIALEN::SelVbFilialen **************************************************/

retClient Vbfilialen_SelVbFilialen(vbfilialenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Vbfilialen_SelVbFilialen";
    exec sql begin declare section;
    vbfilialenS *d;
    exec sql end declare section;

    d = a;

        a->WEEKDAY =  ppGGetWeekDay(ppGGetDate(), stError->spError) ;
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelVbFilialen11 cursor with hold for
                  select alternativfiliale.filialnr,
                     alternativfiliale.verbundfilialnr,
                     zeitarten.tagestyp,
                     zeitarten.zeitbegin,
                     zeitarten.zeitende,
                     zeitarten.weekday,
                     alternativfiliale.VbTyp
                from ALTERNATIVFILIALE, ZEITARTEN
                  where verbundfilialnr=zeitschluessel
                        and zeitart = 2
                        and weekday = :d->WEEKDAY
                        and zeitende != 0
                        and zeitarten.VertriebszentrumNr = alternativfiliale.filialnr
                        order by verbundfilialnr;
        exec sql open CSelVbFilialen11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelVbFilialen11" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelVbFilialen11;
        return CheckSql( fun, stError, "%s", "close CSelVbFilialen11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelVbFilialen11 into :d->FILIALNR,
                     :d->VERBUNDFILIALNR,
                     :d->TAGESTYP,
                     :d->ZEITBEGIN,
                     :d->ZEITENDE,
                     :d->WEEKDAY,
                     :d->VBTYP;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelVbFilialen11" )) == IS_ERROR )
        return rc;
    return rc;
}



/* VBFILIALEN: Insert *********************************************************/



/* VBFILIALEN: Update *********************************************************/



/* VBFILIALEN: Select *********************************************************/



/* VBFILIALEN: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : VerbundIdf.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:42 2022                                         */
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
#include "filialpartner.h"

/* VerbundIdf: Select *********************************************************/

/* VerbundIdf::SelVBIdf *******************************************************/

retClient Verbundidf_SelVBIdf(verbundidfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Verbundidf_SelVBIdf";
    exec sql begin declare section;
    verbundidfS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select filiale.filialnr,
                     filiale.bganr_ek
                into :d->FILIALNR,
                     :d->BGANR_EK
                from FILIALE
              where filiale.filialnr	 =	:d->FILIALNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* VerbundIdf: Insert *********************************************************/



/* VerbundIdf: Update *********************************************************/



/* VerbundIdf: Select *********************************************************/



/* VerbundIdf: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ZielFilialen.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:44 2022                                         */
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
#include "filialpartner.h"

/* ZielFilialen: Select *******************************************************/

/* ZielFilialen::SelList ******************************************************/

retClient Zielfilialen_SelList(zielfilialenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Zielfilialen_SelList";
    exec sql begin declare section;
    zielfilialenS *d;
    exec sql end declare section;

    d = a;

    exec sql select rechner_name into :d->RECHNER_NAME from rechner where filialnr = :d->FILIALNR;
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList13 cursor with hold for
                  select filiale.filialnr,
                     rechner.rechner_name,
                     filiale.name
                from FILIALE, RECHNER
                  where filiale.filialnr	!=	:d->FILIALNR	and
                        rechner.rechner_name	 =	:d->RECHNER_NAME	 and
                        rechner.filialnr	 =	filiale.filialnr
                        order by filiale.filialnr;
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
    exec sql fetch CSelList13 into :d->FILIALNR,
                     :d->RECHNER_NAME,
                     :d->NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList13" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ZielFilialen: Insert *******************************************************/



/* ZielFilialen: Update *******************************************************/



/* ZielFilialen: Select *******************************************************/



/* ZielFilialen: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : filialpartner.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:48 2022                                         */
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
#include "filialpartner.h"

/* filialpartner: Select ******************************************************/

/* filialpartner::Sel *********************************************************/

retClient filialpartner_Sel(filialpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "filialpartner_Sel";
    exec sql begin declare section;
    filialpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel14 cursor with hold for
                  select filialpartner.filialnr,
                     filialpartner.name,
                     filialpartner.bganr,
                     filialpartner.support_from,
                     filialpartner.support_until,
                     filialpartner.rechner_name
                from FILIALPARTNER
                  where FilialPartner.filialnr	>=	0
                        order by FilialPartner.filialnr;
        exec sql open CSel14;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel14" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel14;
        return CheckSql( fun, stError, "%s", "close CSel14" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel14 into :d->FILIALNR,
                     :d->NAME,
                     :d->BGANR,
                     :d->SUPPORT_FROM,
                     :d->SUPPORT_UNTIL,
                     :d->RECHNER_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel14" )) == IS_ERROR )
        return rc;
    return rc;
}

/* filialpartner::SelSupportTime **********************************************/

retClient filialpartner_SelSupportTime(filialpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "filialpartner_SelSupportTime";
    exec sql begin declare section;
    filialpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select filialpartner.filialnr,
                     filialpartner.name,
                     filialpartner.bganr,
                     filialpartner.support_from,
                     filialpartner.support_until,
                     filialpartner.rechner_name
                into :d->FILIALNR,
                     :d->NAME,
                     :d->BGANR,
                     :d->SUPPORT_FROM,
                     :d->SUPPORT_UNTIL,
                     :d->RECHNER_NAME
                from FILIALPARTNER
              where FilialPartner.filialnr	 =	:d->FILIALNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* filialpartner: Insert ******************************************************/

/* filialpartner::Insert ******************************************************/

retClient filialpartner_Insert(filialpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "filialpartner_Insert";
    exec sql begin declare section;
    filialpartnerS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into filialpartner (filialnr,
                     name,
                     bganr,
                     support_from,
                     support_until,
                     rechner_name)
        values (:d->FILIALNR,
                     :d->NAME,
                     :d->BGANR,
                     :d->SUPPORT_FROM,
                     :d->SUPPORT_UNTIL,
                     :d->RECHNER_NAME);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert filialpartner" ) ) != IS_OK )
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



/* filialpartner: Update ******************************************************/

/* filialpartner::Update ******************************************************/

retClient filialpartner_Update(filialpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "filialpartner_Update";
    exec sql begin declare section;
    filialpartnerS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate16 cursor with hold for
              select filialnr,
                     name,
                     bganr,
                     support_from,
                     support_until,
                     rechner_name
               from FILIALPARTNER
              where FilialPartner.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CUpdate16;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate16" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate16;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate16" ) ) != IS_OK )
            break;
        exec sql update filialpartner set filialnr = :d->FILIALNR,
                     name = :d->NAME,
                     bganr = :d->BGANR,
                     support_from = :d->SUPPORT_FROM,
                     support_until = :d->SUPPORT_UNTIL,
                     rechner_name = :d->RECHNER_NAME where current of CUpdate16;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate16" ) ) != IS_OK )
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



/* filialpartner: Select ******************************************************/

/* filialpartner::Delete ******************************************************/

retClient filialpartner_Delete(filialpartnerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "filialpartner_Delete";
    exec sql begin declare section;
    filialpartnerS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete17 cursor with hold for
              select filialnr,
                     name,
                     bganr,
                     support_from,
                     support_until,
                     rechner_name
               from FILIALPARTNER
              where FilialPartner.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CDelete17;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete17" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete17" ) ) != IS_OK )
            break;
        exec sql delete from filialpartner where current of CDelete17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete17" ) ) != IS_OK )
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



/* filialpartner: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : filialzeiten.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:50 2022                                         */
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
#include "filialpartner.h"

/* filialzeiten: Select *******************************************************/

/* filialzeiten::SelZeiten ****************************************************/

retClient filialzeiten_SelZeiten(filialzeitenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "filialzeiten_SelZeiten";
    exec sql begin declare section;
    filialzeitenS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelZeiten18 cursor with hold for
                  select filiale.filialnr,
                     filiale.closed_from,
                     filiale.closed_until
                from FILIALE
                  where filiale.filialnr	 =	:d->FILIALNR;
        exec sql open CSelZeiten18;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelZeiten18" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelZeiten18;
        return CheckSql( fun, stError, "%s", "close CSelZeiten18" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelZeiten18 into :d->FILIALNR,
                     :d->CLOSED_FROM,
                     :d->CLOSED_UNTIL;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelZeiten18" )) == IS_ERROR )
        return rc;
    return rc;
}



/* filialzeiten: Insert *******************************************************/



/* filialzeiten: Update *******************************************************/

/* filialzeiten::UpdateZeiten *************************************************/

retClient filialzeiten_UpdateZeiten(filialzeitenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "filialzeiten_UpdateZeiten";
    exec sql begin declare section;
    filialzeitenS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdateZeiten19 cursor with hold for
              select filialnr,
                     closed_from,
                     closed_until
               from FILIALE
              where filiale.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CUpdateZeiten19;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdateZeiten19" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdateZeiten19;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdateZeiten19" ) ) != IS_OK )
            break;
        exec sql update filiale set filialnr = :d->FILIALNR,
                     closed_from = :d->CLOSED_FROM,
                     closed_until = :d->CLOSED_UNTIL where current of CUpdateZeiten19;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdateZeiten19" ) ) != IS_OK )
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



/* filialzeiten: Select *******************************************************/



/* filialzeiten: Other ********************************************************/



