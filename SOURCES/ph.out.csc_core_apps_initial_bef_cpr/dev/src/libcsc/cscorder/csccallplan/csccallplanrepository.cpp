#include "csccallplanrepository.h"
#include "logger/loggerpool.h"
#include "cscorder/csccallplan/csccallplan.h"
#include "cscorder/csccallplan/csccallplanptr.h"
#include "cscorder/csccallplan/icsccallplan.h"
#include "csccallplansqlmapper.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanRepository::CSCCallplanRepository()
{
}

CSCCallplanRepository::~CSCCallplanRepository()
{
    m_InsertAccessor.reset();
    m_UpdateAccessor.reset();
    m_FindAccessor.reset();
}

void CSCCallplanRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void CSCCallplanRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
{
    m_UpdateAccessor = accessor;
}

void CSCCallplanRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void CSCCallplanRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    m_TransactionFactory = transactionFactory;
}

bool CSCCallplanRepository::saveCSCCallplan(domMod::ICSCCallplanPtr cscCallplan)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCCallplanRepository::saveCSCCallplan()");

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();

    std::stringstream log;
    log << "CSCCallplanRepository::saveCSCCallplan( BranchNo: " << cscCallplan->getBranchNo()
        << ", CustomerNo: " << cscCallplan->getCustomerNo() << ", TimeFrom: " << cscCallplan->getTimeFrom() << " )";

    bool ret = false;

    basar::VarString query;
    basar::VarString exwhat;

    try
    {
        if (!findCSCCallplan(cscCallplan, query, log))
        {
            log << " Abort.";
            BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());
            return true;
        }

        // Increase action value
        cscCallplan->setAction(cscCallplan->getAction() + 1);

        guard.begin();
        {
            query = CSCCallplanSqlMapper::getUpdateSQL();
            m_UpdateAccessor->execute(query, CSCCallplanSqlMapper::getUpdateSqlParameterBinder(cscCallplan));

            query = CSCCallplanSqlMapper::getInsertSQL();
            m_InsertAccessor->execute(query, CSCCallplanSqlMapper::getInsertSqlParameterBinder(cscCallplan));
        }
        guard.commit();

        ret = true;

        cscCallplan->setClean();

        log << " Done.";
        BLOG_TRACE(LoggerPool::getLoggerOrder(), log.str());
    }
    catch (libcsc::exceptions::PropertyUnsetException const& ex)
    {
        exwhat = ex.what();
    }
    catch (libcsc::exceptions::CSCExceptionBase const& ex)
    {
        exwhat = ex.what();
    }
    catch (basar::Exception const& ex)
    {
        exwhat = ex.what();
    }
    if (!ret)
    {
        guard.rollback();
        log << ": " << exwhat.c_str() << " ( " << query.c_str() << " )";
        BLOG_ERROR(LoggerPool::getLoggerOrder(), log.str());
    }
    return ret;
}

bool CSCCallplanRepository::findCSCCallplan(domMod::ICSCCallplanPtr cscCallplan, basar::VarString& query, std::stringstream& log)
{
    query = CSCCallplanSqlMapper::getSelectSQL();
    basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(query, CSCCallplanSqlMapper::getSelectSqlParameterBinder(cscCallplan));
    if (resultset.next()) // full caching
    {
        repo::CSCCallplanSqlMapper mapper(cscCallplan, resultset);
        mapper.map();
        log << " Record found and mapped.";
        return true;
    }

    log << " No Record found.";
    return false;
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
