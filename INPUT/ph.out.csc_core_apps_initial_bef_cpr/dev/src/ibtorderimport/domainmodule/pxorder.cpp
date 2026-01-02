#include "pxorder.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtrequest/ibtrequest.h>
#include <ibt/ibtresponse/iibtresponse.h>
#include <ibt/ibtresponse/ibtresponse.h>
#include <ibt/ibtrequest/remark/iibtrequestremark.h>
#include <ibt/ibtrequest/remark/iibtrequestremarkptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremarklevelenum.h>
#include "pxvb_includes.h"
#include "pxorderitem.h"
#include "pxitemdiscount.h"
#include "ipxitemdiscountptr.h"
#include "pxkdauftragposinfo.hpp"
#include "pxorderremarks.hpp"
#include "types/origintypeenum.inc"
#include <exceptions/invaliddataexception.h>

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

PxOrder::PxOrder(const log4cplus::Logger& logger, ::pxOrder* order) :
    m_Logger(logger), m_pxOrder(order)
{
    METHODNAME_DEF( PxOrder, PxOrder )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

//-----------------------------------------------------------------------------------------

PxOrder::~PxOrder()
{
    METHODNAME_DEF( PxOrder, ~PxOrder )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

//-----------------------------------------------------------------------------------------

const log4cplus::Logger& PxOrder::getLogger()
{
    return m_Logger;
}

//-----------------------------------------------------------------------------------------

bool PxOrder::isBatchWriting() const
{
    return !(0 == m_pxOrder->BatchSchreiben());
}

//-----------------------------------------------------------------------------------------

void PxOrder::activateBatchWriting()
{
    m_pxOrder->BatchSchreiben(cORTYPE_AUXILIARY);
}

//-----------------------------------------------------------------------------------------

void PxOrder::determineIbtComment()
{
    if (m_pxOrder->France())
        m_pxOrder->Bemerkungen("COMMANDE SUIVRA");
    else
        m_pxOrder->Bemerkungen("VERBUND-AUFTRAG");
}

//-----------------------------------------------------------------------------------------

void PxOrder::setOriginBranchNo(const basar::Int16 branchNo)
{
    m_pxOrder->HerkunftFiliale(branchNo);
}

//-----------------------------------------------------------------------------------------

void PxOrder::setPaymentTerm(basar::VarString const& pTerm)
{
    nString term = pTerm.c_str();
    m_pxOrder->SetPaymentTerm(term);
}

//-----------------------------------------------------------------------------------------

void PxOrder::markAsNewSuivra()
{
    m_pxOrder->SetVerbundhausNewSuivra();
}

//-----------------------------------------------------------------------------------------

void PxOrder::setOrderType(libcsc::ibt::IIbtRequestPtr ibtRequest)
{
    nString oType = basar::VarString(ibtRequest->getOrderType()).c_str();

    m_pxOrder->OrderType(oType,
                        basar::VarString(ibtRequest->getPickingType()).at(0),
                        basar::VarString(ibtRequest->getBookingType()).at(0));
}

//-----------------------------------------------------------------------------------------

basar::Int32 PxOrder::getOrderNo()
{
    return m_pxOrder->KdAuftragNr();
}

//-----------------------------------------------------------------------------------------

IPxOrderItemPtr PxOrder::createNewOrderItem(const libcsc::ibt::IIbtRequestPtr ibtRequest)
{
    METHODNAME_DEF( PxOrder, createNewOrderItem )
    BLOG_TRACE_METHOD( getLogger(), fun );

    m_pxOrder->Session()->resetStockBooking();
    if ( basar::Decimal(0) < ibtRequest->getManualFixPrice() ) // PreisEKApoFree() != Nullm
    {
        return IPxOrderItemPtr ( new domMod::PxOrderItem(   getLogger(),
                                                    m_pxOrder->NewOrderItem_05( ibtRequest->getArticleNo(),
                                                                                ibtRequest->getQuantity(),
                                                                                0,                            //long        MengeNatra,
                                                                                ibtRequest->getQuantity(),    //long        MengeNachfrage,
                                                                                basar::Decimal(ibtRequest->getManualFixPrice()).toFloat64(),
                                                                                FREESALE_PRICE,
                                                                                pxOrderItem::BookingTypeDefault,
                                                                                pxOrderItem::TypeProductStocked,      // product identification mode
                                                                                bPOST_DEFAULT)));
    }
    else
    {
        return IPxOrderItemPtr ( new domMod::PxOrderItem(   getLogger(),
                                                    m_pxOrder->NewOrderItem_03( ibtRequest->getArticleNo(),
                                                                                ibtRequest->getQuantity(),
                                                                                0,                            //long        MengeNatra,
                                                                                ibtRequest->getQuantity(),    //long        MengeNachfrage,
                                                                                FREESALE_PRICE,
                                                                                pxOrderItem::BookingTypeDefault,
                                                                                pxOrderItem::TypeProductStocked,      // product identification mode
                                                                                bPOST_DEFAULT)));
    }
}

//-----------------------------------------------------------------------------------------

void PxOrder::addPositionDiscounts(const libcsc::ibt::IIbtRequestPtr ibtRequest, IPxOrderItemPtr item)
{
    // pro Position --> Übernahme discount = ibtrequest->getIbtDiscountRequestCollection()

    libcsc::ibt::IIbtRequestDiscountCollection::const_iterator it = ibtRequest->getDiscounts().begin();

    while (it != ibtRequest->getDiscounts().end())
    {
        nString pharmGrp = basar::VarString((*it)->getPharmacyGroupId()).c_str();

        // has still to be checked if this object is really written automatically to database at closure of order ...
        IPxItemDiscountPtr itemDisc ( new domMod::PxItemDiscount ( getLogger(),
                                                                    new ::pxItemDiscount(   m_pxOrder->Session(),
                                                                                            m_pxOrder->KdAuftragNr(),
                                                                                            item->getPxVbOrderItem()->PosNr(),
                                                                                            static_cast<short>((*it)->getDiscountType()),
                                                                                            pharmGrp )));

        itemDisc->setDiscountValuePct((*it)->getDiscountValuePct());
        itemDisc->setDiscountValuePctMan((*it)->getDiscountValuePctMan());
        itemDisc->setPaymentTargetNo((*it)->getPaymentTargetNo());
        itemDisc->setFixedPrice((*it)->getFixedPrice());
        if ((*it)->getFixedPrice() > basar::Decimal(0))
        {
            basar::Decimal nettopreis = basar::Decimal((*it)->getFixedPrice().toFloat64());
            item->getPxVbOrderItem()->SetPreisEKApoNetto((nMoney)nettopreis.toFloat64());
            item->getPxVbOrderItem()->SetNetPrice();
        }
        itemDisc->getPxVbItemDiscount()->Put();
        item->getPxVbOrderItem()->ItemDiscountList()->Append( itemDisc->getPxVbItemDiscount() );

        ++it;
    }
}

//-----------------------------------------------------------------------------------------

void PxOrder::addPositionRemark(const libcsc::ibt::IIbtRequestPtr ibtRequest, IPxOrderItemPtr item)
{
    libcsc::ibt::IIbtRequestRemarkCollection::const_iterator it = ibtRequest->getRemarks().begin();
    while( it != ibtRequest->getRemarks().end() )
    {
        const libcsc::ibt::IIbtRequestRemark & remark( *( *it ) );
        if ( remark.isHeadRemark() ) // --> only head remark should be written to ibt-pos !!!
        {
            item->setRemark( remark.getRemark() );
            BLOG_DEBUG( getLogger(), "head remark added to pxOrderItem." );
            break;
        }
        ++it;
    }

    it = ibtRequest->getRemarks().begin();
    ::pxGenericOrderRemarkList remarklist( m_pxOrder->Session() );
    while( it != ibtRequest->getRemarks().end() )
    {
        const libcsc::ibt::IIbtRequestRemark & remark( *( *it ) );
        if( remark.isPosRemark() )
        {
            remarklist.AddOrderRemark( item->getPxVbOrderItem()->KdAuftragNr(), item->getPxVbOrderItem()->PosNr(), remark.getRemarkType(), remark.getRemark() );
        }
        ++it;
    }
}

//-----------------------------------------------------------------------------------------

void PxOrder::copyTourDataFromOrigPos(const libcsc::ibt::IIbtRequestPtr ibtRequest, IPxOrderItemPtr item)
{
    // -- copy data from original order position
    basar::VarString dbName = m_pxOrder->Session()->getDatabaseName(ibtRequest->getBranchNo());

    pxKdauftragposInfo* origPos =
        new pxKdauftragposInfo (m_pxOrder->Session(),
                                ibtRequest->getCscOrderNo(),
                                ibtRequest->getCscOrderPosNo(),
                                dbName.c_str());
    if ( origPos->IsGoodState() )
    {
        item->setTourIdIbt( origPos->TourIdIBT() );
        item->setIbtTourWeekDay( origPos->IBTTourWeekDay() );
    }
    else
    {
        BLOG_WARN( getLogger(), "pxKdauftragposInfo NOT created properly!");
    }
    delete origPos;
}

//-----------------------------------------------------------------------------------------

IPxOrderItemPtr PxOrder::addPosition(const libcsc::ibt::IIbtRequestPtr ibtRequest)
{
    METHODNAME_DEF( PxOrder, addPosition )
    BLOG_TRACE_METHOD( getLogger(), fun );

    std::stringstream s;
    s << "trying to add new position for pxOrder= " << getOrderNo();
    BLOG_DEBUG(getLogger(), s.str());

    IPxOrderItemPtr item = createNewOrderItem(ibtRequest);

    if( false == item->getPxVbOrderItem()->IsGoodState() )
    {
        throw libutil::exceptions::InvalidDataException( basar::ExceptInfo( fun, "pxOrderItem could NOT be created!", __FILE__, __LINE__ ) );
    }

    s.str(std::string());
    s << "pxOrderItem with posnr < " << item->getPxVbOrderItem()->PosNr() << " > created successfully.";
    BLOG_DEBUG(getLogger(), s.str());

    addPositionRemark(ibtRequest, item);

    //item->setQtyBooked(ibtRequest->getQuantity()); // Sinn ??? - sollte hier nicht die tatsächlich gebuchte (statt der angeforderten) Menge gesetzt werden
    if (false == item->isCompleteOrderedQtyConfirmed())
    {
        BLOG_WARN( getLogger(), "delivered qty != ordered qty.");
    }

    item->markAsNonPharmosBatch();
    item->setCustomerOrderReference(ibtRequest->getCustOrderRef());
    item->setArticleCodeProperties(ibtRequest->getArticleCodeType(), ibtRequest->getArticleCode());

    if( m_pxOrder->Param()->IsNlevelIBT() )// nur für N-Level !!!
        item->setIbtType(ibtRequest->getNLevelIbtTypeId());

    copyTourDataFromOrigPos(ibtRequest, item);

    addPositionDiscounts(ibtRequest, item);

    return item;
}

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------
