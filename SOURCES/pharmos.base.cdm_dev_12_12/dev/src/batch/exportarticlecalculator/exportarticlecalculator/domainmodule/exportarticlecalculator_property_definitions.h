//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       26.12.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_PROPERTY_DEFINITIONS_H
#define GUARD_EXPORTARTICLECALCULATOR_PROPERTY_DEFINITIONS_H

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
    // article
	CONST_PROPERTY_DESCRIPTION( ARTICLE_NO,             "articleno",            basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( BRANCH_NO,              "branchno",             basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( COOL_ARTICLE_MODE,      "coolarticlemode",      basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( NARCOTIC_FLAG,          "narcoticflag",         basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( EXPORTPERMISSION_FLAG,  "permissionflag",       basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( STORAGE_LOCATION,       "storagelocation",      basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( UN_NO,					"unno",					basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( ARTICLE_LOCKED_FLAG,    "articlelock",          basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( OUTSALE_DATE,		    "outsale",				basar::INT32    )


	CONST_PROPERTY_DESCRIPTION( NOTIFIABLE_FLAG,		"meldepfl",				basar::STRING )
	CONST_PROPERTY_DESCRIPTION( EXPLOSION_FLAG,			"explosionflag",		basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( PSYCHOTROPIC_FLAG,		"psychotropicflag",		basar::STRING )
	CONST_PROPERTY_DESCRIPTION( ANIMAL_MEDICINE_FLAG,	"animalmedicineflag",	basar::STRING )
	CONST_PROPERTY_DESCRIPTION( MEDICINE_FLAG,			"medicineflag",			basar::STRING )
	CONST_PROPERTY_DESCRIPTION( HOMEOPATHY_FLAG,		"homeopathyflag",		basar::STRING )
	CONST_PROPERTY_DESCRIPTION( ANTHROPOSOPHIC_FLAG,	"anthroposophicflag",	basar::STRING )
	CONST_PROPERTY_DESCRIPTION( EXPIRY_DATE,			"expiry",				basar::INT32 )
	CONST_PROPERTY_DESCRIPTION( DISTRIBUTION_BINDING_MODE,	"distributionrestr",basar::STRING )
	CONST_PROPERTY_DESCRIPTION( DISTRIBUTION_BINDING_IFA,	"distributionifa",	basar::STRING )
	CONST_PROPERTY_DESCRIPTION( PRISMAE_NO,				"prismaewoche",			basar::INT32 )
	CONST_PROPERTY_DESCRIPTION( BIOZID_FLAG,			"biozidflag",			basar::STRING )		
	CONST_PROPERTY_DESCRIPTION( ACTIVE_ARTICLE_FLAG,	"articleactivflag",		basar::STRING )
	CONST_PROPERTY_DESCRIPTION( ATC_CODE,				"atccode",				basar::STRING )
	CONST_PROPERTY_DESCRIPTION( EXPORT_BLOCK_FLAG,		"exportblockflag",		basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( NARCOTIC_SUBSTANCE_FLAG,"narcsubstanceflag",	basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_OLD,"hazardold",			basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( HAZARDOUS_SUBSTANCE_NEW,"hazardnew",			basar::INT16 )
			
	// parameter
	CONST_PROPERTY_DESCRIPTION( COUNTRY_CODE,           "country_ifacode",      basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( ACTIVATION_FLAG,		"activationflag",		basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_END,	        "compareendvalue",	    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( COMPARE_START,	        "comparestartvalue",	basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( PSEUDO_STORAGE_LOCATION,"pseudostoragelocation",basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( RULE_ID,				"ruleid",				basar::INT16    )
	
} // end namespace properties

#endif    // GUARD_EXPORTARTICLECALCULATOR_PROPERTY_DEFINITIONS_H
