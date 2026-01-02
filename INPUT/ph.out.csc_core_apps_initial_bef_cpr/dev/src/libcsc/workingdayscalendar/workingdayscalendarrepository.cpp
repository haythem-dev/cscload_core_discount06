#include "workingdayscalendarrepository.h"

#include "workingdayscalendar.h"
#include "workingdayscalendarsqlmapper.h"

#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace workingdayscalendar {

	WorkingdaysCalendarRepository::WorkingdaysCalendarRepository()
	{

	}

	WorkingdaysCalendarRepository::~WorkingdaysCalendarRepository()
	{

	}

	void WorkingdaysCalendarRepository::injectWorkingdaysCalendarAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "WorkingdaysCalendarRepository::injectWorkingdaysCalendarAccessor()");

		m_SelectWorkingdaysCalendarAccessor = accessor;
	}

	WorkingdaysCalendarPtr WorkingdaysCalendarRepository::findWorkingdaysCalendar(const basar::Int16& branchNo, const basar::Int32& calendarDate) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "WorkingdaysCalendarRepository::findWorkingdaysCalendar()");

		WorkingdaysCalendarPtr returnRuleBook;

		try
		{
			basar::db::sql::ResultsetRef resultset = m_SelectWorkingdaysCalendarAccessor->select(
				WorkingdaysCalendarSQLMapper::getSelectSQL(branchNo, calendarDate));

			returnRuleBook = boost::make_shared<WorkingdaysCalendar>();
			WorkingdaysCalendarSQLMapper mapper(returnRuleBook, resultset);
			mapper.map();
		}
		catch (const basar::Exception & e)
		{
			std::stringstream s;
			s << "Error WorkingdaysCalendarRepository::findWorkingdaysCalendar(): " << e.what().c_str();
			BLOG_ERROR(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), s.str().c_str());
			throw;
		}

		return returnRuleBook;
	}

	basar::Int32  WorkingdaysCalendarRepository::getWorkingdaysCalendarDifferenceBetween(const basar::Int16& branchNo, const basar::Int32& calendarDateFrom, const basar::Int32& calendarDateTo) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), "WorkingdaysCalendarRepository::getWorkingdaysCalendarDifferenceBetween()");

		basar::Int32 workDaysBetween = 0;

		try
		{
			basar::db::sql::ResultsetRef resultset = m_SelectWorkingdaysCalendarAccessor->select(
				WorkingdaysCalendarSQLMapper::getSelectBetweenSQL(branchNo, calendarDateFrom, calendarDateTo));

			if (resultset.next())
			{
				workDaysBetween = resultset.getInt32("workingdaysbetween");
			}
		}
		catch (const basar::Exception & e)
		{
			std::stringstream s;
			s << "Error WorkingdaysCalendarRepository::getWorkingdaysCalendarDifferenceBetween(): " << e.what().c_str();
			BLOG_ERROR(libcsc::LoggerPool::getLoggerWorkingdaysCalendar(), s.str().c_str());
			throw;
		}

		return workDaysBetween;
	}



} // end namespace workingdayscalendar
} // end namespace libcsc
