#include "pxdirect.hpp"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"
#include "pxartrem.hpp"
#include "pxoeparm.hpp"
#include "pxbranch.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxstockbooking.hpp"
#include "pxarticlequota.hpp"
#include "types/messagecodeenum.inc"
#include <base/irunnable.h>
#include <ibt/ibtrequest/ibtrequest.h>

/*----------------------------------------------------------------------------*/
/*  Constructor for direct booking object                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxDirect :: pxDirect
(
    pxSession* session,
    short     filiale,
    pxOrderItem* item
)
{
    Session_   = session;
    FilialNr_  = filiale;
    Item_      = item;

    RemQuotaExeeded_ = false;
}

/*----------------------------------------------------------------------------*/
/*  Destructor  for direct booking object                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxDirect :: ~pxDirect
()
{
}

/*----------------------------------------------------------------------------*/
/*  UnBook the remote article                                                 */
/*----------------------------------------------------------------------------*/
void pxDirect :: UnBookIBT(const long Menge, const long IBTCustomerNo)
{
    long retval = 0;
    pxOrder& order = Item_->Order();

    // TourManager - Verbundreservierung mit korrektem Kunden
    long remoteCustomerNo = IBTCustomerNo; // use customer from tour determination
    if (order.Param()->IsSIbtCstOrg())
    {
        remoteCustomerNo = order.Customer()->IDFNr();  // use original customer
    }
    libcsc::ibt::IIbtRequestPtr ibtRequest = Item_->getIbtRequest();
    if ( NULL != ibtRequest.get() )
    {
        remoteCustomerNo = ibtRequest->getIbtCustomerNo();
    }

    retval = Session_->getStockBooking()->CancelReservationForIBT(Item_->ArtBase()->ArtikelNr(), remoteCustomerNo, FilialNr_, Menge);
    if (!Session_->getStockBooking()->IsGoodState())
    {
        Error() = Session_->getStockBooking()->Error();
        return;
    }

    UndoRemArtQuota(retval);  // return interchange Customers Quota

    try
    {
        Item_->Order().getIbtRequestHandler().unbookIbt(FilialNr_, Item_);
    }
    catch (nError& err)
    {
        Error() = err;
    }
}

/*----------------------------------------------------------------------------*/
/*  Book the remote article                                                   */
/*----------------------------------------------------------------------------*/
long pxDirect::BookIBT(const long Menge, const long IBTCustomerNo, const short nleveltypeid /*= 0*/)
{
    long retQty = Menge;
    pxOrder& order = Item_->Order();
    nString KdAuftragBestellNr;

    pxArtRemote Rartikel_(Session_, Item_->ArtikelNr(), FilialNr_, cDBGET_READONLY);
    if (false == Rartikel_.IsGoodState())
    {
        ExternalCondition(Session_->CMsgStream(), CMSG_DA_ART_NOTIN, Item_->ArtikelNr(), FilialNr_);
        return 0L;
    }

    if (Rartikel_.IsNotSaleable() || Rartikel_.IsStopSelling())        // Artikelaktiv = 0   oder Artikelaktiv > 2
    {
        return 0L;
    }

    if ( order.Customer()->Flags().IsVersandApo() && order.Customer()->Flags().IsBaAuftrag() )
    {
        KdAuftragBestellNr.Clear();
        if( !order.ReferenceNr().IsEmpty() )
        {
            KdAuftragBestellNr = order.ReferenceNr();
        }
    }

    retQty = CheckRemArtQuota(retQty);           // check ArticleQuota for interchange CustomerNo
    if (retQty == 0)                             // Quota exceeded
        return retQty;                           // do not book this Product

    long remoteCustomerNo = order.Customer()->IDFNr();
    if (!order.Param()->IsSIbtCstOrg())
    {
        remoteCustomerNo = Session_->Branch()->BGANr_EK();
    }

    // TourManager - Verbundreservierung mit korrektem Kunden
    if( IBTCustomerNo > 0 )
    {
        remoteCustomerNo = IBTCustomerNo;
        if(order.Param()->IsSIbtCstOrg())
        {
            remoteCustomerNo = order.Customer()->IDFNr();
        }
    }

    retQty = Session_->getStockBooking()->AddReservationForIBT(Item_->ArtBase()->ArtikelNr(), remoteCustomerNo, FilialNr_, retQty);
    if (!Session_->getStockBooking()->IsGoodState())
    {
        Error() = Session_->getStockBooking()->Error();
        return 0;
    }

    // now creating the aux info on remote database
    try
    {
        Item_->Order().getIbtRequestHandler().bookIbt(FilialNr_, Item_, nleveltypeid, remoteCustomerNo, KdAuftragBestellNr(), retQty);
    }
    catch (nError& err)
    {
        Error() = err;
        return 0;
    }

    return retQty;
}

/*----------------------------------------------------------------------------*/
/*  CheckRemArtQuota: this methode looks for interchange Customers article    */
/*  Quota entry for the just ordered Product.                                 */
/*  Returnvalues:    0    = if Quota exceeds,                                 */
/*                   Qty  = if Quota fits                                     */
/*                   Rest = Qty - Rest of Quota                               */
/*----------------------------------------------------------------------------*/
long
pxDirect :: CheckRemArtQuota
(
    const long Qty
)
{
    long retval = Qty;                     //  return value
    long rest   = 0;
    long BGANr  = Item_->Session()->Branch()->BGANr_EK();
    pxArticleQuota RemArtQuota(Session_, FilialNr_, BGANr, Item_->ArtikelNr());
    if (RemArtQuota.FindQuotaEntry(cDBGET_FORUPDATE))  //  get and lock it from the database
    {
        return retval;               // nothing to do
    }

    // now do inventory update on RemArtQuota_
    rest = RemArtQuota.Quota() - RemArtQuota.KumQty();
    rest = ((rest < 0) ? 0 : rest);
    retval = ((rest >= retval) ? retval : rest );
    RemArtQuota.AddQuantity(retval);
    RemArtQuota.Put();
    if ( retval == 0 )               // quota exeeded
    {
        RemQuotaExeeded_ = true;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  UnodRemArtQuota: this methode returns the booked quanty(Qty) to the       */
/*  interchange customers ArticleQuota entry.                                 */
/*----------------------------------------------------------------------------*/
void
pxDirect :: UndoRemArtQuota
(
    const long Qty
)
{
    long BGANr  = Item_->Session()->Branch()->BGANr_EK();
    pxArticleQuota RemArtQuota(Session_, FilialNr_, BGANr, Item_->ArtikelNr());
    if (RemArtQuota.FindQuotaEntry(cDBGET_FORUPDATE))  //  get and lock it from the database
    {
        return;               // nothing to do
    }
    // now do inventory update on RemArtQuota_
    RemArtQuota.SubQuantity(Qty);
    RemArtQuota.Put();
}
