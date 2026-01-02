//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions PDX050RemoteProcedure
 *  \author		Steffen Heinlein
 *  \date		11.07.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX050REMOTEPROCEDURE_DEFINITIONS_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_PDX050REMOTEPROCEDURE_DEFINITIONS_H

namespace domMod
{
namespace batchOrder
{
namespace preparation
{
	const basar::VarString	PROCEDURENAMEPDX050( "PDX050" );	

	// DKBVZ Problems
	const basar::VarString	PDX050MESSAGE101( "0101 DKBAZ dataset not found" );
	const basar::VarString	PDX050MESSAGE102( "0102 DKBAZ file not open" );
	const basar::VarString	PDX050MESSAGE103( "0103 DKBAZ duplicate record" );
	const basar::VarString	PDX050MESSAGE105( "0104 DKBAZ end of file" );
	const basar::VarString	PDX050MESSAGE190( "0190 DKBAZ fatal error" );

	// DEBVZ Problems
	const basar::VarString	PDX050MESSAGE201( "0201 DEBAZ dataset not found" );
	const basar::VarString	PDX050MESSAGE202( "0202 DEBAZ file not open" );
	const basar::VarString	PDX050MESSAGE203( "0203 DEBAZ duplicate record" );
	const basar::VarString	PDX050MESSAGE204( "0204 DEBAZ end of file" );
	const basar::VarString	PDX050MESSAGE205( "0205 DEBAZ no space" );
	const basar::VarString	PDX050MESSAGE290( "0290 DEBAZ fatal error" );

	// DKPAR Problems
	const basar::VarString	PDX050MESSAGE301( "0301 DKPAR dataset not found" );
	const basar::VarString	PDX050MESSAGE302( "0302 DKPAR file not open" );
	const basar::VarString	PDX050MESSAGE303( "0303 DKPAR duplicate record" );
	const basar::VarString	PDX050MESSAGE304( "0304 DKPAR end of file" );
	const basar::VarString	PDX050MESSAGE305( "0305 DKPAR no space" );
	const basar::VarString	PDX050MESSAGE390( "0390 DKPAR fatal error" );

	// INDICATORS
	const basar::VarString PDX050UPDATEYES( "J" );
	const basar::VarString PDX050UPDATENO( "N" );

} 
}
}

//----------------------------------------------------------------------------

#endif
