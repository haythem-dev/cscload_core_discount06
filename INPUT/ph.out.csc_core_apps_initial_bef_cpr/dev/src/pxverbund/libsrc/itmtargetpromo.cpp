/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
the main purpose of this module is Targetpromotion handling

REVISION HISTORY

17 Jan 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxrangecontrol.hpp"
#include "pxpromotions.hpp"
#include "pxpromotioncollect.hpp"
#include "pxorderpospromo.hpp"
#include "pxitemdiscount.hpp"

/*----------------------------------------------------------------------------*/
/*  AssignDiscountPct: first look for an rangememberentry on the database     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: AssignDiscountPct
(
    pxDiscount*         diskentry,
    pxRangeControl*     rclentry
)
{
    pxCustBase&       customer    = *(Order().Customer());       // customer
    // unused variable
    /* short             VZ         = */ customer.Vertriebszentrum(); // customers Branchno
    pxPromoCollect*   promocollect = NULL;
    // unused variable
    // pxPromotions*     promo        = NULL;
    pxPromotions*     ProductPromo = NULL;
    pxItemDiscount*   itemdisc     = NULL;
    pxOrderPosPromo*  pospromo     = NULL;
    bool            AddOnOk        = false;
    double          PosRabRebate   =   0.0;
    double          PosPromoRebate =   0.0;
    double          CalcRebate     =   0.0;
    nString m_str;
    m_str = "pxOrderItem :: AssignDiscountPct";

    if ( !PromoCollectList_ == NULL )
    {
        promocollect = PromoCollectList_->BestTargetPromotion();
    }
    if (promocollect)
    {
        // just for BestTargetPromotion
        if ( promocollect->PromotionNo() != diskentry->PromotionNo() )
        {
            return ErrorState();
        }
        // just if DiscountValuePct > 0 ( prevent overhead)
        if (diskentry->DiscountValuePct() == 0.0)
        {
            return ErrorState();
        }
        // if already checked
        pospromo = GetOrderPosPromo(promocollect->PromotionNo());
        if ( pospromo )
        {
            return ErrorState();
        }

        if ( PromotionNo() > 0 && promocollect->PromotionNo() != PromotionNo())  // product promo maybe availabe
        {
            ProductPromo = new pxPromotions(Session(), PromotionNo());
            if (!ProductPromo->IsGoodState())
            {
                delete ProductPromo;
                ProductPromo = NULL;
            }
        }

        // get kdauftragposrab DiscountValuePct
        if ( ItemDiscountList_ != NULL )
        {
            PosRabRebate = GetDiscountValPctMan();
            if ( PosRabRebate > 0.0 )                      // we have manual rebate
            {
                UndoProductPromotion();                      // no PP
                UndoOrderPosPromo();                         // delete entries
                if ( ProductPromo )
                {
                    delete ProductPromo;
                }
                return ErrorState();
            }
            PosRabRebate = GetDiscountValuePct();
        }

        // get kdauftragpospromo DiscountValuePct
        if ( OrderPosPromoList_ != NULL )
        {
            PosPromoRebate  = GetPosPromoDiscountValuePct();
        }

        // no combination with productpromo and standardrebate
        if ( (promocollect->AddOnPromoDiscOk() == '0') &&  ( promocollect->AddOnStdDiscOk() == '0') )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                else
                {
                    UndoProductPromotion();
                }
                delete ProductPromo;
            }
            UndoItemDiscount();
            UndoOrderPosPromo();
            UndoOrderPosRefund();
            itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
            itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
            itemdisc->logKdAuftragPosRab(m_str);
            itemdisc->Put();
            ItemDiscountList()->Append(itemdisc);
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentry->BaseQty(),
                                diskentry->BaseValue(), diskentry->CustomerNo(), promocollect->PromotionNo(), '0', diskentry->DiscountValuePct());

            CheckRefund(diskentry, promocollect, rclentry );

            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion

            // Order().SetDoNotSplittOrder();
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '0' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                else
                {
                    UndoProductPromotion();
                }
                delete ProductPromo;
            }
            UndoOrderPosPromo();
            UndoOrderPosRefund();
            AddOnOk = AddOnDiscountPct(diskentry->DiscountValuePct(), (PosRabRebate - PosPromoRebate));
            if ( !AddOnOk )
            {
                UndoItemDiscount();                      // undo discount
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                itemdisc->logKdAuftragPosRab(m_str);
                itemdisc->Put();
                ItemDiscountList()->Append(itemdisc);
            // Order().SetDoNotSplittOrder();
                return ErrorState();
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentry->BaseQty(),
                                diskentry->BaseValue(), diskentry->CustomerNo(), promocollect->PromotionNo(), '0', diskentry->DiscountValuePct());
            CheckRefund(diskentry, promocollect, rclentry );

            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )                // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();
                    }
                    else
                    {
                        UndoProductPromotion();                                  // rollback ProductPromotion
                        UndoOrderPosPromo();
                        delete ProductPromo;
                        ProductPromo = NULL;
                    }
                }
            }

            if ( ProductPromo )                                               // ProductPromo combination with TargetPromo
            {
                if ( ProductPromo->AddOnStdDiscOk() == '0'  )                  // no combination with standard rebate
                {
                    if ( PosRabRebate > 0.0 && PosPromoRebate == 0.0 )
                    {
                        CalcRebate = PosRabRebate;                               // CalcRebate   = Standard Rebate
                    }
                    else
                    if ( PosRabRebate > 0.0 && PosPromoRebate > 0.0 )
                    {                                                           // CalcRebate   = Standard Rebate (maybe zero)
                        CalcRebate = PosRabRebate - PosPromoRebate ;
                    }
                }
            }

            AddOnOk = AddOnDiscountPct(diskentry->DiscountValuePct(), CalcRebate );
            if ( !AddOnOk )
            {
                UndoItemDiscount();                      // undo discount
                if ( OrderPosPromoList()->Entries() > 0 )
                {
                    UndoOrderPosPromo();
                }
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                itemdisc->logKdAuftragPosRab(m_str);
                itemdisc->Put();
                ItemDiscountList()->Append(itemdisc);
                //Order().SetDoNotSplittOrder();
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentry->BaseQty(),
                                diskentry->BaseValue(), diskentry->CustomerNo(), promocollect->PromotionNo(), '0', diskentry->DiscountValuePct());
            CheckRefund(diskentry, promocollect, rclentry );
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            if ( ProductPromo )
            {
                delete  ProductPromo;
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '0' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    else
                    {
                        UndoProductPromotion();
                        UndoOrderPosPromo();
                        delete ProductPromo;
                        ProductPromo = NULL;
                    }
                }
            }

            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnStdDiscOk() == '1'  )        // no standardrebate with this combination of target promotion
                {
                    if ( PosRabRebate > 0.0 && PosPromoRebate == 0.0 )
                    {
                        CalcRebate = PosRabRebate;                                   // CalcRebate   = Standard Rebate
                    }
                    else
                    if ( PosRabRebate > 0.0 && PosPromoRebate > 0.0 )
                    {                                                               // CalcRebate   = Standard Rebate (maybe zero)
                        CalcRebate = PosRabRebate - PosPromoRebate ;
                    }
                }
            }
            else
            {
                CalcRebate = PosRabRebate;                                        // CalcRebate   = Standard Rebate
            }

            AddOnOk = AddOnDiscountPct(diskentry->DiscountValuePct(), CalcRebate);
            if ( !AddOnOk )
            {
                if ( PosPromoRebate > 0 )
                {
                    UndoOrderPosPromo();
                }
                UndoItemDiscount();                      // undo discount
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                itemdisc->logKdAuftragPosRab(m_str);
                itemdisc->Put();
                ItemDiscountList()->Append(itemdisc);
                //Order().SetDoNotSplittOrder();
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentry->BaseQty(),
                                diskentry->BaseValue(), diskentry->CustomerNo(), promocollect->PromotionNo(), '0', diskentry->DiscountValuePct());
            CheckRefund(diskentry, promocollect, rclentry );
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            if ( ProductPromo )
            {
                delete  ProductPromo;
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  AssignDiscountPct: first look for an rangememberentry on the database     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: AssignDiscountPctProforma
(
    pxDiscount* diskentry,
    pxItemDiscountList* discl
)
{
    pxPromoCollect*   promocollect = NULL;
    pxPromotions*     ProductPromo = NULL;
    double            PosRabRebate   =   0.0;
    double            PosPromoRebate =   0.0;

    if ( discl == NULL || diskentry == NULL )
        return ErrorState();

    if ( !PromoCollectList_ == NULL )
    {
        promocollect = PromoCollectList_->BestTargetPromotion();
    }
    if (promocollect)
    {
        if ( promocollect->PromotionNo() != diskentry->PromotionNo() )
        {
            return ErrorState();
        }
        if (diskentry->DiscountValuePct() == 0.0)
        {
            return ErrorState();
        }
        if ( PromotionNo() > 0 && promocollect->PromotionNo() != PromotionNo())  // product promo maybe availabe
        {
            ProductPromo = new pxPromotions(Session(), PromotionNo());
            if (!ProductPromo->IsGoodState())
            {
                delete ProductPromo;
                ProductPromo = NULL;
            }
        }
        // get kdauftragposrab DiscountValuePct
        pxItemDiscount* itemdisc = discl->GetEntry(PosNr());
        if (itemdisc)
        {
            PosRabRebate = GetDiscountValuePct();
        }
        // get kdauftragpospromo DiscountValuePct
        if ( OrderPosPromoList_ != NULL )
        {
            PosPromoRebate  = GetPosPromoDiscountValuePct();
        }

        if ( (promocollect->AddOnPromoDiscOk() == '0') &&  ( promocollect->AddOnStdDiscOk() == '0') )
        {
            if ( itemdisc )
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    delete ProductPromo;
                }
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
            }
            else
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    delete ProductPromo;
                }
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                discl->Append(itemdisc);
            }
            // Order().SetDoNotSplittOrder();
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '0' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( itemdisc )
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    delete ProductPromo;
                }
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct() + (PosRabRebate - PosPromoRebate));
            }
            else
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    delete ProductPromo;
                }
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                discl->Append(itemdisc);
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( itemdisc )
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                    {
                        if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                        {
                            delete ProductPromo;
                            return ErrorState();                                     // nothing to do
                        }
                    }
                    delete ProductPromo;
                }
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct() + PosRabRebate);
            }
            else
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                    {
                        if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                        {
                            delete ProductPromo;
                            return ErrorState();                                     // nothing to do
                        }
                    }
                    delete ProductPromo;
                }
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                discl->Append(itemdisc);
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '0' )
        {
            if ( itemdisc )
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                    {
                        if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                        {
                            delete ProductPromo;
                            return ErrorState();                                     // nothing to do
                        }
                    }
                    delete ProductPromo;
                }
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct() + PosPromoRebate );
            }
            else
            {
                if ( ProductPromo )
                {
                    if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                    {
                        if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                        {
                            delete ProductPromo;
                            return ErrorState();                                     // nothing to do
                        }
                    }
                    delete ProductPromo;
                }
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(diskentry->DiscountValuePct());
                discl->Append(itemdisc);
            }
        }
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  AssignTargetDiscount: first look for an rangememberentry on the database  */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: AssignTargetDiscount
(
    pxRangeControlList* rcl
)
{
    pxCustBase&       customer    = *(Order().Customer());       // customer
    // unused variable
    /* short             VZ         = */ customer.Vertriebszentrum(); // customers Branchno
    pxPromoCollect*   promocollect = NULL;
    // unused variable
    // pxPromotions*     promo        = NULL;
    pxPromotions*     ProductPromo = NULL;
    pxItemDiscount*   itemdisc     = NULL;
    pxRangeControl*   rentriep     = NULL;             // RangeControlEntry Pointer
    bool              AddOnOk     = false;
    pxDiscount*       diskentry     = NULL;
    pxOrderPosPromo*  pospromo     = NULL;
    double            PosRabRebate   =   0.0;
    double            PosPromoRebate =   0.0;
    double            CalcRebate     =   0.0;
    double            diskentryBaseValue = 0.0;
    long              diskentryBaseQty   = 0;
    double            DiscountValuePct   = 0.0;

    nString m_str;
    m_str = "pxOrderItem :: AssignTargetDiscount";


    if ( !PromoCollectList_ == NULL )
    {
        promocollect = PromoCollectList_->BestTargetPromotion(ArtikelNr_);
    }
    if (promocollect)
    {
        // just for correct entry
        rentriep = rcl->Find( promocollect->PromotionNo());
        if ( rentriep  == NULL )
        {
            return ErrorState();
        }
        // give controle entry
        diskentry = rentriep->GetTargetControlEntry();
        if (diskentry == NULL )
        {
            return ErrorState();
        }
        diskentryBaseValue = rentriep->GetTargetControlBaseValue();
        diskentryBaseQty   = rentriep->GetTargetControlBaseQty();
        // if already checked
        pospromo = GetOrderPosPromo(promocollect->PromotionNo());
        if ( pospromo )
        {
            return ErrorState();
        }

        if (  promocollect->ArticleNo() > 0 )
        {
            DiscountValuePct = promocollect->DiscountValuePct() + diskentry->DiscountValuePct();
        }
        else
        {
            DiscountValuePct =  diskentry->DiscountValuePct();
        }

        if ( PromotionNo() > 0 && promocollect->PromotionNo() != PromotionNo())  // product promo maybe availabe
        {
            ProductPromo = new pxPromotions(Session(), PromotionNo());
            if (!ProductPromo->IsGoodState())
            {
                delete ProductPromo;
                ProductPromo = NULL;
            }
        }

        // get kdauftragposrab DiscountValuePct
        if ( ItemDiscountList_ != NULL )
        {
            PosRabRebate = GetDiscountValPctMan();
            if ( PosRabRebate > 0.0 )                       // we have manual rebate
            {
                UndoProductPromotion();                      // no PP
                UndoOrderPosPromo();                         // delete entries
                if ( ProductPromo )
                {
                    delete ProductPromo;
                }
                return ErrorState();
            }
            PosRabRebate = GetDiscountValuePct();
        }
        // get kdauftragpospromo DiscountValuePct
        if ( OrderPosPromoList_ != NULL )
        {
            PosPromoRebate  = GetPosPromoDiscountValuePct();
        }
        if ( (promocollect->AddOnPromoDiscOk() == '0') &&  ( promocollect->AddOnStdDiscOk() == '0') )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                else
                {
                    UndoProductPromotion();
                }
                delete ProductPromo;
            }
            UndoItemDiscount();
            UndoOrderPosPromo();
            UndoOrderPosRefund();
            if (DiscountValuePct > 0.0 )
            {
                itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                itemdisc->SetDiscountValuePct(DiscountValuePct);
                itemdisc->logKdAuftragPosRab(m_str);
                itemdisc->Put();
                ItemDiscountList()->Append(itemdisc);
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentryBaseQty,
                                diskentryBaseValue, diskentry->CustomerNo(), promocollect->PromotionNo(), '0', DiscountValuePct);
            CheckRefund(diskentry, promocollect, rentriep);
            // Order().SetDoNotSplittOrder();
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '0' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                else
                {
                    UndoProductPromotion();
                }
                delete ProductPromo;
            }

            UndoOrderPosPromo();
            UndoOrderPosRefund();
            if (DiscountValuePct > 0.0 )
            {
                AddOnOk = AddOnDiscountPct(DiscountValuePct, (PosPromoRebate));
                if ( !AddOnOk )
                {
                    if ( PosPromoRebate > 0.0 )
                    {
                        UndoOrderPosPromo();
                    }
                    UndoItemDiscount();                      // undo discount
                    if ( OrderPosPromoList()->Entries() > 0 )
                    {
                        UndoOrderPosPromo();
                    }
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    itemdisc->logKdAuftragPosRab(m_str);
                    itemdisc->Put();
                    ItemDiscountList()->Append(itemdisc);
                }
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentryBaseQty,
                                diskentryBaseValue, diskentry->CustomerNo(), promocollect->PromotionNo(), '0', DiscountValuePct);
            CheckRefund(diskentry, promocollect, rentriep);
            // Order().SetDoNotSplittOrder();
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    else
                    {
                        UndoProductPromotion();
                        UndoOrderPosPromo();
                        delete ProductPromo;
                        ProductPromo = NULL;
                    }
                }
            }

            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnStdDiscOk() == '0' )        // no combination with standard rebate
                {
                    if ( PosRabRebate > 0.0 && PosPromoRebate == 0.0 )
                    {
                        CalcRebate = PosRabRebate;                                   // CalcRebate   = Standard Rebate
                    }
                    else
                    if ( PosRabRebate > 0.0 && PosPromoRebate > 0.0 )
                    {                                                               // CalcRebate   = Standard Rebate (maybe zero)
                        CalcRebate = PosRabRebate - PosPromoRebate ;
                    }
                }
            }

            if ( DiscountValuePct > 0.0 )
            {
                AddOnOk = AddOnDiscountPct(DiscountValuePct, CalcRebate);
                if ( !AddOnOk )
                {
                    UndoItemDiscount();                      // undo discount
                    if ( OrderPosPromoList()->Entries() > 0 )
                    {
                        UndoOrderPosPromo();
                    }
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    itemdisc->logKdAuftragPosRab(m_str);
                    itemdisc->Put();
                    ItemDiscountList()->Append(itemdisc);
                }
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentryBaseQty,
                                diskentryBaseValue, diskentry->CustomerNo(), promocollect->PromotionNo(), '0', DiscountValuePct);
            CheckRefund(diskentry, promocollect, rentriep);
            // Order().SetDoNotSplittOrder();
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            if ( ProductPromo )
            {
                delete  ProductPromo;
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '0' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    else
                    {
                        UndoProductPromotion();
                        UndoOrderPosPromo();
                        delete ProductPromo;
                        ProductPromo = NULL;
                    }
                }
            }
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnStdDiscOk() == '1'  )        // no standardrebate with this combination of target promotion
                {
                    if ( PosRabRebate > 0.0 && PosPromoRebate == 0.0 )
                    {
                        CalcRebate = PosRabRebate;                                   // CalcRebate   = Standard Rebate
                    }
                    else
                    if ( PosRabRebate > 0.0 && PosPromoRebate > 0.0 )
                    {                                                               // CalcRebate   = Standard Rebate (maybe zero)
                        CalcRebate = PosRabRebate - PosPromoRebate ;
                    }
                }
            }
            else
            {
                CalcRebate = PosRabRebate;                                   // CalcRebate   = Standard Rebate
            }

            if ( DiscountValuePct > 0.0 )
            {
                AddOnOk = AddOnDiscountPct(DiscountValuePct, CalcRebate);
                if ( !AddOnOk )
                {
                    UndoItemDiscount();                      // undo discount
                    /*if ( OrderPosPromoList()->Entries() > 0 )
                    {
                        UndoOrderPosPromo();
                    }
                    */
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    itemdisc->logKdAuftragPosRab(m_str);
                    itemdisc->Put();
                    ItemDiscountList()->Append(itemdisc);
                }
            }
            WriteOrderPosPromo( diskentry->PharmacyGroupId(), promocollect->DiscountGrpNo(), diskentryBaseQty,
                                diskentryBaseValue, diskentry->CustomerNo(), promocollect->PromotionNo(), '0', DiscountValuePct);
            CheckRefund(diskentry, promocollect, rentriep);
            // Order().SetDoNotSplittOrder();
            SetPromotionNo(promocollect->PromotionNo() );     // mark promotion
            SetPromoTyp((short) 1);                          // mark promotion
            if ( ProductPromo )
            {
                delete  ProductPromo;
            }
            return ErrorState();
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  AssignTargetDiscountProforma:                                             */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: AssignTargetDiscountProforma
(
    pxRangeControlList* rcl,
    pxItemDiscountList* discl
)
{
    pxPromoCollect*   promocollect = NULL;
    pxPromotions*     ProductPromo = NULL;
    pxRangeControl*   rentriep     = NULL;             // RangeControlEntry Pointer
    pxDiscount*      diskentry     = NULL;
    pxOrderPosPromo*  pospromo     = NULL;
    double            PosRabRebate   =   0.0;
    double            PosPromoRebate =   0.0;
    double            DiscountValuePct   = 0.0;
    pxOrderItem*      proformapos  = NULL;

    // just to prevent cores
    if ( discl == NULL || rcl == NULL )
        return ErrorState();

    // find the best promotion for this Item object
    if ( !PromoCollectList_ == NULL )
    {
        promocollect = PromoCollectList_->BestTargetPromotion(ArtikelNr_);
    }
    // found one
    if (promocollect)
    {
        // find this one in the rangecontole list
        rentriep = rcl->Find( promocollect->PromotionNo());
        if ( rentriep  == NULL )
        {
            return ErrorState();
        }
        // get controle entry
        diskentry = rentriep->GetTargetControlEntry();
        if (diskentry == NULL )
        {
            return ErrorState();
        }
        // if the best promotion is already given, rerurn to caller
        pospromo = GetOrderPosPromo(promocollect->PromotionNo());
        if ( pospromo )
        {
            return ErrorState();
        }
        // get item from the the ItemListProforma
        proformapos = (pxOrderItem*)Order().ItemListProforma()->At((PosNr()-1));
        if (  promocollect->ArticleNo() > 0 )
        {
            DiscountValuePct = promocollect->DiscountValuePct() + diskentry->DiscountValuePct();
        }
        else
        {
            DiscountValuePct =  diskentry->DiscountValuePct();
        }
        if ( PromotionNo() > 0 && promocollect->PromotionNo() != PromotionNo())  // product promo maybe availabe
        {
            ProductPromo = new pxPromotions(Session(), PromotionNo());
            if (!ProductPromo->IsGoodState())
            {
                delete ProductPromo;
                ProductPromo = NULL;
            }
        }

        // get kdauftragposrab DiscountValuePct
        pxItemDiscount* itemdisc = discl->GetEntry(PosNr());
        if (itemdisc)
        {
            PosRabRebate = GetDiscountValuePct();
        }
        // get kdauftragpospromo DiscountValuePct
        if ( OrderPosPromoList_ != NULL )
        {
            PosPromoRebate  = GetPosPromoDiscountValuePct();
        }

        // now check the real situation on the item
        if ( (promocollect->AddOnPromoDiscOk() == '0') &&  ( promocollect->AddOnStdDiscOk() == '0') )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                if ( proformapos )
                {
                    proformapos->UndoProductPromotion(Order().ItemListProforma());
                    delete ProductPromo;
                    ProductPromo = NULL;
                }
                else
                {
                    delete ProductPromo;
                    ProductPromo = NULL;
                }
            }
            if ( DiscountValuePct > 0.0 )
            {
                if ( itemdisc )
                {
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                }
                else
                {
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    discl->Append(itemdisc);
                }
                if (proformapos)
                {
                    proformapos->SetPromotionNo(promocollect->PromotionNo() );
                    proformapos->InvoiceValue(discl);
                }
            }
            if (proformapos)
            {
                proformapos->SetPromotionNo(promocollect->PromotionNo() );
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '0' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                {
                    delete ProductPromo;
                    return ErrorState();                                     // nothing to do
                }
                if ( proformapos )
                {
                    proformapos->UndoProductPromotion(Order().ItemListProforma());
                    delete ProductPromo;
                    ProductPromo = NULL;
                }
                else
                {
                    delete ProductPromo;
                    ProductPromo = NULL;
                }
            }
            if ( DiscountValuePct > 0.0 )
            {
                if ( itemdisc )
                {
                    itemdisc->SetDiscountValuePct(DiscountValuePct + (PosRabRebate - PosPromoRebate) );
                }
                else
                {
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    discl->Append(itemdisc);
                }
                if (proformapos)
                {
                    proformapos->SetPromotionNo(promocollect->PromotionNo() );
                    proformapos->InvoiceValue(discl);
                }
            }
            if (proformapos)
            {
                proformapos->SetPromotionNo(promocollect->PromotionNo() );
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '1' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    if ( proformapos )
                    {
                        proformapos->UndoProductPromotion(Order().ItemListProforma());
                        delete ProductPromo;
                        ProductPromo = NULL;
                    }
                }
            }

            if ( DiscountValuePct > 0.0 )
            {
                if ( itemdisc )
                {
                    itemdisc->SetDiscountValuePct(DiscountValuePct + PosRabRebate );
                }
                else
                {
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct);
                    discl->Append(itemdisc);
                }
                if (proformapos)
                {
                    proformapos->SetPromotionNo(promocollect->PromotionNo() );
                    proformapos->InvoiceValue(discl);
                }
            }
            if (proformapos)
            {
                proformapos->SetPromotionNo(promocollect->PromotionNo() );
            }
            return ErrorState();
        }

        if ( promocollect->AddOnPromoDiscOk() == '1' &&  promocollect->AddOnStdDiscOk() == '0' )
        {
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnPromoDiscOk() == '0'  )    // no combination with target promotion
                {
                    if ( ProductPromo->Priority() < promocollect->Priority() )  // product better than target
                    {
                        delete ProductPromo;
                        return ErrorState();                                     // nothing to do
                    }
                    else
                    {
                        if ( proformapos )
                        {
                            proformapos->UndoProductPromotion(Order().ItemListProforma());
                            delete ProductPromo;
                            ProductPromo = NULL;
                        }
                    }
                }
            }
            if ( ProductPromo )
            {
                if ( ProductPromo->AddOnStdDiscOk() == '1'  )        // no standardrebate with this combination of target promotion
                {
                    if ( PosRabRebate > 0.0 && PosPromoRebate == 0.0 )
                    {
                        // unused variable
                        /// CalcRebate =  PosRabRebate;                                   // CalcRebate   = Standard Rebate
                    }
                    else
                    if ( PosRabRebate > 0.0 && PosPromoRebate > 0.0 )
                    {  // unused variable                                                          // CalcRebate   = Standard Rebate (maybe zero)
                        // CalcRebate = PosRabRebate - PosPromoRebate ;
                    }
                }
            }
            else
            {
                // unused variable
                // CalcRebate = PosRabRebate;                                   // CalcRebate   = Standard Rebate
            }

            if ( DiscountValuePct > 0.0 )
            {
                if ( itemdisc )
                {
                    itemdisc->SetDiscountValuePct(DiscountValuePct + PosPromoRebate );
                }
                else
                {
                    itemdisc = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, (short)BestBuy_ValuePctCash, diskentry->PharmacyGroupId());
                    itemdisc->SetDiscountValuePct(DiscountValuePct + PosPromoRebate);
                    discl->Append(itemdisc);
                }
                if (proformapos)
                {
                    proformapos->SetPromotionNo(promocollect->PromotionNo() );
                    proformapos->InvoiceValue(discl);
                }
            }
            if (proformapos)
            {
                proformapos->SetPromotionNo(promocollect->PromotionNo() );
            }
            return ErrorState();
        }
    }

    return ErrorState();
}
