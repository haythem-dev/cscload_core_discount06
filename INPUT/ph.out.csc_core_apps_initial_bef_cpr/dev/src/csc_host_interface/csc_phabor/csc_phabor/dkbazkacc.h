//----------------------------------------------------------------------------
/*! \file		dkbazkacc.h
 *  \brief		Accessor for DKBAZK
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ACCDKBAZK_DKBAZKACC_H
#define GUARD_ACCDKBAZK_DKBAZKACC_H

//----------------------------------------------------------------------------
/*! \brief namespace for DKBAZK accessor.
 */

namespace acc_dkbazk
{
	// SELECTs
	BEGIN_QUERY_BUILDER_DECLARATION(SelectDKBAZKByPattern)
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION(UpdateDKBAZK)
	END_BUILDER_DECLARATION

} // namespace acc_dkbazk

//-----------------------------------------------------------------------------

#endif
