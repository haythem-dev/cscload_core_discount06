#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <document/deliveryadvice/deliveryadviceinformationfilter.h>
#include <document/deliveryadvice/deliveryadvice.h>
#include <document/deliveryadvice/deliveryadvicesqlmapper.h>

#include <document/deliveryadvice/deliveryadvicevattotals.h>
#include <document/deliveryadvice/deliveryadvicevattotalssqlmapper.h>

#include <document/deliveryadvice/deliveryadviceremarks.h>
#include <document/deliveryadvice/deliveryadviceremarkssqlmapper.h>

#include <document/deliveryadvice/deliveryadviceline/deliveryadviceline.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinesqlmapper.h>

#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscount.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscountsqlmapper.h>

#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetails.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetailssqlmapper.h>

#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturn.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturnsqlmapper.h>

#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlink.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinksqlmapper.h>

#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineextrasat.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineextrasatsqlmapper.h>

#include <exceptions/sqlduplicateexception.h>

#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <parameter/branchparametergetter.h>
#include <boost/make_shared.hpp>

#include <libbasarcmnutil.h>


namespace libcsc {
namespace document {

DeliveryAdviceRepository::DeliveryAdviceRepository()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::DeliveryAdviceRepository()");
}

DeliveryAdviceRepository::~DeliveryAdviceRepository()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::~DeliveryAdviceRepository()");

    m_SelectDeliveryAdviceHeadAccessor.reset();
    m_SelectDeliveryAdviceVatTotalsAccessor.reset();
    m_SelectDeliveryAdviceLinesAccessor.reset();
    m_SelectDeliveryAdviceLineSingleAccessor.reset();
    m_SelectDeliveryAdviceLineRemarksAccessor.reset();
    m_SelectDeliveryAdviceLineDiscountAccessor.reset();
    m_SelectDeliveryAdviceLineDetailsAccessor.reset();
    m_SelectDeliveryAdviceLineIbtLinkAccessor.reset();
    m_UpdateDeliveryAdviceHeadAccessor.reset();
}

void DeliveryAdviceRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectTransactionFactory()");

    m_TransactionFactory = transactionFactory;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceHeadAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceHeadAccessor()");

    m_SelectDeliveryAdviceHeadAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceVatTotalsAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceVatTotalsAccessor()");

    m_SelectDeliveryAdviceVatTotalsAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLinesAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLinesAccessor()");

    m_SelectDeliveryAdviceLinesAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineSingleAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineSingleAccessor()");

    m_SelectDeliveryAdviceLineSingleAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineRemarksAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineRemarksAccessor()");

    m_SelectDeliveryAdviceLineRemarksAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineDiscountAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineDiscountAccessor()");

    m_SelectDeliveryAdviceLineDiscountAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineDetailsAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineDetailsAccessor()");

    m_SelectDeliveryAdviceLineDetailsAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineReturnAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineReturnAccessor()");

    m_SelectDeliveryAdviceLineReturnAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineIbtLinkAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineIbtLinkAccessor()");

    m_SelectDeliveryAdviceLineIbtLinkAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDnNumbersByReferencesAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectSelectDnNumbersByReferencesAccessor()");

    m_SelectDnNumbersByReferencesAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectCustomerOrdersAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::injectSelectCustomerOrdersAccessor()");
    m_SelectCustomerOrdersAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectCustomerOrderDetailsAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::injectSelectCustomerOrderDetailsAccessor()");
    m_SelectCustomerOrderDetailsAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceDetailsAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::injectSelectDeliveryAdviceAccessor()");
    m_SelectDeliveryAdviceDetailsAccessor = accessor;
}

void DeliveryAdviceRepository::injectInsertDeliveryAdviceLineIbtLinkAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::injectInsertDeliveryAdviceLineIbtLinkAccessor()");
    m_InsertDeliveryAdviceLineIbtLinkAccessor = accessor;
}

void DeliveryAdviceRepository::injectSelectDeliveryAdviceLineExtrasATAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::injectSelectDeliveryAdviceLineExtrasATAccessor()");
    m_SelectDeliveryAdviceLineExtrasATAccessor = accessor;
}

void DeliveryAdviceRepository::injectUpdateDeliveryAdviceHeadAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectUpdateDeliveryAdviceHeadAccessor()");

    m_UpdateDeliveryAdviceHeadAccessor = accessor;
}

void DeliveryAdviceRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::injectBranchParameterGetter()");

    m_BranchParameterGetter = parameterGetter;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceCollectionPtr DeliveryAdviceRepository::findDeliveryAdvicesByDateRange(
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const ConfirmationStatusEnum& confirmationStatus,
    const basar::Date& searchPeriodStart,
    const basar::Date& searchPeriodEnd,
    const DeliveryAdviceInformationFilter& filter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdvicesByDateRange()");

    DeliveryAdviceCollectionPtr coll = boost::make_shared<DeliveryAdviceCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
    if (dbName.empty())
    {
        return coll;
    }  

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceHeadAccessor->select(
        DeliveryAdviceSQLMapper::getSelectByDateRangeSQL(dbName, branchNo, customerNo, confirmationStatus, searchPeriodStart, searchPeriodEnd)
    );
    while (resultset.next())
    {
        DeliveryAdvicePtr deliveryAdvice = buildDeliveryAdvice(resultset, filter, true);
        coll->push_back(deliveryAdvice);
    }
    return coll;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceCollectionPtr DeliveryAdviceRepository::findDeliveryAdvicesByKey(
    const DeliveryAdviceKeyCollection& keys,
    const DeliveryAdviceInformationFilter& filter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdvicesByKey()");

    DeliveryAdviceCollectionPtr coll = boost::make_shared<DeliveryAdviceCollection>();
    DeliveryAdviceKeyCollection::const_iterator it = keys.begin();
    while (it != keys.end())
    {
        DeliveryAdvicePtr deliveryAdvice = findDeliveryAdvice(*it, filter, true, true);
        if (NULL != deliveryAdvice && deliveryAdvice->isClean())
        {
            coll->push_back(deliveryAdvice);
        }
        ++it;
    }
    return coll;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdvicePtr DeliveryAdviceRepository::findDeliveryAdvice(
    const DeliveryAdviceKey& key,
    const DeliveryAdviceInformationFilter& filter,
    const bool& incrementRequestCounter,
    const bool& completedOnly)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdvice()");

    DeliveryAdvicePtr deliveryAdvice;

    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(key.branchNo);
    if (dbName.empty())
    {
        return deliveryAdvice;
    }

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceHeadAccessor->select(
        DeliveryAdviceSQLMapper::getSelectByKeySQL(dbName, key.branchNo, key.customerNo, key.deliveryAdviceDate, key.deliveryAdviceNo, key.cscOrderNo, completedOnly)
    );
    if (resultset.next())
    {
        deliveryAdvice = buildDeliveryAdvice(resultset, filter, incrementRequestCounter);
    }
    return deliveryAdvice;
}

std::vector<std::string> DeliveryAdviceRepository::findDnNumbersByReferences(
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const std::vector<std::string>& deliveryAdviceReferences)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDnNumbersByReferences()");

    std::vector<std::string> coll;

    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
    if (dbName.empty())
    {
        return coll;
    }

    basar::db::sql::ResultsetRef resultset = m_SelectDnNumbersByReferencesAccessor->select(
        DeliveryAdviceSQLMapper::getSelectDnNumbersByReferencesSQL(dbName, branchNo, customerNo, deliveryAdviceReferences));

    while (resultset.next())
    {
        coll.push_back(resultset.getString(0));
    }

    return coll;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdvicePtr DeliveryAdviceRepository::buildDeliveryAdvice(
    const basar::db::sql::ResultsetRef resultset,
    const DeliveryAdviceInformationFilter& filter,
    const bool& incrementRequestCounter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::buildDeliveryAdvice()");

    DeliveryAdvicePtr deliveryAdvice = boost::make_shared<DeliveryAdvice>();
    DeliveryAdviceSQLMapper mapper(deliveryAdvice, resultset);
    mapper.map();
    if (true == incrementRequestCounter)
    {
        deliveryAdvice->incrementRequestCounter();
        saveDeliveryAdvice(deliveryAdvice);
    }
    deliveryAdvice->m_Remarks = findDeliveryAdviceHeadRemarks(deliveryAdvice);

    if (true == filter.SendTotals)
    {
        deliveryAdvice->m_VatTotals = findDeliveryAdviceVatTotals(deliveryAdvice);
    }
    if (true == filter.SendLineInformation)
    {
        deliveryAdvice->m_DeliveryAdviceLines = findDeliveryAdviceLines(deliveryAdvice, filter);
    }
    return deliveryAdvice;
}

DeliveryAdvicePtr DeliveryAdviceRepository::buildDeliveryAdviceKeysOnly(const basar::db::sql::ResultsetRef resultset)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::buildDeliveryAdviceKeysOnly()");

    DeliveryAdvicePtr deliveryAdvice = boost::make_shared<DeliveryAdvice>();
    DeliveryAdviceSQLMapper mapper(deliveryAdvice, resultset);
    mapper.mapKeysOnly();

    return deliveryAdvice;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceVatTotalsCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceVatTotals(
    const DeliveryAdvicePtr& deliveryAdvice)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceVatTotals()");

    DeliveryAdviceVatTotalsCollectionPtr vatTotalsCollection = boost::make_shared<DeliveryAdviceVatTotalsCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdvice->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceVatTotalsAccessor->select(
        DeliveryAdviceVatTotalsSQLMapper::getSelectSQL(
            dbName,
            deliveryAdvice->getBranchNo(),
            deliveryAdvice->getCustomerNo(),
            deliveryAdvice->getDeliveryAdviceDate(),
            deliveryAdvice->getDeliveryAdviceNo())
    );

    while (resultset.next())
    {
        DeliveryAdviceVatTotalsPtr deliveryAdviceVatTotals = boost::make_shared<DeliveryAdviceVatTotals>();
        DeliveryAdviceVatTotalsSQLMapper mapper(deliveryAdviceVatTotals, resultset);
        mapper.map();
        vatTotalsCollection->push_back(deliveryAdviceVatTotals);
    }
    return vatTotalsCollection;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLines(
    const DeliveryAdvicePtr& deliveryAdvice,
    const DeliveryAdviceInformationFilter& filter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLines()");

    DeliveryAdviceLineCollectionPtr lines = boost::make_shared<DeliveryAdviceLineCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdvice->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLinesAccessor->select(
        DeliveryAdviceLineSQLMapper::getSelectSQL(
            dbName,
            deliveryAdvice->getBranchNo(),
            deliveryAdvice->getCustomerNo(),
            deliveryAdvice->getDeliveryAdviceDate(),
            deliveryAdvice->getDeliveryAdviceNo(),
            filter.SendOnlyInvoicedLines)
    );

    while (resultset.next())
    {
        DeliveryAdviceLinePtr deliveryAdviceLine = boost::make_shared<DeliveryAdviceLine>();
        DeliveryAdviceLineSQLMapper mapper(deliveryAdviceLine, deliveryAdvice, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLine);

        deliveryAdviceLine->m_Remarks = findDeliveryAdviceLineRemarks(deliveryAdviceLine, deliveryAdvice->getCscOrderNo());
        if (true == filter.SendLineDiscountInformation)
        {
            deliveryAdviceLine->m_Discounts = findDeliveryAdviceLineDiscounts(deliveryAdviceLine);
        }
        if (true == filter.SendLinePickingInformation)
        {
            if (deliveryAdviceLine->getLineType() == DeliveryAdviceLine::LINETYPE_IBT) // 1 == Verbund
            {
                deliveryAdviceLine->m_Details = boost::make_shared<DeliveryAdviceLineDetailsCollection>(); // quick and dirty hack!
                deliveryAdviceLine->m_IbtLink = findDeliveryAdviceLineIbtLink(deliveryAdviceLine, deliveryAdvice->getCscOrderNo());
                if (NULL != deliveryAdviceLine->m_IbtLink.get())
                {
                    DeliveryAdviceLinePtr deliveryAdviceLineIbt = findDeliveryAdviceLineIbt(deliveryAdviceLine->m_IbtLink, filter);
                    if (NULL != deliveryAdviceLineIbt.get())
                    {
                        deliveryAdviceLine->m_Details = findDeliveryAdviceLineDetails(deliveryAdviceLineIbt);
                    }
                }
            }
            else
            {
                deliveryAdviceLine->m_Details = findDeliveryAdviceLineDetails(deliveryAdviceLine);
            }
        }
        if(true == filter.SendLineReturn)
        {
            deliveryAdviceLine->m_Return = findDeliveryAdviceLineReturn(deliveryAdviceLine);
        }
        if (true == filter.SendLineExtrasAT)
        { 
            deliveryAdviceLine->m_ExtrasAT = findDeliveryAdviceLineExtrasAT(deliveryAdviceLine);
        }
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLinePtr DeliveryAdviceRepository::findDeliveryAdviceLineIbt(
        const DeliveryAdviceLineIbtLinkPtr& ibtLink,
        const DeliveryAdviceInformationFilter& filter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLine()");

    DeliveryAdviceLinePtr deliveryAdviceLine;
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(ibtLink->getIbtBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineSingleAccessor->select(
        DeliveryAdviceLineSQLMapper::getSelectSingleSQL(
            dbName,
            ibtLink->getIbtBranchNo(),
            ibtLink->getIbtCustomerNo(),
            ibtLink->getIbtDeliveryAdviceDate(),
            ibtLink->getIbtDeliveryAdviceNo(),
            ibtLink->getIbtDeliveryAdvicePosNo()
        )
    );

    if (resultset.next())
    {
        deliveryAdviceLine = boost::make_shared<DeliveryAdviceLine>();
        DeliveryAdviceLineSQLMapper mapper(deliveryAdviceLine, DeliveryAdvicePtr() /* == NULL */, resultset);
        mapper.map();

        deliveryAdviceLine->m_Remarks = findDeliveryAdviceLineRemarks(deliveryAdviceLine, ibtLink->getIbtCscOrderNo());
        if (true == filter.SendLineDiscountInformation)
        {
            deliveryAdviceLine->m_Discounts = findDeliveryAdviceLineDiscounts(deliveryAdviceLine);
        }
        if (true == filter.SendLinePickingInformation)
        {
            deliveryAdviceLine->m_Details = findDeliveryAdviceLineDetails(deliveryAdviceLine);
        }
        if (true == filter.SendLineReturn)
        {
            deliveryAdviceLine->m_Return = findDeliveryAdviceLineReturn(deliveryAdviceLine);
        }
    }

    return deliveryAdviceLine;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceRemarksCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceHeadRemarks(
    const DeliveryAdvicePtr& deliveryAdvice)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceHeadRemarks()");

    DeliveryAdviceRemarksCollectionPtr lines = boost::make_shared<DeliveryAdviceRemarksCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdvice->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineRemarksAccessor->select(
        DeliveryAdviceRemarksSQLMapper::getSelectSQL(dbName,
            deliveryAdvice->getBranchNo(),
            deliveryAdvice->getCustomerNo(),
            deliveryAdvice->getDeliveryAdviceDate(),
            deliveryAdvice->getCscOrderNo(),
            0) // posnr = 0 --> order head remarks
    );
    while (resultset.next())
    {
        DeliveryAdviceRemarksPtr deliveryAdviceHeadRemark = boost::make_shared<DeliveryAdviceRemarks>();
        DeliveryAdviceRemarksSQLMapper mapper(deliveryAdviceHeadRemark, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceHeadRemark);
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceRemarksCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLineRemarks(
    const DeliveryAdviceLinePtr& deliveryAdviceLine , basar::Int32 cscOrderNo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineRemarks()");

    DeliveryAdviceRemarksCollectionPtr lines = boost::make_shared<DeliveryAdviceRemarksCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineRemarksAccessor->select(
        DeliveryAdviceRemarksSQLMapper::getSelectSQL(dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            cscOrderNo,
            deliveryAdviceLine->getCscOrderPosNo())
    );

    while (resultset.next())
    {
        DeliveryAdviceRemarksPtr deliveryAdviceLineRemark = boost::make_shared<DeliveryAdviceRemarks>();
        DeliveryAdviceRemarksSQLMapper mapper(deliveryAdviceLineRemark, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLineRemark);
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineDiscountCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLineDiscounts(
    const DeliveryAdviceLinePtr& deliveryAdviceLine)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineDiscounts()");

    DeliveryAdviceLineDiscountCollectionPtr lines = boost::make_shared<DeliveryAdviceLineDiscountCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineDiscountAccessor->select(
        DeliveryAdviceLineDiscountSQLMapper::getSelectSQL(dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            deliveryAdviceLine->getPharmosOrderNo(),
            deliveryAdviceLine->getPharmosOrderPosNo())
    );

    while (resultset.next())
    {
        DeliveryAdviceLineDiscountPtr deliveryAdviceLineDiscount = boost::make_shared<DeliveryAdviceLineDiscount>();
        DeliveryAdviceLineDiscountSQLMapper mapper(deliveryAdviceLineDiscount, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLineDiscount);
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineDetailsCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLineDetails(
    const DeliveryAdviceLinePtr& deliveryAdviceLine)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineDetails()");

    DeliveryAdviceLineDetailsCollectionPtr lines = boost::make_shared<DeliveryAdviceLineDetailsCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineDetailsAccessor->select(
        DeliveryAdviceLineDetailsSQLMapper::getSelectSQL(
            dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            deliveryAdviceLine->getPharmosOrderNo(),
            deliveryAdviceLine->getPharmosOrderPosNo())
    );

    while (resultset.next())
    {
        DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails = boost::make_shared<DeliveryAdviceLineDetails>();
        DeliveryAdviceLineDetailsSQLMapper mapper(deliveryAdviceLineDetails, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLineDetails);
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineDetailsCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLineDetails(
    const DeliveryAdviceLineIbtLinkPtr& deliveryAdviceLineIbtLink)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineDetails()");

    DeliveryAdviceLineDetailsCollectionPtr lines = boost::make_shared<DeliveryAdviceLineDetailsCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLineIbtLink->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineDetailsAccessor->select(
        DeliveryAdviceLineDetailsSQLMapper::getSelectSQL(
            dbName,
            deliveryAdviceLineIbtLink->getIbtBranchNo(),
            deliveryAdviceLineIbtLink->getIbtCustomerNo(),
            deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate(),
            deliveryAdviceLineIbtLink->getIbtCscOrderNo(),      // eigentlich: getPharmosOrderNo(),
            deliveryAdviceLineIbtLink->getIbtCscOrderPosNo()    // eigentlich: getPharmosOrderPosNo()
        )
    );

    while (resultset.next())
    {
        DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails = boost::make_shared<DeliveryAdviceLineDetails>();
        DeliveryAdviceLineDetailsSQLMapper mapper(deliveryAdviceLineDetails, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLineDetails);
    }
    return lines;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineReturnCollectionPtr DeliveryAdviceRepository::findDeliveryAdviceLineReturn(
    const DeliveryAdviceLinePtr& deliveryAdviceLine)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineReturn()");

    DeliveryAdviceLineReturnCollectionPtr linesReturn = boost::make_shared<DeliveryAdviceLineReturnCollection>();
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    //TODO DZ: we need to use pharmosorderposno instead of deliveryadviceposno, because the naming is false in the database its the pharmosorderposno 
    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineReturnAccessor->select(
        DeliveryAdviceLineReturnSQLMapper::getSelectSQL(
            dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            deliveryAdviceLine->getDeliveryAdviceNo(),
            deliveryAdviceLine->getPharmosOrderPosNo())
    );

    while (resultset.next())
    {
        DeliveryAdviceLineReturnPtr deliveryAdviceLineReturn = boost::make_shared<DeliveryAdviceLineReturn>();
        DeliveryAdviceLineReturnSQLMapper mapper(deliveryAdviceLineReturn, resultset);
        mapper.map();
        linesReturn->push_back(deliveryAdviceLineReturn);
    }
    return linesReturn;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineIbtLinkPtr DeliveryAdviceRepository::findDeliveryAdviceLineIbtLink(
    const DeliveryAdviceLinePtr& deliveryAdviceLine, basar::Int32 cscOrderNo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineIbtLink()");

    DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink;
    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineIbtLinkAccessor->select(
        DeliveryAdviceLineIbtLinkSQLMapper::getSelectSQL(
            dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            cscOrderNo,
            deliveryAdviceLine->getCscOrderPosNo())
    );

    if (resultset.next())
    {
        deliveryAdviceLineIbtLink = boost::make_shared<DeliveryAdviceLineIbtLink>();
        DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
        mapper.map();
    }

    return deliveryAdviceLineIbtLink;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineExtrasATPtr DeliveryAdviceRepository::findDeliveryAdviceLineExtrasAT(
    const DeliveryAdviceLinePtr& deliveryAdviceLine)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdviceLineExtrasAT()");

    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdviceLine->getBranchNo());

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineExtrasATAccessor->select(
        DeliveryAdviceLineExtrasATSQLMapper::getSelectSQL(
            dbName,
            deliveryAdviceLine->getBranchNo(),
            deliveryAdviceLine->getCustomerNo(),
            deliveryAdviceLine->getDeliveryAdviceDate(),
            deliveryAdviceLine->getPharmosOrderNo(),
            deliveryAdviceLine->getPharmosOrderPosNo())
    );

    DeliveryAdviceLineExtrasATPtr deliveryAdviceLineDetails = boost::make_shared<DeliveryAdviceLineExtrasAT>();
    while (resultset.next())
    {
        DeliveryAdviceLineExtrasATSQLMapper mapper(deliveryAdviceLineDetails, resultset);
        mapper.map();
    }
    return deliveryAdviceLineDetails;
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void DeliveryAdviceRepository::saveDeliveryAdvice(const DeliveryAdvicePtr deliveryAdvice)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::saveDeliveryAdvice()");

    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(deliveryAdvice->getBranchNo());

    m_UpdateDeliveryAdviceHeadAccessor->execute(
        DeliveryAdviceSQLMapper::getUpdateSQL(dbName, deliveryAdvice)
    );
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
DeliveryAdviceLineIbtLinkCollectionPtr DeliveryAdviceRepository::createEmptyDeliveryAdviceLineIbtLinks() const
{
    return boost::make_shared<DeliveryAdviceLineIbtLinkCollection>();
}

DeliveryAdviceLineIbtLinkPtr DeliveryAdviceRepository::createEmptyDeliveryAdviceLineIbtLink() const
{
    return boost::make_shared<DeliveryAdviceLineIbtLink>();
}

DeliveryAdviceCollectionPtr DeliveryAdviceRepository::findDeliveryAdvicesForBatchAdviceCreation(const basar::Int16& branchNo, bool batchCorrectionOnly)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findDeliveryAdvicesForBatchAdviceCreation()");

    DeliveryAdviceCollectionPtr coll = boost::make_shared<DeliveryAdviceCollection>();

    basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
    if (dbName.empty())
    {
        return coll;
    }

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceHeadAccessor->select(
        DeliveryAdviceSQLMapper::getSelectForBatchAdvice(dbName, branchNo, batchCorrectionOnly)
    );

    while (resultset.next())
    {
        DeliveryAdvicePtr deliveryAdvice = buildDeliveryAdviceKeysOnly(resultset);
        coll->push_back(deliveryAdvice);;
    }

    return coll;
}

DeliveryAdviceLineIbtLinkCollectionPtr DeliveryAdviceRepository::findCustomerOrders(
    const basar::UInt16 shuttleBranchNo,
    const basar::UInt32 shuttleOrderNo) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findCustomerOrders()");

    DeliveryAdviceLineIbtLinkCollectionPtr deliveryAdviceLineIbtLinks = createEmptyDeliveryAdviceLineIbtLinks();

    try
    {
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findCustomerOrders() - begin for "
            "shuttleBranchNo " << shuttleBranchNo << ", shuttleOrderNo " << shuttleOrderNo);
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectCustomerOrdersAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrdersSelectSQL(shuttleBranchNo, shuttleOrderNo)
        );

        while (resultset.next())
        {
            DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink = createEmptyDeliveryAdviceLineIbtLink();
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapCustomerOrders();
            deliveryAdviceLineIbtLinks->push_back(deliveryAdviceLineIbtLink);
        }
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findCustomerOrders() - end");
    }
    catch( basar::Exception & )
    {
        throw;
    }

    return deliveryAdviceLineIbtLinks;
}

bool DeliveryAdviceRepository::findCustomerOrderDetails(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::findCustomerOrderDetails()");

    try
    {
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findCustomerOrderDetails() - begin for BranchNo "
            << deliveryAdviceLineIbtLink->getBranchNo()
            << ", CustomerNo " << deliveryAdviceLineIbtLink->getCustomerNo()
            << ", CscOrderNo " << deliveryAdviceLineIbtLink->getIbtCscOrderNo()
            << ", PositionBookingDate " << deliveryAdviceLineIbtLink->getPositionBookingDate());
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectCustomerOrderDetailsAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getCustomerOrderDetailsSelectSQL(
                deliveryAdviceLineIbtLink->getBranchNo(),
                deliveryAdviceLineIbtLink->getCustomerNo(),
                deliveryAdviceLineIbtLink->getCscOrderNo(),
//              deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate()
                deliveryAdviceLineIbtLink->getPositionBookingDate()
            )
        );
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findCustomerOrderDetails() - end");

        if (resultset.next())
        {
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapCustomerOrderDetails();
            return true;
        }
        return false;
    }
    catch (basar::Exception& ex)
    {
        std::stringstream ss;
        ss << "DeliveryAdviceRepository::findCustomerOrderDetails(): Error: " << ex.what();
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerDocuments(), ss.str());
        throw;
    }
}

bool DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder(
    DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder()");

    try
    {
        basar::Int16 branchNo = deliveryAdviceLineIbtLink->getBranchNo();
        basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);

        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder() - begin for branchNo " << branchNo
            << ", CustomerNo " << deliveryAdviceLineIbtLink->getCustomerNo()
            << ", CscOrderNo " << deliveryAdviceLineIbtLink->getCscOrderNo()
            << ", CscOrderPosNo " << deliveryAdviceLineIbtLink->getCscOrderPosNo()
            << ", DeliveryAdviceDate " << deliveryAdviceLineIbtLink->getDeliveryAdviceDate().toStrDate());
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectDeliveryAdviceDetailsAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getDeliveryAdviceDetails4CustomerOrderSelectSQL(
                databaseName,
                branchNo,
                deliveryAdviceLineIbtLink->getCustomerNo(),
                deliveryAdviceLineIbtLink->getCscOrderNo(),
                deliveryAdviceLineIbtLink->getCscOrderPosNo(),
                deliveryAdviceLineIbtLink->getDeliveryAdviceDate()
            )
        );

        if (resultset.next())
        {
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapDeliveryAdvice4CustomerOrder();
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
                "DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder() - end found DeliveryAdviceNo "
                << deliveryAdviceLineIbtLink->getDeliveryAdviceNo()
                << ", DeliveryAdvicePosNo " << deliveryAdviceLineIbtLink->getDeliveryAdvicePosNo());
            return true;
        }
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder() - end nothing found");
        return false;
    }
    catch (basar::Exception& ex)
    {
        std::stringstream ss;
        ss << "DeliveryAdviceRepository::findDeliveryAdviceDetails4CustomerOrder(): Error: " << ex.what();
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerDocuments(), ss.str());
        throw;
    }
}

DeliveryAdviceLineIbtLinkCollectionPtr DeliveryAdviceRepository::findShuttleOrders(
    const basar::UInt16 branchNo, const basar::UInt32 customerNo, const basar::UInt32 cscOrderNo) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findShuttleOrders()");

    DeliveryAdviceLineIbtLinkCollectionPtr deliveryAdviceLineIbtLinks = createEmptyDeliveryAdviceLineIbtLinks();

    try
    {
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findShuttleOrders() - begin for branchNo " << branchNo
            << ", customerNo " << customerNo << ", cscOrderNo " << cscOrderNo);
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectCustomerOrdersAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getShuttleOrdersSelectSQL(branchNo, customerNo, cscOrderNo)
            );

        int z = 0;
        while (resultset.next())
        {
            ++z;
            DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink = createEmptyDeliveryAdviceLineIbtLink();
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapShuttleOrders();
            deliveryAdviceLineIbtLinks->push_back(deliveryAdviceLineIbtLink);
        }
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findShuttleOrders() - end found " << z << " orders");
    }
    catch (basar::Exception& ex)
    {
        std::stringstream ss;
        ss << "DeliveryAdviceRepository::findShuttleOrders(): Error: " << ex.what();
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerDocuments(), ss.str());
        throw;
    }

    return deliveryAdviceLineIbtLinks;
}

bool DeliveryAdviceRepository::findShuttleOrderDetails(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::findShuttleOrderDetails()");

    try
    {
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findShuttleOrderDetails() - begin for IbtBranchNo "
            << deliveryAdviceLineIbtLink->getIbtBranchNo()
            << ", IbtCscOrderNo " << deliveryAdviceLineIbtLink->getIbtCscOrderNo()
            << ", IbtCscOrderPosNo " << deliveryAdviceLineIbtLink->getIbtCscOrderPosNo()
            << ", IbtDeliveryAdviceDate " << deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate().toStrDate());
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectCustomerOrderDetailsAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getShuttleOrderDetailsSelectSQL(
                deliveryAdviceLineIbtLink->getIbtBranchNo(),
                deliveryAdviceLineIbtLink->getIbtCscOrderNo(),
                deliveryAdviceLineIbtLink->getIbtCscOrderPosNo(),
                deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate()
                )
            );

        if (resultset.next())
        {
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapShuttleOrderDetails();
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
                "DeliveryAdviceRepository::findShuttleOrderDetails() - end found IbtDeliveryAdviceNo "
                << deliveryAdviceLineIbtLink->getIbtDeliveryAdviceNo()
                << ", DeliveryAdviceDate " << deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate().toStrDate());
            return true;
        }
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findShuttleOrderDetails() - end nothing found");
        return false;
    }
    catch (basar::Exception& ex)
    {
        std::stringstream ss;
        ss << "DeliveryAdviceRepository::findShuttleOrderDetails(): Error: " << ex.what();
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerDocuments(), ss.str());
        throw;
    }
}

bool DeliveryAdviceRepository::findDeliveryAdviceDetails4ShuttleOrder(
    DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::findDeliveryAdviceDetails4ShuttleOrder()");

    try
    {
        basar::Int16 branchNo = deliveryAdviceLineIbtLink->getIbtBranchNo();
        basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);

        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findDeliveryAdviceDetails4ShuttleOrder() - begin for branchNo " << branchNo
            << ", IbtCustomerNo " << deliveryAdviceLineIbtLink->getIbtCustomerNo()
            << ", IbtCscOrderNo " << deliveryAdviceLineIbtLink->getIbtCscOrderNo()
            << ", IbtCscOrderPosNo " << deliveryAdviceLineIbtLink->getIbtCscOrderPosNo()
            << ", IbtDeliveryAdviceDate " << deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate().toStrDate()
            << ", IbtDeliveryAdviceNo " << deliveryAdviceLineIbtLink->getIbtDeliveryAdviceNo());
        basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectDeliveryAdviceDetailsAccessor->select(
            DeliveryAdviceLineIbtLinkSQLMapper::getDeliveryAdviceDetails4ShuttleOrderSelectSQL(
                databaseName,
                branchNo,
                deliveryAdviceLineIbtLink->getIbtCustomerNo(),
                deliveryAdviceLineIbtLink->getIbtCscOrderNo(),
                deliveryAdviceLineIbtLink->getIbtCscOrderPosNo(),
                deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate(),
                deliveryAdviceLineIbtLink->getIbtDeliveryAdviceNo()
            )
        );
        LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
            "DeliveryAdviceRepository::findDeliveryAdviceDetails4ShuttleOrder() - end");

        if (resultset.next())
        {
            DeliveryAdviceLineIbtLinkSQLMapper mapper(deliveryAdviceLineIbtLink, resultset);
            mapper.mapDeliveryAdvice4ShuttleOrder();
            return true;
        }
        return false;
    }
    catch (basar::Exception& ex)
    {
        std::stringstream ss;
        ss << "DeliveryAdviceRepository::findDeliveryAdviceDetails4ShuttleOrder(): Error: " << ex.what();
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerDocuments(), ss.str());
        throw;
    }
}

DeliveryAdviceLineDetailsCollectionPtr DeliveryAdviceRepository::findIbtPickingData(
    DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::findIbtPickingData()");

    DeliveryAdviceLineDetailsCollectionPtr lines = boost::make_shared<DeliveryAdviceLineDetailsCollection>();
    basar::Int16 branchNo = deliveryAdviceLineIbtLink->getIbtBranchNo();
    basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);

    basar::db::sql::ResultsetRef resultset = m_SelectDeliveryAdviceLineDetailsAccessor->select(
        DeliveryAdviceLineDetailsSQLMapper::getSelectSQL(
            databaseName,
            branchNo,
            deliveryAdviceLineIbtLink->getIbtCustomerNo(),
            deliveryAdviceLineIbtLink->getIbtDeliveryAdviceDate(),
            deliveryAdviceLineIbtLink->getIbtDeliveryAdviceNo(),
            deliveryAdviceLineIbtLink->getIbtDeliveryAdvicePosNo() )
    );
    while (resultset.next())
    {
        DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails = boost::make_shared<DeliveryAdviceLineDetails>();
        DeliveryAdviceLineDetailsSQLMapper mapper(deliveryAdviceLineDetails, resultset);
        mapper.map();
        lines->push_back(deliveryAdviceLineDetails);
    }
    return lines;
}

void DeliveryAdviceRepository::saveDeliveryAdviceLineIbtLink(
    DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DeliveryAdviceRepository::saveDeliveryAdviceLineIbtLink()");

    basar::Int16 branchNo = deliveryAdviceLineIbtLink->getBranchNo();
    basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);

    LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::saveDeliveryAdviceLineIbtLink() - begin");
    basar::db::sql::ExecuteReturnInfo retVal = m_InsertDeliveryAdviceLineIbtLinkAccessor->execute(
        DeliveryAdviceLineIbtLinkSQLMapper::getInsertSQL(
            databaseName,
            deliveryAdviceLineIbtLink
        ),
        false
    );
    LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerDocuments(),
        "DeliveryAdviceRepository::saveDeliveryAdviceLineIbtLink() - end");
        if (true == retVal.hasError() && retVal.getError() != basar::db::sql::DBErrorCode::INSERT_DUPL)
    {
        throw libcsc::exceptions::PersistenceException(basar::ExceptInfo("DeliveryAdviceRepository::saveDeliveryAdviceLineIbtLink()", "", __FILE__, __LINE__));
    }
}

} // end namespace document
} // end namespace libcsc
