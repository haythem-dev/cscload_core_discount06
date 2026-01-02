//-------------------------------------------------------------------------------------------------//
/*! \file	deliveryparamdm.cpp
*   \brief	domain module für deliveryparam data (csubsequentdeliveryparam)
*   \author NTT Data
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#include "deliveryparamdm.h"
#include "infrastructure/accessor/deliveryparam/deliveryparamacc.h"
#include "libutil/exception.h"

namespace subsequentdeliveryrelevantcalculator
{
	namespace domMod
	{
		namespace deliveryparam
		{
			DeliveryParamDM::DeliveryParamDM(const log4cplus::Logger& logger)
				: m_Logger(logger)
			{
				METHODNAME_DEF(DeliveryParamDM, DeliveryParamDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			DeliveryParamDM::~DeliveryParamDM()
			{
				METHODNAME_DEF(DeliveryParamDM, ~DeliveryParamDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void DeliveryParamDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
				m_DbSqlConnection = conn->getCurrentConnection().getSqlConnection();
			}

			basar::db::aspect::ExecuteResultInfo DeliveryParamDM::selectDeliveryParams(basar::Int16 branchno)
			{
				METHODNAME_DEF(DeliveryParamDM, selectDeliveryParams)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getDeliveryParamData().insert(basar::FOR_UNKNOWN);

					whereCondition.setInt16(DELIVERYPARAM_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::deliveryparam::lit::SelectDeliveryParams, whereCondition, true, true, basar::db::aspect::HOLD_RECORDSET);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::deliveryparam::lit::SelectDeliveryParams, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::deliveryparam::lit::SelectDeliveryParams, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::AccessorPropertyTableRef DeliveryParamDM::getDeliveryParamData()
			{
				METHODNAME_DEF(PriceDataDM, getDeliveryParamData)
				BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			void DeliveryParamDM::beginTransaction()
			{
				getDbConnection().beginTransaction();
			}

			void DeliveryParamDM::commitTransaction()
			{
				getDbConnection().commitTransaction();
			}

			void DeliveryParamDM::rollbackTransaction()
			{
				getDbConnection().rollbackTransaction();
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// DeliveryParamData containing deliveryparam data for
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			DeliveryParamData::DeliveryParamData()
				:branchNo(0)
				, ruleId(0)
				, ruleStart(0)
				, value1("")
				, value2("")
				, value3("")
			{

			}

			DeliveryParamData::DeliveryParamData(const DeliveryParamData& other)
			{
				*this = other;
			}

			DeliveryParamData& DeliveryParamData::operator=(const DeliveryParamData& other)
			{
				branchNo = other.branchNo;
				ruleId = other.ruleId;
				ruleStart = other.ruleStart;
				ruleTrue = other.ruleTrue;
				ruleFalse = other.ruleFalse;
				ruleActive = other.ruleActive;
				value1 = other.value1;
				value2 = other.value2;
				value3 = other.value3;
				return *this;
			}
		}
	}
}
