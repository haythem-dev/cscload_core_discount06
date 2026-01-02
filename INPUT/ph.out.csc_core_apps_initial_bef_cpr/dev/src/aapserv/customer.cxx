/******************************************************************************/
/*                                                                            */
/* header  : ChainCustomers.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:26 2022                                         */
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
#include "customer.h"

/* ChainCustomers: Select *****************************************************/

/* ChainCustomers::SelList ****************************************************/

retClient Chaincustomers_SelList(chaincustomersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Chaincustomers_SelList";
    exec sql begin declare section;
    chaincustomersS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select kunde.nameapo,
                     kunde.strasse,
                     kunde.ort,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.MainCstNo
                from KUNDE, kundeschalter
                  where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kunde.MainCstNo	 =	:d->MAINCSTNO	 and
                        kunde.VertriebszentrumNr	 =	kundeschalter.VertriebszentrumNr and
                        kunde.KundenNr	 =	kundeschalter.KundenNr and
                        kundeschalter.skdkundeaegesperrt = '0';
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
    exec sql fetch CSelList0 into :d->NAMEAPO,
                     :d->STRASSE,
                     :d->ORT,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->MAINCSTNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ChainCustomers: Insert *****************************************************/



/* ChainCustomers: Update *****************************************************/



/* ChainCustomers: Select *****************************************************/



/* ChainCustomers: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckCustomerExist.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:28 2022                                         */
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
#include "customer.h"

/* CheckCustomerExist: Select *************************************************/



/* CheckCustomerExist: Insert *************************************************/



/* CheckCustomerExist: Update *************************************************/



/* CheckCustomerExist: Select *************************************************/



/* CheckCustomerExist: Other **************************************************/

/* CheckCustomerExist::SelExist ***********************************************/

retClient Checkcustomerexist_SelExist(checkcustomerexistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "CheckCustomerExist_SelExist";
    exec sql begin declare section;
    checkcustomerexistS *d;
    char cRechner[81];
    char cDatenbank[141];
    char buffer[2048];
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select rechner.datenbank_name
         into :cRechner
         from rechner
         where filialnr = :d->VERTRIEBSZENTRUMNR;

    sprintf(cDatenbank,"%s:kundeschalter",cRechner);
    strcpy( buffer, "select  VertriebszentrumNr, " );
    strcat( buffer, "kundennr " );
    strcat( buffer, "from ");
    strcat( buffer, cDatenbank );
    strcat( buffer, " where VertriebszentrumNr = ? ");
    strcat( buffer, "and Kundennr = ? ");
    strcat( buffer, "and skdkundeaegesperrt != '1' ");
    exec sql prepare Sel_kundeexist from :buffer;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;

    exec sql execute Sel_kundeexist 
             using   :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : CheckListe5.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:29 2022                                         */
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
#include "customer.h"

/* CheckListe5: Select ********************************************************/

/* CheckListe5::IsListe5 ******************************************************/

retClient Checkliste5_IsListe5(checkliste5S *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkliste5_IsListe5";
    exec sql begin declare section;
    checkliste5S *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select discountgrp.BranchNo,
                     discountgrpmem.ArticleNo,
                     discountgrp.CustomerNo
                into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->CUSTOMERNO
                from DISCOUNTGRP, DISCOUNTGRPMEM
              where DiscountGrp.BranchNo	 =	:d->BRANCHNO	 and
                    DiscountGrp.CustomerNo	 =	:d->CUSTOMERNO	 and
                    DiscountGrpMem.ArticleNo	 =	:d->ARTICLENO	 and
                    DiscountGrp.discountgrptype	 =	3 and
                    DiscountGrp.BranchNo	 =	DiscountGrpMem.BranchNo and
                    DiscountGrp.DiscountGrpNo	 =	DiscountGrpMem.DiscountGrpNo;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckListe5: Insert ********************************************************/



/* CheckListe5: Update ********************************************************/



/* CheckListe5: Select ********************************************************/



/* CheckListe5: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstBranchInfo.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:37 2022                                         */
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
#include "customer.h"

/* CstBranchInfo: Select ******************************************************/

/* CstBranchInfo::SelList *****************************************************/

retClient Cstbranchinfo_SelList(cstbranchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstbranchinfo_SelList";
    exec sql begin declare section;
    cstbranchinfoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList2 cursor with hold for
                  select cstbranchinfo.BranchNo,
                     cstbranchinfo.lfdnr,
                     cstbranchinfo.InfoText,
                     cstbranchinfo.DateTo,
                     cstbranchinfo.TimeTo
                from CstBranchInfo
                  where CstBranchInfo.BranchNo	 =	:d->BRANCHNO;
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
    exec sql fetch CSelList2 into :d->BRANCHNO,
                     :d->LFDNR,
                     :d->INFOTEXT,
                     :d->DATETO,
                     :d->TIMETO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList2" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstBranchInfo::SelListValid ************************************************/

retClient Cstbranchinfo_SelListValid(cstbranchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstbranchinfo_SelListValid";
    exec sql begin declare section;
    cstbranchinfoS *d;
    long lDate;
    long lTime;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    lTime = ppGGetTime();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListValid3 cursor with hold for
                  select cstbranchinfo.BranchNo,
                     cstbranchinfo.lfdnr,
                     cstbranchinfo.InfoText,
                     cstbranchinfo.DateTo,
                     cstbranchinfo.TimeTo
                from CstBranchInfo
                  where CstBranchInfo.BranchNo	 =	:d->BRANCHNO	 and
                        (CstBranchInfo.DateTo	 >	:lDate  or
                        ( CstBranchInfo.DateTo	 =	:lDate  and
                        CstBranchInfo.TimeTo	>=	:lTime ))
                        order by CstBranchInfo.lfdnr desc;
        exec sql open CSelListValid3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListValid3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListValid3;
        return CheckSql( fun, stError, "%s", "close CSelListValid3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListValid3 into :d->BRANCHNO,
                     :d->LFDNR,
                     :d->INFOTEXT,
                     :d->DATETO,
                     :d->TIMETO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListValid3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstBranchInfo: Insert ******************************************************/

/* CstBranchInfo::Insert ******************************************************/

retClient Cstbranchinfo_Insert(cstbranchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstbranchinfo_Insert";
    exec sql begin declare section;
    cstbranchinfoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into cstbranchinfo (BranchNo,
                     InfoText,
                     DateTo,
                     TimeTo)
        values (:d->BRANCHNO,
                     :d->INFOTEXT,
                     :d->DATETO,
                     :d->TIMETO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert cstbranchinfo" ) ) != IS_OK )
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



/* CstBranchInfo: Update ******************************************************/

/* CstBranchInfo::Update ******************************************************/

retClient Cstbranchinfo_Update(cstbranchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Cstbranchinfo_Update";
    exec sql begin declare section;
    cstbranchinfoS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate4 cursor with hold for
              select BranchNo,
                     InfoText,
                     DateTo,
                     TimeTo
               from CstBranchInfo
              where CstBranchInfo.lfdnr	 =	:d->LFDNR
              for update;
    exec sql open CUpdate4;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate4" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate4" ) ) != IS_OK )
            break;
        exec sql update cstbranchinfo set BranchNo = :d->BRANCHNO,
                     InfoText = :d->INFOTEXT,
                     DateTo = :d->DATETO,
                     TimeTo = :d->TIMETO where current of CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate4" ) ) != IS_OK )
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



/* CstBranchInfo: Select ******************************************************/

/* CstBranchInfo::Delete ******************************************************/

retClient Cstbranchinfo_Delete(cstbranchinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Cstbranchinfo_Delete";
    exec sql begin declare section;
    cstbranchinfoS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete5 cursor with hold for
              select BranchNo,
                     InfoText,
                     DateTo,
                     TimeTo
               from CstBranchInfo
              where CstBranchInfo.lfdnr	 =	:d->LFDNR
              for update;
    exec sql open CDelete5;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete5" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete5" ) ) != IS_OK )
            break;
        exec sql delete from cstbranchinfo where current of CDelete5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete5" ) ) != IS_OK )
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



/* CstBranchInfo: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstBulgaria.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:42 2022                                         */
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
#include "customer.h"

/* CstBulgaria: Select ********************************************************/

/* CstBulgaria::SelCst ********************************************************/

retClient Cstbulgaria_SelCst(cstbulgariaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstbulgaria_SelCst";
    exec sql begin declare section;
    cstbulgariaS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.RebateMethFreeSale,
                     kunde.RebateMethHealthF,
                     kunde.MainCstNo
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->REBATEMETHFREESALE,
                     :d->REBATEMETHHEALTHF,
                     :d->MAINCSTNO
                from KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstBulgaria: Insert ********************************************************/



/* CstBulgaria: Update ********************************************************/



/* CstBulgaria: Select ********************************************************/



/* CstBulgaria: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstBuyingOptions.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:46 2022                                         */
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
#include "customer.h"

/* CstBuyingOptions: Select ***************************************************/

/* CstBuyingOptions::SelBuyingOptions *****************************************/

retClient Cstbuyingoptions_SelBuyingOptions(cstbuyingoptionsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstbuyingoptions_SelBuyingOptions";
    exec sql begin declare section;
    cstbuyingoptionsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.etartklasse1,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.kzPsychoStoffe
                into :d->ETARTKLASSE1,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->KZPSYCHOSTOFFE
                from kunde
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstBuyingOptions: Insert ***************************************************/



/* CstBuyingOptions: Update ***************************************************/



/* CstBuyingOptions: Select ***************************************************/



/* CstBuyingOptions: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstDiscAcc.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:53 2022                                         */
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
#include "customer.h"

/* CstDiscAcc: Select *********************************************************/

/* CstDiscAcc::CheckExist *****************************************************/

retClient Cstdiscacc_CheckExist(cstdiscaccS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscacc_CheckExist";
    exec sql begin declare section;
    cstdiscaccS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CCheckExist8 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     cstdiscacc.Balance,
                     cstdiscacc.upd_flag,
                     cstdiscacc.kdauftragnr,
                     cstdiscacc.date,
                     cstdiscacc.InvoiceNumber,
                     cstdiscacc.InvoiceAmount,
                     cstdiscacc.VoucherTyp,
                     cstdiscacc.preis_typ,
                     cstdiscacc.priority,
                     cstdiscacc.kdauftragnrsplit,
                     cstdiscacc.InvoicePaid,
                     cstdiscacc.paymentarget,
                     cstdiscacc.lfdnr
                from CSTDISCACC
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.CustomerNo	 =	:d->CUSTOMERNO and
                        CstDiscAcc.kdauftragnr	 =	0;
        exec sql open CCheckExist8;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CCheckExist8" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CCheckExist8;
        return CheckSql( fun, stError, "%s", "close CCheckExist8" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CCheckExist8 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->BALANCE,
                     :d->UPD_FLAG,
                     :d->KDAUFTRAGNR,
                     :d->DATE,
                     :d->INVOICENUMBER,
                     :d->INVOICEAMOUNT,
                     :d->VOUCHERTYP,
                     :d->PREIS_TYP,
                     :d->PRIORITY,
                     :d->KDAUFTRAGNRSPLIT,
                     :d->INVOICEPAID,
                     :d->PAYMENTARGET,
                     :d->LFDNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckExist8" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstDiscAcc::SelListCst *****************************************************/

retClient Cstdiscacc_SelListCst(cstdiscaccS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscacc_SelListCst";
    exec sql begin declare section;
    cstdiscaccS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListCst9 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     cstdiscacc.Balance,
                     cstdiscacc.upd_flag,
                     cstdiscacc.kdauftragnr,
                     cstdiscacc.date,
                     cstdiscacc.InvoiceNumber,
                     cstdiscacc.InvoiceAmount,
                     cstdiscacc.VoucherTyp,
                     cstdiscacc.preis_typ,
                     cstdiscacc.priority,
                     cstdiscacc.kdauftragnrsplit,
                     cstdiscacc.InvoicePaid,
                     cstdiscacc.paymentarget,
                     cstdiscacc.lfdnr
                from CSTDISCACC
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.CustomerNo	 =	:d->CUSTOMERNO	and
                        CstDiscAcc.kdauftragnr	 =	0 and
                        CstDiscAcc.date	>=	:d->DATUM	 and
                        CstDiscAcc.date	<=	:d->DATE	
                        order by CstDiscAcc.date;
        exec sql open CSelListCst9;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListCst9" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListCst9;
        return CheckSql( fun, stError, "%s", "close CSelListCst9" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListCst9 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->BALANCE,
                     :d->UPD_FLAG,
                     :d->KDAUFTRAGNR,
                     :d->DATE,
                     :d->INVOICENUMBER,
                     :d->INVOICEAMOUNT,
                     :d->VOUCHERTYP,
                     :d->PREIS_TYP,
                     :d->PRIORITY,
                     :d->KDAUFTRAGNRSPLIT,
                     :d->INVOICEPAID,
                     :d->PAYMENTARGET,
                     :d->LFDNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListCst9" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstDiscAcc::SelListGrp *****************************************************/

retClient Cstdiscacc_SelListGrp(cstdiscaccS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscacc_SelListGrp";
    exec sql begin declare section;
    cstdiscaccS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListGrp10 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     cstdiscacc.Balance,
                     cstdiscacc.upd_flag,
                     cstdiscacc.kdauftragnr,
                     cstdiscacc.date,
                     cstdiscacc.InvoiceNumber,
                     cstdiscacc.InvoiceAmount,
                     cstdiscacc.VoucherTyp,
                     cstdiscacc.preis_typ,
                     cstdiscacc.priority,
                     cstdiscacc.kdauftragnrsplit,
                     cstdiscacc.InvoicePaid,
                     cstdiscacc.paymentarget,
                     cstdiscacc.lfdnr
                from CSTDISCACC
                  where CstDiscAcc.MainCstNo	 =	:d->MAINCSTNO	and not
                        (CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.CustomerNo	 =	:d->CUSTOMERNO	) and
                        CstDiscAcc.kdauftragnr	 =	0	and
                        CstDiscAcc.date	>=	:d->DATUM	 and
                        CstDiscAcc.date	<=	:d->DATE	
                        order by CstDiscAcc.date;
        exec sql open CSelListGrp10;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListGrp10" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListGrp10;
        return CheckSql( fun, stError, "%s", "close CSelListGrp10" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListGrp10 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->BALANCE,
                     :d->UPD_FLAG,
                     :d->KDAUFTRAGNR,
                     :d->DATE,
                     :d->INVOICENUMBER,
                     :d->INVOICEAMOUNT,
                     :d->VOUCHERTYP,
                     :d->PREIS_TYP,
                     :d->PRIORITY,
                     :d->KDAUFTRAGNRSPLIT,
                     :d->INVOICEPAID,
                     :d->PAYMENTARGET,
                     :d->LFDNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListGrp10" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstDiscAcc: Insert *********************************************************/



/* CstDiscAcc: Update *********************************************************/



/* CstDiscAcc: Select *********************************************************/



/* CstDiscAcc: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstDiscAccAnz.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:56 2022                                         */
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
#include "customer.h"

/* CstDiscAccAnz: Select ******************************************************/

/* CstDiscAccAnz::CheckMain ***************************************************/

retClient Cstdiscaccanz_CheckMain(cstdiscaccanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscaccanz_CheckMain";
    exec sql begin declare section;
    cstdiscaccanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CCheckMain11 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     kunde.nameapo,
                     kunde.strasse,
                     kunde.ort
                from CSTDISCACC, KUNDE
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.MainCstNo	 =	:d->MAINCSTNO and
                        CstDiscAcc.BranchNo	 =	kunde.VertriebszentrumNr and
                        CstDiscAcc.MainCstNo	 =	kunde.KundenNr;
        exec sql open CCheckMain11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CCheckMain11" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CCheckMain11;
        return CheckSql( fun, stError, "%s", "close CCheckMain11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CCheckMain11 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->NAMEAPO,
                     :d->STRASSE,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckMain11" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstDiscAccAnz::CheckMember *************************************************/

retClient Cstdiscaccanz_CheckMember(cstdiscaccanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscaccanz_CheckMember";
    exec sql begin declare section;
    cstdiscaccanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CCheckMember12 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     kunde.nameapo,
                     kunde.strasse,
                     kunde.ort
                from CSTDISCACC, KUNDE
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.CustomerNo	 =	:d->CUSTOMERNO and
                        CstDiscAcc.BranchNo	 =	kunde.VertriebszentrumNr and
                        CstDiscAcc.CustomerNo	 =	kunde.KundenNr;
        exec sql open CCheckMember12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CCheckMember12" ) ) != IS_OK )
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
    exec sql fetch CCheckMember12 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->NAMEAPO,
                     :d->STRASSE,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckMember12" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstDiscAccAnz::SelList *****************************************************/

retClient Cstdiscaccanz_SelList(cstdiscaccanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscaccanz_SelList";
    exec sql begin declare section;
    cstdiscaccanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList13 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     kunde.nameapo,
                     kunde.strasse,
                     kunde.ort
                from CSTDISCACC, KUNDE
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.MainCstNo	 =	:d->MAINCSTNO	 and
                        CstDiscAcc.BranchNo	 =	kunde.VertriebszentrumNr and
                        CstDiscAcc.CustomerNo	 =	kunde.KundenNr
                        group by CstDiscAcc.BranchNo,
                        CstDiscAcc.CustomerNo,
                        CstDiscAcc.MainCstNo,
                        kunde.nameapo,
                        kunde.strasse,
                        kunde.ort;
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
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->NAMEAPO,
                     :d->STRASSE,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList13" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CstDiscAccAnz::SelMain *****************************************************/

retClient Cstdiscaccanz_SelMain(cstdiscaccanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdiscaccanz_SelMain";
    exec sql begin declare section;
    cstdiscaccanzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMain14 cursor with hold for
                  select cstdiscacc.BranchNo,
                     cstdiscacc.CustomerNo,
                     cstdiscacc.MainCstNo,
                     kunde.nameapo,
                     kunde.strasse,
                     kunde.ort
                from CSTDISCACC, KUNDE
                  where CstDiscAcc.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscAcc.MainCstNo	 =	:d->MAINCSTNO	 and
                        CstDiscAcc.BranchNo	 =	kunde.VertriebszentrumNr and
                        CstDiscAcc.MainCstNo	 =	kunde.KundenNr
                        group by CstDiscAcc.BranchNo,
                        CstDiscAcc.CustomerNo,
                        CstDiscAcc.MainCstNo,
                        kunde.nameapo,
                        kunde.strasse,
                        kunde.ort;
        exec sql open CSelMain14;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMain14" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMain14;
        return CheckSql( fun, stError, "%s", "close CSelMain14" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMain14 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MAINCSTNO,
                     :d->NAMEAPO,
                     :d->STRASSE,
                     :d->ORT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMain14" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstDiscAccAnz: Insert ******************************************************/



/* CstDiscAccAnz: Update ******************************************************/



/* CstDiscAccAnz: Select ******************************************************/



/* CstDiscAccAnz: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstDiscCont.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:59 2022                                         */
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
#include "customer.h"

/* CstDiscCont: Select ********************************************************/

/* CstDiscCont::SelList *******************************************************/

retClient Cstdisccont_SelList(cstdisccontS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstdisccont_SelList";
    exec sql begin declare section;
    cstdisccontS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList15 cursor with hold for
                  select cstdiscountcont.BranchNo,
                     cstdiscountcont.CustomerNo,
                     cstdiscountcont.order_type,
                     discountlist.PharmacyGroupId,
                     cstdiscountcont.sub_order_type,
                     cstdiscountcont.payment_term,
                     cstdiscountcont.valuta_days,
                     cstdiscountcont.min_order_value,
                     cstdiscountcont.min_tubes,
                     cstdiscountcont.loss_in_discount,
                     cstdiscountcont.upd_flag
                from CSTDISCOUNTCONT,DISCOUNTLIST
                  where CstDiscountCont.BranchNo	 =	:d->BRANCHNO	 and
                        CstDiscountCont.CustomerNo	 =	:d->CUSTOMERNO	 and
                        CstDiscountCont.order_type	 =	:d->ORDER_TYPE and
                        CstDiscountCont.order_type	 =	DiscountList.order_type and
                        CstDiscountCont.sub_order_type	 =	DiscountList.sub_order_type and
                        ( ( DiscountList.PharmacyGroupId	 in
                        ( select	customerpharmacygr.PharmacyGroupId  from customerpharmacygr 
                        where CstDiscountCont.BranchNo	 =	customerpharmacygr.BranchNo and
                        CstDiscountCont.CustomerNo	 =	customerpharmacygr.CustomerNo ) ) or
                        ( DiscountList.PharmacyGroupId	 =	'000' ) );
        exec sql open CSelList15;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList15" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList15;
        return CheckSql( fun, stError, "%s", "close CSelList15" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList15 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->ORDER_TYPE,
                     :d->PHARMACYGROUPID,
                     :d->SUB_ORDER_TYPE,
                     :d->PAYMENT_TERM,
                     :d->VALUTA_DAYS,
                     :d->MIN_ORDER_VALUE,
                     :d->MIN_TUBES,
                     :d->LOSS_IN_DISCOUNT,
                     :d->UPD_FLAG;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList15" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstDiscCont: Insert ********************************************************/



/* CstDiscCont: Update ********************************************************/



/* CstDiscCont: Select ********************************************************/



/* CstDiscCont: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstPayTerm.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:01 2022                                         */
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
#include "customer.h"

/* CstPayTerm: Select *********************************************************/

/* CstPayTerm::SelList ********************************************************/

retClient Cstpayterm_SelList(cstpaytermS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstpayterm_SelList";
    exec sql begin declare section;
    cstpaytermS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList16 cursor with hold for
                  select cstpaymentterms.BranchNo,
                     cstpaymentterms.CustomerNo,
                     cstpaymentterms.preis_typ,
                     cstpaymentterms.paymentarget
                from CSTPAYMENTTERMS
                  where CstPaymentTerms.BranchNo	 =	:d->BRANCHNO	 and
                        CstPaymentTerms.CustomerNo	 =	:d->CUSTOMERNO;
        exec sql open CSelList16;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList16" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList16;
        return CheckSql( fun, stError, "%s", "close CSelList16" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList16 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->PREIS_TYP,
                     :d->PAYMENTARGET;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList16" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstPayTerm: Insert *********************************************************/



/* CstPayTerm: Update *********************************************************/



/* CstPayTerm: Select *********************************************************/



/* CstPayTerm: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstRebateType.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:03 2022                                         */
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
#include "customer.h"

/* CstRebateType: Select ******************************************************/

/* CstRebateType::SelRebateType ***********************************************/

retClient Cstrebatetype_SelRebateType(cstrebatetypeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstrebatetype_SelRebateType";
    exec sql begin declare section;
    cstrebatetypeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.RebateMethFreeSale,
                     kunde.RebateMethHealthF
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->REBATEMETHFREESALE,
                     :d->REBATEMETHHEALTHF
                from KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstRebateType: Insert ******************************************************/



/* CstRebateType: Update ******************************************************/



/* CstRebateType: Select ******************************************************/



/* CstRebateType: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CustPharma.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:05 2022                                         */
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
#include "customer.h"

/* CustPharma: Select *********************************************************/

/* CustPharma::SelList ********************************************************/

retClient Custpharma_SelList(custpharmaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custpharma_SelList";
    exec sql begin declare section;
    custpharmaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList18 cursor with hold for
                  select customerpharmacygr.CustomerNo,
                     customerpharmacygr.BranchNo,
                     customerpharmacygr.PharmacyGroupId,
                     customerpharmacygr.Ranking
                from customerpharmacygr
                  where customerpharmacygr.BranchNo	 =	:d->BRANCHNO	 and
                        customerpharmacygr.CustomerNo	 =	:d->CUSTOMERNO	
                        order by customerpharmacygr.Ranking;
        exec sql open CSelList18;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList18" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList18;
        return CheckSql( fun, stError, "%s", "close CSelList18" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList18 into :d->CUSTOMERNO,
                     :d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->RANKING;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList18" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CustPharma: Insert *********************************************************/



/* CustPharma: Update *********************************************************/



/* CustPharma: Select *********************************************************/



/* CustPharma: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CustPhon.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:08 2022                                         */
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
#include "customer.h"

/* CustPhon: Select ***********************************************************/

/* CustPhon::SelList **********************************************************/

retClient Custphon_SelList(custphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custphon_SelList";
    exec sql begin declare section;
    custphonS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList19 cursor with hold for
                  select customerphoneno.VertriebszentrumNr,
                     customerphoneno.KundenNr,
                     customerphoneno.telnr,
                     customerphoneno.datum
                from CustomerPhoneNo
                  where CustomerPhoneNo.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        CustomerPhoneNo.KundenNr	 =	:d->KUNDENNR;
        exec sql open CSelList19;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList19" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList19;
        return CheckSql( fun, stError, "%s", "close CSelList19" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList19 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TELNR,
                     :d->DATUM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList19" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CustPhon::SelPhoneNo *******************************************************/

retClient Custphon_SelPhoneNo(custphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custphon_SelPhoneNo";
    exec sql begin declare section;
    custphonS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select customerphoneno.VertriebszentrumNr,
                     customerphoneno.KundenNr,
                     customerphoneno.telnr,
                     customerphoneno.datum
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TELNR,
                     :d->DATUM
                from CustomerPhoneNo
              where CustomerPhoneNo.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    CustomerPhoneNo.telnr	 =	:d->TELNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CustPhon: Insert ***********************************************************/

/* CustPhon::Insert ***********************************************************/

retClient Custphon_Insert(custphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custphon_Insert";
    exec sql begin declare section;
    custphonS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into customerphoneno (VertriebszentrumNr,
                     KundenNr,
                     telnr,
                     datum)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TELNR,
                     :d->DATUM);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert customerphoneno" ) ) != IS_OK )
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



/* CustPhon: Update ***********************************************************/



/* CustPhon: Select ***********************************************************/

/* CustPhon::Delete ***********************************************************/

retClient Custphon_Delete(custphonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Custphon_Delete";
    exec sql begin declare section;
    custphonS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete21 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     telnr,
                     datum
               from CustomerPhoneNo
              where CustomerPhoneNo.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    CustomerPhoneNo.telnr	 =	:d->TELNR
              for update;
    exec sql open CDelete21;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete21" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete21;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete21" ) ) != IS_OK )
            break;
        exec sql delete from customerphoneno where current of CDelete21;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete21" ) ) != IS_OK )
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



/* CustPhon: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CustRout.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:13 2022                                         */
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
#include "customer.h"

/* CustRout: Select ***********************************************************/

/* CustRout::SelActRouting ****************************************************/

retClient Custrout_SelActRouting(custroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custrout_SelActRouting";
    exec sql begin declare section;
    custroutS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelActRouting22 cursor with hold for
                  select customerrouting.CustomerNo,
                     customerrouting.BranchNo,
                     customerrouting.TimeFrom,
                     customerrouting.TimeTo,
                     customerrouting.DestBranchNo,
                     customerrouting.DayOfWeek,
                     customerrouting.weekday
                from CUSTOMERROUTING
                  where CustomerRouting.BranchNo	 =	:d->BRANCHNO	 and
                        CustomerRouting.CustomerNo	 =	:d->CUSTOMERNO	 and
                        CustomerRouting.weekday	 =	:d->WEEKDAY	 and
                        CustomerRouting.TimeFrom	<=	:d->TIMEFROM	 and
                        CustomerRouting.TimeTo	>=	:d->TIMETO;
        exec sql open CSelActRouting22;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelActRouting22" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelActRouting22;
        return CheckSql( fun, stError, "%s", "close CSelActRouting22" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelActRouting22 into :d->CUSTOMERNO,
                     :d->BRANCHNO,
                     :d->TIMEFROM,
                     :d->TIMETO,
                     :d->DESTBRANCHNO,
                     :d->DAYOFWEEK,
                     :d->WEEKDAY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelActRouting22" )) == IS_ERROR )
        return rc;
    return rc;
}

/* CustRout::SelList **********************************************************/

retClient Custrout_SelList(custroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custrout_SelList";
    exec sql begin declare section;
    custroutS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList23 cursor with hold for
                  select customerrouting.CustomerNo,
                     customerrouting.BranchNo,
                     customerrouting.TimeFrom,
                     customerrouting.TimeTo,
                     customerrouting.DestBranchNo,
                     customerrouting.DayOfWeek,
                     customerrouting.weekday
                from CustomerRouting
                  where CustomerRouting.BranchNo	 =	:d->BRANCHNO	 and
                        CustomerRouting.CustomerNo	 =	:d->CUSTOMERNO;
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
    exec sql fetch CSelList23 into :d->CUSTOMERNO,
                     :d->BRANCHNO,
                     :d->TIMEFROM,
                     :d->TIMETO,
                     :d->DESTBRANCHNO,
                     :d->DAYOFWEEK,
                     :d->WEEKDAY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList23" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CustRout: Insert ***********************************************************/

/* CustRout::Insert ***********************************************************/

retClient Custrout_Insert(custroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Custrout_Insert";
    exec sql begin declare section;
    custroutS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into customerrouting (CustomerNo,
                     BranchNo,
                     TimeFrom,
                     TimeTo,
                     DestBranchNo,
                     DayOfWeek,
                     weekday)
        values (:d->CUSTOMERNO,
                     :d->BRANCHNO,
                     :d->TIMEFROM,
                     :d->TIMETO,
                     :d->DESTBRANCHNO,
                     :d->DAYOFWEEK,
                     :d->WEEKDAY);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert customerrouting" ) ) != IS_OK )
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



/* CustRout: Update ***********************************************************/

/* CustRout::Update ***********************************************************/

retClient Custrout_Update(custroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Custrout_Update";
    exec sql begin declare section;
    custroutS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate24 cursor with hold for
              select CustomerNo,
                     BranchNo,
                     TimeFrom,
                     TimeTo,
                     DestBranchNo,
                     DayOfWeek,
                     weekday
               from CustomerRouting
              where CustomerRouting.BranchNo	 =	:d->BRANCHNO	 and
                    CustomerRouting.CustomerNo	 =	:d->CUSTOMERNO	 and
                    CustomerRouting.weekday	 =	:d->WEEKDAY	 and
                    CustomerRouting.TimeFrom	 =	:d->ZEIT_VON
              for update;
    exec sql open CUpdate24;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate24" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate24;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate24" ) ) != IS_OK )
            break;
        exec sql update customerrouting set CustomerNo = :d->CUSTOMERNO,
                     BranchNo = :d->BRANCHNO,
                     TimeFrom = :d->TIMEFROM,
                     TimeTo = :d->TIMETO,
                     DestBranchNo = :d->DESTBRANCHNO,
                     DayOfWeek = :d->DAYOFWEEK,
                     weekday = :d->WEEKDAY where current of CUpdate24;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate24" ) ) != IS_OK )
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



/* CustRout: Select ***********************************************************/

/* CustRout::Delete ***********************************************************/

retClient Custrout_Delete(custroutS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Custrout_Delete";
    exec sql begin declare section;
    custroutS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete25 cursor with hold for
              select CustomerNo,
                     BranchNo,
                     TimeFrom,
                     TimeTo,
                     DestBranchNo,
                     DayOfWeek,
                     weekday
               from CustomerRouting
              where CustomerRouting.BranchNo	 =	:d->BRANCHNO	 and
                    CustomerRouting.CustomerNo	 =	:d->CUSTOMERNO	 and
                    CustomerRouting.weekday	 =	:d->WEEKDAY	 and
                    CustomerRouting.TimeFrom	 =	:d->TIMEFROM
              for update;
    exec sql open CDelete25;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete25" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete25;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete25" ) ) != IS_OK )
            break;
        exec sql delete from customerrouting where current of CDelete25;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete25" ) ) != IS_OK )
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



/* CustRout: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CustomerDoubles.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:15 2022                                         */
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
#include "customer.h"

/* CustomerDoubles: Select ****************************************************/

/* CustomerDoubles::SelDouble *************************************************/

retClient Customerdoubles_SelDouble(customerdoublesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Customerdoubles_SelDouble";
    exec sql begin declare section;
    customerdoublesS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select first 1 kunde.VertriebszentrumNr, kunde.KundenNr, filiale.name
                into :d->VERTRIEBSZENTRUMNR	,:d->KUNDENNR	,:d->NAME
                from KUNDE,KUNDESCHALTER, FILIALE
              where kunde.VertriebszentrumNr	 =	kundeschalter.VertriebszentrumNr and
                    kunde.KundenNr	 =	kundeschalter.KundenNr and
                    kunde.VertriebszentrumNr	 =	filiale.filialnr and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    kunde.VertriebszentrumNr != :d->VERTRIEBSZENTRUMNR and
                    (kunde.originalfilialnr = '0' or
                    kunde.originalfilialnr = kunde.VertriebszentrumNr) and
                    kundeschalter.skdkundeaegesperrt	 =	'0';
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CustomerDoubles: Insert ****************************************************/



/* CustomerDoubles: Update ****************************************************/



/* CustomerDoubles: Select ****************************************************/



/* CustomerDoubles: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : DistressRouting.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:19 2022                                         */
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
#include "customer.h"

/* DistressRouting: Select ****************************************************/

/* DistressRouting::SelNot ****************************************************/

retClient Distressrouting_SelNot(distressroutingS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Distressrouting_SelNot";
    exec sql begin declare section;
    distressroutingS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelNot27 cursor with hold for
                  select distressrouting.BranchNo,
                     distressrouting.CustomerNo,
                     distressrouting.DestBranchNo,
                     kunde.nameapo,
                     kunde.ort,
                     kunde.postleitzahl,
                     kunde.personalnrvertr,
                     kunde.kzkdklasse
                from DISTRESSROUTING, KUNDE
                  where DistressRouting.BranchNo	 =	:d->BRANCHNO	 and
                        DistressRouting.DestBranchNo	 =	0 and
                        DistressRouting.BranchNo	 =	kunde.VertriebszentrumNr and
                        DistressRouting.CustomerNo	 =	kunde.KundenNr
                        order by kunde.nameapo;
        exec sql open CSelNot27;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelNot27" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelNot27;
        return CheckSql( fun, stError, "%s", "close CSelNot27" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelNot27 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DESTBRANCHNO,
                     :d->NAMEAPO,
                     :d->ORT,
                     :d->POSTLEITZAHL,
                     :d->PERSONALNRVERTR,
                     :d->KZKDKLASSE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelNot27" )) == IS_ERROR )
        return rc;
    return rc;
}

/* DistressRouting::SelRouted *************************************************/

retClient Distressrouting_SelRouted(distressroutingS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Distressrouting_SelRouted";
    exec sql begin declare section;
    distressroutingS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelRouted28 cursor with hold for
                  select distressrouting.BranchNo,
                     distressrouting.CustomerNo,
                     distressrouting.DestBranchNo,
                     kunde.nameapo,
                     kunde.ort,
                     kunde.postleitzahl,
                     kunde.personalnrvertr,
                     kunde.kzkdklasse
                from DISTRESSROUTING, KUNDE
                  where DistressRouting.BranchNo	 =	:d->BRANCHNO	 and
                        DistressRouting.DestBranchNo	 >	0 and
                        DistressRouting.BranchNo	 =	kunde.VertriebszentrumNr and
                        DistressRouting.CustomerNo	 =	kunde.KundenNr
                        order by kunde.nameapo;
        exec sql open CSelRouted28;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelRouted28" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelRouted28;
        return CheckSql( fun, stError, "%s", "close CSelRouted28" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelRouted28 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->DESTBRANCHNO,
                     :d->NAMEAPO,
                     :d->ORT,
                     :d->POSTLEITZAHL,
                     :d->PERSONALNRVERTR,
                     :d->KZKDKLASSE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelRouted28" )) == IS_ERROR )
        return rc;
    return rc;
}



/* DistressRouting: Insert ****************************************************/



/* DistressRouting: Update ****************************************************/

/* DistressRouting::Update ****************************************************/

retClient Distressrouting_Update(distressroutingS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Distressrouting_Update";
    exec sql begin declare section;
    distressroutingS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate29 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     DestBranchNo
               from DISTRESSROUTING
              where DistressRouting.BranchNo	 =	:d->BRANCHNO	 and
                    DistressRouting.CustomerNo	 =	:d->CUSTOMERNO
              for update;
    exec sql open CUpdate29;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate29" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate29;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate29" ) ) != IS_OK )
            break;
        exec sql update distressrouting set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     DestBranchNo = :d->DESTBRANCHNO where current of CUpdate29;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate29" ) ) != IS_OK )
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



/* DistressRouting: Select ****************************************************/



/* DistressRouting: Other *****************************************************/

/* DistressRouting::GetCount **************************************************/

retClient Distressrouting_GetCount(distressroutingS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  bool bInTrans = FALSE;
  char *fun = "Distressrouting_GetCount";
  exec sql begin declare section;
  distressroutingS *d;
  exec sql end declare section;

  d = a;

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->CUSTOMERNO from distressrouting
            where branchno = :d->BRANCHNO;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->CUSTOMERNO = 0; 

  return (retClient)IS_OK;
}



/******************************************************************************/
/*                                                                            */
/* header  : EncloserTimes.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:24 2022                                         */
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
#include "customer.h"

/* EncloserTimes: Select ******************************************************/

/* EncloserTimes::SelList *****************************************************/

retClient Enclosertimes_SelList(enclosertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Enclosertimes_SelList";
    exec sql begin declare section;
    enclosertimesS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList30 cursor with hold for
                  select encloserscale.BranchNo,
                     encloserscale.CustomerNo,
                     encloserscale.TimeDiff,
                     encloserscale.MaxPositions
                from ENCLOSERSCALE
                  where EncloserScale.BranchNo	 =	:d->BRANCHNO	 and
                        EncloserScale.CustomerNo	 =	:d->CUSTOMERNO	
                        order by EncloserScale.TimeDiff desc;
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
    exec sql fetch CSelList30 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->TIMEDIFF,
                     :d->MAXPOSITIONS;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList30" )) == IS_ERROR )
        return rc;
    return rc;
}



/* EncloserTimes: Insert ******************************************************/

/* EncloserTimes::Insert ******************************************************/

retClient Enclosertimes_Insert(enclosertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Enclosertimes_Insert";
    exec sql begin declare section;
    enclosertimesS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into encloserscale (BranchNo,
                     CustomerNo,
                     TimeDiff,
                     MaxPositions)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->TIMEDIFF,
                     :d->MAXPOSITIONS);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert encloserscale" ) ) != IS_OK )
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



/* EncloserTimes: Update ******************************************************/

/* EncloserTimes::Update ******************************************************/

retClient Enclosertimes_Update(enclosertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Enclosertimes_Update";
    exec sql begin declare section;
    enclosertimesS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate31 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     TimeDiff,
                     MaxPositions
               from EncloserScale
              where EncloserScale.BranchNo	 =	:d->BRANCHNO	 and
                    EncloserScale.CustomerNo	 =	:d->CUSTOMERNO	 and
                    EncloserScale.TimeDiff	 =	:d->TIMEDIFF
              for update;
    exec sql open CUpdate31;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate31" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate31;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate31" ) ) != IS_OK )
            break;
        exec sql update encloserscale set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     TimeDiff = :d->TIMEDIFF,
                     MaxPositions = :d->MAXPOSITIONS where current of CUpdate31;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate31" ) ) != IS_OK )
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



/* EncloserTimes: Select ******************************************************/

/* EncloserTimes::Delete ******************************************************/

retClient Enclosertimes_Delete(enclosertimesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Enclosertimes_Delete";
    exec sql begin declare section;
    enclosertimesS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete32 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     TimeDiff,
                     MaxPositions
               from EncloserScale
              where EncloserScale.BranchNo	 =	:d->BRANCHNO	 and
                    EncloserScale.CustomerNo	 =	:d->CUSTOMERNO	 and
                    EncloserScale.TimeDiff	 =	:d->TIMEDIFF	 and
                    EncloserScale.MaxPositions	 =	:d->MAXPOSITIONS
              for update;
    exec sql open CDelete32;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete32" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete32;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete32" ) ) != IS_OK )
            break;
        exec sql delete from encloserscale where current of CDelete32;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete32" ) ) != IS_OK )
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



/* EncloserTimes: Other *******************************************************/

/* EncloserTimes::CopyEncloser ************************************************/

retClient Enclosertimes_CopyEncloser(enclosertimesS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Enclosertimes_CopyEncloser";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
short sBranchno;
long lCustomerno;
short sTimediff;
short sMaxpositions;
enclosertimesS *d;
exec sql end declare section;

d = a;
exec sql declare CSelcopyencloser cursor with hold for
  select branchno,timediff,maxpositions
  from encloserscale
  where
  branchno = :d->BRANCHNO and
  customerno = :d->CUSTOMERNO;
exec sql open CSelcopyencloser;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
for(;;)
{
  exec sql fetch CSelcopyencloser into :sBranchno,:sTimediff,:sMaxpositions;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelcopyencloser;" ) ) != IS_OK )
    break;
  exec sql insert into encloserscale
  (Branchno,Customerno,Timediff,Maxpositions)
  values
  (:sBranchno,:d->KUNDENNR,:sTimediff,:sMaxpositions);
  if ( ( rc=CheckSql( fun, stError,  "%s", "insert CSelcopyencloser;" ) ) != IS_OK )
  {
    if(rc == IS_EXISTS) continue;
    else break;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : KNDTOURFENSTER.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:26 2022                                         */
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
#include "customer.h"

/* KNDTOURFENSTER: Select *****************************************************/

/* KNDTOURFENSTER::SelPeriods *************************************************/

retClient Kndtourfenster_SelPeriods(kndtourfensterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndtourfenster_SelPeriods";
    exec sql begin declare section;
    kndtourfensterS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelPeriods33 cursor with hold for
                  select orderperiod.CustomerNo,
                     orderperiod.tourid,
                     orderperiod.BranchNo,
                     orderperiod.weekday,
                     orderperiodtime.FromTime,
                     orderperiodtime.ToTime,
                     orderperiodtime.MainTime
                from ORDERPERIOD, ORDERPERIODTIME
                  where OrderPeriod.CustomerNo	 =	:d->CUSTOMERNO	 and
                        OrderPeriod.BranchNo	 =	:d->BRANCHNO	 and
                        OrderPeriod.weekday	 =	:d->WEEKDAY	 and
                        OrderPeriod.tourid	 =	:d->TOURID	 and
                        OrderPeriod.id	 =	OrderPeriodTime.Order_Period_ID
                        order by OrderPeriodTime.FromTime;
        exec sql open CSelPeriods33;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelPeriods33" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelPeriods33;
        return CheckSql( fun, stError, "%s", "close CSelPeriods33" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelPeriods33 into :d->CUSTOMERNO,
                     :d->TOURID,
                     :d->BRANCHNO,
                     :d->WEEKDAY,
                     :d->FROMTIME,
                     :d->TOTIME,
                     :d->MAINTIME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelPeriods33" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KNDTOURFENSTER: Insert *****************************************************/



/* KNDTOURFENSTER: Update *****************************************************/



/* KNDTOURFENSTER: Select *****************************************************/



/* KNDTOURFENSTER: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KNDTOURWOCHE.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:29 2022                                         */
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
#include "customer.h"

/* KNDTOURWOCHE: Select *******************************************************/

/* KNDTOURWOCHE::SelList ******************************************************/

retClient Kndtourwoche_SelList(kndtourwocheS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndtourwoche_SelList";
    exec sql begin declare section;
    kndtourwocheS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList34 cursor with hold for
                  select tourplantagwoche.VertriebszentrumNr,
                     tourplantagwoche.KundenNr,
                     tourplantagwoche.weekday,
                     tourplantagwoche.IstVerbundTour,
                     tourplantagwoche.kdauftragart,
                     tourplantagwoche.IsBTM,
                     tourplantagwoche.IsKK,
                     tourplantagwoche.IsK08,
                     tourplantagwoche.IsK20,
                     tourplantagwoche.ReturnsTour,
                     tourplantagwoche.transpexclpsycho,
                     tourplanwoche.tourid,
                     tourplanwoche.tagestyp
                from TOURPLANTAGWOCHE, TOURPLANWOCHE
                  where TourplantagWoche.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        TourplantagWoche.KundenNr	 =	:d->KUNDENNR	 and
                        TourplantagWoche.VertriebszentrumNr	 =	TourPlanWoche.filialnr and
                        TourplantagWoche.tourid	 =	TourPlanWoche.tourid and
                        TourplantagWoche.weekday	 =	TourPlanWoche.weekday
                        order by TourPlanWoche.weekday, TourPlanWoche.tourid;
        exec sql open CSelList34;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList34" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList34;
        return CheckSql( fun, stError, "%s", "close CSelList34" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList34 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->WEEKDAY,
                     :d->ISTVERBUNDTOUR,
                     :d->KDAUFTRAGART,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20,
                     :d->RETURNSTOUR,
                     :d->TRANSPEXCLPSYCHO,
                     :d->TOURID,
                     :d->TAGESTYP;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList34" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KNDTOURWOCHE: Insert *******************************************************/



/* KNDTOURWOCHE: Update *******************************************************/



/* KNDTOURWOCHE: Select *******************************************************/



/* KNDTOURWOCHE: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KNDTOURWOCHE2.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:31 2022                                         */
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
#include "customer.h"

/* KNDTOURWOCHE2: Select ******************************************************/

/* KNDTOURWOCHE2::SelList *****************************************************/

retClient Kndtourwoche2_SelList(kndtourwoche2S *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndtourwoche2_SelList";
    exec sql begin declare section;
    kndtourwoche2S *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList35 cursor with hold for
                  select tourplanconstime.VertriebszentrumNr,
                     tourplanconstime.KundenNr,
                     tourplanconstime.tourid,
                     tourplanconstime.datumkommi,
                     tourplanconstime.ConsTime
                from TOURPLANCONSTIME
                  where TourplanConsTime.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        TourplanConsTime.KundenNr	 =	:d->KUNDENNR	 and
                        TourplanConsTime.tourid	 =	:d->TOURID and
                        TourplanConsTime.datumkommi	 =	:d->DATUMKOMMI
                        order by TourplanConsTime.ConsTime;
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
    exec sql fetch CSelList35 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TOURID,
                     :d->DATUMKOMMI,
                     :d->CONSTIME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList35" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KNDTOURWOCHE2: Insert ******************************************************/



/* KNDTOURWOCHE2: Update ******************************************************/



/* KNDTOURWOCHE2: Select ******************************************************/



/* KNDTOURWOCHE2: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KNDTOURWOCHE3.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:33 2022                                         */
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
#include "customer.h"

/* KNDTOURWOCHE3: Select ******************************************************/

/* KNDTOURWOCHE3::SelList *****************************************************/

retClient Kndtourwoche3_SelList(kndtourwoche3S *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndtourwoche3_SelList";
    exec sql begin declare section;
    kndtourwoche3S *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList36 cursor with hold for
                  select tourconstime.filialnr,
                     tourconstime.tourid,
                     tourconstime.datumkommi,
                     tourconstime.ConsTime
                from TOURCONSTIME
                  where TourConsTime.filialnr	 =	:d->FILIALNR	 and
                        TourConsTime.tourid	 =	:d->TOURID   and
                        TourConsTime.datumkommi	 =	:d->DATUMKOMMI
                        order by TourConsTime.ConsTime;
        exec sql open CSelList36;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList36" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList36;
        return CheckSql( fun, stError, "%s", "close CSelList36" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList36 into :d->FILIALNR,
                     :d->TOURID,
                     :d->DATUMKOMMI,
                     :d->CONSTIME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList36" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KNDTOURWOCHE3: Insert ******************************************************/



/* KNDTOURWOCHE3: Update ******************************************************/



/* KNDTOURWOCHE3: Select ******************************************************/



/* KNDTOURWOCHE3: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KndFilInfo.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:35 2022                                         */
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
#include "customer.h"

/* KndFilInfo: Select *********************************************************/

/* KndFilInfo::SelKnd *********************************************************/

retClient Kndfilinfo_SelKnd(kndfilinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndfilinfo_SelKnd";
    exec sql begin declare section;
    kndfilinfoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kndausku.KundenNr,
                     kndausku.VertriebszentrumNr,
                     kndausku.DispoGebuehr,
                     kndausku.BtmGebuehr,
                     kndausku.DokuGebuehr,
                     kunde.tourenkippzeit
                into :d->KUNDENNR,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->DISPOGEBUEHR,
                     :d->BTMGEBUEHR,
                     :d->DOKUGEBUEHR,
                     :d->TOURENKIPPZEIT
                from KNDAUSKU, KUNDE
              where kndausku.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kndausku.KundenNr	 =	:d->KUNDENNR	 and
                    kunde.VertriebszentrumNr	 =	kndausku.VertriebszentrumNr and
                    kunde.KundenNr	 =	kndausku.KundenNr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KndFilInfo: Insert *********************************************************/



/* KndFilInfo: Update *********************************************************/



/* KndFilInfo: Select *********************************************************/



/* KndFilInfo: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KndFilInfo2.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:37 2022                                         */
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
#include "customer.h"

/* KndFilInfo2: Select ********************************************************/

/* KndFilInfo2::SelInfo *******************************************************/

retClient Kndfilinfo2_SelInfo(kndfilinfo2S *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kndfilinfo2_SelInfo";
    exec sql begin declare section;
    kndfilinfo2S *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select paraauftragbearb.filialnr,
                     paraauftragbearb.durchlaufnormal,
                     paraauftragbearb.durchlaufeilbote,
                     paraauftragbearb.tourverspaetung,
                     paraauftragbearb.tourenkippzeit
                into :d->FILIALNR,
                     :d->DURCHLAUFNORMAL,
                     :d->DURCHLAUFEILBOTE,
                     :d->TOURVERSPAETUNG,
                     :d->TOURENKIPPZEIT
                from PARAAUFTRAGBEARB
              where paraauftragbearb.filialnr	 =	:d->FILIALNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KndFilInfo2: Insert ********************************************************/



/* KndFilInfo2: Update ********************************************************/



/* KndFilInfo2: Select ********************************************************/



/* KndFilInfo2: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KreditLimit.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:42 2022                                         */
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
#include "customer.h"

/* KreditLimit: Select ********************************************************/

/* KreditLimit::SelLimit ******************************************************/

retClient Kreditlimit_SelLimit(kreditlimitS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kreditlimit_SelLimit";
    exec sql begin declare section;
    kreditlimitS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select debtlimit.partnerno,
                     debtlimit.partnername,
                     debtlimit.limit,
                     debtlimit.sum_debitside,
                     debtlimit.sum_creditside,
                     debtlimit.sum_monturnover,
                     debtlimit.sum_dayturnover,
                     debtlimit.sum_returns,
                     debtlimit.sum_goodsreceipt,
                     debtlimit.LimitType,
                     debtlimit.Liste5,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr
                into :d->PARTNERNO,
                     :d->PARTNERNAME,
                     :d->LIMIT,
                     :d->SUM_DEBITSIDE,
                     :d->SUM_CREDITSIDE,
                     :d->SUM_MONTURNOVER,
                     :d->SUM_DAYTURNOVER,
                     :d->SUM_RETURNS,
                     :d->SUM_GOODSRECEIPT,
                     :d->LIMITTYPE,
                     :d->LISTE5,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR
                from DEBTLIMIT, kunde
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    debtlimit.partnerno	 =	kunde.partnernr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* KreditLimit::SelLimit1 *****************************************************/

retClient Kreditlimit_SelLimit1(kreditlimitS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kreditlimit_SelLimit1";
    exec sql begin declare section;
    kreditlimitS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select debtlimit.partnerno,
                     debtlimit.partnername,
                     debtlimit.limit,
                     debtlimit.sum_debitside,
                     debtlimit.sum_creditside,
                     debtlimit.sum_monturnover,
                     debtlimit.sum_dayturnover,
                     debtlimit.sum_returns,
                     debtlimit.sum_goodsreceipt,
                     debtlimit.LimitType,
                     debtlimit.Liste5,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr
                into :d->PARTNERNO,
                     :d->PARTNERNAME,
                     :d->LIMIT,
                     :d->SUM_DEBITSIDE,
                     :d->SUM_CREDITSIDE,
                     :d->SUM_MONTURNOVER,
                     :d->SUM_DAYTURNOVER,
                     :d->SUM_RETURNS,
                     :d->SUM_GOODSRECEIPT,
                     :d->LIMITTYPE,
                     :d->LISTE5,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR
                from DEBTLIMIT, KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    debtlimit.partnerno	 =	kunde.partnernr and
                    debtlimit.LimitType	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* KreditLimit::SelLimit2 *****************************************************/

retClient Kreditlimit_SelLimit2(kreditlimitS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kreditlimit_SelLimit2";
    exec sql begin declare section;
    kreditlimitS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select debtlimit.partnerno,
                     debtlimit.partnername,
                     debtlimit.limit,
                     debtlimit.sum_debitside,
                     debtlimit.sum_creditside,
                     debtlimit.sum_monturnover,
                     debtlimit.sum_dayturnover,
                     debtlimit.sum_returns,
                     debtlimit.sum_goodsreceipt,
                     debtlimit.LimitType,
                     debtlimit.Liste5,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr
                into :d->PARTNERNO,
                     :d->PARTNERNAME,
                     :d->LIMIT,
                     :d->SUM_DEBITSIDE,
                     :d->SUM_CREDITSIDE,
                     :d->SUM_MONTURNOVER,
                     :d->SUM_DAYTURNOVER,
                     :d->SUM_RETURNS,
                     :d->SUM_GOODSRECEIPT,
                     :d->LIMITTYPE,
                     :d->LISTE5,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR
                from DEBTLIMIT, KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    debtlimit.partnerno	 =	kunde.partnernr and
                    debtlimit.LimitType	 =	2;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* KreditLimit::SelLimitMain **************************************************/

retClient Kreditlimit_SelLimitMain(kreditlimitS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kreditlimit_SelLimitMain";
    exec sql begin declare section;
    kreditlimitS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select debtlimit.partnerno,
                     debtlimit.partnername,
                     debtlimit.limit,
                     debtlimit.sum_debitside,
                     debtlimit.sum_creditside,
                     debtlimit.sum_monturnover,
                     debtlimit.sum_dayturnover,
                     debtlimit.sum_returns,
                     debtlimit.sum_goodsreceipt,
                     debtlimit.LimitType,
                     debtlimit.Liste5,
                     kunde.VertriebszentrumNr,
                     kunde.KundenNr
                into :d->PARTNERNO,
                     :d->PARTNERNAME,
                     :d->LIMIT,
                     :d->SUM_DEBITSIDE,
                     :d->SUM_CREDITSIDE,
                     :d->SUM_MONTURNOVER,
                     :d->SUM_DAYTURNOVER,
                     :d->SUM_RETURNS,
                     :d->SUM_GOODSRECEIPT,
                     :d->LIMITTYPE,
                     :d->LISTE5,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR
                from DEBTLIMIT, KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    debtlimit.partnerno	 =	kunde.maincstno and
                    debtlimit.LimitType	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KreditLimit: Insert ********************************************************/



/* KreditLimit: Update ********************************************************/



/* KreditLimit: Select ********************************************************/



/* KreditLimit: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KundeLizensen.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:44 2022                                         */
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
#include "customer.h"

/* KundeLizensen: Select ******************************************************/

/* KundeLizensen::SelLicenses *************************************************/

retClient Kundelizensen_SelLicenses(kundelizensenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kundelizensen_SelLicenses";
    exec sql begin declare section;
    kundelizensenS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.ApoLizens,
                     kunde.BTMLizens
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->APOLIZENS,
                     :d->BTMLIZENS
                from KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KundeLizensen: Insert ******************************************************/



/* KundeLizensen: Update ******************************************************/



/* KundeLizensen: Select ******************************************************/



/* KundeLizensen: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : KundeVerbundFiliale.cxx                                          */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:47 2022                                         */
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
#include "customer.h"

/* KundeVerbundFiliale: Select ************************************************/

/* KundeVerbundFiliale::Sel ***************************************************/

retClient Kundeverbundfiliale_Sel(kundeverbundfilialeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kundeverbundfiliale_Sel";
    exec sql begin declare section;
    kundeverbundfilialeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel44 cursor with hold for
                  select kdverbundfiliale.VertriebszentrumNr,
                     kdverbundfiliale.KundenNr,
                     kdverbundfiliale.reihenfolgenr,
                     kdverbundfiliale.verbundfilialnr
                from kdverbundfiliale
                  where KdVerbundFiliale.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        KdVerbundFiliale.KundenNr	 =	:d->KUNDENNR	
                        order by KdVerbundFiliale.reihenfolgenr;
        exec sql open CSel44;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel44" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel44;
        return CheckSql( fun, stError, "%s", "close CSel44" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel44 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->REIHENFOLGENR,
                     :d->VERBUNDFILIALNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel44" )) == IS_ERROR )
        return rc;
    return rc;
}



/* KundeVerbundFiliale: Insert ************************************************/

/* KundeVerbundFiliale::Insert ************************************************/

retClient Kundeverbundfiliale_Insert(kundeverbundfilialeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Kundeverbundfiliale_Insert";
    exec sql begin declare section;
    kundeverbundfilialeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into kdverbundfiliale (VertriebszentrumNr,
                     KundenNr,
                     reihenfolgenr,
                     verbundfilialnr)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->REIHENFOLGENR,
                     :d->VERBUNDFILIALNR);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kdverbundfiliale" ) ) != IS_OK )
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



/* KundeVerbundFiliale: Update ************************************************/

/* KundeVerbundFiliale::Update ************************************************/

retClient Kundeverbundfiliale_Update(kundeverbundfilialeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Kundeverbundfiliale_Update";
    exec sql begin declare section;
    kundeverbundfilialeS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate45 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     reihenfolgenr,
                     verbundfilialnr
               from kdverbundfiliale
              where KdVerbundFiliale.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KdVerbundFiliale.KundenNr	 =	:d->KUNDENNR	 and
                    KdVerbundFiliale.verbundfilialnr	 =	:d->VERBUNDFILIALNR
              for update;
    exec sql open CUpdate45;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate45" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate45;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate45" ) ) != IS_OK )
            break;
        exec sql update kdverbundfiliale set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     reihenfolgenr = :d->REIHENFOLGENR,
                     verbundfilialnr = :d->VERBUNDFILIALNR where current of CUpdate45;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate45" ) ) != IS_OK )
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



/* KundeVerbundFiliale: Select ************************************************/

/* KundeVerbundFiliale::Delete ************************************************/

retClient Kundeverbundfiliale_Delete(kundeverbundfilialeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Kundeverbundfiliale_Delete";
    exec sql begin declare section;
    kundeverbundfilialeS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete46 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     reihenfolgenr,
                     verbundfilialnr
               from kdverbundfiliale
              where KdVerbundFiliale.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KdVerbundFiliale.KundenNr	 =	:d->KUNDENNR	 and
                    KdVerbundFiliale.verbundfilialnr	 =	:d->VERBUNDFILIALNR
              for update;
    exec sql open CDelete46;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete46" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete46;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete46" ) ) != IS_OK )
            break;
        exec sql delete from kdverbundfiliale where current of CDelete46;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete46" ) ) != IS_OK )
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



/* KundeVerbundFiliale: Other *************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Liste5.cxx                                                       */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:50 2022                                         */
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
#include "customer.h"

/* Liste5: Select *************************************************************/

/* Liste5::SelList ************************************************************/

retClient Liste5_SelList(liste5S *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Liste5_SelList";
    exec sql begin declare section;
    liste5S *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList47 cursor with hold for
                  select discountgrp.BranchNo,
                     discountgrpmem.ArticleNo,
                     artikelpreis.preisekapo,
                     discountgrp.CustomerNo,
                     artikelpreis.preis_typ,
                     artikelzentral.TaxLevel,
                     artikelzentral.artikel_langname
                from DISCOUNTGRP, DISCOUNTGRPMEM, ARTIKELZENTRAL, ARTIKELPREIS
                  where DiscountGrp.BranchNo	 =	:d->BRANCHNO	 and
                        DiscountGrp.CustomerNo	 =	:d->CUSTOMERNO	 and
                        DiscountGrp.discountgrptype	 =	3 and
                        DiscountGrp.BranchNo	 =	DiscountGrpMem.BranchNo and
                        DiscountGrp.DiscountGrpNo	 =	DiscountGrpMem.DiscountGrpNo and
                        DiscountGrpMem.ArticleNo	 =	artikelzentral.artikel_nr and
                        DiscountGrpMem.ArticleNo	 =	artikelpreis.artikel_nr
                        order by artikelzentral.artikel_langname;
        exec sql open CSelList47;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList47" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList47;
        return CheckSql( fun, stError, "%s", "close CSelList47" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList47 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->PREISEKAPO,
                     :d->CUSTOMERNO,
                     :d->PREIS_TYP,
                     :d->TAXLEVEL,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList47" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Liste5: Insert *************************************************************/



/* Liste5: Update *************************************************************/



/* Liste5: Select *************************************************************/



/* Liste5: Other **************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerEmergencyServicePlan.cxx                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:56:55 2022                                         */
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
#include "customer.h"

/* MCustomerEmergencyServicePlan: Select **************************************/

/* MCustomerEmergencyServicePlan::SelList *************************************/

retClient Mcustomeremergencyserviceplan_SelList(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomeremergencyserviceplan_SelList";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList48 cursor with hold for
                  select kundenotdienstplan.VertriebszentrumNr,
                     kundenotdienstplan.KundenNr,
                     kundenotdienstplan.datum,
                     kundenotdienstplan.uhrzeitvon,
                     kundenotdienstplan.uhrzeitbis,
                     kundenotdienstplan.bemerkungen,
                     kundenotdienstplan.IsBTM,
                     kundenotdienstplan.IsKK,
                     kundenotdienstplan.IsK08,
                     kundenotdienstplan.IsK20
                from KUNDENOTDIENSTPLAN
                  where KundeNotdienstPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        KundeNotdienstPlan.KundenNr	 =	:d->KUNDENNR;
        exec sql open CSelList48;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList48" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList48;
        return CheckSql( fun, stError, "%s", "close CSelList48" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList48 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->UHRZEITVON,
                     :d->UHRZEITBIS,
                     :d->BEMERKUNGEN,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList48" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerEmergencyServicePlan::SelListHist *********************************/

retClient Mcustomeremergencyserviceplan_SelListHist(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomeremergencyserviceplan_SelListHist";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListHist49 cursor with hold for
                  select kundenotdienstplan.VertriebszentrumNr,
                     kundenotdienstplan.KundenNr,
                     kundenotdienstplan.datum,
                     kundenotdienstplan.uhrzeitvon,
                     kundenotdienstplan.uhrzeitbis,
                     kundenotdienstplan.bemerkungen,
                     kundenotdienstplan.IsBTM,
                     kundenotdienstplan.IsKK,
                     kundenotdienstplan.IsK08,
                     kundenotdienstplan.IsK20
                from KUNDENOTDIENSTPLAN
                  where KundeNotdienstPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        KundeNotdienstPlan.datum	 =	:d->DATUM;
        exec sql open CSelListHist49;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHist49" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListHist49;
        return CheckSql( fun, stError, "%s", "close CSelListHist49" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListHist49 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->UHRZEITVON,
                     :d->UHRZEITBIS,
                     :d->BEMERKUNGEN,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListHist49" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerEmergencyServicePlan::SelUni **************************************/

retClient Mcustomeremergencyserviceplan_SelUni(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomeremergencyserviceplan_SelUni";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kundenotdienstplan.VertriebszentrumNr,
                     kundenotdienstplan.KundenNr,
                     kundenotdienstplan.datum,
                     kundenotdienstplan.uhrzeitvon,
                     kundenotdienstplan.uhrzeitbis,
                     kundenotdienstplan.bemerkungen,
                     kundenotdienstplan.IsBTM,
                     kundenotdienstplan.IsKK,
                     kundenotdienstplan.IsK08,
                     kundenotdienstplan.IsK20
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->UHRZEITVON,
                     :d->UHRZEITBIS,
                     :d->BEMERKUNGEN,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20
                from KUNDENOTDIENSTPLAN
              where KundeNotdienstPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeNotdienstPlan.KundenNr	 =	:d->KUNDENNR	 and
                    KundeNotdienstPlan.datum	 =	:d->DATUM;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerEmergencyServicePlan: Insert **************************************/

/* MCustomerEmergencyServicePlan::Insert **************************************/

retClient Mcustomeremergencyserviceplan_Insert(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomeremergencyserviceplan_Insert";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->BEMERKUNGEN);
    if ( *d->BEMERKUNGEN == '\0' )
        strcpy( d->BEMERKUNGEN, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into kundenotdienstplan (VertriebszentrumNr,
                     KundenNr,
                     datum,
                     uhrzeitvon,
                     uhrzeitbis,
                     bemerkungen,
                     IsBTM,
                     IsKK,
                     IsK08,
                     IsK20)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUM,
                     :d->UHRZEITVON,
                     :d->UHRZEITBIS,
                     :d->BEMERKUNGEN,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kundenotdienstplan" ) ) != IS_OK )
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



/* MCustomerEmergencyServicePlan: Update **************************************/

/* MCustomerEmergencyServicePlan::Update **************************************/

retClient Mcustomeremergencyserviceplan_Update(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomeremergencyserviceplan_Update";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->BEMERKUNGEN);
    if ( *d->BEMERKUNGEN == '\0' )
        strcpy( d->BEMERKUNGEN, " " );


    exec sql declare CUpdate51 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     uhrzeitvon,
                     uhrzeitbis,
                     bemerkungen,
                     IsBTM,
                     IsKK,
                     IsK08,
                     IsK20
               from KUNDENOTDIENSTPLAN
              where KundeNotdienstPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeNotdienstPlan.KundenNr	 =	:d->KUNDENNR	 and
                    KundeNotdienstPlan.datum	 =	:d->DATUM
              for update;
    exec sql open CUpdate51;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate51" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate51;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate51" ) ) != IS_OK )
            break;
        exec sql update kundenotdienstplan set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     datum = :d->DATUM,
                     uhrzeitvon = :d->UHRZEITVON,
                     uhrzeitbis = :d->UHRZEITBIS,
                     bemerkungen = :d->BEMERKUNGEN,
                     IsBTM = :d->ISBTM,
                     IsKK = :d->ISKK,
                     IsK08 = :d->ISK08,
                     IsK20 = :d->ISK20 where current of CUpdate51;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate51" ) ) != IS_OK )
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



/* MCustomerEmergencyServicePlan: Select **************************************/

/* MCustomerEmergencyServicePlan::Delete **************************************/

retClient Mcustomeremergencyserviceplan_Delete(mcustomeremergencyserviceplanS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomeremergencyserviceplan_Delete";
    exec sql begin declare section;
    mcustomeremergencyserviceplanS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete52 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datum,
                     uhrzeitvon,
                     uhrzeitbis,
                     bemerkungen,
                     IsBTM,
                     IsKK,
                     IsK08,
                     IsK20
               from KUNDENOTDIENSTPLAN
              where KundeNotdienstPlan.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeNotdienstPlan.KundenNr	 =	:d->KUNDENNR	 and
                    KundeNotdienstPlan.datum	 =	:d->DATUM
              for update;
    exec sql open CDelete52;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete52" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete52;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete52" ) ) != IS_OK )
            break;
        exec sql delete from kundenotdienstplan where current of CDelete52;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete52" ) ) != IS_OK )
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



/* MCustomerEmergencyServicePlan: Other ***************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MCustomerVacation.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:00 2022                                         */
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
#include "customer.h"

/* MCustomerVacation: Select **************************************************/

/* MCustomerVacation::SelList *************************************************/

retClient Mcustomervacation_SelList(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomervacation_SelList";
    exec sql begin declare section;
    mcustomervacationS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList53 cursor with hold for
                  select kundeurlaub.VertriebszentrumNr,
                     kundeurlaub.KundenNr,
                     kundeurlaub.datumgueltigab,
                     kundeurlaub.datumgueltigbis
                from KUNDEURLAUB
                  where KundeUrlaub.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        KundeUrlaub.KundenNr	 =	:d->KUNDENNR;
        exec sql open CSelList53;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList53" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList53;
        return CheckSql( fun, stError, "%s", "close CSelList53" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList53 into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUMGUELTIGAB,
                     :d->DATUMGUELTIGBIS;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList53" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MCustomerVacation::SelUni **************************************************/

retClient Mcustomervacation_SelUni(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomervacation_SelUni";
    exec sql begin declare section;
    mcustomervacationS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kundeurlaub.VertriebszentrumNr,
                     kundeurlaub.KundenNr,
                     kundeurlaub.datumgueltigab,
                     kundeurlaub.datumgueltigbis
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUMGUELTIGAB,
                     :d->DATUMGUELTIGBIS
                from KUNDEURLAUB
              where KundeUrlaub.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeUrlaub.KundenNr	 =	:d->KUNDENNR	 and
                    KundeUrlaub.datumgueltigab	<=	:d->DATUMGUELTIGAB	 and
                    KundeUrlaub.datumgueltigbis	>=	:d->DATUMGUELTIGAB;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCustomerVacation: Insert **************************************************/

/* MCustomerVacation::Insert **************************************************/

retClient Mcustomervacation_Insert(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomervacation_Insert";
    exec sql begin declare section;
    mcustomervacationS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into kundeurlaub (VertriebszentrumNr,
                     KundenNr,
                     datumgueltigab,
                     datumgueltigbis)
        values (:d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUMGUELTIGAB,
                     :d->DATUMGUELTIGBIS);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kundeurlaub" ) ) != IS_OK )
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



/* MCustomerVacation: Update **************************************************/

/* MCustomerVacation::Update **************************************************/

retClient Mcustomervacation_Update(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcustomervacation_Update";
    exec sql begin declare section;
    mcustomervacationS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate55 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datumgueltigab,
                     datumgueltigbis
               from KUNDEURLAUB
              where KundeUrlaub.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeUrlaub.KundenNr	 =	:d->KUNDENNR	 and
                    KundeUrlaub.datumgueltigab	 =	:d->DATUMGUELTIGAB
              for update;
    exec sql open CUpdate55;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate55" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate55;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate55" ) ) != IS_OK )
            break;
        exec sql update kundeurlaub set VertriebszentrumNr = :d->VERTRIEBSZENTRUMNR,
                     KundenNr = :d->KUNDENNR,
                     datumgueltigab = :d->DATUMGUELTIGAB,
                     datumgueltigbis = :d->DATUMGUELTIGBIS where current of CUpdate55;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate55" ) ) != IS_OK )
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



/* MCustomerVacation: Select **************************************************/

/* MCustomerVacation::Delete **************************************************/

retClient Mcustomervacation_Delete(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Mcustomervacation_Delete";
    exec sql begin declare section;
    mcustomervacationS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete56 cursor with hold for
              select VertriebszentrumNr,
                     KundenNr,
                     datumgueltigab,
                     datumgueltigbis
               from KUNDEURLAUB
              where KundeUrlaub.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeUrlaub.KundenNr	 =	:d->KUNDENNR	 and
                    KundeUrlaub.datumgueltigab	 =	:d->DATUMGUELTIGAB
              for update;
    exec sql open CDelete56;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete56" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete56;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete56" ) ) != IS_OK )
            break;
        exec sql delete from kundeurlaub where current of CDelete56;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete56" ) ) != IS_OK )
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



/* MCustomerVacation: Other ***************************************************/

/* MCustomerVacation::SelNextEffective ****************************************/

retClient Mcustomervacation_SelNextEffective(mcustomervacationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcustomervacation_SelUni";
    exec sql begin declare section;
    mcustomervacationS *d;
    long lDate;
    exec sql end declare section;

    d = a;
    lDate = ppGGetDate();

    if ( bIsTrans);

    exec sql declare CSelNextEffective cursor for
              select kundeurlaub.VertriebszentrumNr,
                     kundeurlaub.KundenNr,
                     kundeurlaub.datumgueltigab,
                     kundeurlaub.datumgueltigbis
                from KUNDEURLAUB KUNDEURLAUB
              where KundeUrlaub.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    KundeUrlaub.KundenNr	 =	:d->KUNDENNR	 and
                    KundeUrlaub.datumgueltigbis	>=	:lDate
              order by KundeUrlaub.datumgueltigab;
    exec sql open CSelNextEffective;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CSelNextEffective" ) ) != IS_OK )
        return rc;
    exec sql fetch CSelNextEffective into
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->DATUMGUELTIGAB,
                     :d->DATUMGUELTIGBIS;
    if ((rc = CheckSql( fun, stError, "%s", "fetch CSelNextEffective" )) == IS_ERROR )
        return rc;
    exec sql close CSelNextEffective;
    return CheckSql( fun, stError, "%s", "close CSelNextEffective" );
}



/******************************************************************************/
/*                                                                            */
/* header  : PayTerm.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:02 2022                                         */
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
#include "customer.h"

/* PayTerm: Select ************************************************************/

/* PayTerm::SelList ***********************************************************/

retClient Payterm_SelList(paytermS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Payterm_SelList";
    exec sql begin declare section;
    paytermS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList57 cursor with hold for
                  select paymentterms.payment_term,
                     paymentterms.paymentarget,
                     paymentterms.cashdisount
                from PAYMENTTERMS, KUNDE
                  where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kunde.KundenNr	 =	:d->KUNDENNR	 and
                        PaymentTerms.payment_term	 =	kunde.payment_term
                        order by PaymentTerms.paymentarget desc;
        exec sql open CSelList57;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList57" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList57;
        return CheckSql( fun, stError, "%s", "close CSelList57" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList57 into :d->PAYMENT_TERM,
                     :d->PAYMENTARGET,
                     :d->CASHDISOUNT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList57" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PayTerm: Insert ************************************************************/



/* PayTerm: Update ************************************************************/



/* PayTerm: Select ************************************************************/



/* PayTerm: Other *************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PaymentList.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:05 2022                                         */
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
#include "customer.h"

/* PaymentList: Select ********************************************************/

/* PaymentList::SelList *******************************************************/

retClient Paymentlist_SelList(paymentlistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Paymentlist_SelList";
    exec sql begin declare section;
    paymentlistS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList58 cursor with hold for
                  select cstpaymentlist.BranchNo,
                     cstpaymentlist.CustomerNo,
                     cstpaymentlist.InvoiceNumber,
                     cstpaymentlist.TotalInvoiceAmount,
                     cstpaymentlist.OpenInvoiceAmount,
                     cstpaymentlist.PaidInvoiceAmount,
                     cstpaymentlist.DriverID,
                     cstpaymentlist.PaymentDate,
                     cstpaymentlist.InvoiceDate,
                     cstpaymentlist.PaymentSpec
                from CSTPAYMENTLIST
                  where CstPaymentList.BranchNo	 =	:d->BRANCHNO	 and
                        CstPaymentList.CustomerNo	 =	:d->CUSTOMERNO	 and
                        CstPaymentList.OpenInvoiceAmount	 !=	0.00	 and
                        CstPaymentList.SequenceNo	 =	0
                        order by CstPaymentList.InvoiceDate, CstPaymentList.InvoiceNumber;
        exec sql open CSelList58;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList58" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList58;
        return CheckSql( fun, stError, "%s", "close CSelList58" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList58 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->INVOICENUMBER,
                     :d->TOTALINVOICEAMOUNT,
                     :d->OPENINVOICEAMOUNT,
                     :d->PAIDINVOICEAMOUNT,
                     :d->DRIVERID,
                     :d->PAYMENTDATE,
                     :d->INVOICEDATE,
                     :d->PAYMENTSPEC;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList58" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PaymentList: Insert ********************************************************/



/* PaymentList: Update ********************************************************/



/* PaymentList: Select ********************************************************/



/* PaymentList: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PrewholeCst.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:06 2022                                         */
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
#include "customer.h"

/* PrewholeCst: Select ********************************************************/

/* PrewholeCst::IsPrewholeCst *************************************************/

retClient Prewholecst_IsPrewholeCst(prewholecstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Prewholecst_IsPrewholeCst";
    exec sql begin declare section;
    prewholecstS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kunde.VertriebszentrumNr,
                     kunde.KundenNr,
                     kunde.MainCstNo
                into :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->MAINCSTNO
                from KUNDE
              where kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    kunde.KundenNr	 =	:d->KUNDENNR	 and
                    kunde.MainCstNo	!=	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PrewholeCst: Insert ********************************************************/



/* PrewholeCst: Update ********************************************************/



/* PrewholeCst: Select ********************************************************/



/* PrewholeCst: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ShipAuxNo.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:10 2022                                         */
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
#include "customer.h"

/* ShipAuxNo: Select **********************************************************/

/* ShipAuxNo::SelList *********************************************************/

retClient Shipauxno_SelList(shipauxnoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Shipauxno_SelList";
    exec sql begin declare section;
    shipauxnoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList60 cursor with hold for
                  select shipauxno.BranchNo,
                     shipauxno.CustomerNo,
                     shipauxno.AuxBranchNo,
                     shipauxno.AuxBGANo
                from SHIPAUXNO
                  where ShipAuxNo.BranchNo	 =	:d->BRANCHNO	 and
                        ShipAuxNo.CustomerNo	 =	:d->CUSTOMERNO	
                        order by ShipAuxNo.AuxBranchNo;
        exec sql open CSelList60;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList60" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList60;
        return CheckSql( fun, stError, "%s", "close CSelList60" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList60 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->AUXBRANCHNO,
                     :d->AUXBGANO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList60" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ShipAuxNo: Insert **********************************************************/

/* ShipAuxNo::Insert **********************************************************/

retClient Shipauxno_Insert(shipauxnoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Shipauxno_Insert";
    exec sql begin declare section;
    shipauxnoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into shipauxno (BranchNo,
                     CustomerNo,
                     AuxBranchNo,
                     AuxBGANo)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->AUXBRANCHNO,
                     :d->AUXBGANO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert shipauxno" ) ) != IS_OK )
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



/* ShipAuxNo: Update **********************************************************/

/* ShipAuxNo::Update **********************************************************/

retClient Shipauxno_Update(shipauxnoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Shipauxno_Update";
    exec sql begin declare section;
    shipauxnoS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate61 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     AuxBranchNo,
                     AuxBGANo
               from SHIPAUXNO
              where ShipAuxNo.BranchNo	 =	:d->BRANCHNO	 and
                    ShipAuxNo.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ShipAuxNo.AuxBranchNo	 =	:d->AUXBRANCHNO
              for update;
    exec sql open CUpdate61;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate61" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate61;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate61" ) ) != IS_OK )
            break;
        exec sql update shipauxno set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     AuxBranchNo = :d->AUXBRANCHNO,
                     AuxBGANo = :d->AUXBGANO where current of CUpdate61;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate61" ) ) != IS_OK )
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



/* ShipAuxNo: Select **********************************************************/

/* ShipAuxNo::Delete **********************************************************/

retClient Shipauxno_Delete(shipauxnoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Shipauxno_Delete";
    exec sql begin declare section;
    shipauxnoS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete62 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     AuxBranchNo,
                     AuxBGANo
               from SHIPAUXNO
              where ShipAuxNo.BranchNo	 =	:d->BRANCHNO	 and
                    ShipAuxNo.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ShipAuxNo.AuxBranchNo	 =	:d->AUXBRANCHNO
              for update;
    exec sql open CDelete62;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete62" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete62;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete62" ) ) != IS_OK )
            break;
        exec sql delete from shipauxno where current of CDelete62;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete62" ) ) != IS_OK )
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



/* ShipAuxNo: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TourPflege.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:14 2022                                         */
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
#include "customer.h"

/* TourPflege: Select *********************************************************/

/* TourPflege::SelTourenKunde *************************************************/

retClient Tourpflege_SelTourenKunde(tourpflegeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tourpflege_SelTourenKunde";
    exec sql begin declare section;
    tourpflegeS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelTourenKunde63 cursor with hold for
                  select tourplantag.tourid,
                     tourplantag.reihenfolgenr,
                     tourplantag.fahrtzeit,
                     tourplantag.bemerkungen,
                     tourplantag.VertriebszentrumNr,
                     tourplantag.KundenNr,
                     tourplantag.tm_date,
                     tourplantag.tm_time,
                     tourplantag.loginId,
                     tourplantag.changeId,
                     tourplantag.koart
                from tourplantag
                  where tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        tourplantag.KundenNr	 =	:d->KUNDENNR	 and
                        tourplantag.datumkommi	 =	:lDate;
        exec sql open CSelTourenKunde63;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelTourenKunde63" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelTourenKunde63;
        return CheckSql( fun, stError, "%s", "close CSelTourenKunde63" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelTourenKunde63 into :d->TOURID,
                     :d->REIHENFOLGENR,
                     :d->FAHRTZEIT,
                     :d->BEMERKUNGEN,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->LOGINID,
                     :d->CHANGEID,
                     :d->KOART;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelTourenKunde63" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TourPflege: Insert *********************************************************/



/* TourPflege: Update *********************************************************/

/* TourPflege::Update *********************************************************/

retClient Tourpflege_Update(tourpflegeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Tourpflege_Update";
    exec sql begin declare section;
    tourpflegeS *d;
    exec sql end declare section;

    d = a;

    d->TM_DATE = ppGGetDate();
d->TM_TIME = ppGGetTime();
strcpy(d->CHANGEID, "U");
    ppGStripLast(d->BEMERKUNGEN);
    if ( *d->BEMERKUNGEN == '\0' )
        strcpy( d->BEMERKUNGEN, " " );


    exec sql declare CUpdate64 cursor with hold for
              select tm_date,
                     tm_time,
                     loginId,
                     changeId,
                     koart
               from tourplantag
              where tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    tourplantag.KundenNr	 =	:d->KUNDENNR	 and
                    tourplantag.tourid	 =	:d->TOURID
              for update;
    exec sql open CUpdate64;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate64" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate64;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate64" ) ) != IS_OK )
            break;
        exec sql update tourplantag set tm_date = :d->TM_DATE,
                     tm_time = :d->TM_TIME,
                     loginId = :d->LOGINID,
                     changeId = :d->CHANGEID,
                     koart = :d->KOART where current of CUpdate64;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate64" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 3 ) == 0 )
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



/* TourPflege: Select *********************************************************/



/* TourPflege: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : delayedcst.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:22 2022                                         */
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
#include "customer.h"

/* delayedcst: Select *********************************************************/

/* delayedcst::SelDay *********************************************************/

retClient delayedcst_SelDay(delayedcstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayedcst_SelDay";
    exec sql begin declare section;
    delayedcstS *d;
    exec sql end declare section;

    d = a;

    {
    char msg[256] = { 0 };
    d->WEEKDAY = AllgGetWeekDay(AllgGetDate(), msg);
}
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select delayeddeliverycst.BranchNo,
                     delayeddeliverycst.CustomerNo,
                     delayeddeliverycst.weekday,
                     delayeddeliverycst.time,
                     delayeddeliverycst.tourid,
                     delayeddeliverycst.activ,
                     delayeddeliverycst.delayedweekday,
                     delayeddeliverycst.narcotic,
                     delayeddeliverycst.coldchain,
                     delayeddeliverycst.cool08,
                     delayeddeliverycst.cool20
                into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->TOURID,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20
                from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	:d->CUSTOMERNO	 and
                    delayeddeliverycst.weekday	 =	:d->WEEKDAY and
                    delayeddeliverycst.activ	 =	'1';
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* delayedcst::SelList ********************************************************/

retClient delayedcst_SelList(delayedcstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayedcst_SelList";
    exec sql begin declare section;
    delayedcstS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList66 cursor with hold for
                  select delayeddeliverycst.BranchNo,
                     delayeddeliverycst.CustomerNo,
                     delayeddeliverycst.weekday,
                     delayeddeliverycst.time,
                     delayeddeliverycst.tourid,
                     delayeddeliverycst.activ,
                     delayeddeliverycst.delayedweekday,
                     delayeddeliverycst.narcotic,
                     delayeddeliverycst.coldchain,
                     delayeddeliverycst.cool08,
                     delayeddeliverycst.cool20
                from delayeddeliverycst
                  where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                        delayeddeliverycst.CustomerNo	 =	:d->CUSTOMERNO;
        exec sql open CSelList66;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList66" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList66;
        return CheckSql( fun, stError, "%s", "close CSelList66" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList66 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->TOURID,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList66" )) == IS_ERROR )
        return rc;
    return rc;
}



/* delayedcst: Insert *********************************************************/

/* delayedcst::Insert *********************************************************/

retClient delayedcst_Insert(delayedcstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayedcst_Insert";
    exec sql begin declare section;
    delayedcstS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
        exec sql select kdgruppe from kunde
      where Vertriebszentrumnr     = :d->BRANCHNO      and
                 Kundennr                  = :d->CUSTOMERNO and
                 Kdgruppe                  in ("13","18");
    if ( ( rc=CheckSql( fun, stError, "%s", "Select KdGruppe" ) ) == IS_ERROR )
        return rc;
    else if ( ( rc=CheckSql( fun, stError, "%s", "Select KdGruppe" ) ) != IS_NOTFOUND )
    {
        sprintf( stError->spError, "Not Allowed" );
        if ( bIsTrans )
       {
           if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
        }
        return -5;
    }
    exec sql insert into delayeddeliverycst (BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     tourid,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->TOURID,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert delayeddeliverycst" ) ) != IS_OK )
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



/* delayedcst: Update *********************************************************/

/* delayedcst::Update *********************************************************/

retClient delayedcst_Update(delayedcstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayedcst_Update";
    exec sql begin declare section;
    delayedcstS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate67 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     tourid,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20
               from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	:d->CUSTOMERNO	 and
                    delayeddeliverycst.weekday	 =	:d->WEEKDAY
              for update;
    exec sql open CUpdate67;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate67" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate67;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate67" ) ) != IS_OK )
            break;
        exec sql update delayeddeliverycst set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     weekday = :d->WEEKDAY,
                     time = :d->TIME,
                     tourid = :d->TOURID,
                     activ = :d->ACTIV,
                     delayedweekday = :d->DELAYEDWEEKDAY,
                     narcotic = :d->NARCOTIC,
                     coldchain = :d->COLDCHAIN,
                     cool08 = :d->COOL08,
                     cool20 = :d->COOL20 where current of CUpdate67;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate67" ) ) != IS_OK )
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



/* delayedcst: Select *********************************************************/

/* delayedcst::Delete *********************************************************/

retClient delayedcst_Delete(delayedcstS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayedcst_Delete";
    exec sql begin declare section;
    delayedcstS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete68 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     tourid,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20
               from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	:d->CUSTOMERNO	 and
                    delayeddeliverycst.weekday	 =	:d->WEEKDAY
              for update;
    exec sql open CDelete68;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete68" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete68;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete68" ) ) != IS_OK )
            break;
        exec sql delete from delayeddeliverycst where current of CDelete68;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete68" ) ) != IS_OK )
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



/* delayedcst: Other **********************************************************/

/* delayedcst::DeleteAll ******************************************************/

retClient delayedcst_DeleteAll(delayedcstS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "delayedcst_DeleteAll";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
delayedcstS *d;
exec sql end declare section;

d = a;
exec sql declare CDelDDCst0 cursor with hold for
  select activ
  from delayeddeliverycst
  where
  branchno = :d->BRANCHNO
  and weekday = :d->WEEKDAY
  for update;
  
exec sql open CDelDDCst0;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
for(;;)
{
  exec sql fetch CDelDDCst0;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelDDCst0;" ) ) != IS_OK )
    break;
  exec sql delete delayeddeliverycst
  where current of CDelDDCst0;
  if ( ( rc=CheckSql( fun, stError,  "%s", "delete delayeddeliverycst;" ) ) != IS_OK )
  {
    break;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* delayedcst::InsertAll ******************************************************/

retClient delayedcst_InsertAll(delayedcstS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "delayedcst_InsertAll";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
delayedcstS *d;
char tag[3];
int ddday;
char acttag[3];
char zeittour[7];
char tourzeit[7];
exec sql end declare section;

d = a;
exec sql declare CSelDDCst0 cursor with hold for
  select kundennr
  from kunde
  where
  vertriebszentrumnr = :d->BRANCHNO and
  kdgruppe not in ("09","13","18");

if(d->WEEKDAY==0) {strcpy(tag,"MO");strcpy(acttag,"SO");ddday=1;}
else if(d->WEEKDAY==1) {strcpy(tag,"DI");strcpy(acttag,"MO");ddday=2;}
else if(d->WEEKDAY==2) {strcpy(tag,"MI");strcpy(acttag,"DI");ddday=3;}
else if(d->WEEKDAY==3) {strcpy(tag,"DO");strcpy(acttag,"MI");ddday=4;}
else if(d->WEEKDAY==4) {strcpy(tag,"FR");strcpy(acttag,"DO");ddday=5;}
else if(d->WEEKDAY==5) {strcpy(tag,"SA");strcpy(acttag,"FR");ddday=6;}
else if(d->WEEKDAY==6) {strcpy(tag,"MO");strcpy(acttag,"SA");ddday=1;}

sprintf(zeittour,"%06d",((d->TIME+1)*100));

exec sql declare CSelDDCst01 cursor for
  select t.tourid
  from tourplantagwoche t,tourplanwoche w
  where
  t.vertriebszentrumnr = :d->BRANCHNO
  and t.kundennr = :d->CUSTOMERNO
  and w.weekday = :ddday
  and w.weekday = t.weekday
  and w.filialnr = t.vertriebszentrumnr
  and w.tourid = t.tourid
  order by t.tourid;

exec sql declare CSelDDCst02 cursor for
  select t.tourid
  from tourplantagwoche t,tourplanwoche w
  where
  t.vertriebszentrumnr = :d->BRANCHNO
  and t.kundennr = :d->CUSTOMERNO
  and w.weekday = :d->WEEKDAY
  and w.weekday = t.weekday
  and w.filialnr = t.vertriebszentrumnr
  and w.tourid = t.tourid
  and w.tourid < :zeittour
  order by t.tourid desc;
  
exec sql open CSelDDCst0;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
for(;;)
{
  exec sql fetch CSelDDCst0 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelDDCst0;" ) ) != IS_OK )
    break;
  exec sql open CSelDDCst01;
  exec sql fetch CSelDDCst01 into :d->TOURID;
  if (sqlca.sqlcode == SQLNOTFOUND) strcpy(d->TOURID,"000000");
  else if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelDDCst01;" ) ) != IS_OK )
    break;
  exec sql open CSelDDCst02;
  exec sql fetch CSelDDCst02 into :tourzeit;
  if (sqlca.sqlcode == SQLNOTFOUND) strcpy(tourzeit,zeittour);
  else if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelDDCst01;" ) ) != IS_OK )
    break;
  d->TIME = atoi(tourzeit)-1;
  d->TIME = d->TIME/100;
  exec sql insert into delayeddeliverycst(
    BranchNo,
    CustomerNo,
    WeekDay,
    Time,
    TourId,
    Activ,
    delayedweekday,
    narcotic,
    coldchain,
    cool08,
    cool20)
  values(
    :d->BRANCHNO,
    :d->CUSTOMERNO,
    :d->WEEKDAY,
    :d->TIME,
    :d->TOURID,
    '1',
    :ddday,
    :d->NARCOTIC,
    :d->COLDCHAIN,
    :d->COOL08,
    :d->COOL20);
  if ( ( rc=CheckSql( fun, stError,  "%s", "into delayeddeliverycst;" ) ) != IS_OK )
  {
    if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
      break;
    else
      continue;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* delayedcst::SelectActTouren ************************************************/

retClient delayedcst_SelectActTouren(delayedcstS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "delayedcst_SelectActTouren";
exec sql begin declare section;
delayedcstS *d;
char tag[3];
exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
  if(d->WEEKDAY==0) strcpy(tag,"SO");
  else if(d->WEEKDAY==1) strcpy(tag,"MO");
  else if(d->WEEKDAY==2) strcpy(tag,"DI");
  else if(d->WEEKDAY==3) strcpy(tag,"MI");
  else if(d->WEEKDAY==4) strcpy(tag,"DO");
  else if(d->WEEKDAY==5) strcpy(tag,"FR");
  else if(d->WEEKDAY==6) strcpy(tag,"SA");

  exec sql declare CSelDDTour1 cursor for
    select t.tourid
    from tourplantagwoche t,tourplanwoche w
    where
    t.vertriebszentrumnr = :d->BRANCHNO
    and t.kundennr = :d->CUSTOMERNO
    and w.weekday = :d->WEEKDAY
    and w.weekday = t.weekday
    and w.filialnr = t.vertriebszentrumnr
    and w.tourid = t.tourid
    order by t.tourid;

  exec sql open CSelDDTour1;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CSelDDTour1" ) ) != IS_OK )
      return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
  exec sql close CSelDDTour1;
  return CheckSql( fun, stError, "%s", "close CSelDDTour1" );
}

exec sql fetch CSelDDTour1 into
  :d->TOURID;
if ((rc=CheckSql( fun, stError, "%s", "fetch CSelDDTour1" )) == IS_ERROR )
  return rc;
return rc;
}

/* delayedcst::SelectTouren ***************************************************/

retClient delayedcst_SelectTouren(delayedcstS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "delayedcst_SelectTouren";
exec sql begin declare section;
delayedcstS *d;
char tag[3];
exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
  if(d->WEEKDAY==0) strcpy(tag,"MO");
  else if(d->WEEKDAY==1) strcpy(tag,"DI");
  else if(d->WEEKDAY==2) strcpy(tag,"MI");
  else if(d->WEEKDAY==3) strcpy(tag,"DO");
  else if(d->WEEKDAY==4) strcpy(tag,"FR");
  else if(d->WEEKDAY==5) strcpy(tag,"SA");
  else if(d->WEEKDAY==6) strcpy(tag,"MO");

  exec sql declare CSelDDTour0 cursor for
    select t.tourid
    from tourplantagowche t,tourplanwoche w
    where
    t.vertriebszentrumnr = :d->BRANCHNO
    and t.kundennr = :d->CUSTOMERNO
    and w.weekday = :d->WEEKDAY
    and w.weekday = t.weekday
    and w.filialnr = t.vertriebszentrumnr
    and w.tourid = t.tourid
    order by t.tourid;

  exec sql open CSelDDTour0;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CSelDDTour0" ) ) != IS_OK )
      return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
  exec sql close CSelDDTour0;
  return CheckSql( fun, stError, "%s", "close CSelDDTour0" );
}

exec sql fetch CSelDDTour0 into
  :d->TOURID;
if ((rc=CheckSql( fun, stError, "%s", "fetch CSelDDTour0" )) == IS_ERROR )
  return rc;
return rc;
}

/* delayedcst::SetActiv *******************************************************/

retClient delayedcst_SetActiv(delayedcstS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "delayedcst_SetActiv";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
delayedcstS *d;
exec sql end declare section;

d = a;
exec sql declare CSelDDCstAct0 cursor with hold for
  select activ
  from delayeddeliverycst
  where
  branchno = :d->BRANCHNO
  and weekday = :d->WEEKDAY
  for update;
  
exec sql open CSelDDCstAct0;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
for(;;)
{
  exec sql fetch CSelDDCstAct0;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelDDCstAct0;" ) ) != IS_OK )
    break;
  exec sql update delayeddeliverycst
  set activ = :d->ACTIV
  where current of CSelDDCstAct0;
  if ( ( rc=CheckSql( fun, stError,  "%s", "update delayeddeliverycst;" ) ) != IS_OK )
  {
    break;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : delayeddeliverycstspecial.cxx                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:57:27 2022                                         */
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
#include "customer.h"

/* delayeddeliverycstspecial: Select ******************************************/

/* delayeddeliverycstspecial::Sel *********************************************/

retClient delayeddeliverycstspecial_Sel(delayeddeliverycstspecialS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayeddeliverycstspecial_Sel";
    exec sql begin declare section;
    delayeddeliverycstspecialS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel69 cursor with hold for
                  select delayeddeliverycst.BranchNo,
                     delayeddeliverycst.CustomerNo,
                     delayeddeliverycst.weekday,
                     delayeddeliverycst.time,
                     delayeddeliverycst.activ,
                     delayeddeliverycst.delayedweekday,
                     delayeddeliverycst.narcotic,
                     delayeddeliverycst.coldchain,
                     delayeddeliverycst.cool08,
                     delayeddeliverycst.cool20,
                     delayeddeliverycst.DateFrom,
                     delayeddeliverycst.DateTo
                from delayeddeliverycst
                  where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                        delayeddeliverycst.CustomerNo	 =	0
                        order by delayeddeliverycst.DateFrom;
        exec sql open CSel69;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel69" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel69;
        return CheckSql( fun, stError, "%s", "close CSel69" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel69 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20,
                     :d->DATEFROM,
                     :d->DATETO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel69" )) == IS_ERROR )
        return rc;
    return rc;
}

/* delayeddeliverycstspecial::SelUni ******************************************/

retClient delayeddeliverycstspecial_SelUni(delayeddeliverycstspecialS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayeddeliverycstspecial_SelUni";
    exec sql begin declare section;
    delayeddeliverycstspecialS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select delayeddeliverycst.BranchNo,
                     delayeddeliverycst.CustomerNo,
                     delayeddeliverycst.weekday,
                     delayeddeliverycst.time,
                     delayeddeliverycst.activ,
                     delayeddeliverycst.delayedweekday,
                     delayeddeliverycst.narcotic,
                     delayeddeliverycst.coldchain,
                     delayeddeliverycst.cool08,
                     delayeddeliverycst.cool20,
                     delayeddeliverycst.DateFrom,
                     delayeddeliverycst.DateTo
                into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20,
                     :d->DATEFROM,
                     :d->DATETO
                from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	0	 and
                    delayeddeliverycst.DateFrom	=	:lDate;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* delayeddeliverycstspecial: Insert ******************************************/

/* delayeddeliverycstspecial::Insert ******************************************/

retClient delayeddeliverycstspecial_Insert(delayeddeliverycstspecialS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayeddeliverycstspecial_Insert";
    exec sql begin declare section;
    delayeddeliverycstspecialS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into delayeddeliverycst (BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     DateFrom,
                     DateTo)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->WEEKDAY,
                     :d->TIME,
                     :d->ACTIV,
                     :d->DELAYEDWEEKDAY,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20,
                     :d->DATEFROM,
                     :d->DATETO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert delayeddeliverycst" ) ) != IS_OK )
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



/* delayeddeliverycstspecial: Update ******************************************/

/* delayeddeliverycstspecial::Update ******************************************/

retClient delayeddeliverycstspecial_Update(delayeddeliverycstspecialS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayeddeliverycstspecial_Update";
    exec sql begin declare section;
    delayeddeliverycstspecialS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate71 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     DateFrom,
                     DateTo
               from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	0	 and
                    delayeddeliverycst.weekday	 =	:d->WEEKDAY and
                    delayeddeliverycst.DateFrom	 =	:d->DATEFROM
              for update;
    exec sql open CUpdate71;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate71" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate71;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate71" ) ) != IS_OK )
            break;
        exec sql update delayeddeliverycst set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     weekday = :d->WEEKDAY,
                     time = :d->TIME,
                     activ = :d->ACTIV,
                     delayedweekday = :d->DELAYEDWEEKDAY,
                     narcotic = :d->NARCOTIC,
                     coldchain = :d->COLDCHAIN,
                     cool08 = :d->COOL08,
                     cool20 = :d->COOL20,
                     DateFrom = :d->DATEFROM,
                     DateTo = :d->DATETO where current of CUpdate71;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate71" ) ) != IS_OK )
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



/* delayeddeliverycstspecial: Select ******************************************/

/* delayeddeliverycstspecial::Delete ******************************************/

retClient delayeddeliverycstspecial_Delete(delayeddeliverycstspecialS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayeddeliverycstspecial_Delete";
    exec sql begin declare section;
    delayeddeliverycstspecialS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete72 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     weekday,
                     time,
                     activ,
                     delayedweekday,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     DateFrom,
                     DateTo
               from delayeddeliverycst
              where delayeddeliverycst.BranchNo	 =	:d->BRANCHNO	 and
                    delayeddeliverycst.CustomerNo	 =	0 and
                    delayeddeliverycst.weekday	 =	:d->WEEKDAY and
                    delayeddeliverycst.DateFrom	 =	:d->DATEFROM
              for update;
    exec sql open CDelete72;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete72" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete72;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete72" ) ) != IS_OK )
            break;
        exec sql delete from delayeddeliverycst where current of CDelete72;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete72" ) ) != IS_OK )
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



/* delayeddeliverycstspecial: Other *******************************************/



