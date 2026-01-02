#include <libutil/accessor.h>
#include <libutil/dbconnection.h>
#include <libbasardbsql.h>
#include <libbasardbaspect_accessor.h>

#ifndef GUARD_DELIVERYPARAM_H
#define GUARD_DELIVERYPARAM_H
//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace subsequentdeliveryrelevantcalculator
{
	namespace domMod
	{
		namespace deliveryparam
		{

			class DeliveryParamData
			{
			public:
				basar::Int32 branchNo;
				basar::Int32 ruleId;
				basar::Int32 ruleStart;
				basar::Int32 ruleTrue;
				basar::Int32 ruleFalse;
				bool ruleActive;
				basar::VarString value1;
				basar::VarString value2;
				basar::VarString value3;
				basar::VarString value4;
				basar::VarString value5;
				basar::VarString value6;
			public:
				DeliveryParamData();
				~DeliveryParamData() {};
				DeliveryParamData(const DeliveryParamData& other);
				DeliveryParamData& operator=(const DeliveryParamData& other);
			};

			class DeliveryParamDM
			{
			public:
				DeliveryParamDM(const log4cplus::Logger& logger);
				~DeliveryParamDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				basar::db::aspect::ExecuteResultInfo selectDeliveryParams(basar::Int16 branchno);

				basar::db::aspect::AccessorPropertyTableRef getDeliveryParamData();

				void beginTransaction();
				void commitTransaction();
				void rollbackTransaction();

			private:
				DeliveryParamDM(const DeliveryParamDM& other);
				DeliveryParamDM& operator=(const DeliveryParamDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::sql::ConnectionRef m_DbSqlConnection;
				basar::db::sql::ConnectionRef& getDbSqlConnection() { return m_DbSqlConnection; };
			};

			typedef boost::shared_ptr< DeliveryParamDM > DeliveryParamDMPtr;

			//! List DeliveryParam properties
			CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_BRANCHNO, "branchno", basar::INT16)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULEID, "ruleid", basar::INT32)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULESTART, "rulestart", basar::INT16)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULETRUE, "ruletrue", basar::INT32)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULEFALSE, "rulefalse", basar::INT32)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULEACTIVE, "activationflag", basar::INT16)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_RULENAME, "rulename", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE1, "value1", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE2, "value2", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE3, "value3", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE4, "value4", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE5, "value5", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE6, "value6", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE7, "value7", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE8, "value8", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE9, "value9", basar::STRING)
				CONST_PROPERTY_DESCRIPTION(DELIVERYPARAM_VALUE10, "value10", basar::STRING)
		}
	}
}

#endif