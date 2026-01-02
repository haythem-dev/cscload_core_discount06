/******************************************************************************/
/*                                                                            */
/* header  : CollOrderGrp.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:00 2022                                         */
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
#include "collectivorders.h"

/* CollOrderGrp: Select *******************************************************/

/* CollOrderGrp::SelList ******************************************************/

retClient Collordergrp_SelList(collordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Collordergrp_SelList";
    exec sql begin declare section;
    collordergrpS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select collordergrp.CollOrderGrpID,
                     collordergrp.CollOrderGrpName,
                     collordergrp.BranchNo
                from COLLORDERGRP
                  where CollOrderGrp.BranchNo	 =	:d->BRANCHNO
                        order by 	CollOrderGrp.CollOrderGrpName;
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
    exec sql fetch CSelList0 into :d->COLLORDERGRPID,
                     :d->COLLORDERGRPNAME,
                     :d->BRANCHNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CollOrderGrp: Insert *******************************************************/

/* CollOrderGrp::Insert *******************************************************/

retClient Collordergrp_Insert(collordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Collordergrp_Insert";
    exec sql begin declare section;
    collordergrpS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select MAX(collordergrpid)+1 into :d->COLLORDERGRPID from collordergrp;
    exec sql insert into collordergrp (CollOrderGrpID,
                     CollOrderGrpName,
                     BranchNo)
        values (:d->COLLORDERGRPID,
                     :d->COLLORDERGRPNAME,
                     :d->BRANCHNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert collordergrp" ) ) != IS_OK )
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



/* CollOrderGrp: Update *******************************************************/

/* CollOrderGrp::Update *******************************************************/

retClient Collordergrp_Update(collordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Collordergrp_Update";
    exec sql begin declare section;
    collordergrpS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate1 cursor with hold for
              select CollOrderGrpID,
                     CollOrderGrpName,
                     BranchNo
               from COLLORDERGRP
              where CollOrderGrp.BranchNo	 =	:d->BRANCHNO	 and
                    CollOrderGrp.CollOrderGrpID	 =	:d->COLLORDERGRPID
              for update;
    exec sql open CUpdate1;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate1;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate1" ) ) != IS_OK )
            break;
        exec sql update collordergrp set CollOrderGrpID = :d->COLLORDERGRPID,
                     CollOrderGrpName = :d->COLLORDERGRPNAME,
                     BranchNo = :d->BRANCHNO where current of CUpdate1;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate1" ) ) != IS_OK )
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



/* CollOrderGrp: Select *******************************************************/

/* CollOrderGrp::Delete *******************************************************/

retClient Collordergrp_Delete(collordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Collordergrp_Delete";
    exec sql begin declare section;
    collordergrpS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete2 cursor with hold for
              select CollOrderGrpID,
                     CollOrderGrpName,
                     BranchNo
               from COLLORDERGRP
              where CollOrderGrp.BranchNo	 =	:d->BRANCHNO	 and
                    CollOrderGrp.CollOrderGrpID	 =	:d->COLLORDERGRPID
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
        exec sql delete from collordergrp where current of CDelete2;
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



/* CollOrderGrp: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CollOrderGrpMem.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:04 2022                                         */
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
#include "collectivorders.h"

/* CollOrderGrpMem: Select ****************************************************/

/* CollOrderGrpMem::SelList ***************************************************/

retClient Collordergrpmem_SelList(collordergrpmemS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Collordergrpmem_SelList";
    exec sql begin declare section;
    collordergrpmemS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList3 cursor with hold for
                  select collordergrpmem.BranchNo,
                     kunde.idfnr,
                     kunde.matchcode,
                     collordergrpmem.CustomerNo,
                     collordergrpmem.CollOrderGrpID,
                     kunde.nameapo,
                     kunde.nameinhaber,
                     kunde.strasse,
                     kunde.ort,
                     kunde.kzkdklasse,
                     kundeschalter.skdkundeaegesperrt
                from COLLORDERGRPMEM, KUNDE, KUNDESCHALTER
                  where CollOrderGrpMem.BranchNo	 =	:d->BRANCHNO	 and
                        CollOrderGrpMem.CollOrderGrpID	 =	:d->COLLORDERGRPID and
                        CollOrderGrpMem.BranchNo	 =	kunde.VertriebszentrumNr and
                        CollOrderGrpMem.CustomerNo	 =	kundeschalter.KundenNr and
                        kundeschalter.KundenNr	 =	kunde.KundenNr and
                        kundeschalter.VertriebszentrumNr = kunde.VertriebszentrumNr
                        order by kunde.idfnr;
        exec sql open CSelList3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList3;
        return CheckSql( fun, stError, "%s", "close CSelList3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList3 into :d->BRANCHNO,
                     :d->IDFNR,
                     :d->MATCHCODE,
                     :d->CUSTOMERNO,
                     :d->COLLORDERGRPID,
                     :d->NAMEAPO,
                     :d->NAMEINHABER,
                     :d->STRASSE,
                     :d->ORT,
                     :d->KZKDKLASSE,
                     :d->SKDKUNDEAEGESPERRT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CollOrderGrpMem: Insert ****************************************************/

/* CollOrderGrpMem::Insert ****************************************************/

retClient Collordergrpmem_Insert(collordergrpmemS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Collordergrpmem_Insert";
    exec sql begin declare section;
    collordergrpmemS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into collordergrpmem (BranchNo,
                     CustomerNo,
                     CollOrderGrpID)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->COLLORDERGRPID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert collordergrpmem" ) ) != IS_OK )
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



/* CollOrderGrpMem: Update ****************************************************/



/* CollOrderGrpMem: Select ****************************************************/

/* CollOrderGrpMem::Delete ****************************************************/

retClient Collordergrpmem_Delete(collordergrpmemS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Collordergrpmem_Delete";
    exec sql begin declare section;
    collordergrpmemS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete4 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     CollOrderGrpID
               from COLLORDERGRPMEM
              where :d->BRANCHNO		 =	CollOrderGrpMem.BranchNo and
                    :d->CUSTOMERNO		 =	CollOrderGrpMem.CustomerNo and
                    CollOrderGrpMem.CollOrderGrpID	 =	:d->COLLORDERGRPID
              for update;
    exec sql open CDelete4;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete4" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete4;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete4" ) ) != IS_OK )
            break;
        exec sql delete from collordergrpmem where current of CDelete4;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete4" ) ) != IS_OK )
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



/* CollOrderGrpMem: Other *****************************************************/



