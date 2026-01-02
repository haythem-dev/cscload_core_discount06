#include "orderresponserepository.h"
#include "orderresponsesqlmapper.h"
#include "orderresponse.h"
#include <persistence/iaccessor.h>
#include <exceptions/sqlduplicateexception.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace msv3 {

OrderResponseRepository::OrderResponseRepository()
{
}

OrderResponseRepository::~OrderResponseRepository()
{
    m_FindAccessor.reset();
}

void OrderResponseRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void OrderResponseRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void OrderResponseRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
{
    m_UpdateAccessor = accessor;
}

OrderResponsePtr OrderResponseRepository::createEmptyOrderResponse() const
{
	return boost::make_shared<OrderResponse>();
}

OrderResponsePtr OrderResponseRepository::findOrderResponse(const basar::VarString& orderUuid) const
{
	OrderResponsePtr orderResponse = createEmptyOrderResponse();

	try
	{
		basar::db::sql::ResultsetRef resultset;
		resultset = m_FindAccessor->select(
			OrderResponseSQLMapper::getSelectSQL(),
			OrderResponseSQLMapper::getSelectSqlParameterBinder(orderUuid));
		
		if (resultset.next())
		{
			OrderResponseSQLMapper mapper(orderResponse, resultset);
			mapper.map();
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}

	return orderResponse;
}

void OrderResponseRepository::saveOrderResponse(OrderResponsePtr orderResponse) const
{
	basar::db::sql::ExecuteReturnInfo retVal;
	if (orderResponse->isDirty())
	{
		retVal = m_InsertAccessor->execute(
			OrderResponseSQLMapper::getInsertSQL(),
			OrderResponseSQLMapper::getInsertSqlParameterBinder(orderResponse),
			false
		);
		if (false == retVal.hasError())
		{
			OrderResponseSQLMapper mapper(orderResponse);
			mapper.mapSerial(static_cast<basar::Int32>(m_InsertAccessor->getLastInsertedSerial()));
		}
		else if (basar::db::sql::DBErrorCode::INSERT_DUPL == retVal.getError())
		{
			throw libcsc::exceptions::SqlDuplicateException(basar::ExceptInfo("TransmissionResponseRepository::saveTransmissionResponse()", "", __FILE__, __LINE__));
		}
	}
	else if (orderResponse->isClean())
	{
		retVal = m_UpdateAccessor->execute(
			OrderResponseSQLMapper::getUpdateSQL(),
			OrderResponseSQLMapper::getUpdateSqlParameterBinder(orderResponse),
			false
		);
	}
	else
	{
		// nothing to do
	}
	if (retVal.hasError())
	{
		throw libcsc::exceptions::PersistenceException(basar::ExceptInfo("TransmissionResponseRepository::saveTransmissionResponse()", "", __FILE__, __LINE__));
	}
}

} // end namespace msv3
} // end namespace libcsc
