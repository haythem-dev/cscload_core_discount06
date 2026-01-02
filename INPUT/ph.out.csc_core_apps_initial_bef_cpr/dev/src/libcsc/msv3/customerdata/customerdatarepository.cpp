#include "customerdatarepository.h"
#include "customerdatasqlmapper.h"
#include "customerdata.h"
#include <persistence/iaccessor.h>

namespace libcsc {
namespace msv3 {

CustomerDataRepository::CustomerDataRepository()
{
}

CustomerDataRepository::~CustomerDataRepository()
{
    m_FindAccessor.reset();
}

void CustomerDataRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

CustomerDataPtr CustomerDataRepository::findCustomerData(const basar::Int16& branchno, const basar::Int32& customerno) const
{
	CustomerDataPtr customerData = CustomerDataPtr(new CustomerData(branchno, customerno));

	try
	{
		basar::db::sql::ResultsetRef resultset;
		resultset = m_FindAccessor->select(
			CustomerDataSQLMapper::getSelectSQL(),
			CustomerDataSQLMapper::getSelectSqlParameterBinder(customerData->getBranchNo(), customerData->getCustomerNo()));
		
		if (resultset.next())
		{
			CustomerDataSQLMapper mapper(customerData, resultset);
			mapper.map();
		} 
	}
	catch( basar::Exception & )
	{
		throw;
	}

	return customerData;
}

} // end namespace msv3
} // end namespace libcsc
