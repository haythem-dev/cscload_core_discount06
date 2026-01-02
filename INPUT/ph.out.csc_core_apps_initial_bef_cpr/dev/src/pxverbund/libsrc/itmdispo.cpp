#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxtaxrates.hpp"
#include "pxservices.hpp"
#include "nntypes.h"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Return article dispo class pointer. If the object is not already          */
/*  referenced, its read constructor is called.                               */
/*  If DBAccessMode is cDBGET_FORUPDATE and the record is not already locked, */
/*  the record is read and locked.                                            */
/*----------------------------------------------------------------------------*/
pxArtDispo*
pxOrderItem :: ArtDispo
(
    DBAccessMode mode
)

{
    if ( (ArtDispo_) && ArtDispo_->IsActive() && mode != cDBGET_FORUPDATE )
        return ArtDispo_;                 // simply return the pointer

    // must read, but ensure we have a dispo item:
    if ( IsDispoItem() )
    {
        if (!ArtDispo_)                   // then must construct pxArtDispo object
            ArtDispo_ = new pxArtDispo(Session(), KdAuftragNr_, PosNr_, mode);
        else if ( (mode == cDBGET_FORUPDATE) && !(ArtDispo_->IsLocked()) )
            ArtDispo_->Get(mode);

        if ( !(ArtDispo_->IsGoodState()) )  // then dispo item not found
        {
            nError::operator = (ArtDispo_->Error()); // copy error object
            delete ArtDispo_;             // and delete the object instance
            ArtDispo_ = NULL;
            PosTyp_ = TypeProductUnknown;
        }
    }

    return ArtDispo_;
}

int
pxOrderItem :: DispoUpdate
(
    tDISPOITEM& s,
    BookingType btype
)
{
/*----------------------------------------------------------------------------*/
/*  Update self.                                                              */
/*----------------------------------------------------------------------------*/
    MengeBestellt_ = s.MengeBestellt;
    Bemerkungen_   = s.Bemerkungen;
    PreisEKApo_    = s.PreisEKApo;
    PreisEKGrosso_ = s.PreisEKGrosso;
    RabattFestDM_  = s.RabattFestDM;
    RabattFest_    = s.RabattFest;
    KzPriso_       = s.KzPriso;
    PostType(btype);
    if ( PreisEKApo_ > pxConstants::mZero || PreisEKGrosso_ > pxConstants::mZero )
    {
        PosTyp_ = TypeDispoItemValued;   // this is a valued dispo item
        MengeBestaetigt_ = MengeBestellt_;
        MengeGeliefert_  = MengeBestellt_;
        ETArtSchalter_.ClearErmaessigtMwst();
        if ( s.MWSTSchluessel == HALFTAX )
            ETArtSchalter_.SetErmaessigtMwst();
        if ( s.TaxPflichtig )
            ETArtKlasse_.SetTaxPflichtig();
        SalesTaxRate(static_cast<short>(s.MWSTSchluessel));
    }
    else                                // values are to be supplied after
        PosTyp_ = TypeDispoItem;         // purchasing the product

/*----------------------------------------------------------------------------*/
/*  Set service routing flags.                                                */
/*----------------------------------------------------------------------------*/
    ClearToCustomerService();
    ClearToDisposal();
    if (IsDisponieren() || IsNachliefern())
    {
        SetToCustomerService();          // inform customer service branch
        SetToDisposal();                 // and product disposal
    }

/*----------------------------------------------------------------------------*/
/*  Update dispo article object.                                              */
/*----------------------------------------------------------------------------*/
    ArtDispo_->SetOrder(KdAuftragNr_, PosNr_);
    *ArtDispo_ = s;

    SetDirty();

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Return dispo item values in a tDISPOITEM structure.                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DispoGet
(
    tDISPOITEM& s
)
{
    ClearError();
    if ( !IsDispoItem() )               // must be a dispo item
        return ExternalError(CMsgStream(), CMSG_ITM_NOVALUEDTEXT);

    if ( ArtDispo() )
    {
        pxArtDispo& dr    = *ArtDispo_;

        s.MengeBestellt   = MengeBestellt_;
        s.Bemerkungen     = Bemerkungen_;
        s.KzPriso         = KzPriso_;

        dr.DispoGet(s);
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Update dispo item.                                                        */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DispoSet
(
    tDISPOITEM& s,
    BookingType btype
)
{

    ClearError();
    if ( !IsChangeable() )              // item must be changeable
        return ErrorState();
    if ( !IsDispoItem() )               // item must be a dispo item
        return ExternalError(CMsgStream(), CMSG_ITM_NOVALUEDTEXT);
    if ( DispoSanity(s, btype) )       // data sanity check
        return ErrorState();

    nDBBeginTransaction(cDBTransRecord);
    if (ArtDispo(cDBGET_FORUPDATE))
    {
        if ( !DispoUpdate(s, btype) )
        {
            ArtDispo_->Put();
            nError::operator = (ArtDispo_->Error()); // copy error object
        }
        if ( !IsGoodState() )            // Then error occured during
        {                                // data base update.
            delete ArtDispo_;             // Force new read construction
            ArtDispo_ = NULL;             // for this object.
        }
    }

    return ItemUpdate();
}

/*----------------------------------------------------------------------------*/
/*  Data sanity checks to be performed prior to any update.                   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DispoSanity
(
    tDISPOITEM& s,
    BookingType btype
)
{

    ClearError();
    const double cHIGHPERCENT = 20.00;  // Discount in percent: high limit
 
    // Booking type: must be default, delivery confirmed or rest delivery
    if ( !(btype == BookingTypeDefault ||
           btype == PurchaseOrder      ||
           btype == RestDelivery) )
        return ExternalError(CMsgStream(), CMSG_ITM_BTYPE_INVALID);

	if ( s.Service_No != 0 )
	{
    	pxServicesList servicelist(Session());
	    servicelist.Select(s.Service_No);
	    if ( servicelist.Entries() == 0 ) 
	    {
		   return ExternalError(CMsgStream(), CMSG_ITM_SERVICENO_INVALID, s.Service_No);
	    }
	}
		
    pxTaxRates* taxrate = Session()->TaxRatesList()->Find(static_cast<short>(s.MWSTSchluessel));
    if ( taxrate == NULL )
        return ExternalError(CMsgStream(), CMSG_ITM_BTYPE_INVALID);

    // Order quantity is required
    if (s.MengeBestellt <= 0)
        return ExternalError(CMsgStream(), CMSG_ITM_OQ_MISSING);

    // Article description is required.
    s.Bezeichnung.Strip(nString::cTRAILING, cSPACE);
    if ( s.Bezeichnung.Length() == 0 )
        return ExternalError(CMsgStream(), CMSG_ITM_DESC_MISSING);

    // Entering the wholesale purchase price requires chemist's
    // purchase price, too.
    if ( s.PreisEKGrosso > pxConstants::mZero && s.PreisEKApo <= pxConstants::mZero )
          return ExternalError(CMsgStream(), CMSG_ITM_AEP_REQUIRED);

    // Chemist's purchase price must be > wholesale purchase price.
    if ( Session()->isBulgaria() || Session()->isSwitzerland() )
    {
        if ( s.PreisEKApo > pxConstants::mZero && s.PreisEKApo < s.PreisEKGrosso )
            return ExternalError(CMsgStream(), CMSG_ITM_AEP_NOTLESS_GEP);
    }
    else
    {
        if ( s.PreisEKApo > pxConstants::mZero && s.PreisEKApo <= s.PreisEKGrosso )
            return ExternalError(CMsgStream(), CMSG_ITM_AEP_NOTGT_GEP);
    }

    // For an automatic discount calculation, a price must be there
    // and a discount value may not be entered.
    if (s.Rabattfaehig)
    {
        if ( s.PreisEKApo <= pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_AEP_REQUIRED);
        if ( s.RabattFestDM > pxConstants::mZero || (s.RabattFest) )
            return ExternalError(CMsgStream(), CMSG_ITM_DSP_NOTDIS);
    }

    // Check direct discount percentage:
    if (s.RabattFest)
    {
        // Reject a direct money discount:
        if ( s.RabattFestDM > pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_DIS_OR_PERCENT);
        // Ensure discount percentage is within limits:
        if (s.RabattFest > cHIGHPERCENT)
            return ExternalError(CMsgStream(), CMSG_ITM_DSP_PERCENTHIGH);
        // For a sales rate calucation, both prices are required:
        if ( s.PreisEKApo <= pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_AEP_REQUIRED);
        if ( s.PreisEKGrosso <= pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_GEP_REQUIRED);
        // Ensure discount percentage does not exceed the sales rate percentage
        if ( s.RabattFest >= (double)(((s.PreisEKApo - s.PreisEKGrosso) * 100.0) / s.PreisEKApo) )
            return ExternalError(CMsgStream(), CMSG_ITM_DSP_PERCENTHIGH);
    }

    // Check direct money discount:
    if ( s.RabattFestDM > pxConstants::mZero )
    {
        // Reject a discount percentage
        if (s.RabattFest)
            return ExternalError(CMsgStream(), CMSG_ITM_DIS_OR_PERCENT);
        // At least the chemist's purchase price must be there
        if ( s.PreisEKApo <= pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_AEP_REQUIRED);
        // Ensure discount does'nt exceed sales rate
        if ( ((s.PreisEKApo - s.PreisEKGrosso) * (double)s.MengeBestellt) <= s.RabattFestDM )
            return ExternalError(CMsgStream(), CMSG_ITM_DSP_AMOUNTHIGH);
    }
    else
    // No discount values. If one price has been entered, the other
    // must be there.
    {
        if ( s.PreisEKApo > pxConstants::mZero && s.PreisEKGrosso <= pxConstants::mZero )
            return ExternalError(CMsgStream(), CMSG_ITM_GEP_REQUIRED);
    }

    return ErrorState();
}
