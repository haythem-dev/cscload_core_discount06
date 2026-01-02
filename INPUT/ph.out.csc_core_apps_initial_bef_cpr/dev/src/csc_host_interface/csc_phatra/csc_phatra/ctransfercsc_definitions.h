//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions ctransfercsc
 *  \author		Frank Naumann
 *  \date		23.01.2015
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CTRANSFERCSC_DEFINITIONS_H
#define GUARD_CTRANSFERCSC_DEFINITIONS_H

#include <libbasarcmnutil_bstring.h>

namespace lit
{
namespace acc_ctransfercsc
{	
	// Accessor
	const basar::VarString	ACC_CTRANSFERCSC( "AccCTransferCsc" );
	const basar::VarString	ACC_CTRANSFERCSC_INSTANCE( "AccInstCTransferCsc" );

	// Access Methods
	const basar::VarString	SELECT_CTRANSFERCSC_BY_PATTERN( "SelectChangeRecords" );
	const basar::VarString	SAVE_CTRANSFERCSC( "UpdateChangeRecord" );

} // namespace acc_ctransfercsc
} // namespace lit

//----------------------------------------------------------------------------

#endif // GUARD_CTRANSFERCSC_DEFINITIONS_H

//----------------------------------------------------------------------------

