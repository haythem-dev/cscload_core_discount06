//----------------------------------------------------------------------------
/*! \file		pharmosbatchorderheadacc.h
 *  \brief		Accessor for PharmosBatchOrderHead
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ACCPHARMOSBATCHORDERHEAD_PHARMOSBATCHORDERHEADACC_H
#define GUARD_ACCPHARMOSBATCHORDERHEAD_PHARMOSBATCHORDERHEADACC_H

//----------------------------------------------------------------------------
/*! \brief namespace for PharmosBatchOrderHead accessor.
 */

namespace acc_pharmosbatchorderhead
{
	// SELECTs
	BEGIN_QUERY_BUILDER_DECLARATION(SelectPharmosBatchOrderHeadByPattern)
	END_BUILDER_DECLARATION

	BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectLastKey)
	END_BUILDER_DECLARATION		

	// MODIFIER
	BEGIN_WRITE_BUILDER_DECLARATION(InsertPharmosBatchOrderHead)
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION(UpdatePharmosBatchOrderHead)
	END_BUILDER_DECLARATION

} // namespace acc_pharmosbatchorderhead

//-----------------------------------------------------------------------------

#endif
