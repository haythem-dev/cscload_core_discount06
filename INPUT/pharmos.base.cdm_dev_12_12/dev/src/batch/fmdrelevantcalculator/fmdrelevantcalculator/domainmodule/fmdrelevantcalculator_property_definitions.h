//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Walid Haddad
 *  \date       14.12.2018
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_PROPERTY_DEFINITIONS_H
#define GUARD_FMDRELEVANTCALCULATOR_PROPERTY_DEFINITIONS_H

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
	CONST_PROPERTY_DESCRIPTION( ARTICLE_NO,             "artikel_nr",           basar::INT32 )
	CONST_PROPERTY_DESCRIPTION( ARZNEIMITTEL,           "arzneimittel",         basar::STRING)
	CONST_PROPERTY_DESCRIPTION( REZEPTPFL,				"rezeptpfl",			basar::STRING)
	CONST_PROPERTY_DESCRIPTION( TIERARZNEI,				"tierarznei",			basar::STRING)
	CONST_PROPERTY_DESCRIPTION( HOMOEOPATHIKUM,			"HOMOEOPATHIKUM",		basar::STRING)
	CONST_PROPERTY_DESCRIPTION( MEDIZINISCHE_GASE,		"MEDIZINISCHE_GASE",	basar::STRING)
	CONST_PROPERTY_DESCRIPTION( ATC_CODE,				"atccode",				basar::STRING)

	CONST_PROPERTY_DESCRIPTION( FMD_RELEVANT,			"fmd_relevant",			basar::INT16)
	CONST_PROPERTY_DESCRIPTION( BATCH_ARTICLE,			"chargenartikel",		basar::STRING)
	
	CONST_PROPERTY_DESCRIPTION( IFA_FMD_VAL,			"a11verihoc",			basar::INT32)
	CONST_PROPERTY_DESCRIPTION( DC_FMD_VAL,				"dc_faelschsicher",		basar::INT16)
	CONST_PROPERTY_DESCRIPTION( EXCEPTION_TYPE,			"exceptiontype",		basar::INT16)

	// parameter
	CONST_PROPERTY_DESCRIPTION( RULE_ID,				"ruleid",				basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( SEQUENCE_NO,			"sequenceno",			basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( ACTIVATION_FLAG,		"activationflag",		basar::INT16 )
	CONST_PROPERTY_DESCRIPTION( COMPARE_START,			"comparestartvalue",	basar::STRING)
	CONST_PROPERTY_DESCRIPTION( COMPARE_END,			"compareendvalue",		basar::STRING)
	
} // end namespace properties

#endif    // GUARD_FMDRELEVANTCALCULATOR_PROPERTY_DEFINITIONS_H
