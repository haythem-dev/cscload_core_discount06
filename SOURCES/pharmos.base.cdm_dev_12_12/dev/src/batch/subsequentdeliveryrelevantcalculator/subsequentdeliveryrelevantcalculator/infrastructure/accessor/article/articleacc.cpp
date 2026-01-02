//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/article/articleacc.h"
#include "domainmodule/article/articledm.h"
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
			namespace article
			{
				using namespace subsequentdeliveryrelevantcalculator::domMod::article;

				BEGIN_ACCESSOR_DEFINITION(lit::ArticleAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_BRANCHNO)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_ARTICLENO)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_NAME)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_CONTINGENT_PPE)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_BTM)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_DATE_EXPIRED)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_DATE_AVAILBLE_FROM)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_COOLING)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_ALLOCATED_QUANTITY_CONTROL)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_GROUP)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_STORAGE_LOCATION)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_OPEN_ORDER_QUANTITY)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_OPEN_ORDER_QUANTITY_NOT_EFFECTIVE)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_SUBSEQUENTDELIVERY)
					PROPERTY_DESCRIPTION_LIST_ADD(ARTICLE_LASTCHANGEUSER)
					END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::SelectArticles)
				{
					SQL_BUILDER_CREATE(SelectArticles)
					SQL_BUILDER_PUSH_BACK(SelectArticles)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// selectArticles
				//
				// select all relevant articles 
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectArticles)
				bool SelectArticles::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(ARTICLE_BRANCHNO.getName());

					return arePropertiesSet(paramList);
				}

				void SelectArticles::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT za.artikel_nr AS ").append(ARTICLE_ARTICLENO.getName());
					stmtSQL.append("      ,za.artikel_name AS ").append(ARTICLE_NAME.getName());
					stmtSQL.append("      ,za.kontingent_ppe AS ").append(ARTICLE_CONTINGENT_PPE.getName());
					stmtSQL.append("      ,za.btm AS ").append(ARTICLE_BTM.getName());
					stmtSQL.append("      ,za.datum_ah ").append(ARTICLE_DATE_EXPIRED.getName());
					stmtSQL.append("      ,za.datum_lieferbar_ab AS ").append(ARTICLE_DATE_AVAILBLE_FROM.getName());
					stmtSQL.append("      ,za.kuehlartikel AS ").append(ARTICLE_COOLING.getName());
					stmtSQL.append("      ,za.kontingent_mengensteuerung AS ").append(ARTICLE_ALLOCATED_QUANTITY_CONTROL.getName());
					stmtSQL.append("      ,nvl(zwg.warengruppe,'') AS ").append(ARTICLE_GROUP.getName());
					stmtSQL.append("      ,nvl(af.lagerfachnr,'') AS ").append(ARTICLE_STORAGE_LOCATION.getName());
					stmtSQL.append("      ,nvl(af.offene_bestmenge,0) AS ").append(ARTICLE_OPEN_ORDER_QUANTITY.getName());
					stmtSQL.append("      ,nvl(af.openorderqty_noteffective,0) AS ").append(ARTICLE_OPEN_ORDER_QUANTITY_NOT_EFFECTIVE.getName());
					stmtSQL.append("      ,nvl(cf.subsequentdelivery, -1)::SMALLINT AS ").append(ARTICLE_SUBSEQUENTDELIVERY.getName());
					stmtSQL.append("      ,nvl(cf.lastchangeuser,'') AS ").append(ARTICLE_LASTCHANGEUSER.getName());
					stmtSQL.append("  FROM zartikel za ");
					stmtSQL.append("  LEFT JOIN artikelf af ON (af.artikel_nr = za.artikel_nr and af.filialnr = ").append(ARTICLE_BRANCHNO.toSQLReplacementString()).append(")");
					stmtSQL.append("  LEFT JOIN zartwg zwg ON (zwg.artikel_nr = za.artikel_nr and zwg.art = 2)");
					stmtSQL.append("  LEFT JOIN csubsequentdeliverybrancharticleconfig cf ON cf.branchno = af.filialnr AND cf.articleno = af.artikel_nr");
					stmtSQL.append(" WHERE za.zentr_eksperre = '0'");
					stmtSQL.append("   AND za.artikel_gesperrt = '0'");
					stmtSQL.append("   AND za.artikel_geloescht = '0'");
					//stmtSQL.append("   AND af.filialnr = ").append(ARTICLE_BRANCHNO.toSQLReplacementString());
					stmtSQL.append("   AND (cf.subsequentdelivery is null or cf.subsequentdelivery in (0, 1))");
					stmtSQL.append(" ORDER BY af.artikel_nr");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerAccessors());
				}
			} // end namespace article
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace subsequentdeliveryrelevantcalculator
