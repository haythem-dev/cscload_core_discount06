#include "transmissionresponserepository.h"
#include "transmissionresponsesqlmapper.h"
#include "transmissionresponse.h"
#include <persistence/iaccessor.h>
#include <exceptions/sqlduplicateexception.h>
#include <boost/make_shared.hpp>


namespace libcsc {
namespace msv3 {

TransmissionResponseRepository::TransmissionResponseRepository()
{
}

TransmissionResponseRepository::~TransmissionResponseRepository()
{
    m_FindAccessor.reset();
}

void TransmissionResponseRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void TransmissionResponseRepository::injectFindByInternalHashAccessor(persistence::IAccessorPtr accessor)
{
	m_FindByInternalHashAccessor = accessor;
}


void TransmissionResponseRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
    m_InsertAccessor = accessor;
}

void TransmissionResponseRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
{
    m_UpdateAccessor = accessor;
}

TransmissionResponsePtr TransmissionResponseRepository::createEmptyTransmissionResponse() const
{
	return boost::make_shared<TransmissionResponse>();
}

TransmissionResponsePtr TransmissionResponseRepository::findTransmissionResponse(const basar::VarString& transmissionUuid) const
{
	TransmissionResponsePtr transmissionResponse;

	try
	{
		basar::db::sql::ResultsetRef resultset;
		resultset = m_FindAccessor->select(
			TransmissionResponseSQLMapper::getSelectSQL(),
			TransmissionResponseSQLMapper::getSelectSqlParameterBinder(transmissionUuid));
		
		if (resultset.next())
		{
			transmissionResponse = createEmptyTransmissionResponse();
			TransmissionResponseSQLMapper mapper(transmissionResponse, resultset);
			mapper.map();
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}

	return transmissionResponse;
}

TransmissionResponsePtr TransmissionResponseRepository::findByInternalHash(
	const basar::Int16& branchNo,
	const basar::Int32& customerNo,
	const basar::VarString& internalHash,
	const basar::DateTime& checkFrom) const
{
	TransmissionResponsePtr transmissionResponse;

	try
	{
		// TODO FN
		basar::db::sql::ResultsetRef resultset;
		resultset = m_FindByInternalHashAccessor->select(
			TransmissionResponseSQLMapper::getSelectByInternalHashSQL(),
			TransmissionResponseSQLMapper::getSelectByInternalHashSqlParameterBinder(branchNo, customerNo, internalHash, checkFrom));

		if (resultset.next())
		{
			transmissionResponse = createEmptyTransmissionResponse();
			TransmissionResponseSQLMapper mapper(transmissionResponse, resultset);
			mapper.map();
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}

	return transmissionResponse;
}


void TransmissionResponseRepository::saveTransmissionResponse(TransmissionResponsePtr transmissionResponse) const
{
	basar::db::sql::ExecuteReturnInfo retVal;

	if (transmissionResponse->isDirty())
	{
		retVal = m_InsertAccessor->execute(
			TransmissionResponseSQLMapper::getInsertSQL(),
			TransmissionResponseSQLMapper::getInsertSqlParameterBinder(transmissionResponse),
			false
		);
		if (false == retVal.hasError())
		{
			TransmissionResponseSQLMapper mapper(transmissionResponse);
			mapper.mapSerial(static_cast<basar::Int32>(m_InsertAccessor->getLastInsertedSerial()));
		}
		else if (basar::db::sql::DBErrorCode::INSERT_DUPL == retVal.getError())
		{
			throw libcsc::exceptions::SqlDuplicateException(basar::ExceptInfo("TransmissionResponseRepository::saveTransmissionResponse()", "", __FILE__, __LINE__));
		}
	}
	else if (transmissionResponse->isClean())
	{
		retVal = m_UpdateAccessor->execute(
			TransmissionResponseSQLMapper::getUpdateSQL(),
			TransmissionResponseSQLMapper::getUpdateSqlParameterBinder(transmissionResponse),
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
