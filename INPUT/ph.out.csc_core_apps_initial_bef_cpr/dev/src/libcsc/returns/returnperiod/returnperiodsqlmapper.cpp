#include "returnperiodsqlmapper.h"
#include <logger/loggerpool.h>


namespace libcsc {
	namespace returns {

		ReturnPeriodSQLMapper::ReturnPeriodSQLMapper(ReturnPeriodPtr returnPeriod, const basar::db::sql::ResultsetRef resultSet)
			: ReturnPeriodMapperBase(returnPeriod), m_ResultSet(resultSet)
		{
		}

		ReturnPeriodSQLMapper::~ReturnPeriodSQLMapper()
		{
		}

		const basar::VarString ReturnPeriodSQLMapper::getSelectAllSQL()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnPeriodSQLMapper::getSelectAllSQL()");

			std::stringstream sql;

			sql <<
				"SELECT "
				"r.articletypeid, "
				"r.periodofvalidreturn, "
				"r.returnreasoncode, "
				"ra.name "
				"FROM returnperiod r "
				"LEFT JOIN returnperiodarticletype ra ON r.articletypeid = ra.articletypeid "
				"ORDER BY r.articletypeid";

			BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

			return sql.str();
		}

		void ReturnPeriodSQLMapper::doMap()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnRuleBookSQLMapper::doMap()");

			if (m_ResultSet.isNull())
			{
				throw;
			}

			setArticleTypeID(m_ResultSet.getInt16("articletypeid"));
			setReturnReasonCode(m_ResultSet.getString("returnreasoncode"));
			setPeriodOfValidReturn(m_ResultSet.getInt16("periodofvalidreturn"));
			setName(m_ResultSet.getString("name"));
		}

	} //returns
} //libcsc
