/*
 * repository.cpp
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#include "repository.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <libbasarcmnutil_exceptions.h>
#include <libbasarcmnutil_datetime.h>
#include <crema/guidata/guidatasqlmapper.h>
#include <crema/guidata/guidatasql.h>
#include <crema/guidata/guidata.h>
#include <crema/maildata/maildatasqlmapper.h>
#include <crema/maildata/maildatasql.h>
#include <crema/maildata/maildata.h>
#include <crema/reason/reason.h>
#include <crema/reason/reasonsql.h>
#include <crema/reason/reasonsqlmapper.h>
#include <crema/orderdata/orderdatasqlmapper.h>
#include <crema/orderdata/orderdatasql.h>
#include <crema/orderdata/orderdata.h>
#include <crema/usersuggestion/usersuggestionsqlmapper.h>
#include <crema/usersuggestion/usersuggestionsql.h>
#include <crema/usersuggestion/usersuggestion.h>
#include <crema/cremaorder/cremaordersqlmapper.h>
#include <crema/cremaorder/cremaordersql.h>
#include <crema/cremaorder/cremaorder.h>
#include <crema/creditlimitdata/creditlimitdata.h>
#include <crema/creditlimitdata/creditlimitdatasql.h>
#include <crema/creditlimitdata/creditlimitdatasqlmapper.h>
#include <boost/make_shared.hpp>
#include "exceptions/sqlnotfoundexception.h"
#include "exceptions/sqltoomanyrowsexception.h"

namespace libcsc {
namespace crema {
namespace repo {

Repository::Repository(log4cplus::Logger const& logger)
    : m_Logger(logger)
{
}

Repository::~Repository()
{
    m_FindAccessor.reset();
}

IRepositoryPtr Repository::create(log4cplus::Logger const& logger)
{
    return IRepositoryPtr(new Repository(logger));
}

void Repository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void Repository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void Repository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
{
    m_UpdateAccessor = accessor;
}

GuiDataPtr Repository::findGuiData(const basar::Int16& branchNo, const basar::Int32& orderNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(GuiDataSql::getGuiDataQuery(branchNo, orderNo));
        if (resultset.next())
        {
            GuiDataPtr guiData = boost::make_shared<GuiData>();
            GuiDataSqlMapper mapper(guiData, resultset);
            mapper.map();
            return guiData;
        }

        return GuiDataPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findGuiData: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

MailDataPtr Repository::findMailData(const basar::VarString& uuid)
{
    try
    {
        MailDataPtr result = boost::make_shared<MailData>();
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(MailDataSql::getMailDataQuery(uuid));
        bool bFound = false;
        while (resultset.next())
        {
            MailDataSqlMapper mapper(result, resultset);
            mapper.map();
            bFound = true;
        }
        return bFound ? result : MailDataPtr(); // if not found, members of MailData are not set and throw exception. Therefor return NULL-MailData pointer!
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findMailData: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

ReasonCollectionPtr Repository::findReasons(
    const basar::Int32& country, const basar::Int32& language, const bool& unlock)
{
    try
    {
        ReasonCollectionPtr result = boost::make_shared<ReasonCollection>();
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ReasonSql::getReasonQuery(country, language, unlock));
        while (resultset.next())
        {
            ReasonPtr reason = boost::make_shared<Reason>();
            ReasonSqlMapper mapper(reason, resultset);
            mapper.map();
            result->push_back(reason);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findReasons: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

OrderDataPtr Repository::findOrderData(const basar::VarString& uuid)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(OrderDataSql::getOrderDataQuery(uuid));
        if (resultset.next())
        {
            OrderDataPtr orderData = boost::make_shared<OrderData>();
            OrderDataSqlMapper mapper(orderData, resultset);
            mapper.map();
            return orderData;
        }

        return OrderDataPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findOrderData: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

UserSuggestionPtr Repository::findUserSuggestion(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& userName, const bool& byTime)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(byTime ?
            UserSuggestionSql::getUserSuggestionQuery(branchNo, customerNo) :
            UserSuggestionSql::getUserSuggestionQuery(branchNo, customerNo, userName));
        if (resultset.next())
        {
            UserSuggestionPtr userSuggestion = boost::make_shared<UserSuggestion>();
            UserSuggestionSqlMapper mapper(userSuggestion, resultset);
            mapper.map();
            return userSuggestion;
        }

        return UserSuggestionPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findUserSuggestion: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

CremaOrderCollectionPtr Repository::findOpenCremaOrders(
    const basar::Int16& userLevel, const std::vector<basar::Int16>& relevantBranchNos)
{
    try
    {
        CremaOrderCollectionPtr result = boost::make_shared<CremaOrderCollection>();
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            CremaOrderSql::getOpenCremaOrdersQuery(userLevel, relevantBranchNos));
        while (resultset.next())
        {
            CremaOrderPtr cremaOrder = boost::make_shared<CremaOrder>();
            CremaOrderSqlMapper mapper(cremaOrder, resultset);
            mapper.map();
            result->push_back(cremaOrder);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findOpenCremaOrders: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

CremaOrderCollectionPtr Repository::findFinishedTodayCremaOrders(const std::vector<basar::Int16>& relevantBranchNos)
{
    try
    {
        CremaOrderCollectionPtr result = boost::make_shared<CremaOrderCollection>();
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            CremaOrderSql::getFinishedTodayCremaOrdersQuery(relevantBranchNos));
        while (resultset.next())
        {
            CremaOrderPtr cremaOrder = boost::make_shared<CremaOrder>();
            CremaOrderSqlMapper mapper(cremaOrder, resultset);
            mapper.map();
            result->push_back(cremaOrder);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findFinishedTodayCremaOrders: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

void Repository::saveLastDecision(
    const basar::Int16& typeClose, const basar::Int32& reason, const basar::VarString& comment, const basar::VarString& user,
    const basar::Int16& branchNo, const basar::Int32& orderNo)
{
    try
    {
        basar::Int32 customerNo;
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            UserSuggestionSql::getCustomerNoQuery(branchNo, orderNo));
        if (resultset.next())
        {
            customerNo = resultset.getInt32("idfnr");
        }

        UserSuggestionPtr userSuggestion = findUserSuggestion(branchNo, customerNo, user, false);
        if (userSuggestion == NULL)
        {
            m_InsertAccessor->execute(
                UserSuggestionSql::getUserSuggestionInsertQuery(typeClose, reason, comment, user, branchNo, customerNo));
        }
        else
        {
            m_UpdateAccessor->execute(
                UserSuggestionSql::getUserSuggestionUpdateQuery(typeClose, reason, comment, userSuggestion->getId()));
        }
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "saveLastDecision: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

CreditLimitDataCollectionPtr Repository::findCreditLimitData(const basar::Int16& branchNo, const basar::Int32& orderNo)
{
    try
    {
        CreditLimitDataCollectionPtr result = boost::make_shared<CreditLimitDataCollection>();

        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CreditlimitDataSql::getCreditlimitDataQuery(branchNo, orderNo));
        while (resultset.next())
        {
            CreditLimitDataPtr creditLimitData = boost::make_shared<CreditLimitData>();
            CreditLimitDataSqlMapper mapper(creditLimitData, resultset);
            mapper.map();
            result->push_back(creditLimitData);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findCreditLimitData: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}
} // end namespace repo
} // end namespace crema
} // end namespace libcsc
