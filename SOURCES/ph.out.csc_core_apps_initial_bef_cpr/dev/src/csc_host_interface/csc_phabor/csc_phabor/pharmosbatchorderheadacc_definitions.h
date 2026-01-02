//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions PharmosBatchOrderHeadACC
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LIT_ACCPHARMOSBATCHORDERHEAD_PHARMOSBATCHORDERHEADACCDEFINITIONS_H
#define GUARD_LIT_ACCPHARMOSBATCHORDERHEAD_PHARMOSBATCHORDERHEADACCDEFINITIONS_H

#include "cmndm.h"

namespace lit
{
namespace acc_pharmosbatchorderhead
{	
	// Accessor
	const basar::VarString	ACC_PHARMOSBATCHORDERHEAD( "AccPharmosBatchOrderHead" );

	// Access Methods
	const basar::VarString	SELECT_PHARMOSBATCHORDERHEAD_BY_PATTERN ( "SelectPharmosBatchOrderHeadByPattern" );
	const basar::VarString	SELECT_LAST_KEY						    ( "SelectLastKey" );
	const basar::VarString	SAVE_PHARMOSBATCHORDERHEAD				( "SavePharmosBatchOrderHead" );

} // namespace acc_pharmosbatchorderhead
} // namespace lit

//----------------------------------------------------------------------------

#endif

//----------------------------------------------------------------------------
