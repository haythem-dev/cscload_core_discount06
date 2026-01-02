//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/subsequentdeliveryconfig/subsequentdeliveryconfigacc.h"
#include "domainmodule/subsequentdeliveryconfig/subsequentdeliveryconfigdm.h"
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"

#include <libbasardbaspect.h>

#define CALCULATOR_BATCH_NAME "CALCULATOR_BATCH"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace subsequentdeliveryconfig
			{
				using namespace subsequentdeliveryrelevantcalculator::domMod::subsequentdeliveryconfig;

				BEGIN_ACCESSOR_DEFINITION(lit::SubsequentDeliveryConfigAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(CFG_BRANCHNO)
					PROPERTY_DESCRIPTION_LIST_ADD(CFG_ARTICLENO)
					PROPERTY_DESCRIPTION_LIST_ADD(CFG_SUBSEQUENTDELIVERY)
					PROPERTY_DESCRIPTION_LIST_ADD(CFG_LASTCHANGEDATE)
					PROPERTY_DESCRIPTION_LIST_ADD(CFG_LASTCHANGEUSER)
				END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::InitSubsequentDeliveryConfig)
				{
					SQL_BUILDER_CREATE(InitSubsequentDeliveryConfig)
					SQL_BUILDER_PUSH_BACK(InitSubsequentDeliveryConfig)
				}

				ACCESS_METHOD(lit::InsertSubsequentDeliveryConfig)
				{
					SQL_BUILDER_CREATE(InsertSubsequentDeliveryConfig)
					SQL_BUILDER_PUSH_BACK(InsertSubsequentDeliveryConfig)
				}

				ACCESS_METHOD(lit::UpdateSubsequentDeliveryConfig)
				{
					SQL_BUILDER_CREATE(UpdateSubsequentDeliveryConfig)
					SQL_BUILDER_PUSH_BACK(UpdateSubsequentDeliveryConfig)
				}

				ACCESS_METHOD(lit::ResetSubsequentDeliveryConfig)
				{
					SQL_BUILDER_CREATE(ResetSubsequentDeliveryConfig)
					SQL_BUILDER_PUSH_BACK(ResetSubsequentDeliveryConfig)
				}

				ACCESS_METHOD(lit::DeleteSubsequentDeliveryConfigForNotExistingArticles)
				{
					SQL_BUILDER_CREATE(DeleteSubsequentDeliveryConfigForNotExistingArticles)
					SQL_BUILDER_PUSH_BACK(DeleteSubsequentDeliveryConfigForNotExistingArticles)
				}

				ACCESS_METHOD(lit::DeleteSubsequentDeliveryConfigForBlockedArticles)
				{
					SQL_BUILDER_CREATE(DeleteSubsequentDeliveryConfigForBlockedArticles)
					SQL_BUILDER_PUSH_BACK(DeleteSubsequentDeliveryConfigForBlockedArticles)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// InitSubsequentDeliveryConfig
				//
				// update delivery config entries to subesequentdelivery = 0 for all disabled articles
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(InitSubsequentDeliveryConfig)
				bool InitSubsequentDeliveryConfig::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());
					return arePropertiesSet(paramList);
				}

				void InitSubsequentDeliveryConfig::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE csubsequentdeliverybrancharticleconfig SET ");
					stmtSQL.append("  subsequentdelivery = 0");
					stmtSQL.append(" ,lastchangedate = CURRENT");
					stmtSQL.append(" ,lastchangeuser = 'Disabled'");
					stmtSQL.append(" WHERE branchno = ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append("   AND articleno IN (");
					stmtSQL.append("                      SELECT artikel_nr FROM zartikel ");
					stmtSQL.append("                       WHERE zentr_eksperre = '1'");
					stmtSQL.append("                          OR artikel_gesperrt = '1'");
					stmtSQL.append("                          OR artikel_geloescht = '1'");
					stmtSQL.append("                    )");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// InsertSubsequentDeliveryConfig
				//
				// insert delivery config entry
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(InsertSubsequentDeliveryConfig)
				bool InsertSubsequentDeliveryConfig::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());
					paramList.push_back(CFG_ARTICLENO.getName());
					paramList.push_back(CFG_SUBSEQUENTDELIVERY.getName());

					return arePropertiesSet(paramList);
				}

				void InsertSubsequentDeliveryConfig::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("INSERT INTO csubsequentdeliverybrancharticleconfig (");
					stmtSQL.append(" branchno");
					stmtSQL.append(",articleno");
					stmtSQL.append(",subsequentdelivery");
					stmtSQL.append(",lastchangedate");
					stmtSQL.append(",lastchangeuser");
					stmtSQL.append(") VALUES ( ");
					stmtSQL.append("  ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append(" ,").append(CFG_ARTICLENO.toSQLReplacementString());
					stmtSQL.append(" ,").append(CFG_SUBSEQUENTDELIVERY.toSQLReplacementString());
					stmtSQL.append(" ,CURRENT");
					stmtSQL.append(" ,'").append(CFG_LASTCHANGEUSER.toSQLReplacementString()).append("'");
					stmtSQL.append(")");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// UpdateSubsequentDeliveryConfig
				//
				// update delivery config entry
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdateSubsequentDeliveryConfig)
				bool UpdateSubsequentDeliveryConfig::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());
					paramList.push_back(CFG_ARTICLENO.getName());
					paramList.push_back(CFG_SUBSEQUENTDELIVERY.getName());

					return arePropertiesSet(paramList);
				}

				void UpdateSubsequentDeliveryConfig::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE csubsequentdeliverybrancharticleconfig SET ");
					stmtSQL.append("  subsequentdelivery = ").append(CFG_SUBSEQUENTDELIVERY.toSQLReplacementString());
					stmtSQL.append(" ,lastchangedate = CURRENT");
					stmtSQL.append(" ,lastchangeuser = '").append(CFG_LASTCHANGEUSER.toSQLReplacementString()).append("'");
					stmtSQL.append(" WHERE branchno = ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append("   AND articleno = ").append(CFG_ARTICLENO.toSQLReplacementString());;

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// ResetSubsequentDeliveryConfig
				//
				// resets all entries for given branch from subsequentdelivery value 1 to 0
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(ResetSubsequentDeliveryConfig)
				bool ResetSubsequentDeliveryConfig::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());

					return arePropertiesSet(paramList);
				}

				void ResetSubsequentDeliveryConfig::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE csubsequentdeliverybrancharticleconfig");
					stmtSQL.append(" SET  subsequentdelivery = 0");
					stmtSQL.append("     ,lastchangedate = CURRENT");
					stmtSQL.append("     ,lastchangeuser = '" CALCULATOR_BATCH_NAME "'");
					stmtSQL.append(" WHERE branchno = ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append("   AND subsequentdelivery = 1");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// DeleteSubsequentDeliveryConfigForNotExistingArticles
				//
				// delete config entries for which no zarticle entry exists
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeleteSubsequentDeliveryConfigForNotExistingArticles)
				bool DeleteSubsequentDeliveryConfigForNotExistingArticles::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());

					return arePropertiesSet(paramList);
				}

				void DeleteSubsequentDeliveryConfigForNotExistingArticles::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM csubsequentdeliverybrancharticleconfig WHERE");
					stmtSQL.append(" branchno = ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append(" and articleno not in (select artikel_nr from zartikel)");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// DeleteSubsequentDeliveryConfigForBlockedArticles
				//
				// delete config entries for which only blocked zarticle entry exists
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeleteSubsequentDeliveryConfigForBlockedArticles)
				bool DeleteSubsequentDeliveryConfigForBlockedArticles::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(CFG_BRANCHNO.getName());

					return arePropertiesSet(paramList);
				}

				void DeleteSubsequentDeliveryConfigForBlockedArticles::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM csubsequentdeliverybrancharticleconfig WHERE");
					stmtSQL.append(" branchno = ").append(CFG_BRANCHNO.toSQLReplacementString());
					stmtSQL.append(" and articleno in (select artikel_nr ");
					stmtSQL.append("                   from zartikel ");
					stmtSQL.append("                   where zentr_eksperre <> '0'");
					stmtSQL.append("                      or artikel_gesperrt <> '0'");
					stmtSQL.append("                      or artikel_geloescht <> '0')");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}
			} // end namespace subsequentdeliveryconfig
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace subsequentdeliveryrelevantcalculator
