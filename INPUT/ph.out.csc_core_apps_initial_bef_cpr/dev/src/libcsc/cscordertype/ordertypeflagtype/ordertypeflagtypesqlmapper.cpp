#include "ordertypeflagtypesqlmapper.h"
#include "logger/loggerpool.h"
#include <sstream>

namespace libcsc
{
	namespace cscordertype
	{
		OrderTypeFlagTypeSqlMapper::OrderTypeFlagTypeSqlMapper(
			OrderTypeFlagTypePtr orderType,
			const basar::db::sql::ResultsetRef resultSet
		)
			: OrderTypeFlagTypeMapperBase(orderType),
			m_ResultSet(resultSet)
		{
		}

		OrderTypeFlagTypeSqlMapper::~OrderTypeFlagTypeSqlMapper()
		{
		}

		const basar::VarString OrderTypeFlagTypeSqlMapper::getSelectSQL(const basar::VarString& orderType)
		{
			BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "OrderTypeFlagTypeSqlMapper::getSelectSQL()");

			std::stringstream ss;
			ss <<
				"SELECT "
				"ot.cscordertype, "
				"ot.name, "
				"otf.ordertypeflagtype, "
				"otf.ordertypeflag, "
				"otft.description, "
				"otft.index_dkaua "
				"FROM ordertype ot "
				"LEFT JOIN ordertypeflags otf ON otf.cscordertype = ot.cscordertype "
				"LEFT JOIN ordertypeflagtype otft ON otft.ordertypeflagtype = otf.ordertypeflagtype "
				"WHERE ot.cscordertype = '" << orderType << "';";

			BLOG_TRACE(LoggerPool::getLoggerParameter(), ss.str().c_str());

			return ss.str();
		}

		void OrderTypeFlagTypeSqlMapper::doMap()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "OrderTypeFlagTypeSqlMapper::doMap()");

			if (m_ResultSet.isNull())
			{
				throw;
			}

			setOrderType(m_ResultSet.getString("cscordertype"));
			setName(m_ResultSet.getString("name"));
			setOrderTypeFlagType(m_ResultSet.getInt16("ordertypeflagtype"));
			setOrderTypeFlag(m_ResultSet.getInt16("ordertypeflag"));
			setDescription(m_ResultSet.getString("description"));
			setIndexDKAUA(m_ResultSet.getInt16("index_dkaua"));
		}

	} // end namespace cscordertype
} // end namespace libcsc
