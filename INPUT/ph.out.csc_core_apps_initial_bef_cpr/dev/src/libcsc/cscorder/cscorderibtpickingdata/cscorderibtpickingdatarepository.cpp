#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include "logger/loggerpool.h"
#include "cscorderibtpickingdata.h"
#include "cscorderibtpickingdataptr.h"
#include "cscorderibtpickingdatarepository.h"
#include "cscorderibtpickingdatasqlmapper.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderIBTPickingdataRepository::CSCOrderIBTPickingdataRepository()
{
}

CSCOrderIBTPickingdataRepository::~CSCOrderIBTPickingdataRepository()
{
    m_InsertAccessor.reset();
    m_FindAccessor.reset();
}

void CSCOrderIBTPickingdataRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void CSCOrderIBTPickingdataRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void CSCOrderIBTPickingdataRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    m_TransactionFactory = transactionFactory;
}

bool CSCOrderIBTPickingdataRepository::savePickingdata(domMod::ICSCOrderIBTPickingdataPtr pickingdata)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerIbtRequest(), "CSCOrderIBTPickingdataRepository::savePickingdata()");

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();

    std::stringstream logmsg;
    logmsg << "CSCOrderIBTPickingdataRepository::savePickingdata("
           << pickingdata->getCscOrderNo() << ", "
           << pickingdata->getCscOrderPosNo() << ", "
           << pickingdata->getDeliveryPosNo() << ", "
           << pickingdata->getQuantity() << ", "
           << pickingdata->getBatch() << ", "
           << pickingdata->getExpiryDate() << ")";

    basar::VarString query = "";
    try
    {
        guard.begin();
        {
            query = CSCOrderIBTPickingdataSqlMapper::getInsertSQL();
            m_InsertAccessor->execute(
                query, CSCOrderIBTPickingdataSqlMapper::getInsertSqlParameterBinder(pickingdata));
        }
        guard.commit();

        domMod::CSCOrderIBTPickingdataPtr temppickingdata =
            boost::dynamic_pointer_cast<domMod::CSCOrderIBTPickingdata>(pickingdata);
        CSCOrderIBTPickingdataSqlMapper::setClean(temppickingdata);

        logmsg << " done";
        LOG4CPLUS_TRACE(LoggerPool::getLoggerIbtRequest(), logmsg.str());
    }
    catch(libcsc::exceptions::PropertyUnsetException const& exc)
    {
        guard.rollback();
        logmsg << std::endl << ": " << exc.what() << " ( " <<  query << " ) ";
        LOG4CPLUS_ERROR(LoggerPool::getLoggerIbtRequest(), logmsg.str());
        return false;
    }
    catch(libcsc::exceptions::CSCExceptionBase const& exc )
    {
        guard.rollback();
        logmsg << std::endl << ": " << exc.what() << " ( " << query << " ) ";
        LOG4CPLUS_ERROR(LoggerPool::getLoggerIbtRequest(), logmsg.str());
        return false;
    }
    catch (basar::Exception const& exc)
    {
        guard.rollback();
        logmsg << std::endl << ": " << exc.what() << " ( " << query << " ) ";
        LOG4CPLUS_ERROR(LoggerPool::getLoggerIbtRequest(), logmsg.str());
        return false;
    }
    return true;
}

domMod::CSCOrderIBTPickingdataCollectionPtr CSCOrderIBTPickingdataRepository::findPickingdata(
    const basar::Int32 cscorderno, const basar::Int32 cscorderposno)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerIbtRequest(), "CSCOrderIBTPickingdataRepository::findPickingdata");

    std::stringstream logmsg;
    logmsg << "CSCOrderIBTPickingdataRepository::findPickingdata("
           << cscorderno << ", "
           << cscorderposno << ")" << std::endl
           << "Records found and mapped." << std::endl;
    try
    {
        domMod::CSCOrderIBTPickingdataCollectionPtr pickingdatacoll = domMod::makeCSCOrderIBTPickingdataCollection();
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            repo::CSCOrderIBTPickingdataSqlMapper::getSelectSQL(cscorderno, cscorderposno));

        while (resultset.next()) // full caching
        {
            domMod::CSCOrderIBTPickingdataPtr pickingdata = domMod::makeCSCOrderIBTPickingdata();
            repo::CSCOrderIBTPickingdataSqlMapper mapper(pickingdata, resultset);
            mapper.map();
            pickingdatacoll->add(pickingdata);
            logmsg << " CscOrderNo: " << pickingdata->getCscOrderNo()
                   << " CscOrderPosNo: " << pickingdata->getCscOrderPosNo()
                   << " DeliveryPosNo: " << pickingdata->getDeliveryPosNo()
                   << " Quantity: " << pickingdata->getQuantity()
                   << " Batch: " << pickingdata->getBatch()
                   << " ExpiryDate: " << pickingdata->getExpiryDate() << std::endl;
        };
        LOG4CPLUS_TRACE(LoggerPool::getLoggerIbtRequest(), logmsg.str());

        return pickingdatacoll;
    }
    catch(basar::Exception& e)
    {
        logmsg << std::endl << ": " << e.what();
        LOG4CPLUS_ERROR(LoggerPool::getLoggerIbtRequest(), logmsg.str());
        throw;
    }
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
