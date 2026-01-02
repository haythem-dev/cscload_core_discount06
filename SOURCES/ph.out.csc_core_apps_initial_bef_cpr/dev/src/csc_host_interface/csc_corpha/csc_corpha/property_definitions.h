//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Steffen Heinlein
 *  \date       22.10.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H
#define GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H

#include <libbasarproperty.h>

namespace properties
{	
	namespace dkotr
	{		
		CONST_PROPERTY_DESCRIPTION( KSCANR,		"otrkscanr",	basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( LFDNR,		"otrlfdnr",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( SA,			"otrsa",		basar::STRING )
		CONST_PROPERTY_DESCRIPTION( DIRECTION,	"otrdirection",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( STATUS,		"otrstatus",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( ZEIT,		"otrzeit",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( BUFFER,		"otrbuffer",	basar::STRING )
	} // dkotr

	namespace dkote
	{
		CONST_PROPERTY_DESCRIPTION( TIME,		"otetime",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KSCANR,		"otekscanr",	basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( LFDNR,		"otelfdnr",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( SA,			"otesa",		basar::STRING )
		CONST_PROPERTY_DESCRIPTION( TIME2,		"otetime2",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( DIRECTION,	"otedirection",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( STATUS,		"otestatus",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( ZEIT,		"otezeit",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( BUFFER,		"otebuffer",	basar::STRING )
	} // dkote

	namespace dkoto
	{
		CONST_PROPERTY_DESCRIPTION( TIME,		"ototime",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KSCANR,		"otokscanr",	basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( LFDNR,		"otolfdnr",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( TIME2,		"ototime2",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( SA,			"otosa",		basar::STRING )
		CONST_PROPERTY_DESCRIPTION( DIRECTION,	"otodirection",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( STATUS,		"otostatus",	basar::STRING )
		CONST_PROPERTY_DESCRIPTION( ZEIT,		"otozeit",		basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( BUFFER,		"otobuffer",	basar::STRING )
	} // dkoto

} // properties

#endif // GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H
