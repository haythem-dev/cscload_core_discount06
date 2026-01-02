//-------------------------------------------------------------------------------------------------//
/*! \file	articledm.cpp
*   \brief	domain module für article data (zartikel / artikelf)
*   \author NTT Data
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#include "articledm.h"
#include "infrastructure/accessor/article/articleacc.h"
#include "libutil/exception.h"

namespace subsequentdeliveryrelevantcalculator
{
	namespace domMod
	{
		namespace article
		{
			ArticleDM::ArticleDM(const log4cplus::Logger& logger)
				: m_Logger(logger)
			{
				METHODNAME_DEF(ArticleDM, ArticleDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			ArticleDM::~ArticleDM()
			{
				METHODNAME_DEF(ArticleDM, ~ArticleDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void ArticleDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
				m_DbSqlConnection = conn->getCurrentConnection().getSqlConnection();
			}

			basar::db::aspect::ExecuteResultInfo ArticleDM::selectArticles(basar::Int16 branchno)
			{
				METHODNAME_DEF(ArticleDM, selectArticles)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getArticleData().insert(basar::FOR_UNKNOWN);

					whereCondition.setInt16(ARTICLE_BRANCHNO.getName(), branchno);

					executeResultInfo = getAccessor()->execute(infrastructure::accessor::article::lit::SelectArticles, whereCondition, true, true, basar::db::aspect::HOLD_RECORDSET);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::article::lit::SelectArticles, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::article::lit::SelectArticles, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::AccessorPropertyTableRef ArticleDM::getArticleData()
			{
				METHODNAME_DEF(ArticleDM, getArticleData)
			    BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			void ArticleDM::beginTransaction()
			{
				getDbConnection().beginTransaction();
			}

			void ArticleDM::commitTransaction()
			{
				getDbConnection().commitTransaction();
			}

			void ArticleDM::rollbackTransaction()
			{
				getDbConnection().rollbackTransaction();
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// ArticleData containing article data for
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			ArticleData::ArticleData()
				:articleNo(0)
				, name("")
				, contingentPpe("")
				, btm("")
				, dateAvailableFrom(0)
				, cooling("")
				, allocatedQuantityControl("")
			{

			}

			ArticleData::ArticleData(const ArticleData& other)
			{
				*this = other;
			}

			ArticleData& ArticleData::operator=(const ArticleData& other)
			{
				articleNo = other.articleNo;
				name = other.name;
				contingentPpe = other.contingentPpe;
				btm = other.btm;
				dateExpired = other.dateExpired;
				dateAvailableFrom = other.dateAvailableFrom;
				cooling = other.cooling;
				allocatedQuantityControl = other.allocatedQuantityControl;
				return *this;
			}
		}
	}
}
