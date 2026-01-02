//----------------------------------------------------------------------------
/*! \file		dkoteacc.h
 *  \brief		Accessor for DKOTE
 *  \author		Steffen Heinlein
 *  \date		24.05.2013
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ACCDKOTE_DKOTEACC_H
#define GUARD_ACCDKOTE_DKOTEACC_H

//! \note This include is just for doxygen!
#include <libbasardbaspect_macros.h>

namespace acc_dkote
{	

	BEGIN_WRITE_BUILDER_DECLARATION(InsertDKOTE)
	END_BUILDER_DECLARATION	

	BEGIN_WRITE_BUILDER_DECLARATION(UpdateDKOTE)
	END_BUILDER_DECLARATION	
		
	BEGIN_QUERY_BUILDER_DECLARATION(SelectDKOTEByPattern)
	END_BUILDER_DECLARATION		

	BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectDKOTECountByPattern)
	END_BUILDER_DECLARATION		
} // namespace acc_dkote

#endif
