//-------------------------------------------------------------------------------------------------//
/*! \file	articlecodedm.cpp
*   \brief	domain module for article codes
*   \author NTT DATA
*   \date	14.02.2022
*/
//-------------------------------------------------------------------------------------------------//

#include "articlecodesdm.h"
#include "infrastructure/accessor/articlecodes/articlecodesacc.h"
#include "libutil/exception.h"

namespace importpricelist
{
	namespace domMod
	{
		namespace articlecodes
		{
			ArticleCodesDM::ArticleCodesDM(const log4cplus::Logger& logger)
				: m_Logger(logger)
			{
				METHODNAME_DEF(ArticleCodesDM, ArticleCodesDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			ArticleCodesDM::~ArticleCodesDM()
			{
				METHODNAME_DEF(ArticleCodesDM, ~ArticleCodesDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void ArticleCodesDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
			}

			bool ArticleCodesDM::selectArticleNoByCodeAndType(const basar::VarString articleCode, const basar::Int16 codeType, basar::Int32 &articleNo)
			{
				METHODNAME_DEF(ArticleCodesDM, selectArticleNoByCodeAndType)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getArticleCodes().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(ARTCD_ARTICLECODE.getName(), articleCode);
					whereCondition.setInt16(ARTCD_CODETYPE.getName(), codeType);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::articlecodes::lit::SelectArticleNoByCodeAndType, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::articlecodes::lit::SelectArticleNoByCodeAndType, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::articlecodes::lit::SelectArticleNoByCodeAndType, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getArticleCodes();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						articleNo = dataIterator.getInt32(ARTCD_ARTICLENO.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			basar::db::aspect::AccessorPropertyTableRef ArticleCodesDM::getArticleCodes()
			{
				METHODNAME_DEF(PriceDataDM, getPriceData)
				BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}
		}
	}
}
