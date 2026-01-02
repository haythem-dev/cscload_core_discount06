//-------------------------------------------------------------------------------------------------//
/*! \file	pricedatadm.h
*   \brief	domain module for price data within cdiscount table
*   \author NTT DATA
*   \date	27.08.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_ARTICLEDM_H  
#define GUARD_ARTICLEDM_H

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
		namespace article
		{
			class ArticleData
			{
			public:
				basar::Int32 articleNo;
				basar::VarString name;
				basar::VarString contingentPpe;
				basar::VarString btm;
				basar::Int32 dateExpired;          // Format YYYYMMDD
				basar::Int32 dateAvailableFrom;    // Format YYYYMMDD
				basar::VarString cooling;
				basar::VarString allocatedQuantityControl;

			public:
				ArticleData();
				~ArticleData() {};
				ArticleData(const ArticleData& other);
				ArticleData& operator=(const ArticleData& other);
			};

			class ArticleDM
			{
			public: 
				ArticleDM(const log4cplus::Logger& logger);
				~ArticleDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				basar::db::aspect::ExecuteResultInfo selectArticles(basar::Int16 branchno);

				basar::db::aspect::AccessorPropertyTableRef getArticleData();

				void beginTransaction();
				void commitTransaction();
				void rollbackTransaction();

			private:
				ArticleDM(const ArticleDM& other);
				ArticleDM& operator=(const ArticleDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::sql::ConnectionRef m_DbSqlConnection;
				basar::db::sql::ConnectionRef& getDbSqlConnection() { return m_DbSqlConnection; };
			};

			typedef boost::shared_ptr< ArticleDM > ArticleDMPtr;

			//! List article properties
			CONST_PROPERTY_DESCRIPTION(ARTICLE_ARTICLENO, "artikel_nr", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_NAME, "name", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_CONTINGENT_PPE, "kontingent_ppe", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_BTM, "btm", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_DATE_EXPIRED, "datum_ah", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_DATE_AVAILBLE_FROM, "datum_lieferbar_ab", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_COOLING, "kuehlartikel", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_ALLOCATED_QUANTITY_CONTROL, "kontingent_mengensteuerung", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_STORAGE_LOCATION, "lagerfachnr", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_OPEN_ORDER_QUANTITY, "offene_bestmenge", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_OPEN_ORDER_QUANTITY_NOT_EFFECTIVE, "openorderqty_noteffective", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_SUBSEQUENTDELIVERY, "subsequentdelivery", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_LASTCHANGEUSER, "lastchangeuser", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTICLE_BRANCHNO, "branchno", basar::INT16)
		    CONST_PROPERTY_DESCRIPTION(ARTICLE_GROUP, "warengruppe", basar::STRING)
		} // namespace Article
	} // namespace domMod
}// namespace subsequentdeliveryrelevantcalculator
#endif