/******************************************************************************/
/*                                                                            */
/* header  : CheckPromoScale.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:07 2022                                         */
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
#include "promoinfo.h"

/* CheckPromoScale: Select ****************************************************/

/* CheckPromoScale::PromoScaleExist *******************************************/

retClient Checkpromoscale_PromoScaleExist(checkpromoscaleS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkpromoscale_PromoScaleExist";
    exec sql begin declare section;
    checkpromoscaleS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select promotionscale.BasePromotion,
                     promotionscale.promotion_no
                into :d->BASEPROMOTION,
                     :d->PROMOTION_NO
                from PROMOTIONSCALE
              where PromotionScale.promotion_no	 =	:d->PROMOTION_NO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckPromoScale: Insert ****************************************************/



/* CheckPromoScale: Update ****************************************************/



/* CheckPromoScale: Select ****************************************************/



/* CheckPromoScale: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoQuotaAnz.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:10 2022                                         */
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
#include "promoinfo.h"

/* PromoQuotaAnz: Select ******************************************************/

/* PromoQuotaAnz::SelList *****************************************************/

retClient Promoquotaanz_SelList(promoquotaanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotaanz_SelList";
    exec sql begin declare section;
    promoquotaanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select promotionquota.BranchNo,
                     promotionquota.promotion_no,
                     promotions.name,
                     promotionquota.branchquotaqty,
                     promotionquota.customerquotaqty,
                     promotionquota.SoldQtyBranch,
                     promotionquota.ArticleNo,
                     promotionquota.customerminqty
                from PROMOTIONQUOTA, PROMOTIONS
                  where PromotionQuota.BranchNo	 =	:d->BRANCHNO	 and
                        PromotionQuota.promotion_no	 =	Promotions.promotion_no
                        order by Promotions.name,PromotionQuota.ArticleNo;
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
    exec sql fetch CSelList1 into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->BRANCHQUOTAQTY,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYBRANCH,
                     :d->ARTICLENO,
                     :d->CUSTOMERMINQTY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}

/* PromoQuotaAnz::SelQuota ****************************************************/

retClient Promoquotaanz_SelQuota(promoquotaanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotaanz_SelQuota";
    exec sql begin declare section;
    promoquotaanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelQuota2 cursor with hold for
                  select promotionquota.BranchNo,
                     promotionquota.promotion_no,
                     promotions.name,
                     promotionquota.branchquotaqty,
                     promotionquota.customerquotaqty,
                     promotionquota.SoldQtyBranch,
                     promotionquota.ArticleNo,
                     promotionquota.customerminqty
                from PROMOTIONQUOTA, PROMOTIONS
                  where PromotionQuota.BranchNo	 =	:d->BRANCHNO	 and
                        PromotionQuota.promotion_no	 =	:d->PROMOTION_NO	 and
                        PromotionQuota.promotion_no	 =	Promotions.promotion_no;
        exec sql open CSelQuota2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelQuota2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelQuota2;
        return CheckSql( fun, stError, "%s", "close CSelQuota2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelQuota2 into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->BRANCHQUOTAQTY,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYBRANCH,
                     :d->ARTICLENO,
                     :d->CUSTOMERMINQTY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelQuota2" )) == IS_ERROR )
        return rc;
    return rc;
}

/* PromoQuotaAnz::SelQuotaPzn *************************************************/

retClient Promoquotaanz_SelQuotaPzn(promoquotaanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotaanz_SelQuotaPzn";
    exec sql begin declare section;
    promoquotaanzS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select promotionquota.BranchNo,
                     promotionquota.promotion_no,
                     promotions.name,
                     promotionquota.branchquotaqty,
                     promotionquota.customerquotaqty,
                     promotionquota.SoldQtyBranch,
                     promotionquota.ArticleNo,
                     promotionquota.customerminqty
                into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->BRANCHQUOTAQTY,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYBRANCH,
                     :d->ARTICLENO,
                     :d->CUSTOMERMINQTY
                from PROMOTIONQUOTA, PROMOTIONS
              where PromotionQuota.BranchNo	 =	:d->BRANCHNO	 and
                    PromotionQuota.promotion_no	 =	:d->PROMOTION_NO	 and
                    PromotionQuota.promotion_no	 =	Promotions.promotion_no and
                    PromotionQuota.ArticleNo	 =	:d->ARTICLENO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoQuotaAnz: Insert ******************************************************/



/* PromoQuotaAnz: Update ******************************************************/



/* PromoQuotaAnz: Select ******************************************************/



/* PromoQuotaAnz: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoQuotaCheck.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:13 2022                                         */
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
#include "promoinfo.h"

/* PromoQuotaCheck: Select ****************************************************/

/* PromoQuotaCheck::SelQuota **************************************************/

retClient Promoquotacheck_SelQuota(promoquotacheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotacheck_SelQuota";
    exec sql begin declare section;
    promoquotacheckS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select promotionquota.BranchNo,
                     promotionquota.promotion_no,
                     promotionquota.branchquotaqty,
                     promotionquota.customerquotaqty,
                     promotionquotacst.SoldQtyCst,
                     promotionquota.SoldQtyBranch,
                     promotionquotacst.CustomerNo,
                     promotionquota.ArticleNo,
                     promotionquota.customerminqty
                into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->BRANCHQUOTAQTY,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYCST,
                     :d->SOLDQTYBRANCH,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->CUSTOMERMINQTY
                from promotionquota, outer promotionquotacst
              where PromotionQuota.BranchNo	 =	:d->BRANCHNO	 and
                    PromotionQuota.promotion_no	 =	:d->PROMOTION_NO	 and
                    PromotionQuotaCst.CustomerNo	 =	:d->CUSTOMERNO	 and
                    PromotionQuota.BranchNo	 =	PromotionQuotaCst.BranchNo and
                    PromotionQuota.promotion_no	 =	PromotionQuotaCst.promotion_no and
                    (PromotionQuota.ArticleNo	 =	0 or
                    PromotionQuota.ArticleNo	 =	:d->ARTICLENO)	 and
                    PromotionQuota.ArticleNo	 =	PromotionQuotaCst.ArticleNo;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoQuotaCheck: Insert ****************************************************/



/* PromoQuotaCheck: Update ****************************************************/



/* PromoQuotaCheck: Select ****************************************************/



/* PromoQuotaCheck: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoQuotaCstAnz.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:17 2022                                         */
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
#include "promoinfo.h"

/* PromoQuotaCstAnz: Select ***************************************************/

/* PromoQuotaCstAnz::SelList **************************************************/

retClient Promoquotacstanz_SelList(promoquotacstanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotacstanz_SelList";
    exec sql begin declare section;
    promoquotacstanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList5 cursor with hold for
                  select promotionquotacst.BranchNo,
                     promotionquotacst.promotion_no,
                     promotions.name,
                     promotionquotacst.customerquotaqty,
                     promotionquotacst.SoldQtyCst,
                     promotionquotacst.CustomerNo,
                     promotionquotacst.ArticleNo,
                     kunde.nameapo,
                     kunde.ort
                from PROMOTIONQUOTACST, KUNDE, PROMOTIONS
                  where PromotionQuotaCst.BranchNo	 =	:d->BRANCHNO	 and
                        PromotionQuotaCst.BranchNo	 =	kunde.VertriebszentrumNr and
                        PromotionQuotaCst.CustomerNo	 =	kunde.KundenNr and
                        PromotionQuotaCst.promotion_no	 =	Promotions.promotion_no
                        order by Promotions.name, kunde.nameapo, kunde.ort;
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
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYCST,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->NAMEAPO,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList5" )) == IS_ERROR )
        return rc;
    return rc;
}

/* PromoQuotaCstAnz::SelListCst ***********************************************/

retClient Promoquotacstanz_SelListCst(promoquotacstanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotacstanz_SelListCst";
    exec sql begin declare section;
    promoquotacstanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListCst6 cursor with hold for
                  select promotionquotacst.BranchNo,
                     promotionquotacst.promotion_no,
                     promotions.name,
                     promotionquotacst.customerquotaqty,
                     promotionquotacst.SoldQtyCst,
                     promotionquotacst.CustomerNo,
                     promotionquotacst.ArticleNo,
                     kunde.nameapo,
                     kunde.ort
                from PROMOTIONQUOTACST, KUNDE, PROMOTIONS
                  where PromotionQuotaCst.BranchNo	 =	:d->BRANCHNO	 and
                        PromotionQuotaCst.CustomerNo	 =	:d->CUSTOMERNO	 and
                        PromotionQuotaCst.BranchNo	 =	kunde.VertriebszentrumNr and
                        PromotionQuotaCst.CustomerNo	 =	kunde.KundenNr and
                        PromotionQuotaCst.promotion_no	 =	Promotions.promotion_no
                        order by Promotions.name,PromotionQuotaCst.ArticleNo;
        exec sql open CSelListCst6;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListCst6" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListCst6;
        return CheckSql( fun, stError, "%s", "close CSelListCst6" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListCst6 into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYCST,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->NAMEAPO,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListCst6" )) == IS_ERROR )
        return rc;
    return rc;
}

/* PromoQuotaCstAnz::SelListPromo *********************************************/

retClient Promoquotacstanz_SelListPromo(promoquotacstanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotacstanz_SelListPromo";
    exec sql begin declare section;
    promoquotacstanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListPromo7 cursor with hold for
                  select promotionquotacst.BranchNo,
                     promotionquotacst.promotion_no,
                     promotions.name,
                     promotionquotacst.customerquotaqty,
                     promotionquotacst.SoldQtyCst,
                     promotionquotacst.CustomerNo,
                     promotionquotacst.ArticleNo,
                     kunde.nameapo,
                     kunde.ort
                from PROMOTIONQUOTACST, PROMOTIONS, KUNDE
                  where PromotionQuotaCst.BranchNo	 =	:d->BRANCHNO	 and
                        PromotionQuotaCst.promotion_no	 =	:d->PROMOTION_NO	 and
                        PromotionQuotaCst.BranchNo	 =	kunde.VertriebszentrumNr and
                        PromotionQuotaCst.CustomerNo	 =	kunde.KundenNr and
                        PromotionQuotaCst.promotion_no	 =	Promotions.promotion_no and
                        PromotionQuotaCst.ArticleNo	 =	:d->ARTICLENO
                        order by kunde.nameapo, kunde.ort;
        exec sql open CSelListPromo7;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListPromo7" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListPromo7;
        return CheckSql( fun, stError, "%s", "close CSelListPromo7" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListPromo7 into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYCST,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->NAMEAPO,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListPromo7" )) == IS_ERROR )
        return rc;
    return rc;
}

/* PromoQuotaCstAnz::SelQuota *************************************************/

retClient Promoquotacstanz_SelQuota(promoquotacstanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoquotacstanz_SelQuota";
    exec sql begin declare section;
    promoquotacstanzS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select promotionquotacst.BranchNo,
                     promotionquotacst.promotion_no,
                     promotions.name,
                     promotionquotacst.customerquotaqty,
                     promotionquotacst.SoldQtyCst,
                     promotionquotacst.CustomerNo,
                     promotionquotacst.ArticleNo,
                     kunde.nameapo,
                     kunde.ort
                into :d->BRANCHNO,
                     :d->PROMOTION_NO,
                     :d->NAME,
                     :d->CUSTOMERQUOTAQTY,
                     :d->SOLDQTYCST,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->NAMEAPO,
                     :d->ORT
                from PROMOTIONQUOTACST, PROMOTIONS, KUNDE
              where PromotionQuotaCst.BranchNo	 =	:d->BRANCHNO	 and
                    PromotionQuotaCst.promotion_no	 =	:d->PROMOTION_NO	 and
                    PromotionQuotaCst.CustomerNo	 =	:d->CUSTOMERNO	 and
                    PromotionQuotaCst.promotion_no	 =	Promotions.promotion_no and
                    PromotionQuotaCst.BranchNo	 =	kunde.VertriebszentrumNr and
                    PromotionQuotaCst.CustomerNo	 =	kunde.KundenNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoQuotaCstAnz: Insert ***************************************************/



/* PromoQuotaCstAnz: Update ***************************************************/



/* PromoQuotaCstAnz: Select ***************************************************/



/* PromoQuotaCstAnz: Other ****************************************************/



