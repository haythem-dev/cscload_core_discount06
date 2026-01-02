//----------------------------------------------------------------------------
/*! \file   connection.cpp
 *  \brief  connection class implementation
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#include "commonheader.h"
#include "connection.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//----------------------------------------------------------------------------

namespace zpldcust {

//----------------------------------------------------------------------------

Connection::Connection()
{
}

//----------------------------------------------------------------------------

Connection::~Connection()
{
}

//----------------------------------------------------------------------------

void Connection::connect()
{
  VarString msg;

  setInfxDbInfo();
  m_InfxConn = basar::db::aspect::Manager::getInstance().createConnect(m_DbInfoInfx);
  m_InfxConn.setIsolationLevel(basar::INFX_DIRTYREAD);
  m_InfxConn.setLockModeWait  (basar::WAITSECS, 30);

  if (LoggerPool::zpldcust.isEnabledFor(log4cplus::INFO_LOG_LEVEL) && m_InfxConn.isOpen())
  {
    msg.format("zpldcust connected successfully <%s, %s>.",
      m_DbInfoInfx.dbServer.c_str(),
      m_DbInfoInfx.database.c_str());
    LoggerPool::zpldcust.forcedLog(log4cplus::INFO_LOG_LEVEL, msg, __FILE__, __LINE__);
  }

  setCicsDbInfo();
  m_CicsConn = basar::db::aspect::Manager::getInstance().createConnect(m_DbInfoCics);

  if (LoggerPool::zpldcust.isEnabledFor(log4cplus::INFO_LOG_LEVEL) && m_CicsConn.isOpen() )
  {
    msg.format("zpldcust connected successfully <%s (%s:%s)>.",
      m_DbInfoCics.dbServer.c_str(),
      m_DbInfoCics.cicsCustom.ipAddr.c_str(),
      m_DbInfoCics.cicsCustom.port.c_str());
    LoggerPool::zpldcust.forcedLog(log4cplus::INFO_LOG_LEVEL, msg, __FILE__, __LINE__);
  }
}

//----------------------------------------------------------------------------

void Connection::setInfxDbInfo()
{
  // get user´s branch he logged in for to get area-specific database
  I18nString branch;
  I18nString user;
  // variables where parameters for host and database are put in
  I18nString hostVal;			
  I18nString databaseVal;		

  branch.format("%d", basar::login::Manager::getInstance().getAreaID());
  user = basar::login::Manager::getInstance().getUserName();

  // ask login for parameters -> libbasarlogin has to be called before opening connection for gibooking
  if (basar::login::Manager::getInstance().getParaValue(branch, user, UADM_HOST, hostVal) == false)
  {
    // no user-specific host parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue(branch, UADM_HOST, hostVal);
  }

  if (basar::login::Manager::getInstance().getParaValue(branch, user, UADM_DB, databaseVal) == false)
  {
    // no user-specific database parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue(branch, UADM_DB, databaseVal);
  }

  m_DbInfoInfx.setInfx(hostVal, databaseVal);
}

//----------------------------------------------------------------------------

void Connection::setCicsDbInfo()
{
	// get user´s branch he logged in for to get area-specific database
  I18nString branch;
  I18nString user;
  // variables where parameter for host is put in
  I18nString cicsHostVal;			
  I18nString cicsIpVal;
  I18nString cicsPortVal;
  I18nString cicsStartTransVal;

  branch.format("%d", basar::login::Manager::getInstance().getAreaID());
  user = basar::login::Manager::getInstance().getUserName();
	
  // ask login for parameters -> libbasarlogin has to be called before opening connection for goodsin
	if (basar::login::Manager::getInstance().getParaValue(branch, user, UADM_HOST_CICS, cicsHostVal) == false)
  {
    // no user-specific host parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue(branch, UADM_HOST_CICS, cicsHostVal);
  }

  if (basar::login::Manager::getInstance().getParaValue(branch, user, UADM_IP_CICS, cicsIpVal) == false)
  {
    // no user-specific host parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue(branch, UADM_IP_CICS, cicsIpVal);
  }

  if (basar::login::Manager::getInstance().getParaValue(branch, user, UADM_PORT_CICS, cicsPortVal) == false)
  {
    // no user-specific host parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue(branch, UADM_PORT_CICS, cicsPortVal);
  }

  if ( basar::login::Manager::getInstance().getParaValue(branch, user, UADM_START_TRANSACTION_CICS, cicsStartTransVal) == false)
  {
    // no user-specific host parameter found (for individual testing!), then take general
    basar::login::Manager::getInstance().getParaValue( branch, UADM_START_TRANSACTION_CICS, cicsStartTransVal);
  }

  m_DbInfoCics.setCICS(cicsHostVal, cicsIpVal, cicsPortVal, cicsStartTransVal, "ZDPBATCH", "ZDPBATCH");
}

//----------------------------------------------------------------------------

void Connection::disconnect()
{
  VarString msg;

  if (!m_CicsConn.isNull())
  {
    m_CicsConn.close();
    if (LoggerPool::zpldcust.isEnabledFor(log4cplus::INFO_LOG_LEVEL))
    {
      msg.format("zpldcust disconnected successfully <%s (%s:%s)>.",
        m_DbInfoCics.dbServer.c_str(),
        m_DbInfoCics.cicsCustom.ipAddr.c_str(),
        m_DbInfoCics.cicsCustom.port.c_str()
        );
      LoggerPool::zpldcust.forcedLog(log4cplus::INFO_LOG_LEVEL, msg, __FILE__, __LINE__);
    }
  }

  if (!m_InfxConn.isNull())
  {
    m_InfxConn.close();
    if (LoggerPool::zpldcust.isEnabledFor(log4cplus::INFO_LOG_LEVEL))
    {
      msg.format("zpldcust disconnected successfully <%s (%s:%s)>.",
        m_DbInfoCics.dbServer.c_str(),
        m_DbInfoCics.cicsCustom.ipAddr.c_str(),
        m_DbInfoCics.cicsCustom.port.c_str()
        );
      LoggerPool::zpldcust.forcedLog(log4cplus::INFO_LOG_LEVEL, msg, __FILE__, __LINE__);
    }
  }
}

//----------------------------------------------------------------------------

const ConnectionRef Connection::getInfxConnection() const
{
  return m_InfxConn;
}

//----------------------------------------------------------------------------

const ConnectionRef Connection::getCicsConnection() const
{
  return m_CicsConn;
}

//----------------------------------------------------------------------------

} // namespace zpldcust

//----------------------------------------------------------------------------
