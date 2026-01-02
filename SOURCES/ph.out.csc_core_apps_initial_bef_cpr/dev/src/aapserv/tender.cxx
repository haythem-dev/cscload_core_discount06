/******************************************************************************/
/*                                                                            */
/* header  : TenderArticle.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:34 2022                                         */
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
#include "tender.h"

/* TenderArticle: Select ******************************************************/

/* TenderArticle::SelArt ******************************************************/

retClient Tenderarticle_SelArt(tenderarticleS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderarticle_SelArt";
    exec sql begin declare section;
    tenderarticleS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select tenderpos.TenderNo,
                     tenderpos.ArticleNo,
                     tenderpos.ContractQty,
                     artikelpreis.preisekapo,
                     artikelpreis.preisekgrosso,
                     tenderpos.ContractPrice,
                     tenderpos.RemainingLife,
                     artikelpreis.preisekgrossona,
                     tenderpos.AddDiscountPct,
                     tenderpos.Aep,
                     tenderpos.TenderState,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.TaxLevel,
                     artikelzentral.artikel_langname
                into :d->TENDERNO,
                     :d->ARTICLENO,
                     :d->CONTRACTQTY,
                     :d->PREISEKAPO,
                     :d->PREISEKGROSSO,
                     :d->CONTRACTPRICE,
                     :d->REMAININGLIFE,
                     :d->PREISEKGROSSONA,
                     :d->ADDDISCOUNTPCT,
                     :d->AEP,
                     :d->TENDERSTATE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->TAXLEVEL,
                     :d->ARTIKEL_LANGNAME
                from ARTIKELZENTRAL, TENDERPOS, ARTIKELPREIS
              where TenderPos.TenderNo	 =	:d->TENDERNO	 and
                    TenderPos.ArticleNo	 =	:d->ARTICLENO	 and
                    TenderPos.TenderState	 =	'1' and
                    artikelzentral.artikel_nr	 =	TenderPos.ArticleNo and
                    artikelpreis.artikel_nr	 =	TenderPos.ArticleNo and
                    artikelpreis.preis_typ	 =	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TenderArticle::SelList *****************************************************/

retClient Tenderarticle_SelList(tenderarticleS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderarticle_SelList";
    exec sql begin declare section;
    tenderarticleS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select tenderpos.TenderNo,
                     tenderpos.ArticleNo,
                     tenderpos.ContractQty,
                     artikelpreis.preisekapo,
                     artikelpreis.preisekgrosso,
                     tenderpos.ContractPrice,
                     tenderpos.RemainingLife,
                     artikelpreis.preisekgrossona,
                     tenderpos.AddDiscountPct,
                     tenderpos.Aep,
                     tenderpos.TenderState,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.TaxLevel,
                     artikelzentral.artikel_langname
                from ARTIKELZENTRAL, TENDERPOS, ARTIKELPREIS
                  where TenderPos.TenderNo	 =	:d->TENDERNO	 and
                        artikelzentral.artikel_nr	 =	TenderPos.ArticleNo and
                        TenderPos.TenderState	 =	'1' and
                        artikelpreis.artikel_nr	 =	TenderPos.ArticleNo and
                        artikelpreis.preis_typ	 =	0
                        order by artikelzentral.artikel_name;
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
    exec sql fetch CSelList1 into :d->TENDERNO,
                     :d->ARTICLENO,
                     :d->CONTRACTQTY,
                     :d->PREISEKAPO,
                     :d->PREISEKGROSSO,
                     :d->CONTRACTPRICE,
                     :d->REMAININGLIFE,
                     :d->PREISEKGROSSONA,
                     :d->ADDDISCOUNTPCT,
                     :d->AEP,
                     :d->TENDERSTATE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->TAXLEVEL,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TenderArticle: Insert ******************************************************/



/* TenderArticle: Update ******************************************************/



/* TenderArticle: Select ******************************************************/



/* TenderArticle: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TenderInfo.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:39 2022                                         */
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
#include "tender.h"

/* TenderInfo: Select *********************************************************/

/* TenderInfo::SelList ********************************************************/

retClient Tenderinfo_SelList(tenderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderinfo_SelList";
    exec sql begin declare section;
    tenderinfoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList2 cursor with hold for
                  select tenderhead.TenderNo,
                     tenderhead.TenderType,
                     tenderhead.ContractNo,
                     tenderhead.BranchNo,
                     tenderhead.CustomerNo,
                     tenderhead.DateFrom,
                     tenderhead.DateTo,
                     tenderhead.exceedancepct,
                     tenderhead.PharmacyChainNo
                from TENDERHEAD
                  where TenderHead.BranchNo	 =	:d->BRANCHNO	 and
                        TenderHead.CustomerNo	 =	:d->CUSTOMERNO	 and
                        TenderHead.TenderState	 =	'1' and
                        TenderHead.DateFrom	<=	:lDate  and
                        TenderHead.DateTo	>=	:lDate;
        exec sql open CSelList2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList2;
        return CheckSql( fun, stError, "%s", "close CSelList2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList2 into :d->TENDERNO,
                     :d->TENDERTYPE,
                     :d->CONTRACTNO,
                     :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->EXCEEDANCEPCT,
                     :d->PHARMACYCHAINNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList2" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TenderInfo::SelListChain ***************************************************/

retClient Tenderinfo_SelListChain(tenderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderinfo_SelListChain";
    exec sql begin declare section;
    tenderinfoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListChain3 cursor with hold for
                  select tenderhead.TenderNo,
                     tenderhead.TenderType,
                     tenderhead.ContractNo,
                     tenderhead.BranchNo,
                     tenderhead.CustomerNo,
                     tenderhead.DateFrom,
                     tenderhead.DateTo,
                     tenderhead.exceedancepct,
                     tenderhead.PharmacyChainNo
                from TENDERHEAD,KUNDE
                  where ((TenderHead.BranchNo	 =	:d->BRANCHNO	 and
                        TenderHead.CustomerNo	 =	:d->CUSTOMERNO	and
                        TenderHead.BranchNo	 =	Kunde.Vertriebszentrumnr	 and
                        TenderHead.CustomerNo	 =	Kunde.Kundennr	)
                        or
                        (TenderHead.CustomerNo	 =	0	 and
                        Kunde.Kundennr		=	:d->CUSTOMERNO	 and
                        Kunde.Vertriebszentrumnr	=	:d->BRANCHNO	and
                        TenderHead.PharmacyChainNo	=	Kunde.MasterCstNo	and
                        (Kunde.kdgruppe	=	TenderHead.CustomerGroupID  or
                        TenderHead.CustomerGroupID = '  ')
                        ))	and
                        TenderHead.TenderState	 =	'1' and
                        TenderHead.DateFrom	<=	:lDate  and
                        TenderHead.DateTo	>=	:lDate;
        exec sql open CSelListChain3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListChain3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListChain3;
        return CheckSql( fun, stError, "%s", "close CSelListChain3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListChain3 into :d->TENDERNO,
                     :d->TENDERTYPE,
                     :d->CONTRACTNO,
                     :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->EXCEEDANCEPCT,
                     :d->PHARMACYCHAINNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListChain3" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TenderInfo::SelListPos *****************************************************/

retClient Tenderinfo_SelListPos(tenderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderinfo_SelListPos";
    exec sql begin declare section;
    tenderinfoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListPos4 cursor with hold for
                  select tenderhead.TenderNo,
                     tenderhead.TenderType,
                     tenderhead.ContractNo,
                     tenderhead.BranchNo,
                     tenderhead.CustomerNo,
                     tenderhead.DateFrom,
                     tenderhead.DateTo,
                     tenderhead.exceedancepct,
                     tenderhead.PharmacyChainNo
                from TENDERHEAD, KUNDE,TENDERPOS
                  where ((TenderHead.BranchNo	 =	:d->BRANCHNO	 and
                        TenderHead.CustomerNo	 =	:d->CUSTOMERNO	and
                        TenderHead.BranchNo	 =	Kunde.Vertriebszentrumnr	 and
                        TenderHead.CustomerNo	 =	Kunde.Kundennr	)
                         or
                        (TenderHead.CustomerNo	 =	0	 and
                        Kunde.Kundennr		=	:d->CUSTOMERNO	 and
                        Kunde.Vertriebszentrumnr	=	:d->BRANCHNO	and
                        TenderHead.PharmacyChainNo	=	Kunde.MasterCstNo	and
                        (Kunde.kdgruppe	=	TenderHead.CustomerGroupID  or
                        TenderHead.CustomerGroupID = '  ')
                        ))	and
                        TenderHead.TenderState	 =	'1' and
                        TenderHead.DateFrom	<=	:lDate  and
                        TenderHead.DateTo	>=	:lDate and
                        TenderHead.TenderNo	 =	TenderPos.TenderNo and
                        TenderPos.ArticleNo	 =	:d->ARTICLENO and
                        TenderPos.TenderState	 =	'1';
        exec sql open CSelListPos4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListPos4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListPos4;
        return CheckSql( fun, stError, "%s", "close CSelListPos4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListPos4 into :d->TENDERNO,
                     :d->TENDERTYPE,
                     :d->CONTRACTNO,
                     :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->EXCEEDANCEPCT,
                     :d->PHARMACYCHAINNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListPos4" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TenderInfo::SelListStaat ***************************************************/

retClient Tenderinfo_SelListStaat(tenderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderinfo_SelListStaat";
    exec sql begin declare section;
    tenderinfoS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListStaat5 cursor with hold for
                  select tenderhead.TenderNo,
                     tenderhead.TenderType,
                     tenderhead.ContractNo,
                     tenderhead.BranchNo,
                     tenderhead.CustomerNo,
                     tenderhead.DateFrom,
                     tenderhead.DateTo,
                     tenderhead.exceedancepct,
                     tenderhead.PharmacyChainNo
                from TENDERHEAD, TENDERCUSTOMER
                  where TenderCustomer.BranchNo	 =	:d->BRANCHNO	 and
                        TenderCustomer.CustomerNo	 =	:d->CUSTOMERNO	 and
                        TenderCustomer.TenderNo	 =	TenderHead.TenderNo	 and
                        TenderHead.TenderState	 =	'1' and
                        TenderHead.DateFrom	<=	:lDate  and
                        TenderHead.DateTo	>=	:lDate;
        exec sql open CSelListStaat5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListStaat5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListStaat5;
        return CheckSql( fun, stError, "%s", "close CSelListStaat5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListStaat5 into :d->TENDERNO,
                     :d->TENDERTYPE,
                     :d->CONTRACTNO,
                     :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->EXCEEDANCEPCT,
                     :d->PHARMACYCHAINNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListStaat5" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TenderInfo::SelTender ******************************************************/

retClient Tenderinfo_SelTender(tenderinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderinfo_SelTender";
    exec sql begin declare section;
    tenderinfoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select tenderhead.TenderNo,
                     tenderhead.TenderType,
                     tenderhead.ContractNo,
                     tenderhead.BranchNo,
                     tenderhead.CustomerNo,
                     tenderhead.DateFrom,
                     tenderhead.DateTo,
                     tenderhead.exceedancepct,
                     tenderhead.PharmacyChainNo
                into :d->TENDERNO,
                     :d->TENDERTYPE,
                     :d->CONTRACTNO,
                     :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->EXCEEDANCEPCT,
                     :d->PHARMACYCHAINNO
                from TENDERHEAD
              where TenderHead.TenderNo	 =	:d->TENDERNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TenderInfo: Insert *********************************************************/



/* TenderInfo: Update *********************************************************/



/* TenderInfo: Select *********************************************************/



/* TenderInfo: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TenderStock.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:42 2022                                         */
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
#include "tender.h"

/* TenderStock: Select ********************************************************/

/* TenderStock::SelQty ********************************************************/

retClient Tenderstock_SelQty(tenderstockS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tenderstock_SelQty";
    exec sql begin declare section;
    tenderstockS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select nvl (sum( TenderProgress.DeliveryQty) ,0) , nvl (sum( TenderProgress.ReturnQty) ,0) ,artikellokal.bestand,artikellagerort.datumverfall
                into :d->DELIVERYQTY	,:d->RETURNQTY	,:d->BESTAND    ,:d->DATUMVERFALL
                from ARTIKELLOKAL, ARTIKELLAGERORT, outer TENDERPROGRESS
              where artikellokal.filialnr	 =	:d->FILIALNR	 and
                    artikellokal.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikellokal.filialnr = artikellagerort.filialnr and
                    artikellokal.artikel_nr = artikellagerort.artikel_nr and
                    TenderProgress.TenderNo	 =	:d->TENDERNO	 and
                    TenderProgress.ArticleNo	 =	artikellokal.artikel_nr
                    group by artikellokal.bestand,artikellagerort.datumverfall;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TenderStock: Insert ********************************************************/



/* TenderStock: Update ********************************************************/



/* TenderStock: Select ********************************************************/



/* TenderStock: Other *********************************************************/



