/******************************************************************************/
/*                                                                            */
/* header  : HerstellerListe.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:58:39 2022                                         */
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
#include "hersteller.h"

/* HerstellerListe: Select ****************************************************/

/* HerstellerListe::SelList ***************************************************/

retClient Herstellerliste_SelList(herstellerlisteS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Herstellerliste_SelList";
    exec sql begin declare section;
    herstellerlisteS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        ppGMakeToLike( d->NAME, L_HERSTELLERLISTE_NAME );
        exec sql declare CSelList0 cursor with hold for
                  select herstel.hersteller_nr,
                     herstel.name
                from HERSTEL
                  where upper(herstel.name)	like	:d->NAME;
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
    exec sql fetch CSelList0 into :d->HERSTELLER_NR,
                     :d->NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* HerstellerListe: Insert ****************************************************/



/* HerstellerListe: Update ****************************************************/



/* HerstellerListe: Select ****************************************************/



/* HerstellerListe: Other *****************************************************/



