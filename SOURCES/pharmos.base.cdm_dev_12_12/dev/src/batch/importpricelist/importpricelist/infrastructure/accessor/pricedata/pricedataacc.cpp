//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/pricedata/pricedataacc.h"
#include "domainmodule/pricedata/pricedatadm.h"
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
			namespace pricedata
			{
				using namespace importpricelist::domMod::pricedata;

				BEGIN_ACCESSOR_DEFINITION(lit::PriceDataAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_PHARMACYGROUPID)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_ARTICLENO)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_DATEFROM)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_DATETO)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_QUANTITY)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_FIXEDPRICE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_DISCOUNT_TYPE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRICEDATA_DISCOUNT_SPEC)
				END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::SelectPriceDataByPharmacyGroup)
				{
					SQL_BUILDER_CREATE(SelectPriceDataByPharmacyGroup)
					SQL_BUILDER_PUSH_BACK(SelectPriceDataByPharmacyGroup)
				}

				ACCESS_METHOD(lit::SelectArticlesWithValidPrices)
				{
					SQL_BUILDER_CREATE(SelectArticlesWithValidPrices)
					SQL_BUILDER_PUSH_BACK(SelectArticlesWithValidPrices)
				}

				ACCESS_METHOD(lit::SelectPriceDataNotInZArtikel)
				{
					SQL_BUILDER_CREATE(SelectPriceDataNotInZArtikel)
					SQL_BUILDER_PUSH_BACK(SelectPriceDataNotInZArtikel)
				}

				ACCESS_METHOD(lit::InsertPriceData)
				{
					SQL_BUILDER_CREATE(InsertPriceData)
					SQL_BUILDER_PUSH_BACK(InsertPriceData)
				}

				ACCESS_METHOD(lit::UpdatePriceDataDateToByPharmacyGroup)
				{
					SQL_BUILDER_CREATE(UpdatePriceDataDateToByPharmacyGroup)
					SQL_BUILDER_PUSH_BACK(UpdatePriceDataDateToByPharmacyGroup)
				}

				ACCESS_METHOD(lit::DeletePriceDataByPharmacyGroup)
				{
					SQL_BUILDER_CREATE(DeletePriceDataByPharmacyGroup)
					SQL_BUILDER_PUSH_BACK(DeletePriceDataByPharmacyGroup)
				}

				ACCESS_METHOD(lit::UpdatePriceDataDateToByPharmacyGroupArticle)
				{
					SQL_BUILDER_CREATE(UpdatePriceDataDateToByPharmacyGroupArticle)
					SQL_BUILDER_PUSH_BACK(UpdatePriceDataDateToByPharmacyGroupArticle)
				}

				ACCESS_METHOD(lit::DeletePriceDataByPharmacyGroupArticle)
				{
					SQL_BUILDER_CREATE(DeletePriceDataByPharmacyGroupArticle)
					SQL_BUILDER_PUSH_BACK(DeletePriceDataByPharmacyGroupArticle)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// selectPriceDataByPharmacyGroup
				//
				// select the latest still valid prices from cdiscount for update on receiving a new pricelist
				// dateto must be at least within the value of the current processing date assuring
				// not to select prices that have been invalidated previously.
				// each entry is uniquely defined by
				//    articleno, pharmacygroupid, quantity, discounttype, discountspec, datefrom, dateto
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPriceDataByPharmacyGroup)
				bool SelectPriceDataByPharmacyGroup::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPriceDataByPharmacyGroup::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT articleno AS ").append(PRICEDATA_ARTICLENO.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRICEDATA_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,datefrom AS ").append(PRICEDATA_DATEFROM.getName());
					stmtSQL.append("      ,dateto AS ").append(PRICEDATA_DATETO.getName());
					stmtSQL.append("      ,baseqty AS ").append(PRICEDATA_QUANTITY.getName());
					stmtSQL.append("      ,fixedprice AS ").append(PRICEDATA_FIXEDPRICE.getName());
					stmtSQL.append("      ,discounttype AS ").append(PRICEDATA_DISCOUNT_TYPE.getName());
					stmtSQL.append("      ,discountspec AS ").append(PRICEDATA_DISCOUNT_SPEC.getName());
					stmtSQL.append("  FROM cdiscount");
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND datefrom <= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					stmtSQL.append("   AND dateto >= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");
					stmtSQL.append(" ORDER BY articleno");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectPriceDataByArticlePharmacyGroup
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPriceDataByArticlePharmacyGroup)
					bool SelectPriceDataByArticlePharmacyGroup::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_ARTICLENO.getName());
					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());
					paramList.push_back(PRICEDATA_DATETO.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPriceDataByArticlePharmacyGroup::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT articleno AS ").append(PRICEDATA_ARTICLENO.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRICEDATA_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,datefrom AS ").append(PRICEDATA_DATEFROM.getName());
					stmtSQL.append("      ,dateto AS ").append(PRICEDATA_DATETO.getName());
					stmtSQL.append("      ,baseqty AS ").append(PRICEDATA_QUANTITY.getName());
					stmtSQL.append("      ,fixedprice AS ").append(PRICEDATA_FIXEDPRICE.getName());
					stmtSQL.append("      ,discounttype AS ").append(PRICEDATA_DISCOUNT_TYPE.getName());
					stmtSQL.append("      ,discountspec AS ").append(PRICEDATA_DISCOUNT_SPEC.getName());
					stmtSQL.append("  FROM cdiscount ");
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND articleno = ").append(PRICEDATA_ARTICLENO.toSQLReplacementString());
					stmtSQL.append("   AND datefrom >= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					stmtSQL.append("   AND dateto <= ").append(PRICEDATA_DATETO.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectArticlesWithValidPrices
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectArticlesWithValidPrices)
					bool SelectArticlesWithValidPrices::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());

					return arePropertiesSet(paramList);
				}

				void SelectArticlesWithValidPrices::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("SELECT distinct articleno AS ").append(PRICEDATA_ARTICLENO.getName());
					stmtSQL.append("  FROM cdiscount ");
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND datefrom <= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					stmtSQL.append("   AND dateto >= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// selectPriceDataNotInZArtikel
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPriceDataNotInZArtikel)
					bool SelectPriceDataNotInZArtikel::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPriceDataNotInZArtikel::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					stmtSQL.append("SELECT articleno AS ").append(PRICEDATA_ARTICLENO.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRICEDATA_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,datefrom AS ").append(PRICEDATA_DATEFROM.getName());
					stmtSQL.append("      ,dateto AS ").append(PRICEDATA_DATETO.getName());
					stmtSQL.append("      ,baseqty AS ").append(PRICEDATA_QUANTITY.getName());
					stmtSQL.append("      ,fixedprice AS ").append(PRICEDATA_FIXEDPRICE.getName());
					stmtSQL.append("      ,discounttype AS ").append(PRICEDATA_DISCOUNT_TYPE.getName());
					stmtSQL.append("      ,discountspec AS ").append(PRICEDATA_DISCOUNT_SPEC.getName());
					stmtSQL.append("  FROM cdiscount ");
					stmtSQL.append(" WHERE pharmacygroupid = ").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString());
					stmtSQL.append("   AND datefrom >= ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");
					/* do not use "articleno not in (select artikel_nr from zartikel)" here, as it is
					   considerably slower than "NOT EXISTS" */
					stmtSQL.append("   AND NOT EXISTS (select artikel_nr from zartikel where artikel_nr = articleno)");
					stmtSQL.append(" ORDER BY articleno, datefrom, dateto, baseqty");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// insertPriceData
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(InsertPriceData)
					bool InsertPriceData::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_ARTICLENO.getName());
					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());
					paramList.push_back(PRICEDATA_DATETO.getName());
					paramList.push_back(PRICEDATA_QUANTITY.getName());
					paramList.push_back(PRICEDATA_FIXEDPRICE.getName());
					paramList.push_back(PRICEDATA_DISCOUNT_TYPE.getName());
					paramList.push_back(PRICEDATA_DISCOUNT_SPEC.getName());

					return arePropertiesSet(paramList);
				}

				void InsertPriceData::buildSQLString()
				{
					basar::VarString stmtSQL;
					stmtSQL.append("INSERT INTO cdiscount ");
					stmtSQL.append("( ");
					stmtSQL.append("   articleno");
					stmtSQL.append("  ,pharmacygroupid");
					stmtSQL.append("  ,datefrom");
					stmtSQL.append("  ,dateto");
					stmtSQL.append("  ,baseqty");
					stmtSQL.append("  ,fixedprice");
					stmtSQL.append("  ,discounttype");
					stmtSQL.append("  ,discountspec");
					// we have to explicitly set values for some columns where the default values set 
					// by the database are not what the proccessing programs expect (e.g. for 
					// monthlydiscount the db default value is ' ', but programs expect only boolean
					// values '0' or '1')
					stmtSQL.append("  ,pharmgrpexcluded");
					stmtSQL.append("  ,internaldiscount");
					stmtSQL.append("  ,monthlydiscount");
					stmtSQL.append("  ,pharmgrpexcl_2");
					stmtSQL.append("  ,pharmgrpexcl_3");
					stmtSQL.append("  ,no_multiple_qty");
					stmtSQL.append("  ,addondiscountok");
					stmtSQL.append("  ,paymenttermtype");
					stmtSQL.append("  ,turnovercalcimpact");
					stmtSQL.append(") VALUES ( ");
					stmtSQL.append(PRICEDATA_ARTICLENO.toSQLReplacementString());
					stmtSQL.append(",'").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append(",").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					stmtSQL.append(",").append(PRICEDATA_DATETO.toSQLReplacementString());
					stmtSQL.append(",").append(PRICEDATA_QUANTITY.toSQLReplacementString());
					stmtSQL.append(",").append(PRICEDATA_FIXEDPRICE.toSQLReplacementString());
					stmtSQL.append(",").append(PRICEDATA_DISCOUNT_TYPE.toSQLReplacementString());
					stmtSQL.append(",").append(PRICEDATA_DISCOUNT_SPEC.toSQLReplacementString());
					// constant default values
					stmtSQL.append(",'000'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'000'");
					stmtSQL.append(",'000'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(")");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// updatePriceDataDateToByPharmacyGroup
				// 
				// price data will not be deleted unless the entries have been archived
				// on receiving new price data, the previous prices will be set to "dateto" until today
				// only the latest prices will be updated not the entire history that have alread been "invalidated"
				// also future prices should not be touched
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdatePriceDataDateToByPharmacyGroup)
					bool UpdatePriceDataDateToByPharmacyGroup::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATETO.getName());

					return arePropertiesSet(paramList);
				}

				void UpdatePriceDataDateToByPharmacyGroup::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("UPDATE cdiscount ");
					stmtSQL.append("   SET dateto = ").append(PRICEDATA_DATETO.toSQLReplacementString());
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND datefrom <= ").append(PRICEDATA_DATETO.toSQLReplacementString());
					stmtSQL.append("   AND dateto > ").append(PRICEDATA_DATETO.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// deletePriceDataByPharmacyGroup
				//
				// deletes all future prices of a given pharmacygroup (pricelist) in case of duplicate processing
				// of the same pricelist file and in case within the last file had been future prices that have
				// not reached the date of validity (datefrom)
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeletePriceDataByPharmacyGroup)
					bool DeletePriceDataByPharmacyGroup::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());

					return arePropertiesSet(paramList);
				}

				void DeletePriceDataByPharmacyGroup::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM cdiscount");
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND datefrom > ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// updatePriceDataDateToByPharmacyGroupArticle
				// 
				// price data will not be deleted unless the entries have been archived
				// on receiving new price data, the previous prices will be set to "dateto" until today
				// only the latest prices will be updated not the entire history that have alread been "invalidated"
				// also future prices should not be touched
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(UpdatePriceDataDateToByPharmacyGroupArticle)
					bool UpdatePriceDataDateToByPharmacyGroupArticle::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_ARTICLENO.getName());
					paramList.push_back(PRICEDATA_DATETO.getName());

					return arePropertiesSet(paramList);
				}

				void UpdatePriceDataDateToByPharmacyGroupArticle::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("UPDATE cdiscount ");
					stmtSQL.append("   SET dateto = ").append(PRICEDATA_DATETO.toSQLReplacementString());
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND articleno = ").append(PRICEDATA_ARTICLENO.toSQLReplacementString());
					stmtSQL.append("   AND datefrom <= ").append(PRICEDATA_DATETO.toSQLReplacementString());
					stmtSQL.append("   AND dateto > ").append(PRICEDATA_DATETO.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}

				//---------------------------------------------------------------------------------------------//
				// deletePriceDataByPharmacyGroupArticle
				//
				// deletes all future prices of a given pharmacygroup (pricelist) in case of duplicate processing
				// of the same pricelist file and in case within the last file had been future prices that have
				// not reached the date of validity (datefrom)
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(DeletePriceDataByPharmacyGroupArticle)
					bool DeletePriceDataByPharmacyGroupArticle::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRICEDATA_PHARMACYGROUPID.getName());
					paramList.push_back(PRICEDATA_ARTICLENO.getName());
					paramList.push_back(PRICEDATA_DATEFROM.getName());

					return arePropertiesSet(paramList);
				}

				void DeletePriceDataByPharmacyGroupArticle::buildSQLString()
				{
					basar::VarString stmtSQL = "";

					stmtSQL.append("DELETE FROM cdiscount");
					stmtSQL.append(" WHERE pharmacygroupid = '").append(PRICEDATA_PHARMACYGROUPID.toSQLReplacementString()).append("'");
					stmtSQL.append("   AND articleno = ").append(PRICEDATA_ARTICLENO.toSQLReplacementString());
					stmtSQL.append("   AND datefrom > ").append(PRICEDATA_DATEFROM.toSQLReplacementString());
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}
			} // end namespace pricedata
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist
