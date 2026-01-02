#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxsubordertype.hpp"
#include "pxcstot.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcalcdiscount.hpp"
#include "pxdiscount.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxcstbas.hpp"
#include "pxarticlegroup.hpp"
#include "pxstockbooking.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  Construct a discount-in-kind list related to a customer's assiocated      */
/*  terms of condition groups, an article and a given order quantity.         */
/*  For each term group associated to the customer, the list will contain     */
/*  one instance of a class pxCalcDiscount object.                            */
/*----------------------------------------------------------------------------*/
pxCalcDiscountList :: pxCalcDiscountList
(
    pxCustBase& customer,
    pxArtBase&  article,
    pxOrderItem* item,
    long        QOrdered,
    pxCustPharmGroupList* Phglist
)
{
    init(customer, QOrdered);
    short vz = customer.Vertriebszentrum();
    short discounttype = 0;            // discounttype

    pxDiscountList   *dlist   = new pxDiscountList(Session());
    nDate            today;

    // Init OrderType
    item->Order().OrderType();

    pxDiscountOrdTypList* dotl = Session()->DiscountOrderTypList();
    if(dotl)
    {
        discounttype = dotl->Find(item->Order().KdAuftragArt());
    }
/*----------------------------------------------------------------------------*/
/*  In this part we try to find entries within the table discount depend on   */
/*  OrderType and SubOrderType. This is a special feature and the difference  */
/*  between this feature and the normal discountcalculation is, we must find  */
/*  entries within the table discount, otherwise we return an error and       */
/*  booking for this product is rejected.                                     */
/*  Usage  per example for the french application Short and Generika lists    */
/*----------------------------------------------------------------------------*/
    if ( customer.SubOrderType() )
    {
        if (discounttype == 0)
        {
            ExternalError(CMsgStream(), CMSG_ITM_NO_DISCOUNT_ENTRY, article.ArtikelNr());
        }
        else
        {
            dlist->Select(vz, article.ArtikelNr(), discounttype, customer.SubOrderType()->PharmacyGroupId());
            if (dlist->Entries() == 0)
            {
                if (Session()->getStockBooking()->GetAvailableQtyInStock(article) > 0 )
                {
                    item->SetKeinBestandsDefekt();
                }
                ExternalError(CMsgStream(), CMSG_ITM_NO_DISCOUNT_ENTRY, article.ArtikelNr());
            }
        }
    }
    else if ( Session()->isSwitzerland() )
    {
#ifdef CHDISCLOG
		std::stringstream v;
#endif
        // Prio 1 rebates on customer level
        //dlist->Select(vz, article.ArtikelNr(), customer.IDFNr());
        //dlist->ReduceToValidOffers(QOrdered);
        dlist->Select(CASCADE_JUST_JOIN_PHARMACYGROUP_1, vz, article.ArtikelNr(), customer.IDFNr());
       /* if ( !dlist->Entries() )
        {
           // Prio 2  rebate on pharmacygroup level
           dlist->Select(CASCADE_JUST_JOIN_PHARMACYGROUP, vz, article.ArtikelNr(), customer.IDFNr());
        }
      */
        if ( !dlist->Entries() )
        {
           // Prio 3 rebates on common level(pharmacygroupid = "000")
           dlist->Select(CASCADE_JUST_PHARMACYGROUP_ZERO, vz, article.ArtikelNr(), 0L);


#ifdef CHDISCLOG
			if ( !dlist->Entries() )
			{
				v << "No entries in Discount-List from cursor C25 or C26!";
			}
			else
        	{
           		v << "Entries found in Discount-List from cursor C25:";
			}
#endif
        }
#ifdef CHDISCLOG
        else
        {
          		v << "Entries found in Discount-List from cursor C26:";
        }

        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
#endif
    }
    else
    {
        dlist->Select(vz, article.ArtikelNr(), customer.IDFNr());
        if ( !dlist->Entries() )
        {
            dlist->Select(vz, article.ArtikelNr());
        }
    }

#ifdef CHDISCLOG
    pxDiscount *curp;
    pxDiscountListIter cursor(*dlist);

	int i = 1;

    while ( (curp = (pxDiscount*) ++cursor) != NULL )
    {
		std::stringstream v;
        v << "pxCalcDiscountList::pxCalcDiscountList() Discount-No. " << i++;
		v << ": BranchNo = " << curp->BranchNo();
		v << ", ArticleNo = " << curp->ArticleNo();
		v << ", BaseQty = " << curp->BaseQty();
        v << ", DiscountType = " << curp->DiscountType();
        v << ", DiscountSpec = " << curp->DiscountSpec();
        v << ", DiscountGroupNo = " << curp->DiscountGrpNo();
        v << ", DiscountValuePct = " << curp->DiscountValuePct();
		v << ", DiscountQty = " << curp->DiscountQty();
		v << ", DiscountQtyPct = " << curp->DiscountQtyPct();
		v << ", BaseValue = " << curp->BaseValue();
		v << ", MaxQty = " << curp->MaxQty();
        v << ", SurchargePct = " << curp->SurchargePct();
        v << ", RefundPct = " << curp->RefundPct();
    	BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
    }
#endif

    if (dlist->Entries())
    {                                    // then discount-in-kind table entries
                                         // are there for this article
#ifdef CHDISCLOG
        std::stringstream u;
        u << "execute Shrink and CheckList:";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), u.str());
#endif
        dlist->Shrink(Phglist);          // shrink this list
        dlist->CheckList(item);          // check contents of this list

#ifdef CHDISCLOG
    	pxDiscountListIter cursor2(*dlist);

		i = 1;

		std::stringstream w;
		w << "Shrink and CheckList done:";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), w.str());

    	while ( (curp = (pxDiscount*) ++cursor2) != NULL )
    	{
    		std::stringstream v;
            v << "pxCalcDiscountList::pxCalcDiscountList() Discount-No. " << i++;
            v << ": BranchNo = " << curp->BranchNo();
            v << ", ArticleNo = " << curp->ArticleNo();
            v << ", BaseQty = " << curp->BaseQty();
            v << ", DiscountType = " << curp->DiscountType();
            v << ", DiscountSpec = " << curp->DiscountSpec();
            v << ", DiscountGroupNo = " << curp->DiscountGrpNo();
            v << ", DiscountValuePct = " << curp->DiscountValuePct();
            v << ", DiscountQty = " << curp->DiscountQty();
            v << ", DiscountQtyPct = " << curp->DiscountQtyPct();
            v << ", BaseValue = " << curp->BaseValue();
            v << ", MaxQty = " << curp->MaxQty();
            v << ", SurchargePct = " << curp->SurchargePct();
            v << ", RefundPct = " << curp->RefundPct();
            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
    	}
#endif

        CalcDiscount(customer, dlist, QOrdered, (short)-1); // calc discount-in-kind
        NrIntern_ = dlist->CheckNrIntern();
        if ( dlist->checkHigherConditions(item, QOrdered))
        {
            item->SetHigherConditionsAvailable();
        }      
    }

    dlist->Clear();                      // the article-related discount table
    delete dlist;                        // entries are no longer needed
}

/*----------------------------------------------------------------------------*/
/*  Construct a discount-in-kind list using an already created list of        */
/*  discount table entries related to an article.                             */
/*----------------------------------------------------------------------------*/
pxCalcDiscountList :: pxCalcDiscountList
(
    pxCustBase& customer,
    pxDiscountList *dlist,
    long        QOrdered
)
{
    init(customer, QOrdered);
    CalcDiscount(customer, dlist, QOrdered, (short)-1);
}

/*----------------------------------------------------------------------------*/
/*  Construct a discount-in-kind list using an already created list of        */
/*  discount table entries related to an article.                             */
/*----------------------------------------------------------------------------*/
pxCalcDiscountList :: pxCalcDiscountList
(
    pxCustBase&  customer,
    pxArtBase&   article,
    pxOrderItem* item,
    long        QOrdered,
    int         mode,
    bool AddOnPromoDiscount,
    bool AddOnStdDiscount,
    pxCustPharmGroupList* Phglist
)
{
    init(customer, QOrdered);
    short vz = customer.Vertriebszentrum();
    short discounttype = 0;            // discounttype
    CountryMode = mode;
    bool AddOnPromoDiscountOfProductPromo = true;
    bool AddOnStdDiscountOfProductPromo = true;
    bool NotBySalesWeb = true;

    pxDiscountList       *dlist    = new pxDiscountList(Session());
    nDate                today;
    // BG Performance test code
    pxOrder* CurrentOrder = Session()->CurrentOrder();
    pxDiscountList       *OrderPosDiscountList = NULL;

    // Init OrderType
    item->Order().OrderType();

    pxDiscountOrdTypList* dotl = Session()->DiscountOrderTypList();
    bool blnFound = false;  // hasn't found a discount up to now

    switch(mode)
    {
    case MODE_BULGARIA:
        // Cascading Bulgaria:
                    // 0. cascade: promotions auf Positionsebene (Achtung, wenn mit Ansammeln, dann KEIN STOP nach dieser Kaskade!)
        // 1. cascade: article (discount.articleno)
        // 2. cascade: manufacturer (discount.manufacturerno)
        // 3. cascade: RPG (discount.discountgrpno<>0 AND discountgrpmem.articleno AND discountgrp.discountgrptype=1)
                    // 4. cascade: article group (articles by SQL-Statement)
        // 5. cascade: customer (discount.customerno)
        // 6. cascade: customer group (discount.pharmacygroupid) überflüssig (und wenn, dann nur mit Abfrage Artikelno=0!!!)
        //
        // Distinguish between voluntary sale (Freiverkauf) and health fund (Krankenkasse)

        // Set grossprofitpct fro freesale to 0.0:
        item->SetGrossProfitPctFV(0.0);

        // BG Performance test code
        if ( CurrentOrder && !item->IsNotSaveDiscountList() )      // only BG
        {
            OrderPosDiscountList = CurrentOrder->OrderPosDiscountList();
            if ( OrderPosDiscountList )
            {
                if ( OrderPosDiscountList->ArtikelNr() == 0 )
                {
                    OrderPosDiscountList->SetArtikelNr(article.ArtikelNr());
                }
                else
                if (  OrderPosDiscountList->ArtikelNr() != article.ArtikelNr() )
                {
                    CurrentOrder->DeleteOrderPosDiscountList();
                    OrderPosDiscountList = CurrentOrder->OrderPosDiscountList();
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SetArtikelNr(article.ArtikelNr());
                    }
                }
            }
        }

        if( dotl )
        {
            discounttype = dotl->Find(item->Order().KdAuftragArt());
        }

        /*----------------------------------------------------------------------------*/
        /*  In this part we try to find entries within the table discount depend on   */
        /*  OrderType and SubOrderType. This is a special feature and the difference  */
        /*  between this feature and the normal discountcalculation is, we must find  */
        /*  entries within the table discount, otherwise we return an error and       */
        /*  booking for this product is rejected.                                     */
        /*  Usage  per example for the french application Short and Generika lists    */
        /*----------------------------------------------------------------------------*/
        if(customer.SubOrderType())  // Tender hat speziellen Discounttype
        {
            if (discounttype == 0)
            {
                ExternalError(CMsgStream(), CMSG_ITM_NO_DISCOUNT_ENTRY, article.ArtikelNr());
            }
            else
            {
                dlist->Select(vz, article.ArtikelNr(), discounttype, customer.SubOrderType()->PharmacyGroupId());
                if (dlist->Entries() == 0)
                {
                    ExternalError(CMsgStream(), CMSG_ITM_NO_DISCOUNT_ENTRY, article.ArtikelNr());
                }
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)-1);
            }
        }

        //----- 0. cascade: promotions auf Positionsebene (Achtung, wenn mit Ansammeln, dann KEIN STOP nach dieser Kaskade!)
        if(AddOnPromoDiscount)
        {
            if ( OrderPosDiscountList && OrderPosDiscountList->Entries())
            {
                if ( OrderPosDiscountList->FindCasCadeNo( (short)CASCADE_PROMOTION_0 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short)CASCADE_PROMOTION_0 );
                    goto perCASCADE_PROMOTION_0;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_PROMOTION_1 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short)CASCADE_PROMOTION_1 );
                    goto perCASCADE_PROMOTION_1;
                }
                goto perCASCADESTDPROMO;
            }

            if(!dlist->Entries()) // 0. cascade
            {
                // look for promotions (promotion_no>0) and customerno:
                dlist->Select(CASCADE_PROMOTION_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_PROMOTION_0);
                }
perCASCADE_PROMOTION_0:
                ShrinkDiscountListBG(dlist, item, QOrdered, Phglist);

                if(!dlist->Entries())
                {
                    // look for promotions (promotion_no>0):
                    dlist->Select(CASCADE_PROMOTION_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_PROMOTION_1);
                    }
perCASCADE_PROMOTION_1:
                    ShrinkDiscountListBG(dlist, item, QOrdered, Phglist);
                }

                if(dlist->Entries())
                {
                    // Does the first (highest prio) promotion allow further ones?
                    pxDiscount *dikp;               // ptr to list entry
                    pxDiscountListIter cursor(*dlist);  // define an iterator
                    dikp = (pxDiscount*) ++cursor;
                    item->GetAddOnFlags(dikp->PromotionNo(), AddOnPromoDiscountOfProductPromo, AddOnStdDiscountOfProductPromo, NotBySalesWeb);

                    CheckDiscountListBG(1, dlist, customer, item, QOrdered, Phglist, (short)0);
                    dlist->Clear();
                }
            }
        }

perCASCADESTDPROMO:
        if(AddOnStdDiscount && AddOnStdDiscountOfProductPromo)
        {
            if ( OrderPosDiscountList && OrderPosDiscountList->Entries())
            {
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ARTICLE_0 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ARTICLE_0 );
                    goto perCASCADE_ARTICLE_0;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ARTICLE_1 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ARTICLE_1 );
                    goto perCASCADE_ARTICLE_1;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_MANUFACTURER_0 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_MANUFACTURER_0 );
                    goto perCASCADE_MANUFACTURER_0;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_MANUFACTURER_1 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_MANUFACTURER_1 );
                    goto perCASCADE_MANUFACTURER_1;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ART_AND_MAN_0 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ART_AND_MAN_0 );
                    goto perCASCADE_ART_AND_MAN_0;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ART_AND_MAN_1 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ART_AND_MAN_1 );
                    goto perCASCADE_ART_AND_MAN_1;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ARTICLEGROUP_0 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ARTICLEGROUP_0 );
                    goto perCASCADE_ARTICLEGROUP_0;
                }
                else
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_ARTICLEGROUP_1 ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_ARTICLEGROUP_1 );
                    goto perCASCADE_ARTICLEGROUP_1;
                }
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_CUSTOMER ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_CUSTOMER );
                    goto perCASCADE_CUSTOMER;
                }
                if ( OrderPosDiscountList->FindCasCadeNo( (short) CASCADE_PHARMACYGROUP ) )
                {
                    OrderPosDiscountList->ReloadDiscountList(dlist, (short) CASCADE_PHARMACYGROUP );
                    goto perCASCADE_PHARMACYGROUP;
                }
            }

            //----- 1. cascade: article
            if(!dlist->Entries()) // 1. cascade
            {
                // look for article and customer:
                dlist->Select(CASCADE_ARTICLE_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ARTICLE_0);
                }
perCASCADE_ARTICLE_0:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)1);

                if(!dlist->Entries())
                {
                    // look for article (and pharmacygroup):
                    dlist->Select(CASCADE_ARTICLE_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ARTICLE_1);
                    }
perCASCADE_ARTICLE_1:
                    CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)1);
                }
            }

            //----- 2. cascade: manufacturer
            if(!dlist->Entries()) // 2. cascade
            {
                // look for manufacturer and customer:
                dlist->Select(CASCADE_MANUFACTURER_0, vz, 0L, customer.IDFNr(), article.HerstellerNr(), 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_MANUFACTURER_0);
                }
perCASCADE_MANUFACTURER_0:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)2);

                // look for manufacturer (and pharmacygroup):
                if(!dlist->Entries())
                {
                    dlist->Select(CASCADE_MANUFACTURER_1, vz, 0L, customer.IDFNr(), article.HerstellerNr(), 0);  // -> discount.cpp
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_MANUFACTURER_1);
                    }
perCASCADE_MANUFACTURER_1:
                    CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)2);
                }
            }

            //----- 3. cascade: RPG
            if(!dlist->Entries()) // 3. cascade
            {
                // look for article and customer:
                dlist->Select(CASCADE_ART_AND_MAN_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ART_AND_MAN_0);
                }
perCASCADE_ART_AND_MAN_0:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)3);

                // look for article (and pharmacygroup):
                if(!dlist->Entries())
                {
                    dlist->Select(CASCADE_ART_AND_MAN_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ART_AND_MAN_1);
                    }
perCASCADE_ART_AND_MAN_1:
                    CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)3);
                }
            }

            //----- 4. cascade: article group (articles by SQL-Statement)
            if(!dlist->Entries()) // 4. cascade
            {
                // look for article group and customer:
                dlist->Select(CASCADE_ARTICLEGROUP_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ARTICLEGROUP_0);
                }

perCASCADE_ARTICLEGROUP_0:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)4);

                // look for article group (and pharmacygroup):
                if(!dlist->Entries())
                {
                    dlist->Select(CASCADE_ARTICLEGROUP_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                    if ( OrderPosDiscountList )
                    {
                        OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_ARTICLEGROUP_1);
                    }
perCASCADE_ARTICLEGROUP_1:
                    CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)4);
                }
            }

            //----- 5. cascade: customer
            if(!dlist->Entries()) // 5. cascade
            {
                // look for customer:
                dlist->Select(CASCADE_CUSTOMER, vz, 0L, customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_CUSTOMER);
                }
perCASCADE_CUSTOMER:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)5);
            }

            //----- 6. cascade: pharmacygroup
            if(!dlist->Entries()) // 6. cascade
            {
                // look for pharmacygroup and article:
                // Special Bulgarian construct: If there is an article with discount=0, don't take the default discount for the pharmacygroup!!!
                dlist->Select(CASCADE_PHARMACYGROUP, vz, 0L, customer.IDFNr(), 0L, 0);  // -> discount.cpp
                if ( OrderPosDiscountList )
                {
                    OrderPosDiscountList->SaveDiscountList(dlist, (short)CASCADE_PHARMACYGROUP);
                }
perCASCADE_PHARMACYGROUP:
                CheckDiscountListBG(0, dlist, customer, item, QOrdered, Phglist, (short)6);
            }
        }
        break;

    case MODE_SERBIA:
        // Cascading Serbia:
        // 0. cascade: occasions (discount.discountspec==10)
        // 1. cascade: article (discount.articleno)
        // 2. cascade: article group of a single manufacturer (discount.discountgrpno<>0 AND discountgrpmem.articleno AND discountgrp.discountgrptype=1)
        // 3. cascade: manufacturer (discount.manufacturerno)
        // 4. cascade: article group definable by SQL statement (discount.artcategoryno)
        // 5. cascade: article group containing single articles (discount.discountgrpno<>0 AND discountgrpmem.articleno AND discountgrp.discountgrptype=2)

        // don't ask for dlist->Entries() any more, because wrong pharmacygroupids are not filtered out of dlist any more
        // but out of subdlists now!
        blnFound = false;  // hasn't found a discount up to now
        //----- 0. cascade: occasions
        if(!dlist->Entries()) // 0. cascade
        {
            // look for occasions:
            dlist->Select(CASCADE_OCCASIONS, vz, article.ArtikelNr(), 0L, 0L, 0);  // -> discount.cpp
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
        }

        //----- 1. cascade: article
        if(!dlist->Entries()) // 1. cascade
        {
            // look for article and customer:
            dlist->Select(vz,article.ArtikelNr(),customer.IDFNr());
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            if (!blnFound)
            {
                // look for article (and pharmacygroup):
                dlist->Select(vz, article.ArtikelNr());
                blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            }
        }

        //----- 2. cascade: articlegroup of a single manufacturer
        if (!blnFound) // 2. cascade
        {
            // look for article and customer:
            dlist->Select(CASCADE_ART_AND_MAN_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);

            // look for article (and pharmacygroup):
            dlist->Select(CASCADE_ART_AND_MAN_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
        }

        //----- 3. cascade: manufacturer
        if (!blnFound) // 3. cascade
        {
            // look for manufacturer and customer:
            if (!blnFound)
            {
                dlist->Select(CASCADE_MANUFACTURER_0, vz, 0L, customer.IDFNr(), article.HerstellerNr(), 0);  // -> discount.cpp
                blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            }

            // look for manufacturer (and pharmacygroup):
            if (!blnFound)
            {
                dlist->Select(CASCADE_MANUFACTURER_1, vz, 0L, customer.IDFNr(), article.HerstellerNr(), 0);  // -> discount.cpp
                blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            }
        }

        //----- 4. cascade: article group (articles by SQL-Statement)
        if (!blnFound) // 4. cascade
        {
            // look for article group and customer:
            dlist->Select(CASCADE_ARTICLEGROUP_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);

            // look for article group (and pharmacygroup):
            if (!blnFound)
            {
                dlist->Select(CASCADE_ARTICLEGROUP_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
                blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            }
        }

        //----- 5. cascade: article group (single articles)
        if (!blnFound) // 5. cascade
        {
            // look for article group and customer or pharmacygroup:
            dlist->Select(CASCADE_SINGLEART_0, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // -> discount.cpp
            blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);

            // look for article group (and pharmacygroup):
            if (!blnFound)
            {
                dlist->Select(CASCADE_SINGLEART_1, vz, article.ArtikelNr(), customer.IDFNr(), 0L, 0);  // customer.IDFNr() necessary to check pharmacygroupid
                blnFound = SplitAndProcess(customer, item, QOrdered, mode, Phglist, dlist, 6);
            }
        }
        break;

    default:
        break;
    }

    item->SaveArtDiscountInfoList(dlist, this, QOrdered); // save this list for display on GUI;
    dlist->Clear();                      // the article-related discount table
    delete dlist;                        // entries are no longer needed
}

void pxCalcDiscountList::init(pxCustBase& customer, long qOrdered)
{
    session_  = customer.Session();
    QOrdered_ = qOrdered;
    PromotionValuePct_ = 0.0;
    PromotionNatraQty_ = 0;
    QOrderedPromo_ = qOrdered;
    DiscountkeyPromo_ = 0.0;
    DiscounttypePromo_ = (short)0;
    DiscountArticlePromo_ = 0L;
    DiscountBestBuyPromo_ = (short)0;
    PharmacyGroupIdPromo_ = "000";
    RefundValuePromo_ = 0.0;
    RefundPctPromo_ = 0.0;
    Promotion_NoPromo_ = (short)0;
    TurnOverCalcImpactPromo_ = '0';
    InternalDiscountPromo_ = '0';
}

//----------------------------------------------------------------------------
//  Splits dlist into several subdlists for different paymenttargetnos
//  and processes every subdlist.
//  paymenttargetnos 0 - maxptn (including) are considered,
//  so maxptn + 1 subdlists are created and processed.
//  paymenttargetno 0 means: discount is valid for all payment targets.
//  Is used for Serbia only
//----------------------------------------------------------------------------
bool
pxCalcDiscountList :: SplitAndProcess
(
    pxCustBase&            customer,
    pxOrderItem*           item,
    long                   QOrdered,
    int                    mode,
    pxCustPharmGroupList*  Phglist,
    pxDiscountList*        dlist,
    int                    maxptn
)
{
    if (dlist->Entries())
    {
        dlist->Shrink(Phglist);           // shrink this list
    }

    bool blnFound = false;
    if(dlist->Entries())
    {
        for(int ptn=0; ptn<=maxptn; ptn++)
        {
            pxDiscountList *subdlist = new pxDiscountList(Session());
            CreateSubdlist(dlist, subdlist, ptn);
            CheckDiscountList(mode, subdlist, customer, item, QOrdered, Phglist);
            if(this->Entries()) // don't ask for subdlist, because wrong quantity is filtered out only in this (calclist), not in dlist!
            {
                blnFound=true;
            }
            subdlist->Clear();
            delete subdlist;
        }
    }
    return blnFound;
}

//----------------------------------------------------------------------------
//  Shrinks dlist to special paymenttargetno
//  Is used for Serbia only
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: CreateSubdlist
(
    pxDiscountList*        dlist,
    pxDiscountList*        subdlist,
    int                    ptn
)
{
    tDISCOUNT rec;
    pxDiscountListIter iter(*dlist);
    pxDiscount* ditp;
    bool found=false;
    while ( (ditp = (pxDiscount*) ++iter) != NULL )
    {
        if(ptn == ditp->PaymentTargetNo())
        {
            Assign(rec, *ditp);
            subdlist->AddToList(&rec, 0); //2. parameter is not used at all
            found = true;
        }
    }

    // if nothing found:
    if(!found)
    {
        memset(&rec, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
        subdlist->AddToList(&rec, 0); //2. parameter is not used at all
    }
}

//----------------------------------------------------------------------------
//  Creates a Sub-dlist containing only one entry which is defined by index of
//  original dlist.
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: CreateSubdlistByIndex
(
    pxDiscountList* dlist,
    const int index,
    pxDiscountList* subdlist
)
{
    tDISCOUNT rec;
    pxDiscountListIter iter(*dlist);
    pxDiscount* ditp;
    bool found=false;
    for(int i = 0; i <= index; i++)
    {
        ditp = (pxDiscount*) ++iter;
        if(i == index)
        {
            Assign(rec, *ditp);
            subdlist->AddToList(&rec, 0); //2. parameter is not used at all
            found = true;
        }
    }

    // if nothing found:
    if(!found)
    {
        memset(&rec, 0, sizeof(tDISCOUNT));  // zero out entire record buffer
        subdlist->AddToList(&rec, 0); //2. parameter is not used at all
    }
}

//----------------------------------------------------------------------------
//  Shrinks and checks the discount list.
//  Calculates the rebate-in-kind
//  real calculation work is done within the class pxDiscountList object.
//  If a discount quantity > 0 is returned, an object instance of class
//  pxCalcDiscount is constructed and inserted into the list.
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: CheckDiscountList
(
    int                    mode,
    pxDiscountList*        dlist,
    pxCustBase&            customer,
    pxOrderItem*           item,
    long                   QOrdered,
    pxCustPharmGroupList*  Phglist
)
{

    if (dlist->Entries())
    {                

                                          // then there are discount-in-kind table entries for this article
        dlist->Shrink(Phglist);           // shrink this list
        /* not necessary and not welcome, in case that Serbia uses other discountspecs in the future
        if(MODE_SERBIA==mode)
        {
            dlist->ShrinkDiscountSpec();
        }
        */

        dlist->CheckList(item);           // check contents of this list
        CalcDiscount(customer, dlist, QOrdered, (short)-1); // calc discount-in-kind

        // the following code corresponds to DeleteRaises() and is used for Serbia and Bulgaria,
        // which don't have automatical quantity raising (automatische Mengenerhöhung):
        if((MODE_BULGARIA == mode) || (MODE_SERBIA == mode))
        {
            pxCalcDiscount  *curp;
            pxCalcDiscountListIter cursor(*this);
            while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
            {
                if(curp->IsRaised(*this))
                {
                    delete cursor.Remove();
                }
            }
        }

        NrIntern_ = dlist->CheckNrIntern();  //interne Geschichte, die für Bulgarien nicht relevant ist
    }
}

//----------------------------------------------------------------------------
//  Shrinks the discount list for Bulgaria
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: ShrinkDiscountListBG
(
    pxDiscountList* dlist,
    pxOrderItem* item,
    long QOrdered,
    pxCustPharmGroupList* Phglist
)
{
    nDate deldate;
    if (item)
    {
        deldate = item->Order().DatumAuslieferung();
    }
    if (!dlist->Entries())
        return;

    dlist->Shrink(Phglist);           // shrink this list
    dlist->ShrinkPriceType(item, QOrdered);
    dlist->ShrinkPromotions(item);
    dlist->ShrinkCashPayment(item);
//  dlist->ShrinkDateDelivery(&(item->Order()));
}

//----------------------------------------------------------------------------
//  Shrinks and checks the discount list for Bulgaria
//  Calculates the rebate-in-kind
//  real calculation work is done within the class pxDiscountList object.
//  If a discount quantity > 0 is returned, an object instance of class
//  pxCalcDiscount is constructed and inserted into the list.
//
//      mode=0: normaler Durchlauf
//      mode=1: Promotions
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: CheckDiscountListBG
(
    int mode,
    pxDiscountList* dlist,
    pxCustBase& customer,
    pxOrderItem* item,
    long QOrdered,
    pxCustPharmGroupList* Phglist,
    short CascadeLevel
)
{
    pxDiscount *dikp;               // ptr to list entry
    pxDiscountListIter dlistiter(*dlist);  // define an iterator
    short PromotionNo = 0;
    bool bWORKUPINONCE = false;

    if (!dlist->Entries())
        return;

    ShrinkDiscountListBG(dlist, item, QOrdered, Phglist);

    switch(mode)
    {
    case 0:
        dlist->CheckList(item);           // check contents of this list
        CalcDiscount(customer, dlist, QOrdered, CascadeLevel); // calc discount-in-kind
        break;

    case 1:
        // STOPSTOP Before build up a sublist for each entry within dlist, check the list.
        // maybe the list contains more then one entry with the same promotionno(Staffelung bei Natramengen)
        // In this case, the list must workup in once
        while ( (dikp = (pxDiscount*) ++dlistiter) != NULL )
        {
            if ( dikp->PromotionNo() > 0 )
            {
                if ( PromotionNo == 0 )
                {
                    PromotionNo = dikp->PromotionNo();
                }
                else
                if ( PromotionNo == dikp->PromotionNo() )
                {
                    bWORKUPINONCE = true;
                }
                else
                {
                    bWORKUPINONCE = false;
                    break;
                }
            }
        }

        if ( bWORKUPINONCE )
        {
            dlist->CheckList(item);           // check contents of this list
            CalcDiscount(customer, dlist, QOrdered, CascadeLevel); // calc discount-in-kind
            break;
        }

        for(unsigned int i = 0; i < (dlist->Entries()); i++)
        {
            pxDiscountList *subdlist = new pxDiscountList(Session());
            CreateSubdlistByIndex(dlist, i, subdlist);
            subdlist->CheckList(item);           // check contents of this list
            CalcDiscount(customer, subdlist, QOrdered, CascadeLevel); // calc discount-in-kind
        }
        break;
    }

    // the following code corresponds to DeleteRaises() and is used for Serbia and Bulgaria,
    // which don't have automatical quantity raising (automatische Mengenerhöhung):
    pxCalcDiscount  *curp;
    pxCalcDiscountListIter cursor(*this);
    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if(curp->IsRaised(*this))
            delete cursor.Remove();
    }

    NrIntern_ = dlist->CheckNrIntern();  //interne Geschichte, die für Bulgarien nicht relevant ist
}

//----------------------------------------------------------------------------
//  For Serbia only.
//  Steps through dlist and looks for discountvaluepct=0.0.
//  If found any puts entry into calclist.
//----------------------------------------------------------------------------
void
pxCalcDiscountList :: InsertZeroDiscount
(
    pxDiscountList *dlist,
    long       QOrdered
)
{
    short      Discounttype;           // Type of Discount
    long       Quantity;

    if(CountryMode != MODE_SERBIA)
        return;

    Quantity = QOrdered;
    Discounttype = DiscType_Default;

    pxDiscountListIter iter(*dlist);
    pxDiscount* ditp;
    while ( (ditp = (pxDiscount*) ++iter) != NULL )
    {
        if ((0.0 == ditp->DiscountValuePct()) && (ditp->PaymentTargetNo() > 0))
            InsertAscending(new pxCalcDiscount(Discounttype, Quantity, 0.0, 0.0, 0.0, BestBuy_ValuePctCash,
                ditp->PharmacyGroupId(), ditp->PaymentTargetNo(), (nMoney)0, (short)0, (char)'0', (short)-1, (char)'0', 0L, 0.0, 0L, 0, 1));
    }
}

/*----------------------------------------------------------------------------*/
/*  For each term group associated to the customer, the discount-in-kind      */
/*  quantity is calculated based upon the order quantity. However, the        */
/*  real calculation work is done within the class pxDiscountList object.     */
/*  If a discount quantity > 0 is returned, an object instance of class       */
/*  pxCalcDiscount is constructed and inserted into the list.                 */
/*----------------------------------------------------------------------------*/
void
pxCalcDiscountList :: CalcDiscount
(
    pxCustBase& /*customer*/,
    pxDiscountList *dlist,
    long       QOrdered,
    short CascadeLevel

)
{
    short      Discounttype;           // Type of Discount
    double     Discountkey;            // Refund percentage
    long       Quantity;
    nMoney     PreisEKApoNetto;
    double     DiscountValuePct;
    short      DiscountBestBuy;
    double     GrossProfitPct;
    short*     ArrayKindOffRebate = dlist->ArrayKindOffRebate(); // Array of discounttypes within dlist
    int        ArrayIndex = 0;                                   // Index for this Array
    nMoney     RefundValue = pxConstants::mZero;
    short      Promotion_No=(short)0;
    char       TurnOverCalcImpact='0';
    char       InternalDiscount='0';
    long       PromoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

#ifdef CHDISCLOG
	std::stringstream u;
	u << "execute ReduceToValidOffers:";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), u.str());
#endif

    if ( dlist->ReduceToValidOffers(QOrdered) ) // delete expired offers
    {
#ifdef CHDISCLOG
    	pxDiscount  *curp;
    	pxDiscountListIter cursor(*dlist);
		int i = 1;

		std::stringstream w;
		w << "ReduceToValidOffers done:";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), w.str());

    	while ( (curp = (pxDiscount*) ++cursor) != NULL )
    	{
    		std::stringstream v;
            v << "pxCalcDiscountList::CalcDiscount() Discount-No. " << i++;
            v << ": BranchNo = " << curp->BranchNo();
            v << ", ArticleNo = " << curp->ArticleNo();
            v << ", BaseQty = " << curp->BaseQty();
            v << ", DiscountType = " << curp->DiscountType();
            v << ", DiscountSpec = " << curp->DiscountSpec();
            v << ", DiscountGroupNo = " << curp->DiscountGrpNo();
            v << ", DiscountValuePct = " << curp->DiscountValuePct();
            v << ", DiscountQty = " << curp->DiscountQty();
            v << ", DiscountQtyPct = " << curp->DiscountQtyPct();
            v << ", BaseValue = " << curp->BaseValue();
            v << ", MaxQty = " << curp->MaxQty();
            v << ", SurchargePct = " << curp->SurchargePct();
            v << ", RefundPct = " << curp->RefundPct();
            BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), v.str());
    	}
#endif
        for (ArrayIndex = 0; ArrayKindOffRebate[ArrayIndex] > 0 ; ++ArrayIndex)
        {
            RefundValue = pxConstants::mZero;
            Promotion_No = (short)0;
            TurnOverCalcImpact ='0';
            Quantity = QOrdered;

            switch (ArrayKindOffRebate[ArrayIndex])
            {
            case NatraDefault:
                calcDiscountNatra(DiscType_Default, dlist, CascadeLevel);
                break;
            case NatraTeam:
                calcDiscountNatra(DiscType_Team, dlist, CascadeLevel);
                break;
            case NatraDiabetes:
                calcDiscountNatra(DiscType_Diabetes, dlist, CascadeLevel);
                break;
            case FixedPriceDefault:
                calcDiscountNetto(DiscType_Default, dlist, CascadeLevel);
                break;
            case FixedPricePharmGroup:
                calcDiscountNetto(BestBuy_FixedPricePharmGroup, dlist, CascadeLevel);
                break;
            case FixedPriceTeam:
                calcDiscountNetto(DiscType_Team, dlist, CascadeLevel);
                break;
            case FixedPriceDiabetes:
                calcDiscountNetto(DiscType_Diabetes, dlist, CascadeLevel);
                break;
            case ValuePctCash: // Barrabat
                calcDiscountCashWithGrossProfitPctZero(DiscType_Default, dlist, CascadeLevel);
                break;
            case ValuePctShort: // Barrabat Short
                calcDiscountCash(DiscType_Shortrabatt, dlist, CascadeLevel);
                break;
            case ValuePctShortLine: // Barrabat Short Line
                calcDiscountCash(BestBuy_ValuePctShortLine, dlist, CascadeLevel);
                break;
            case FixedDiscountValue:
                calcDiscountFixedValue(FixedDiscountValue, dlist, CascadeLevel);
                break;
            case ValuePctGenerika: // Barrabat Generika
                calcDiscountCash(DiscType_Generika, dlist, CascadeLevel);
                break;
            case ValuePctPartenariat: // Barrabat Partenariat
                calcDiscountCash(DiscType_Partenariat, dlist, CascadeLevel);
                break;
            case ValuePctWholeSale: // Barrabat Wholesale
                calcDiscountCash(BestBuy_ValuePctWholeSale, dlist, CascadeLevel);
                break;
            case ValuePctWholeSaleInd: // Barrabat Wholesale Industrie
                calcDiscountCash(BestBuy_ValuePctWholeSaleInd, dlist, CascadeLevel);
                break;
            case ValuePctRetail: // Barrabat Retail
                calcDiscountCash(BestBuy_ValuePctRetail, dlist, CascadeLevel);
                break;
            case ValuePctTena: // Barrabat Tena
                calcDiscountCash(BestBuy_ValuePctTena, dlist, CascadeLevel);
                break;
            case SpecialPriceHR:
                calcDiscountNetto(BestBuy_SpecialPrice, dlist, CascadeLevel);
                break;
            case LogisticAddition:
                Discounttype = BestBuy_LogisticAddition ;
                DiscountValuePct = dlist->CalcDiscountCash(&Quantity, Discounttype, &Discountkey, &DiscountBestBuy, &RefundValue,
                    &Promotion_No, &TurnOverCalcImpact, &InternalDiscount, &PromoBaseQty, &RefundPct, &CustomerNo, &DiscountCalcFrom, 
                    &DiscountApplyTo);

                // then: discount quantity there
                //if ( (DiscountValuePct > 0.0) || (Discountkey > 0.0 ) )
                //{
                InsertAscending(new pxCalcDiscount(Discounttype, Quantity, DiscountValuePct, Discountkey, DiscountBestBuy,
                                                   dlist->PharmacyGroupId(), RefundValue, Promotion_No, TurnOverCalcImpact,
                                                   CascadeLevel, InternalDiscount, PromoBaseQty, RefundPct, CustomerNo,
                                                   DiscountCalcFrom, DiscountApplyTo));
                //}
                break;
            case ValuePctPhoenixMagic: // Barrabat OrderType PM
                calcDiscountCash(BestBuy_ValuePctPhoenixMagic, dlist, CascadeLevel);
                break;
            case ValuePctOverdrive: // Barrabat OrderType OV
                calcDiscountCashWithGrossProfitPctZero(DiscType_Default, dlist, CascadeLevel);
                break;
            case ValueGrossProfitPct: // Rohertragsrabat
                Discounttype = BestBuy_GrossProfitPct;
                GrossProfitPct = dlist->CalcGrossProfitPct(&Quantity, Discounttype, &Discountkey, &DiscountBestBuy, &RefundValue,
                    &Promotion_No, &TurnOverCalcImpact, &InternalDiscount, &PromoBaseQty, &RefundPct, &CustomerNo);

                // then: discount quantity there
                if (GrossProfitPct != 0.0)
                {
                    InsertAscending(new pxCalcDiscount(Discounttype, Quantity, 0.0, GrossProfitPct, Discountkey, DiscountBestBuy,
                                                       dlist->PharmacyGroupId(), (short)0, RefundValue, Promotion_No, TurnOverCalcImpact,
                                                       CascadeLevel, InternalDiscount, PromoBaseQty, RefundPct, CustomerNo,
                                                       DiscountCalcFrom, DiscountApplyTo));
                }
                break;
            case LogisticDataTransfer:
                Discounttype = BestBuy_LogisticDataTransfer;
                DiscountValuePct = dlist->CalcDiscountCash(&Quantity, Discounttype, &Discountkey, &DiscountBestBuy, &RefundValue,
                    &Promotion_No, &TurnOverCalcImpact, &InternalDiscount, &PromoBaseQty, &RefundPct, &CustomerNo, &DiscountCalcFrom,
                    &DiscountApplyTo);

                InsertAscending(new pxCalcDiscount(Discounttype, Quantity, DiscountValuePct, Discountkey, DiscountBestBuy,
                    dlist->PharmacyGroupId(), RefundValue, Promotion_No, TurnOverCalcImpact,
                    CascadeLevel, InternalDiscount, PromoBaseQty, RefundPct, CustomerNo,
                    DiscountCalcFrom, DiscountApplyTo));
                break;
            case ValuePctCashAssorted: // assorted cash discount
                Discounttype = BestBuy_ValuePctCashAssorted;
                calcDiscountCash(BestBuy_ValuePctCashAssorted, dlist, CascadeLevel);
                break;
            default:
                break;
            }

            InsertZeroDiscount(dlist, QOrdered);
        }
    }
#ifdef CHDISCLOG
    else
    {
		std::stringstream w;
		w << "ReduceToValidOffers done: Discount-List is now empty!";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), w.str());
    }    
#endif    

}

void pxCalcDiscountList::calcDiscountNatra(short discounttype, pxDiscountList* dlist, short cascadeLevel)
{
    double     discountKey;            // Refund percentage
    long       quantity = QOrdered_;
    short      discountBestBuy;
    long       discountArticle;        // maybe on Natraentries available
    nMoney     refundValue = pxConstants::mZero;
    short      promotionNo = (short)0;
    char       turnOverCalcImpact = '0';
    char       internalDiscount = '0';
    long       promoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

    long discountQty = dlist->CalcDiscountNatra(&quantity, discounttype, &discountKey, &discountBestBuy, &discountArticle, &refundValue,
                                                &promotionNo, &turnOverCalcImpact, &internalDiscount, &promoBaseQty, &RefundPct, 
                                                &CustomerNo, &DiscountCalcFrom, &DiscountApplyTo);
    if (discountQty != 0L)
    // then: discount quantity there
    {
        InsertAscending(new pxCalcDiscount(discounttype, quantity, discountQty, discountKey, discountBestBuy, discountArticle,
                                           dlist->PharmacyGroupId(), refundValue, promotionNo, turnOverCalcImpact, cascadeLevel,
                                           internalDiscount, promoBaseQty, RefundPct, CustomerNo, DiscountCalcFrom, DiscountApplyTo));
    }
}

void pxCalcDiscountList::calcDiscountNetto(short discounttype, pxDiscountList* dlist, short cascadeLevel)
{
    double     discountKey;            // Refund percentage
    long       quantity = QOrdered_;
    short      discountBestBuy;
    nMoney     refundValue = pxConstants::mZero;
    short      promotionNo = (short)0;
    char       turnOverCalcImpact = '0';
    char       internalDiscount = '0';
    long       promoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

    nMoney preisEKApoNetto = dlist->CalcDiscountNetto(&quantity, discounttype, &discountKey, &discountBestBuy, &refundValue, &promotionNo,
        &turnOverCalcImpact, &internalDiscount, &promoBaseQty, &RefundPct, &CustomerNo);

    if (preisEKApoNetto != pxConstants::mZero)
    // then: discount quantity there
    {
        InsertAscending(new pxCalcDiscount(discounttype, quantity, preisEKApoNetto, discountKey, discountBestBuy,
                                           dlist->PharmacyGroupId(), refundValue, promotionNo, turnOverCalcImpact, cascadeLevel,
                                           internalDiscount, promoBaseQty, RefundPct, CustomerNo, DiscountCalcFrom, DiscountApplyTo));
    }
}

void pxCalcDiscountList::calcDiscountCashWithGrossProfitPctZero(short discounttype, pxDiscountList* dlist, short cascadeLevel)
{
    double     discountKey;            // Refund percentage
    long       quantity = QOrdered_;
    short      discountBestBuy;
    nMoney     refundValue = pxConstants::mZero;
    short      promotionNo = (short)0;
    char       turnOverCalcImpact = '0';
    char       internalDiscount = '0';
    long       promoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

    double discountValuePct = dlist->CalcDiscountCash(&quantity, discounttype, &discountKey, &discountBestBuy, &refundValue, &promotionNo,
        &turnOverCalcImpact, &internalDiscount, &promoBaseQty, &RefundPct, &CustomerNo, &DiscountCalcFrom, &DiscountApplyTo);

    if (discountValuePct != 0.0)
    // then: discount quantity there
    {
        InsertAscending(new pxCalcDiscount(discounttype, quantity, discountValuePct, 0.0, discountKey, discountBestBuy,
                                           dlist->PharmacyGroupId(), dlist->PaymentTargetNo(), refundValue, promotionNo,
                                           turnOverCalcImpact, cascadeLevel, internalDiscount, promoBaseQty, RefundPct,
                                           CustomerNo, DiscountCalcFrom, DiscountApplyTo));
    }
}

void pxCalcDiscountList::calcDiscountFixedValue(short discounttype, pxDiscountList* dlist, short cascadeLevel)
{
    double     discountKey;            // Refund percentage
    long       quantity = QOrdered_;
    short      discountBestBuy;
    nMoney     refundValue = pxConstants::mZero;
    short      promotionNo = (short)0;
    char       turnOverCalcImpact = '0';
    char       internalDiscount = '0';
    long       promoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

    double fixedDiscVal = dlist->CalcFixedDiscountValue(&quantity, discounttype, &discountKey, &discountBestBuy, &refundValue, &promotionNo,
        &turnOverCalcImpact, &internalDiscount, &promoBaseQty, &RefundPct, &CustomerNo);

    if (fixedDiscVal != 0.0)
    {
        InsertAscending(new pxCalcDiscount(discounttype, quantity, discountKey, discountBestBuy,
            dlist->PharmacyGroupId(), refundValue, promotionNo, turnOverCalcImpact, cascadeLevel, internalDiscount, promoBaseQty, fixedDiscVal, RefundPct, CustomerNo, DiscountCalcFrom, DiscountApplyTo));
    }
}

void pxCalcDiscountList::calcDiscountCash(short discounttype, pxDiscountList* dlist, short cascadeLevel)
{
    double     discountKey;            // Refund percentage
    long       quantity = QOrdered_;
    short      discountBestBuy;
    nMoney     refundValue = pxConstants::mZero;
    short      promotionNo = (short)0;
    char       turnOverCalcImpact = '0';
    char       internalDiscount = '0';
    long       promoBaseQty = 0;
    double     RefundPct = pxConstants::dZero;
    long       CustomerNo = 0;
    short      DiscountCalcFrom = pxConstants::CalcFrom;
    short      DiscountApplyTo = pxConstants::ApplyTo;

    double discountValuePct = dlist->CalcDiscountCash(&quantity, discounttype, &discountKey, &discountBestBuy, &refundValue, &promotionNo,
                                                      &turnOverCalcImpact, &internalDiscount, &promoBaseQty, &RefundPct, &CustomerNo,
                                                      &DiscountCalcFrom, &DiscountApplyTo);
    if (discountValuePct != 0.0)
    // then: discount quantity there
    {
        InsertAscending(new pxCalcDiscount(discounttype, quantity, discountValuePct, discountKey, discountBestBuy,
                                           dlist->PharmacyGroupId(), refundValue, promotionNo, turnOverCalcImpact, cascadeLevel,
                                           internalDiscount, promoBaseQty, RefundPct, CustomerNo, DiscountCalcFrom, DiscountApplyTo));
    }
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyNatra
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
#ifdef CHDISCLOG
		BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxCalcDiscountList::BestBuyNatra - Validate BestBuyNatra 1");
#endif
        if( curp->IsNatraDefault() || curp->IsNatraTeam() || curp->IsNatraDiabetes())
        {

            if ((!bestp) || bestp->DiscountQty_ < curp->DiscountQty_)
            {
                bestp = curp;              // far the best at this moment
            }
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyNatra
(
    long QOrdered
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
#ifdef CHDISCLOG
		BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxCalcDiscountList::BestBuyNatra - Validate BestBuyNatra 2");
#endif
        if( curp->IsNatraDefault() || curp->IsNatraTeam() || curp->IsNatraDiabetes())
        {

            if ((!bestp || bestp->DiscountQty_ < curp->DiscountQty_) && (QOrdered >= curp->DiscountQty()))
            {
                bestp = curp;              // far the best at this moment
            }
        }
    }

    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyNetto
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if( curp->IsFixedPriceDefault() || curp->IsFixedPriceTeam() ||
            curp->IsFixedPriceDiabetes() || curp->IsFixedPricePharmGroup() ||
            curp->IsSpecialPrice())
        {
            if ((!bestp) || bestp->FixedPrice_ > curp->FixedPrice_)
            {
                bestp = curp;              // far the best at this moment
            }
        }
    }        
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyLogAddition
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if ( curp->IsLogisticAddition() && (!bestp || bestp->DiscountValuePct_ < curp->DiscountValuePct_) )
        {
            bestp = curp;              // far the best at this moment
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList::BestBuyLogAdditionDataTransfer
(
) const
{
    pxCalcDiscount* curp;
    pxCalcDiscount* bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ((curp = (pxCalcDiscount*) ++cursor) != NULL)
    {
        if (curp->IsLogisticAdditionDataTransfer() && (!bestp || bestp->DiscountValuePct_ < curp->DiscountValuePct_))
        {
            bestp = curp;              // far the best at this moment
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyFixedDiscountValue
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if ( curp->IsFixedDiscountValue() && (!bestp || bestp->FixedDiscountValue_ < curp->FixedDiscountValue_) )
        {
            bestp = curp;              // far the best at this moment
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyCash
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
#ifdef CHDISCLOG
		BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxCalcDiscountList::BestBuyCash - Validate BestBuyCash 1");
#endif
        if ( curp->IsValuePctCash() || curp->IsValuePctShort() ||  curp->IsValuePctShortLine() ||
             curp->IsValuePctGenerika() || curp->IsValuePctPartenariat() ||
             curp->IsValuePctWholeSale() || curp->IsValuePctRetail() ||
             curp->IsValuePctTena() ||  curp->IsValuePctPhoenixMagic() ||
             curp->IsValuePctOverDrive() || curp->IsValuePctWholeSaleInd() || 
             curp->IsValuePctCashAssorted())
        {
            if ((!bestp) || bestp->DiscountValuePct_ < curp->DiscountValuePct_)
            {
                bestp = curp;              // far the best at this moment
            }
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount-in-kind   */
/*  quantity, this method scans the entire list and returns a reference to    */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyCash
(
    long QOrdered
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
#ifdef CHDISCLOG
		BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxCalcDiscountList::BestBuyCash - Validate BestBuyCash 2");
#endif
        if ( curp->IsValuePctCash() || curp->IsValuePctShort() || curp->IsValuePctShortLine() ||
             curp->IsValuePctGenerika() || curp->IsValuePctPartenariat() ||
             curp->IsValuePctWholeSale() || curp->IsValuePctRetail() ||
             curp->IsValuePctTena() ||  curp->IsValuePctPhoenixMagic() ||
             curp->IsValuePctOverDrive() || curp->IsValuePctWholeSaleInd() ||
             curp->IsValuePctCashAssorted())
        {
            if ((!bestp || bestp->DiscountValuePct_ < curp->DiscountValuePct_) && (QOrdered >= curp->DiscountQty()))
            {
                bestp = curp;              // far the best at this moment
            }
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  There maybe entries in the list for each term group associated to the     */
/*  customer. To find the "best buy", that is, the highest discount           */
/*  percentage, this method scans the entire list and returns a reference to  */
/*  entry containing the highest discount quantity, without respecting the    */
/*  term group.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount*
pxCalcDiscountList :: BestBuyGrossProfitPct
(
) const
{
    pxCalcDiscount  *curp;
    pxCalcDiscount  *bestp = NULL;         // init best-buy pointer
    pxCalcDiscountListIter cursor((pxCalcDiscountList&)*this); // cast away constness

    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if ( curp->IsGrossProfitPct() && (!bestp || bestp->GrossProfitPct_ < curp->GrossProfitPct_) )
        {
            bestp = curp;              // far the best at this moment
        }
    }
    return bestp;
}

/*----------------------------------------------------------------------------*/
/*  Discount-in-kind quantity calculation automatically raises the order      */
/*  quantity until at least the first discount condition is met. However, a   */
/*  customer might deny this approach, so this function may be called to      */
/*  remove those entries from the list.                                       */
/*----------------------------------------------------------------------------*/
int
pxCalcDiscountList :: DeleteRaises
(
    const short Discounttype
)
{
    pxCalcDiscount  *curp;
    pxCalcDiscountListIter cursor(*this);
    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        if (( Discounttype == DiscType_Default && curp->IsRaised(*this)))
        {
            delete cursor.Remove();
        }
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCalcDiscountList :: Clear()
{
    pxCalcDiscount  *curp;
    pxCalcDiscountListIter cursor(*this);
    while ( (curp = (pxCalcDiscount*) ++cursor) != NULL )
    {
        cursor.Remove();
        delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Constructor of class pxCalcDiscount.                                      */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: pxCalcDiscount
(
    const short      Discounttype,
    const long       QOrdered,
    const long       DiscountQty,
    const double     Discountkey,
    const short      DiscountBestBuy,
    const long       DiscountArticle,
    const nString&   PharmacyGroupId,
    const nMoney     RefundValue,
    const short      Promotion_No,
    const char       TurnOverCalcImpact,
    const short      CascadeLevel,
    const char       InternalDiscount,
    const long       PromoBaseQty,
    const double     RefundPct,
    const long       CustomerNo,
    const short      DiscountCalcFrom,
    const short      DiscountApplyTo
)
{
    Discounttype_     =  Discounttype;
    QOrdered_         =  QOrdered;
    DiscountQty_      =  DiscountQty;
    FixedPrice_       =  pxConstants::mZero;
    DiscountValuePct_ =  0;
    Discountkey_      =  Discountkey;
    DiscountBestBuy_  =  DiscountBestBuy;
    DiscountArticle_  =  DiscountArticle;
    PharmacyGroupId_  =  PharmacyGroupId;
    PaymentTargetNo_  =  (short)0;
    RefundValue_      =  RefundValue;
    Promotion_No_     =  Promotion_No;
    TurnOverCalcImpact_ = TurnOverCalcImpact;
    CascadeLevel_     = CascadeLevel;
    InternalDiscount_ = InternalDiscount;
    PromoBaseQty_     = PromoBaseQty;
    RefundPct_        = RefundPct;
    CustomerNo_       = CustomerNo;
    DiscountCalcFrom_ = DiscountCalcFrom;
    DiscountApplyTo_  = DiscountApplyTo;
}

/*----------------------------------------------------------------------------*/
/*  Constructor of class pxCalcDiscount.                                      */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: pxCalcDiscount
(
    const short      Discounttype,
    const long       QOrdered,
    const double     Discountkey,
    const short      DiscountBestBuy,
    const nString&   PharmacyGroupId,
    const nMoney     RefundValue,
    const short      Promotion_No,
    const char       TurnOverCalcImpact,
    const short      CascadeLevel,
    const char       InternalDiscount,
    const long       PromoBaseQty,
    const double     FixedDiscountValue,
    const double     RefundPct,
    const long       CustomerNo,
    const short      DiscountCalcFrom,
    const short      DiscountApplyTo
)
{
    Discounttype_     =  Discounttype;
    QOrdered_         =  QOrdered;
    DiscountQty_      =  0;
    FixedPrice_       =  pxConstants::mZero;
    DiscountValuePct_ =  0;
    Discountkey_      =  Discountkey;
    DiscountBestBuy_  =  DiscountBestBuy;
    DiscountArticle_  =  0L;
    PharmacyGroupId_  =  PharmacyGroupId;
    PaymentTargetNo_  =  (short)0;
    RefundValue_      =  RefundValue;
    Promotion_No_     =  Promotion_No;
    TurnOverCalcImpact_ = TurnOverCalcImpact;
    CascadeLevel_     = CascadeLevel;
    InternalDiscount_ = InternalDiscount;
    PromoBaseQty_     = PromoBaseQty;
    FixedDiscountValue_ = FixedDiscountValue;
    RefundPct_        = RefundPct;
    CustomerNo_       = CustomerNo;
    DiscountCalcFrom_ = DiscountCalcFrom;
    DiscountApplyTo_  = DiscountApplyTo;
}

/*----------------------------------------------------------------------------*/
/*  Constructor of class pxCalcDiscount.                                      */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: pxCalcDiscount
(
    const short      Discounttype,
    const long       QOrdered,
    const nMoney     FixedPrice,
    const double     Discountkey,
    const short      DiscountBestBuy,
    const nString&   PharmacyGroupId,
    const nMoney     RefundValue,
    const short      Promotion_No,
    const char       TurnOverCalcImpact,
    const short      CascadeLevel,
    const char       InternalDiscount,
    const long       PromoBaseQty,
    const double     RefundPct,
    const long       CustomerNo,
    const short      DiscountCalcFrom,
    const short      DiscountApplyTo
)
{
    Discounttype_     =  Discounttype;
    QOrdered_         =  QOrdered;
    DiscountQty_      =  0;
    FixedPrice_       =  FixedPrice;
    DiscountValuePct_ =  0;
    Discountkey_      =  Discountkey;
    DiscountBestBuy_  =  DiscountBestBuy;
    DiscountArticle_  =  0L;
    PharmacyGroupId_  =  PharmacyGroupId;
    PaymentTargetNo_  =  (short)0;
    RefundValue_      =  RefundValue;
    Promotion_No_     =  Promotion_No;
    TurnOverCalcImpact_=TurnOverCalcImpact;
    CascadeLevel_     = CascadeLevel;
    InternalDiscount_ = InternalDiscount;
    PromoBaseQty_     = PromoBaseQty;
    RefundPct_        = RefundPct;
    CustomerNo_       = CustomerNo;
    DiscountCalcFrom_ = DiscountCalcFrom;
    DiscountApplyTo_  = DiscountApplyTo;
}

/*----------------------------------------------------------------------------*/
/*  Constructor of class pxCalcDiscount.                                      */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: pxCalcDiscount
(
    const short      Discounttype,
    const long       QOrdered,
    const double     DiscountValuePct,
    const double     Discountkey,
    const short      DiscountBestBuy,
    const nString&   PharmacyGroupId,
    const nMoney     RefundValue,
    const short      Promotion_No,
    const char       TurnOverCalcImpact,
    const short      CascadeLevel,
    const char       InternalDiscount,
    const long       PromoBaseQty,
    const double     RefundPct,
    const long       CustomerNo,
    const short      DiscountCalcFrom,
    const short      DiscountApplyTo
)
{
    Discounttype_     =  Discounttype;
    if ( Discounttype == DiscType_Default )
        Discounttype_ = DiscType_CashDiscount;
    QOrdered_         =  QOrdered;
    DiscountQty_      =  0;
    FixedPrice_       =  pxConstants::mZero;
    DiscountValuePct_ =  DiscountValuePct;
    Discountkey_      =  Discountkey;
    DiscountBestBuy_  =  DiscountBestBuy;
    DiscountArticle_  =  0L;
    PharmacyGroupId_  =  PharmacyGroupId;
    PaymentTargetNo_  =  (short)0;
    RefundValue_      =  RefundValue;
    Promotion_No_     =  Promotion_No;
    TurnOverCalcImpact_ = TurnOverCalcImpact;
    CascadeLevel_     = CascadeLevel;
    InternalDiscount_ = InternalDiscount;
    PromoBaseQty_     = PromoBaseQty;
    RefundPct_        = RefundPct;
    CustomerNo_       = CustomerNo;
    DiscountCalcFrom_ = DiscountCalcFrom;
    DiscountApplyTo_  = DiscountApplyTo;
}

pxCalcDiscount :: pxCalcDiscount
(
    const short      Discounttype,
    const long       QOrdered,
    const double     DiscountValuePct,
    const double     GrossProfitPct,
    const double     Discountkey,
    const short      DiscountBestBuy,
    const nString&   PharmacyGroupId,
    const short      PaymentTargetNo,
    const nMoney     RefundValue,
    const short      Promotion_No,
    const char       TurnOverCalcImpact,
    const short      CascadeLevel,
    const char       InternalDiscount,
    const long       PromoBaseQty,
    const double     RefundPct,
    const long       CustomerNo,
    const short      DiscountCalcFrom,
    const short      DiscountApplyTo
)
{
    Discounttype_     =  Discounttype;
    if ( Discounttype == DiscType_Default )
        Discounttype_ = DiscType_CashDiscount;
    QOrdered_         =  QOrdered;
    DiscountQty_      =  0;
    FixedPrice_       =  pxConstants::mZero;
    DiscountValuePct_ =  DiscountValuePct;
    GrossProfitPct_   =  GrossProfitPct;
    Discountkey_      =  Discountkey;
    DiscountBestBuy_  =  DiscountBestBuy;
    DiscountArticle_  =  0L;
    PharmacyGroupId_  =  PharmacyGroupId;
    PaymentTargetNo_  =  PaymentTargetNo;
    RefundValue_      =  RefundValue;
    Promotion_No_     =  Promotion_No;
    TurnOverCalcImpact_ = TurnOverCalcImpact;
    CascadeLevel_     = CascadeLevel;
    InternalDiscount_ = InternalDiscount;
    PromoBaseQty_     = PromoBaseQty;
    RefundPct_        = RefundPct;
    CustomerNo_       = CustomerNo;
    DiscountCalcFrom_ = DiscountCalcFrom;
    DiscountApplyTo_  = DiscountApplyTo;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: pxCalcDiscount
(
    const pxCalcDiscount& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCalcDiscount :: ~pxCalcDiscount()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxCalcDiscount&
pxCalcDiscount :: operator=( const pxCalcDiscount& src)
{
    Discounttype_   =  src.Discounttype_;
    QOrdered_       =  src.QOrdered_;
    DiscountQty_    =  src.DiscountQty_;
    FixedPrice_     =  src.FixedPrice_;
    Discountkey_    =  src.Discountkey_;
    DiscountArticle_ = src.DiscountArticle_;
    PharmacyGroupId_ = src.PharmacyGroupId_;
    PaymentTargetNo_ = src.PaymentTargetNo_;
    RefundValue_     = src.RefundValue_;
    Promotion_No_    = src.Promotion_No_;
    TurnOverCalcImpact_ = src.TurnOverCalcImpact_;
    PromoBaseQty_      =src.PromoBaseQty_;
    RefundPct_       = src.RefundPct_;
    CustomerNo_      = src.CustomerNo_;
    DiscountCalcFrom_ = src.DiscountCalcFrom_;
    DiscountApplyTo_  = src.DiscountApplyTo_;

    return *this;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCalcDiscount list objects being inserted in the following       */
/*  ascending  sequence:                                                      */
/*  KondGruppenNr, DiscountCode                                               */
/*----------------------------------------------------------------------------*/
int
pxCalcDiscount :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCalcDiscount *that = (pxCalcDiscount*)That;
    int retval = (Discounttype_ == that->Discounttype_) ? 0
               : (Discounttype_ > that->Discounttype_ ? 1 : -1);
    
    if ( retval == 0 )
        retval = (DiscountQty_ == that->DiscountQty_) ? 0
               : (DiscountQty_ > that->DiscountQty_ ? 1 : -1);

    if ( retval == 0 )
        retval = (FixedPrice_ == that->FixedPrice_) ? 0
               : (FixedPrice_ > that->FixedPrice_ ? 1 : -1);

    return retval;
}

enum tDiscountCategory pxCalcDiscount::GetDiscountCategory() const
{
    if (CustomerNo_ > 0)
    {
        return DiscCategory_Customer;
    }
    if (PharmacyGroupId_ != "000" && false == PharmacyGroupId_.IsEmpty())
    {
        return DiscCategory_PharmacyGroup;
    }
    return DiscCategory_Common;
}
