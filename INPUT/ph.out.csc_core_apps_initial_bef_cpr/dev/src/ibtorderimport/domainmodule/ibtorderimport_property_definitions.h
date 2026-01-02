//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       26.12.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_PROPERTY_DEFINITIONS_H
#define GUARD_IBTORDERIMPORT_PROPERTY_DEFINITIONS_H

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

    // parameter
	CONST_PROPERTY_DESCRIPTION( BRANCH_NO,				"branchno",				basar::INT16    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_DEC,		"comparevaluedecimal",	basar::DECIMAL    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_INT,		"comparevalueint",		basar::INT32    )
	CONST_PROPERTY_DESCRIPTION( COMPARE_VALUE_STR,		"comparevaluestring",	basar::STRING    )
	CONST_PROPERTY_DESCRIPTION( CONTEXT_NAME,	        "contextname",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( INTERVAL_END,	        "endvalue",			    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( INTERVAL_START,	        "startvalue",		    basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( OPERATOR,		        "operator",				basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( PSEUDO_STORAGE_LOCATION,"pseudostoragelocation",basar::STRING   )
	CONST_PROPERTY_DESCRIPTION( RULE_ID,				"ruleid",				basar::INT32    )
	
} // end namespace properties

#endif    // GUARD_IBTORDERIMPORT_PROPERTIES_DEFINITIONS_H
