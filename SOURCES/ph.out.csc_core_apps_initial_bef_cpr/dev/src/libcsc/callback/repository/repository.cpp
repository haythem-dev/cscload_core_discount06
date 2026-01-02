/*
 * repository.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "repository.h"
#include "callbacksqlmapper.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <libbasarcmnutil_exceptions.h>
#include <libbasarcmnutil_datetime.h>
#include "callback/domainmodule/callbackdm.h"
#include "callback/domainmodule/callbackposcollectionptr.h"
#include "callback/domainmodule/callbackcustomerdm.h"
#include "callback/domainmodule/callbackdivisioncollection.h"
#include "callback/domainmodule/callbackdivisiondm.h"
#include "callback/domainmodule/callbackitemdm.h"
#include "callback/domainmodule/callbackitemdmptr.h"
#include "callback/domainmodule/callbackreasondm.h"
#include "callback/domainmodule/callbackreasondmptr.h"
#include "callback/domainmodule/callbackstatuscollection.h"
#include "callback/domainmodule/callbackstatusdmptr.h"
#include "callback/domainmodule/callbackstatuscollectionptr.h"
#include "callback/domainmodule/critdm.h"
#include "callback/domainmodule/critdmptr.h"
#include "callback/domainmodule/critposdm.h"
#include "callback/domainmodule/critposdmptr.h"
#include "callback/domainmodule/newcallbackdm.h"
#include "callback/exceptions/callbacklockedexception.h"
#include "callback/exceptions/callbacknotfoundexception.h"
#include "callback/exceptions/customernotfoundexception.h"
#include "exceptions/sqlnotfoundexception.h"
#include "exceptions/sqltoomanyrowsexception.h"

namespace libcsc {
namespace callback {
namespace repo {

VarString const Repository::LockTagSet("1");
VarString const Repository::LockTagUnset("0");

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

void Repository::injectDbName(basar::VarString const& dbName)
{
    m_DbName = dbName;
}

void Repository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    m_TransactionFactory = transactionFactory;
}

void Repository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void Repository::injectInsertCritAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertCritAccessor = accessor;
}

void Repository::injectInsertCritPosAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertCritPosAccessor = accessor;
}

void Repository::injectUpdateCallbackItemAccessor(persistence::IAccessorPtr accessor)
{
    m_UpdateCallbackItemAccessor = accessor;
}

void Repository::injectInsertCallbackItemAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertCallbackItemAccessor = accessor;
}

bool Repository::hasCallback(basar::Int32 const callbackNo) const
{
    domMod::ICallbackItemPtr callbackItem = findCallbackItem(callbackNo);
    return (callbackItem != NULL);
}

bool Repository::tryGetCallback(basar::Int32 const callbackNo, domMod::ICallbackPtr& callback, domMod::CallbackPosCollectionPtr& callbackPos) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::tryGetCallback()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackSelectSQL(callbackNo, m_DbName));
        if (!resultset.next())
        {
            callback.reset();
            callbackPos.reset();
            return false;
        }

        callback = CallbackSqlMapper::mapCallback(resultset);

        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::tryGetCallback()", "", __FILE__, __LINE__ ));
        }

        resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackPosSelectSQL(callback->getCritNo(), m_DbName));
        callbackPos = domMod::makeCallbackPosCollection();
        while (resultset.next())
        {
            callbackPos->add(CallbackSqlMapper::mapCallbackPos(resultset));
        }
        if (callbackPos->isEmpty())
        {
            throw libcsc::exceptions::SqlNotFoundException(basar::ExceptInfo("Repository::tryGetCallback()", "", __FILE__, __LINE__ ));
        }
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::tryGetCallback()");
        throw;
    }

    return true;
}

domMod::ICallbackItemPtr Repository::findCallbackItem(basar::Int32 const callbackNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCallbackItem()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackItemSelectSQL(callbackNo, m_DbName));
        if (!resultset.next())
        {
            return domMod::ICallbackItemPtr();
        }

        domMod::ICallbackItemPtr callbackItem = CallbackSqlMapper::mapCallbackItem(resultset);

        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::findCallbackItem()", "", __FILE__, __LINE__ ) );
        }

        return callbackItem;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCallbackItem()");
        throw;
    }
}

void Repository::writeNewCritPos(basar::Int32 const callbackNo, basar::Int16 statusNo, domMod::ICritPosPtr critPos)
{
    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
    try
    {
        domMod::ICallbackItemPtr callbackItem = findCallbackItem(callbackNo);
        if (callbackItem == NULL)
        {
            throw exceptions::CallbackNotFoundException(basar::ExceptInfo("Repository::writeNewCritPos()", "", __FILE__, __LINE__ ) );
        }
        if (callbackItem->getLockTag() == LockTagSet)
        {
            throw exceptions::CallbackLockedException(basar::ExceptInfo("Repository::writeNewCritPos()", "", __FILE__, __LINE__ ) );
        }

        guard.begin();
        {
            bool statusChanged = false;
            if ((callbackItem->getCallbackStatus() != statusNo)&&(callbackItem->getPosNoDone() != static_cast<libcsc::Int32>(0)))
            {
                callbackItem->setLockTag(LockTagSet);
                callbackItem->setCallbackStatus(statusNo);
                m_UpdateCallbackItemAccessor->execute(CallbackSqlMapper::getUpdateCallbackStatusSQL(m_DbName), CallbackSqlMapper::getUpdateCallbackStatusSqlParameterBinder(callbackItem));
                statusChanged = true;

            }
            if (callbackItem->getPosNoDone() == static_cast<libcsc::Int32>(0))
            {
                callbackItem->setLockTag(LockTagSet);
                if (callbackItem->getCallbackStatus() != statusNo)
                {
					callbackItem->setCallbackStatus(statusNo);
				}
                m_UpdateCallbackItemAccessor->execute(CallbackSqlMapper::getUpdateCallbackItemSQL(m_DbName), CallbackSqlMapper::getUpdateCallbackItemSqlParameterBinder(callbackItem));
            }
            critPos->setCritNo(callbackItem->getCritNo());
            critPos->setPosTypeTag(callbackItem->getPosTypeTag());
            basar::Int32 newPosNo = writeNewCritPos(critPos);

            if (callbackItem->getPosNoDone() == static_cast<libcsc::Int32>(0))
            {
                callbackItem->setLockTag(VarString(LockTagUnset));
                callbackItem->setPosNoDone(newPosNo);
                if (callbackItem->getCallbackStatus() != statusNo)
                {
                    callbackItem->setCallbackStatus(statusNo);
                }
                m_UpdateCallbackItemAccessor->execute(CallbackSqlMapper::getUpdateCallbackItemSQL(m_DbName), CallbackSqlMapper::getUpdateCallbackItemSqlParameterBinder(callbackItem));

            }
            if (statusChanged) 
            {
                callbackItem->setLockTag(VarString(LockTagUnset));
                m_UpdateCallbackItemAccessor->execute(CallbackSqlMapper::getUpdateCallbackStatusSQL(m_DbName), CallbackSqlMapper::getUpdateCallbackStatusSqlParameterBinder(callbackItem));

            }
        }
        guard.commit();
    }
    catch (basar::Exception const& exc)
    {
        guard.rollback();
        std::stringstream ss;
        ss << "Repository::writeNewCritPos(): " << exc.what().c_str();
        BLOG_ERROR(LoggerPool::getLoggerCallback(), ss.str().c_str());
        throw;
    }
}

basar::Int32 Repository::writeNewCritPos(domMod::ICritPosPtr critPos) const
{
    basar::Int32 newPosNo = getNewCritPosNo(critPos->getCritNo(), critPos->getPosTypeTag());
    critPos->setPosNo(newPosNo);
    m_InsertCritPosAccessor->execute(CallbackSqlMapper::getInsertCritPosSQL(m_DbName), CallbackSqlMapper::getInsertCritPosSqlParameterBinder(critPos));
    return newPosNo;
}

basar::Int32 Repository::getNewCritPosNo(basar::Int32 const critNo, basar::VarString const& posTypeTag) const
{
    basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getMaxPosSelectSQL(critNo, posTypeTag, m_DbName));
    return getNewIndexFromSqlMax(resultset);
}

basar::Int32 Repository::getNewIndexFromSqlMax(basar::db::sql::ResultsetRef& resultset) const
{
    resultset.next();
    basar::Int32 maxIndex = resultset.getInt32(0);
    if (maxIndex < 0)
    {
        maxIndex = 0;
    }
    return ++maxIndex;
}

domMod::CallbackDivisionCollectionPtr Repository::getDivisions(basar::Int16 const branchNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::getDivisions()");

    domMod::CallbackDivisionCollectionPtr divisions = domMod::makeCallbackDivisionCollection();
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackDivisionsSelectSQL(branchNo, m_DbName));

        while (resultset.next())
        {
            domMod::ICallbackDivisionPtr division = CallbackSqlMapper::mapCallbackDivision(resultset);
            divisions->add(division);
        }
        return divisions;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::getDivisions()");
        throw;
    }
}

domMod::CallbackReasonCollectionPtr Repository::getReasons(basar::Int16 const branchNo, basar::Int16 const divisionNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::getReasons()");

    domMod::CallbackReasonCollectionPtr reasons = domMod::makeCallbackReasonCollection();
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackReasonsSelectSQL(branchNo, divisionNo, m_DbName));

        while (resultset.next())
        {
            domMod::ICallbackReasonPtr reason = CallbackSqlMapper::mapCallbackReason(resultset);
            reasons->add(reason);
        }
        return reasons;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::getReasons()");
        throw;
    }
}

domMod::CallbackStatusCollectionPtr Repository::getStatuses() const
{
	BLOG_TRACE_METHOD(m_Logger, "Repository::getStatus()");

	domMod::CallbackStatusCollectionPtr status = domMod::makeCallbackStatusCollection();
	try
	{
		basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackStatusesSelectSQL(m_DbName));

		while (resultset.next())
		{
			domMod::ICallbackStatusPtr statusItem = CallbackSqlMapper::mapCallbackStatus(resultset);
			status->add(statusItem);
		}
		return status;
	}
	catch (basar::Exception const&)
	{
		BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::getStatus()");
		throw;
	}
}

bool Repository::isCallbackStatusVisibile() const
{
	BLOG_TRACE_METHOD(m_Logger, "Repository::isCallbackStatusVisibile()");
	try
	{
		basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackStatusVisibilitySelectSQL(m_DbName));
		bool visible = false;
		if (!resultset.next())
		{
			return false;
		}
		visible = CallbackSqlMapper::mapCallbackStatusVisibility(resultset);
        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::isCallbackStatusVisibile()", "", __FILE__, __LINE__));
        }


		return visible;
	}
	catch (basar::Exception const&)
	{
		BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::isCallbackStatusVisibile()");
		throw;
	}
}

domMod::ICallbackReasonPtr Repository::findCallbackReason(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCallbackReason()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackReasonSelectSQL(branchNo, divisionNo, reasonNo, m_DbName));
        if (!resultset.next())
        {
            throw libcsc::exceptions::SqlNotFoundException(basar::ExceptInfo("Repository::findCallbackReason()", "", __FILE__, __LINE__ ) );
        }

        domMod::ICallbackReasonPtr reason = CallbackSqlMapper::mapCallbackReason(resultset);

        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::findCallbackReason()", "", __FILE__, __LINE__ ) );
        }
        return reason;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCallbackReason()");
        throw;
    }
}

domMod::CallbackCustomerCollectionPtr Repository::findCustomers(FindCustomersRequestPtr const findCustomersRequest) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCustomers()");

    domMod::CallbackCustomerCollectionPtr customers = domMod::makeCallbackCustomerCollection();
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getFindCustomersSelectSQL(findCustomersRequest, m_DbName));

        while (resultset.next())
        {
            domMod::ICallbackCustomerPtr customer = CallbackSqlMapper::mapCustomer(resultset);
            customers->add(customer);
        }
        return customers;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCustomers()");
        throw;
    }
}

basar::Int32 Repository::getFindCustomersCount(FindCustomersRequestPtr const findCustomersRequest) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::getFindCustomersCount()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getFindCustomersCountSelectSQL(findCustomersRequest, m_DbName));
        resultset.next();
        return resultset.getInt32(0);
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::getFindCustomersCount()");
        throw;
    }
}

basar::Int32 Repository::writeNewCallback(domMod::ICallbackItemPtr callback, domMod::ICritPtr crit, domMod::ICritPosPtr critPos)
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::writeNewCallback()");

    basar::Int32 newCallbackNo;
    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
    try
    {
        guard.begin();
        {
            basar::Int32 newCritNo = writeNewCrit(crit);

            critPos->setCritNo(newCritNo);
            basar::Int32 newPosNo = writeNewCritPos(critPos);

            callback->setCritNo(newCritNo);
            callback->setPosNo(newPosNo);
            newCallbackNo = writeNewCallback(callback);
            //updateCallbackStaus(callback);
        }
        guard.commit();
        return newCallbackNo;
    }
    catch (basar::Exception const& exc)
    {
        guard.rollback();
        std::stringstream ss;
        ss << "Repository::writeNewCallback(): " << exc.what().c_str();
        BLOG_ERROR(LoggerPool::getLoggerCallback(), ss.str().c_str());
        throw;
    }
}

basar::Int32 Repository::writeNewCrit(domMod::ICritPtr crit) const
{
    basar::Int32 newCritNo = getNewCritNo();
    crit->setCritNo(newCritNo);
    m_InsertCritAccessor->execute(CallbackSqlMapper::getInsertCritSQL(m_DbName), CallbackSqlMapper::getInsertCritSqlParameterBinder(crit));
    return newCritNo;
}

basar::Int32 Repository::getNewCritNo() const
{
    basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getMaxCritNoSelectSQL(m_DbName));
    return getNewIndexFromSqlMax(resultset);
}

basar::Int32 Repository::writeNewCallback(domMod::ICallbackItemPtr callbackItem) const
{
    basar::Int32 newCallbackNo = getNewCallbackNo();
    callbackItem->setCallbackNo(newCallbackNo);
    m_InsertCallbackItemAccessor->execute(CallbackSqlMapper::getInsertCallbackItemSQL(m_DbName), CallbackSqlMapper::getInsertCallbackItemSqlParameterBinder(callbackItem));
    return newCallbackNo;
}

void Repository::updateCallbackStaus(domMod::ICallbackItemPtr callbackItem) const
{
	m_UpdateCallbackItemAccessor->execute(CallbackSqlMapper::getUpdateCallbackStatusSQL(m_DbName), CallbackSqlMapper::getUpdateCallbackStatusSqlParameterBinder(callbackItem));
}

basar::Int32 Repository::getNewCallbackNo() const
{
    basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getMaxCallbackNoSelectSQL(m_DbName));
    return getNewIndexFromSqlMax(resultset);
}

basar::VarString Repository::getCallbackMailingList(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::getCallbackMailingList()");

    try
    {
        domMod::ICallbackReasonPtr reason = findCallbackReason(branchNo, divisionNo, reasonNo);
        basar::VarString mailingList(reason->getMailingList());
        mailingList.trim();
        if (mailingList == "")
        {
            domMod::ICallbackDivisionPtr division = findCallbackDivision(branchNo, divisionNo);
            mailingList = division->getMailingList();
            mailingList.trim();
        }
        return mailingList;
    }
    catch (basar::Exception const& exc)
    {
        std::stringstream ss;
        ss << "Repository::getCallbackMailingList(): " << exc.what().c_str();
        BLOG_ERROR(LoggerPool::getLoggerCallback(), ss.str().c_str());
        throw;
    }
}

domMod::ICallbackDivisionPtr Repository::findCallbackDivision(basar::Int16 const branchNo, basar::Int16 const divisionNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCallbackDivision()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackDivisionSelectSQL(branchNo, divisionNo, m_DbName));
        if (!resultset.next())
        {
            throw libcsc::exceptions::SqlNotFoundException(basar::ExceptInfo("Repository::findCallbackDivision()", "", __FILE__, __LINE__ ) );
        }

        domMod::ICallbackDivisionPtr division = CallbackSqlMapper::mapCallbackDivision(resultset);

        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::findCallbackDivision()", "", __FILE__, __LINE__ ) );
        }
        return division;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCallbackDivision()");
        throw;
    }
}

domMod::ICallbackCustomerPtr Repository::findCustomer(basar::Int16 const branchNo, basar::Int32 const customerNo) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCustomer()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackCustomerSelectSQL(branchNo, customerNo, m_DbName));
        if (!resultset.next())
        {
            throw exceptions::CustomerNotFoundException(basar::ExceptInfo("Repository::findCustomer()", "", __FILE__, __LINE__ ) );
        }

        domMod::ICallbackCustomerPtr reason = CallbackSqlMapper::mapCallbackCustomer(resultset);

        if (resultset.next())
        {
            throw libcsc::exceptions::SqlTooManyRowsException(basar::ExceptInfo("Repository::findCustomer()", "", __FILE__, __LINE__ ) );
        }
        return reason;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCustomer()");
        throw;
    }
}

basar::VarString Repository::findUserName(basar::Int16 const branchNo, basar::Int32 const uid) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findUserName()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getCallbackUserNameSelectSQL(branchNo, uid, m_DbName));
        if (!resultset.next())
        {
            throw libcsc::exceptions::SqlNotFoundException(basar::ExceptInfo("Repository::findUserName()", "", __FILE__, __LINE__ ) );
        }

        return resultset.getString(0);
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findUserName()");
        throw;
    }
}

domMod::CallbackOverviewCollectionPtr Repository::findCallbacks(FindCallbacksRequestPtr const findCallbacksRequest) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::findCallbacks()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getFindCallbacksSelectSQL(findCallbacksRequest, m_DbName));

        domMod::CallbackOverviewCollectionPtr callbacks = domMod::makeCallbackOverviewCollection();
        while (resultset.next())
        {
            domMod::ICallbackOverviewItemPtr callback = CallbackSqlMapper::mapCallback4Overview(resultset);
            callbacks->add(callback);
        }
        return callbacks;
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::findCallbacks()");
        throw;
    }
}

basar::Int32 Repository::getFindCallbacksCount(FindCallbacksRequestPtr const findCallbacksRequest) const
{
    BLOG_TRACE_METHOD(m_Logger, "Repository::getFindCallbacksCount()");

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(CallbackSqlMapper::getFindCallbacksCountSelectSQL(findCallbacksRequest, m_DbName));
        resultset.next();
        return resultset.getInt32(0);
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::callback::repo::Repository::getFindCallbacksCount()");
        throw;
    }
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
