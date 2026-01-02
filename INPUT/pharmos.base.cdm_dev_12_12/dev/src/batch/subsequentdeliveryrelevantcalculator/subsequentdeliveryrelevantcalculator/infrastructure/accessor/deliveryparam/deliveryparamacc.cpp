//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/deliveryparam/deliveryparamacc.h"
#include "domainmodule/deliveryparam/deliveryparamdm.h"
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace deliveryparam
			{
				using namespace subsequentdeliveryrelevantcalculator::domMod::deliveryparam;

				BEGIN_ACCESSOR_DEFINITION(lit::DeliveryParamAcc)

					BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_BRANCHNO)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULEID)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULESTART)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULETRUE)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULEFALSE)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULEACTIVE)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_RULENAME)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE1)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE2)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE3)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE4)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE5)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE6)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE7)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE8)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE9)
					PROPERTY_DESCRIPTION_LIST_ADD(DELIVERYPARAM_VALUE10)
					END_PROPERTY_DESCRIPTION_LIST

					ACCESS_METHOD(lit::SelectDeliveryParams)
					{
						SQL_BUILDER_CREATE(SelectDeliveryParams)
						SQL_BUILDER_PUSH_BACK(SelectDeliveryParams)
					}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// SelectDeliveryParams
				//
				// select all relevant deliveryparams 
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectDeliveryParams)
				bool SelectDeliveryParams::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(DELIVERYPARAM_BRANCHNO.getName());

					return arePropertiesSet(paramList);
				}

				void SelectDeliveryParams::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("SELECT dp.branchNo AS ").append(DELIVERYPARAM_BRANCHNO);
					stmtSQL.append("      ,dp.ruleid AS ").append(DELIVERYPARAM_RULEID);
					stmtSQL.append("      ,dp.rulestart AS ").append(DELIVERYPARAM_RULESTART);
					stmtSQL.append("      ,dp.ruletrue AS ").append(DELIVERYPARAM_RULETRUE);
					stmtSQL.append("      ,dp.rulefalse AS ").append(DELIVERYPARAM_RULEFALSE);
					stmtSQL.append("      ,dp.activationflag AS ").append(DELIVERYPARAM_RULEACTIVE);
					stmtSQL.append("      ,dr.rulename AS ").append(DELIVERYPARAM_RULENAME);
					stmtSQL.append("      ,dp.value1 AS ").append(DELIVERYPARAM_VALUE1);
					stmtSQL.append("      ,dp.value2 AS ").append(DELIVERYPARAM_VALUE2);
					stmtSQL.append("      ,dp.value3 AS ").append(DELIVERYPARAM_VALUE3);
					stmtSQL.append("      ,dp.value4 AS ").append(DELIVERYPARAM_VALUE4);
					stmtSQL.append("      ,dp.value5 AS ").append(DELIVERYPARAM_VALUE5);
					stmtSQL.append("      ,dp.value6 AS ").append(DELIVERYPARAM_VALUE6);
					stmtSQL.append("      ,dp.value7 AS ").append(DELIVERYPARAM_VALUE7);
					stmtSQL.append("      ,dp.value8 AS ").append(DELIVERYPARAM_VALUE8);
					stmtSQL.append("      ,dp.value9 AS ").append(DELIVERYPARAM_VALUE9);
					stmtSQL.append("      ,dp.value10 AS ").append(DELIVERYPARAM_VALUE10);
					stmtSQL.append(" FROM csubsequentdeliveryparam dp, csubsequentdeliveryrule dr");
					stmtSQL.append(" WHERE dp.branchno = ").append(DELIVERYPARAM_BRANCHNO.toSQLReplacementString());
					//stmtSQL.append("   AND dp.activationflag = 1");
					stmtSQL.append("   AND dp.ruleid=dr.ruleid");
					stmtSQL.append(" ORDER BY ruleid, rulename ASC");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}
			} // end namespace deliveryparam
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist
