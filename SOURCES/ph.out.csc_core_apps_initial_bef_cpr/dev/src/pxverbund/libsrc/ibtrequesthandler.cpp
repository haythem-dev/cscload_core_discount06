#include <libbasarcmnutil.h>
#include <logger/loggerpool.h>
#include "ibtrequesthandler.h"
#include <ibt/ibtrequest/iibtrequestrepository.h>
#include <ibt/ibtrequest/ibtrequestkey.h>
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtrequest/remark/iibtrequestremark.h>
#include <ibt/ibtrequest/discount/iibtrequestdiscount.h>
#include "error.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxitemdiscount.hpp"
#include "pxorderitemtour.hpp"
#include "pxorderremarks.hpp"
#include "tourutil.hpp"
#include "tourinfo.hpp"
#include "types/orderremarktypeenum.inc"

extern bool pxGlobalNoDatabaseWrite;

IbtRequestHandler::IbtRequestHandler()
{
}

IbtRequestHandler::~IbtRequestHandler()
{
}

void IbtRequestHandler::bookIbt(
    basar::Int16 const ibtBranchNo, pxOrderItem* item,
    basar::Int16 const nLevelIbtTypeId, basar::Long32 const ibtCustomerNo, basar::VarString const& custOrderRef, basar::Long32 const quantity)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerIbtRequest(), "IbtRequestHandler::bookIbt()" );

    libcsc::ibt::IIbtRequestPtr ibtRequest = item->Order().getIbtRequestRepository()->createRequest(
        libcsc::ibt::IbtRequestKey(
            item->Order().FilialNr(),
            item->Order().KdAuftragNr(),
            item->PosNr()
        )
    );
    ibtRequest->setIbtBranchNo(ibtBranchNo);
    ibtRequest->setIbtCustomerNo(ibtCustomerNo);
    ibtRequest->setCreationDateTime(basar::cmnutil::DateTime::getCurrent());
    ibtRequest->setProcessingState(libcsc::ibt::Open);
    ibtRequest->setCustomerNo(item->Order().IDFNr());
    ibtRequest->setOrderType("NO");
    ibtRequest->setPickingType("0");
    ibtRequest->setBookingType("0");
    ibtRequest->setArticleNo(item->ArtikelNr());
    ibtRequest->setArticleCodeType(item->CodeType());
    ibtRequest->setArticleCode(item->ArticleCode()());
    ibtRequest->setQuantity(quantity);
    ibtRequest->setCustomerTourId(item->getItemTourInformation(true)->getTourID()());
    ibtRequest->setTourWeekDay(static_cast<WeekDayEnum>(TourUtil::getWeekdayForDate(item->getItemTourInformation(true)->getTourDate().GetYYYYMMDD())));
    ibtRequest->setNLevelIbtTypeId(nLevelIbtTypeId);
    ibtRequest->setDayIbtFlag(item->IsDayIBT() ? 1 : 0);
    ibtRequest->setCustOrderRef(custOrderRef);
    ibtRequest->setManualFixPrice(basar::Decimal(item->PreisEKApoFree()));
    ibtRequest->setPaymentTerm(item->Order().PaymentTerm()());
    ibtRequest->setIbtTourId(item->getItemTourInformation(true)->getIBTTourID()());
    basar::Date ibtTourDate(item->getItemTourInformation(true)->getIBTTourDate().GetYYYYMMDD());
    ibtRequest->setIbtTourDate(ibtTourDate);

    // krükke kdauftrag.bemerkungen
    basar:: VarString bem = item->Order().Bemerkungen()();
    bem.trim();
    if (false == bem.empty())
    {
        libcsc::ibt::IIbtRequestRemarkPtr ibtRemarkRequest =
            ibtRequest->getRemark( libcsc::ibt::OrderHeadRemark, eUndefinedOrderRemarkType );
        ibtRemarkRequest->setRemark(bem);
    }

    // copy orderremarks to ibtremarkrequest
    pxGenericOrderRemarkList* orderRemarks = item->getGenericOrderRemarks();
    pxGenericOrderRemarkListIter iter = pxGenericOrderRemarkListIter(*orderRemarks);
    pxGenericOrderRemark* remark;
    while ( NULL != (remark = (pxGenericOrderRemark*)++iter) )
    {
        if (remark->RemarkType() == eOrderReferenceXML)
        {
            libcsc::ibt::IIbtRequestRemarkPtr ibtRemarkRequest =
                ibtRequest->getRemark( libcsc::ibt::OrderHeadRemark, eOrderReferenceXML );
            ibtRemarkRequest->setRemark(remark->RemarkText());
        }
        if (remark->RemarkType() == eOrderLineReferenceXML)
        {
            libcsc::ibt::IIbtRequestRemarkPtr ibtRemarkRequest =
                ibtRequest->getRemark( libcsc::ibt::OrderPosRemark, eOrderLineReferenceXML );
            ibtRemarkRequest->setRemark(remark->RemarkText());
        }
        if (remark->RemarkType() == eTenderNo)
        {
            libcsc::ibt::IIbtRequestRemarkPtr ibtRemarkRequest =
                ibtRequest->getRemark( libcsc::ibt::OrderPosRemark, eTenderNo );
            ibtRemarkRequest->setRemark(remark->RemarkText());
        }
    }

    item->setIbtRequest(ibtRequest);
    item->Order().getIbtRequestRepository()->saveIbtRequest(ibtRequest);
}

void IbtRequestHandler::unbookIbt(basar::Int16 const /*ibtBranchNo*/, pxOrderItem* item)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerIbtRequest(), "IbtRequestHandler::unbookIbt()" );

    libcsc::ibt::IIbtRequestPtr ibtRequest = item->getIbtRequest();
    if( NULL == ibtRequest.get() )
    {
        ibtRequest = item->getOrder()->getIbtRequestRepository()->findIbtRequestByKey(
            libcsc::ibt::IbtRequestKey(
                item->getOrder()->FilialNr(),
                item->KdAuftragNr(),
                item->PosNr()
            )
        );

        if( ibtRequest->getIbtRequestId().isUnset() )
        {
            std::stringstream ss;
            ss << "IbtRequestHandler::unbookIbt(): ibtRequest is UNSET, but should exist! BranchNo=<"
                << item->getOrder()->FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
            BLOG_ERROR( libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
            item->setIbtRequest( libcsc::ibt::IIbtRequestPtr() );
            return;
        }
        item->setIbtRequest( ibtRequest );
    }

    item->Order().getIbtRequestRepository()->deleteIbtRequest( ibtRequest );
    item->setIbtRequest( libcsc::ibt::IIbtRequestPtr() );
}

void IbtRequestHandler::readAllIbtRequests(pxOrder* order)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerIbtRequest(), "IbtRequestHandler::readAllIbtRequests()" );

    pxOrderItemListIter it(*order->ItemList());
    pxOrderItem *item = NULL;
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (false == item->IsAuxPosted())
        {
            continue;
        }
        libcsc::ibt::IIbtRequestPtr ibtRequest = order->getIbtRequestRepository()->findIbtRequestByKey(
            libcsc::ibt::IbtRequestKey(
                order->FilialNr(),
                order->KdAuftragNr(),
                item->PosNr()
            )
        );

        if( ibtRequest->getIbtRequestId().isUnset() )
        {
            std::stringstream ss;
            ss << "IbtRequestHandler::readAllIbtRequests(): ibtRequest is UNSET, but should exist! BranchNo=<"
                << order->FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
            BLOG_ERROR( libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
            item->setIbtRequest( libcsc::ibt::IIbtRequestPtr() );
            continue;
        }
        item->setIbtRequest( ibtRequest );
    }
}

void IbtRequestHandler::readIbtRequest(pxOrder* order, pxOrderItem* item)
{
    if (false == item->IsAuxPosted())
    {
        return;
    }
    libcsc::ibt::IIbtRequestPtr ibtRequest = order->getIbtRequestRepository()->findIbtRequestByKey(
        libcsc::ibt::IbtRequestKey(
            order->FilialNr(),
            order->KdAuftragNr(),
            item->PosNr()
        )
    );

    if (ibtRequest->getIbtRequestId().isUnset())
    {
        std::stringstream ss;
        ss << "IbtRequestHandler::readAllIbtRequests(): ibtRequest is UNSET, but should exist! BranchNo=<"
            << order->FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
        BLOG_ERROR(libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str());
        item->setIbtRequest(libcsc::ibt::IIbtRequestPtr());
        return;
    }
    item->setIbtRequest(ibtRequest);
}

void IbtRequestHandler::closeAllIbtRequests(pxOrder* order)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerIbtRequest(), "IbtRequestHandler::closeAllIbtRequests()" );

    // CreMa: Bei ZU und Kreditlimitüberschreitung Verbund nicht abschliessen!!!
    if (order->IsEntryDeferred() && order->IsKreditLimitErreicht() && order->Param()->IsSCrema())
        return;

    if (order->IsEntryClosed() ||                                           // order closed
        (order->IsEntryDeferred() && order->closeIBTAtOnce() && !order->IsProblemClearance()))  // order deferred and param set "close immediately"
    {
        pxOrderItemListIter it(*order->ItemList());
        pxOrderItem *item = NULL;
        while ((item = (pxOrderItem*) ++it) != NULL)
        {
            if (false == item->IsAuxPosted())
            {
                continue;
            }
            libcsc::ibt::IIbtRequestPtr ibtRequest = item->getIbtRequest();
            if( NULL == ibtRequest.get() )
            {
                ibtRequest = order->getIbtRequestRepository()->findIbtRequestByKey(
                    libcsc::ibt::IbtRequestKey(
                        order->FilialNr(),
                        order->KdAuftragNr(),
                        item->PosNr()
                    )
                );

                if( ibtRequest->getIbtRequestId().isUnset() )
                {
                    std::stringstream ss;
                    ss << "IbtRequestHandler::closeAllIbtRequests(): ibtRequest is UNSET, but should exist! BranchNo=<"
                        << order->FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
                    BLOG_ERROR( libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
                    continue;
                }
                item->setIbtRequest( ibtRequest );
            }

            if( libcsc::ibt::Open == ibtRequest->getProcessingState() )
            {
                ibtRequest->setProcessingState( libcsc::ibt::ReadyForProcessing );		
			//} I-23056497 this closing brace we moved down to fix France incident
				//for verbund article with discount, kdauftragposrab disc type is diff then ibtdiscountrequest the insert fails
				//as it tries to insert on existing ibtrequestid with diffrent discounttype into table ibtdiscountrequest.
				
				// check for discounts (TODO: only in FR / PFR???)
				pxItemDiscount* itemdisc = item->ItemDiscountList()->FindDiscountValuePct();
				if (NULL != itemdisc)
				{
					libcsc::ibt::IIbtRequestDiscountPtr ibtRequestDiscount = ibtRequest->getDiscount(
						static_cast<libcsc::ibt::IbtRequestDiscountTypeEnum>( itemdisc->DiscountType() ), itemdisc->PaymentTargetNo() );
					ibtRequestDiscount->setDiscountValuePct(basar::Decimal(itemdisc->DiscountValuePct()));
					ibtRequestDiscount->setDiscountValuePctMan(basar::Decimal(itemdisc->DiscountValPctMan()));
					ibtRequestDiscount->setPharmacyGroupId(itemdisc->PharmacyGroupId()());
					ibtRequestDiscount->setFixedPrice(basar::Decimal (itemdisc->FixedPrice()));
				}
				else
				{
					itemdisc = item->ItemDiscountList()->FindFixedPrice();
					if (NULL != itemdisc)
					{
						libcsc::ibt::IIbtRequestDiscountPtr ibtRequestDiscount = ibtRequest->getDiscount(
							static_cast<libcsc::ibt::IbtRequestDiscountTypeEnum>(itemdisc->DiscountType()), itemdisc->PaymentTargetNo());
						ibtRequestDiscount->setDiscountValuePct(basar::Decimal(itemdisc->DiscountValuePct()));
						ibtRequestDiscount->setDiscountValuePctMan(basar::Decimal(itemdisc->DiscountValPctMan()));
						ibtRequestDiscount->setPharmacyGroupId(itemdisc->PharmacyGroupId()());
						ibtRequestDiscount->setFixedPrice(basar::Decimal(itemdisc->FixedPrice()));
					}
				}
			} //Begin I-23056497 for verbund art with disc, kdauftragposrab disc type is diff then ibtdiscountrequest the insert fails
			
			try 
			{
				order->getIbtRequestRepository()->saveIbtRequest(ibtRequest);
			}
			catch (const basar::Exception& e)
            {
                std::stringstream ss;
                ss << "IbtRequestRepository::saveIbtRequest(): " << e.what().c_str();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str());
            } //end I-23056497 we add try catch as the call to saveIbtRequest does a throw in case of failure we are handling it here
        }
    }
}

void IbtRequestHandler::setArticleCodeValues(pxOrderItem* item, basar::Int16 const articleCodeType, basar::VarString const& articleCode)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerIbtRequest(), "IbtRequestHandler::setArticleCodeValues()" );

    if (false == item->IsAuxPosted())
        return;

    libcsc::ibt::IIbtRequestPtr ibtRequest = item->getIbtRequest();
    if( NULL == ibtRequest.get() )
    {
        ibtRequest = item->getOrder()->getIbtRequestRepository()->findIbtRequestByKey(
            libcsc::ibt::IbtRequestKey(
                item->getOrder()->FilialNr(),
                item->KdAuftragNr(),
                item->PosNr()
            )
        );

        if( ibtRequest->getIbtRequestId().isUnset() )
        {
            std::stringstream ss;
            ss << "IbtRequestHandler::setArticleCodeValues(): ibtRequest is UNSET, but should exist! BranchNo=<"
                << item->getOrder()->FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
            BLOG_ERROR( libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
            return;
        }
        item->setIbtRequest( ibtRequest );
    }

    ibtRequest->setArticleCodeType(articleCodeType);
    ibtRequest->setArticleCode(articleCode);
    item->Order().getIbtRequestRepository()->saveIbtRequest(ibtRequest);
}

