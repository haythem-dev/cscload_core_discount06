#include "pxitem.hpp"
#include <date.hpp>
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxdelpos.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "ibtbrancheslist.hpp"
#include "ibtbranches.hpp"
#include "ibtbrancharticleconfig.h"
#include "ibtassortmenttype.h"
#include "pxoeparm.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
int pxOrderItem::CheckPossibilityForIBTDelivery( short ibtbranchno /*AuxFil*/, int flags, BookingType btype /*= BookingTypeDefault*/ )
{
    // check if customer generally accepts interbranch delivery
    if( !Session()->Device()->IsVideo() )
    {
        if( !(ArtBase_->IsPrivatProductRange()) && this->Order().Customer()->IsNeverAuxDeliveryUser() )
        {
            return CMSG_AD_NOTPOSSIBLE;
        }
    }

    // check if interbranch transfer is allowed for order type of order
    if( this->Order().OrderType().IsAuxDelInhibit() )
    {
        return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
    }

    IBTBranchesList ibtbrancheslist(Session());


    if( this->Order().Param()->IsNlevelIBT() )
    {
        ibtbrancheslist.getIBTBranchesByArticleNoForNLevelIBT( this->Order().FilialNr(), ibtbranchno, this->ArtBase()->ArtikelNr() );
    }
    else
    {
        ibtbrancheslist.getIBTBranchesByIBTType( this->Order().FilialNr(), ibtbranchno, IBTBranchesList::getIBTProductValue( this->ArtBase()->VerbundArtikel() ) );
    }

    // no ibt if there are no ibt branches configured
    if( 0 == ibtbrancheslist.Entries() )
    {
        return CMSG_AD_NOTPOSSIBLE;
        //return ExternalError( CMsgStream(), CMSG_AD_CMP_NOTIN, ibtbranchno );
    }

    // if method is called without ibtbranchno, use the first one configured in ibtbranches where ibt is possible now
    if( ibtbranchno <= 0 )
    {
        for( size_t i = 0; i < ibtbrancheslist.Entries(); ++i )
        {
            IBTBranches* ib = (IBTBranches*)ibtbrancheslist.At(i);
            ibtbranchno = ib->getIBTBranchNo();
            if( ibtbrancheslist.isIBTPossibleNow( this->Order().FilialNr(), ibtbranchno ) )
            {
                break;
            }
        }
    }

    // we jump out for nlevel IBT
    if ( this->Order().Param()->IsNlevelIBT() )
    {
        return checkPossibilityForNlevelIBTDelivery( ibtbrancheslist, ibtbranchno, flags, btype );
    }

    if( !Session()->Device()->IsVideo() ) // checks for devices without active user (NON VIDEO)
    {
        // artikel->Prisoart = 0 oder 3
        if( !(ArtBase_->IsPrivatProductRange() ) && !( ArtBase_->IsAuxStockProductRegional()) )
        {
            if( !(ArtBase_->IsAuxStockProduct()) ) // artikel->verbundartikel != 1
            {
               return CMSG_AD_ART_NOTIN;
            }
            return  CheckPossibilityForIBTDeliveryCommonNonVideo( flags, btype );

        }
    }
    else // checks for devices with active user
    {
        if ( !(ArtBase_->IsPrivatProductRange()) && !(ArtBase_->IsAuxStockProductRegional()) ) // artikel->Prisoart = 0
        {
            if ( !(ArtBase_->IsAuxStockProductAnyway()) ) // artikel->Verbundartikel = 0 // NOT FOR NLEVELIBT
            {
               return ExternalError( CMsgStream(), CMSG_AD_ART_NOTIN, ArtikelNr_ );
            }

            // kunde->Verbundkunde = 0
            if( !(Order().Customer()->IsAuxDeliveryAllowed())
                && !(Order().Customer()->IsUnusualAuxDeliveryUser()) )
            {
                return ExternalError( CMsgStream(), CMSG_AD_CST_NOTIN,Order().IDFNr() );
            }
        }

        if( !IsAuxPosted() )
        {
            if( !ibtbrancheslist.isIBTPossibleNow( this->Order().FilialNr(), ibtbranchno ) )
            {
                return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
            }
        }
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
int pxOrderItem::CheckPossibilityForIBTDeliveryCommonNonVideo( int flags, BookingType btype )
{
    int retval = 0;

    if( Order().Customer()->IsAuxDeliveryUser() && Order().Customer()->Flags().IsVerbundGanz() ) // kunde->verbundkunde = 1 und kunde = Ganztagsverbund
    {
       return retval;
    }

    if( (Order().Customer()->IsAuxDeliveryUser()) && (!Order().Customer()->CustTimeList()) ) // kunde->verbundkunde = 1 und keine Zeitliste
    {
       return retval =  CMSG_AD_NOTPOSSIBLE;
    }

    if (Session()->isFrance())
    {
       // kunde->verbundkunde = 1 oder 4
       if( (Order().Customer()->IsAuxDeliveryUser() || Order().Customer()->IsUnusualAuxDeliveryUser())
                    && !( Order().Customer()->Flags().IsVerbundGanz() )
                    && !( Order().Customer()->CustTimeList()->TimeInWindow() )
                    && !( flags & bPOST_AUXDELIVERY ) )
       {
          return retval = CMSG_AD_NOTPOSSIBLE;
       }
    }

    // kunde->verbundkunde = 1 oder 4
    if( ( Order().Customer()->IsAuxDeliveryUser() || Order().Customer()->IsUnusualAuxDeliveryUser() )
        && !( Order().Customer()->Flags().IsVerbundGanz() )
        && !( Order().Customer()->CustTimeList()->TimeInWindow() )
        && !(flags & bPOST_AUXDELIVERY) )
    {
        SetAuxPostPossible();
    }
    else if( Order().Customer()->IsNotAuxDeliveryUser() )
    {
        return retval = CMSG_AD_NOTPOSSIBLE;
    }
    else if( (Order().Customer()->IsAuxDeliveryInfoUser()) && !(flags & bPOST_AUXDELIVERY) ) // kunde->verbundkunde = 5
    {
        SetAuxPostPossible();
    }
    else if( (Order().Customer()->IsSpecialAuxDeliveryUser()) && !((flags & bPOST_AUXDELIVERY) || btype == PurchaseOrder || btype == RestDelivery)) // kunde->verbundkunde = 3
    {
        return retval = CMSG_AD_NOTPOSSIBLE;
    }

    if( Order().Austria() && IsAuxPostPossible() )
    {
        if( Order().Customer()->IsGeneralRestDeliveryUser() )
        {
            ClearAuxPostPossible();
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
int pxOrderItem::checkPossibilityForNlevelIBTDelivery(IBTBranchesList& ibtbrancheslist, short ibtbranchno, int flags, BookingType btype )
{
    int retval = 0;
    bool   ibtcustomersonly = false;
    bool   ibtperiodneeded = false;
    IBTAssortmentType* assortmenttyp = NULL;
    IBTAssortmentTypeList* ibtassortmenttypelist = NULL;

    if ( ArtBase_->getIBTBranchArticleConfigPtr() )
    {
        ibtassortmenttypelist = Session()->getIBTAssortmentTypeList();
        if ( ibtassortmenttypelist )
        {
            assortmenttyp = ibtassortmenttypelist->Find(ArtBase_->getIBTBranchArticleConfigPtr()->getIBTAssortmentTypeID());
            if ( assortmenttyp )
            {
                ibtcustomersonly    = assortmenttyp->isIBTCustomersOnly();
                ibtperiodneeded     = assortmenttyp->isIBTPeriodNeeded();
            }
            else
            {
                return retval;
            }
        }
    }

    if ( !Session()->Device()->IsVideo() ) // checks for devices without active user (NON VIDEO)
    {
        retval = checkPossibilityForNlevelNonVideo( ibtcustomersonly, ibtperiodneeded, flags,  btype );
    }
    else
    {
        retval = checkPossibilityForNlevelVideo(&ibtbrancheslist, ibtbranchno, ibtcustomersonly, ibtperiodneeded );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
int pxOrderItem::checkPossibilityForNlevelNonVideo( bool ibtcustomersonly, bool ibtperiodneeded, int flags, BookingType btype )
{
    int retval = 0;

    // now do check depend on ibtcustomersonly and ibtperiodneeded
    if ( ibtcustomersonly == false && ibtperiodneeded == false )        // no further checks needed
    {
        return retval;
    }
    if ( ibtcustomersonly == true && ibtperiodneeded == true )          // customer and timelist check.
    {
        return CheckPossibilityForIBTDeliveryCommonNonVideo(  flags,  btype );
    }
    if ( ibtcustomersonly == true && ibtperiodneeded == false )         // only customer without timelist check.
    {
        return checkPossibilityForNlevelCustomersOnly(  flags,  btype );
    }
    if ( ibtcustomersonly == false && ibtperiodneeded == true )         // only  timelist check.
    {
        return checkPossibilityForNlevelPeriodNeeded();
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
int pxOrderItem::checkPossibilityForNlevelVideo(IBTBranchesList* ibtbrancheslist, short ibtbranchno, bool ibtcustomersonly, bool ibtperiodneeded )
{
    int retval = 0;

    // now do check depend on ibtcustomersonly and ibtperiodneeded
    if ( ibtcustomersonly == false && ibtperiodneeded == false )        // no further checks needed
    {
        return retval;
    }

    if ( (ibtcustomersonly == true && ibtperiodneeded == true) ||
         (ibtcustomersonly == true && ibtperiodneeded == false) ||
         (ibtcustomersonly == false && ibtperiodneeded == true))
    {
        // kunde->Verbundkunde = 0
        if( !(Order().Customer()->IsAuxDeliveryAllowed()) && !(Order().Customer()->IsUnusualAuxDeliveryUser()) )
        {
           return ExternalError( CMsgStream(), CMSG_AD_CST_NOTIN,Order().IDFNr() );
        }
        if( !IsAuxPosted() )
        {
            if( !ibtbrancheslist->isIBTPossibleNow( this->Order().FilialNr(), ibtbranchno ) )
            {
                return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
            }
        }

    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Just switch Verbundkunde check, No timelist check                         */
/*----------------------------------------------------------------------------*/
int pxOrderItem::checkPossibilityForNlevelCustomersOnly( int flags, BookingType btype )
{
    int retval = 0;

    if( Order().Customer()->IsAuxDeliveryUser() )     // kunde->verbundkunde = 1
    {
       return retval;
    }

    if (Session()->isFrance())
    {
       // kunde->verbundkunde = 1 oder 4
       if( (Order().Customer()->IsAuxDeliveryUser() || Order().Customer()->IsUnusualAuxDeliveryUser()) )
       {
          return retval;
       }
    }

    if ( Order().Customer()->IsNotAuxDeliveryUser() )
    {
        return retval = CMSG_AD_NOTPOSSIBLE;
    }
    else if( (Order().Customer()->IsAuxDeliveryInfoUser()) && !(flags & bPOST_AUXDELIVERY) ) // kunde->verbundkunde = 5
    {
        SetAuxPostPossible();
    }
    else if( (Order().Customer()->IsSpecialAuxDeliveryUser()) && !((flags & bPOST_AUXDELIVERY) || btype == PurchaseOrder || btype == RestDelivery)) // kunde->verbundkunde = 3
    {
        return retval = CMSG_AD_NOTPOSSIBLE;
    }

    if( Order().Austria() && IsAuxPostPossible() )
    {
        if( Order().Customer()->IsGeneralRestDeliveryUser() )
        {
            ClearAuxPostPossible();
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Just  timelist check                                                      */
/*----------------------------------------------------------------------------*/
int pxOrderItem::checkPossibilityForNlevelPeriodNeeded()
{
    int retval = 0;

    if ( Order().Customer()->Flags().IsVerbundGanz() ) //  kunde = Ganztagsverbund
    {
       return retval;
    }

    if (!Order().Customer()->CustTimeList() )           // kunde hat keine Zeitliste
    {
       return retval =  CMSG_AD_NOTPOSSIBLE;
    }

    if ( !Order().Customer()->CustTimeList()->TimeInWindow() )
    {
        return retval = CMSG_AD_NOTPOSSIBLE;
    }

    return retval;
}
