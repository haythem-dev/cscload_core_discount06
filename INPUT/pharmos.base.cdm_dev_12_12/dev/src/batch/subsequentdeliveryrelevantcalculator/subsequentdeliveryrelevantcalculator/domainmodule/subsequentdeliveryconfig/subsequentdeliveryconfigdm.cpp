//-------------------------------------------------------------------------------------------------//
/*! \file	SubsequentDeliveryConfigDM.cpp
*   \brief	domain module für article data (zartikel / artikelf)
*   \author NTT Data
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#include "subsequentdeliveryconfigdm.h"
#include "infrastructure/accessor/subsequentdeliveryconfig/subsequentdeliveryconfigacc.h"
#include "libutil/exception.h"
#include "libutil/exception.h"

/* the implementation as prepared statement is necesseary for performance reasons,
   but we might move them later to the accessor. It should be possible to use
   prepared statement via accessor also. Currently insert and upate are implemented
   twice but ony the implementation within the DM is beeing used */
#define USE_PREPARED_STATEMENTS
//#define CALCULATOR_BATCH_NAME "CALCULATOR_BATCH"

namespace subsequentdeliveryrelevantcalculator
{
	namespace domMod
	{
		namespace subsequentdeliveryconfig
		{
			basar::VarString SubsequentDeliveryConfigDM::CALCULATOR_BATCH_NAME = "CALCULATOR_BATCH";

			SubsequentDeliveryConfigDM::SubsequentDeliveryConfigDM(const log4cplus::Logger& logger)
				: m_Logger(logger)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, SubsequentDeliveryConfigDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			SubsequentDeliveryConfigDM::~SubsequentDeliveryConfigDM()
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, ~SubsequentDeliveryConfigDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void SubsequentDeliveryConfigDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
				m_DbSqlConnection = conn->getCurrentConnection().getSqlConnection();
			}

			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::initSubsequentDeliveryConfig(basar::Int16 branchno)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, initSubsequentDeliveryConfig)
					BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator updateValues = getSubsequentDeliveryConfigData().insert(basar::FOR_UPDATE);

					updateValues.setInt16(CFG_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::InitSubsequentDeliveryConfig, updateValues);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::InsertSubsequentDeliveryConfig, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::InsertSubsequentDeliveryConfig, executeResultInfo)
				}

				return executeResultInfo;
			}

#ifndef USE_PREPARED_STATEMENTS
			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::insertSubsequentDeliveryConfig(basar::Int16 branchno, 
				                                                                                            basar::Int32 articleno, 
				                                                                                            basar::Int16 subsequentdelivery,
                                                                                                            basar::VarString lastchangeuser)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, insertSubsequentDeliveryConfig)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator insertValues = getSubsequentDeliveryConfigData().insert(basar::FOR_INSERT);

					insertValues.setInt16(CFG_BRANCHNO.getName(), branchno);
					insertValues.setInt32(CFG_ARTICLENO.getName(), articleno);
					insertValues.setInt16(CFG_SUBSEQUENTDELIVERY.getName(), subsequentdelivery);
					insertValues.setString(CFG_LASTCHANGEUSER.getName(), lastchangeuser.c_str());

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::InsertSubsequentDeliveryConfig, insertValues);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::InsertSubsequentDeliveryConfig, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::InsertSubsequentDeliveryConfig, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::updateSubsequentDeliveryConfig(basar::Int16 branchno,
   				                                                                                            basar::Int32 articleno,
				                                                                                            basar::Int16 subsequentdelivery,
				                                                                                            basar::VarString lastchangeuser)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, updateSubsequentDeliveryConfig)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator updateValues = getSubsequentDeliveryConfigData().insert(basar::FOR_UPDATE);

					updateValues.setInt16(CFG_BRANCHNO.getName(), branchno);
					updateValues.setInt32(CFG_ARTICLENO.getName(), articleno);
					updateValues.setInt16(CFG_SUBSEQUENTDELIVERY.getName(), subsequentdelivery);
					insertValues.setString(CFG_LASTCHANGEUSER.getName(), lastchangeuser.c_str());

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::UpdateSubsequentDeliveryConfig, updateValues);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::UpdateSubsequentDeliveryConfig, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::UpdateSubsequentDeliveryConfig, executeResultInfo)
				}

				return executeResultInfo;
			}
#else
			basar::db::sql::ExecuteReturnInfo SubsequentDeliveryConfigDM::insertSubsequentDeliveryConfig(basar::Int16 branchno,
				                                                                                         basar::Int32 articleno,
					                                                                                     basar::Int16 subsequentdelivery,
					                                                                                     basar::VarString lastchangeuser)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, insertSubsequentDeliveryConfig)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtInsert.isNull() || !m_PrepStmtInsert.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("INSERT INTO csubsequentdeliverybrancharticleconfig (");
					stmtSQL.append(" branchno ");
					stmtSQL.append(",articleno ");
					stmtSQL.append(",subsequentdelivery ");
					stmtSQL.append(",lastchangedate ");
					stmtSQL.append(",lastchangeuser ");
					stmtSQL.append(") VALUES ( ");
					stmtSQL.append("  ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(",CURRENT ");
					stmtSQL.append(", ?");
					stmtSQL.append(")");

					m_PrepStmtInsert = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared INSERT stmt <" << stmtSQL.c_str() << "> created";
					BLOG_DEBUG(m_Logger, ss.str());
				}

				m_PrepStmtInsert.setInt16(0, branchno);
				m_PrepStmtInsert.setInt32(1, articleno);
				m_PrepStmtInsert.setInt16(2, subsequentdelivery);
				m_PrepStmtInsert.setString(3, lastchangeuser.c_str());

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtInsert.execute();

				return returnInfo;
			}

			basar::db::sql::ExecuteReturnInfo SubsequentDeliveryConfigDM::updateSubsequentDeliveryConfig(basar::Int16 branchno, 
				                                                                                         basar::Int32 articleno, 
				                                                                                         basar::Int16 subsequentdelivery, 
				                                                                                         basar::VarString lastchangeuser)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, updateSubsequentDeliveryConfig)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtUpdate.isNull() || !m_PrepStmtUpdate.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("UPDATE csubsequentdeliverybrancharticleconfig SET ");
					stmtSQL.append(" subsequentdelivery = ? ");
					stmtSQL.append(",lastchangedate = CURRENT ");
					stmtSQL.append(",lastchangeuser = ?");
					stmtSQL.append("WHERE branchno = ?");
					stmtSQL.append("  AND articleno = ?");

					m_PrepStmtUpdate = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared UPDATE stmt <" << stmtSQL.c_str() << "> created";
					BLOG_DEBUG(m_Logger, ss.str());
				}

				m_PrepStmtUpdate.setInt16(0, subsequentdelivery);
				m_PrepStmtUpdate.setString(1, lastchangeuser.c_str());
				m_PrepStmtUpdate.setInt16(2, branchno);
				m_PrepStmtUpdate.setInt32(3, articleno);

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtUpdate.execute();

				return returnInfo;
			}
#endif


			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::resetSubsequentDeliveryConfig(basar::Int16 branchno)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, resetSubsequentDeliveryConfig)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getSubsequentDeliveryConfigData().insert(basar::FOR_UNKNOWN);

					whereCondition.setInt16(CFG_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::ResetSubsequentDeliveryConfig, whereCondition);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::ResetSubsequentDeliveryConfig, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::ResetSubsequentDeliveryConfig, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::deleteSubsequentDeliveryConfigForNotExistingArticles(basar::Int16 branchno)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, deleteSubsequentDeliveryConfigForNotExistingArticles)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getSubsequentDeliveryConfigData().insert(basar::FOR_UNKNOWN);

					whereCondition.setInt16(CFG_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForNotExistingArticles, whereCondition);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForNotExistingArticles, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForNotExistingArticles, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo SubsequentDeliveryConfigDM::deleteSubsequentDeliveryConfigForBlockedArticles(basar::Int16 branchno)
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, deleteSubsequentDeliveryConfigForBlockedArticles)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getSubsequentDeliveryConfigData().insert(basar::FOR_UNKNOWN);

					whereCondition.setInt16(CFG_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForBlockedArticles, whereCondition);
				}
				catch (basar::Exception& e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForBlockedArticles, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::subsequentdeliveryconfig::lit::DeleteSubsequentDeliveryConfigForBlockedArticles, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::AccessorPropertyTableRef SubsequentDeliveryConfigDM::getSubsequentDeliveryConfigData()
			{
				METHODNAME_DEF(SubsequentDeliveryConfigDM, getSubsequentDeliveryConfigData)
			    BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			void SubsequentDeliveryConfigDM::beginTransaction()
			{
				getDbConnection().beginTransaction();
			}

			void SubsequentDeliveryConfigDM::commitTransaction()
			{
				getDbConnection().commitTransaction();
			}

			void SubsequentDeliveryConfigDM::rollbackTransaction()
			{
				getDbConnection().rollbackTransaction();
			}
		}
	}
}
