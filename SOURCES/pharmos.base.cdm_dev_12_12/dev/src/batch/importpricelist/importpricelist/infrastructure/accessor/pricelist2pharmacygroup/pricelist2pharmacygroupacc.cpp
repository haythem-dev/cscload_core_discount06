//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/pricelist2pharmacygroup/pricelist2pharmacygroupacc.h"
#include "domainmodule/pricelist2pharmacygroup/pricelist2pharmacygroupdm.h"
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
			namespace pricelist2pharmacygroup
			{
				using namespace importpricelist::domMod::pricelist2pharmacygroup;

				BEGIN_ACCESSOR_DEFINITION(lit::PriceList2PharmacyGroupAcc)

				BEGIN_PROPERTY_DESCRIPTION_LIST
					PROPERTY_DESCRIPTION_LIST_ADD(PRL2PHGRP_PRICELISTID)
					PROPERTY_DESCRIPTION_LIST_ADD(PRL2PHGRP_PRICELISTNAME)
					PROPERTY_DESCRIPTION_LIST_ADD(PRL2PHGRP_PHARMACYGROUPID)
					PROPERTY_DESCRIPTION_LIST_ADD(PRL2PHGRP_DISCOUNT_TYPE)
					PROPERTY_DESCRIPTION_LIST_ADD(PRL2PHGRP_DISCOUNT_SPEC)
				END_PROPERTY_DESCRIPTION_LIST

				ACCESS_METHOD(lit::SelectPharmacyGroupByPriceListId)
				{
					SQL_BUILDER_CREATE(SelectPharmacyGroupByPriceListId)
					SQL_BUILDER_PUSH_BACK(SelectPharmacyGroupByPriceListId)
				}

				END_ACCESSOR_DEFINITION

				//---------------------------------------------------------------------------------------------//
				// selectPharmacyGroupByPriceListId
				//
				// select the pharmacy group id and other data (discounttype, discountspec), that
				// has been mapped to a price list id from the mapping table cpricelist2pharmgrp
				//---------------------------------------------------------------------------------------------//
				BUILDER_DEFINITION(SelectPharmacyGroupByPriceListId)
				bool SelectPharmacyGroupByPriceListId::isExecutable() const
				{
					basar::cmnutil::ParameterList paramList;

					paramList.push_back(PRL2PHGRP_PRICELISTID.getName());

					return arePropertiesSet(paramList);
				}

				void SelectPharmacyGroupByPriceListId::buildSQLString()
				{
					basar::VarString stmtSQL = "";
					
					stmtSQL.append("SELECT pricelistid AS ").append(PRL2PHGRP_PRICELISTID.getName());
					stmtSQL.append("      ,pricelistname AS ").append(PRL2PHGRP_PRICELISTNAME.getName());
					stmtSQL.append("      ,pharmacygroupid AS ").append(PRL2PHGRP_PHARMACYGROUPID.getName());
					stmtSQL.append("      ,discounttype AS ").append(PRL2PHGRP_DISCOUNT_TYPE.getName());
					stmtSQL.append("      ,discountspec AS ").append(PRL2PHGRP_DISCOUNT_SPEC.getName());
					stmtSQL.append("  FROM cpricelist2pharmgrp");
					stmtSQL.append(" WHERE pricelistid = ").append(PRL2PHGRP_PRICELISTID.toSQLReplacementString());

					resolve(stmtSQL);
					BLOG_TRACE_SQLSTRING(importpricelist::LoggerPool::getLoggerAccessors());
				}
			} // end namespace pricelist2pharmaycygroup
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist
