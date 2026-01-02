//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/pricelistproc/pricelistprocacc.h"
#include "domainmodule/pricelistproc/pricelistprocdm.h"
#include "loggerpool/importpricelist_loggerpool.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace pricelistproc
			{
				using namespace importpricelist::domMod::pricelistproc;

				BEGIN_ACCESSOR_DEFINITION(lit::PriceListProcAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_FILENAME)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PRICELISTTYPE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PRICELISTID)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PHARMACYGROUPID)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_CALCDATE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_SEQNO)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PROCDATE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_DATEFROM)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMARTICLES)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMPRICES)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMPROCARTICLES)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMPROCPRICES)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMDELARTICLES)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_NUMARTICLESERROR)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PROCSTATE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICELISTPROC_PROCINFOMSG)
				END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::SelectPriceListProcByFileName)
				{
					SQL_BUILDER_CREATE(SelectPriceListProcByFileName)
					SQL_BUILDER_PUSH_BACK(SelectPriceListProcByFileName)
				}

				ACCESS_METHOD(lit::SelectPriceListProcByKey)
				{
					SQL_BUILDER_CREATE(SelectPriceListProcByKey)
					SQL_BUILDER_PUSH_BACK(SelectPriceListProcByKey)
				}

				ACCESS_METHOD(lit::SelectMaxDates)
				{
					SQL_BUILDER_CREATE(SelectMaxDates)
					SQL_BUILDER_PUSH_BACK(SelectMaxDates)
				}

				ACCESS_METHOD(lit::SelectMaxSeqNo)
				{
					SQL_BUILDER_CREATE(SelectMaxSeqNo)
					SQL_BUILDER_PUSH_BACK(SelectMaxSeqNo)
				}

				ACCESS_METHOD(lit::InsertPriceListProc)
				{
					SQL_BUILDER_CREATE(InsertPriceListProc)
					SQL_BUILDER_PUSH_BACK(InsertPriceListProc)
				}

				ACCESS_METHOD(lit::UpdatePriceListProc)
				{
					SQL_BUILDER_CREATE(UpdatePriceListProc)
					SQL_BUILDER_PUSH_BACK(UpdatePriceListProc)
				}

				ACCESS_METHOD(lit::UpdateStatusAndInfoMsg)
				{
					SQL_BUILDER_CREATE(UpdateStatusAndInfoMsg)
					SQL_BUILDER_PUSH_BACK(UpdateStatusAndInfoMsg)
				}

				ACCESS_METHOD(lit::UpdateStatusToFailed)
				{
					SQL_BUILDER_CREATE(UpdateStatusToFailed)
					SQL_BUILDER_PUSH_BACK(UpdateStatusToFailed)
				}

				ACCESS_METHOD(lit::DeletePriceListProcByFileName)
				{
					SQL_BUILDER_CREATE(DeletePriceListProcByFileName)
					SQL_BUILDER_PUSH_BACK(DeletePriceListProcByFileName)
				}

				ACCESS_METHOD(lit::DeletePriceListProcByKey)
				{
					SQL_BUILDER_CREATE(DeletePriceListProcByKey)
					SQL_BUILDER_PUSH_BACK(DeletePriceListProcByKey)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// selectPriceListProcByFileName
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPriceListProcByFileName)
				bool SelectPriceListProcByFileName::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_FILENAME.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPriceListProcByFileName::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT filename AS ").append(PRICELISTPROC_FILENAME.getName());
					stmtSQL.append("      ,pricelisttype AS ").append(PRICELISTPROC_PRICELISTTYPE.getName());
					stmtSQL.append("      ,pricelistid AS ").append(PRICELISTPROC_PRICELISTID.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRICELISTPROC_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,calcdate AS ").append(PRICELISTPROC_CALCDATE.getName());
					stmtSQL.append("      ,seqno AS ").append(PRICELISTPROC_SEQNO.getName());
					stmtSQL.append("      ,procdate AS ").append(PRICELISTPROC_PROCDATE.getName());
					stmtSQL.append("      ,datefrom AS ").append(PRICELISTPROC_DATEFROM.getName());
					stmtSQL.append("      ,numarticles AS ").append(PRICELISTPROC_NUMARTICLES.getName());
					stmtSQL.append("      ,numprices AS ").append(PRICELISTPROC_NUMPRICES.getName());
					stmtSQL.append("      ,numprocarticles AS ").append(PRICELISTPROC_NUMPROCARTICLES.getName());
					stmtSQL.append("      ,numprocprices AS ").append(PRICELISTPROC_NUMPROCPRICES.getName());
					stmtSQL.append("      ,numdelarticles AS ").append(PRICELISTPROC_NUMDELARTICLES.getName());
					stmtSQL.append("      ,numarticleserror AS ").append(PRICELISTPROC_NUMARTICLESERROR.getName());
					stmtSQL.append("      ,procstate AS ").append(PRICELISTPROC_PROCSTATE.getName());
					stmtSQL.append("      ,procinformsg AS ").append(PRICELISTPROC_PROCINFOMSG.getName());
					stmtSQL.append("  FROM cpricelistproc");
					stmtSQL.append(" WHERE filename = '").append(PRICELISTPROC_FILENAME.toSQLReplacementString()).append("'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectPriceListProcByKey
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPriceListProcByKey)
					bool SelectPriceListProcByKey::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());
					paramList.push_back(PRICELISTPROC_CALCDATE.getName());
					paramList.push_back(PRICELISTPROC_SEQNO.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPriceListProcByKey::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("SELECT filename AS ").append(PRICELISTPROC_FILENAME.getName());
					stmtSQL.append("      ,pricelisttype AS ").append(PRICELISTPROC_PRICELISTTYPE.getName());
					stmtSQL.append("      ,pricelistid AS ").append(PRICELISTPROC_PRICELISTID.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRICELISTPROC_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,calcdate AS ").append(PRICELISTPROC_CALCDATE.getName());
					stmtSQL.append("      ,seqno AS ").append(PRICELISTPROC_SEQNO.getName());
					stmtSQL.append("      ,procdate AS ").append(PRICELISTPROC_PROCDATE.getName());
					stmtSQL.append("      ,datefrom AS ").append(PRICELISTPROC_DATEFROM.getName());
					stmtSQL.append("      ,numarticles AS ").append(PRICELISTPROC_NUMARTICLES.getName());
					stmtSQL.append("      ,numprices AS ").append(PRICELISTPROC_NUMPRICES.getName());
					stmtSQL.append("      ,numprocarticles AS ").append(PRICELISTPROC_NUMPROCARTICLES.getName());
					stmtSQL.append("      ,numprocprices AS ").append(PRICELISTPROC_NUMPROCPRICES.getName());
					stmtSQL.append("      ,numdelarticles AS ").append(PRICELISTPROC_NUMDELARTICLES.getName());
					stmtSQL.append("      ,numarticleserror AS ").append(PRICELISTPROC_NUMARTICLESERROR.getName());
					stmtSQL.append("      ,procstate AS ").append(PRICELISTPROC_PROCSTATE.getName());
					stmtSQL.append("      ,procinformsg AS ").append(PRICELISTPROC_PROCINFOMSG.getName());
					stmtSQL.append("  FROM cpricelistproc");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND calcdate = ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("   AND seqno = ").append(PRICELISTPROC_SEQNO.toSQLReplacementString());

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectMaxDates
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectMaxDates)
					bool SelectMaxDates::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());

					return arePropertiesSet(paramList);
				}

				void SelectMaxDates::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("SELECT max(calcdate) AS ").append(PRICELISTPROC_CALCDATE.getName());
					stmtSQL.append("      ,max(datefrom) AS ").append(PRICELISTPROC_DATEFROM.getName());
					stmtSQL.append("  FROM cpricelistproc");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND procstate <> 'rejected'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectMaxSeqNo
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectMaxSeqNo)
					bool SelectMaxSeqNo::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());

					return arePropertiesSet(paramList);
				}

				void SelectMaxSeqNo::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("SELECT max(seqno) AS ").append(PRICELISTPROC_SEQNO.getName());
					stmtSQL.append("  FROM cpricelistproc");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND calcdate = ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("   AND procstate <> 'rejected'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// insertPriceListProc
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(InsertPriceListProc)
					bool InsertPriceListProc::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_FILENAME.getName());
					paramList.push_back(PRICELISTPROC_PRICELISTTYPE.getName());
					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());
					paramList.push_back(PRICELISTPROC_PHARMACYGROUPID.getName());
					paramList.push_back(PRICELISTPROC_CALCDATE.getName());
					paramList.push_back(PRICELISTPROC_SEQNO.getName());
					paramList.push_back(PRICELISTPROC_PROCDATE.getName());
					paramList.push_back(PRICELISTPROC_DATEFROM.getName());
					paramList.push_back(PRICELISTPROC_NUMARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMPRICES.getName());
					paramList.push_back(PRICELISTPROC_NUMPROCARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMPROCPRICES.getName());
					paramList.push_back(PRICELISTPROC_NUMDELARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMARTICLESERROR.getName());
					paramList.push_back(PRICELISTPROC_PROCSTATE.getName());
					paramList.push_back(PRICELISTPROC_PROCINFOMSG.getName());

					return arePropertiesSet(paramList);
				}

				void InsertPriceListProc::buildSQLString()
				{
					basar::VarString stmtSQL;
					stmtSQL.append("INSERT INTO cpricelistproc ");
					stmtSQL.append("( ");
					stmtSQL.append("   filename");
					stmtSQL.append("  ,pricelisttype");
					stmtSQL.append("  ,pricelistid");
					stmtSQL.append("  ,pharmacygroupid");
					stmtSQL.append("  ,calcdate");
					stmtSQL.append("  ,seqno");
					stmtSQL.append("  ,procdate");
					stmtSQL.append("  ,datefrom");
					stmtSQL.append("  ,numarticles");
					stmtSQL.append("  ,numprices");
					stmtSQL.append("  ,numprocarticles");
					stmtSQL.append("  ,numprocprices");
					stmtSQL.append("  ,numdelarticles");
					stmtSQL.append("  ,numarticleserror");
					stmtSQL.append("  ,procstate");
					stmtSQL.append("  ,procinformsg");
					stmtSQL.append(") VALUES ( ");
					stmtSQL.append(" '").append(PRICELISTPROC_FILENAME.toSQLReplacementString()).append("'");
					stmtSQL.append(",'").append(PRICELISTPROC_PRICELISTTYPE.toSQLReplacementString()).append("'");
					stmtSQL.append(",").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append(",'").append(PRICELISTPROC_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append(",").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_SEQNO.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_PROCDATE.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_DATEFROM.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMARTICLES.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMPRICES.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMPROCARTICLES.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMPROCPRICES.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMDELARTICLES.toSQLReplacementString());
					stmtSQL.append(",").append(PRICELISTPROC_NUMARTICLESERROR.toSQLReplacementString());
					stmtSQL.append(",'").append(PRICELISTPROC_PROCSTATE.toSQLReplacementString()).append("'");
					stmtSQL.append(",'").append(PRICELISTPROC_PROCINFOMSG.toSQLReplacementString()).append("'");
					stmtSQL.append(")");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// updatePriceListProc
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdatePriceListProc)
					bool UpdatePriceListProc::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_FILENAME.getName());
					paramList.push_back(PRICELISTPROC_NUMARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMPRICES.getName());
					paramList.push_back(PRICELISTPROC_NUMPROCARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMPROCPRICES.getName());
					paramList.push_back(PRICELISTPROC_NUMDELARTICLES.getName());
					paramList.push_back(PRICELISTPROC_NUMARTICLESERROR.getName());
					paramList.push_back(PRICELISTPROC_PROCSTATE.getName());
					paramList.push_back(PRICELISTPROC_PROCINFOMSG.getName());

					return arePropertiesSet(paramList);
				}

				void UpdatePriceListProc::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("UPDATE cpricelistproc SET ");
					stmtSQL.append("   numarticles = ").append(PRICELISTPROC_NUMARTICLES.toSQLReplacementString());
					stmtSQL.append("  ,numprices = ").append(PRICELISTPROC_NUMPRICES.toSQLReplacementString());
					stmtSQL.append("  ,numprocarticles = ").append(PRICELISTPROC_NUMPROCARTICLES.toSQLReplacementString());
					stmtSQL.append("  ,numprocprices = ").append(PRICELISTPROC_NUMPROCPRICES.toSQLReplacementString());
					stmtSQL.append("  ,numdelarticles = ").append(PRICELISTPROC_NUMDELARTICLES.toSQLReplacementString());
					stmtSQL.append("  ,numarticleserror = ").append(PRICELISTPROC_NUMARTICLESERROR.toSQLReplacementString());
					stmtSQL.append("  ,procstate = '").append(PRICELISTPROC_PROCSTATE.toSQLReplacementString()).append("'");
					stmtSQL.append("  ,procinformsg = '").append(PRICELISTPROC_PROCINFOMSG.toSQLReplacementString()).append("'");
					stmtSQL.append(" WHERE filename = '").append(PRICELISTPROC_FILENAME.toSQLReplacementString()).append("'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// updateStatusAndInfoMsg
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdateStatusAndInfoMsg)
					bool UpdateStatusAndInfoMsg::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());
					paramList.push_back(PRICELISTPROC_CALCDATE.getName());
					paramList.push_back(PRICELISTPROC_SEQNO.getName());
					paramList.push_back(PRICELISTPROC_PROCSTATE.getName());
					paramList.push_back(PRICELISTPROC_PROCINFOMSG.getName());

					return arePropertiesSet(paramList);
				}

				void UpdateStatusAndInfoMsg::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE cpricelistproc SET ");
					stmtSQL.append("   procstate = '").append(PRICELISTPROC_PROCSTATE.toSQLReplacementString()).append("'");
					stmtSQL.append("  ,procinformsg = '").append(PRICELISTPROC_PROCINFOMSG.toSQLReplacementString()).append("'");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND calcdate = ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("   AND seqno = ").append(PRICELISTPROC_SEQNO.toSQLReplacementString());

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// updateStatusToFailed
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdateStatusToFailed)
					bool UpdateStatusToFailed::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());
					paramList.push_back(PRICELISTPROC_CALCDATE.getName());
					paramList.push_back(PRICELISTPROC_SEQNO.getName());

					return arePropertiesSet(paramList);
				}

				void UpdateStatusToFailed::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE cpricelistproc SET ");
					stmtSQL.append("   procstate = 'aborted'");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND (calcdate < ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("        OR (calcdate = ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("            AND seqno < ").append(PRICELISTPROC_SEQNO.toSQLReplacementString());
					stmtSQL.append("           )");
					stmtSQL.append("       )");
					stmtSQL.append("   AND procstate = 'processing'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// deletePriceListProcByFileName
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeletePriceListProcByFileName)
					bool DeletePriceListProcByFileName::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_FILENAME.getName());

					return arePropertiesSet(paramList);
				}

				void DeletePriceListProcByFileName::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM cpricelistproc ");
					stmtSQL.append(" WHERE filename = '").append(PRICELISTPROC_FILENAME.toSQLReplacementString()).append("'");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// deletePriceListProcByKey
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeletePriceListProcByKey)
					bool DeletePriceListProcByKey::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICELISTPROC_PRICELISTID.getName());
					paramList.push_back(PRICELISTPROC_CALCDATE.getName());
					paramList.push_back(PRICELISTPROC_SEQNO.getName());

					return arePropertiesSet(paramList);
				}

				void DeletePriceListProcByKey::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM cpricelistproc ");
					stmtSQL.append(" WHERE pricelistid = ").append(PRICELISTPROC_PRICELISTID.toSQLReplacementString());
					stmtSQL.append("   AND calcdate = ").append(PRICELISTPROC_CALCDATE.toSQLReplacementString());
					stmtSQL.append("   AND seqno = ").append(PRICELISTPROC_SEQNO.toSQLReplacementString());

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}
			} // end namespace pricedata
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist
