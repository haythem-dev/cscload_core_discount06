//----------------------------------------------------------------------------
/*! \file		pharmosbatchorderposacc.h
 *  \brief		Accessor for PHARMOSBATCHORDERPOS
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ACCPHARMOSBATCHORDERPOS_PHARMOSBATCHORDERPOSACC_H
#define GUARD_ACCPHARMOSBATCHORDERPOS_PHARMOSBATCHORDERPOSACC_H

//----------------------------------------------------------------------------
/*! \brief namespace for PHARMOSBATCHORDERPOS accessor.
 */

namespace acc_pharmosbatchorderpos
{
	// SELECTs
	BEGIN_QUERY_BUILDER_DECLARATION(SelectPharmosBatchOrderPosByPattern)
	END_BUILDER_DECLARATION

	BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectLastKey)
	END_BUILDER_DECLARATION		

	// MODIFIER
	BEGIN_WRITE_BUILDER_DECLARATION(InsertPharmosBatchOrderPos)
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION(UpdatePharmosBatchOrderPos)
	END_BUILDER_DECLARATION

} // namespace acc_pharmosbatchorderpos

//-----------------------------------------------------------------------------

#endif
