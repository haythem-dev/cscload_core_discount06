//-------------------------------------------------------------------------------------------------//
/*! \file   loadcustomeruc.cpp
 *  \brief  Implementation of use case class.
 *  \author	Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#include "commonheader.h"
#include "loadcustomerappl.h"
#include "loadcustomeruc.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//-------------------------------------------------------------------------------------------------//

namespace zpldcust {
namespace useCase {

//-------------------------------------------------------------------------------------------------//

LoadCustomerUC::LoadCustomerUC()
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerUC::LoadCustomerUC()");
}

//-------------------------------------------------------------------------------------------------//

LoadCustomerUC::~LoadCustomerUC()
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerUC::~LoadCustomerUC()");
}

//-------------------------------------------------------------------------------------------------//

LoadCustomerApplBase& LoadCustomerUC::getManager()
{
  return LoadCustomerAppl::getInstance();
}

//-------------------------------------------------------------------------------------------------//

EventReturnType LoadCustomerUC::run(IEventSource&, AccessorPropertyTable_YIterator yitFromEvSrc)
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "LoadCustomerUC::run()");

  EventReturnStruct ret;
  I18nString        msg;
  ConnectionRef     conn     = getManager().m_Connection.getInfxConnection();
  Int16             branchno = basar::login::Manager::getInstance().getAreaID();

  registerEventHandlers(true);

  //! \note initialize domain modules with opened connection ! 
  getManager().m_CustomerDM.init(getManager().m_Connection.getInfxConnection(), branchno);
  getManager().m_CicsCustomerDM.init(getManager().m_Connection.getCicsConnection(), branchno);
  getManager().m_GeneralBranchParameterDM.init(getManager().m_Connection.getInfxConnection(), branchno);

  ret = SystemEventManager::getInstance().fire("LoadCustomer", yitFromEvSrc);

  getManager().m_CustomerDM.shutdown();
  getManager().m_CicsCustomerDM.shutdown();
  getManager().m_GeneralBranchParameterDM.shutdown();

  registerEventHandlers(false);
  return ret;
}

//-------------------------------------------------------------------------------------------------//

BEGIN_HANDLERS_REGISTRATION(LoadCustomerUC)
  SYSTEM_EVENT_HANDLER_REGISTRATION(LoadCustomerUC, LoadCustomer)
END_HANDLERS_REGISTRATION()

//-------------------------------------------------------------------------------------------------//

EventReturnType LoadCustomerUC::handleLoadCustomer(basar::appl::IEventSource&, basar::db::aspect::AccessorPropertyTable_YIterator yitFromEvSrc)
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "Event LoadCustomerUC::handleLoadCustomer()");

  EventReturnStruct               ret;
  AccessorPropertyTableRef        tabCicsCustomer;
  AccessorPropertyTable_YIterator yitCicsCustomer;
  AccessorPropertyTable_YIterator yitSearch;
  I18nString                      mode = zpldcust::MODE_FULL;
  ConstString                     YYMMDD = "%02y%02m%02d"; //!< field formatted Date  YYMMDD

  yitSearch = getManager().m_CicsCustomerDM.addEmptyDKKUL();
  if (yitFromEvSrc.isContainedAndSet(lit::zpldcust::MODE) &&
      yitFromEvSrc.getString(lit::zpldcust::MODE) == zpldcust::MODE_LAST)
  {
    Date dateFrom = getManager().m_GeneralBranchParameterDM.getLastWorkDayBefore(Date::getCurrent());
    yitSearch.setInt32(lit::zpldcust::KUL_AEDAT, dateFrom.toString(YYMMDD).stoi());
    mode = zpldcust::MODE_LAST;
  }
  //! \note read restriction for KUL_GRP from uadm parameter "DKKUL_GRP"
 	I18nString branch;
  I18nString restrictionKUL_GRP;
  branch.format("%d", basar::login::Manager::getInstance().getAreaID());

  basar::login::Manager::getInstance().getParaValue(branch, UADM_DKKUL_GRP, restrictionKUL_GRP);
  if (restrictionKUL_GRP.length() > 0)
    yitSearch.setString(lit::zpldcust::KUL_GRP_SEARCH, restrictionKUL_GRP);

  tabCicsCustomer = getManager().m_CicsCustomerDM.findDKKULByPattern(yitSearch);
  if (tabCicsCustomer.isNull())
  {
    ret.ret = basar::appl::HANDLER_ERROR;
    ret.message = "Error while reading from DKKUL!";
    BLOG_DEBUG(LoggerPool::zpldcust, ret.message);
    return ret;
  }

  logStart(basar::login::Manager::getInstance().getAreaID(), mode);
  yitCicsCustomer = tabCicsCustomer.begin();
  while (!yitCicsCustomer.isEnd())
  {
    ret.message.format("Checking DKKUL FIL1 %d; IDF %d; AEDAT %d",
      yitCicsCustomer.getInt16(lit::zpldcust::KUL_FIL1),
      yitCicsCustomer.getInt32(lit::zpldcust::KUL_IDF),
      yitCicsCustomer.getInt32(lit::zpldcust::KUL_AEDAT));
    BLOG_DEBUG(LoggerPool::zpldcust, ret.message);

    ret = checkCustomerUpdate(yitCicsCustomer);
    switch (ret.ret)
    {
      case basar::appl::HANDLER_OK :        break;
      case basar::appl::HANDLER_INFO :      BLOG_TRACE(LoggerPool::zpldcust, ret.message);
                                            break;
      case basar::appl::HANDLER_ERROR :     // fall through
      case basar::appl::HANDLER_NOT_FOUND : BLOG_ERROR(LoggerPool::zpldcust, ret.message);
                                            break;
    }
    ++yitCicsCustomer;
  }
  logEnd(basar::login::Manager::getInstance().getAreaID(), mode);
	return ret;
}

//-------------------------------------------------------------------------------------------------//

EventReturnType LoadCustomerUC::checkCustomerUpdate(AccessorPropertyTable_YIterator yitCicsCustomer)
{
  BLOG_TRACE_METHOD(LoggerPool::zpldcust, "Event LoadCustomerUC::checkCustomerUpdate()");

  EventReturnStruct               ret;
  ExecuteResultInfo               resInfo;
  I18nString                      searchStr;
  AccessorPropertyTable_YIterator yitSearch;
  AccessorPropertyTable_YIterator yitCustomer;
  Int16                           branchno = basar::login::Manager::getInstance().getAreaID();
  I18nString                      kul_plz;

  searchStr.format("%s=%d;", lit::zpldcust::CUSTOMERNO.getName().c_str(), 
    yitCicsCustomer.getInt32(lit::zpldcust::KUL_IDF));
  yitSearch = basar::db::aspect::Manager::getInstance().createAccessorYIterator(searchStr);

  kul_plz.itos(yitCicsCustomer.getInt32(lit::zpldcust::KUL_PLZ));

  yitCustomer = getManager().m_CustomerDM.findCustomer(yitSearch);
  if (yitCustomer.isNull() || yitCustomer.isEnd()) //! \note Prüfung, ob gelesene IDF schon vorhanden
  {
    //! \note wenn nicht, dann Neuanlage und Flag auf 0
    yitCustomer = getManager().m_CustomerDM.addEmptyCustomer();
    yitCustomer.setInt32(lit::zpldcust::CUSTOMERNO, yitCicsCustomer.getInt32(lit::zpldcust::KUL_IDF));
    yitCustomer.setString(lit::zpldcust::CUSTOMER_NAME, yitCicsCustomer.getString(lit::zpldcust::KUL_NAM1));
    yitCustomer.setString(lit::zpldcust::POSTAL_CODE, kul_plz);
    yitCustomer.setString(lit::zpldcust::CITY, yitCicsCustomer.getString(lit::zpldcust::KUL_ORT));
    
	if (yitCicsCustomer.getInt16(lit::zpldcust::KUL_VFIL) > 0) // INC-030998: wenn VFIL gefüllt, dann mit dieser branchno anlegen, da Kunde dorthin übertragen wird.
		yitCustomer.setInt16(lit::zpldcust::BRANCHNO, yitCicsCustomer.getInt16(lit::zpldcust::KUL_VFIL));
	else
		yitCustomer.setInt16(lit::zpldcust::BRANCHNO, yitCicsCustomer.getInt16(lit::zpldcust::KUL_FIL1));
	
    yitCustomer.setInt16(lit::zpldcust::MULTIPLECUSTFLAG, zpldcust::MULTIPLECUSTFLAG_NEW);
    m_NewRows++;
  }
  else
  {
    //! \note prüfen, ob die gelesene Filialnummer gleich der hinterlegten ist
    if (yitCustomer.getInt16(lit::zpldcust::BRANCHNO) == branchno)
    {
      //! \note wenn ja, dann Update und Flag auf 1, wenn es aktuell 2 ist
      yitCustomer.setString(lit::zpldcust::CUSTOMER_NAME, yitCicsCustomer.getString(lit::zpldcust::KUL_NAM1));
      yitCustomer.setString(lit::zpldcust::POSTAL_CODE, kul_plz);
      yitCustomer.setString(lit::zpldcust::CITY, yitCicsCustomer.getString(lit::zpldcust::KUL_ORT));
      if (yitCustomer.getInt16(lit::zpldcust::MULTIPLECUSTFLAG) == zpldcust::MULTIPLECUSTFLAG_DIFFERENCE)
        yitCustomer.setInt16(lit::zpldcust::MULTIPLECUSTFLAG, zpldcust::MULTIPLECUSTFLAG_UPDATED);
      m_Updated++;
    }
    else
    {
      //! \note ansonsten Werte vergleichen (Name, PLZ, Ort) und wenn Differenzen, dann Flag auf 2 setzen
      if (yitCustomer.getString(lit::zpldcust::CUSTOMER_NAME) != yitCicsCustomer.getString(lit::zpldcust::KUL_NAM1) ||
          yitCustomer.getString(lit::zpldcust::POSTAL_CODE) != kul_plz ||
          yitCustomer.getString(lit::zpldcust::CITY) != yitCicsCustomer.getString(lit::zpldcust::KUL_ORT))
      {
        yitCustomer.setInt16(lit::zpldcust::MULTIPLECUSTFLAG, zpldcust::MULTIPLECUSTFLAG_DIFFERENCE);
        m_DiffBranch++;
      }
    }
  }
  resInfo = getManager().m_CustomerDM.saveCustomer(yitCustomer);
  if (resInfo.hasError())
  {
    if (resInfo.getError() == basar::db::aspect::NOT_EXECUTABLE)
    {
      ret.ret = basar::appl::HANDLER_INFO;
      ret.message = "No update of ccustomermaindata necessary!";
    }
    else
    {
      ret.ret = basar::appl::HANDLER_ERROR;
      ret.message = "Error during update of ccustomermaindata!";
    }
  }
  else if (resInfo.getAffectedRows() == 0)
  {
    ret.ret = basar::appl::HANDLER_INFO;
    ret.message = "No update of ccustomermaindata necessary!";
  }
  return ret;
}

//-------------------------------------------------------------------------------------------------//

void LoadCustomerUC::logStart(basar::Int16 branchno, basar::I18nString mode)
{
  I18nString msg;

  m_NewRows = 0;
  m_Updated = 0;
  m_DiffBranch = 0;

  msg.format("---------- START branch %d mode %s ----------", branchno, mode.c_str());
  BLOG_INFO(LoggerPool::zpldcust, msg);
}

//-------------------------------------------------------------------------------------------------//

void LoadCustomerUC::logEnd(basar::Int16 branchno, basar::I18nString mode)
{
  I18nString msg;

  msg.format("New customer: %d", m_NewRows);
  BLOG_INFO(LoggerPool::zpldcust, msg);
  msg.format("Updated: %d", m_Updated);
  BLOG_INFO(LoggerPool::zpldcust, msg);
  msg.format("Differences: %d", m_DiffBranch);
  BLOG_INFO(LoggerPool::zpldcust, msg);
  msg.format("---------- END   branch %d mode %s ----------", branchno, mode.c_str());
  BLOG_INFO(LoggerPool::zpldcust, msg);
}

//-------------------------------------------------------------------------------------------------//
} // namespace useCase
} // namespace zpldcust

//-------------------------------------------------------------------------------------------------//
