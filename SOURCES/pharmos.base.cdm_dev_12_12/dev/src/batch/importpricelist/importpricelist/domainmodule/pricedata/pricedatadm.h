//-------------------------------------------------------------------------------------------------//
/*! \file	pricedatadm.h
*   \brief	domain module for price data within cdiscount table
*   \author NTT DATA
*   \date	27.08.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICEDATADM_H  
#define GUARD_PRICEDATADM_H

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
		namespace pricedata
		{
			class PriceData
			{
			public:
				basar::Int32 pharmacyGroupId; 
				basar::Int32 articleNo;
				basar::Int32 dateFrom;	// Format YYYYMMDD
				basar::Int32 dateTo;    // Format YYYYMMDD
				basar::Int32 quantity;
				basar::Decimal fixedPrice;
				basar::Int16 discountType;
				basar::Int16 discountSpec;

			public:
				PriceData();
				~PriceData() {};
				PriceData(const PriceData& other);
				PriceData& operator=(const PriceData& other);

				static basar::VarString convertInt32ToVarString(const basar::Int32 value, const basar::Int16 length);
				static basar::Int32     convertVarStringToInt32(const basar::VarString& value);
				static basar::Decimal   convertVarStringToDecimal(const basar::VarString& value);
			};

			class PriceDataDM
			{
			public: 
				PriceDataDM(const log4cplus::Logger& logger);
				~PriceDataDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				basar::db::aspect::ExecuteResultInfo selectPriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom);
				basar::db::aspect::ExecuteResultInfo selectArticlesWithValidPrices(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom);
				basar::db::aspect::ExecuteResultInfo selectPriceDataNotInZArtikel(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom);
				// insertPriceData uses a prepared statement and is implemented directly in the DM (no accessor)
				// --> returns different object than the other methods
				basar::db::sql::ExecuteReturnInfo    insertPriceData(const PriceData& priceData);
				basar::db::aspect::ExecuteResultInfo invalidatePriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateTo);
				basar::db::aspect::ExecuteResultInfo deletePriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom);
				basar::db::aspect::ExecuteResultInfo invalidatePriceDataByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateTo);
				basar::db::aspect::ExecuteResultInfo deletePriceDataByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateFrom);
                // invalidating and deleting prices per article with prepared statements
				basar::db::sql::ExecuteReturnInfo    invalidateByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateTo);
				basar::db::sql::ExecuteReturnInfo    deleteByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateFrom);

				basar::db::aspect::AccessorPropertyTableRef getPriceData();

				void beginTransaction();
				void commitTransaction();
				void rollbackTransaction();

			private:
				PriceDataDM(const PriceDataDM& other);
				PriceDataDM& operator=(const PriceDataDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::sql::ConnectionRef m_DbSqlConnection;
				basar::db::sql::ConnectionRef& getDbSqlConnection() { return m_DbSqlConnection; };

				basar::db::sql::PreparedStatementRef m_PrepStmtInsert;
				basar::db::sql::PreparedStatementRef m_PrepStmtInvalidate;
				basar::db::sql::PreparedStatementRef m_PrepStmtDelete;
			};

			typedef boost::shared_ptr< PriceDataDM > PriceDataDMPtr;

			//! List cdiscount / pricedata properties
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_PHARMACYGROUPID, "pharmacygroupid", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_ARTICLENO, "articleno", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_DATEFROM, "datefrom", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_DATETO, "dateto", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_QUANTITY, "baseqty", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_DISCOUNT_TYPE, "discounttype", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_DISCOUNT_SPEC, "discountspec", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(PRICEDATA_FIXEDPRICE, "fixedprice", basar::DECIMAL)
			CONST_PROPERTY_DESCRIPTION(FORMAT_CODE_DUMMY, "dummy", basar::STRING)

		} // namespace pricedata
	} // namespace domMod
}// namespace importpricelist
#endif