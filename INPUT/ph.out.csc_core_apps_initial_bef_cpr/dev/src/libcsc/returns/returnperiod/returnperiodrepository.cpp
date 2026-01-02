#include "returnperiodrepository.h"
#include <returns/returnperiod/returnperiodsqlmapper.h>
#include <returns/returnperiod/returnperiod.h>
#include <returns/returnperiod/returnperiodptr.h>
#include <persistence/iaccessor.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace returns {

ReturnPeriodRepository::ReturnPeriodRepository()
{
}

ReturnPeriodRepository::~ReturnPeriodRepository()
{
}

void ReturnPeriodRepository::injectReturnPeriodAccessor(persistence::IAccessorPtr accessor)
{
	m_SelectReturnPeriodAccessor = accessor;
}

ReturnPeriodPtr ReturnPeriodRepository::findReturnPeriod(const basar::VarString& returnReasonCode, const ReturnPeriodArticleTypeEnum articleTypeID) const
{
	if (NULL == m_ReturnPeriods.get())
	{
		m_ReturnPeriods = boost::make_shared<ReturnPeriodCollection>();
		basar::db::sql::ResultsetRef resultset = m_SelectReturnPeriodAccessor->select(
			ReturnPeriodSQLMapper::getSelectAllSQL());

		while (resultset.next())
		{
			ReturnPeriodPtr returnPeriod = boost::make_shared<ReturnPeriod>();
			ReturnPeriodSQLMapper mapper(returnPeriod, resultset);
			mapper.map();
			m_ReturnPeriods->push_back(returnPeriod);
		}
	}

	ReturnPeriodPtr returnPeriod;
	ReturnPeriodCollection::const_iterator it = m_ReturnPeriods->begin();
	while (it != m_ReturnPeriods->end())
	{
		if ((*it)->getArticleTypeID() == articleTypeID &&
			(*it)->getReturnReasonCode() == returnReasonCode)
		{
			returnPeriod = (*it);
			break;
		}
		++it;
	}
	return returnPeriod;
}

} // namespace returns
} //namespace libcsc
