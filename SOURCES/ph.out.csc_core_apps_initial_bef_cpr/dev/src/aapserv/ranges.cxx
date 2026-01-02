/******************************************************************************/
/*                                                                            */
/* header  : DiscountGroup.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:26 2022                                         */
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
#include "ranges.h"

/* DiscountGroup: Select ******************************************************/

/* DiscountGroup::Selgroup ****************************************************/

retClient Discountgroup_Selgroup(discountgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Discountgroup_Selgroup";
    exec sql begin declare section;
    discountgroupS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select discountgrp.BranchNo,
                     discountgrp.DiscountGrpNo,
                     discountgrp.description
                into :d->BRANCHNO,
                     :d->DISCOUNTGRPNO,
                     :d->DESCRIPTION
                from DISCOUNTGRP
              where DiscountGrp.BranchNo	 =	:d->BRANCHNO	 and
                    DiscountGrp.DiscountGrpNo	 =	:d->DISCOUNTGRPNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* DiscountGroup: Insert ******************************************************/



/* DiscountGroup: Update ******************************************************/



/* DiscountGroup: Select ******************************************************/



/* DiscountGroup: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : RangeMembers.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:29 2022                                         */
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
#include "ranges.h"

/* RangeMembers: Select *******************************************************/

/* RangeMembers::SelArticle ***************************************************/

retClient Rangemembers_SelArticle(rangemembersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Rangemembers_SelArticle";
    exec sql begin declare section;
    rangemembersS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelArticle1 cursor with hold for
                  select discountgrpmem.BranchNo,
                     discountgrpmem.DiscountGrpNo,
                     artikelpreis.preisekapo,
                     discountgrpmem.manufacturerno,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from DISCOUNTGRPMEM, ARTIKELZENTRAL, ARTIKELPREIS, ARTIKELLOKAL
                  where DiscountGrpMem.BranchNo	 =	:d->BRANCHNO	 and
                        DiscountGrpMem.DiscountGrpNo	 =	:d->DISCOUNTGRPNO	 and
                        DiscountGrpMem.ArticleNo	 =	artikelzentral.artikel_nr and
                        DiscountGrpMem.BranchNo	 =	artikellokal.filialnr and
                        DiscountGrpMem.ArticleNo	 =	artikellokal.artikel_nr and
                        DiscountGrpMem.ArticleNo	 =	artikelpreis.artikel_nr and
                        artikelpreis.preis_typ	 =	0;
        exec sql open CSelArticle1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelArticle1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelArticle1;
        return CheckSql( fun, stError, "%s", "close CSelArticle1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelArticle1 into :d->BRANCHNO,
                     :d->DISCOUNTGRPNO,
                     :d->PREISEKAPO,
                     :d->MANUFACTURERNO,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelArticle1" )) == IS_ERROR )
        return rc;
    return rc;
}

/* RangeMembers::SelManu ******************************************************/

retClient Rangemembers_SelManu(rangemembersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Rangemembers_SelManu";
    exec sql begin declare section;
    rangemembersS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelManu2 cursor with hold for
                  select discountgrpmem.BranchNo,
                     discountgrpmem.DiscountGrpNo,
                     artikelpreis.preisekapo,
                     discountgrpmem.manufacturerno,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from DISCOUNTGRPMEM, ARTIKELZENTRAL, ARTIKELPREIS, ARTIKELLOKAL
                  where DiscountGrpMem.BranchNo	 =	:d->BRANCHNO	 and
                        DiscountGrpMem.DiscountGrpNo	 =	:d->DISCOUNTGRPNO	 and
                        DiscountGrpMem.manufacturerno	 =	artikelzentral.hersteller_nr and
                        DiscountGrpMem.manufacturerno	 >	0 and
                        DiscountGrpMem.BranchNo	 =	artikellokal.filialnr and
                        artikelzentral.artikel_nr	 =	artikellokal.artikel_nr and
                        artikelzentral.artikel_nr	 =	artikelpreis.artikel_nr and
                        artikelpreis.preis_typ	 =	0;
        exec sql open CSelManu2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelManu2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelManu2;
        return CheckSql( fun, stError, "%s", "close CSelManu2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelManu2 into :d->BRANCHNO,
                     :d->DISCOUNTGRPNO,
                     :d->PREISEKAPO,
                     :d->MANUFACTURERNO,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelManu2" )) == IS_ERROR )
        return rc;
    return rc;
}



/* RangeMembers: Insert *******************************************************/



/* RangeMembers: Update *******************************************************/



/* RangeMembers: Select *******************************************************/



/* RangeMembers: Other ********************************************************/



