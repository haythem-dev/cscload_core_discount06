#include "returnperiodmapperbase.h"
#include "returnperiod.h"

namespace libcsc {
	namespace returns {

		ReturnPeriodMapperBase::ReturnPeriodMapperBase(ReturnPeriodPtr returnPeriod)
			: m_ReturnPeriod(returnPeriod)
		{
		}

		ReturnPeriodMapperBase::~ReturnPeriodMapperBase()
		{
		}

		void ReturnPeriodMapperBase::map()
		{
			doMap();
		}

		void ReturnPeriodMapperBase::setArticleTypeID(const basar::Int16& articleTypeID)
		{
			m_ReturnPeriod->m_ArticleTypeID = articleTypeID;
			m_ReturnPeriod->m_ArticleTypeID.setClean();
		}

		void ReturnPeriodMapperBase::setReturnReasonCode(const basar::VarString& reasonCode)
		{
			m_ReturnPeriod->m_ReturnReasonCode = reasonCode;
			m_ReturnPeriod->m_ReturnReasonCode.setClean();
		}

		void ReturnPeriodMapperBase::setPeriodOfValidReturn(const basar::Int16& periodOfValidReturn)
		{
			m_ReturnPeriod->m_PeriodOfValidReturn = periodOfValidReturn;
			m_ReturnPeriod->m_PeriodOfValidReturn.setClean();
		}

		void ReturnPeriodMapperBase::setName(const basar::VarString& name)
		{
			m_ReturnPeriod->m_Name = name;
			m_ReturnPeriod->m_Name.setClean();
		}

	} //returns
} //libscs
