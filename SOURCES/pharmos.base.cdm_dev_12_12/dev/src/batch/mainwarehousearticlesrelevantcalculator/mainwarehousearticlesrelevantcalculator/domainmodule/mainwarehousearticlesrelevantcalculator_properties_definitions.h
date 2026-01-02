#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_PROPERTIES_DEFINITIONS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_PROPERTIES_DEFINITIONS_H

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
    basar::ConstString NAMESPACE_NAME( "properties" );

    // in alphabetical order
    CONST_PROPERTY_DESCRIPTION( BRANCH_NO,                    "branchno",              basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( BRANCH_NO_MAINWAREHOUSE,      "branchnomainwarehouse", basar::INT16   )

    // article
    CONST_PROPERTY_DESCRIPTION( ARTICLE_LOCKED_FLAG,          "articlelock",           basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( ARTICLE_NO,                   "articleno",             basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( BATCH_FLAG,                   "batchflag",             basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( CENTRALPURCHASE_LOCKED_FLAG,  "centralpurchaselock",   basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( CONSIGNMENT_PARTNER_NO,       "consignmentpartnerno",  basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( COOL_ARTICLE_MODE,            "coolarticlemode",       basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( CREATION_DATE,                "creationdate",          basar::DATE    )
    CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_NEW,      "hazard_new",            basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_OLD,      "hazard_old",            basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( IBT_RELEVANT_COUNT,           "ibtrelevantcount",      basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( LAST_PROGNOSIS_DATE,          "lastprognosisdate",     basar::INT32   )
	CONST_PROPERTY_DESCRIPTION( MANUAL_SIGNED_ZDP,		      "manualsignedzdp",       basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( NARCOTIC_FLAG,                "narcoticflag",          basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( OUTSALE_DATE,                 "outsale",               basar::DATE    )
    CONST_PROPERTY_DESCRIPTION( PREVIOUS_RELEVANCE_FLAG,      "previousrelevanceflag", basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( PROGNOSIS,                    "prognosis",             basar::FLOAT64 )
    CONST_PROPERTY_DESCRIPTION( PURCHASING_PRICE,             "purchasingprice",       basar::DECIMAL )
	CONST_PROPERTY_DESCRIPTION( REGISTRABLE_FLAG,             "registrableflag",       basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( RELEVANCE_FLAG,               "relevanceflag",         basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_1,               "seasongroup1",          basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_2,               "seasongroup2",          basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( SEASON_GROUP_3,               "seasongroup3",          basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( SPECIAL_ARTICLE_TYPE,         "specialarticletype",    basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( STORAGE_LOCATION,             "storagelocation",       basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( STORAGE_LOCATION_MAINWH,      "storagelocationmainwh", basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( UN_NO,				          "unno",                  basar::STRING  )
	CONST_PROPERTY_DESCRIPTION( REGIONALARTICLE_FLAG,		  "regionalarticleflag",   basar::STRING  )
	CONST_PROPERTY_DESCRIPTION( UNDERDELIVERYQUOTA_LIMIT,	  "underdeliveryquotalimit", basar::INT32 )
	CONST_PROPERTY_DESCRIPTION( UNDERDELIVERYQUOTA_VAL,       "underdeliveryquotaval", basar::INT32   )
	CONST_PROPERTY_DESCRIPTION( STAMMLAGER_FLAG,			  "stammlagerkennz",	   basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( ADMISSION_PARAM_GROUPID,      "admissionparamgroupid", basar::INT16  )
    // parameter
    CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_DEC,            "comparevaluedecimal",   basar::DECIMAL )
    CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_INT,            "comparevalueint",       basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_STR,            "comparevaluestring",    basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( CONTEXT_NAME,                 "contextname",           basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( INT_INTERVAL_END,             "endvalueinteger",       basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( INT_INTERVAL_START,           "startvalueinteger",     basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( OPERATOR,                     "operator",              basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( RULEID,                       "ruleid",                basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( STRING_INTERVAL_END,          "endvaluestring",        basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( STRING_INTERVAL_START,        "startvaluestring",      basar::STRING  )

    // storagelocationslot
    CONST_PROPERTY_DESCRIPTION( PSEUDO_STORAGE_LOCATION, "pseudostoragelocation", basar::STRING  )
} // end namespace properties

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_PROPERTIES_DEFINITIONS_H
