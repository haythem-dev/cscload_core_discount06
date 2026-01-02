//-------------------------------------------------------------------------------------------------//
/*! \file	subsequentdeliveryconfigdm.h
*   \brief	domain module for subsequent delivery config table
*   \author NTT DATA
*   \date	27.08.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYCONFIGDM_H  
#define GUARD_SUBSEQUENTDELIVERYCONFIGDM_H

#include <libutil/accessor.h>
#include <libutil/dbconnection.h>
#include <libbasardbsql.h>
#include <libbasardbaspect_accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace subsequentdeliveryrelevantcalculator
{
	namespace domMod
	{
		namespace subsequentdeliveryconfig
		{
			class SubsequentDeliveryConfigDM
			{
			public: 
				SubsequentDeliveryConfigDM(const log4cplus::Logger& logger);
				~SubsequentDeliveryConfigDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				basar::db::aspect::ExecuteResultInfo initSubsequentDeliveryConfig(basar::Int16 branchno);

				// insert and update methods use prepared statements implemented directly in the domain module
				basar::db::sql::ExecuteReturnInfo insertSubsequentDeliveryConfig(basar::Int16 branchno,
					                                                             basar::Int32 articleno, 
					                                                             basar::Int16 subsequentdelivery, 
					                                                             basar::VarString lastchangeuser = SubsequentDeliveryConfigDM::CALCULATOR_BATCH_NAME);
				basar::db::sql::ExecuteReturnInfo updateSubsequentDeliveryConfig(basar::Int16 branchno,
				                                                                 basar::Int32 articleno,
					                                                             basar::Int16 subsequentdelivery,
					                                                             basar::VarString lastchangeuser = SubsequentDeliveryConfigDM::CALCULATOR_BATCH_NAME);
				basar::db::aspect::ExecuteResultInfo resetSubsequentDeliveryConfig(basar::Int16 branchno);
				basar::db::aspect::ExecuteResultInfo deleteSubsequentDeliveryConfigForNotExistingArticles(basar::Int16 branchno);
				basar::db::aspect::ExecuteResultInfo deleteSubsequentDeliveryConfigForBlockedArticles(basar::Int16 branchno);

				basar::db::aspect::AccessorPropertyTableRef getSubsequentDeliveryConfigData();

				void beginTransaction();
				void commitTransaction();
				void rollbackTransaction();

				static basar::VarString CALCULATOR_BATCH_NAME;

			private:
				SubsequentDeliveryConfigDM(const SubsequentDeliveryConfigDM& other);
				SubsequentDeliveryConfigDM& operator=(const SubsequentDeliveryConfigDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::sql::ConnectionRef m_DbSqlConnection;
				basar::db::sql::ConnectionRef& getDbSqlConnection() { return m_DbSqlConnection; };

				basar::db::sql::PreparedStatementRef m_PrepStmtInsert;
				basar::db::sql::PreparedStatementRef m_PrepStmtUpdate;
			};

			typedef boost::shared_ptr< SubsequentDeliveryConfigDM > SubsequentDeliveryConfigDMPtr;

			//! List article properties
			CONST_PROPERTY_DESCRIPTION(CFG_BRANCHNO, "branchno", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(CFG_ARTICLENO, "articleno", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(CFG_SUBSEQUENTDELIVERY, "subsequentdelivery", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(CFG_LASTCHANGEDATE, "lastchangedate", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(CFG_LASTCHANGEUSER, "lastchangeuser", basar::STRING)
		} // namespace subsequentdeliveryconfig
	} // namespace domMod
}// namespace subsequentdeliveryrelevantcalculator
#endif