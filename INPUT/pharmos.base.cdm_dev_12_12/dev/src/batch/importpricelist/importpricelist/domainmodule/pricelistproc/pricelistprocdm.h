//-------------------------------------------------------------------------------------------------//
/*! \file	pricelistprocdm.h
*   \brief	domain module for price list processing status
*   \author NTT DATA
*   \date	14.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICELISTPROCDM_H  
#define GUARD_PRICELISTPROCDM_H

#include <libutil/accessor.h>
#include <libutil/dbconnection.h>
#include <libbasardbsql.h>
#include <libbasardbaspect_accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelistproc
		{
			class PriceListProc
			{
			public:
				basar::VarString fileName;
				basar::VarString priceListType;
				basar::Int32 priceListId;
				basar::Int32 pharmacyGroupId;
				basar::Int32 calcDate;
				basar::Int16 seqNo;
				basar::Int32 procDate;
				basar::Int32 dateFrom;
				basar::Int32 numArticles;
				basar::Int32 numPrices;
				basar::Int32 numProcArticles;
				basar::Int32 numProcPrices;
				basar::Int32 numDelArticles;
				basar::Int32 numArticlesError;
				basar::VarString procState;
				basar::VarString procInfoMsg;

			public:
				PriceListProc();
				~PriceListProc() {};
				PriceListProc(const PriceListProc& other);
				PriceListProc& operator=(const PriceListProc& other);
			};

			class PriceListProcDM
			{
			public: 
				PriceListProcDM(const log4cplus::Logger& logger);
				~PriceListProcDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				bool selectPriceListProcByFileName(const basar::VarString fileName, PriceListProc& priceListProc);
				bool selectPriceListProcByKey(PriceListProc& priceListProc);
				bool selectMaxDates(basar::Int32 priceListId, basar::Int32& maxCalcDate, basar::Int32& maxDateFrom);
				bool selectMaxSeqNo(basar::Int32 priceListId, basar::Int32 calcDate, basar::Int16& maxSeqNo);
				basar::db::aspect::ExecuteResultInfo insertPriceListProc(const PriceListProc& priceListProc);
				basar::db::aspect::ExecuteResultInfo updatePriceListProc(const PriceListProc& priceListProc);
				basar::db::sql::ExecuteReturnInfo    updatePriceListProcPrep(const PriceListProc& priceListProc);
				basar::db::aspect::ExecuteResultInfo updateStatusAndInfoMsg(const PriceListProc& priceListProc);
				basar::db::aspect::ExecuteResultInfo updateStatusToFailed(basar::Int32 priceListId, basar::Int32 calcDate, basar::Int16 seqNo);
				basar::db::aspect::ExecuteResultInfo deletePriceListProcByFileName(const basar::VarString& fileName);
				basar::db::aspect::ExecuteResultInfo deletePriceListProcByKey(const PriceListProc& priceListProc);

			private:
				PriceListProcDM(const PriceListProcDM& other);
				PriceListProcDM& operator=(const PriceListProcDM& other);

				basar::VarString cleanupProcInfoMsg(const basar::VarString& procInfoMsg);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::AccessorPropertyTableRef getPriceListProc();

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::sql::ConnectionRef m_DbSqlConnection;
				basar::db::sql::ConnectionRef& getDbSqlConnection() { return m_DbSqlConnection; };

				basar::db::sql::PreparedStatementRef m_PrepStmtUpdate;
			};

			typedef boost::shared_ptr< PriceListProcDM > PriceListProcDMPtr;

			//! List price list proc properties
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_FILENAME, "filename", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PRICELISTTYPE, "pricelisttype", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PRICELISTID, "pricelistid", basar::DECIMAL)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PHARMACYGROUPID, "pharmacygroupid", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_CALCDATE, "calcdate", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_SEQNO, "seqno", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PROCDATE, "procdate", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_DATEFROM, "datefrom", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMARTICLES, "numarticles", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMPRICES, "numprices", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMPROCARTICLES, "numprocarticles", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMPROCPRICES, "numprocprices", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMDELARTICLES, "numdelarticles", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_NUMARTICLESERROR, "numarticleserror", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PROCSTATE, "procstate", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRICELISTPROC_PROCINFOMSG, "procinformsg", basar::STRING)

		} // namespace pricelistproc
	} // namespace domMod
}// namespace importpricelist
#endif