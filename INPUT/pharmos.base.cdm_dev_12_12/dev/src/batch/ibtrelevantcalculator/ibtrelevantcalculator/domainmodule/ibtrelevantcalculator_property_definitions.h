//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       26.12.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTRELEVANTCALCULATOR_PROPERTY_DEFINITIONS_H
#define GUARD_IBTRELEVANTCALCULATOR_PROPERTY_DEFINITIONS_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarproperty_definitions.h>
#include <libbasarproperty_propertydescription.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace properties
{
    // in alphabetical order

    // article
	CONST_PROPERTY_DESCRIPTION( ARTICLE_NO,             "articleno",            basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( FIXREGIONAL,            "isfixedregional",      basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( ASSORTMENT_TYPE,        "assortmenttype",       basar::INT32    )
    CONST_PROPERTY_DESCRIPTION( BATCH_FLAG,				"batchflag",			basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( BRANCH_NO,              "branchno",             basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( COOL_ARTICLE_MODE,      "coolarticlemode",      basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( CONSIGNMENT_PARTNER_NO, "consignmentpartnerno", basar::INT32    )
    CONST_PROPERTY_DESCRIPTION( IBT_EXCLUDE_FLAG,       "ibtexcludeflag",       basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( NARCOTIC_FLAG,          "narcoticflag",         basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( NUM_OF_DEMAND,			"demand",				basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( PRIVATE_GOODS_TYPE,     "privategoods",         basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( PURCHASING_PRICE,       "purchasingprice",      basar::DECIMAL    )
	CONST_PROPERTY_DESCRIPTION( RELEVANCE_FLAG,         "relevanceflag",        basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_1,			"seasongroup1",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_2,			"seasongroup2",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_3,			"seasongroup3",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( SPECIAL_ARTICLE_TYPE,	"specialarticletype",   basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( STORAGE_LOCATION,       "storagelocation",      basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( UN_NO,					"unno",					basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( ARTICLE_LOCKED_FLAG,    "articlelock",          basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( CENTR_PU_ART_LOCKED_FLAG,"centrpuarticlelock",  basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( OUTSALE_DATE,		    "outsale",				basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_OLD,"hazard_old",			basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_NEW,"hazard_new",			basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( ABC_CATEGORY,			"abc_category",			basar::STRING    )
			
	// parameter
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_DEC,		"comparevaluedecimal",	basar::DECIMAL    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_INT,		"comparevalueint",		basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_STR,		"comparevaluestring",	basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( CONTEXT_NAME,	        "contextname",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( INTERVAL_END,	        "endvalue",			    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( INTERVAL_START,	        "startvalue",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( OPERATOR,		        "operator",				basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( PSEUDO_STORAGE_LOCATION,"pseudostoragelocation",basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( RULE_ID,				"ruleid",				basar::INT32    )

	CONST_PROPERTY_DESCRIPTION( FIXREGIONALASSIGNMENTFLAG, "considerfixregionalassignmentflag", basar::INT16    )
} // end namespace properties

#endif    // GUARD_IBTRELEVANTCALCULATOR_PROPERTIES_DEFINITIONS_H
