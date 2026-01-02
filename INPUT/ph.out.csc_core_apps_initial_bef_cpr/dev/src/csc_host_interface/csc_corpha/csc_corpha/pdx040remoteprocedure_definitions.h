//----------------------------------------------------------------------------
/*! \file		pdx040remoteprocedure_definitions.h
 *  \brief		definitions PDX040RemoteProcedure
 *  \author		Steffen Heinlein
 *  \date		22.08.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_DEFINITIONS_H

namespace domMod
{
	namespace corpha
	{
		const basar::VarString	PROCEDURENAME( "PDX041" );		

		const basar::VarString  PDX040MESSAGE1000( "1000 OTRANOTAVAILABLE" );
		const basar::VarString  PDX040MESSAGE1001( "1001 OTRPNOTAVAILABLE" );
		const basar::VarString  PDX040MESSAGE1002( "1002 OTRRNERROR" );
		const basar::VarString	PDX040MESSAGE2000( "2000 Duplicate order." );
		const basar::VarString  PDX040MESSAGE3100( "3100 DKKUL not found." );
		const basar::VarString  PDX040MESSAGE3200( "3200 DKKUI not found." );
		const basar::VarString  PDX040MESSAGE4100( "4100 ABENOTOPEN." );
		const basar::VarString  PDX040MESSAGE4200( "4200 DKART problem." );
		const basar::VarString  PDX040MESSAGE5000( "5000 PA12 problem." );
		const basar::VarString  PDX040MESSAGE5100( "5100 PA14 problem." );
		const basar::VarString  PDX040MESSAGE9000( "9000 ERRCONNECT." );
		const basar::VarString  PDX040MESSAGE9100( "9100 A1 enter problem." );
		const basar::VarString  PDX040MESSAGE9200( "9200 A1 write problem." );
		const basar::VarString  PDX040MESSAGE9300( "9300 LORBAS open error." );
		const basar::VarString  PDX040MESSAGE9400( "9400 Q4 problem." );
		const basar::VarString  PDX040MESSAGE9500( "9500 P1 problem." );
		const basar::VarString  PDX040MESSAGE9600( "9600 Q1 problem." );
		const basar::VarString  PDX040MESSAGE9800( "9800 Q8 problem." );
	}
}

//----------------------------------------------------------------------------

#endif // GUARD_DOMMOD_CORPHA_PDX040REMOTEPROCEDURE_DEFINITIONS_H
