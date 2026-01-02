#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxartoldprice.hpp"
#include "pxarticlelppr.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxitemdiscount.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "types/messagecodeenum.inc"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  Return a price valid for item value calculation.                          */
/*  If no price is available, an nMoney object containing 0 is returned.      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: Price
(
)
{
    pxCustBase&       customer    = *(Order().Customer());
    nMoney m_price;
    m_price = PreisEKApoNetto_;     // first take customer net purchase price

    // BG/ID252 fixedprice
    if ( m_price > pxConstants::mZero && Session()->isBulgaria() )
    {
       return m_price;
    }

    if (!m_price)                         // not there, hopefully the customer
       m_price = PreisEKApoFree_;         // Free proce entered

    if (!m_price)                         // not there, hopefully the customer
    {
       if ( customer.CustomerGroupFlagsList()->isGroupBasePriceAEP() )
       {
          m_price = PreisEKApo_;          // purchase price is there or the current
          if (!m_price )
          {
             m_price = PreisEKGrosso_;
          }
       }
    }
    if (!m_price)                         // not there, hopefully the customer
    {
       if ( customer.CustomerGroupFlagsList()->isGroupBasePriceGEP() )
       {
          m_price = PreisEKGrosso_;       // Wholesaleprice is there or the current
          if (Session()->isBulgaria()) // only for Bulgaria
          {
             //ID218 new AEP will be calculated if special surcharge is added (in all other cases AEP=GEP)
             if( IsTHWertAusKsc() )
             {
                m_price = PreisEKApo_;
             }
          }
       }
    }
    if (!m_price)                         // not there, hopefully the customer
    {
       if ( customer.CustomerGroupFlagsList()->isGroupBasePriceGEPNA() )
       {
          m_price = PreisEKGrossoNA_;
          if (!m_price )
          {
             m_price = PreisEKGrosso_;
          }
       }
    }
    return m_price;                       // item is not chargeable
}// Price

/*----------------------------------------------------------------------------*/
/*  Return a price valid for item value calculation.                          */
/*  If no price is available, an nMoney object containing 0 is returned.      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: PriceCstGr12
(
)
{
    pxCustBase&       customer    = *(Order().Customer());
    nMoney price(PreisEKApoNetto_);     // first take customer net purchase price
    if (!price)                         // not there, hopefully the customer
       price = PreisEKApoFree_;         // Free proce entered
    /*if ( !Order().Swiss() )
    {
       if (!price)                         // not there
          price = PreisEKGrossoNA_;        // take wholesale net price
    }
        */
    if (!price)                         // not there, hopefully the customer
       price = PreisEKApo_;             // purchase price is there or the current
    if (!price)                         // not there, hopefully the customer
       price = PreisEKGrosso_;          // Wholesaleprice is there or the current

    if (Session()->isBulgaria()) // only for Bulgaria
    {
       if ( customer.CustomerGroupFlagsList()->isGroupBasePriceGEPNA() )
       {
          price = PreisEKGrossoNA_;
          if (!price )
             price = PreisEKGrosso_;
       }
           // for customer groups 12 and 15 price is AEP (basis for calculating PreisFaktur)
           // so: do nothing
    }

    return price;                       // item is not chargeable
}// PriceCstGr12

/*----------------------------------------------------------------------------*/
/*  Calculate this item's order value.                                        */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: OrderValue
(
)
{
    if ( IsDispoItemValued() )
    {
       if (Session()->isBulgaria())         //  just for Bulgary
       {
          if ( ArtDispo() )
          {
             if ( ArtDispo_->NetPrice() > pxConstants::dZero )
             {
                return ( ArtDispo_->NetPrice() * (double)MengeBestellt_);
             }
          }
       }
    }
	return Price() * (double)MengeBestellt_;
}

/*----------------------------------------------------------------------------*/
/*  Calculate this item's ship value.                                         */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: ShipValue
(
)
{
    if ( IsDispoItemValued() )
       return OrderValue();
	return Price() * (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
}

/*----------------------------------------------------------------------------*/
/*  Calculate this item's order value.                                        */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem::OrderValueDisc
(
)
{
	if (PreisFaktur() > pxConstants::mZero)
			return PreisFaktur() * (double)MengeBestellt_;
	return Price() * (double)MengeBestellt_;
}

/*----------------------------------------------------------------------------*/
/*  Calculate this item's ship value.                                         */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem::ShipValueDisc
(
)
{
	if (IsDispoItemValued())
		return OrderValue();
	if (PreisFaktur() > pxConstants::mZero)
			return PreisFaktur() * (double)MengeBestellt_;
	return Price() * (double)(MengeGeliefert_ + MengeVerbund() - MengeNatra_);
}

/*----------------------------------------------------------------------------*/
/*  Calculate this item's corrupt value .                                     */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: OrderCorruptValue
(
)
{
    if ( MengeBestellt() - MengeGeliefert() - MengeVerbund() > 0 )
       return Price() * (double) (MengeBestellt() - MengeGeliefert() - MengeVerbund() );
    else
       return pxConstants::mZero;

}

/*----------------------------------------------------------------------------*/
/*  Calculate this item's invoice price.                                      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: InvoiceValue
(
    pxItemDiscountList* discl
)
{
    double       Reb(0.0);
    pxCustBase& customer = *(Order().Customer());
    if (Session()->isSerbia())
       return pxConstants::mZero;

    if ( IsFixedInvoicePrice() )
        return PreisFaktur_;

    if ( IsDispoItemValued() )
    {
       if (!Session()->isBulgaria())
       {
          return OrderValue();
       }
    }

    if ( discl )
    {
        pxItemDiscount* entryp = discl->GetEntry(PosNr_);
       if (entryp)
       {
          Reb = entryp->DiscountValuePct();
          DiscountValPctProforma_ = Reb;
       }
    }

    double Qty    = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
    if (Qty == pxConstants::dZero)                          // prevent devision by zero
       return pxConstants::mZero;

    if (Reb == pxConstants::dZero)
    {
       Reb    = ( DiscountValPctMan_ > pxConstants::dZero ) ? DiscountValPctMan_ : GetDiscountValuePct();
    }
    nMoney   Bprice = Price();                  // AEP/GEP

    if (Session()->isBulgaria())         // special Bulgarian calculation
    {
       if(customer.IsCommercialRounding())
       {
          PreisFaktur_    = Bprice * (1 - (Reb/(100+Reb)));          // commerercial calculation;
                  PreisFakturCstGr12_    = PriceCstGr12() * (1 - (Reb/(100+Reb)));          // commerercial calculation;
       }
       else
       {
          PreisFaktur_    = Bprice - ((Bprice*Reb)/100.0);     // mathematical calculation;
          PreisFakturCstGr12_    = PriceCstGr12() - ((Bprice*Reb)/100.0);     // mathematical calculation;
       }
       RabattFestDM_   = Bprice - PreisFaktur_;    // rebate value
    }
    else
    {
          PreisFaktur_    = Bprice - ((Bprice*Reb)/100.0);     // mathematical calculation;
    }
    
	// CPR-201272
	nMoney FixedPrice = getOrderPositionDiscountDiscountValue();                       //HR Get DiscountValue from Table orderpositiondiscount
	PreisFaktur_ = (FixedPrice > pxConstants::mZero) ? FixedPrice : PreisFaktur_;

    SetDirty();                                 // should be written to the database

    if ( discl)                                 // generated by order->ProformaInvoice()
    {
       return (PreisFaktur_ * Qty);
    }

    return PreisFaktur_;
}// InvoiceValue


/*----------------------------------------------------------------------------*/
/*  Calculate this item's NaturalRebate value.                                */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: NaturalRebateValue
(
)
{
       return Price() * (double) (MengeNatra_);

}
/*----------------------------------------------------------------------------*/
/*  Obtain the base prices from the price list.                               */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: GetBasePrices
(
    const PriceTypeEnum priceType
)

{
    ClearError();
    pxArtOldPrice*  oldprice = NULL;
    const pxCustOrderType&  ot = Order().OrderType();
    pxCustBase* customer = Order().Customer();
    short BranchNo = customer->Vertriebszentrum();
    nMoney     iPreisEKApo = PreisEKApo_;
    PreisEKApo_       = pxConstants::mZero;
    PreisVKApo_       = pxConstants::mZero;
    PreisEKApoNetto_  = pxConstants::mZero;
    PreisEKGrosso_    = pxConstants::mZero;
    PreisEKGrossoNA_  = pxConstants::mZero;
    PreisAGP_         = pxConstants::mZero;
    RabattFest_       = pxConstants::mZero;
    nMoney TenderContractPrice(0.0);


    if ( ArtPrice_ == NULL )
    {
       if ( ArtPriceList() )
       {
          ArtPrice_ = ArtPriceList()->Find(priceType);
       }
    }

    //now try to get old price for this article
    if ( oldprice == NULL )
    {
       oldprice = new pxArtOldPrice(Session(),BranchNo,ArtikelNr_);
       if ( oldprice->Get(cDBGET_READONLY))
       {
          delete oldprice;
          oldprice = NULL;
       }
    }

    // maybe PriceTyp changed
    if ( ArtPrice_ != NULL )
    {
       if ( ArtPrice_->PreisTyp() != priceType )
       {
          ArtPrice_ = NULL;
          ArtPrice_ = ArtPriceList()->Find(priceType);
          if ( ArtPrice_ != NULL )
          {
             iPreisEKApo = pxConstants::mZero;
          }
       }
    }

    if ( ArtPrice_ == NULL )
    {
       ArtPrice_ = ArtPriceList()->Find(FREESALE_PRICE);
    }

    if ( ArtPrice_ != NULL )
    {
       if (  iPreisEKApo == pxConstants::mZero )
       {
          PreisEKApo_       = ArtPrice_->PreisEKApo      ();
       }
       else
       {
          PreisEKApo_       = iPreisEKApo;
       }

       PreisVKApo_       = ArtPrice_->PreisVKApo      ();
       PreisEKGrosso_    = ArtPrice_->PreisEKGrosso   ();
       PreisEKGrossoNA_  = ArtPrice_->PreisEKGrossoNA ();
       PreisAGP_         = ArtPrice_->PreisAGP        ();
       if ( ot.IsDiscountable() )
          RabattFest_       = ArtPrice_->RabattFest     ();
       if ( oldprice != NULL )
       {
          if (  iPreisEKApo == pxConstants::mZero )
          {
             PreisEKApo_       =  oldprice->PreisEKApo      ();
          }
          else
          {
             PreisEKApo_       = iPreisEKApo;
          }
          PreisVKApo_       = oldprice->PreisVKApo      ();
          PreisEKGrosso_    = oldprice->PreisEKGrosso   ();
          PreisEKGrossoNA_  = oldprice->PreisEKGrossoNA ();
       }
       TenderContractPrice = GetTenderContractPrice();
       if ( TenderContractPrice != pxConstants::mZero )
       {
          PreisEKApo_ = TenderContractPrice;
       }
    }
    else
       ExternalError(CMsgStream(), CMSG_ART_NOBASEPRICES, ArtikelNr_);

    if (oldprice)
    {
       delete oldprice;
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  ReimbursementPrice: returns the reimbursementprice for a given articleno  */
/*  If there is no entry within table articlelppr, so 0.0 will be returned    */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: ReimbursementPrice
(
    const    long  ArticleNo,
    const    char  Type
)
{
    nMoney PriceReimB  = pxConstants::mZero;
    pxArticleLppr*    ReimB = NULL;
    ReimB = new pxArticleLppr(Session(),ArticleNo,Type);
    if ( ReimB->Get(cDBGET_READONLY))
    {
       delete ReimB;
       return PriceReimB;
    }
    PriceReimB = ReimB->ReimbursementPrice();
    delete ReimB;
    return PriceReimB;
}
/*----------------------------------------------------------------------------*/
/*  Calculate this item's netto value                                         */
/*  Netto Value =                                                             */
/*  PreisFaktur_ * ( MengeGeliefert_ + MengeVerbund() - MengeNatra_ )         */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: WertNetto
(
)
{
    if (!Session()->isBulgaria())         //  just for Bulgary
       return pxConstants::mZero;

    double Qty    = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
    if ( IsDispoItemValued() )
    {
       if ( ArtDispo() )
       {
          if ( ArtDispo_->NetPrice() > pxConstants::dZero )
          {
             return (ArtDispo_->NetPrice() * Qty);
          }
       }
    }

    return (PreisFaktur_ * Qty);
}
/*----------------------------------------------------------------------------*/
/*  Calculate this item's bruttovalue                                         */
/*  Brutto Value =                                                            */
/*  Price() * ( MengeGeliefert_ + MengeVerbund() - MengeNatra_ )              */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: WertBrutto
(
)
{
    nMoney         BruttoPrice;
        double       Reb(0.0);
    pxCustBase& customer = *(Order().Customer());
    if (!Session()->isBulgaria())         //  just for Bulgary
       return pxConstants::mZero;

    double Qty    = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
    if (Qty == pxConstants::dZero)              // prevent devision by zero
       return pxConstants::mZero;

    nMoney   Bprice = Price();                  // AEP/GEP

    if (Session()->isBulgaria())         // special Bulgarian calculation
    {
       if(customer.IsCommercialRounding())
       {
          BruttoPrice    = Bprice * (1 - (Reb/(100+Reb)));          // commerercial calculation;
       }
       else
       {
          BruttoPrice    = Bprice - ((Bprice*Reb)/100.0);     // mathematical calculation;
       }
    }
    else
    {
          BruttoPrice    = Bprice - ((Bprice*Reb)/100.0);     // mathematical calculation;
    }

    return (BruttoPrice*Qty * (1 + (SalesTaxRate_/100)));
}// InvoiceValue
/*----------------------------------------------------------------------------*/
/*  Calculate this item's rebate value                                        */
/*  Rebate Value =                                                            */
/*  (Aep - PreisFaktur_) * ( MengeGeliefert_ + MengeVerbund() - MengeNatra_ ) */
/*  Member RabattFestDM_ contains difference between Aep and PreisFaktur_     */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: WertRabatt
(
)
{
    if (!Session()->isBulgaria())         //  just for Bulgary
       return pxConstants::mZero;

    double Qty    = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);

    return (RabattFestDM_ * Qty);
}
/*----------------------------------------------------------------------------*/
/*  CalcSalesTax                                                              */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: CalcSalesTax
(
)
{
    nMoney         taxvalue(0.0);
    if (!Session()->isBulgaria())         //  just for Bulgary
       return pxConstants::mZero;

    taxvalue = (( WertNetto() * SalesTaxRate_ ) / 100.0);
    return taxvalue;
}
/*----------------------------------------------------------------------------*/
/*  SetPreisTyp                                                               */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: PreisTyp
(
    const PriceTypeEnum preisTyp
)
{
    if (  PreisEKApo_ == pxConstants::mZero )        // new Position
    {
       PreisTyp_ = preisTyp;
    }
    else
    if ( PreisTyp_ != preisTyp )
    {
       PreisTyp_ = preisTyp;
       PreisEKApo_  = pxConstants::mZero;            // force new Preis
    }
    SetDirty();
}
/*----------------------------------------------------------------------------*/
/*  Calculate this item's invoice price.                                      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: calculateInvoiceValue
(
)
{
    nMoney         iValue(0.0);

    if ( MengeBestaetigt_ == 0)            // just if MengeBestaetgt_  > 0
    {
       return iValue;
    }
    if ( PreisFaktur_ == pxConstants::mZero ) // just if InvaoicValue available
    {
       return iValue;
    }

    iValue = (PreisFaktur_ - RabattFest_) * (double)MengeBestaetigt_;

    return iValue;
}
/*----------------------------------------------------------------------------*/
/*  Calculate this item's invoice price.                                      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: calculateNaturalRebateValue
(
)
{
    nMoney         iValue(0.0);

    if ( MengeNatra_ > 0 )           // maybe there is naturalrebate (same article)
    {
       iValue = iValue + (double)NaturalRebateValue();
    }

    return iValue;
}

#include <pxregistersprices.hpp>
#include <pxnhifprices.hpp>
#include <calcdiscpct.h>

nMoney pxOrderItem::GetGepNaNa()
{
	basar::Decimal gepnana;
	basar::Decimal invDisc(ArtBase_->InvoiceRebatePct());
	invDisc /= basar::Decimal(100);
	basar::Decimal rebInKind(ArtBase_->RebateInKindPct());
	rebInKind /= basar::Decimal(100);
	basar::Decimal invDiscAnnual(ArtBase_->AnnualInvRebPct());
	invDiscAnnual /= basar::Decimal(100);
	basar::Decimal rebInKindAnnual(ArtBase_->AnnualRebIKPct());
	rebInKindAnnual /= basar::Decimal(100);

	basar::Decimal gep(PreisTyp() == HEALTHFUND_PRICE ? PreisEKGrossoKK() : PreisEKGrossoFV());
	calcdisc::calcGepnana(
		gep,
		invDisc,
		invDiscAnnual,
		rebInKind,
		rebInKindAnnual,
		gepnana);
	return gepnana.toFloat64();
}

int pxOrderItem::checkPriceLimitations( bool ignorePriceLimitation, long& qtyToPost )
{
    ///////////////////////////////////////////////////////////////////////////
    // PRECONDITIONS
    ///////////////////////////////////////////////////////////////////////////
    if (Session()->isCheckPriceLimitationSet() == false)
    {
        return ErrorState();
    }
    
    if (true == ArtBase()->MinistryProductCode().IsEmpty())
    {
        return ErrorState();
    }

    if (false == Order().OrderType().IsNormal() && false == Order().OrderType().IsTenderInvoice())
    {
        return ErrorState();
    }

    ///////////////////////////////////////////////////////////////////////////
    // selection of 
    ///////////////////////////////////////////////////////////////////////////
    nMoney maxwholesalePrice = pxConstants::mZero;
    nMoney referencePrice = pxConstants::mZero;
    nMoney nhifPrice = pxConstants::mZero;

    pxRegistersPrices p(Session(), ArtBase()->MinistryProductCode());
    if (0 == p.Get())
    {
        //maxwholesalePrice = p.MaxWholesalePrice();							// without VAT --> OK
        maxwholesalePrice = p.getMaxWholesalePrice();
        referencePrice = p.ReferencePrice() / (1 + (SalesTaxRate() / 100));	// with VAT    --> without
    }

    if (false == ArtBase()->HealthFundCodeHospital().IsEmpty())
    {
        pxNHIFPrices n(Session(), ArtBase()->HealthFundCodeHospital());
        if (0 == n.Get())
        {
            nhifPrice = n.NHIFPrice() / (1 + (SalesTaxRate() / 100));				// with VAT    --> without
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // HOSPITAL MARKET
    ///////////////////////////////////////////////////////////////////////////
    if (Order().Customer()->KdGruppe() == "06")
    {
        if (nhifPrice > pxConstants::mZero)
        {
            if (PreisEKApo_ > nhifPrice)
            {
                if (nhifPrice == referencePrice && nhifPrice == maxwholesalePrice)
                {
                    // Test case #8
                    SetPreisEKApo( nhifPrice );
                }
                else
                {
                    if (nhifPrice > referencePrice && referencePrice == maxwholesalePrice)
                    {
                        // Test case #9
                        SetPreisEKApo( maxwholesalePrice );
                    } 
                    else
                    {
                        // Test case #10
                        SetPriceLimitExceeded();
                        SetPreisEKApo( maxwholesalePrice );
                        if( false == ignorePriceLimitation )
                        {
                            FehlerArtikel_ = ArtStatePriceLimitCompViolationNHIFPriceMWPRefPrice;
                            ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE);
                        }
                    }
                    return ErrorState();
                }
            }
        }
        else
        {
            if (referencePrice > pxConstants::mZero)
            {
                if (PreisEKApo_ > referencePrice)
                {
                    if (referencePrice == maxwholesalePrice)
                    {
                        // Test case #2
                        SetPreisEKApo(referencePrice);
                    }  
                    else if (referencePrice < maxwholesalePrice) 
                    {
                        if (1 - GetGepNaNa() / referencePrice > 0.06)
                        {
                            // Test case #5
                            SetPreisEKApo( referencePrice );
                        } else {
                            // Test case #4
                            SetPriceLimitExceeded();
                            SetPreisEKApo( maxwholesalePrice );
                            if( false == ignorePriceLimitation )
                            {
                                FehlerArtikel_ = ArtStatePriceLimitCompViolationMWPAndRefPrice;
                                ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE);
                            }
                        }
                    } 
                    else 
                    {
                        // Test case #3
                        SetPriceLimitExceeded();
                        SetPreisEKApo( maxwholesalePrice );
                        if (false == ignorePriceLimitation)
                        {
                            FehlerArtikel_ = ArtStatePriceLimitCompViolationMWPAndRefPrice;
                            ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE);
                        }
                        return ErrorState();
                    }
                }
            }
            else
            {
                // System does not have NHIFPrice and RefPrice
                if (maxwholesalePrice > pxConstants::mZero)
                {
                    // Test case #11
                    if (PreisEKApo_ > maxwholesalePrice)
                    {
                        SetPreisEKApo( maxwholesalePrice );
                    }
                    // Test case #1 common path with Test case #11, but price os not set newly.
                } 
                else 
                {
                    // Test case #12: MWS IS ZERO
                    SetPriceLimitExceeded();
                    
                    if (false == ignorePriceLimitation)
                    {
                        FehlerArtikel_ = ArtStatePriceLimitDeletion;
                        ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION);
                    }
                    else
                    {
                        qtyToPost = 0;
                    }
                }
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    // NO HOSPITAL MARKET
    ///////////////////////////////////////////////////////////////////////////
    else
    {
        /*if (false == ArtBase()->MinistryProductCode().IsEmpty())
        {*/
            if (PreisEKApo_ > maxwholesalePrice && (maxwholesalePrice > pxConstants::mZero /* Product not cancelled! */) )
            {
                // Test case #6
                SetPriceLimitExceeded();
                                
                if( Session()->Device()->IsVideo() )
                {
                    if (false == ignorePriceLimitation)
                    {
                        //"The product price is higher than the MWP. Please contact your supervisor."
                        FehlerArtikel_ = ArtStatePriceLimitMWPExceedance;
                        ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE);
                        //in Exception object the errorcodenumber = CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE;
                    }
                }
                            
                return ErrorState();
            }
            
            if (maxwholesalePrice == pxConstants::mZero) /* Product cancelled */
            {
                // Test case #7: MWS IS ZERO
                SetPriceLimitExceeded();
                
                if (Session()->Device()->IsVideo())
                {
                    if (false == ignorePriceLimitation)
                    {
                        //"The registered price of this product has been cancelled."
                        FehlerArtikel_ = ArtStatePriceLimitDeletion;
                        ExternalError(CMsgStream(), CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION);
                    }
                }

                return ErrorState();
            }
    }

    return ErrorState();
}
