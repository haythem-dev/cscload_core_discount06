//-------------------------------------------------------------------------------------------------//
/*! \file
*  \brief  implemtation of generalbranchparameter domain module
*  \author Rolf Raab
*  \date	09.04.2008
*/
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// includes
//-------------------------------------------------------------------------------------------------//
#include "commonheader.h"
#include "generalbranchparameterdm.h"
#include "loggerpool.h"
#include "publicholidayacc.h"
#include "generalbranchparameterdm_definitions.h"
#include "zpldcust_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespaces
//-------------------------------------------------------------------------------------------------//
namespace domMod {

  //-------------------------------------------------------------------------------------------------//

  GeneralBranchParameterDM::GeneralBranchParameterDM() : m_Initialized(0)
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::GeneralBranchParameterDM().");
  }

  //-------------------------------------------------------------------------------------------------//

  GeneralBranchParameterDM::~GeneralBranchParameterDM() 
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::~GeneralBranchParameterDM().");
  }

  //-------------------------------------------------------------------------------------------------//

  void GeneralBranchParameterDM::init(const ConnectionRef activeConn, const Int16 branchNo)
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::init()");

    if (zpldcust::LoggerPool::zpldcust.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL))
    {
      VarString msg;
      msg.format("GeneralBranchParameterDM::init(). Branch:<%d>", branchNo);
      zpldcust::LoggerPool::zpldcust.forcedLog(log4cplus::DEBUG_LOG_LEVEL, msg.c_str(), __FILE__, __LINE__);
    }

    if (0 == m_Initialized) 
    {
      m_PublicHolidayACC = basar::db::aspect::Manager::getInstance().createAccessorInstance(
        "AccInstPublicHoliday", "AccDefinitionPublicHoliday", activeConn);
    }
    ++m_Initialized;

    VarString defParam;
    defParam.format("%s=%d;", lit::pdm_generalbranchparameter::BRANCHNO.getName().c_str(), branchNo);
    m_PublicHolidayACC.setDefaultParameter(defParam);
  }

  //-------------------------------------------------------------------------------------------------//

  void GeneralBranchParameterDM::shutdown()
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::shutdown().");

    if (0 == m_Initialized)
      return;

    --m_Initialized;

    if (0 == m_Initialized)
    {
      FREE_ACCESSOR(m_PublicHolidayACC);
    }
  }

  //-------------------------------------------------------------------------------------------------//

  AccessorPropertyTableRef GeneralBranchParameterDM::findAllPublicHolidaysByBranchno()
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::findAllPublicHolidaysByBranchno()");

    AccessorPropertyTableRef result;
    ExecuteResultInfo executeResult;

    executeResult = m_PublicHolidayACC.execute("amSelectAllPublicHolidaysByBranchno", true, true, basar::db::aspect::HOLD_RECORDSET);
    if (false == executeResult.hasError())
      result = m_PublicHolidayACC.getPropertyTable();
    return result;
  }

  //-------------------------------------------------------------------------------------------------//

  bool GeneralBranchParameterDM::isWorkDay(Date dateToCheck)
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::isWorkDay()");

    Int32 weekday = dateToCheck.getDayOfWeek();

    // Saturday & Sunday are generally no workdays
    if (weekday == basar::Date::SUNDAY || weekday == basar::Date::SATURDAY)
      return false;

    // read table of holidays if empty
    if (m_PublicHolidayACC.getPropertyTable().empty())
      findAllPublicHolidaysByBranchno();

    AccessorPropertyTable_YIterator yitHoliday = m_PublicHolidayACC.getPropertyTable().begin();
    while (!yitHoliday.isEnd())
    {
      // day of year in format MMDD for mode 0
      Int16 day_mode_0 = (100 * dateToCheck.getMonth()) + dateToCheck.getDay();

      // day of Easter Sunday for mode 1
      Date easter_sunday = basar::Date::getEasterSunday(dateToCheck.getYear());
      Int16 day_mode_1 = easter_sunday.getDayOfYear();

      // year for check if public holiday exists in this year
      Int16 year = dateToCheck.getYear();

      Int16 day = yitHoliday.getInt16(lit::pdm_generalbranchparameter::DAY.getName());
      Int16 year_from = yitHoliday.getInt16(lit::pdm_generalbranchparameter::YEAR_FROM.getName());
      Int16 year_to = yitHoliday.getInt16(lit::pdm_generalbranchparameter::YEAR_TO.getName());

      if (year_from <= year && (year <= year_to || year_to == 0))
      {
        switch (yitHoliday.getInt16(lit::pdm_generalbranchparameter::MODE))
        {
          case 0 : // absolute day in format MMDD
            if (day == day_mode_0)
              return false;
            break;
          case 1 : // relative to easter sunday
            if ((dateToCheck.getDayOfYear() - day_mode_1) == day)
              return false;
            break;
        }
      }
      yitHoliday++;
    }
    return true;
  }

  //-------------------------------------------------------------------------------------------------//

  Date GeneralBranchParameterDM::getLastWorkDayBefore(Date date)
  {
    BLOG_TRACE_METHOD(zpldcust::LoggerPool::zpldcust, "GeneralBranchParameterDM::getLastWorkDayBefore()");

    Date retDate = date;

    retDate.addDays(-1);
    while (!isWorkDay(retDate))
      retDate.addDays(-1);
    return retDate;
  }

  //-------------------------------------------------------------------------------------------------//

} // namespace domMod

//-------------------------------------------------------------------------------------------------//
