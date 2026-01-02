//----------------------------------------------------------------------------
/*! \file		dkotoacc.h
 *  \brief		Accessor for DKOTO
 *  \author		Steffen Heinlein
 *  \date		24.05.2013
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ACCDKOTO_DKOTOACC_H
#define GUARD_ACCDKOTO_DKOTOACC_H

//! \note This include is just for doxygen!
#include <libbasardbaspect_macros.h>

namespace acc_dkoto
{	

	BEGIN_WRITE_BUILDER_DECLARATION(InsertDKOTO)
	END_BUILDER_DECLARATION	

	BEGIN_WRITE_BUILDER_DECLARATION(UpdateDKOTO)
	END_BUILDER_DECLARATION	
		
	BEGIN_QUERY_BUILDER_DECLARATION(SelectDKOTOByPattern)
	END_BUILDER_DECLARATION		

	BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectDKOTOCountByPattern)
	END_BUILDER_DECLARATION		

} // namespace acc_dkoto

#endif
