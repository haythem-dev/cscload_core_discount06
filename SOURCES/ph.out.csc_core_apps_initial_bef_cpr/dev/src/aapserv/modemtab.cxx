/******************************************************************************/
/*                                                                            */
/* header  : ModemTab.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Aug 16 16:38:41 2019                                         */
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
#include "modemtab.h"

/* ModemTab: Select ***********************************************************/

/* ModemTab::SelAll ***********************************************************/

retClient Modemtab_SelAll(modemtabS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Modemtab_SelAll";
    exec sql begin declare section;
    modemtabS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAll0 cursor with hold for
                  select modemtab.filialnr,
                     modemtab.geraeteid
                from MODEMTAB
                  where modemtab.filialnr	>=	0
                        order by modemtab.filialnr, modemtab.geraeteid;
        exec sql open CSelAll0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAll0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAll0;
        return CheckSql( fun, stError, "%s", "close CSelAll0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAll0 into :d->FILIALNR,
                     :d->GERAETEID;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAll0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ModemTab: Insert ***********************************************************/

/* ModemTab::Insert ***********************************************************/

retClient Modemtab_Insert(modemtabS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Modemtab_Insert";
    exec sql begin declare section;
    modemtabS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into modemtab (filialnr,
                     geraeteid)
        values (:d->FILIALNR,
                     :d->GERAETEID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert modemtab" ) ) != IS_OK )
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



/* ModemTab: Update ***********************************************************/



/* ModemTab: Select ***********************************************************/

/* ModemTab::DeleteModem ******************************************************/

retClient Modemtab_DeleteModem(modemtabS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Modemtab_DeleteModem";
    exec sql begin declare section;
    modemtabS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteModem1 cursor with hold for
              select filialnr,
                     geraeteid
               from MODEMTAB
              where modemtab.geraeteid	 =	:d->GERAETEID
              for update;
    exec sql open CDeleteModem1;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteModem1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteModem1;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteModem1" ) ) != IS_OK )
            break;
        exec sql delete from modemtab where current of CDeleteModem1;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteModem1" ) ) != IS_OK )
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



/* ModemTab: Other ************************************************************/



