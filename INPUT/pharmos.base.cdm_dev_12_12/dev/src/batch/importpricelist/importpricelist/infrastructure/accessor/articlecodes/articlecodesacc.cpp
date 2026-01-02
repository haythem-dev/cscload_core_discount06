//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/articlecodes/articlecodesacc.h"
#include "domainmodule/articlecodes/articlecodesdm.h"
#include "loggerpool/importpricelist_loggerpool.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace articlecodes
			{
				using namespace importpricelist::domMod::articlecodes;

				BEGIN_ACCESSOR_DEFINITION(lit::ArticleCodesAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(ARTCD_ARTICLENO)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTCD_ARTICLECODE)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTCD_CODETYPE)
				END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::SelectArticleNoByCodeAndType)
				{
					SQL_BUILDER_CREATE(SelectArticleNoByCodeAndType)
					SQL_BUILDER_PUSH_BACK(SelectArticleNoByCodeAndType)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// selectArticleNoByCodeAndType
				//
				// select the article no for the given article code and article code type
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectArticleNoByCodeAndType)
				bool SelectArticleNoByCodeAndType::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(ARTCD_ARTICLECODE.getName());
					paramList.push_back(ARTCD_CODETYPE.getName());

					return arePropertiesSet(paramList);
				}

				void SelectArticleNoByCodeAndType::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT articleno AS ").append(ARTCD_ARTICLENO.getName());
					stmtSQL.append("  FROM carticlecodes");
					stmtSQL.append(" WHERE article_code = '").append(ARTCD_ARTICLECODE.toSQLReplacementString()).append("'");
					stmtSQL.append(" AND code_type = ").append(ARTCD_CODETYPE.toSQLReplacementString());

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}
			} // end namespace articlecodes
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist
