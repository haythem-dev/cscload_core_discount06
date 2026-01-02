//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief	
 *  \author		Steffen Heinlein
 *  \date		15.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSRECORD_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSRECORD_H

namespace domMod 
{		
namespace corpha
{    
namespace processOrder
{
	struct CICSRecord 
	{
		basar::Int32		CSCOrderNo;		// CONST_PROPERTY_DESCRIPTION( KSCANR,		"otrkscanr",	basar::INT32 )
		basar::Int32		SeqeuentialNo;	// CONST_PROPERTY_DESCRIPTION( LFDNR,		"otrlfdnr",		basar::INT32 )
		basar::VarString	RecordType;		// CONST_PROPERTY_DESCRIPTION( SA,			"otrsa",		basar::STRING )
		basar::VarString	Direction;		// CONST_PROPERTY_DESCRIPTION( DIRECTION,	"otrdirection",	basar::STRING )
		basar::VarString	Status;			// CONST_PROPERTY_DESCRIPTION( STATUS,		"otrstatus",	basar::STRING )
		basar::Int32		Time;			// CONST_PROPERTY_DESCRIPTION( ZEIT,		"otrzeit",		basar::INT32 )
		basar::VarString	Buffer;			// CONST_PROPERTY_DESCRIPTION( BUFFER,		"otrbuffer",	basar::STRING )			
	};
	   
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSRECORD_H
