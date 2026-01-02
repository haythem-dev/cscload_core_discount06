//-------------------------------------------------------------------------------------------------//
/*! \file	articlecodesdm.h
*   \brief	domain module for article codes
*   \author NTT DATA
*   \date	14.02.2022
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_ARTICLECODESDM_H  
#define GUARD_ARTICLECODESDM_H

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
		namespace articlecodes
		{
			class ArticleCodesDM
			{
			public: 
				ArticleCodesDM(const log4cplus::Logger& logger);
				~ArticleCodesDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				bool selectArticleNoByCodeAndType(const basar::VarString articleCode, const basar::Int16 codeType, basar::Int32 &articleNo);

			private:
				ArticleCodesDM(const ArticleCodesDM& other);
				ArticleCodesDM& operator=(const ArticleCodesDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::aspect::AccessorPropertyTableRef getArticleCodes();
			};

			typedef boost::shared_ptr< ArticleCodesDM > ArticleCodesDMPtr;

			//! List price list 2 pharmacy group properties
			CONST_PROPERTY_DESCRIPTION(ARTCD_ARTICLENO, "articleno", basar::INT32)
			CONST_PROPERTY_DESCRIPTION(ARTCD_ARTICLECODE, "articlecode", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(ARTCD_CODETYPE, "code_type", basar::INT16)

		} // namespace pricedata
	} // namespace domMod
}// namespace importpricelist
#endif