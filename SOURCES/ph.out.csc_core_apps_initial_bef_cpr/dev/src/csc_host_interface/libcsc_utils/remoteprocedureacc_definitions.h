//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions RemoteProcedureACC
 *  \author		Steffen Heinlein
 *  \date		21.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LIT_ACC_REMOTEPROCEDURE_REMOTEPROCEDUREACCDEFINITIONS_H
#define GUARD_LIT_ACC_REMOTEPROCEDURE_REMOTEPROCEDUREACCDEFINITIONS_H

#include <libbasarproperty.h>

//! namespace containing all database - fieldnames used for matching / accessing properties
namespace lit 
{
	namespace acc_remoteprocedure
	{
		// RemoteProcedure Accessor
		const basar::VarString	ACC_REMOTEPROCEDURE( "AAccRemoteProcedure" );

		const basar::VarString  DEFAULT_STORED_PROCEDURE( "TCASTP" );

		// Access Methods
		const basar::VarString	CALL_REMOTEPROCEDURE( "amCallRemoteProcedure" );

		// Properties
		CONST_PROPERTY_DESCRIPTION( REMOTEPROCEDURENAME,	"remoteProcedureName",		basar::STRING)
		CONST_PROPERTY_DESCRIPTION( REMOTEPROCEDUREQUERY,	"param",					basar::STRING)
		CONST_PROPERTY_DESCRIPTION( STOREDPROCEDURE,		"storedprocedure",			basar::STRING)

	} // namespace acc_remoteprocedure
} // namespace lit

//----------------------------------------------------------------------------

#endif // GUARD_LIT_ACC_REMOTEPROCEDURE_REMOTEPROCEDUREACCDEFINITIONS_H

//----------------------------------------------------------------------------
