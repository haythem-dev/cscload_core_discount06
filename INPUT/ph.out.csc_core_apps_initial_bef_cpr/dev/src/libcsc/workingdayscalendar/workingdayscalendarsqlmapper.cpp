#include "workingdayscalendarsqlmapper.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace workingdayscalendar {

	WorkingdaysCalendarSQLMapper::WorkingdaysCalendarSQLMapper(WorkingdaysCalendarPtr workingdaysCalendar, const basar::db::sql::ResultsetRef resultSet)
		: WorkingdaysCalendarMapperBase(workingdaysCalendar), m_ResultSet(resultSet)
	{

	}

	WorkingdaysCalendarSQLMapper::~WorkingdaysCalendarSQLMapper()
	{

	}

	const basar::VarString WorkingdaysCalendarSQLMapper::getSelectSQL(const basar::Int16& branchNo, const basar::Int32& calendarDate)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "ReturnRuleBookSQLMapperWorkingdaysCalendarSQLMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"branchno, "
			"calendardate, "
			"dayofyear, "
			"weekofyear, "
			"workingdayofmonth, "
			"workingdayofyear, "
			"workingdayofweek, "
			"daytype "
			"FROM workingdayscalendar "
			"WHERE branchno=" << branchNo << " AND "
			"calendardate= " << calendarDate << " ";

		BLOG_TRACE(LoggerPool::getLoggerWorkingdaysCalendar(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString WorkingdaysCalendarSQLMapper::getSelectBetweenSQL(const basar::Int16& branchNo, const basar::Int32& calendarDateFrom, const basar::Int32& calendarDateTo)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "ReturnRuleBookSQLMapperWorkingdaysCalendarSQLMapper::getSelectBetweenSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"CAST(count(*) AS INT) AS workingdaysbetween "
			"FROM workingdayscalendar "
			"WHERE calendardate BETWEEN " << calendarDateFrom << " AND " << calendarDateTo<< " AND "
			"branchno = " << branchNo << " AND "
			"daytype = 'A'";

		BLOG_TRACE(LoggerPool::getLoggerWorkingdaysCalendar(), sql.str().c_str());

		return sql.str();
	}

	void WorkingdaysCalendarSQLMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "WorkingdaysCalendarSQLMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setBranchNo(m_ResultSet.getInt16("branchno"));
		setCalendarDate(m_ResultSet.getInt32("calendardate"));
		setDayOfYear(m_ResultSet.getInt16("dayofyear"));
		setWeekOfYear(m_ResultSet.getInt16("weekofyear"));
		setWorkingdayOfMonth(m_ResultSet.getInt16("workingdayofmonth"));
		setWorkingdayOfYear(m_ResultSet.getInt16("workingdayofyear"));
		setWorkingdayOfWeek(m_ResultSet.getInt16("workingdayofweek"));
		setDayType(m_ResultSet.getString("daytype"));
	}

} // end namespace workingdayscalendar
} // end namespace libcsc
