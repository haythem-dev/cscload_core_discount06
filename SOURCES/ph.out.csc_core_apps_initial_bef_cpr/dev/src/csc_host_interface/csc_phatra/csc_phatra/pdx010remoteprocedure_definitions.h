//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions PDX010RemoteProcedure
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX010REMOTEPROCEDURE_DEFINITIONS_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX010REMOTEPROCEDURE_DEFINITIONS_H

namespace domMod
{
namespace pharmosTransaction
{
namespace preparation
{
	const basar::VarString	PROCEDURENAME( "PDX010" );	

	// DKBVZ Problems
	const basar::VarString	PDX010MESSAGE101( "0101 DKBVZ dataset not found" );
	const basar::VarString	PDX010MESSAGE102( "0102 DKBVZ file not open" );
	const basar::VarString	PDX010MESSAGE103( "0103 DKBVZ duplicate record" );
	const basar::VarString	PDX010MESSAGE105( "0104 DKBVZ end of file" );
	const basar::VarString	PDX010MESSAGE190( "0190 DKBVZ fatal error" );

	// DEBVZ Problems
	const basar::VarString	PDX010MESSAGE201( "0201 DEBVZ dataset not found" );
	const basar::VarString	PDX010MESSAGE202( "0202 DEBVZ file not open" );
	const basar::VarString	PDX010MESSAGE203( "0203 DEBVZ duplicate record" );
	const basar::VarString	PDX010MESSAGE204( "0204 DEBVZ end of file" );
	const basar::VarString	PDX010MESSAGE205( "0205 DEBVZ no space" );
	const basar::VarString	PDX010MESSAGE290( "0290 DEBVZ fatal error" );

	// DKPAR Problems
	const basar::VarString	PDX010MESSAGE301( "0301 DKPAR dataset not found" );
	const basar::VarString	PDX010MESSAGE302( "0302 DKPAR file not open" );
	const basar::VarString	PDX010MESSAGE303( "0303 DKPAR duplicate record" );
	const basar::VarString	PDX010MESSAGE304( "0304 DKPAR end of file" );
	const basar::VarString	PDX010MESSAGE305( "0305 DKPAR no space" );
	const basar::VarString	PDX010MESSAGE390( "0390 DKPAR fatal error" );

} 
}
}

//----------------------------------------------------------------------------

#endif

//----------------------------------------------------------------------------

