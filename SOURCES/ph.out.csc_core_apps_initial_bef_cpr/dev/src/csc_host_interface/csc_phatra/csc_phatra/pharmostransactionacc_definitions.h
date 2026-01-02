//----------------------------------------------------------------------------
/*! \file		pharmostransactionacc_definitions.h
 *  \brief		definitions pharmostransaction acc
 *  \author		Julian Machata
 *  \date		28.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_PHARMOSTRANSACTIONACCDEFINITIONS_H
#define GUARD_PHARMOSTRANSACTIONACCDEFINITIONS_H


namespace lit
{
namespace acc_pharmostransaction
{	
	// Accessor
	const basar::VarString	ACC_PHARMOSTRANSACTION              ( "AccPharmosTransaction" );

	// Access Methods
	//const basar::VarString	SELECT_PHARMOSTRANSACTION_BY_PATTERN( "SelectPharmosTransactionByPattern" );
	const basar::VarString	SELECT_LAST_KEY                     ( "SelectLastKey" );
	const basar::VarString	SELECT_OPEN_TRANSACTIONS            ( "SelectOpenTransactions" );
    

	const basar::VarString  SAVE_PHARMOSTRANSACTION             ( "SavePharmosTransaction" );

} // namespace acc_pharmostransaction
} // namespace lit

//----------------------------------------------------------------------------

#endif // GUARD_PHARMOSTRANSACTIONACCDEFINITIONS_H

//----------------------------------------------------------------------------

