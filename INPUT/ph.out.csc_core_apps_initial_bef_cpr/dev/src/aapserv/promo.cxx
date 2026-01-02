/******************************************************************************/
/*                                                                            */
/* header  : ProductPromo.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:17 2022                                         */
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
#include "promo.h"

/* ProductPromo: Select *******************************************************/

/* ProductPromo::SelList ******************************************************/

retClient Productpromo_SelList(productpromoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Productpromo_SelList";
    exec sql begin declare section;
    productpromoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select discount.BranchNo,
                     promotions.promotion_no,
                     discount.ArticleNo,
                     promotions.name,
                     artikelpreis.preisekapo,
                     discount.CustomerNo,
                     promotions.addonstddiscok,
                     discount.DiscountValuePct,
                     discount.MaxQty,
                     artikellokal.bestand,
                     artikellokal.artikelaktiv,
                     artikelzentral.TaxLevel,
                     artikelzentral.artikel_langname
                from DISCOUNT, ARTIKELZENTRAL, ARTIKELLOKAL, ARTIKELPREIS,PROMOTIONS
                  where Promotions.promotion_type	 =	1 and
                        Promotions.promotion_no	 =	Discount.promotion_no and( ( Discount.CustomerNo	 =	:d->CUSTOMERNO	 )  or
                         (DISCOUNT.PHARMACYGROUPID  = '000'	and
                         DISCOUNT.CUSTOMERNO       =  0) or
                         DISCOUNT.PHARMACYGROUPID in
                         (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
                         from  CUSTOMERPHARMACYGR
                         where DISCOUNT.BRANCHNO         = :d->BRANCHNO
                         and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :d->CUSTOMERNO) ) and
                        ( Discount.PharmGrpExcluded = '000' or
                         Discount.PharmGrpExcluded	not in 
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                         Discount.PharmGrpExcl_2	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                         Discount.PharmGrpExcl_3	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        Discount.ArticleNo	 =	artikelzentral.artikel_nr and
                        Discount.BranchNo	 =	:d->BRANCHNO and
                        Discount.BranchNo	 =	artikellokal.filialnr and
                        Discount.ArticleNo	 =	artikellokal.artikel_nr and
                        Discount.ArticleNo	 =	artikelpreis.artikel_nr and
                        artikelpreis.preis_typ	 =	0
                        order by artikelzentral.artikel_langname;
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
                     :d->PROMOTION_NO,
                     :d->ARTICLENO,
                     :d->NAME,
                     :d->PREISEKAPO,
                     :d->CUSTOMERNO,
                     :d->ADDONSTDDISCOK,
                     :d->DISCOUNTVALUEPCT,
                     :d->MAXQTY,
                     :d->BESTAND,
                     :d->ARTIKELAKTIV,
                     :d->TAXLEVEL,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ProductPromo: Insert *******************************************************/



/* ProductPromo: Update *******************************************************/



/* ProductPromo: Select *******************************************************/



/* ProductPromo: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoHerst.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:29 2022                                         */
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
#include "promo.h"

/* PromoHerst: Select *********************************************************/

/* PromoHerst::SelList ********************************************************/

retClient Promoherst_SelList(promoherstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoherst_SelList";
    exec sql begin declare section;
    promoherstS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
{
d->DATEFROM = ppGGetDate();
EXEC SQL drop table t_herst;
EXEC SQL select discount.manufacturerno
from DISCOUNT
where Discount.BranchNo = :d->FILIALNR and
Discount.promotion_no = :d->PROMOTION_NO and
Discount.DateFrom <= :d->DATEFROM and
Discount.DateTo >= :d->DATEFROM and
Discount.ArticleNo = 0 and
Discount.manufacturerno > 0
into temp t_herst;
}
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select artikelpreis.preisekapo,
                     artikellagerort.datumverfall,
                     artikelpreis.preis_typ,
                     artikellokal.filialnr,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikellokal.artikelaktiv,
                     artikelzentral.hersteller_nr,
                     artikelzentral.TaxLevel,
                     artikelzentral.HealthFundCode,
                     artikelzentral.artikel_langname
                from ARTIKELZENTRAL, ARTIKELLOKAL, ARTIKELPREIS,t_herst, ARTIKELLAGERORT
                  where artikelzentral.hersteller_nr	 =	t_herst.MANUFACTURERNO	and
                        artikellokal.filialnr	 =	:d->FILIALNR	 and
                        artikellagerort.filialnr	 =	:d->FILIALNR	 and
                        artikelzentral.artikel_nr	 =	artikellokal.artikel_nr and
                        artikellagerort.artikel_nr	 =	artikellokal.artikel_nr and
                        artikellokal.artikelaktiv	 =	'1' and
                        artikelpreis.preis_typ	 =	:d->PREIS_TYP	 and
                        artikelpreis.artikel_nr	 =	artikelzentral.artikel_nr
                        order by artikelzentral.artikel_langname;
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
    exec sql fetch CSelList1 into :d->PREISEKAPO,
                     :d->DATUMVERFALL,
                     :d->PREIS_TYP,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->ARTIKELAKTIV,
                     :d->HERSTELLER_NR,
                     :d->TAXLEVEL,
                     :d->HEALTHFUNDCODE,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoHerst: Insert *********************************************************/



/* PromoHerst: Update *********************************************************/



/* PromoHerst: Select *********************************************************/



/* PromoHerst: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoManufact.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:39 2022                                         */
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
#include "promo.h"

/* PromoManufact: Select ******************************************************/

/* PromoManufact::SelManuNo ***************************************************/

retClient Promomanufact_SelManuNo(promomanufactS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promomanufact_SelManuNo";
    exec sql begin declare section;
    promomanufactS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelManuNo2 cursor with hold for
                  select discount.BranchNo,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.manufacturerno,
                     discount.promotion_no
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.promotion_no	 =	:d->PROMOTION_NO	 and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate and
                        Discount.ArticleNo	 =	0 and
                        Discount.manufacturerno	 >	0;
        exec sql open CSelManuNo2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelManuNo2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelManuNo2;
        return CheckSql( fun, stError, "%s", "close CSelManuNo2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelManuNo2 into :d->BRANCHNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->MANUFACTURERNO,
                     :d->PROMOTION_NO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelManuNo2" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoManufact: Insert ******************************************************/



/* PromoManufact: Update ******************************************************/



/* PromoManufact: Select ******************************************************/



/* PromoManufact: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoMembers.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:42 2022                                         */
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
#include "promo.h"

/* PromoMembers: Select *******************************************************/

/* PromoMembers::SelList ******************************************************/

retClient Promomembers_SelList(promomembersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promomembers_SelList";
    exec sql begin declare section;
    promomembersS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList3 cursor with hold for
                  select DiscountGrpMem.BranchNo,
DiscountGrpMem.DiscountGrpNo,
nvl(Discount.BaseQty,0),
nvl(Discount.DiscountQty,0),
nvl(Discount.DiscountValuePct,0),
nvl(Discount.no_multiple_qty,0),
nvl(Discount.MaxQty,0),
artikelzentral.artikel_nr,
artikelzentral.artikel_langname,
artikellagerort.datumverfall
                         into :d->BRANCHNO,
:d->DISCOUNTGRPNO,
:d->BASEQTY,
:d->DISCOUNTQTY,
:d->DISCOUNTVALUEPCT,
:d->NO_MULTIPLE_QTY,
:d->MAXQTY,
:d->ARTIKEL_NR,
:d->ARTIKEL_LANGNAME,
:d->DATUMVERFALL
                   from DISCOUNTGRPMEM, ARTIKELZENTRAL, ARTIKELLAGERORT, outer DISCOUNT
                  where DiscountGrpMem.BranchNo	 =	:d->BRANCHNO	 and
                        DiscountGrpMem.DiscountGrpNo	 =	:d->DISCOUNTGRPNO	 and
                        DiscountGrpMem.ArticleNo	 =	artikelzentral.artikel_nr and
                        DiscountGrpMem.ArticleNo	 =	Discount.ArticleNo and
                        DiscountGrpMem.DiscountGrpNo	 =	Discount.DiscountGrpNo and
                        DiscountGrpMem.BranchNo	 =	Discount.BranchNo and
                        DiscountGrpMem.BranchNo	 =	artikellagerort.filialnr and
                        DiscountGrpMem.ArticleNo	 =	artikellagerort.artikel_nr
                        order by artikelzentral.artikel_langname;
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
    exec sql fetch CSelList3;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoMembers: Insert *******************************************************/



/* PromoMembers: Update *******************************************************/



/* PromoMembers: Select *******************************************************/



/* PromoMembers: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Promotionen.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:52 2022                                         */
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
#include "promo.h"

/* Promotionen: Select ********************************************************/

/* Promotionen::SelList *******************************************************/

retClient Promotionen_SelList(promotionenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promotionen_SelList";
    exec sql begin declare section;
    promotionenS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList4 cursor with hold for
                  select discount.BranchNo,
                     promotions.name,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     promotions.addonstddiscok,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountArticle,
                     discount.base_value,
                     discount.manufacturerno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.promotion_no
                from DISCOUNT, PROMOTIONS
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.articleno = 0 and
                        Discount.manufacturerno = 0 and
                        Discount.promotion_no	 >	0 and
                        Discount.DiscountGrpNo	!=	0 and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        Discount.promotion_no = Promotions.promotion_no and
                        ( ( Discount.CustomerNo	 =	:d->CUSTOMERNO	 )  or
                         (DISCOUNT.PHARMACYGROUPID  = '000'	and
                         DISCOUNT.CUSTOMERNO       =  0) or
                         DISCOUNT.PHARMACYGROUPID in
                         (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
                         from  CUSTOMERPHARMACYGR
                         where DISCOUNT.BRANCHNO         = :d->BRANCHNO
                         and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :d->CUSTOMERNO) ) and
                        ( Discount.PharmGrpExcluded = '000' or
                         Discount.PharmGrpExcluded	not in 
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                         Discount.PharmGrpExcl_2	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                         Discount.PharmGrpExcl_3	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) )
                        order by Discount.promotion_no;
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
    exec sql fetch CSelList4 into :d->BRANCHNO,
                     :d->NAME,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->ADDONSTDDISCOK,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTARTICLE,
                     :d->BASE_VALUE,
                     :d->MANUFACTURERNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PROMOTION_NO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList4" )) == IS_ERROR )
        return rc;
    return rc;
}

/* Promotionen::SelListManu ***************************************************/

retClient Promotionen_SelListManu(promotionenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promotionen_SelListManu";
    exec sql begin declare section;
    promotionenS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListManu5 cursor with hold for
                  select discount.BranchNo,
                     promotions.name,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     promotions.addonstddiscok,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountArticle,
                     discount.base_value,
                     discount.manufacturerno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.promotion_no
                from DISCOUNT, PROMOTIONS
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.articleno = 0 and
                        Discount.promotion_no	 >	0 and
                        Discount.manufacturerno	!=	0 and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        Discount.promotion_no = Promotions.promotion_no and
                        ( ( Discount.CustomerNo	 =	:d->CUSTOMERNO	 )  or
                         (DISCOUNT.PHARMACYGROUPID  = '000'	and
                         DISCOUNT.CUSTOMERNO       =  0) or
                         DISCOUNT.PHARMACYGROUPID in
                         (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
                         from  CUSTOMERPHARMACYGR
                         where DISCOUNT.BRANCHNO         = :d->BRANCHNO
                         and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :d->CUSTOMERNO) ) and
                        ( Discount.PharmGrpExcluded = '000' or
                         Discount.PharmGrpExcluded	not in 
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                         Discount.PharmGrpExcl_2	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                         Discount.PharmGrpExcl_3	not in
                         (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                          where
                          customerpharmacygr.BranchNo = :d->BRANCHNO and
                          customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) )
                        order by Discount.promotion_no;
        exec sql open CSelListManu5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListManu5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListManu5;
        return CheckSql( fun, stError, "%s", "close CSelListManu5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListManu5 into :d->BRANCHNO,
                     :d->NAME,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->ADDONSTDDISCOK,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTARTICLE,
                     :d->BASE_VALUE,
                     :d->MANUFACTURERNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PROMOTION_NO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListManu5" )) == IS_ERROR )
        return rc;
    return rc;
}

/* Promotionen::SelPromoNo ****************************************************/

retClient Promotionen_SelPromoNo(promotionenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promotionen_SelPromoNo";
    exec sql begin declare section;
    promotionenS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select discount.BranchNo,
                     promotions.name,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     promotions.addonstddiscok,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountArticle,
                     discount.base_value,
                     discount.manufacturerno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.promotion_no
                into :d->BRANCHNO,
                     :d->NAME,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->ADDONSTDDISCOK,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTARTICLE,
                     :d->BASE_VALUE,
                     :d->MANUFACTURERNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PROMOTION_NO
                from DISCOUNT, PROMOTIONS
              where Discount.BranchNo	 =	:d->BRANCHNO	 and
                    Discount.articleno = 0 and
                    Discount.manufacturerno = 0 and
                    Discount.promotion_no	 =	:d->PROMOTION_NO and
                    Discount.DiscountGrpNo	=	:d->DISCOUNTGRPNO and
                    Discount.PharmacyGroupId	=	:d->PHARMACYGROUPID and
                    Discount.BaseQty	=	:d->BASEQTY and
                    Discount.base_value	=	:d->BASE_VALUE and
                    Discount.DateFrom	<=	:lDate  and
                    Discount.DateTo	>=	:lDate  and
                    Discount.promotion_no = Promotions.promotion_no and
                    Discount.CustomerNo	 =	:d->CUSTOMERNO
                    order by Discount.promotion_no;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* Promotionen::SelPromoNoManu ************************************************/

retClient Promotionen_SelPromoNoManu(promotionenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promotionen_SelPromoNoManu";
    exec sql begin declare section;
    promotionenS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select discount.BranchNo,
                     promotions.name,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     promotions.addonstddiscok,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountArticle,
                     discount.base_value,
                     discount.manufacturerno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.promotion_no
                into :d->BRANCHNO,
                     :d->NAME,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->ADDONSTDDISCOK,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTARTICLE,
                     :d->BASE_VALUE,
                     :d->MANUFACTURERNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PROMOTION_NO
                from DISCOUNT, PROMOTIONS
              where Discount.BranchNo	 =	:d->BRANCHNO	 and
                    Discount.articleno = 0 and
                    Discount.promotion_no	 =	:d->PROMOTION_NO and
                    Discount.manufacturerno	!=	0 and
                    Discount.DateFrom	<=	:lDate  and
                    Discount.DateTo	>=	:lDate  and
                    Discount.DiscountGrpNo	=	:d->DISCOUNTGRPNO and
                    Discount.PharmacyGroupId	=	:d->PHARMACYGROUPID and
                    Discount.BaseQty	=	:d->BASEQTY and
                    Discount.base_value	=	:d->BASE_VALUE and
                    Discount.DateFrom	<=	:lDate  and
                    Discount.DateTo	>=	:lDate  and
                    Discount.promotion_no = Promotions.promotion_no and
                    Discount.CustomerNo	 =	:d->CUSTOMERNO
                    order by Discount.promotion_no;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Promotionen: Insert ********************************************************/



/* Promotionen: Update ********************************************************/



/* Promotionen: Select ********************************************************/



/* Promotionen: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Stotinken.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:54 2022                                         */
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
#include "promo.h"

/* Stotinken: Select **********************************************************/

/* Stotinken::SelList *********************************************************/

retClient Stotinken_SelList(stotinkenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Stotinken_SelList";
    exec sql begin declare section;
    stotinkenS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList8 cursor with hold for
                  select artikelpreis.preisekapo,
                     artikellokal.filialnr,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.TaxLevel,
                     artikelzentral.artikel_langname
                from ARTIKELZENTRAL, ARTIKELLOKAL, ARTIKELPREIS
                  where artikellokal.filialnr	 =	:d->FILIALNR	 and
                        artikellokal.artikel_nr	 =	artikelzentral.artikel_nr and
                        artikelpreis.artikel_nr	 =	artikelzentral.artikel_nr and
                        artikelzentral.sortiment_3	 =	'1'
                        order by artikelzentral.artikel_langname;
        exec sql open CSelList8;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList8" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList8;
        return CheckSql( fun, stError, "%s", "close CSelList8" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList8 into :d->PREISEKAPO,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->TAXLEVEL,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList8" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Stotinken: Insert **********************************************************/



/* Stotinken: Update **********************************************************/



/* Stotinken: Select **********************************************************/



/* Stotinken: Other ***********************************************************/



