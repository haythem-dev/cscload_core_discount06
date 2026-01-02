//-------------------------------------------------------------------------------------------------//
/*! \file	pricelistprocdm.cpp
*   \brief	domain module for price list processing status
*   \author NTT DATA
*   \date	14.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#include "pricelistprocdm.h"
#include "domainmodule/pricedata/pricedatadm.h"
#include "infrastructure/accessor/pricelistproc/pricelistprocacc.h"
#include "libutil/exception.h"

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelistproc
		{
			PriceListProcDM::PriceListProcDM(const log4cplus::Logger& logger)
				:m_Logger(logger)
			{
				METHODNAME_DEF(PriceListProcDM, PriceListProcDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			PriceListProcDM::~PriceListProcDM()
			{
				METHODNAME_DEF(PriceListProcDM, ~PriceListProcDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void PriceListProcDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
				m_DbSqlConnection = conn->getCurrentConnection().getSqlConnection();
			}

			bool PriceListProcDM::selectPriceListProcByFileName(const basar::VarString fileName, PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, selectPriceListProcByFileName)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceListProc().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICELISTPROC_FILENAME.getName(), fileName);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByFileName, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByFileName, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByFileName, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceListProc();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						priceListProc.fileName = dataIterator.getString(PRICELISTPROC_FILENAME.getName());
						priceListProc.priceListType = dataIterator.getString(PRICELISTPROC_PRICELISTTYPE.getName());
						priceListProc.priceListId = dataIterator.getDecimal(PRICELISTPROC_PRICELISTID.getName()).toInt32();
						priceListProc.pharmacyGroupId = dataIterator.getString(PRICELISTPROC_PHARMACYGROUPID.getName()).stoi();
						priceListProc.calcDate = dataIterator.getInt32(PRICELISTPROC_CALCDATE.getName());
						priceListProc.seqNo = dataIterator.getInt16(PRICELISTPROC_SEQNO.getName());
						priceListProc.procDate = dataIterator.getInt32(PRICELISTPROC_PROCDATE.getName());
						priceListProc.dateFrom = dataIterator.getInt32(PRICELISTPROC_DATEFROM.getName());
						priceListProc.numArticles = dataIterator.getInt32(PRICELISTPROC_NUMARTICLES.getName());
						priceListProc.numPrices = dataIterator.getInt32(PRICELISTPROC_NUMPRICES.getName());
						priceListProc.numProcArticles = dataIterator.getInt32(PRICELISTPROC_NUMPROCARTICLES.getName());
						priceListProc.numProcPrices = dataIterator.getInt32(PRICELISTPROC_NUMPROCPRICES.getName());
						priceListProc.numDelArticles = dataIterator.getInt32(PRICELISTPROC_NUMDELARTICLES.getName());
						priceListProc.numArticlesError = dataIterator.getInt32(PRICELISTPROC_NUMARTICLESERROR.getName());
						priceListProc.procState = dataIterator.getString(PRICELISTPROC_PROCSTATE.getName());
						priceListProc.procInfoMsg = dataIterator.getString(PRICELISTPROC_PROCINFOMSG.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			bool PriceListProcDM::selectPriceListProcByKey(PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, selectPriceListProcByKey)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceListProc().insert(basar::FOR_UNKNOWN);
					basar::Decimal decPriceListId(priceListProc.priceListId);

					whereCondition.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					whereCondition.setInt32(PRICELISTPROC_CALCDATE.getName(), priceListProc.calcDate);
					whereCondition.setInt16(PRICELISTPROC_SEQNO.getName(), priceListProc.seqNo);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByKey, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByKey, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::SelectPriceListProcByKey, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceListProc();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						priceListProc.fileName = dataIterator.getString(PRICELISTPROC_FILENAME.getName());
						priceListProc.priceListType = dataIterator.getString(PRICELISTPROC_PRICELISTTYPE.getName());
						priceListProc.priceListId = dataIterator.getDecimal(PRICELISTPROC_PRICELISTID.getName()).toInt32();
						priceListProc.pharmacyGroupId = dataIterator.getString(PRICELISTPROC_PHARMACYGROUPID.getName()).stoi();
						priceListProc.calcDate = dataIterator.getInt32(PRICELISTPROC_CALCDATE.getName());
						priceListProc.seqNo = dataIterator.getInt16(PRICELISTPROC_SEQNO.getName());
						priceListProc.procDate = dataIterator.getInt32(PRICELISTPROC_PROCDATE.getName());
						priceListProc.dateFrom = dataIterator.getInt32(PRICELISTPROC_DATEFROM.getName());
						priceListProc.numArticles = dataIterator.getInt32(PRICELISTPROC_NUMARTICLES.getName());
						priceListProc.numPrices = dataIterator.getInt32(PRICELISTPROC_NUMPRICES.getName());
						priceListProc.numProcArticles = dataIterator.getInt32(PRICELISTPROC_NUMPROCARTICLES.getName());
						priceListProc.numProcPrices = dataIterator.getInt32(PRICELISTPROC_NUMPROCPRICES.getName());
						priceListProc.numDelArticles = dataIterator.getInt32(PRICELISTPROC_NUMDELARTICLES.getName());
						priceListProc.numArticlesError = dataIterator.getInt32(PRICELISTPROC_NUMARTICLESERROR.getName());
						priceListProc.procState = dataIterator.getString(PRICELISTPROC_PROCSTATE.getName());
						priceListProc.procInfoMsg = dataIterator.getString(PRICELISTPROC_PROCINFOMSG.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			bool PriceListProcDM::selectMaxDates(basar::Int32 priceListId, basar::Int32& maxCalcDate, basar::Int32& maxDateFrom)
			{
				METHODNAME_DEF(PriceListProcDM, selectMaxDates)
				BLOG_TRACE_METHOD(m_Logger, fun);

				maxCalcDate = 0;
				maxDateFrom = 0;

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceListProc().insert(basar::FOR_UNKNOWN);
					basar::Decimal decPriceListId(priceListId);

					whereCondition.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::SelectMaxDates, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::SelectMaxDates, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::SelectMaxDates, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceListProc();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						maxCalcDate = dataIterator.getInt32(PRICELISTPROC_CALCDATE.getName());
						maxDateFrom = dataIterator.getInt32(PRICELISTPROC_DATEFROM.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			bool PriceListProcDM::selectMaxSeqNo(basar::Int32 priceListId, basar::Int32 calcDate, basar::Int16& maxSeqNo)
			{
				METHODNAME_DEF(PriceListProcDM, selectMaxSeqNo)
				BLOG_TRACE_METHOD(m_Logger, fun);

				maxSeqNo = 0;

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceListProc().insert(basar::FOR_UNKNOWN);
					basar::Decimal decPriceListId(priceListId);

					whereCondition.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					whereCondition.setInt32(PRICELISTPROC_CALCDATE.getName(), calcDate);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::SelectMaxSeqNo, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::SelectMaxSeqNo, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::SelectMaxSeqNo, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceListProc();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						maxSeqNo = dataIterator.getInt16(PRICELISTPROC_SEQNO.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::insertPriceListProc(const PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, insertPriceListProc)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator insertValues = getPriceListProc().insert(basar::FOR_INSERT);
					basar::Decimal decPriceListId(priceListProc.priceListId);

					insertValues.setString(PRICELISTPROC_FILENAME.getName(), priceListProc.fileName);
					insertValues.setString(PRICELISTPROC_PRICELISTTYPE.getName(), priceListProc.priceListType);
					insertValues.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					insertValues.setString(PRICELISTPROC_PHARMACYGROUPID.getName(), domMod::pricedata::PriceData::convertInt32ToVarString(priceListProc.pharmacyGroupId, 3));
					insertValues.setInt32(PRICELISTPROC_CALCDATE.getName(), priceListProc.calcDate);
					insertValues.setInt16(PRICELISTPROC_SEQNO.getName(), priceListProc.seqNo);
					insertValues.setInt32(PRICELISTPROC_PROCDATE.getName(), priceListProc.procDate);
					insertValues.setInt32(PRICELISTPROC_DATEFROM.getName(), priceListProc.dateFrom);
					insertValues.setInt32(PRICELISTPROC_NUMARTICLES.getName(), priceListProc.numArticles);
					insertValues.setInt32(PRICELISTPROC_NUMPRICES.getName(), priceListProc.numPrices);
					insertValues.setInt32(PRICELISTPROC_NUMPROCARTICLES.getName(), priceListProc.numProcArticles);
					insertValues.setInt32(PRICELISTPROC_NUMPROCPRICES.getName(), priceListProc.numProcPrices);
					insertValues.setInt32(PRICELISTPROC_NUMDELARTICLES.getName(), priceListProc.numDelArticles);
					insertValues.setInt32(PRICELISTPROC_NUMARTICLESERROR.getName(), priceListProc.numArticlesError);
					insertValues.setString(PRICELISTPROC_PROCSTATE.getName(), priceListProc.procState);
					insertValues.setString(PRICELISTPROC_PROCINFOMSG.getName(), cleanupProcInfoMsg(priceListProc.procInfoMsg));

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::InsertPriceListProc, insertValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::InsertPriceListProc, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::InsertPriceListProc, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::updatePriceListProc(const PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, updatePriceListProc)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator updateValues = getPriceListProc().insert(basar::FOR_UPDATE);

					updateValues.setString(PRICELISTPROC_FILENAME.getName(), priceListProc.fileName);
					updateValues.setInt32(PRICELISTPROC_NUMARTICLES.getName(), priceListProc.numArticles);
					updateValues.setInt32(PRICELISTPROC_NUMPRICES.getName(), priceListProc.numPrices);
					updateValues.setInt32(PRICELISTPROC_NUMPROCARTICLES.getName(), priceListProc.numProcArticles);
					updateValues.setInt32(PRICELISTPROC_NUMPROCPRICES.getName(), priceListProc.numProcPrices);
					updateValues.setInt32(PRICELISTPROC_NUMDELARTICLES.getName(), priceListProc.numDelArticles);
					updateValues.setInt32(PRICELISTPROC_NUMARTICLESERROR.getName(), priceListProc.numArticlesError);
					updateValues.setString(PRICELISTPROC_PROCSTATE.getName(), priceListProc.procState);
					updateValues.setString(PRICELISTPROC_PROCINFOMSG.getName(), cleanupProcInfoMsg(priceListProc.procInfoMsg));

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::UpdatePriceListProc, updateValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::UpdatePriceListProc, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::UpdatePriceListProc, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::sql::ExecuteReturnInfo PriceListProcDM::updatePriceListProcPrep(const PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, updatePriceListProcPrep)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtUpdate.isNull() || !m_PrepStmtUpdate.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("UPDATE cpricelistproc SET ");
					stmtSQL.append("  numarticles = ?");
					stmtSQL.append(" ,numprices = ?");
					stmtSQL.append(" ,numprocarticles = ?");
					stmtSQL.append(" ,numprocprices = ?");
					stmtSQL.append(" ,numdelarticles = ?");
					stmtSQL.append(" ,numarticleserror = ?");
					stmtSQL.append(" ,procstate = ?");
					stmtSQL.append(" ,procinformsg = ?");
					stmtSQL.append(" WHERE pricelistid = ? ");
					stmtSQL.append(" AND calcdate = ? ");
					stmtSQL.append(" AND seqno = ?");

					m_PrepStmtUpdate = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared UPDATE stmt <" << stmtSQL.c_str() << "> created";
					BLOG_INFO(m_Logger, ss.str());
				}

				basar::Decimal decPriceListId(priceListProc.priceListId);

				m_PrepStmtUpdate.setInt32(0, priceListProc.numArticles);
				m_PrepStmtUpdate.setInt32(1, priceListProc.numPrices);
				m_PrepStmtUpdate.setInt32(2, priceListProc.numProcArticles);
				m_PrepStmtUpdate.setInt32(3, priceListProc.numProcPrices);
				m_PrepStmtUpdate.setInt32(4, priceListProc.numDelArticles);
				m_PrepStmtUpdate.setInt32(5, priceListProc.numArticlesError);
				m_PrepStmtUpdate.setString(6, priceListProc.procState.c_str());
				m_PrepStmtUpdate.setString(7, cleanupProcInfoMsg(priceListProc.procInfoMsg).c_str());
				m_PrepStmtUpdate.setDecimal(8, decPriceListId);
				m_PrepStmtUpdate.setInt32(9, priceListProc.calcDate);
				m_PrepStmtUpdate.setInt16(10, priceListProc.seqNo);

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtUpdate.execute();

				return returnInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::updateStatusAndInfoMsg(const PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, updateStatusAndInfoMsg)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator updateValues = getPriceListProc().insert(basar::FOR_UPDATE);
					basar::Decimal decPriceListId(priceListProc.priceListId);

					updateValues.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					updateValues.setInt32(PRICELISTPROC_CALCDATE.getName(), priceListProc.calcDate);
					updateValues.setInt16(PRICELISTPROC_SEQNO.getName(), priceListProc.seqNo);
					updateValues.setString(PRICELISTPROC_PROCSTATE.getName(), priceListProc.procState);
					updateValues.setString(PRICELISTPROC_PROCINFOMSG.getName(), cleanupProcInfoMsg(priceListProc.procInfoMsg));

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::UpdateStatusAndInfoMsg, updateValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::UpdateStatusAndInfoMsg, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::UpdateStatusAndInfoMsg, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::updateStatusToFailed(basar::Int32 priceListId, basar::Int32 calcDate, basar::Int16 seqNo)
			{
				METHODNAME_DEF(PriceListProcDM, updateStatusToFailed)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator updateValues = getPriceListProc().insert(basar::FOR_UPDATE);
					basar::Decimal decPriceListId(priceListId);

					updateValues.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					updateValues.setInt32(PRICELISTPROC_CALCDATE.getName(), calcDate);
					updateValues.setInt16(PRICELISTPROC_SEQNO.getName(), seqNo);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::UpdateStatusToFailed, updateValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::UpdateStatusToFailed, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::UpdateStatusToFailed, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::deletePriceListProcByFileName(const basar::VarString& fileName)
			{
				METHODNAME_DEF(PriceListProcDM, delectPriceListProcByFileName)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator deleteValues = getPriceListProc().insert(basar::FOR_DELETE);

					deleteValues.setString(PRICELISTPROC_FILENAME.getName(), fileName);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByFileName, deleteValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByFileName, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByFileName, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceListProcDM::deletePriceListProcByKey(const PriceListProc& priceListProc)
			{
				METHODNAME_DEF(PriceListProcDM, delectPriceListProcByFileName)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator deleteValues = getPriceListProc().insert(basar::FOR_DELETE);
					basar::Decimal decPriceListId(priceListProc.priceListId);

					deleteValues.setDecimal(PRICELISTPROC_PRICELISTID.getName(), decPriceListId);
					deleteValues.setInt32(PRICELISTPROC_CALCDATE.getName(), priceListProc.calcDate);
					deleteValues.setInt16(PRICELISTPROC_SEQNO.getName(), priceListProc.seqNo);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByKey, deleteValues);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByKey, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelistproc::lit::DeletePriceListProcByKey, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::AccessorPropertyTableRef PriceListProcDM::getPriceListProc()
			{
				METHODNAME_DEF(PriceDataDM, getPriceListProc)
				BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			// the info msg may contain carriage return and line feed characters, which mess up
			// the sql processing; we replace these characters with other values
			basar::VarString PriceListProcDM::cleanupProcInfoMsg(const basar::VarString& procInfoMsg)
			{
				basar::VarString result(procInfoMsg);

				result.exchange("\n", "\\n");
				result.exchange("\r", "");

				return result;
			}


			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// PriceListProc containing price list processing status info
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			PriceListProc::PriceListProc()
				: fileName("")
				, priceListType("")
				, priceListId(0)
				, pharmacyGroupId(0)
				, calcDate(0)
				, seqNo(0)
				, procDate(0)
				, dateFrom(0)
				, numArticles(-1)
				, numPrices(-1)
				, numProcArticles(0)
				, numProcPrices(0)
				, numDelArticles(0)
				, numArticlesError(0)
				, procState("")
				, procInfoMsg("")
			{

			}

			PriceListProc::PriceListProc(const PriceListProc& other)
			{
				*this = other;
			}

			PriceListProc& PriceListProc::operator=(const PriceListProc& other)
			{
				fileName = other.fileName;
				priceListType = other.priceListType;
				priceListId = other.priceListId;
				pharmacyGroupId = other.pharmacyGroupId;
				calcDate = other.calcDate;
				seqNo = other.seqNo;
				procDate = other.procDate;
				dateFrom = other.dateFrom;
				numArticles = other.numArticles;
				numPrices = other.numPrices;
				numProcArticles = other.numProcArticles;
				numProcPrices = other.numProcPrices;
				numDelArticles = other.numDelArticles;
				numArticlesError = other.numArticlesError;
				procState = other.procState;
				procInfoMsg = other.procInfoMsg;
				return *this;
			}
		}
	}
}
