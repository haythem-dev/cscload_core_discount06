#include "deliverynotecompleteduc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <document/componentmanager/documentcomponentmanager.h>
#include "document/deliveryadvice/deliveryadvice.h"
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetailsptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetails.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinkptr.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlink.h>
#include "document/deliveryadvice/deliveryadviceinformationfilter.h"
#include <document/deliveryadvice/deliveryadvicerepositoryptr.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecompleted/ideliverynotecompleted.h>
#include <exceptions/cscexceptionbase.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_logging.h>
#include <libutil/util.h>
#include <cscorder/componentmanager/cscordercomponentmanager.h>
#include <cscorder/cscorderflags/icscorderflagsrepositoryptr.h>
#include <cscorder/cscorderflags/icscorderflagsrepository.h>
#include <cscorder/cscorderflags/cscorderflags.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepositoryptr.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepository.h>
#include <cscorder/cscorderibtpickingdata/cscorderibtpickingdata.h>
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/ibtbranch/iibtbranchrepositoryptr.h>
#include <ibt/ibtbranch/iibtbranchrepository.h>
#include <ibt/ibtbranch/iibtbranchsetting.h>
#include <ibt/ibtbranch/iibtbranchsettingcollection.h>
#include <pxxmit.hpp>
#include <pxitem.hpp>
#include <set>



namespace csc_phadex {
namespace useCase {


DeliveryNoteCompletedUC::DeliveryNoteCompletedUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, DeliveryNoteCompletedUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

DeliveryNoteCompletedUC::~DeliveryNoteCompletedUC()
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, ~DeliveryNoteCompletedUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void DeliveryNoteCompletedUC::setDeliveryNoteCompletedRecord(csc_phadex::domMod::phadexTransaction::IDeliveryNoteCompletedPtr dncr )
{
    m_DeliveryNoteCompletedRecord = dncr;
}

void DeliveryNoteCompletedUC::injectPxOrderTransmit( pxOrderTransmitPtr xmit )
{
    m_pxOrderTransmit = xmit;
}

void DeliveryNoteCompletedUC::run()
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

    switch (m_DeliveryNoteCompletedRecord->getMode()) // 0=KUNDEN-, 1=SHUTTLE-AUFTRAG
    {
        case 0: // TODO enum
            completeCustomerOrder();
            break;
        case 1:
            completeShuttleOrder();
            break;
        default:
            break;
    }
}

void DeliveryNoteCompletedUC::completeCustomerOrder()
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, completeCustomerOrder );
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
        libcsc::document::DeliveryAdviceRepositoryPtr deliveryAdviceRepository =
            m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

        libcsc::document::DeliveryAdviceLineIbtLinkCollectionPtr deliveryAdviceLineIbtLinks =
            deliveryAdviceRepository->findShuttleOrders(
                m_DeliveryNoteCompletedRecord->getBranchno(),
                m_DeliveryNoteCompletedRecord->getCustomerNo(),
                m_DeliveryNoteCompletedRecord->getCscOrderNo());

        libcsc::document::DeliveryAdviceLineIbtLinkCollection::iterator iter;
        for (iter = deliveryAdviceLineIbtLinks->begin(); iter != deliveryAdviceLineIbtLinks->end(); ++iter)
        {
            libcsc::Date deliveryAdviceDate(basar::cmnutil::Date::getCurrent().getDate());
            (*iter)->setDeliveryAdviceDate(deliveryAdviceDate);

            basar::VarString invoiceNoTrimmed = m_DeliveryNoteCompletedRecord->getInvoiceNo();
            invoiceNoTrimmed.trim(basar::VarString::FIRST_END); // remove leading/trailing blanks
            invoiceNoTrimmed.erase(0, std::min(invoiceNoTrimmed.find_first_not_of('0'), invoiceNoTrimmed.size() - 1)); // remove leading zeroes
            (*iter)->setDeliveryAdviceNo(invoiceNoTrimmed);

			if (false == deliveryAdviceRepository->findShuttleOrderDetails(*iter))
			{
				// This position is not part of the shuttle order
				// TODO FN logging
				continue;
			}
			if (false == deliveryAdviceRepository->findDeliveryAdviceDetails4CustomerOrder(*iter))
			{
				// TODO FN logging
				continue;
			}
			if (false == deliveryAdviceRepository->findDeliveryAdviceDetails4ShuttleOrder(*iter))
            {
                // or delivery advices are not yet existing
				// TODO FN logging
				continue;
            }
            deliveryAdviceRepository->saveDeliveryAdviceLineIbtLink(*iter);

            checkCustomerOrderForCompletion(*iter);
        }
    }
    catch (const libcsc::exceptions::CSCExceptionBase& e)
    {
        std::stringstream ss;
        ss << "DeliveryNoteCompletedUC::completeCustomerOrder(): Error during calculation: " << e.reason().c_str();
        BLOG_ERROR(LoggerPool::getLoggerUseCases(), ss.str());
    }
}

void DeliveryNoteCompletedUC::completeShuttleOrder()
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, completeShuttleOrder );
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
        libcsc::ibt::IIbtBranchRepositoryPtr ibtBranchRepo = m_pxOrderTransmit.get()->getIbtComponentManager()->createIbtBranchRepository();
        libcsc::ibt::IIbtBranchSettingPtr ibtBranchSetting;

        libcsc::document::DeliveryAdviceRepositoryPtr deliveryAdviceRepository =
            m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

        libcsc::document::DeliveryAdviceLineIbtLinkCollectionPtr deliveryAdviceLineIbtLinks =
            deliveryAdviceRepository->findCustomerOrders(
                m_DeliveryNoteCompletedRecord->getBranchno(), // local branch no for shuttle order
                m_DeliveryNoteCompletedRecord->getCscOrderNo()); // shuttle order no

        bool waitForIBTPicking = false;
        bool reduceIBTQtyForIBTLacks = false;

        std::set<basar::Int32> ordersClearWaitForIBTPicking;

        libcsc::document::DeliveryAdviceLineIbtLinkCollection::iterator iter;
        for (iter = deliveryAdviceLineIbtLinks->begin(); iter != deliveryAdviceLineIbtLinks->end(); ++iter)
        {
            (*iter)->setIbtDeliveryAdviceDate(basar::cmnutil::Date::getCurrent().getDate());

            basar::VarString invoiceNoTrimmed = m_DeliveryNoteCompletedRecord->getInvoiceNo();
            invoiceNoTrimmed.trim(basar::VarString::FIRST_END); // remove leading/trailing blanks
            invoiceNoTrimmed.erase(0, std::min(invoiceNoTrimmed.find_first_not_of('0'), invoiceNoTrimmed.size() - 1)); // remove leading zeroes
            (*iter)->setIbtDeliveryAdviceNo(invoiceNoTrimmed);

            deliveryAdviceRepository->findDeliveryAdviceDetails4ShuttleOrder(*iter);

            // get IBTBranchSettings if not yet available
            if (NULL == ibtBranchSetting.get())
            {
                ibtBranchSetting = ibtBranchRepo->findIbtBranchSetting((*iter)->getBranchNo(), (*iter)->getIbtBranchNo());
                if (NULL != ibtBranchSetting.get())
                {
                    waitForIBTPicking = ibtBranchSetting->getWaitForPicking();
                    reduceIBTQtyForIBTLacks = ibtBranchSetting->getReduceIBTQtyForIBTLacks();
                }
            }

			// write picking data only if not yet archived!!! IMPORTANT!!!
			if (false == (*iter)->isCustomerOrderArchived())
			{
				basar::Int32 sumLackQty = writePickingData(*iter);
				if (sumLackQty > 0 && reduceIBTQtyForIBTLacks)
				{
					decreaseQuantityConfirmed(*iter, sumLackQty);
				}
			}

            // store order numbers for further order based processing at the end (remove wait for ibt picking flag)
            if (true == waitForIBTPicking)
            {
                ordersClearWaitForIBTPicking.insert((*iter)->getCscOrderNo());
            }

            if (false == waitForIBTPicking)
            {
                if (false == deliveryAdviceRepository->findCustomerOrderDetails(*iter))
                {
                    // This position is not part of the customer order
                    // TODO FN logging
                    continue;
                }
                if (false == deliveryAdviceRepository->findDeliveryAdviceDetails4CustomerOrder(*iter))
                {
                    // or delivery advices are not yet existing
                    // TODO FN logging
                    continue;
                }
                deliveryAdviceRepository->saveDeliveryAdviceLineIbtLink(*iter);

                // check if all ibtpos are completed for customer order
                checkCustomerOrderForCompletion(*iter);
            }
        }

        // Process removal of wait for IBT picking flag on customer orders
        if (!ordersClearWaitForIBTPicking.empty())
        {
            for (std::set<basar::Int32>::iterator itOrdersClearWaitForIBTPicking = ordersClearWaitForIBTPicking.begin(); itOrdersClearWaitForIBTPicking != ordersClearWaitForIBTPicking.end(); ++itOrdersClearWaitForIBTPicking)
            {
                clearWaitForIbtPickingFlag((*itOrdersClearWaitForIBTPicking));
            }
        }

        // set shuttle order itself to completed.
        iter = deliveryAdviceLineIbtLinks->begin();
        if (iter != deliveryAdviceLineIbtLinks->end())
        {
            setShuttleOrdertoCompleted(*iter);
        }
    }
    catch (const libcsc::exceptions::CSCExceptionBase& e)
    {
        std::stringstream ss;
        ss << "DeliveryNoteCompletedUC::completeShuttleOrder(): Error during calculation: " << e.reason().c_str();
        BLOG_ERROR(m_Logger, ss.str());
    }
}

basar::Int32 DeliveryNoteCompletedUC::writePickingData(libcsc::document::DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink)
{
    libcsc::document::DeliveryAdviceRepositoryPtr deliveryAdviceRepository =
        m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

    libcsc::document::DeliveryAdviceLineDetailsCollectionPtr ibtpickingdata =
        deliveryAdviceRepository->findIbtPickingData(deliveryAdviceLineIbtLink);

    libcsc::cscorder::domMod::ICSCOrderIBTPickingdataPtr pickingdata =
        libcsc::cscorder::domMod::ICSCOrderIBTPickingdataPtr(new libcsc::cscorder::domMod::CSCOrderIBTPickingdata);

    pickingdata->setCscOrderNo(deliveryAdviceLineIbtLink->getCscOrderNo());
    pickingdata->setCscOrderPosNo(deliveryAdviceLineIbtLink->getCscOrderPosNo());

    libcsc::cscorder::repo::ICSCOrderIBTPickingdataRepositoryPtr cscOrderIBTPickingdataRepository =
        m_pxOrderTransmit->getCSCOrderComponentManager()->getCSCOrderIBTPickingdataRepository();

    basar::Int32 sumLackQty = 0;
    libcsc::document::DeliveryAdviceLineDetailsCollection::iterator pickiter;
    for (pickiter = ibtpickingdata->begin(); pickiter != ibtpickingdata->end(); ++pickiter)
    {
        pickingdata->setDeliveryPosNo((*pickiter)->getDeliveryPosNo());
        pickingdata->setExpiryDate((*pickiter)->getExpiryDate().getDate());
        pickingdata->setBatch((*pickiter)->getBatch());
        basar::Int32 qty = (*pickiter)->getQuantityDelivery();
        if (qty == 0)
        {
            qty = (*pickiter)->getQuantityLack();
            sumLackQty += qty;
        }
        pickingdata->setQuantity(qty);
        cscOrderIBTPickingdataRepository->savePickingdata(pickingdata);
    }
    return sumLackQty;
}

void DeliveryNoteCompletedUC::decreaseQuantityConfirmed(
    libcsc::document::DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink, basar::Int32 sumLackQty)
{
    METHODNAME_DEF(DeliveryNoteCompletedUC, decreaseQuantityConfirmed);
    BLOG_TRACE_METHOD(m_Logger, fun);

    pxOrderItem* item = new pxOrderItem(m_pxOrderTransmit.get(), deliveryAdviceLineIbtLink->getCscOrderNo(),
        deliveryAdviceLineIbtLink->getCscOrderPosNo(), cDBGET_FORUPDATE);
    if (!item->IsGoodState())
    {
        BLOG_ERROR(m_Logger, "Could not read order item");
        return;
    }

    long confirmedQty = item->MengeBestaetigt() - sumLackQty;
    if (confirmedQty < 0)
    {
        confirmedQty = 0;
        std::stringstream ss;
        ss << "Quantity below zero. Set quantity to zero. [MengeBestaetigt=" << item->MengeBestaetigt()
            << "; sumLackQty=" << sumLackQty << "]";
        BLOG_WARN(m_Logger, ss.str());
    }
    item->MengeBestaetigt(confirmedQty);
    item->nDBBeginTransaction(cDBTransRecord);
    item->Put();
    if (item->IsGoodState())
    {
        item->nDBCommit();
        return;
    }
    BLOG_ERROR(m_Logger, "Could not update order item");
    item->nDBRollBack();
}

void DeliveryNoteCompletedUC::clearWaitForIbtPickingFlag(basar::Int32 cscOrderNo)
{
	std::stringstream ss;
	ss << "clearWaitForIbtPickingFlag for CSC order " << cscOrderNo;
	BLOG_DEBUG(m_Logger, ss.str());

	libcsc::cscorder::repo::ICSCOrderFlagsRepositoryPtr cscOrderFlagsRepository =
        m_pxOrderTransmit->getCSCOrderComponentManager()->getCSCOrderFlagsRepository();

    libcsc::cscorder::domMod::ICSCOrderFlagsPtr cscOrderFlags = cscOrderFlagsRepository->findCSCOrderFlags(cscOrderNo);

	// save only if not already in archive!!!
	if (0 != cscOrderFlags->getCscOrderNo())
	{
		cscOrderFlags->setWaitForIbtPicking(false);
		cscOrderFlagsRepository->saveCSCOrderFlags(cscOrderFlags);

		ss.str("");
		ss << "clearWaitForIbtPickingFlag for CSC order " << cscOrderNo << " OK";
		BLOG_DEBUG(m_Logger, ss.str());
	}
	else
	{
		ss.str("");
		ss << "clearWaitForIbtPickingFlag for CSC order " << cscOrderNo << " already archived!";
		BLOG_DEBUG(m_Logger, ss.str());
	}


}

void DeliveryNoteCompletedUC::checkCustomerOrderForCompletion(libcsc::document::DeliveryAdviceLineIbtLinkPtr ibtLink)
{
    METHODNAME_DEF( DeliveryNoteCompletedUC, checkCustomerOrderForCompletion );
    BLOG_TRACE_METHOD( m_Logger, fun );

    libcsc::document::DeliveryAdviceRepositoryPtr repo =
        m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

    libcsc::document::DeliveryAdviceKey key;
    key.branchNo = ibtLink->getBranchNo();
    key.customerNo = ibtLink->getCustomerNo();
    key.deliveryAdviceDate = ibtLink->getDeliveryAdviceDate();
    key.deliveryAdviceNo = ibtLink->getDeliveryAdviceNo();

	std::stringstream ss;
	ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] checkCustomerOrderForCompletion.";
	BLOG_DEBUG(m_Logger, ss.str());

	libcsc::document::DeliveryAdviceInformationFilter filter;
    filter.SendTotals = false;
    filter.SendLineInformation = true;
    filter.SendLinePickingInformation = true;
    filter.SendLineDiscountInformation = false;
    filter.SendLineReturn = false;
    filter.SendCustomerInformation = false;

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = repo->findDeliveryAdvice(key, filter, false, false);
    if (NULL != deliveryAdvice.get())
    {
		if (true == deliveryAdvice->areAllIbtPositionsCompleted())
		{
			ss.str("");
			ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] all ibt pos completed!.";
			BLOG_DEBUG(m_Logger, ss.str());

			if (false == deliveryAdvice->isCompleted())
			{
				ss.str("");
				ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] set to completed!.";
				BLOG_DEBUG(m_Logger, ss.str());

				deliveryAdvice->setCompleted();
				repo->saveDeliveryAdvice(deliveryAdvice);
			}
		}
		else
		{
			ss.str("");
			ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] NOT all ibt pos completed!.";
			BLOG_DEBUG(m_Logger, ss.str());
		}
	}
	else
	{
		ss.str("");
		ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] delivery advice not found!.";
		BLOG_DEBUG(m_Logger, ss.str());
	}
}

void DeliveryNoteCompletedUC::setShuttleOrdertoCompleted(libcsc::document::DeliveryAdviceLineIbtLinkPtr ibtLink)
{
    METHODNAME_DEF(DeliveryNoteCompletedUC, setShuttleOrdertoCompleted);
    BLOG_TRACE_METHOD(m_Logger, fun);

    libcsc::document::DeliveryAdviceRepositoryPtr repo =
        m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

    libcsc::document::DeliveryAdviceKey key;
    key.branchNo = ibtLink->getIbtBranchNo();
    key.customerNo = ibtLink->getIbtCustomerNo();
    key.deliveryAdviceDate = ibtLink->getIbtDeliveryAdviceDate();
    key.deliveryAdviceNo = ibtLink->getIbtDeliveryAdviceNo();

    libcsc::document::DeliveryAdviceInformationFilter filter;
    filter.SendTotals = false;
    filter.SendLineInformation = false;
    filter.SendLinePickingInformation = false;
    filter.SendLineDiscountInformation = false;
    filter.SendLineReturn = false;
    filter.SendCustomerInformation = false;

	std::stringstream ss;
	ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] setShuttleOrdertoCompleted.";
	BLOG_DEBUG(m_Logger, ss.str());

    libcsc::document::DeliveryAdvicePtr deliveryAdvice = repo->findDeliveryAdvice(key, filter, false, false);
    if (NULL != deliveryAdvice.get())
    {
        if (false == deliveryAdvice->isCompleted())
        {
            deliveryAdvice->setCompleted();
            repo->saveDeliveryAdvice(deliveryAdvice);
        }
		else
		{
			ss.str("");
			ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] delivery advice already completed!.";
			BLOG_DEBUG(m_Logger, ss.str());
		}
    }
	else
	{
		ss.str("");
		ss << "[" << key.branchNo << "|" << key.deliveryAdviceDate << "|" << key.deliveryAdviceNo << "] delivery advice not found!.";
		BLOG_DEBUG(m_Logger, ss.str());
	}
}


} // namespace usecase
} // namespace csc_phadex
