#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include "logger/loggerpool.h"
#include "cscorderpossplittinfo.h"
#include "cscorderpossplittinfoptr.h"
#include "cscorderpossplittinforepository.h"
#include "cscorderpossplittinfosqlmapper.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

CSCOrderposSplittinfoRepository::CSCOrderposSplittinfoRepository()
{
}

CSCOrderposSplittinfoRepository::~CSCOrderposSplittinfoRepository()
{
    m_InsertAccessor.reset();
    m_FindAccessor.reset();
}

void CSCOrderposSplittinfoRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void CSCOrderposSplittinfoRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void CSCOrderposSplittinfoRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    m_TransactionFactory = transactionFactory;
}

bool CSCOrderposSplittinfoRepository::saveSplittinfo(domMod::ICSCOrderposSplittinfoPtr splittinfo)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrderPos(), "CSCOrderposSplittinfoRepository::saveSplittinfo()");

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();

    std::stringstream tmp;
    tmp << "CSCOrderposSplittinfoRepository::saveSplittinfo("
        << splittinfo->getCscOrderNo() << ", "
        << splittinfo->getCscOrderPosNo() << ", "
        << splittinfo->getSplittType() << ", "
        << splittinfo->getOriginal() << ", "
        << splittinfo->getOrderNo() << ", "
        << splittinfo->getOrderPosNo() << ")";

    basar::VarString query = "";
    try
    {
        guard.begin();
        {
            query = CSCOrderposSplittinfoSqlMapper::getInsertSQL();
            m_InsertAccessor->execute(query, CSCOrderposSplittinfoSqlMapper::getInsertSqlParameterBinder(splittinfo));
        }
        guard.commit();

        domMod::CSCOrderposSplittinfoPtr tempsplittinfo =
            boost::dynamic_pointer_cast<domMod::CSCOrderposSplittinfo>(splittinfo);
        CSCOrderposSplittinfoSqlMapper::setClean(tempsplittinfo);

        tmp << " done";
        BLOG_TRACE(LoggerPool::getLoggerOrderPos(), tmp.str());
    }
    catch(libcsc::exceptions::PropertyUnsetException const& exc)
    {
        guard.rollback();
        tmp << std::endl << ": " << exc.what() << " ( " <<  query << " ) ";
        BLOG_ERROR(LoggerPool::getLoggerOrderPos(), tmp.str());
        return false;
    }
    catch(libcsc::exceptions::CSCExceptionBase const& exc )
    {
        guard.rollback();
        tmp << std::endl << ": " << exc.what() << " ( " << query << " ) ";
        BLOG_ERROR(LoggerPool::getLoggerOrderPos(), tmp.str());
        return false;
    }
    catch (basar::Exception const& exc)
    {
        guard.rollback();
        tmp << std::endl << ": " << exc.what() << " ( " << query << " ) ";
        BLOG_ERROR(LoggerPool::getLoggerOrderPos(), tmp.str());
        return false;
    }
    return true;
}

domMod::ICSCOrderposSplittinfoPtr CSCOrderposSplittinfoRepository::findSplittinfo(const basar::Int32 cscorderno,
    const basar::Int32 cscorderposno, const SplittTypeEnum splitttype, const basar::Int32 date /*= 0*/)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrderPos(), "CSCOrderposSplittinfoRepository::findSplittinfo");

    std::stringstream tmp;
    tmp << "CSCOrderposSplittinfoRepository::findSplittinfo("
        << cscorderno << ", "
        << cscorderposno << ", "
        << splitttype << ", "
        << date << ")";

    try
    {
        domMod::CSCOrderposSplittinfoPtr splittinfo;

        basar::db::sql::ResultsetRef resultset;
        if (date == 0)
        {
            resultset = m_FindAccessor->select(repo::CSCOrderposSplittinfoSqlMapper::getSelectSQL(
                cscorderno, cscorderposno, static_cast<basar::Int16>(splitttype)));
        }
        else
        {
            resultset = m_FindAccessor->select(repo::CSCOrderposSplittinfoSqlMapper::getSelectArchiveSQL(
                cscorderno, cscorderposno, static_cast<basar::Int16>(splitttype), date));
        }

        if (resultset.next()) // full caching
        {
            splittinfo = domMod::CSCOrderposSplittinfoPtr(new domMod::CSCOrderposSplittinfo());
            repo::CSCOrderposSplittinfoSqlMapper mapper(splittinfo, resultset);
            mapper.map();
            tmp << " Record found and mapped." << std::endl
                << "CscOrderNo: " << splittinfo->getCscOrderNo()
                << " CscOrderPosNo: " << splittinfo->getCscOrderPosNo()
                << " SplittType: " << splittinfo->getSplittType()
                << " Original: " << splittinfo->getOriginal()
                << " OrderNo: " << splittinfo->getOrderNo()
                << " OrderPosNo: " << splittinfo->getOrderPosNo();
        }
        else
        {
            tmp << " No Record found.";
        }
        BLOG_TRACE(LoggerPool::getLoggerOrderPos(), tmp.str());

        return splittinfo;
    }
    catch(basar::Exception& e)
    {
        tmp << std::endl << ": " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerOrderPos(), tmp.str());
        throw;
    }
}

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc
