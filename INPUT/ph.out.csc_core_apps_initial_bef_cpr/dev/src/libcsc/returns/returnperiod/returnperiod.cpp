#include "returnperiod.h"

namespace libcsc {
	namespace returns {

		ReturnPeriod::ReturnPeriod()
		{}

		ReturnPeriod::~ReturnPeriod()
		{}

		const basar::Int16& ReturnPeriod::getArticleTypeID() const
		{
			return m_ArticleTypeID;
		}

		const basar::VarString& ReturnPeriod::getReturnReasonCode() const
		{
			return m_ReturnReasonCode;
		}

		const basar::Int16& ReturnPeriod::getPeriodOfValidReturn() const
		{
			return m_PeriodOfValidReturn;
		}

		const basar::VarString& ReturnPeriod::getName() const
		{
			return m_Name;
		}

	} // returns
} //libcsc
