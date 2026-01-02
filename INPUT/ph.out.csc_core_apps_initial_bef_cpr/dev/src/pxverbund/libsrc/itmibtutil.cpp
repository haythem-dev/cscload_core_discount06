/* Zwecks Verbund neu */
#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxdirect.hpp"
#include "pxcstot.hpp"
#include "pxvartikellokal.hpp"
#include "pxvartikellokallist.hpp"
#include "pxstockbooking.hpp"
#include "pxitemattributes.hpp"
#include "tourinfo.hpp"
#include "pxbase/pxconstants.hpp"
#include "logger/loggerpool.h"
#include "tourassignmentutil.hpp"
#include "types/messagecodeenum.inc"
#include <ibt/ibtrequest/iibtrequest.h>


using pxVerbund::subsequentDelivery::pxDeliveryPos;

/*----------------------------------------------------------------------------*/
/*  get ibt quantity including quantities from linked positions               */
/*----------------------------------------------------------------------------*/
long pxOrderItem::TotalIBTQuantity()
{
    long retval = 0;

    // add ibt quantity from original item
    retval += MengeVerbund();

    // add ibt quantity from linked item
    if( this->LinkPosNr() > 0 )
    {
        pxOrderItem* linkeditem = NULL;
        if( (linkeditem = (pxOrderItem*)this->Order().ItemList()->At( this->LinkPosNr()-1 )) != NULL )
        {
            if( linkeditem->IsAuxPosted() )
            {
                retval += linkeditem->MengeVerbund();
            }
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  This function returns the quantity posted from that auxiliary stock.      */
/*----------------------------------------------------------------------------*/
long pxOrderItem::MengeVerbund()
{
    if (MengeVerbund_ > 0)                // if already exist in item object
    {
        return MengeVerbund_;
    }

    if ( IsAuxPosted() || IsDayNightMergePosition() )  // there should exist a deliverypos entry
    {
         libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
         if (NULL != ibtRequest.get())
         {
             MengeVerbund_ = ibtRequest->getQuantity();
         }
    }
    return MengeVerbund_;
}

/*----------------------------------------------------------------------------*/
/*  Construct a inter branch transfer  vartikellokal list                     */
/*----------------------------------------------------------------------------*/
pxVartikelLokalList* pxOrderItem::AuxStoreLocList()
{
    if ( AuxStoreLocList_ )             // vartikellokal list available
    {
        if ( AuxStoreLocList_->FindArticleNo(ArtikelNr_) )
        {
            return AuxStoreLocList_;
        }
        else
        {
            DeleteAuxStoreLocList();
        }
    }

    short custfil = Order().Customer()->FilialNr();
    Order().FilialNr();

    ClearError();

    AuxStoreLocList_ = new pxVartikelLokalList( Session(), Order().Param() );
    AuxStoreLocList_->getIBTWarehouseStockList( ArtikelNr_, custfil, Order().IDFNr(), &Order() );

    return AuxStoreLocList_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pointer to the ArtStoreLoc entry where to post    */
/*  from. If a deliverypos pointer exist, so the corresponding ArtStoreLoc    */
/*  entry will be manipulated depend on AuxFil.                               */
/*----------------------------------------------------------------------------*/
pxVartikelLokal* pxOrderItem::GetAuxStockEntry(const short AuxFil // auxilary company to post from
)
{
    pxVartikelLokal* oldstp;
    pxVartikelLokal* stp = NULL;

	libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
    if (NULL != ibtRequest.get())
    {
        stp = ((AuxFil > 0) ? AuxStoreLocList()->Find(AuxFil) : AuxStoreLocList()->Find(ibtRequest->getIbtBranchNo()));
        oldstp = AuxStoreLocList()->Find(ibtRequest->getIbtBranchNo());
        if (oldstp)
        {
            pxDirect direct(Session(), ibtRequest->getIbtBranchNo(), this);
            direct.UnBookIBT(ibtRequest->getQuantity(), 0);
        }
        else
        {
            stp = NULL;
        }
    }
    else
    {
        stp = AuxStoreLocList()->Find(AuxFil); // if new delivery-item
    }
    return stp;
}

/*----------------------------------------------------------------------------*/
/*  This function is called if an orderitem is canceled.                      */
/*  If a deliverypos exist,so the posted quantity is returned to the          */
/*  corresponding auxstock. The deliveryposentry is deleted                   */
/*----------------------------------------------------------------------------*/
int pxOrderItem::UndoAuxPosting()
{
    if (IsAuxPosted())
    {
        libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
        if (NULL != ibtRequest.get())
        {
            pxDirect direct(Session(), ibtRequest->getIbtBranchNo(), this);
            // TourManager - Verbundreservierung mit korrektem Kunden
            TourInfo* ibttourinfo = this->getItemTourInformation(true);
            if (NULL != ibttourinfo)
            {
                direct.UnBookIBT(ibtRequest->getQuantity(), ibttourinfo->getIBTCustomerNo());
            }
            else
            {
                // Logging!!!
                direct.UnBookIBT(ibtRequest->getQuantity(), 0);
            }
            delete AuxStoreLocList_;
            AuxStoreLocList_ = NULL;
        }
    }
    ClearAuxPosted();              // clear auxpos marker
    return ErrorState();

}

/*----------------------------------------------------------------------------*/
/*  Post quantities on the alternate delivery service                         */
/*  Use this member function only on a well constructed pxOrderItem object.   */
/*  QPostAux returns the quantity posted from the auxilary stock.             */
/*  In case of an error NULL is returned.                                     */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: QPostAux
(
    const  long           q,            // Quantity to post
    pxVartikelLokal*      stp           // entry where to post from
)
{
    pxDevice             *device = Session()->Device();
    long                 retval = 0L;    // return value
    const pxCustOrderType&     ot = Order().OrderType();
    nDate dateddel = Order().DatumAuslieferung();   // date delayeddelivery
    nDate now;

    //prevent booking if not allowed
    if (ot.IsAuxDelInhibit())
        return 0L;
    //prevent bad references
    if (!( AuxStoreLocList()->Entries() ) )   // if no article found
        return 0L;

    if ( !q )                             //  quantity must be > 0
        return 0L;

    if (stp == NULL)                      // prevent bad reference
        return 0L;

    // CR-13D047 TourManager mit Transportausschluss: Keine VB-Buchung wenn Transport nicht möglich!
    if( Order().getTourAssignmentUtil()->specialTourPossible(ArtBase_) )
    {
        if( false == Order().getTourAssignmentUtil()->isArticleDeliverableForIBT(stp->FilialNr(), ArtBase_ ) )
        {
            return 0L;
        }
        else
        {
            TourInfo ti = this->determineItemIBTTour( stp->FilialNr(), stp->getNLevelIBTTypeId() );
            if( !ti.getTourFound() )
            {
                return 0L;
            }
        }
    }

    long QInStock = Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_);
    // Implementation of ItemAttributes Class
    if ( ItemAttributes() )
    {
        if ( !ItemAttributes()->IsPartialDelivery() )
        {
            if ( (MengeBestellt_ - QInStock) > stp->Bestand() )
                return 0L;
        }
    }

    // check quantity in storelocentry, maybe the quantity was reduced
    // during this transaction.
    if ( stp->Bestand() >= q )       // Stock suffices wanted quantity
        retval = q;                   // auxdelivery quantity
    if ( stp->Bestand() < q && stp->Bestand() != 0L )
        retval = ( device->IsVideo() ? 0L : stp->Bestand() );

    if ( retval > 0L )                   // book now
    {
///// new for direct booking in auxcompany
        pxDirect direct(Session(), stp->FilialNr(), this);

        assignItemIBTTour(stp->FilialNr(), stp->getNLevelIBTTypeId());  // Verbundtour ermitteln
        this->SetIBTTypeID(stp->getNLevelIBTTypeId());

        // TourManager - Verbundreservierung mit korrektem Kunden
        TourInfo* ibttourinfo = this->getItemTourInformation(true);
        if (NULL != ibttourinfo)
        {
            retval = direct.BookIBT(retval, ibttourinfo->getIBTCustomerNo(), stp->getNLevelIBTTypeId());
        }
        else
        {
            // Logging!
            retval = direct.BookIBT(retval, 0, stp->getNLevelIBTTypeId());
        }

        if ( retval == 0L && device->IsVideo() && !direct.IsRemQuotaExeeded() )
        {
            VerbundFilialNr_ = stp->FilialNr();
        }

        if (retval > 0L)                      // achieved to book any ?
        {                                    // yes
                SetAuxPosted();                    // mark this item
                VerbundFilialNr_ = stp->FilialNr();  //delpos->FirstPartnerNr();
        }
        else
        if (!(device->IsVideo()))
        {
            // get next Store-entry that also would satisfy the ordered quantity
            pxVartikelLokal* nextstorep = AuxStoreLocList()->QSatisfy( retval, stp->FilialNr() );
            AuxStoreLocList()->Remove(stp);
            return QPostAux(q, /*dp,*/ nextstorep); // try the next stp
        }
    }
    else
    {
        retval  = 0L;                    // return value
    }

    return   retval;
}

/***************************************************************************************************************************/
long  pxOrderItem :: getIBTQuantityInStock( const long qty, const short ibtfil, const int flags)
{
    long QtyInStock = 0L;
    // SR-15067377 nicht weitermachen wenn Item schon nicht mehr GoodState ist
    if( !this->IsGoodState() )
    {
        return QtyInStock;
    }
    pxVartikelLokal*    stp = NULL;           // vartikel entry in list
    if ( !AuxDeliveryCheck( ibtfil, flags) )
    {
        if ( AuxStoreLocList()->Entries() )
        {
            stp = AuxStoreLocList()->QuantityInList(qty);
            if ( stp )
            {
                QtyInStock = stp->Bestand();
            }
        }
    }
    ClearError(); // SR-15067377 Item darf durch die Prüfung nicht !GoodState werden
    return QtyInStock;
}

/***************************************************************************************************************************/
void  pxOrderItem :: SetTourIdIBT( nString& tourid)
{
    TourIdIBT_.Strip();
    if ( TourIdIBT_.IsEmpty() )
    {
        TourIdIBT_ = tourid;
        SetDirty();
    }
}
