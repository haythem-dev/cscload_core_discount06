#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxrangecollect.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxitemdiscount.hpp"
#include "types/messagecodeenum.inc"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  CommomProformaInvoice: This is a  methode devoloped for the order         */
/*  entry system in all countries, except Bulgaria.                           */
/*  This methode calculates the invoice price for this order under respect    */
/*  of all rebate conditions (RPG(Ranges) included).                          */
/*  It recalculates the members WertAuftrag, Wertlieferung, WertZeilen.       */
/*  This fuction is most reflected by the XML application. It is very         */
/*  important to send all information recarding quantities, correct prices and*/
/*  correct discount percentages to the customer.                             */
/*  It builds up a this->ItemProformaList_ for callers usage.                 */
/*  Caution: the table promotions is not affected within this fuction         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CommonProformaInvoice
(
    const short pricetype /* = -1 as default */
)
{
    pxRangeControlList*    rangcl = NULL;
    pxRangeControl*      rentriep = NULL;             // RangeControlEntry Pointer
    pxOrderItem*             item = NULL;             // OrderItem Entry
    pxItemDiscountList* posrablist = NULL;
    tKDAUFTRAGPOSRAB        record;
    short discounttype = 0;            // discounttype

/*----------------------------------------------------------------------------*/
/*  Basic sanity checks.                                                      */
/*----------------------------------------------------------------------------*/
    ClearError();
    if (!ItemList_ )                    // then order item processing not open
       return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (!isProformaInvoiceAllowed())
    {
        return NULL;
    }

    // generate new ItemListProforma_
    if ( ItemListProforma_ )
    {
       delete ItemListProforma_;
       ItemListProforma_ = NULL;
    }

    ItemListProforma( pricetype );
    if (ItemListProforma_->Entries() == 0)
    {
        return ErrorState();
    }

    pxDiscountOrdTypList* dotl = Session()->DiscountOrderTypList();
    if (dotl)
    {
        discounttype = dotl->Find(KdAuftragArt());
    }

/*----------------------------------------------------------------------------*/
/*  First collect all rebates(percentages) until now into a temporary         */
/*  pxItemDiscountList(posrablist). Scan for that the order position list     */
/*----------------------------------------------------------------------------*/
    posrablist = new pxItemDiscountList(Session());
    pxOrderItemListIter it(*ItemListProforma_);
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       pxItemDiscount* posrabp = item->ItemDiscountList()->FindDiscountValuePct();
       if (posrabp)
       {
          Assign(record, *posrabp);
          posrablist->AddToList(&record,0);
       }
    }

    DeleteRangeCollectList();

/*----------------------------------------------------------------------------*/
/*  Now look for discount groups like we do while orderclosing under respect  */
/*  of the temporary itemdiscountlist posrablist                              */
/*  Be carefull if there are no RPG rebates within this order. In that case   */
/*  it is stingently necessary to recalculate the  InvoiceValue for each Item */
/*  under respect of the posrablist as was build above. The meaning for doing */
/*  this,is to get the DiscountValPctProforma(pxOrderItem member) for each    */
/*  position. DiscountValPctProforma will be send back to the customer.       */
/*----------------------------------------------------------------------------*/
    RangeCollectList();                     // init RangeCollectList
    BuildRangeCollectList();                // collection of discountgroupmembers
    if ( !RangeCollectList()->Entries() )
    {
       cleanupCommonProformaInvoice(pricetype, posrablist);
       return ErrorState();
    }

    rangcl = BuildRangeControleList();      // collection of discountgroup numbers
    pxRangeControlListIter    cursor(*rangcl);
    if ( rangcl->Entries() == 0)
    {
       cleanupCommonProformaInvoice(pricetype, posrablist);
       delete rangcl;
       rangcl = NULL;
       return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Third: Assign TargetPromotion depend on condition                         */
/*  where articleno > 0                                                       */
/*----------------------------------------------------------------------------*/
    cursor.Reset();
    while ((rentriep = (pxRangeControl*) ++cursor) != NULL)
    {
        pxDiscount* discp = rentriep->RangeCondition(Session(), this);
        if (discp)
        {
            if (discounttype != discp->DiscountType())
            {
                continue;
            }

            if (rentriep->GrpDiscountTyp() > 0)
            {
                calculateRangeGroupCondition(rentriep, posrablist);
                if ( rentriep->GroupInvoiceValue() != pxConstants::mZero && Session()->isFrance() )
                {
                    if ((rentriep->InvoiceValue() - rentriep->NaturalRebateValue()) <= (rentriep->GroupInvoiceValue() - rentriep->GroupNaturalRebateValue()))
                    {
                        continue;
                    }
                }
            }

            switch (rentriep->GrpDiscountTyp())
            {
                case pxRangeControl::RangeCond_MultyCondArticle:
                {
                    AssignRangeMultyCondArticle(rentriep, posrablist);     // special handling fore multy conditions
                    break;
                }
                case pxRangeControl::RangeCond_MultyCondManufacturer:
                {
                    AssignRangeMultyCondManuMacturer(rentriep, posrablist); // special handling manufacturers conditions
                    break;
                }
                case pxRangeControl::RangeCond_BaseValue:
                {
                    AssignRangeBaseValue(rentriep, posrablist);             // special handling base value conditions
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
/*----------------------------------------------------------------------------*/
/*  Now build up the new delivery value of this order (WertLieferung)         */
/*  on respect of the temporary itemdiscountlist posrablist                   */
/*----------------------------------------------------------------------------*/
    ReCalcValuesProforma(posrablist);

    delete posrablist;
    if ( rangcl )
       delete rangcl;
    if (RangeCollectList_ )
    {
       delete RangeCollectList_;
       RangeCollectList_ = NULL;
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  isProformaInvoiceAllowed                                                  */
/*----------------------------------------------------------------------------*/
bool pxOrder::isProformaInvoiceAllowed()
{
    pxCustBase*       customer = Customer();       // customer
    bool retval = true;
    if (!IsPseudoLock())
    {
        if (!IsLocked())                  // order still locked ??
        {
            ExternalError(CMsgStream(), CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
            retval = false;
        }
    }
    if (AnzPos() == 0)
    {
        retval = false;
    }

    if (Session()->isBulgaria())
    {
        retval = false;
    }

    // OrderType is not discountable
    if (!OrderType().IsDiscountable())
    {
        retval = false;
    }

    // Customer Group is not discountable(Group 8,9,13)
    if (!customer->CustomerGroupFlagsList()->IsKscDiscountEnabled())
    {
        retval = false;
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  cleanupCommonProformaInvoice: do some common cleanups                     */
/*----------------------------------------------------------------------------*/
int pxOrder :: cleanupCommonProformaInvoice(const short pricetype, pxItemDiscountList* posrablist)
{
    AssignPosDiscountValPctProforma(posrablist); // call  InvoiceValue for each position
    ItemListProforma(pricetype);
    AssignPosDiscountValPctProforma();
    ReCalcValuesProforma(posrablist);
    delete posrablist;
    delete RangeCollectList_;
    RangeCollectList_ = NULL;
    return ErrorState();
}
