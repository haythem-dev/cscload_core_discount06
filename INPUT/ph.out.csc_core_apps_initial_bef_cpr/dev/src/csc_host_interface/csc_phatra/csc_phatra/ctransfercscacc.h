//----------------------------------------------------------------------------
/*! \file		ctransfercscacc.h
 *  \brief		Accessor for ZDP table ctransfercsc
 *  \author		Frank Naumann
 *  \date		23.01.2015
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CTRANSFERCSCACC_H
#define GUARD_CTRANSFERCSCACC_H

#include <libbasardbaspect.h>

//----------------------------------------------------------------------------
/*! \brief namespace for DKBVZ accessor.
 */

namespace acc_ctransfercsc
{
	BEGIN_QUERY_BUILDER_DECLARATION(SelectChangeRecords)
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION(UpdateChangeRecord)
	END_BUILDER_DECLARATION

} // namespace acc_ctransfercsc

//-----------------------------------------------------------------------------

#endif // GUARD_CTRANSFERCSCACC_H

